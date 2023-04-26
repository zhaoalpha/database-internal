load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "demo-lib",
    srcs = ["demo/demo.cc",
            "utils/packed_map.cc"],
    hdrs = ["include/demo/demo.h",
            "utils/packed_map.h"],
    copts = ["-std=c++17"],
    visibility = ["//tests:__pkg__"],
)
