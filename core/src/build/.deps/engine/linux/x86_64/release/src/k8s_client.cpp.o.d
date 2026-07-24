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
    depfiles = "k8s_client.o: src/k8s_client.cpp\
",
    files = {
        "src/k8s_client.cpp"
    }
}