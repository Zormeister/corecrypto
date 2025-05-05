target("libcorecrypto_static")
    set_kind("static")
    set_basename("corecrypto_static")

    add_sysincludedirs("$(projectdir)/include")

    add_files(
        "src/*.c",
        "src/**.c",
        "src/aes/**.c"
    )

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

    add_deps("libcorecrypto_static")

    add_sysincludedirs("$(projectdir)/include")

    add_files("$(projectdir)/cctest/*.c")
