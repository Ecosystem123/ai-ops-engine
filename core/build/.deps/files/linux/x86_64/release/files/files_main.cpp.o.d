{
    depfiles_format = "gcc",
    files = {
        "files/files_main.cpp"
    },
    depfiles = "files_main.o: files/files_main.cpp\
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