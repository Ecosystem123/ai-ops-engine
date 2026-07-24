{
    files = {
        "src/docker_client.cpp"
    },
    depfiles = "docker_client.o: src/docker_client.cpp\
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