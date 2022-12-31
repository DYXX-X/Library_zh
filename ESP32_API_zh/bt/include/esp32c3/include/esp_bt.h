/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef __ESP_BT_H__
#define __ESP_BT_H__

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "sdkconfig.h"
#include "esp_task.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_BT_CTRL_CONFIG_MAGIC_VAL    0x5A5AA5A5
#define ESP_BT_CTRL_CONFIG_VERSION      0x02112280

#define ESP_BT_HCI_TL_MAGIC_VALUE   0xfadebead
#define ESP_BT_HCI_TL_VERSION       0x00010000

/**
 * @brief 控制器启用/禁用的蓝牙模式
 */
typedef enum {
    ESP_BT_MODE_IDLE       = 0x00,   /*!< 蓝牙未运行*/
    ESP_BT_MODE_BLE        = 0x01,   /*!< 运行BLE模式*/
    ESP_BT_MODE_CLASSIC_BT = 0x02,   /*!< 运行经典BT模式*/
    ESP_BT_MODE_BTDM       = 0x03,   /*!< 运行双模式*/
} esp_bt_mode_t;

/**
 * @brief 控制器类型HCI传输层
 */
typedef enum {
    ESP_BT_CTRL_HCI_TL_UART = 0,      /*!< HCI UART h4传输层*/
    ESP_BT_CTRL_HCI_TL_VHCI = 1,      /*!< VHCI接口*/
} esp_bt_ctrl_hci_tl_t;

/**
 * @breif BLE连接事件长度计算类型
 */
typedef enum {
    ESP_BLE_CE_LEN_TYPE_ORIG = 0,      /*!< 起初的*/
    ESP_BLE_CE_LEN_TYPE_CE   = 1,      /*!< 使用HCI命令中的CE_LEN参数*/
    ESP_BLE_CE_LEN_TYPE_SD   = 1,      /*!< Espressif供应商定义*/
} esp_ble_ce_len_t;

/**
 * @brief 蓝牙睡眠模式
 */
typedef enum {
    ESP_BT_SLEEP_MODE_NONE = 0,      /*!< 蓝牙睡眠模式已禁用*/
    ESP_BT_SLEEP_MODE_1    = 1,      /*!< 蓝牙睡眠模式1*/
} esp_bt_sleep_mode_t;

/**
 * @brief 蓝牙睡眠时钟
 */
typedef enum {
    ESP_BT_SLEEP_CLOCK_NONE            = 0,   /*!< 睡眠时钟未配置*/
    ESP_BT_SLEEP_CLOCK_MAIN_XTAL       = 1,   /*!< SoC主晶体*/
    ESP_BT_SLEEP_CLOCK_EXT_32K_XTAL    = 2,   /*!< 外部32.768kHz晶体*/
    ESP_BT_SLEEP_CLOCK_RTC_SLOW        = 3,   /*!< 内部150kHz RC振荡器*/
    ESP_BT_SLEEP_CLOCK_FPGA_32K        = 4,   /*!< 临时用于FPGA的硬接线32KHz时钟*/
} esp_bt_sleep_clock_t;

/**
 * @brief 用于蓝牙的天线索引
 */
enum {
    ESP_BT_ANT_IDX_0 = 0,               /*!< anntena编号0*/
    ESP_BT_ANT_IDX_1 = 1,               /*!< 1号天线*/
};

/**
 * @brief 编码PHY连接的最大Tx/Rx时间限制
 */
enum {
    ESP_BT_COEX_PHY_CODED_TX_RX_TIME_LIMIT_FORCE_DISABLE = 0,    /*!< 禁用限制*/
    ESP_BT_COEX_PHY_CODED_TX_RX_TIME_LIMIT_FORCE_ENABLE,         /*!< 始终启用限制*/
};

#define ESP_BT_HCI_TL_STATUS_OK            (0)   /*!< HCI_TL Tx/Rx操作状态正常*/

/**
 * @brief HCI传输层发送/接收操作的回调函数
 */
typedef void (* esp_bt_hci_tl_callback_t) (void *arg, uint8_t status);

#ifdef CONFIG_BT_ENABLED

