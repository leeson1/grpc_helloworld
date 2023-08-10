proto_library(
    name = "hello_proto",
    srcs = ["helloworld.proto"],
)

load("@rules_proto_grpc//cpp:defs.bzl", "cpp_proto_library")
cpp_proto_library(
    name = "cpp_hello_proto_lib",
    protos = [":hello_proto"],
)

load("@rules_proto_grpc//cpp:defs.bzl", "cpp_grpc_library")

cpp_grpc_library(
    name = "hello_greeter_cpp_grpc",
    protos = [":hello_proto"],
    visibility = ["//visibility:public"]
)