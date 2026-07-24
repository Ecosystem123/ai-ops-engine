{
    depfiles = "main.o: src/main.cpp src/../../data/logs/enginelog_c++/commonlog.hpp\
",
    files = {
        "src/main.cpp"
    },
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
            "-isystem",
            "/home/abhinandps/.xmake/packages/c/cpr/1.14.2/9598c17037e047d5a6fc8903c12e0a48/include",
            "-isystem",
            "/home/abhinandps/.xmake/packages/l/libcurl/8.21.0/cbe3939eb8a84e359a111967cdb1018d/include",
            "-isystem",
            "/home/abhinandps/.xmake/packages/b/boost/1.90.0/488fd73e25524085beb3971ea8741c31/include",
            "-isystem",
            "/home/abhinandps/.xmake/packages/j/jsoncpp/1.9.8/dff818dedfa545bcbec0e8d8dc91c0e8/include",
            "-DNDEBUG"
        }
    }
}