#define BT_CTRL_BLE_MAX_ACT_LIMIT           10  //最大BLE活动限制
#define SLAVE_CE_LEN_MIN_DEFAULT             5

#ifdef CONFIG_BT_CTRL_SCAN_DUPL_TYPE
#define SCAN_DUPLICATE_TYPE_VALUE  CONFIG_BT_CTRL_SCAN_DUPL_TYPE
#else
#define SCAN_DUPLICATE_TYPE_VALUE  0
#endif

/* 正常adv缓存大小*/
#ifdef CONFIG_BT_CTRL_SCAN_DUPL_CACHE_SIZE
#define NORMAL_SCAN_DUPLICATE_CACHE_SIZE            CONFIG_BT_CTRL_SCAN_DUPL_CACHE_SIZE
#else
#define NORMAL_SCAN_DUPLICATE_CACHE_SIZE            20
#endif

#ifndef CONFIG_BT_CTRL_BLE_MESH_SCAN_DUPL_EN
#define CONFIG_BT_CTRL_BLE_MESH_SCAN_DUPL_EN FALSE
#endif

#define SCAN_DUPLICATE_MODE_NORMAL_ADV_ONLY         0
#define SCAN_DUPLICATE_MODE_NORMAL_ADV_MESH_ADV     1

#if CONFIG_BT_CTRL_BLE_MESH_SCAN_DUPL_EN
    #define SCAN_DUPLICATE_MODE                     SCAN_DUPLICATE_MODE_NORMAL_ADV_MESH_ADV
    #ifdef CONFIG_BT_CTRL_MESH_DUPL_SCAN_CACHE_SIZE
    #define MESH_DUPLICATE_SCAN_CACHE_SIZE          CONFIG_BT_CTRL_MESH_DUPL_SCAN_CACHE_SIZE
    #else
    #define MESH_DUPLICATE_SCAN_CACHE_SIZE          50
    #endif
#else
    #define SCAN_DUPLICATE_MODE SCAN_DUPLICATE_MODE_NORMAL_ADV_ONLY
    #define MESH_DUPLICATE_SCAN_CACHE_SIZE          0
#endif

#ifdef CONFIG_BT_CTRL_AGC_RECORRECT_EN
#define BT_CTRL_AGC_RECORRECT_EN  CONFIG_BT_CTRL_AGC_RECORRECT_EN
#else
#define BT_CTRL_AGC_RECORRECT_EN        0
#endif

#ifdef CONFIG_BT_CTRL_CODED_AGC_RECORRECT_EN
#define BT_CTRL_CODED_AGC_RECORRECT  CONFIG_BT_CTRL_CODED_AGC_RECORRECT_EN
#else
#define BT_CTRL_CODED_AGC_RECORRECT        0
#endif

#define AGC_RECORRECT_EN       ((BT_CTRL_AGC_RECORRECT_EN << 0) | (BT_CTRL_CODED_AGC_RECORRECT <<1))


#define CFG_MASK_BIT_SCAN_DUPLICATE_OPTION    (1<<0)

#define CFG_NASK      CFG_MASK_BIT_SCAN_DUPLICATE_OPTION

#define BLE_HW_TARGET_CODE_ESP32C3_CHIP_ECO0                      (0x01010000)

