/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_GATT_
#define H_BLE_GATT_

/**
 * @brief 蓝牙通用属性配置文件（GATT）
 * @defgroup bt_gatt蓝牙通用属性配置文件（gatt）
 * @ingroup bt_主机@{
 */

#include <inttypes.h>
#include "host/ble_att.h"
#include "host/ble_uuid.h"
#ifdef __cplusplus
extern "C" {
#endif

struct ble_hs_conn;
struct ble_att_error_rsp;
struct ble_hs_cfg;

#define BLE_GATT_REGISTER_OP_SVC                        1
#define BLE_GATT_REGISTER_OP_CHR                        2
#define BLE_GATT_REGISTER_OP_DSC                        3

#define BLE_GATT_SVC_UUID16                             0x1801
#define BLE_GATT_DSC_CLT_CFG_UUID16                     0x2902

#define BLE_GATT_CHR_PROP_BROADCAST                     0x01
#define BLE_GATT_CHR_PROP_READ                          0x02
#define BLE_GATT_CHR_PROP_WRITE_NO_RSP                  0x04
#define BLE_GATT_CHR_PROP_WRITE                         0x08
#define BLE_GATT_CHR_PROP_NOTIFY                        0x10
#define BLE_GATT_CHR_PROP_INDICATE                      0x20
#define BLE_GATT_CHR_PROP_AUTH_SIGN_WRITE               0x40
#define BLE_GATT_CHR_PROP_EXTENDED                      0x80

#define BLE_GATT_ACCESS_OP_READ_CHR                     0
#define BLE_GATT_ACCESS_OP_WRITE_CHR                    1
#define BLE_GATT_ACCESS_OP_READ_DSC                     2
#define BLE_GATT_ACCESS_OP_WRITE_DSC                    3

#define BLE_GATT_CHR_F_BROADCAST                        0x0001
#define BLE_GATT_CHR_F_READ                             0x0002
#define BLE_GATT_CHR_F_WRITE_NO_RSP                     0x0004
#define BLE_GATT_CHR_F_WRITE                            0x0008
#define BLE_GATT_CHR_F_NOTIFY                           0x0010
#define BLE_GATT_CHR_F_INDICATE                         0x0020
#define BLE_GATT_CHR_F_AUTH_SIGN_WRITE                  0x0040
#define BLE_GATT_CHR_F_RELIABLE_WRITE                   0x0080
#define BLE_GATT_CHR_F_AUX_WRITE                        0x0100
#define BLE_GATT_CHR_F_READ_ENC                         0x0200
#define BLE_GATT_CHR_F_READ_AUTHEN                      0x0400
#define BLE_GATT_CHR_F_READ_AUTHOR                      0x0800
#define BLE_GATT_CHR_F_WRITE_ENC                        0x1000
#define BLE_GATT_CHR_F_WRITE_AUTHEN                     0x2000
#define BLE_GATT_CHR_F_WRITE_AUTHOR                     0x4000

#define BLE_GATT_SVC_TYPE_END                           0
#define BLE_GATT_SVC_TYPE_PRIMARY                       1
#define BLE_GATT_SVC_TYPE_SECONDARY                     2

/***@客户端。*/
struct ble_gatt_error {
    uint16_t status;
    uint16_t att_handle;
};

struct ble_gatt_svc {
    uint16_t start_handle;
    uint16_t end_handle;
    ble_uuid_any_t uuid;
};

struct ble_gatt_attr {
    uint16_t handle;
    uint16_t offset;
    struct os_mbuf *om;
};

struct ble_gatt_chr {
    uint16_t def_handle;
    uint16_t val_handle;
    uint8_t properties;
    ble_uuid_any_t uuid;
};

struct ble_gatt_dsc {
    uint16_t handle;
    ble_uuid_any_t uuid;
};

typedef int ble_gatt_mtu_fn(uint16_t conn_handle,
                            const struct ble_gatt_error *error,
                            uint16_t mtu, void *arg);
typedef int ble_gatt_disc_svc_fn(uint16_t conn_handle,
                                 const struct ble_gatt_error *error,
                                 const struct ble_gatt_svc *service,
                                 void *arg);

/**
 * 执行回调后，主机将自动释放属性mbuf。应用程序可以获得mbuf的所有权，并通过向attr->om分配NULL来防止其被释放。
 */
typedef int ble_gatt_attr_fn(uint16_t conn_handle,
                             const struct ble_gatt_error *error,
                             struct ble_gatt_attr *attr,
                             void *arg);

/**
 * 执行回调后，主机将自动释放属性mbufs。应用程序可以获得mbuf的所有权，并通过向每个属性的om字段分配NULL来防止它们被释放。
 */
typedef int ble_gatt_reliable_attr_fn(uint16_t conn_handle,
                                      const struct ble_gatt_error *error,
                                      struct ble_gatt_attr *attrs,
                                      uint8_t num_attrs, void *arg);

typedef int ble_gatt_chr_fn(uint16_t conn_handle,
                            const struct ble_gatt_error *error,
                            const struct ble_gatt_chr *chr, void *arg);

typedef int ble_gatt_dsc_fn(uint16_t conn_handle,
                            const struct ble_gatt_error *error,
                            uint16_t chr_val_handle,
                            const struct ble_gatt_dsc *dsc,
                            void *arg);

/**
 * 启动GATT程序：交换MTU。
 *
 * @param conn_handle           通过其执行过程的连接。
 * @param cb                    用于报告过程状态更新的函数；null表示没有回调。
 * @param cb_arg                要传递给回调函数的可选参数。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gattc_exchange_mtu(uint16_t conn_handle,
                           ble_gatt_mtu_fn *cb, void *cb_arg);

/**
 * 启动GATT程序：发现所有主要服务。
 *
 * @param conn_handle           通过其执行过程的连接。
 * @param cb                    用于报告过程状态更新的函数；null表示没有回调。
 * @param cb_arg                要传递给回调函数的可选参数。
 */
int ble_gattc_disc_all_svcs(uint16_t conn_handle,
                            ble_gatt_disc_svc_fn *cb, void *cb_arg);

/**
 * 启动GATT程序：按服务UUID发现主要服务。
 *
 * @param conn_handle           通过其执行过程的连接。
 * @param service_uuid128       要发现的服务的128位UUID。
 * @param cb                    用于报告过程状态更新的函数；null表示没有回调。
 * @param cb_arg                要传递给回调函数的可选参数。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gattc_disc_svc_by_uuid(uint16_t conn_handle, const ble_uuid_t *uuid,
                               ble_gatt_disc_svc_fn *cb, void *cb_arg);

/**
 * 启动GATT程序：查找包含的服务。
 *
 * @param conn_handle           通过其执行过程的连接。
 * @param start_handle          开始搜索的句柄（通常是服务定义句柄）。
 * @param end_handle            结束搜索的句柄（通常是服务中的最后一个句柄）。
 * @param cb                    用于报告过程状态更新的函数；null表示没有回调。
 * @param cb_arg                要传递给回调函数的可选参数。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gattc_find_inc_svcs(uint16_t conn_handle, uint16_t start_handle,
                            uint16_t end_handle,
                            ble_gatt_disc_svc_fn *cb, void *cb_arg);

/**
 * 启动GATT程序：发现服务的所有特征。
 *
 * @param conn_handle           通过其执行过程的连接。
 * @param start_handle          开始搜索的句柄（通常是服务定义句柄）。
 * @param end_handle            结束搜索的句柄（通常是服务中的最后一个句柄）。
 * @param cb                    用于报告过程状态更新的函数；null表示没有回调。
 * @param cb_arg                要传递给回调函数的可选参数。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gattc_disc_all_chrs(uint16_t conn_handle, uint16_t start_handle,
                            uint16_t end_handle, ble_gatt_chr_fn *cb,
                            void *cb_arg);

/**
 * 启动GATT程序：通过UUID发现特征。
 *
 * @param conn_handle           通过其执行过程的连接。
 * @param start_handle          开始搜索的句柄（通常是服务定义句柄）。
 * @param end_handle            结束搜索的句柄（通常是服务中的最后一个句柄）。
 * @param chr_uuid128           要发现的特征的128位UUID。
 * @param cb                    用于报告过程状态更新的函数；null表示没有回调。
 * @param cb_arg                要传递给回调函数的可选参数。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gattc_disc_chrs_by_uuid(uint16_t conn_handle, uint16_t start_handle,
                               uint16_t end_handle, const ble_uuid_t *uuid,
                               ble_gatt_chr_fn *cb, void *cb_arg);

/**
 * 启动GATT程序：发现所有特征描述符。
 *
 * @param conn_handle           通过其执行过程的连接。
 * @param chr_val_handle        特征值属性的句柄。
 * @param chr_end_handle        特征定义中的最后一个句柄。
 * @param cb                    用于报告过程状态更新的函数；null表示没有回调。
 * @param cb_arg                要传递给回调函数的可选参数。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gattc_disc_all_dscs(uint16_t conn_handle, uint16_t start_handle,
                            uint16_t end_handle,
                            ble_gatt_dsc_fn *cb, void *cb_arg);

/**
 * 启动GATT程序：读取特征值。
 *
 * @param conn_handle           通过其执行过程的连接。
 * @param attr_handle           要读取的特征值的句柄。
 * @param cb                    用于报告过程状态更新的函数；null表示没有回调。
 * @param cb_arg                要传递给回调函数的可选参数。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gattc_read(uint16_t conn_handle, uint16_t attr_handle,
                   ble_gatt_attr_fn *cb, void *cb_arg);

/**
 * 启动GATT程序：使用特征UUID读取。
 *
 * @param conn_handle           通过其执行过程的连接。
 * @param start_handle          要搜索的第一个句柄（通常是服务定义的句柄）。
 * @param end_handle            最后一个要搜索的句柄（通常是服务定义中的最后一个句柄）。
 * @param cb                    用于报告过程状态更新的函数；null表示没有回调。
 * @param cb_arg                要传递给回调函数的可选参数。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gattc_read_by_uuid(uint16_t conn_handle, uint16_t start_handle,
                           uint16_t end_handle, const ble_uuid_t *uuid,
                           ble_gatt_attr_fn *cb, void *cb_arg);

/**
 * 启动GATT程序：读取长特征值。
 *
 * @param conn_handle           通过其执行过程的连接。
 * @param handle                要读取的特征值的句柄。
 * @param cb                    用于报告过程状态更新的函数；null表示没有回调。
 * @param cb_arg                要传递给回调函数的可选参数。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gattc_read_long(uint16_t conn_handle, uint16_t handle, uint16_t offset,
                        ble_gatt_attr_fn *cb, void *cb_arg);

/**
 * 启动GATT程序：读取多个特征值。
 *
 * @param conn_handle           通过其执行过程的连接。
 * @param handles               要读取的16位属性句柄数组。
 * @param num_handles           “handles”数组中的条目数。
 * @param cb                    用于报告过程状态更新的函数；null表示没有回调。
 * @param cb_arg                要传递给回调函数的可选参数。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gattc_read_mult(uint16_t conn_handle, const uint16_t *handles,
                        uint8_t num_handles, ble_gatt_attr_fn *cb,
                        void *cb_arg);

/**
 * 启动GATT程序：无响应写入。无论结果如何，此函数都会消耗所提供的mbuf。
 *
 * @param conn_handle           通过其执行过程的连接。
 * @param attr_handle           要写入的特征值的句柄。
 * @param txom                  要写入特性的值。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gattc_write_no_rsp(uint16_t conn_handle, uint16_t attr_handle,
                           struct os_mbuf *om);

/**
 * 启动GATT程序：无响应写入。无论结果如何，此函数都会消耗所提供的mbuf。
 *
 * @param conn_handle           通过其执行过程的连接。
 * @param attr_handle           要写入的特征值的句柄。
 * @param value                 要写入特性的值。
 * @param value_len             要写入的字节数。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gattc_write_no_rsp_flat(uint16_t conn_handle, uint16_t attr_handle,
                                const void *data, uint16_t data_len);

/**
 * 启动GATT程序：写入特征值。无论结果如何，此函数都会消耗所提供的mbuf。
 *
 * @param conn_handle           通过其执行过程的连接。
 * @param attr_handle           要写入的特征值的句柄。
 * @param txom                  要写入特性的值。
 * @param cb                    用于报告过程状态更新的函数；null表示没有回调。
 * @param cb_arg                要传递给回调函数的可选参数。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gattc_write(uint16_t conn_handle, uint16_t attr_handle,
                    struct os_mbuf *om,
                    ble_gatt_attr_fn *cb, void *cb_arg);

/**
 * 启动GATT程序：写入特征值（平面缓冲区版本）。
 *
 * @param conn_handle           通过其执行过程的连接。
 * @param attr_handle           要写入的特征值的句柄。
 * @param value                 要写入特性的值。
 * @param value_len             要写入的字节数。
 * @param cb                    用于报告过程状态更新的函数；null表示没有回调。
 * @param cb_arg                要传递给回调函数的可选参数。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gattc_write_flat(uint16_t conn_handle, uint16_t attr_handle,
                         const void *data, uint16_t data_len,
                         ble_gatt_attr_fn *cb, void *cb_arg);

/**
 * 启动GATT程序：写入长特征值。无论结果如何，此函数都会消耗所提供的mbuf。
 *
 * @param conn_handle           通过其执行过程的连接。
 * @param attr_handle           要写入的特征值的句柄。
 * @param txom                  要写入特性的值。
 * @param cb                    用于报告过程状态更新的函数；null表示没有回调。
 * @param cb_arg                要传递给回调函数的可选参数。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gattc_write_long(uint16_t conn_handle, uint16_t attr_handle,
                         uint16_t offset, struct os_mbuf *om,
                         ble_gatt_attr_fn *cb, void *cb_arg);

/**
 * 启动GATT程序：可靠写入。无论结果如何，此函数都会消耗提供的mbufs。
 *
 * @param conn_handle           通过其执行过程的连接。
 * @param attrs                 属性描述符数组；指定要写入哪些特征以及要写入哪些数据。此函数将每个属性中的mbuf指针设置为NULL。
 * @param num_attrs             要写入的特征数量；等于“attrs”数组中的元素数。
 * @param cb                    用于报告过程状态更新的函数；null表示没有回调。
 * @param cb_arg                要传递给回调函数的可选参数。
 */
int ble_gattc_write_reliable(uint16_t conn_handle,
                             struct ble_gatt_attr *attrs,
                             int num_attrs, ble_gatt_reliable_attr_fn *cb,
                             void *cb_arg);

/**
 * 发送“自由格式”特征通知。无论结果如何，此函数都会消耗所提供的mbuf。
 *
 * @param conn_handle           通过其执行过程的连接。
 * @param chr_val_handle        要在传出通知中指示的属性句柄。
 * @param txom                  要写入特性的值。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gattc_notify_custom(uint16_t conn_handle, uint16_t att_handle,
                            struct os_mbuf *om);

/**
 * 发送特征通知。从指定的特征读取消息内容。
 *
 * @param conn_handle           通过其执行过程的连接。
 * @param chr_val_handle        要包含在传出通知中的特性的值属性句柄。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gattc_notify(uint16_t conn_handle, uint16_t chr_val_handle);

/**
 * 发送“自由格式”特征指示。提供的mbuf包含指示有效载荷。无论结果如何，此函数都会消耗所提供的mbuf。
 *
 * @param conn_handle           通过其执行过程的连接。
 * @param chr_val_handle        要包含在传出指示中的特性的值属性句柄。
 * @param txom                  要包含在指示中的数据。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gattc_indicate_custom(uint16_t conn_handle, uint16_t chr_val_handle,
                              struct os_mbuf *txom);

/**
 * 发送特征指示。从指定的特征读取消息内容。
 *
 * @param conn_handle           通过其执行过程的连接。
 * @param chr_val_handle        要包含在传出指示中的特性的值属性句柄。
 *
 * @return                      成功时为0；失败时为非零。
 */
int ble_gattc_indicate(uint16_t conn_handle, uint16_t chr_val_handle);

int ble_gattc_init(void);

/***@服务器。*/

struct ble_gatt_access_ctxt;
typedef int ble_gatt_access_fn(uint16_t conn_handle, uint16_t attr_handle,
                               struct ble_gatt_access_ctxt *ctxt, void *arg);

typedef uint16_t ble_gatt_chr_flags;

struct ble_gatt_chr_def {
    /**
     * 指向特征UUID的指针；使用BLE_UUIDxx_DECLARE宏声明正确的UUID；如果服务中没有更多特征，则为NULL。
     */
    const ble_uuid_t *uuid;

    /**
     * 读取或写入此特性时执行的回调。
     */
    ble_gatt_access_fn *access_cb;

    /**回调的可选参数。*/
    void *arg;

    /**
     * 此特性描述符的数组。如果没有描述符，则为NULL。不包括CCCD；如果设置了该特性的通知或指示标志，则自动添加。
     */
    struct ble_gatt_dsc_def *descriptors;

    /**指定此特性允许的操作集。*/
    ble_gatt_chr_flags flags;

    /**指定访问此特性所需的最小密钥大小。*/
    uint8_t min_key_size;

    /**
     * 在注册时，将用特征的值属性句柄填充。
     */
    uint16_t *val_handle;
};

struct ble_gatt_svc_def {
    /**
     * 以下之一：o BLE_GATT_SVC_TYPE_PRIMARY-主要服务o BLE_GATT_SVC_TTYPE_SECONDARY-次要服务o 0-此阵列中没有其他服务。
     */
    uint8_t type;

    /**
     * 指向服务UUID的指针；使用BLE_UUIDxx_DECLARE宏声明正确的UUID；如果服务中没有更多特征，则为NULL。
     */
    const ble_uuid_t *uuid;

    /**
     * 指向其他服务定义的指针数组。在服务发现期间，这些服务被报告为“包含的服务”。使用NULL终止数组。
     */
    const struct ble_gatt_svc_def **includes;

    /**
     * 与属于此服务的特征相对应的特征定义数组。
     */
    const struct ble_gatt_chr_def *characteristics;
};

struct ble_gatt_dsc_def {
    /**
     * 指向描述符UUID的指针；使用BLE_UUIDxx_DECLARE宏声明正确的UUID；如果服务中没有更多特征，则为NULL。
     */
    const ble_uuid_t *uuid;

    /**指定此描述符允许的操作集。*/
    uint8_t att_flags;

    /**指定访问此描述符所需的最小密钥大小。*/
    uint8_t min_key_size;

    /**读取或写入描述符时执行的回调。*/
    ble_gatt_access_fn *access_cb;

    /**回调的可选参数。*/
    void *arg;
};

/**
 * 访问GATT特征或描述符的上下文。当客户端读取或写入本地注册的特征或描述符时，此结构的实例将传递给应用程序回调。
 */
struct ble_gatt_access_ctxt {
    /**
     * 指示正在执行的gatt操作。这等于以下值之一：o BLE_GATT_ACCESS_OP_READ_CHR o BLE_GATT_ACCESS_OP_WRITE_CHR o BLE_GATT_AACCESS_OP_READ_DSC o BLE_GATT_ACCESS-OP_WRITE_DSC
     */
    uint8_t op;

    /**
     * GATT访问数据的容器。o For reads：应用程序用正在读取的特征或描述符的值填充此值。o对于写入：这已经填充了对等方正在写入的值。如果应用程序希望保留此mbuf供以后使用，则访问回调必须将此指针设置为NULL，以防止堆栈释放它。
     */
    struct os_mbuf *om;

    /**
     * 正在执行的GATT操作决定了该联盟中的哪个字段有效。如果正在访问特征，则chr字段有效。否则将访问描述符，在这种情况下，dsc字段是有效的。
     */
    union {
        /**
         * 与所访问的特性相对应的特性定义。这是应用程序在启动时注册的内容。
         */
        const struct ble_gatt_chr_def *chr;

        /**
         * 与正在访问的描述符相对应的描述符定义。这是应用程序在启动时注册的内容。
         */
        const struct ble_gatt_dsc_def *dsc;
    };
};

/**
 * 传递给注册回调的上下文；表示正在注册的GATT服务、特征或描述符。
 */
struct ble_gatt_register_ctxt {
    /**
     * 指示刚刚执行的gatt注册操作。这等于以下值之一：o BLE_GATT_REGISTER_OP_SVC o BLE_GATT_REGISTER_OP_CHR o BLE_GATT_REGISTED_OP_DSC
     */
    uint8_t op;

    /**
     * op字段的值决定此联合中的哪个字段有效。
     */
    union {
        /**服务；如果op==BLE_GATT_REGISTER_op_SVC，则有效。*/
        struct {
            /**服务定义属性的ATT句柄。*/
            uint16_t handle;

            /**
             * 表示正在注册的服务的服务定义。
             */
            const struct ble_gatt_svc_def *svc_def;
        } svc;

        /**特性；如果op==BLE_GATT_REGISTER_op_CHR，则有效。*/
        struct {
            /**特征定义属性的ATT句柄。*/
            uint16_t def_handle;

            /**特征值属性的ATT句柄。*/
            uint16_t val_handle;

            /**
             * 表示正在注册的特征的特征定义。
             */
            const struct ble_gatt_chr_def *chr_def;

            /**
             * 与特征的父服务相对应的服务定义。
             */
            const struct ble_gatt_svc_def *svc_def;
        } chr;

        /**描述符；如果op==BLE_GATT_REGISTER_op_DSC，则有效。*/
        struct {
            /**描述符定义属性的ATT句柄。*/
            uint16_t handle;

            /**
             * 与正在注册的描述符相对应的描述符定义。
             */
            const struct ble_gatt_dsc_def *dsc_def;

            /**
             * 与描述符的父特性相对应的特性定义。
             */
            const struct ble_gatt_chr_def *chr_def;

            /**
             * 与描述符的祖父服务对应的服务定义
             */
            const struct ble_gatt_svc_def *svc_def;
        } dsc;
    };
};

typedef void ble_gatt_register_fn(struct ble_gatt_register_ctxt *ctxt,
                                  void *arg);

/**
 * 将一组服务定义排队进行注册。当调用ble_gatts_start（）时，以这种方式排队的所有服务都会注册。
 *
 * @param svcs                  要排队注册的服务定义数组。此数组必须以“type”等于0的条目终止。
 *
 * @return                      成功时为0；堆耗尽时的BLE_HS_ENOMEM。
 */
int ble_gatts_add_svcs(const struct ble_gatt_svc_def *svcs);

/**
 * 设置本地GATT服务的可见性。不可见的服务不会从数据库中删除，但不会被对等设备发现。应用程序应在需要时通过调用ble_svc_gatt_Changed（）来处理服务更改。
 *
 * @param handle                服务的处理
 * @param visible               如果服务应可见，则为非零
 *
 * @return                      成功时为0；如果未找到服务，则返回BLE_HS_ENOENT。
 */
int ble_gatts_svc_set_visibility(uint16_t handle, int visible);

/**
 * 调整主机配置对象的设置以适应指定的服务定义数组。该函数将计数添加到所提供的配置对象中的相应字段中，而无需先清除它们，因此可以使用不同的输入重复调用该函数以计算总数。在第一次调用此函数之前，请确保将GATT服务器设置归零。
 *
 * @param defs                  包含要计数的资源定义的服务数组。
 *
 * @return                      成功时为0；如果svcs数组包含无效的资源定义，则返回BLE_HS_EINVAL。
 */
int ble_gatts_count_cfg(const struct ble_gatt_svc_def *defs);

/**
 * 向已订阅特定特性的通知（或指示）的任何连接设备发送通知（或显示）。
 *
 * @param chr_val_handle        特征值句柄
 */
void ble_gatts_chr_updated(uint16_t chr_val_handle);

/**
 * 检索与本地GATT服务关联的属性句柄。
 *
 * @param uuid                  要查找的服务的UUID。
 * @param out_handle            成功时，填充服务属性的句柄。如果不需要此值，则传递null。
 *
 * @return                      成功时为0；如果找不到指定的服务，则返回BLE_HS_ENOENT。
 */
int ble_gatts_find_svc(const ble_uuid_t *uuid, uint16_t *out_handle);

/**
 * 检索与本地GATT特性关联的一对属性句柄。
 *
 * @param svc_uuid              父服务的UUID。
 * @param chr_uuid              要查找的特征的UUID。
 * @param out_def_handle        成功时，填充特征定义属性的句柄。如果不需要此值，则传递null。
 * @param out_val_handle        成功时，填充特征值属性的句柄。如果不需要此值，则传递null。
 *
 * @return                      成功时为0；如果找不到指定的服务或特性，则返回BLE_HS_ENOENT。
 */
int ble_gatts_find_chr(const ble_uuid_t *svc_uuid, const ble_uuid_t *chr_uuid,
                       uint16_t *out_def_handle, uint16_t *out_val_handle);

/**
 * 检索与本地GATT描述符关联的属性句柄。
 *
 * @param svc_uuid              祖父服务的UUID。
 * @param chr_uuid              父特征的UUID。
 * @param dsc_uuid              查找描述符的UUID。
 * @param out_handle            成功时，填充描述符属性的句柄。如果不需要此值，则传递null。
 *
 * @return                      成功时为0；如果找不到指定的服务、特征或描述符，则返回BLE_HS_ENOENT。
 */
int ble_gatts_find_dsc(const ble_uuid_t *svc_uuid, const ble_uuid_t *chr_uuid,
                       const ble_uuid_t *dsc_uuid, uint16_t *out_dsc_handle);

typedef void (*ble_gatt_svc_foreach_fn)(const struct ble_gatt_svc_def *svc,
                                        uint16_t handle,
                                        uint16_t end_group_handle,
                                        void *arg);

/**
 * 打印本地GATT数据库的转储。这对于以人类可读的形式记录数据库的本地状态非常有用。
 */
void ble_gatts_show_local(void);

/**
 * 将GATT服务器重置为其初始状态。成功后，此函数将删除所有支持的服务、特征和描述符。此功能要求：o没有对等端连接，o没有GAP操作处于活动状态（通告、发现或连接）。
 *
 * @return                      成功时为0；BLE_HS_EBUSY，如果GATT服务器由于现有连接或活动GAP过程而无法重置。
 */
int ble_gatts_reset(void);

/**
 * 使所有注册的服务对对等方可用。此函数在启动时由NimBLE主机自动调用；手动调用仅在用新服务替换一组受支持的服务时才需要。此功能要求：o没有对等端连接，o没有GAP操作处于活动状态（通告、发现或连接）。
 *
 * @return                      成功时为0；BLE主机核心在出现意外错误时返回代码。
 */
int ble_gatts_start(void);

/**
 * 重置GATT配置参数并释放属性内存。
 *
 */
void ble_gatts_stop(void);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif

