/*
 * @Author: LEESON
 * @Date: 2023-09-29 22:44:24
 */
#include <memory>
#include <iostream>
#include <string>

// #include "absl/flags/flag.h"
// #include "absl/flags/parse.h"
// #include "absl/strings/str_format.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <glog/logging.h>

#include "proto/helloworld.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

class GreeterServiceImpl final : public Greeter::Service
{
  Status SayHello(ServerContext* context, const HelloRequest* request,
                  HelloReply* reply) override
  {
    LOG(INFO) << "SayHello ...";
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());
    return Status::OK;
  }

  Status SayHelloAgain(ServerContext* context, const HelloRequest* request,
                       HelloReply* reply) override
  {
    LOG(INFO) << "SayHelloAgain ...";
    std::string prefix("Hello again ");
    reply->set_message(prefix + request->name());
    
    return Status::OK;
  }
};

void InitGlog() 
{
  google::InitGoogleLogging("grpc_helloworld"); //日志名称
  FLAGS_log_dir = "./logs";                     //日志目录
  FLAGS_logbufsecs = 0;                         //日志缓冲秒数
  FLAGS_colorlogtostderr = true;                //彩色消息
  FLAGS_log_prefix = true;                      //日志前缀
}

void RunServer()
{
  std::string address = "0.0.0.0";
  std::string port = "5001";
  std::string server_address = address + ":" + port;
  GreeterServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  
  server->Wait();
  google::ShutdownGoogleLogging();
}

int main(int argc, char** argv)
{

  InitGlog();

  std::cout << "grpc-version: " << grpc::Version() << std::endl;

#ifdef BAZEL_TEST
  std::cout << "BAZEL_TEST..." << std::endl;
#endif

  RunServer();

  return 0;
}
