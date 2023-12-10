load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_google_protobuf",
    sha256 = "0cbdc9adda01f6d2facc65a22a2be5cecefbefe5a09e5382ee8879b522c04441",
    strip_prefix = "protobuf-3.15.8",
    urls = ["https://github.com/protocolbuffers/protobuf/archive/v3.15.8.tar.gz"],
)

# rules_proto_grpc

local_repository(
    name = "rules_proto_grpc",
    path = "./third_party/rules_proto_grpc/",
)

load("@rules_proto_grpc//:repositories.bzl", "rules_proto_grpc_repos", "rules_proto_grpc_toolchains")

rules_proto_grpc_toolchains()

rules_proto_grpc_repos()

load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")

rules_proto_dependencies()

rules_proto_toolchains()

load("@rules_proto_grpc//cpp:repositories.bzl", rules_proto_grpc_cpp_repos = "cpp_repos")

rules_proto_grpc_cpp_repos()

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")

grpc_extra_deps()

###################

## Generate compile_commands.json

local_repository(
    name = "com_grail_bazel_compdb",
    path = "./third_party/bazel-compilation-database/",
)

load("@com_grail_bazel_compdb//:deps.bzl", "bazel_compdb_deps")

bazel_compdb_deps()

################

## glog

http_archive(
    name = "com_github_gflags_gflags",
    sha256 = "34af2f15cf7367513b352bdcd2493ab14ce43692d2dcd9dfc499492966c64dcf",
    strip_prefix = "gflags-2.2.2",
    urls = ["https://github.com/gflags/gflags/archive/v2.2.2.tar.gz"],
)

http_archive(
    name = "com_github_google_glog",
    sha256 = "122fb6b712808ef43fbf80f75c52a21c9760683dae470154f02bddfc61135022",
    strip_prefix = "glog-0.6.0",
    urls = ["https://github.com/google/glog/archive/v0.6.0.zip"],
)

################

## fmt

http_archive(
    name = "fmt",
    build_file = "//bazel:fmtlib.BUILD",
    # sha256 = "5dea48d1fcddc3ec571ce2058e13910a0d4a6bab4cc09a809d8b1dd1c88ae6f2",
    strip_prefix = "fmt-9.1.0",
    urls = ["https://github.com/fmtlib/fmt/archive/9.1.0.tar.gz"],
)

################

## spdlog

http_archive(
    name = "spdlog",
    build_file = "//bazel:spdlog.BUILD",
    sha256 = "ca5cae8d6cac15dae0ec63b21d6ad3530070650f68076f3a4a862ca293a858bb",
    strip_prefix = "spdlog-1.11.0",
    urls = ["https://github.com/gabime/spdlog/archive/refs/tags/v1.11.0.tar.gz"],
)

################