#define BT_CONTROLLER_INIT_CONFIG_DEFAULT() {                              \
    .magic = ESP_BT_CTRL_CONFIG_MAGIC_VAL,                                 \
    .version = ESP_BT_CTRL_CONFIG_VERSION,                                 \
    .controller_task_stack_size = ESP_TASK_BT_CONTROLLER_STACK,            \
    .controller_task_prio = ESP_TASK_BT_CONTROLLER_PRIO,                   \
    .controller_task_run_cpu = CONFIG_BT_CTRL_PINNED_TO_CORE,              \
    .bluetooth_mode = CONFIG_BT_CTRL_MODE_EFF,                             \
    .ble_max_act = CONFIG_BT_CTRL_BLE_MAX_ACT_EFF,                         \
    .sleep_mode = CONFIG_BT_CTRL_SLEEP_MODE_EFF,                           \
    .sleep_clock = CONFIG_BT_CTRL_SLEEP_CLOCK_EFF,                         \
    .ble_st_acl_tx_buf_nb = CONFIG_BT_CTRL_BLE_STATIC_ACL_TX_BUF_NB,       \
    .ble_hw_cca_check = CONFIG_BT_CTRL_HW_CCA_EFF,                         \
    .ble_adv_dup_filt_max = CONFIG_BT_CTRL_ADV_DUP_FILT_MAX,               \
    .ce_len_type = CONFIG_BT_CTRL_CE_LENGTH_TYPE_EFF,                      \
    .hci_tl_type = CONFIG_BT_CTRL_HCI_TL_EFF,                              \
    .hci_tl_funcs = NULL,                                                  \
    .txant_dft = CONFIG_BT_CTRL_TX_ANTENNA_INDEX_EFF,                      \
    .rxant_dft = CONFIG_BT_CTRL_RX_ANTENNA_INDEX_EFF,                      \
    .txpwr_dft = CONFIG_BT_CTRL_DFT_TX_POWER_LEVEL_EFF,                    \
    .cfg_mask = CFG_NASK,                                                  \
    .scan_duplicate_mode = SCAN_DUPLICATE_MODE,                            \
    .scan_duplicate_type = SCAN_DUPLICATE_TYPE_VALUE,                      \
    .normal_adv_size = NORMAL_SCAN_DUPLICATE_CACHE_SIZE,                   \
    .mesh_adv_size = MESH_DUPLICATE_SCAN_CACHE_SIZE,                       \
    .coex_phy_coded_tx_rx_time_limit = CONFIG_BT_CTRL_COEX_PHY_CODED_TX_RX_TLIM_EFF, \
    .hw_target_code = BLE_HW_TARGET_CODE_ESP32C3_CHIP_ECO0,                \
    .slave_ce_len_min = SLAVE_CE_LEN_MIN_DEFAULT,                          \
    .hw_recorrect_en = AGC_RECORRECT_EN,                                   \
    .cca_thresh = CONFIG_BT_CTRL_HW_CCA_VAL,                               \
};

#else
#define BT_CONTROLLER_INIT_CONFIG_DEFAULT() {0}; _Static_assert(0, "please enable bluetooth in menuconfig to use bt.h");
#endif

/**
 * @brief 当HCI传输层为UART时，应注册该结构
 */
typedef struct {
    uint32_t _magic;                        /* 魔术数字*/
    uint32_t _version;                      /* 定义结构的版本号*/
    uint32_t _reserved;                     /* 保留供将来使用*/
    int (* _open)(void);                    /* hci tl打开*/
    void (* _close)(void);                  /* hci tl关闭*/
    void (* _finish_transfers)(void);       /* hci tl面漆*/
    void (* _recv)(uint8_t *buf, uint32_t len, esp_bt_hci_tl_callback_t callback, void* arg); /* hci tl回收*/
    void (* _send)(uint8_t *buf, uint32_t len, esp_bt_hci_tl_callback_t callback, void* arg); /* hci tl发送*/
    bool (* _flow_off)(void); /* hci tl流量关闭*/
    void (* _flow_on)(void); /* hci tl流量开启*/
} esp_bt_hci_tl_t;

/**
 * @brief 控制器配置选项，取决于配置掩码。配置掩码指示启用了哪些功能，这意味着配置掩码启用了某些功能的某些选项或参数。
 */
