load("@rules_cc//cc:defs.bzl", "cc_binary")
cc_binary(
    name = "test_payload",
    srcs = ["test_payload.cpp"],
    deps = ["//ironman/serialize:serialize"],
    linkopts = ["-pthread", "-gtest", "-gtest_main"],
    copts = ["-Ithirdparty/staging/include/"],
)
