load("@rules_cc//cc:defs.bzl", "cc_binary")
cc_binary(
    name = "test_payload",
    srcs = ["test_payload.cpp"],
    deps = [
      "//ironman/serialize:serialize",
      "@com_google_googletest//:gtest_main",
    ],
    linkopts = ["-pthread",],
    copts = ["-Ithirdparty/staging/include/"],
)