typedef struct {
    /*
     * 调用esp_bt_controller_init（）时，无法在运行时配置以下参数。它们将被menuconfig选项或宏中的常量值覆盖。因此，在esp_bt_controller_init（）时不要修改值
     */
    uint32_t magic;                         /*!< 魔术数字*/
    uint32_t version;                       /*!< 定义结构的版本号*/
    /*
     * 调用esp_bt_controller_init（）时，可以在运行时配置以下参数
     */
    uint16_t controller_task_stack_size;    /*!< 蓝牙控制器任务堆栈大小*/
    uint8_t controller_task_prio;           /*!< 蓝牙控制器任务优先级*/
    uint8_t controller_task_run_cpu;        /*!< 运行蓝牙控制器任务的CPU编号*/
    uint8_t bluetooth_mode;                 /*!< 控制器模式：BR/EDR、BLE或双模式*/
    uint8_t ble_max_act;                    /*!< BLE最大空中活动次数*/
    uint8_t sleep_mode;                     /*!< 控制器休眠模式*/
    uint8_t sleep_clock;                    /*!< 控制器睡眠时钟*/
    uint8_t ble_st_acl_tx_buf_nb;           /*!< 控制器静态ACL TX BUFFER编号*/
    uint8_t ble_hw_cca_check;               /*!< 控制器硬件触发CCA检查*/
    uint16_t ble_adv_dup_filt_max;          /*!< 最大重复扫描过滤器数*/
    bool coex_param_en;                     /*!< 已弃用*/
    uint8_t ce_len_type;                    /*!< 连接事件长度计算方法*/
    bool coex_use_hooks;                    /*!< 已弃用*/
    uint8_t hci_tl_type;                    /*!< HCI传输层、UART、VHCI等*/
    esp_bt_hci_tl_t *hci_tl_funcs;          /*!< 当hci_tl_type为UART时，必须设置使用的hci传输函数*/
    uint8_t txant_dft;                      /*!< 默认Tx天线*/
    uint8_t rxant_dft;                      /*!< 默认Rx天线*/
    uint8_t txpwr_dft;                      /*!< 默认Tx功率*/
    uint32_t cfg_mask;
    uint8_t scan_duplicate_mode;            /*!< 扫描复制模式*/
    uint8_t scan_duplicate_type;            /*!< 扫描重复类型*/
    uint16_t normal_adv_size;               /*!< 扫描副本的正常adv大小*/
    uint16_t mesh_adv_size;                 /*!< 扫描副本的网格adv大小*/
    uint8_t coex_phy_coded_tx_rx_time_limit;  /*!< 使用CODED-PHY和Wi-Fi共存连接时的最大tx/rx时间限制*/
    uint32_t hw_target_code;                /*!< 硬件目标*/
    uint8_t slave_ce_len_min;
    uint8_t hw_recorrect_en;
    uint8_t cca_thresh;                     /*!< cca阈值*/
} esp_bt_controller_config_t;

/**
 * @brief 蓝牙控制器启用/禁用/初始化/解除初始化状态
 */
typedef enum {
    ESP_BT_CONTROLLER_STATUS_IDLE = 0,
    ESP_BT_CONTROLLER_STATUS_INITED,
    ESP_BT_CONTROLLER_STATUS_ENABLED,
    ESP_BT_CONTROLLER_STATUS_NUM,
} esp_bt_controller_status_t;

/**
 * @brief BLE tx电源类型ESP_BLE_PWR_type_CONN_HDL0-8：用于每个连接，仅在连接完成后设置。当断开时，相应的TX功率不受影响。ESP_BLE_PWR_TYPE_ADV：用于广告/扫描响应。ESP_BLE_PWR_TYPE_SCAN：用于扫描。ESP_BLE_PWR_TYPE_DEFAULT：如果未设置每个连接的发送功率，则将使用此默认值。如果既不处于扫描模式也不处于adv模式，它将使用此默认值。如果未设置任何电源类型，系统将使用ESP_PWR_LVL_P3作为ADV/SCAN/CONN0-9的默认值。
 */
typedef enum {
    ESP_BLE_PWR_TYPE_CONN_HDL0  = 0,            /*!< 用于连接手柄0*/
    ESP_BLE_PWR_TYPE_CONN_HDL1  = 1,            /*!< 用于连接手柄1*/
    ESP_BLE_PWR_TYPE_CONN_HDL2  = 2,            /*!< 用于连接手柄2*/
    ESP_BLE_PWR_TYPE_CONN_HDL3  = 3,            /*!< 用于连接手柄3*/
    ESP_BLE_PWR_TYPE_CONN_HDL4  = 4,            /*!< 用于连接手柄4*/
    ESP_BLE_PWR_TYPE_CONN_HDL5  = 5,            /*!< 用于连接手柄5*/
    ESP_BLE_PWR_TYPE_CONN_HDL6  = 6,            /*!< 用于连接手柄6*/
    ESP_BLE_PWR_TYPE_CONN_HDL7  = 7,            /*!< 用于连接手柄7*/
    ESP_BLE_PWR_TYPE_CONN_HDL8  = 8,            /*!< 用于连接手柄8*/
    ESP_BLE_PWR_TYPE_ADV        = 9,            /*!< 用于广告*/
    ESP_BLE_PWR_TYPE_SCAN       = 10,           /*!< 用于扫描*/
    ESP_BLE_PWR_TYPE_DEFAULT    = 11,           /*!< 对于默认值，如果未设置其他，则将使用默认值*/
    ESP_BLE_PWR_TYPE_NUM        = 12,           /*!< TYPE编号*/
} esp_ble_power_type_t;

/**
 * @brief 蓝牙TX功率级别（索引），它只是与功率（dbm）相对应的索引。
 */
typedef enum {
    ESP_PWR_LVL_N27 = 0,              /*!< 对应-27dbm*/
    ESP_PWR_LVL_N24 = 1,              /*!< 对应-24dbm*/
    ESP_PWR_LVL_N21 = 2,              /*!< 对应-21dbm*/
    ESP_PWR_LVL_N18 = 3,              /*!< 对应-18dbm*/
    ESP_PWR_LVL_N15 = 4,              /*!< 对应-15dbm*/
    ESP_PWR_LVL_N12 = 5,              /*!< 对应-12dbm*/
    ESP_PWR_LVL_N9  = 6,              /*!< 对应-9dbm*/
    ESP_PWR_LVL_N6  = 7,              /*!< 对应-6dbm*/
    ESP_PWR_LVL_N3  = 8,              /*!< 对应-3dbm*/
    ESP_PWR_LVL_N0  = 9,              /*!< 对应0dbm*/
    ESP_PWR_LVL_P3  = 10,             /*!< 对应+3dbm*/
    ESP_PWR_LVL_P6  = 11,             /*!< 对应+6dbm*/
    ESP_PWR_LVL_P9  = 12,             /*!< 对应+9dbm*/
    ESP_PWR_LVL_P12 = 13,             /*!< 对应+12dbm*/
    ESP_PWR_LVL_P15 = 14,             /*!< 对应+15dbm*/
    ESP_PWR_LVL_P18 = 15,             /*!< 对应+18dbm*/
    ESP_PWR_LVL_INVALID = 0xFF,         /*!< 指示无效值*/
} esp_power_level_t;

/**
 * @brief  设置BLE TX电源连接TX电源只能在创建连接后设置。
 * @param  power_type ：tx电源的类型，可以设置广告/连接/默认等
 * @param  power_level: 与绝对值（dbm）相对应的功率电平（索引）
 * @return              ESP_OK-成功，其他-失败
 */
esp_err_t esp_ble_tx_power_set(esp_ble_power_type_t power_type, esp_power_level_t power_level);

/**
 * @brief  获取BLE TX电源连接TX电源只能在创建连接后获取。
 * @param  power_type ：tx电源的类型，可以设置广告/连接/默认等
 * @return             >=0-功率电平，<0-无效
 */
esp_power_level_t esp_ble_tx_power_get(esp_ble_power_type_t power_type);

/**
 * @brief       初始化BT控制器以分配任务和其他资源。在调用任何其他BT函数之前，此函数只能调用一次。
 * @param  cfg: BT控制器的初始配置。与以前的版本不同，“cfg”中有一种模式和一些连接配置，用于配置控制器工作模式并分配所需的资源。
 * @return      ESP_OK-成功，其他-失败
 */
esp_err_t esp_bt_controller_init(esp_bt_controller_config_t *cfg);

/**
 * @brief  取消初始化BT控制器以释放资源并删除任务。
 *
 * 在调用任何其他BT函数后，该函数只能调用一次。此函数未完全完成，无法在此函数之后调用esp_bt_controller_init。
 * @return  ESP_OK-成功，其他-失败
 */
esp_err_t esp_bt_controller_deinit(void);

