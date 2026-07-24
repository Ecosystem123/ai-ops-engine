{
    values = {
        "/usr/bin/g++",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-std=c++23",
            "-DSPDLOG_SHARED_LIB",
            "-DSPDLOG_COMPILED_LIB",
            "-DSPDLOG_FMT_EXTERNAL",
            "-DNDEBUG"
        }
    },
    depfiles_format = "gcc",
    depfiles = "main.o: src/main.cpp\
",
    files = {
        "src/main.cpp"
    }
}