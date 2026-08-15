{
    files = {
        "files/bridge.cpp"
    },
    values = {
        "/usr/bin/g++",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-std=c++23",
            "-DNDEBUG"
        }
    },
    depfiles = "bridge.o: files/bridge.cpp files/global.hpp\
",
    depfiles_format = "gcc"
}