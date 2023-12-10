/*
 * @Author: LEESON
 * @Date: 2023-09-29 22:44:24
 */
#include <iostream>
#include <memory>
#include <string>

// #include "absl/flags/flag.h"
// #include "absl/flags/parse.h"
// #include "absl/strings/str_format.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "fmt/core.h"
#include "proto/helloworld.grpc.pb.h"
#include "proto/user.grpc.pb.h"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/spdlog.h"

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

std::map<int32_t, std::function<Status(const UserRequest* req, UserRespond* res)>>
    msg_list;
#define REGISTERMESSAGE(msg_id, fun) msg_list.insert({msg_id, fun})

class GreeterServiceImpl final : public Greeter::Service
{
    Status SayHello(ServerContext* context, const HelloRequest* request,
                    HelloReply* reply) override
    {
        std::string prefix("Hello ");

        reply->set_hitokoto("123");
        reply->set_message(prefix + request->name());
        return Status::OK;
    }

    Status SayHelloAgain(ServerContext* context, const HelloRequest* request,
                         HelloReply* reply) override
    {
        std::string prefix("Hello again ");
        reply->set_message(prefix + request->name());

        return Status::OK;
    }
};

class UserServiceImpl final : public UserMessage::Service
{
    Status UserLogin(ServerContext* context, const UserRequest* req,
                     UserRespond* rsp)
    {
        if (req->msg_id() == user::MessageID::NONE)
        {
            return Status::CANCELLED;
        }

        auto fun = msg_list.find(req->msg_id());
        if(fun == msg_list.end())
        {
            return Status::CANCELLED;
        }
        auto status = fun->second(req, rsp);

        return Status::OK;
    }
};

int32_t RegisterMessage()
{
    REGISTERMESSAGE(user::MessageID::REQ_LOGIN, [](const UserRequest* req, UserRespond* res) { return Status::OK; });
    REGISTERMESSAGE(user::MessageID::REQ_REGISTER, [](const UserRequest* req, UserRespond* res) { return Status::OK; });
    return 0;
}

int32_t Init()
{
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
}

void stdout_example()
{
    // create a color multi-threaded logger
    auto console = spdlog::stdout_color_mt("console");
    auto err_logger = spdlog::stderr_color_mt("stderr");
    spdlog::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(logger_name)");
}

int main(int argc, char** argv)
{
    auto async_file = spdlog::basic_logger_mt<spdlog::async_factory>("async_file_logger", "logs/async_log.txt");
    //auto my_logger = spdlog::basic_logger_mt("file_logger","logs/my_log.txt");
    //spdlog::set_default_logger(my_logger);
    //my_logger->set_level(spdlog::level::debug);
    //my_logger->info("Welcome to spdlog! {} {}",123,456);
    //my_logger->flush_on(spdlog::level::debug);
    spdlog::set_default_logger(async_file);

    async_file->set_level(spdlog::level::debug);
    async_file->flush_on(spdlog::level::debug);
    async_file->info("Welcome to spdlog!", 123, 456);
    spdlog::debug("123123");
    SPDLOG_INFO("SPDLOG_INFO {}","123");
    SPDLOG_DEBUG("SPDLOG_DEBUG {}",123);

    //stdout_example();
    Init();
    RunServer();

    return 0;
}
