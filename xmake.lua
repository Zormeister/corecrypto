set_policy("check.auto_ignore_flags", false)

if is_plat("linux") then
    includes("llvm_toolchain.lua")

   --  set_toolchains("llvm-linux")
end

target("libcorecrypto_static")
    set_kind("static")
    set_basename("corecrypto_static")

    add_sysincludedirs("$(projectdir)/include")

    add_files(
        "src/**.c"
    )

    if is_arch("x86_64", "i386") then
        add_files("src/aes/intel/*.c")
        add_files("src/aes/intel/*.s")

        remove_files(
            "src/aes/intel/Data.s",
            "src/aes/intel/EncryptDecrypt.s",
            "src/aes/intel/ExpandKeyForDecryption.s",
            "src/aes/intel/ExpandKeyForEncryption.s"
        )
    end

    remove_files(
        "src/kext/*.c",
        "src/kprng/*.c",
        "src/kprng/**.c"
    )

    add_cflags("-Wincompatible-pointer-types", "-Wno-int-conversion")
    add_asflags("-x assembler-with-cpp")

    if is_plat("linux") then
        add_cflags("-DCC_LINUX_ASM=1")
        add_asflags("-DCC_LINUX_ASM=1")
    end

target("libcorecrypto")
    set_kind("shared")
    set_basename("corecrypto")

    add_sysincludedirs("$(projectdir)/include")

    add_files(
        "src/**.c"
    )

    if is_arch("x86_64", "i386") then
        add_files("src/aes/intel/*.c")
        add_files("src/aes/intel/*.s")

        remove_files(
            "src/aes/intel/Data.s",
            "src/aes/intel/EncryptDecrypt.s",
            "src/aes/intel/ExpandKeyForDecryption.s",
            "src/aes/intel/ExpandKeyForEncryption.s"
        )
    end

    -- The yarrow PRNG won't compile for Linux, and I doubt it'll compile on Windows without modifications.
    -- Also I don't think we want Darwin Kernel Extension code compiled on a non-Darwin (or non-Userspace) platform.
    remove_files(
        "src/kext/*.c",
        "src/kprng/*.c",
        "src/kprng/**.c"
    )

    add_cflags("-Wincompatible-pointer-types", "-Wno-int-conversion")
    add_asflags("-x assembler-with-cpp")
    add_ldflags("-fPIC")

    if is_plat("linux") then
        add_cflags("-DCC_LINUX_ASM=1")
        add_asflags("-DCC_LINUX_ASM=1")
    end

target("libcorecrypto_noasm")
    set_kind("shared")
    set_basename("corecrypto_noasm")

    add_sysincludedirs("$(projectdir)/include")

    add_files(
        "src/**.c"
    )

    -- Build a non-Assembly utilising copy of corecrypto for sanity's sake.
    -- Can't have a crypto library if it doesn't work without assembly.
    -- Or compiler intrinsics for that matter.
    add_defines("CC_USE_ASM=0")

    remove_files(
        "src/kext/*.c",
        "src/kprng/*.c",
        "src/kprng/**.c"
    )

    add_cflags("-Wincompatible-pointer-types", "-Wno-int-conversion")

target("cctest")
    set_kind("binary")

    -- Link with the static version of libcorecrypto.
    add_deps("libcorecrypto_static")

    add_sysincludedirs("$(projectdir)/include")

    add_files("$(projectdir)/cctest/*.c")
