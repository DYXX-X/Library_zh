// 版权所有2019 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**主要版本号（X.X.X）*/
#define ESP_IDF_VERSION_MAJOR   4
/**次要版本号（x.x.x）*/
#define ESP_IDF_VERSION_MINOR   4
/**补丁版本号（x.x.x）*/
#define ESP_IDF_VERSION_PATCH   1

/**
 * 将IDF版本号转换为整数的宏
 *
 * 用于比较，例如ESP_IDF_VERSION>=ESP_IDF-VERSION_VAL（4，0，0）
 */
#define ESP_IDF_VERSION_VAL(major, minor, patch) ((major << 16) | (minor << 8) | (patch))

/**
 * 当前IDF版本，整数
 *
 * 用于比较，例如ESP_IDF_VERSION>=ESP_IDF-VERSION_VAL（4，0，0）
 */
#define ESP_IDF_VERSION  ESP_IDF_VERSION_VAL(ESP_IDF_VERSION_MAJOR, \
                                             ESP_IDF_VERSION_MINOR, \
                                             ESP_IDF_VERSION_PATCH)

#ifndef __ASSEMBLER__

/**
 * 返回完整的IDF版本字符串，与“git-descripte”输出相同。
 *
 * @note 如果要在日志文件或其他信息中打印ESP-IDF版本，则此函数提供的信息比使用数字版本宏提供的信息更多。例如，数字版本宏不会区分开发版本、预发布版本和发布版本，但该函数的输出会区分。
 *
 * @return IDF_VER中的常量字符串
 */
const char* esp_get_idf_version(void);

#endif

#ifdef __cplusplus
}
#endif

