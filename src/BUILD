proto_library(
    name = "thing_proto",
    srcs = ["thing.proto"],
    deps = ["@com_google_protobuf//:any_proto"],
)

load("@rules_proto_grpc//cpp:defs.bzl", "cpp_proto_library")
cpp_proto_library(
    name = "cpp_thing_proto_lib",
    protos = [":thing_proto"],
)

load("@rules_proto_grpc//cpp:defs.bzl", "cpp_grpc_library")

cpp_grpc_library(
    name = "greeter_cpp_grpc",
    protos = [":thing_proto"],
)

cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [ 
        ":cpp_thing_proto_lib",
        ":greeter_cpp_grpc",
        "//proto:hello_greeter_cpp_grpc",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/strings:str_format",
    ]   
)

load("@com_grail_bazel_compdb//:defs.bzl", "compilation_database")
load("@com_grail_bazel_output_base_util//:defs.bzl", "OUTPUT_BASE")

compilation_database(
    name = "example_compdb",
    targets = [ 
        ":cpp_thing_proto_lib",
        ":greeter_cpp_grpc",
        "//proto:hello_greeter_cpp_grpc",
        ":main",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/strings:str_format",
    ],  
    output_base = OUTPUT_BASE,
)

