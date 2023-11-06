load("@rules_proto_grpc//cpp:defs.bzl", "cpp_proto_library","cpp_grpc_library")

proto_library(
    name = "hello_proto",
    srcs = [
        "helloworld.proto",
        "user.proto"
    ],
)

cpp_proto_library(
    name = "cpp_hello_proto_lib",
    protos = [":hello_proto"],
)

cpp_grpc_library(
    name = "hello_greeter_cpp_grpc",
    protos = [":hello_proto"],
    visibility = ["//visibility:public"],
)
