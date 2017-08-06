#!/usr/bin/env python3

from Crypto.Cipher import AES
import sys
import sys, string, os
import subprocess
import re
import multiprocessing
from multiprocessing import Process, Queue, current_process, freeze_support


def extract_result(stdout,stderr):
    if(len(stderr)):
        print("ERROR reported on stderr:\n%s"%stderr)
        print("stdout:\n%s"%stdout)
        raise ValueError("message on stderr not empty")
    #lower case, remove 0x
    out=str(stdout.lower())
    out=out.replace("0x","")
    #remove all non hex digits,
    out = re.sub("[^0-9,a-f]", "", out)
    #keep only the last 32
    out = out[-32:]
    return out

def check_test_vector(n,message,expected):
    p = subprocess.Popen([impl,message],stdout=subprocess.PIPE,stderr=subprocess.PIPE)
    full_out, err = p.communicate()
    out = extract_result(full_out,err)
    print("%6u %s %s"%(n,message,out))
    if(expected!=out):
        print("ERROR: result mismatch for input %s"%message)
        print("result:   '%s'"%out)
        print("expected: '%s'"%expected)
        print("\nstdout:\n%s"%full_out)
        return 0
    return 1

# Function run by worker processes
def worker(input, output):
    for n,message,expected in iter(input.get, 'STOP'):
        result = check_test_vector(n,message,expected)
        output.put(result)

if __name__ == '__main__':
    freeze_support()
    n_cpus = multiprocessing.cpu_count()

    if(len(sys.argv)!=2):
        print("usage: %s <aes_program>"%sys.argv[0])
        print("enter test vector via stdin.")
        exit(-1)

    impl = sys.argv[1]

    # Create queues
    task_queue = Queue(n_cpus*2)
    done_queue = Queue()

    # Start worker processes
    for i in range(n_cpus):
        Process(target=worker, args=(task_queue, done_queue)).start()

    message = sys.stdin.readline().replace("\n","")
    cnt=1
    res_cnt=1
    for line in sys.stdin:
        expected=line.replace("\n","")

        #send task to one of the workers
        task_queue.put([cnt,message,expected])
        cnt=cnt+1
        message=expected

        #check if any result is available
        try:
            while res_cnt<cnt-n_cpus:
                res=done_queue.get_nowait()
                res_cnt=res_cnt+1
                if res==0:
                    print("KO!")
                    # Tell child processes to stop
                    for i in range(n_cpus):
                        task_queue.put('STOP')
                    exit(-1)
        except:
            pass

    # Tell child processes to stop
    for i in range(n_cpus):
        task_queue.put('STOP')

    while res_cnt<cnt:
        try:
            res=done_queue.get_nowait()
            res_cnt=res_cnt+1
            if res==0:
                print("KO!")
                exit(-1)
        except:
            pass
