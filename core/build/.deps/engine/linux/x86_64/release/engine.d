{
    files = {
        "build/.objs/engine/linux/x86_64/release/src/docker_client.cpp.o",
        "build/.objs/engine/linux/x86_64/release/src/k8s_client.cpp.o",
        "build/.objs/engine/linux/x86_64/release/src/main.cpp.o",
        "build/.objs/engine/linux/x86_64/release/__/data/logs/enginelog_c++/commonlog.cpp.o"
    },
    values = {
        "/usr/bin/g++",
        {
            "-m64",
            "-s",
            "-lspdlog",
            "-lfmt",
            "-pthread"
        }
    }
}