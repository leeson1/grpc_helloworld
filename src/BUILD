load("@com_grail_bazel_compdb//:defs.bzl", "compilation_database")
load("@com_grail_bazel_output_base_util//:defs.bzl", "OUTPUT_BASE")

compilation_database(
    name = "example_compdb",
    targets = [ 
        "//proto:hello_greeter_cpp_grpc",
        ":server",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/strings:str_format",
    ],  
    output_base = OUTPUT_BASE,
)

cc_binary(
    name = "server",
    srcs = ["server.cc"],
    defines = ["BAZEL_TEST"],
    deps = [ 
        "//proto:hello_greeter_cpp_grpc",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/strings:str_format",
    ]   
)

cc_binary(
    name = "client",
    srcs = ["client.cc"],
    defines = ["BAZEL_TEST"],
    deps = [ 
        "//proto:hello_greeter_cpp_grpc",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/strings:str_format",
    ]   
)
