/* 版权所有2018 Espressif Systems（上海）私人有限公司
 *
 * 根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef _ESP_MB_MASTER_INTERFACE_H
#define _ESP_MB_MASTER_INTERFACE_H

#include <stdint.h>                 // 用于标准int类型定义
#include <stddef.h>                 // 对于NULL和std定义
#include "soc/soc.h"                // 用于BITN定义
#include "esp_modbus_common.h"      // 对于常见类型

#ifdef __cplusplus
extern "C" {
#endif

#define MB_MASTER_CHECK(a, err_code, format, ...) MB_RETURN_ON_FALSE(a, err_code, TAG, format __VA_OPT__(,) __VA_ARGS__)

#define MB_MASTER_ASSERT(con) do { \
        if (!(con)) { ESP_LOGE(TAG, "assert errno:%d, errno_str: !(%s)", errno, strerror(errno)); assert(0 && #con); } \
    } while (0)

/*!
 * \简要Modbus描述符表参数类型定义。
 */
typedef enum {
    PARAM_TYPE_U8 = 0x00,                   /*!< 未签名8*/
    PARAM_TYPE_U16 = 0x01,                  /*!< 未签名16*/
    PARAM_TYPE_U32 = 0x02,                  /*!< 无符号32*/
    PARAM_TYPE_FLOAT = 0x03,                /*!< 浮子类型*/
    PARAM_TYPE_ASCII = 0x04                 /*!< ASCII类型*/
} mb_descr_type_t;

/*!
 * \以字节为单位的简短Modbus描述符表参数大小。
 */
typedef enum {
    PARAM_SIZE_U8 = 0x01,                   /*!< 未签名8*/
    PARAM_SIZE_U16 = 0x02,                  /*!< 未签名16*/
    PARAM_SIZE_U32 = 0x04,                  /*!< 无符号32*/
    PARAM_SIZE_FLOAT = 0x04,                /*!< 浮点数大小*/
    PARAM_SIZE_ASCII = 0x08,                /*!< ASCII大小*/
    PARAM_SIZE_ASCII24 = 0x18,              /*!< ASCII24尺寸*/
    PARAM_MAX_SIZE
} mb_descr_size_t;

/*!
 * \描述表的Modbus参数选项
 */
typedef union {
    struct {
        int opt1;                         /*!< 参数选项1*/
        int opt2;                         /*!< 参数选项2*/
        int opt3;                         /*!< 参数选项3*/
    };
    struct {
        int min;                          /*!< 参数最小值*/
        int max;                          /*!< 参数最大值*/
        int step;                         /*!< 参数变更跟踪步骤*/
    };
} mb_parameter_opt_t;

/**
 * @brief 特征的权限
 */
typedef enum {
    PAR_PERMS_READ               = 1 << BIT0,                                   /**<设备特征可读*/
    PAR_PERMS_WRITE              = 1 << BIT1,                                   /**<设备的特性是可写的*/
    PAR_PERMS_TRIGGER            = 1 << BIT2,                                   /**<设备的特性是可触发的*/
    PAR_PERMS_READ_WRITE         = PAR_PERMS_READ | PAR_PERMS_WRITE,            /**<设备的特性可读写*/
    PAR_PERMS_READ_TRIGGER       = PAR_PERMS_READ | PAR_PERMS_TRIGGER,          /**<设备的特性是可读和可触发的*/
    PAR_PERMS_WRITE_TRIGGER      = PAR_PERMS_WRITE | PAR_PERMS_TRIGGER,         /**<设备的特性是可写和可触发的*/
    PAR_PERMS_READ_WRITE_TRIGGER = PAR_PERMS_READ_WRITE | PAR_PERMS_TRIGGER,    /**<设备的特点是可读写和可触发*/
} mb_param_perms_t;

/**
 * @brief 特性描述符类型用于描述特性，并将其与反映其数据的Modbus参数联系起来。
 */
