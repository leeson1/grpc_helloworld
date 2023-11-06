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
#include "proto/user.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;
using user::UserMessage;
using user::UserRequest;
using user::UserRespond;


std::map<int32_t,std::function<Status(const UserRequest* req, UserRespond* res)>> msg_list;
#define REGISTERMESSAGE(msg_id,fun) msg_list.insert({msg_id,fun})


class GreeterServiceImpl final : public Greeter::Service
{
  Status SayHello(ServerContext* context, const HelloRequest* request,
                  HelloReply* reply) override
  {
    LOG(INFO) << "SayHello ...";
    std::string prefix("Hello ");

    reply->set_hitokoto("123");
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

class UserServiceImpl final : public UserMessage::Service 
{
  Status UserLogin(ServerContext* context, const UserRequest* req, UserRespond* rsp)
  {
    LOG(INFO) << "UserLogin ...";
    if(req->msg_id() == user::MessageID::NONE) 
    {
      LOG(ERROR) << "msg_id[" << req->msg_id() << "] error.";
      return Status::CANCELLED; 
    }

    auto fun = msg_list.find(req->msg_id());
    auto status = fun->second(req,rsp);

    return Status::OK;
  }
};

int32_t InitGlog() 
{
  google::InitGoogleLogging("grpc_helloworld"); //日志名称
  FLAGS_log_dir = "./logs";                     //日志目录
  FLAGS_logbufsecs = 0;                         //日志缓冲秒数
  FLAGS_colorlogtostderr = true;                //彩色消息
  FLAGS_log_prefix = true;                      //日志前缀
  return 0;
}

int32_t RegisterMessage() {
  REGISTERMESSAGE(user::MessageID::REQ_LOGIN,[](const UserRequest* req, UserRespond* res){return Status::OK;});
  REGISTERMESSAGE(user::MessageID::REQ_REGISTER,[](const UserRequest* req, UserRespond* res){return Status::OK;});
  return 0;
}

int32_t Init() {
  InitGlog();
  RegisterMessage();
  return 0;
}

void RunServer()
{
  std::string address = "0.0.0.0";
  std::string port = "8081";
  std::string server_address = address + ":" + port;
  GreeterServiceImpl service;
  UserServiceImpl userService;

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
  Init();

  std::cout << "grpc-version: " << grpc::Version() << std::endl;
    std::cout << "Test ccache" << std::endl;
#ifdef BAZEL_TEST
  std::cout << "BAZEL_TEST..." << std::endl;
#endif

  RunServer();

  return 0;
}
