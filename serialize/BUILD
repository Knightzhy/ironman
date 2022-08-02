package(
    default_visibility = ["//visibility:public"],
)
load("@rules_cc//cc:defs.bzl", "cc_library")
cc_library(
  name = "head",
  srcs = ["package.h", "payload.h", "header.h"],
)

cc_library(
  name = "io",
  srcs = ["safe_io.cpp"],
  hdrs = ["safe_io.h"],
)

cc_library(
  name = "message",
  srcs = ["message.cpp"],
  hdrs = ["message.h"],
  deps = [
    ":head"
  ],
)
cc_library(
  name = "string_payload",
  srcs = ["string_payload.cpp"],
  hdrs = ["string_payload.h"],
  deps = [
    ":head"
  ],
)

cc_library(
  name = "sample_header",
  srcs = ["sample_header.cpp"],
  hdrs = ["sample_header.h"],
  deps = [
    ":head"
  ],
)

cc_library(
  name = "rpc_factory",
  srcs = ["rpc_factory.cpp"],
  hdrs = ["rpc_factory.h"],
  deps = [
    ":message"
  ],
)

cc_library(
  name = "rpc",
  srcs = ["rpc.cpp"],
  hdrs = ["rpc.h"],
  deps = [
    ":rpc_factory",
    ":io",
    ":message"
  ],
)

cc_library(
  name = "message_factory",
  srcs = ["message_factory.cpp"],
  hdrs = ["message_factory.h"],
  deps = [
    ":head",
    ":rpc_factory",
  ],
)

cc_library(
    name = "serialize",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
)