typedef struct {
    uint16_t            cid;                /*!< 特征cid*/
    const char*         param_key;          /*!< 参数的键（名称）*/
    const char*         param_units;        /*!< 参数的物理单位*/
    uint8_t             mb_slave_addr;      /*!< Modbus段中设备的从属地址*/
    mb_param_type_t     mb_param_type;      /*!< modbus参数类型*/
    uint16_t            mb_reg_start;       /*!< 这是Modbus寄存器地址。这是基于0的值。*/
    uint16_t            mb_size;            /*!< 寄存器中mb参数的大小*/
    uint16_t            param_offset;       /*!< 参数名称（参数结构中的OFFSET）*/
    mb_descr_type_t     param_type;         /*!< 浮点、U8、U16、U32、ASCII等。*/
    mb_descr_size_t     param_size;         /*!< 参数中的字节数。*/
    mb_parameter_opt_t  param_opts;         /*!< 用于检查限值等的参数选项。*/
    mb_param_perms_t    access;             /*!< 基于模式的访问权限*/
} mb_parameter_descriptor_t;

/**
 * @brief Modbus寄存器请求类型结构
 */
typedef struct {
    uint8_t slave_addr;             /*!< Modbus从站地址*/
    uint8_t command;                /*!< 要发送的Modbus命令*/
    uint16_t reg_start;             /*!< Modbus启动寄存器*/
    uint16_t reg_size;              /*!< Modbus寄存器数量*/
} mb_param_request_t;

/**
 * @brief 初始化Modbus控制器和TCP端口堆栈
 *
 * @param[out] handler 主数据结构的处理程序（指针）
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_NO_MEM参数错误
 *     -不支持ESP_ERR_NOT_SUPPORTED端口类型
 *     -ESP_ERR_INVALID_STATE初始化失败
 */
esp_err_t mbc_master_init_tcp(void** handler);

/**
 * @brief 初始化Modbus主控制器和串行端口堆栈
 *
 * @param[out] handler 主数据结构的处理程序（指针）
 * @param[in] port_type 堆栈类型
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_NO_MEM参数错误
 *     -不支持ESP_ERR_NOT_SUPPORTED端口类型
 *     -ESP_ERR_INVALID_STATE初始化失败
 */
esp_err_t mbc_master_init(mb_port_type_t port_type, void** handler);

/**
 * @brief 初始化Modbus主控制器接口句柄
 *
 * @param[in] handler -指向主数据结构的指针
 */
void mbc_master_init_iface(void* handler);

/**
 * @brief 销毁Modbus控制器和堆栈
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE参数错误
 */
esp_err_t mbc_master_destroy(void);

/**
 * @brief 启动Modbus通信堆栈
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG Modbus堆栈启动错误
 */
esp_err_t mbc_master_start(void);

/**
 * @brief 设置控制器的Modbus通信参数
 *
 * @param comm_info 通信参数结构。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数数据不正确
 */
esp_err_t mbc_master_setup(void* comm_info);

/***************************** 特定接口功能************************************************************以下接口功能提供了读取/写入Modbus段中从设备的基本方法，以及读取与Modbus网络中设备的Modbus参数相关的特定支持特性的API。
*******************************************************************************************************/

/**
 * @brief 为Modbus控制器接口分配参数描述表。
 *
 * @param[in] descriptor 指向参数描述表的指针
 * @param num_elements 表中的元素数
 *
 * @return
 *     -esp_err_t esp_OK-成功设置描述符
 *     -esp_err_t esp_err_INVALID_ARG-函数调用中的参数无效
 */
esp_err_t mbc_master_set_descriptor(const mb_parameter_descriptor_t* descriptor, const uint16_t num_elements);

/**
 * @brief 发送参数请求中定义的数据请求，等待从机的响应并返回命令执行状态。该功能为网络中Modbus设备的读/写访问提供了标准方式。
 *
 * @param[in] request 指向mb_param_request_t类型请求结构的指针
 * @param[in] data_ptr 指向发送或接收数据的数据缓冲区的指针（取决于请求中的命令字段）
 *
 * @return
 *     -esp_err_t esp_OK-请求成功
 *     -esp_err_t esp_err_INVALID_ARG-函数的参数无效
 *     -esp_err_t esp_err_INVALID_RESPONSE-从机的无效响应
 *     -esp_err_t esp_err_TIMEOUT—操作超时或从机无响应
 *     -esp_err_t esp_err_NOT_SUPPORTED-从属设备不支持请求命令
 *     -esp_err_t esp_FAIL-slave返回异常或其他故障
 */
esp_err_t mbc_master_send_request(mb_param_request_t* request, void* data_ptr);

/**
 * @brief 获取有关定义为cid的受支持特性的信息。使用参数描述表获取此信息。该函数将检查定义为cid参数的特性是否受支持，并在param_info中返回其描述。如果不支持特征，则返回ESP_ERR_NOT_FOUND。
 *
 * @param[in] cid 特征id
 * @param param_info 指向特征数据指针的指针。
 *
 * @return
 *     -esp_err_t esp_OK-请求成功，缓冲区包含支持的特征名称
 *     -esp_err_t esp_err_INVALID_ARG-函数的参数无效
 *     -esp_err_t esp_err_NOT_FOUND-未找到特征（cid）
 *     -esp_err_t esp_FAIL-查找表处理过程中出现未知错误
*/
esp_err_t mbc_master_get_cid_info(uint16_t cid, const mb_parameter_descriptor_t** param_info);

/**
 * @brief 从modbus从属设备读取参数，该设备的名称由名称定义，并具有cid。请求的附加数据取自参数描述（查找）表。
 *
 * @param[in] cid 参数的特征id
 * @param[in] name 指向参数字符串名称（键）的指针（以null结尾）
 * @param[out] value 指向参数数据缓冲区的指针
 * @param[out] type 与从参数描述表返回的名称关联的参数类型。
 *
 * @return
 *     -esp_err_t esp_OK-请求成功，值缓冲区包含从属设备的实际参数数据表示
 *     -esp_err_t esp_err_INVALID_ARG-函数或参数描述符的参数无效
 *     -esp_err_t esp_err_INVALID_RESPONSE-从机的无效响应
 *     -esp_err_t esp_err_INVALID_STATE—数据处理或分配失败期间的无效状态
 *     -esp_err_t esp_err_TIMEOUT-操作超时，从属设备无响应
 *     -esp_err_t esp_err_NOT_SUPPORTED-从属设备不支持请求命令
 *     -esp_err_t esp_err_NOT_FOUND-参数描述表中找不到该参数
 *     -esp_err_t esp_FAIL-slave返回异常或其他故障
*/
esp_err_t mbc_master_get_parameter(uint16_t cid, char* name, uint8_t* value, uint8_t *type);

/**
 * @brief 设置定义为名称和cid参数的特性值。cid参数请求的附加数据取自主参数查找表。
 *
 * @param[in] cid 参数的特征id
 * @param[in] name 指向参数字符串名称（键）的指针（以null结尾）
 * @param[out] value 指向参数数据缓冲区的指针（二进制形式的json值字段的实际表示）
 * @param[out] type 指向与从参数查找表返回的名称相关联的参数类型的指针。
 *
 * @return
 *     -esp_err_t esp_OK-请求成功，值保存在从属设备寄存器中
 *     -esp_err_t esp_err_INVALID_ARG-函数或参数描述符的参数无效
 *     -esp_err_t esp_err_INVALID_RESPONSE-在处理参数期间从机的无效响应
 *     -esp_err_t esp_err_INVALID_STATE—数据处理或分配失败期间的无效状态
 *     -esp_err_t esp_err_TIMEOUT-操作超时，从属设备无响应
 *     -esp_err_t esp_err_NOT_SUPPORTED-从属设备不支持请求命令
 *     -esp_err_t esp_FAIL-slave返回异常或其他故障
*/
esp_err_t mbc_master_set_parameter(uint16_t cid, char* name, uint8_t* value, uint8_t *type);

#ifdef __cplusplus
}
#endif

#endif // _ESP_MB_MASTER_INTERFACE_H

