load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "demo-lib",
    srcs = ["demo/demo.cc"],
    hdrs = ["include/demo/demo.h",
            "utils/packed_map.h"],
    visibility = ["//tests:__pkg__"],
)
