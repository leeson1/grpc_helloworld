package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "server",
    srcs = ["server.cc"],
    defines = [
        "BAZEL_TEST",
        "FMT_HEADER_ONLY",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//proto:hello_greeter_cpp_grpc",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/strings:str_format",
        "@spdlog",
    ],
)
