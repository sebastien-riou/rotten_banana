# rotten_banana
"whitebox" implementation of AES-128 encryption for whibox 2017 CTF.

The challenge is to find the key hidden in the code. (it will be published here as soon as it is accepted by the CTF system)

### I found the key, now what ?
Congratulations! I'd love to hear how you managed it. Don't spoil the fun for others though, keep the key secret!

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
1A372B2D8D6B7DE69FE89645289F7225  | 595959594d4d20796f7572206e616d65  | "YYYYMM your name"  | CPA using tool XYZ
  |   |   |  