/**
 * @brief 启用BT控制器。由于已知问题，您不能再次调用esp_bt_controller_enable（）来动态更改控制器模式。要更改控制器模式，请调用esp_bt_controller_disable（），然后使用新模式调用esp_bt_controller_enable（）。
 * @param mode ：要启用的模式（BLE/BT/BTDM）。为了兼容API，请保留此参数。此模式必须与esp_bt_controller_init（）的“cfg”模式相同。
 * @return       ESP_OK-成功，其他-失败
 */
esp_err_t esp_bt_controller_enable(esp_bt_mode_t mode);

/**
 * @brief  禁用BT控制器
 * @return       ESP_OK-成功，其他-失败
 */
esp_err_t esp_bt_controller_disable(void);

/**
 * @brief  获取BT控制器已初始化/已解除初始化/已启用/已禁用
 * @return 状态值
 */
esp_bt_controller_status_t esp_bt_controller_get_status(void);

uint16_t esp_bt_get_tx_buf_num(void);

/** @brief esp_vhci_host_callback用于vhci调用主机函数，以通知主机需要做什么
 */
typedef struct esp_vhci_host_callback {
    void (*notify_host_send_available)(void);               /*!< 用于通知主机可以向控制器发送数据包的回调*/
    int (*notify_host_recv)(uint8_t *data, uint16_t len);   /*!< 用于通知控制器有数据包要发送给主机的回调*/
} esp_vhci_host_callback_t;

/** @brief esp_vhci_host_check_send_available用于主动检查主机是否可以向控制器发送数据包。
 *  @return true表示准备发送，false表示无法发送数据包
 */
bool esp_vhci_host_check_send_available(void);

/** @brief esp_vhci_host_send_packet主机向控制器发送数据包
 *
 * 不应在关键节内或调度程序挂起时调用此函数。
 *
 * @param data 数据包点
 * @param len 数据包长度
 */
void esp_vhci_host_send_packet(uint8_t *data, uint16_t len);

/** @brief esp_vhci_host_register_callback注册由vhci_host_callback结构定义的vhci引用回调结构。
 * @param callback esp_vhci_host_callback类型变量
 * @return ESP_OK-成功，ESP_FAIL-失败
 */
esp_err_t esp_vhci_host_register_callback(const esp_vhci_host_callback_t *callback);

/** @brief esp_bt_controller_mem_release根据模式释放控制器内存
 *
 * 此函数将BSS、数据和控制器的其他部分释放到堆。总大小约为70k字节。
 *
 * esp_bt_controller_mem_release（mode）只能在esp_bt_controller_init（）之前或esp_bt_controller_deinit（）之后调用。
 *
 * 请注意，一旦BT控制器内存被释放，该过程将无法逆转。这意味着您无法使用此功能释放的蓝牙模式。
 *
 * 如果您的固件稍后将升级蓝牙控制器模式（BLE->BT Classic或禁用->启用），则不要调用此功能。
 *
 * 如果应用程序调用esp_bt_controller_enable（esp_bt_MODE_BLE）以仅使用BLE，则在初始化时调用esp_bt_controller_mem_release（esp_bt_MODE_CLASSIC_bt）以释放未使用的bt经典内存是安全的。
 *
 * 如果模式是ESP_BT_mode_BTM，那么调用API ESP_BT_mem_release（ESP_BT_mode_BTDM）可能会很有用，它会在内部调用ESP_BT_controller_mem_release，并将BT/BLE主机堆栈消耗的BSS和数据释放到堆。有关用法的详细信息，请参阅esp_bt_mem_release（）函数的文档
 *
 * @param mode ：要释放内存的模式
 * @return ESP_OK-成功，其他-失败
 */
esp_err_t esp_bt_controller_mem_release(esp_bt_mode_t mode);

