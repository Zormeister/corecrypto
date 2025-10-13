# corecrypto

> [!WARNING]
> This project contains experimental (and highly unstable) code!
> Do **NOT** use this project in a production environment!
>
> Additionally, this project relies on private headers from XNU for both `libcorecrypto` and `corecrypto_kernel` on Darwin based platforms.
>
> The `VNG` (which allegedly stands for Apple's Vector & Numerics Group CoreOS team) implementations of AES are currently untested.
>
> This project is also untested, so the chance for logic bugs is high. Currently, work is being done to implement a unit testing framework.
>

The `corecrypto` project is a low-level cryptography library designed for portability and ease of use, supplying digest functions and encryption modes, alongside other crypographic operations.

The `corecrypto` project has several targets:
- `libcorecrypto`, the userspace library target.
- `libcorecrypto_noasm`, the userspace library target without any assembly.
- `corecrypto_kernel`, the kernel extension for Darwin, utilised by XNU and other components.
- `libcc_test`, all of the source code under the [test](src/test) directory for runtime testing if `libcorecrypto` was configured without testing infrastructure.

Despite the similar name, this library is **not** based on the released
source bundle for Apple’s corecrypto implementation, because that code
is not licensed for re-use. This library is based on the
[botan](https://github.com/randombit/botan) and [LibTomCrypt](https://github.com/libtom/libtomcrypt/) libraries, as well as the
[pdcrypto](https://github.com/rafirafi/pdcrypto) code
