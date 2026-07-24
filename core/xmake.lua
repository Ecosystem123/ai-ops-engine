add_rules("mode.debug", "mode.release")

add_requires("spdlog")

target("engine")
    set_kind("binary")
    set_languages("c++23")
    add_files("src/*.cpp")
    set_rundir("..")
    add_files("../data/logs/enginelog_c++/commonlog.cpp")
    add_packages("spdlog")
