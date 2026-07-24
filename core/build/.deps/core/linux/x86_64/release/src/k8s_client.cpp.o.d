{
    files = {
        "src/k8s_client.cpp"
    },
    depfiles = "k8s_client.o: src/k8s_client.cpp\
",
    depfiles_format = "gcc",
    values = {
        "/usr/bin/g++",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-DNDEBUG"
        }
    }
}