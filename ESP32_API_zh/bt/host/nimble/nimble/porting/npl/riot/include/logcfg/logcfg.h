/**
 * 此文件由Apache newt版本1.8.0-dev生成
 */

#ifndef H_MYNEWT_LOGCFG_
#define H_MYNEWT_LOGCFG_

#include "modlog/modlog.h"
#include "log_common/log_common.h"

#define BLE_HS_LOG_DEBUG(...) IGNORE(__VA_ARGS__)
#define BLE_HS_LOG_INFO(...) MODLOG_INFO(4, __VA_ARGS__)
#define BLE_HS_LOG_WARN(...) MODLOG_WARN(4, __VA_ARGS__)
#define BLE_HS_LOG_ERROR(...) MODLOG_ERROR(4, __VA_ARGS__)
#define BLE_HS_LOG_CRITICAL(...) MODLOG_CRITICAL(4, __VA_ARGS__)
#define BLE_HS_LOG_DISABLED(...) MODLOG_DISABLED(4, __VA_ARGS__)

#define DFLT_LOG_DEBUG(...) IGNORE(__VA_ARGS__)
#define DFLT_LOG_INFO(...) MODLOG_INFO(0, __VA_ARGS__)
#define DFLT_LOG_WARN(...) MODLOG_WARN(0, __VA_ARGS__)
#define DFLT_LOG_ERROR(...) MODLOG_ERROR(0, __VA_ARGS__)
#define DFLT_LOG_CRITICAL(...) MODLOG_CRITICAL(0, __VA_ARGS__)
#define DFLT_LOG_DISABLED(...) MODLOG_DISABLED(0, __VA_ARGS__)

#define MFG_LOG_DEBUG(...) IGNORE(__VA_ARGS__)
#define MFG_LOG_INFO(...) IGNORE(__VA_ARGS__)
#define MFG_LOG_WARN(...) IGNORE(__VA_ARGS__)
#define MFG_LOG_ERROR(...) IGNORE(__VA_ARGS__)
#define MFG_LOG_CRITICAL(...) IGNORE(__VA_ARGS__)
#define MFG_LOG_DISABLED(...) MODLOG_DISABLED(128, __VA_ARGS__)

#endif

