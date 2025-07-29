# CoreCrypto Project Priorities

## Bootloader/Pre-Boot environments

CoreCrypto *can* be used in pre-boot (and embedded!) environments, Apple's own version builds for SEPOS, SEPROM, and even RTKit!

AES in the XTS mode has been made available, so file-systems making use of Full Disk Encryption can be backed using CoreCrypto.

For these environments I suggest that the following functions are prioritised:
- A proper RNG based off of the available DRBG subsystem
- RSA signature verification is accessible (for cryptographic validation).
- Digests are available for hashing (SHA-1 and SHA-2 are more than enough, and already complete).

## Kernel-space

AES now has support for 192-bit and 256-bit keys in ECB mode, other ciphers, like CAST and Blowfish, now have code.

Whilst this is wonderful progress, there is still work to be done.

Notably:
- The ChaCha20 + Poly1305 enc + auth algorithm, and it's associated funcions [see this header](include/corecrypto/ccchacha20poly1305.h)
- The RSA functions `ccrsa_make_pub` and `ccrsa_verify_pkcs1v15`

## Userspace

dare i say it. read [DARWIN19.md](DARWIN19.md) and weep.

commoncrypto won't even build without ec key handling.
or diffie-hellman for that matter.