/** @brief esp_bt_mem_release根据模式释放控制器内存和bt/BLE主机堆栈的BSS和数据部分
 *
 * 此函数首先通过内部调用esp_bt_controller_mem_release（）释放控制器内存。此外，如果模式设置为ESP_BT_mode_BTM，它还会将BT/BLE主机堆栈消耗的BSS和数据释放到堆
 *
 * 请注意，一旦BT内存被释放，该过程将无法逆转。这意味着您无法使用此功能释放的蓝牙模式。
 *
 * 如果您的固件稍后将升级蓝牙控制器模式（BLE->BT Classic或禁用->启用），则不要调用此功能。
 *
 * 如果您从未打算在当前启动周期中使用蓝牙，则可以在esp_bt_controller_init之前或esp_bt_controller_deinit之后调用esp_bt_mem_release（esp_bt_MODE_BTM）。
 *
 * 例如，如果用户仅使用蓝牙来设置WiFi配置，而在产品操作的其余部分不使用蓝牙”。在这种情况下，在接收到WiFi配置后，您可以禁用/卸载蓝牙并释放其内存。以下是针对这种情况调用的API序列：
 *
 *      esp_bluedroid_disable（）；esp_bluedroid_deinit（）；esp_bt_controller_disable（）；esp_bt_controller_deinit（）；esp_bt_mem_release（esp_bt_MODE_BTM）；
 *
 * @param mode ：要释放内存的模式
 * @return ESP_OK-成功，其他-失败
 */
esp_err_t esp_bt_mem_release(esp_bt_mode_t mode);

/**
 * @brief 启用蓝牙进入调制解调器睡眠
 *
 * 注意，在esp_bt_controller_enable（）之前不能调用此函数
 *
 * 蓝牙调制解调器睡眠目前有两种选择，一种是ORIG模式，另一种是EVED模式。EVED模式仅适用于BLE。
 *
 * 对于ORIG模式：如果设置了CONFIG_BTDM_controller_modem_sleep并选择了“ORIG模式”，则默认情况下，在控制器启动时启用蓝牙调制解调器休眠。在ORIG调制解调器睡眠模式下，如果没有要处理的事件，蓝牙控制器将关闭某些组件并不时暂停工作；并根据预定的间隔唤醒并恢复工作。它还可以使用函数“esp_bt_controller_wakeup_request”在外部请求时提前唤醒。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 */
esp_err_t esp_bt_sleep_enable(void);


/**
 * @brief 禁用蓝牙调制解调器睡眠
 *
 * 注意，在esp_bt_controller_enable（）之前不能调用此函数
 *
 * 如果调用esp_bt_sleep_disable（），蓝牙控制器将不允许进入调制解调器睡眠；
 *
 * 如果正在使用ORIG调制解调器睡眠模式，如果调用此功能，则蓝牙控制器可能不会立即唤醒，如果当时处于休眠状态。在这种情况下，esp_bt_controller_wakeup_request（）可用于缩短唤醒时间。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 */
esp_err_t esp_bt_sleep_disable(void);

/**
 * @brief 如果启用了调制解调器睡眠，则检查蓝牙控制器是否正在睡眠
 *
 * 请注意，在esp_bt_controller_enable（）之前不得调用此函数。此函数应用于调制解调器休眠的ORIG模式
 *
 * @return  如果处于调制解调器睡眠状态，则为true，否则为false
 */
bool esp_bt_controller_is_sleeping(void);

/**
 * @brief 请求控制器在睡眠模式期间从睡眠状态唤醒
 *
 * 请注意，在esp_bt_controller_enable（）之前不得调用此函数。请注意，此函数应用于调制解调器睡眠的ORIG模式。请注意：在发出此请求后，只要调制解调器睡眠已启用，蓝牙控制器可能会再次进入睡眠状态
 *
 * 分析显示，在此请求之后，从调制解调器睡眠中唤醒需要几毫秒。通常，如果使用32kHz XTAL比主XTAL需要更长的时间，因为前者作为蓝牙低功耗时钟源的频率较低。
 */
void esp_bt_controller_wakeup_request(void);

/**
 * @brief 发送或接收完成后通知蓝牙控制器任务处理事件
 *
 * 注意，在esp_bt_controller_enable（）之前不能调用此函数。此函数可以在ISR和非ISR上下文中调用
 *
 */
int esp_bt_h4tl_eif_io_event_notify(int event);

/**
 * @brief bt Wi-Fi电源域电源打开
 */
void esp_wifi_bt_power_domain_on(void);

/**
 * @brief bt Wi-Fi电源域电源关闭
 */
void esp_wifi_bt_power_domain_off(void);

#ifdef __cplusplus
}
#endif

#endif /* __ESP_BT_H__ */

