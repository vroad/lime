#ifndef LIME_UTILS_LOGGER_H
#define LIME_UTILS_LOGGER_H

#ifdef ANDROID
#include <android/log.h>
#define LOG_ERROR(args,...) __android_log_print(ANDROID_LOG_ERROR, "Lime", args, ##__VA_ARGS__)
#else
#ifdef IPHONE
//#define LOG_ERROR(args,...) printf(args, ##__VA_ARGS__)
#define LOG_ERROR(args...) { }
#elif defined(TIZEN)
#include <FBase.h>
#define LOG_ERROR(args,...) AppLog(args, ##__VA_ARGS__)
#else
#define LOG_ERROR(args,...) printf(args, ##__VA_ARGS__)
#endif
#endif

#endif