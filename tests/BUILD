load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_test(
    name = "demo-test",
    srcs = glob(["**/*.cc"]),
    copts = ["-Iexternal/gtest/googletest-release-1.7.0/include"],
    deps = ["//src:demo-lib",
           "@gtest//:main"],
)