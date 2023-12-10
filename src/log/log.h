/*
 * @Author: LEESON
 * @Date: 2023-11-29 17:59:19
 */
#include <glog/logging.h>

//INFO, WARNING, ERROR, FATAL
#define LOG_INFO(...) \
    LOG(INFO) << __VA_ARGS__;

#define LOG_WARNING(...) \
    LOG(WARNING) << __VA_ARGS__;

#define LOG_ERROR(...) \
    LOG(ERROR) << __VA_ARGS__;

#define LOG_FATAL(...) \
    LOG(FATAL) << __VA_ARGS__;

