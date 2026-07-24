{
    depfiles_format = "gcc",
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
    files = {
        "../data/logs/enginelog_c++/commonlog.cpp"
    },
    depfiles = "commonlog.o: ../data/logs/enginelog_c++/commonlog.cpp\
"
}