target("libcorecrypto_static")
    set_kind("static")
    set_basename("corecrypto_static")

    add_sysincludedirs("$(projectdir)/include")

    add_files(
        "src/**.c"
    )

    if is_arch("x86_64", "i386") then
        add_files("src/aes/intel/**.c")
        add_files("src/aes/intel/opt/AES.s")
    end

    remove_files(
        "src/kext/*.c",
        "src/kprng/*.c",
        "src/kprng/**.c"
    )

    add_cflags("-Wno-incompatible-pointer-types", "-Wno-int-conversion")

    if is_plat("linux") then
        add_defines("CC_LINUX_ASM=1")
    end

target("libcorecrypto")
    set_kind("shared")
    set_basename("corecrypto")

    add_sysincludedirs("$(projectdir)/include")

    add_files(
        "src/**.c"
    )

    if is_arch("x86_64", "i386") then
        add_files("src/aes/intel/**.c")
        add_files("src/aes/intel/opt/AES.s")
    end

    -- The yarrow PRNG won't compile for Linux, and I doubt it'll compile on Windows without modifications.
    -- Also I don't think we want Darwin Kernel Extension code compiled on a non-Darwin (or non-Userspace) platform.
    remove_files(
        "src/kext/*.c",
        "src/kprng/*.c",
        "src/kprng/**.c"
    )

    add_cflags("-Wno-incompatible-pointer-types", "-Wno-int-conversion")

    if is_plat("linux") then
        add_defines("CC_LINUX_ASM=1")
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

    add_cflags("-Wno-incompatible-pointer-types", "-Wno-int-conversion")

    if is_plat("linux") then
        add_defines("CC_LINUX_ASM=1")
    end

target("cctest")
    set_kind("binary")

    -- Link with the static version of libcorecrypto.
    add_deps("libcorecrypto_static")

    add_sysincludedirs("$(projectdir)/include")

    add_files("$(projectdir)/cctest/*.c")
