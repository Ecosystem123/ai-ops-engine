{
    depfiles = "main.o: src/main.cpp src/../../data/logs/enginelog_c++/commonlog.hpp\
",
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
    files = {
        "src/main.cpp"
    }
}