{
    files = {
        "files/main.cpp"
    },
    depfiles_format = "gcc",
    depfiles = "main.o: files/main.cpp\
",
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
    }
}