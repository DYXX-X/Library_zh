/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_UUID_
#define H_BLE_UUID_

/**
 * @brief 蓝牙UUID
 * @defgroup bt_uuid蓝牙uuid
 * @ingroup bt_主机@{
 */

#include <inttypes.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct os_mbuf;

/**UUID类型*/
enum {
    /**16位UUID（已分配BT SIG）*/
    BLE_UUID_TYPE_16 = 16,

    /**32位UUID（已分配BT SIG）*/
    BLE_UUID_TYPE_32 = 32,

    /**128位UUID*/
    BLE_UUID_TYPE_128 = 128,
};

/**通用UUID类型，仅用作指针*/
typedef struct {
    /**UUID的类型*/
    uint8_t type;
} ble_uuid_t;

/**16位UUID*/
typedef struct {
    ble_uuid_t u;
    uint16_t value;
} ble_uuid16_t;

/**32位UUID*/
typedef struct {
    ble_uuid_t u;
    uint32_t value;
} ble_uuid32_t;

/**128位UUID*/
typedef struct {
    ble_uuid_t u;
    uint8_t value[16];
} ble_uuid128_t;

/**通用UUID类型，用于任何UUID静态分配*/
typedef union {
    ble_uuid_t u;
    ble_uuid16_t u16;
    ble_uuid32_t u32;
    ble_uuid128_t u128;
} ble_uuid_any_t;

#define BLE_UUID16_INIT(uuid16)         \
    {                                   \
        .u.type = BLE_UUID_TYPE_16,     \
        .value = (uuid16),              \
    }

#define BLE_UUID32_INIT(uuid32)         \
    {                                   \
        .u.type = BLE_UUID_TYPE_32,     \
        .value = (uuid32),              \
    }

#define BLE_UUID128_INIT(uuid128...)    \
    {                                   \
        .u.type = BLE_UUID_TYPE_128,    \
        .value = { uuid128 },           \
    }

#define BLE_UUID16_DECLARE(uuid16) \
    ((ble_uuid_t *) (&(ble_uuid16_t) BLE_UUID16_INIT(uuid16)))

#define BLE_UUID32_DECLARE(uuid32) \
    ((ble_uuid_t *) (&(ble_uuid32_t) BLE_UUID32_INIT(uuid32)))

#define BLE_UUID128_DECLARE(uuid128...) \
    ((ble_uuid_t *) (&(ble_uuid128_t) BLE_UUID128_INIT(uuid128)))

#define BLE_UUID16(u) \
    ((ble_uuid16_t *) (u))

#define BLE_UUID32(u) \
    ((ble_uuid32_t *) (u))

#define BLE_UUID128(u) \
    ((ble_uuid128_t *) (u))

/** 将UUID存储为字符串所需的缓冲区大小。包括尾随\0。
 */
#define BLE_UUID_STR_LEN (37)

/** @brief 从字节数组构造UUID对象。
 *
 * @param uuid  成功后，将使用构建的UUID填充此内容。
 * @param buf   要分析的源缓冲区。
 * @param len   缓冲区的大小，以字节为单位。
 *
 * @return      成功时为0，如果源缓冲区不包含有效的UUID，则为BLE_HS_EINVAL。
 */
int ble_uuid_init_from_buf(ble_uuid_any_t *uuid, const void *buf, size_t len);

/** @brief 比较两个蓝牙UUID。
 *
 * @param uuid1  要比较的第一个UUID。
 * @param uuid2  要比较的第二个UUID。
 *
 * @return       如果两个UUID相等，则为0；如果UUID不同，则为非零。
 */
int ble_uuid_cmp(const ble_uuid_t *uuid1, const ble_uuid_t *uuid2);

/** @brief 复制蓝牙UUID
 *
 * @param dst    目标UUID。
 * @param src    源UUID。
 */
void ble_uuid_copy(ble_uuid_any_t *dst, const ble_uuid_t *src);

/** @brief 将指定的UUID转换为其字符串表示形式。
 *
 * 字符串表示示例：o 16位：0x1234 o 32位：0x12345678 o 128位：12345678-1234-1234-1234-123456789abc
 *
 * @param uuid   要转换的源UUID。
 * @param dst    目标缓冲区。
 *
 * @return       指向提供的目标缓冲区的指针。
 */
char *ble_uuid_to_str(const ble_uuid_t *uuid, char *dst);

/** @brief 将指定的16位UUID转换为uint16_t。
 *
 * @param uuid   要转换的源UUID。
 *
 * @return       成功时转换的整数，如果指定的UUID不是16位，则为NULL。
 */
uint16_t ble_uuid_u16(const ble_uuid_t *uuid);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _BLE_HOST_UUID_H */

