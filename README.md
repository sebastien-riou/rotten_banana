# rotten_banana whitebox AES
"whitebox" implementation of AES-128 encryption for [whibox 2017 CTF][whibox] (it is known there as "bright_morse" aka challenge #753).

[whibox]: https://whibox.cr.yp.to/ "whibox"

The challenge is to find the key hidden in the code.

### How to be sure it really implements AES ?
The file testvectors100K contains reference plain-text/cipher-text generated by an [independent AES implementation][8a068216]. This is only 100K tests, so it does not prove anything but give some confidence and plenty of "safe" inputs for generating traces. rotten_banana passed this test on two different machine running different Linux distributions. That's how I convinced myself it computes AES correctly. Another matter is to convince yourself that I tell the truth. One way to do that is to use the [obliv-c][12c6a91c] framework. Feel free to [contact me][0f449899] to setup a connection and try one or two of your desired input.

  [0f449899]: https://www.linkedin.com/in/sebastien-riou-99931220 "contact"
  [12c6a91c]: https://github.com/samee/obliv-c "obliv-c"
  [8a068216]: https://pypi.python.org/pypi/pycrypto "pycrypto"

### Why is it so big and so slow ?
It is tailor made for the whibox 2017 CTF. The setup is somewhat favorable to attackers since challenges are given in C source files. To compensate the allowed size and performances are relaxed: 50MB limit on source size, 20MB on RAM size and 1 second for execution (on a reference machine). The challenges earn points only by remaining unbroken over time, code size and performances don't impact points in any way. In this context, it makes sense to slow down performances as much as allowed and bury the useful data within large tables.  

### I found the key, now what ?
Congratulations! I'd love to hear how you managed it, especially if you worked without source level changes. Don't spoil the fun for others though, keep the key secret!

If you want to prove the world that you got it, send a pull request with the plain-text/cipher-text of your choice.
For example, let's say the key is 00112233445566778899AABBCCDDEEFF:

First convert your text into 16 hex bytes:
```
$ str2hex "YYYYMM your name"
595959594d4d20796f7572206e616d65
```

This is the desired cipher text. Now compute the corresponding plain text by decrypting with the key:
```
$ aes128_dec -key 00112233445566778899AABBCCDDEEFF -dat 595959594d4d20796f7572206e616d65
1A372B2D_8D6B7DE6_9FE89645_289F7225
```

Check you did use the right key:
```
$ rotten_banana 1A372B2D_8D6B7DE6_9FE89645_289F7225
59595959_4D4D2079_6F757220_6E616D65
```

Submit a pull request on this file with the following text at the end:

plain-text  | cipher-text  | cipher-text as ascii  | comments
--|---|---|--
1A372B2D8D6B7DE69FE89645289F7225  | 595959594d4d20796f7572206e616d65  | "YYYYMM your name"  | CPA on 50 traces using tool XYZ
  |   |   |  
