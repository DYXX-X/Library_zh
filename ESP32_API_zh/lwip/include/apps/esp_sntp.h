// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef __ESP_SNTP_H__
#define __ESP_SNTP_H__

#include "lwip/err.h"
#include "lwip/apps/sntp.h"


#ifdef __cplusplus
extern "C" {
#endif

/*
 * 时间更新发生在sntp_sync_time（）函数中。用户可以重新定义此功能，以便重新定义其功能。此函数有两种时间更新模式，可通过sntp_set_sync_mode（）函数设置。有两种模式可用：
 * -第一个是从sntp服务器接收时间时的立即更新，
 * -第二种是平滑的时间更新（如果时间误差不超过35分钟，如果误差超过35分钟则立即更新）。
 *
 * 要接收时间同步通知，可以使用回调函数或通过sntp_get_sync_status（）函数获取同步状态。
 *
 * 要确定设备上的时间同步时间，可以使用：1）sntp_set_time_sync_notification_cb（）函数设置回调函数，该函数便于接收更新时间的通知。2） sntp_get_sync_status（）函数，用于获取时间同步状态。时间同步完成后，状态将为SNTP_SYNC_status_completed，之后将重新设定为SNTP_StYNC_status _RESET，以等待下一个同步周期。
 */

///SNTP时间更新模式
typedef enum {
    SNTP_SYNC_MODE_IMMED,   /*!< 收到SNTP服务器的响应时立即更新系统时间。*/
    SNTP_SYNC_MODE_SMOOTH,  /*!< 平滑时间更新。使用adjtime函数逐渐减少时间误差。如果SNTP响应时间与系统时间之间的差异较大（超过35分钟），则立即更新。*/
} sntp_sync_mode_t;

///SNTP同步状态
typedef enum {
    SNTP_SYNC_STATUS_RESET,         // 重置状态。
    SNTP_SYNC_STATUS_COMPLETED,     // 时间已同步。
    SNTP_SYNC_STATUS_IN_PROGRESS,   // 正在进行平滑时间同步。
} sntp_sync_status_t;

/**
 * @brief 用于通知时间同步事件的SNTP回调函数
 *
 * @param tv 从SNTP服务器接收的时间。
 */
typedef void (*sntp_sync_time_cb_t) (struct timeval *tv);

/**
 * @brief 此功能更新系统时间。
 *
 * 这是一个弱关联函数。通过在应用固件源中放置SNTP_sync_time（）函数，可以替换所有SNTP更新功能。如果使用默认实现，则调用sntp_set_sync_mode（）允许将时间同步模式更改为即时或平滑。如果通过sntp_set_time_sync_notification_cb（）注册了回调函数，则将在时间同步后调用该函数。
 *
 * @param tv 从SNTP服务器接收的时间。
 */
void sntp_sync_time(struct timeval *tv);

/**
 * @brief 设置同步模式
 *
 * 允许两种模式：SNTP_SYNC_mode_IMMED和SNTP_SSYNC_mode_MOOTH。
 * @param sync_mode 同步模式。
 */
void sntp_set_sync_mode(sntp_sync_mode_t sync_mode);

/**
 * @brief 获取设置同步模式
 *
 * @return  SNTP_SYNC_MODE_IMMED：立即更新时间。SNTP_SYNC_MODE_MOOTH：平滑时间更新。
 */
sntp_sync_mode_t sntp_get_sync_mode(void);

/**
 * @brief 获取时间同步状态
 *
 * 更新完成后，状态将返回为SNTP_SYNC_status_completed。之后，状态将重置为SNTP_SYNC_status_reset。如果更新操作尚未完成，状态将为SNTP_SYNC_status_RESET。如果选择了平滑模式，并且同步仍在继续（调整时间有效），那么它将是SNTP_SYNC_STATUS_IN_PROGRESS。
 *
 * @return  SNTP_SYNC_STATUS_RESET：重置状态。SNTP_SYNC_STATUS_COMPLETED：时间已同步。SNTP_SYNC_STATUS_IN_PROGRESS：正在进行平滑时间同步。
 */
sntp_sync_status_t sntp_get_sync_status(void);

/**
 * @brief 设置时间同步状态
 *
 * @param sync_status 时间同步状态（请参见sntp_sync_status_t）
 */
void sntp_set_sync_status(sntp_sync_status_t sync_status);

/**
 * @brief 设置时间同步通知的回调函数
 *
 * @param callback 回调函数
 */
void sntp_set_time_sync_notification_cb(sntp_sync_time_cb_t callback);

/**
 * @brief 设置SNTP操作的同步间隔
 *
 * 注意：SNTPv4 RFC 4330强制执行15秒的最小同步间隔。此同步间隔将用于通过SNTP的下一次尝试更新时间。要应用新的同步间隔，请调用sntp_restart（）函数，否则，它将在最后一个间隔过期后应用。
 *
 * @param interval_ms   以毫秒为单位的同步间隔不能低于15秒，否则将设置15秒。
 */
void sntp_set_sync_interval(uint32_t interval_ms);

/**
 * @brief 获取SNTP操作的同步间隔
 *
 * @return  同步间隔
 */
uint32_t sntp_get_sync_interval(void);

/**
 * @brief 重新启动SNTP
 *
 * @return True-重新启动False-SNTP尚未初始化
 */
bool sntp_restart(void);

#ifdef __cplusplus
}
#endif

#endif // __ESP_SNTP_H__

