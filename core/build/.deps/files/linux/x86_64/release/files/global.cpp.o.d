{
    depfiles = "global.o: files/global.cpp files/global.hpp\
",
    files = {
        "files/global.cpp"
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
    depfiles_format = "gcc"
}