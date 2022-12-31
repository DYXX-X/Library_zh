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

#ifdef CONFIG_BT_ENABLED

#define SOC_MEM_BT_DATA_START               0x3ffae6e0
#define SOC_MEM_BT_DATA_END                 0x3ffaff10
#define SOC_MEM_BT_EM_START                 0x3ffb0000
#define SOC_MEM_BT_EM_END                   0x3ffb7cd8
#define SOC_MEM_BT_EM_BTDM0_START           0x3ffb0000
#define SOC_MEM_BT_EM_BTDM0_END             0x3ffb09a8
#define SOC_MEM_BT_EM_BLE_START             0x3ffb09a8
#define SOC_MEM_BT_EM_BLE_END               0x3ffb1ddc
#define SOC_MEM_BT_EM_BTDM1_START           0x3ffb1ddc
#define SOC_MEM_BT_EM_BTDM1_END             0x3ffb2730
#define SOC_MEM_BT_EM_BREDR_START           0x3ffb2730
#define SOC_MEM_BT_EM_BREDR_NO_SYNC_END     0x3ffb6388  //不使用同步连接支持进行计算
#define SOC_MEM_BT_EM_BREDR_END             0x3ffb7cd8  //使用同步连接支持进行计算
#define SOC_MEM_BT_EM_SYNC0_START           0x3ffb6388
#define SOC_MEM_BT_EM_SYNC0_END             0x3ffb6bf8
#define SOC_MEM_BT_EM_SYNC1_START           0x3ffb6bf8
#define SOC_MEM_BT_EM_SYNC1_END             0x3ffb7468
#define SOC_MEM_BT_EM_SYNC2_START           0x3ffb7468
#define SOC_MEM_BT_EM_SYNC2_END             0x3ffb7cd8
#define SOC_MEM_BT_BSS_START                0x3ffb8000
#define SOC_MEM_BT_BSS_END                  0x3ffb9a20
#define SOC_MEM_BT_MISC_START               0x3ffbdb28
#define SOC_MEM_BT_MISC_END                 0x3ffbdb5c

#define SOC_MEM_BT_EM_PER_SYNC_SIZE         0x870

#define SOC_MEM_BT_EM_BREDR_REAL_END        (SOC_MEM_BT_EM_BREDR_NO_SYNC_END + CONFIG_BTDM_CTRL_BR_EDR_MAX_SYNC_CONN_EFF * SOC_MEM_BT_EM_PER_SYNC_SIZE)

#endif //CONFIG_BT_ENABLED

#define ESP_BT_CONTROLLER_CONFIG_MAGIC_VAL  0x20200622

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
 * @brief BLE睡眠时钟精度（SCA），esp_bt_controller_config_t中BLE_SCA字段的值，当前仅支持esp_BLE_SCA_500PPM和esp_BLE_StCA_250PPM
 */
enum {
    ESP_BLE_SCA_500PPM     = 0,   /*!< 500ppm时的BLE SCA*/
    ESP_BLE_SCA_250PPM,           /*!< 250ppm时的BLE SCA*/
    ESP_BLE_SCA_150PPM,           /*!< 150 ppm时的BLE SCA*/
    ESP_BLE_SCA_100PPM,           /*!< 100ppm时的BLE SCA*/
    ESP_BLE_SCA_75PPM,            /*!< 75ppm时的BLE SCA*/
    ESP_BLE_SCA_50PPM,            /*!< 50ppm时的BLE SCA*/
    ESP_BLE_SCA_30PPM,            /*!< 30ppm时的BLE SCA*/
    ESP_BLE_SCA_20PPM,            /*!< 20ppm时的BLE SCA*/
};

#ifdef CONFIG_BT_ENABLED
/* 在扫描时，如果控制器中的可用内存值小于SCAN_SEND_ADV_RESERVED_SIZE，则将丢弃ADV数据包，直到内存恢复。*/
#define SCAN_SEND_ADV_RESERVED_SIZE        1000
/* 在adv丢失时启用控制器日志调试*/
#define CONTROLLER_ADV_LOST_DEBUG_BIT      (0<<0)

#ifdef CONFIG_BTDM_CTRL_HCI_UART_NO
#define BT_HCI_UART_NO_DEFAULT                      CONFIG_BTDM_CTRL_HCI_UART_NO
#else
#define BT_HCI_UART_NO_DEFAULT                      1
#endif /* BT_HCI_UART_NO_DEFAULT */

#ifdef CONFIG_BTDM_CTRL_HCI_UART_BAUDRATE
#define BT_HCI_UART_BAUDRATE_DEFAULT                CONFIG_BTDM_CTRL_HCI_UART_BAUDRATE
#else
#define BT_HCI_UART_BAUDRATE_DEFAULT                921600
#endif /* BT_HCI_UART_BAUDRATE_DEFAULT */

#ifdef CONFIG_BTDM_SCAN_DUPL_TYPE
#define SCAN_DUPLICATE_TYPE_VALUE  CONFIG_BTDM_SCAN_DUPL_TYPE
#else
#define SCAN_DUPLICATE_TYPE_VALUE  0
#endif

/* 正常adv缓存大小*/
#ifdef CONFIG_BTDM_SCAN_DUPL_CACHE_SIZE
#define NORMAL_SCAN_DUPLICATE_CACHE_SIZE            CONFIG_BTDM_SCAN_DUPL_CACHE_SIZE
#else
#define NORMAL_SCAN_DUPLICATE_CACHE_SIZE            20
#endif

#ifndef CONFIG_BTDM_BLE_MESH_SCAN_DUPL_EN
#define CONFIG_BTDM_BLE_MESH_SCAN_DUPL_EN FALSE
#endif

#define SCAN_DUPLICATE_MODE_NORMAL_ADV_ONLY         0
#define SCAN_DUPLICATE_MODE_NORMAL_ADV_MESH_ADV     1

#if CONFIG_BTDM_BLE_MESH_SCAN_DUPL_EN
    #define SCAN_DUPLICATE_MODE                     SCAN_DUPLICATE_MODE_NORMAL_ADV_MESH_ADV
    #ifdef CONFIG_BTDM_MESH_DUPL_SCAN_CACHE_SIZE
    #define MESH_DUPLICATE_SCAN_CACHE_SIZE          CONFIG_BTDM_MESH_DUPL_SCAN_CACHE_SIZE
    #else
    #define MESH_DUPLICATE_SCAN_CACHE_SIZE          50
    #endif
#else
    #define SCAN_DUPLICATE_MODE SCAN_DUPLICATE_MODE_NORMAL_ADV_ONLY
    #define MESH_DUPLICATE_SCAN_CACHE_SIZE          0
#endif

#if defined(CONFIG_BTDM_CTRL_MODE_BLE_ONLY)
#define BTDM_CONTROLLER_MODE_EFF                    ESP_BT_MODE_BLE
#elif defined(CONFIG_BTDM_CTRL_MODE_BR_EDR_ONLY)
#define BTDM_CONTROLLER_MODE_EFF                    ESP_BT_MODE_CLASSIC_BT
#else
#define BTDM_CONTROLLER_MODE_EFF                    ESP_BT_MODE_BTDM
#endif

#ifdef CONFIG_BTDM_CTRL_AUTO_LATENCY_EFF
#define BTDM_CTRL_AUTO_LATENCY_EFF CONFIG_BTDM_CTRL_AUTO_LATENCY_EFF
#else
#define BTDM_CTRL_AUTO_LATENCY_EFF false
#endif

#ifdef CONFIG_BTDM_CTRL_HLI
#define BTDM_CTRL_HLI CONFIG_BTDM_CTRL_HLI
#else
#define BTDM_CTRL_HLI false
#endif

#ifdef CONFIG_BTDM_CTRL_LEGACY_AUTH_VENDOR_EVT_EFF
#define BTDM_CTRL_LEGACY_AUTH_VENDOR_EVT_EFF CONFIG_BTDM_CTRL_LEGACY_AUTH_VENDOR_EVT_EFF
#else
#define BTDM_CTRL_LEGACY_AUTH_VENDOR_EVT_EFF false
#endif

#define BTDM_CONTROLLER_BLE_MAX_CONN_LIMIT          9   //最大BLE连接限制
#define BTDM_CONTROLLER_BR_EDR_MAX_ACL_CONN_LIMIT   7   //最大ACL连接限制
#define BTDM_CONTROLLER_BR_EDR_MAX_SYNC_CONN_LIMIT  3   //最大SCO/eSCO连接限制

#define BTDM_CONTROLLER_SCO_DATA_PATH_HCI           0   // SCO数据被路由到HCI
#define BTDM_CONTROLLER_SCO_DATA_PATH_PCM           1   // SCO数据路径为PCM

#define BT_CONTROLLER_INIT_CONFIG_DEFAULT() {                              \
    .controller_task_stack_size = ESP_TASK_BT_CONTROLLER_STACK,            \
    .controller_task_prio = ESP_TASK_BT_CONTROLLER_PRIO,                   \
    .hci_uart_no = BT_HCI_UART_NO_DEFAULT,                                 \
    .hci_uart_baudrate = BT_HCI_UART_BAUDRATE_DEFAULT,                     \
    .scan_duplicate_mode = SCAN_DUPLICATE_MODE,                            \
    .scan_duplicate_type = SCAN_DUPLICATE_TYPE_VALUE,                      \
    .normal_adv_size = NORMAL_SCAN_DUPLICATE_CACHE_SIZE,                   \
    .mesh_adv_size = MESH_DUPLICATE_SCAN_CACHE_SIZE,                       \
    .send_adv_reserved_size = SCAN_SEND_ADV_RESERVED_SIZE,                 \
    .controller_debug_flag = CONTROLLER_ADV_LOST_DEBUG_BIT,                \
    .mode = BTDM_CONTROLLER_MODE_EFF,                                      \
    .ble_max_conn = CONFIG_BTDM_CTRL_BLE_MAX_CONN_EFF,                     \
    .bt_max_acl_conn = CONFIG_BTDM_CTRL_BR_EDR_MAX_ACL_CONN_EFF,           \
    .bt_sco_datapath = CONFIG_BTDM_CTRL_BR_EDR_SCO_DATA_PATH_EFF,          \
    .auto_latency = BTDM_CTRL_AUTO_LATENCY_EFF,                            \
    .bt_legacy_auth_vs_evt = BTDM_CTRL_LEGACY_AUTH_VENDOR_EVT_EFF,         \
    .bt_max_sync_conn = CONFIG_BTDM_CTRL_BR_EDR_MAX_SYNC_CONN_EFF,         \
    .ble_sca = CONFIG_BTDM_BLE_SLEEP_CLOCK_ACCURACY_INDEX_EFF,             \
    .pcm_role = CONFIG_BTDM_CTRL_PCM_ROLE_EFF,                             \
    .pcm_polar = CONFIG_BTDM_CTRL_PCM_POLAR_EFF,                           \
    .hli = BTDM_CTRL_HLI,                                                  \
    .magic = ESP_BT_CONTROLLER_CONFIG_MAGIC_VAL,                           \
};

#else
#define BT_CONTROLLER_INIT_CONFIG_DEFAULT() {0}; _Static_assert(0, "please enable bluetooth in menuconfig to use bt.h");
#endif

/**
 * @brief 控制器配置选项，取决于配置掩码。配置掩码指示启用了哪些功能，这意味着配置掩码启用了某些功能的某些选项或参数。
 */
typedef struct {
    /*
     * 调用esp_bt_controller_init（）时，可以在运行时配置以下参数
     */
    uint16_t controller_task_stack_size;    /*!< 蓝牙控制器任务堆栈大小*/
    uint8_t controller_task_prio;           /*!< 蓝牙控制器任务优先级*/
    uint8_t hci_uart_no;                    /*!< 如果使用UART1/2作为HCI IO接口，请指示UART编号*/
    uint32_t hci_uart_baudrate;             /*!< 如果使用UART1/2作为HCI IO接口，请指示UART波特率*/
    uint8_t scan_duplicate_mode;            /*!< 扫描复制模式*/
    uint8_t scan_duplicate_type;            /*!< 扫描重复类型*/
    uint16_t normal_adv_size;               /*!< 扫描副本的正常adv大小*/
    uint16_t mesh_adv_size;                 /*!< 扫描副本的网格adv大小*/
    uint16_t send_adv_reserved_size;        /*!< 控制器最小内存值*/
    uint32_t  controller_debug_flag;        /*!< 控制器调试日志标志*/
    uint8_t mode;                           /*!< 控制器模式：BR/EDR、BLE或双模式*/
    uint8_t ble_max_conn;                   /*!< BLE最大连接数*/
    uint8_t bt_max_acl_conn;                /*!< BR/EDR最大ACL连接数*/
    uint8_t bt_sco_datapath;                /*!< SCO数据路径，即HCI或PCM模块*/
    bool auto_latency;                      /*!< BLE自动延迟，用于增强经典BT性能*/
    bool bt_legacy_auth_vs_evt;             /*!< BR/EDR保护免受BIAS攻击所需的传统身份验证完成事件*/
    /*
     * 调用esp_bt_controller_init（）时，无法在运行时配置以下参数。它将被menuconfig或宏中的常量值覆盖。因此，在esp_bt_controller_init（）时不要修改值
     */
    uint8_t bt_max_sync_conn;               /*!< BR/EDR最大ACL连接数。在menuconfig中生效*/
    uint8_t ble_sca;                        /*!< BLE低功率晶体精度指数*/
    uint8_t pcm_role;                       /*!< PCM角色（主控和从控）*/
    uint8_t pcm_polar;                      /*!< PCM极性触发（下降时钟边缘和上升时钟边缘）*/
    bool hli;                               /*!< 是否使用高级中断*/
    uint32_t magic;                         /*!< 魔术数字*/
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
    ESP_PWR_LVL_N12 = 0,                /*!< 对应-12dbm*/
    ESP_PWR_LVL_N9  = 1,                /*!< 对应-9dbm*/
    ESP_PWR_LVL_N6  = 2,                /*!< 对应-6dbm*/
    ESP_PWR_LVL_N3  = 3,                /*!< 对应-3dbm*/
    ESP_PWR_LVL_N0  = 4,                /*!< 对应0dbm*/
    ESP_PWR_LVL_P3  = 5,                /*!< 对应+3dbm*/
    ESP_PWR_LVL_P6  = 6,                /*!< 对应+6dbm*/
    ESP_PWR_LVL_P9  = 7,                /*!< 对应+9dbm*/
    ESP_PWR_LVL_N14 = ESP_PWR_LVL_N12,  /*!< 向后兼容！设置为-14dbm实际上会导致-12dbm*/
    ESP_PWR_LVL_N11 = ESP_PWR_LVL_N9,   /*!< 向后兼容！设置为-11dbm实际上会导致-9dbm*/
    ESP_PWR_LVL_N8  = ESP_PWR_LVL_N6,   /*!< 向后兼容！设置为-8dbm实际上会导致-6dbm*/
    ESP_PWR_LVL_N5  = ESP_PWR_LVL_N3,   /*!< 向后兼容！设置为-5dbm实际上会导致-3dbm*/
    ESP_PWR_LVL_N2  = ESP_PWR_LVL_N0,   /*!< 向后兼容！设置为-2dbm实际上会导致0dbm*/
    ESP_PWR_LVL_P1  = ESP_PWR_LVL_P3,   /*!< 向后兼容！设置为+1dbm实际上会导致+3dbm*/
    ESP_PWR_LVL_P4  = ESP_PWR_LVL_P6,   /*!< 向后兼容！设置为+4dbm实际上将导致+6dbm*/
    ESP_PWR_LVL_P7  = ESP_PWR_LVL_P9,   /*!< 向后兼容！设置为+7dbm实际上将导致+9dbm*/
} esp_power_level_t;

/**
 * @brief 蓝牙音频数据传输路径
 */
typedef enum {
    ESP_SCO_DATA_PATH_HCI = 0,            /*!< HCI传输数据*/
    ESP_SCO_DATA_PATH_PCM = 1,            /*!< PCM接口上的数据*/
} esp_sco_data_path_t;

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
 * @brief  设置BR/EDR TX功率BR/EDR功率控制将使用最小值和最大值范围内的功率。功率级别将影响全局BR/EDR TX功率，如inquire、page、connection等。请在esp_bt_controller_enable之后，在任何导致RF执行TX的函数之前调用该函数。因此，您可以在执行查找、配置文件初始化等操作之前调用该功能。例如，如果您希望BR/EDR使用新的TX功率执行inquire，则应在inquire之前调用此函数。换句话说，如果在BR/EDR处于查询（ING）状态时调用此函数，请在调用此函数后再次进行查询。默认最小功率电平为ESP_PWR_LVL_N0，最大功率电平为ESP _PWR_LVH_P3。
 * @param  min_power_level: 最小功率电平
 * @param  max_power_level: 最大功率电平
 * @return              ESP_OK-成功，其他-失败
 */
esp_err_t esp_bredr_tx_power_set(esp_power_level_t min_power_level, esp_power_level_t max_power_level);

/**
 * @brief  获取BR/EDR TX功率如果参数不为NULL，则存储相应的值。
 * @param  min_power_level: 最小功率电平
 * @param  max_power_level: 最大功率电平
 * @return              ESP_OK-成功，其他-失败
 */
esp_err_t esp_bredr_tx_power_get(esp_power_level_t *min_power_level, esp_power_level_t *max_power_level);

/**
 * @brief  设置默认SCO数据路径应在控制器启用后和（e）建立SCO链路之前调用
 * @param  data_path: SCO数据路径
 * @return              ESP_OK-成功，其他-失败
 */
esp_err_t esp_bredr_sco_datapath_set(esp_sco_data_path_t data_path);

/**
 * @brief       初始化BT控制器以分配任务和其他资源。在调用任何其他BT函数之前，此函数只能调用一次。
 * @param  cfg: BT控制器的初始配置。与以前的版本不同，“cfg”中有一种模式和一些连接配置，用于配置控制器工作模式并分配所需的资源。
 * @return      ESP_OK-成功，其他-失败
 */
esp_err_t esp_bt_controller_init(esp_bt_controller_config_t *cfg);

/**
 * @brief  取消初始化BT控制器以释放资源并删除任务。
 *
 * 在调用任何其他BT函数后，该函数只能调用一次。
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
 * @note 对于NimBLE主机，要将BSS和数据内存释放到堆，需要将模式设置为ESP_BT_mode_BTM，因为控制器是双模式。
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
 * 对于ORIG模式：如果设置了CONFIG_CTRL_BTDM_modem_sleep并选择了“ORIG模式”，则默认情况下在控制器启动时启用蓝牙调制解调器休眠。在ORIG调制解调器睡眠模式下，如果没有要处理的事件，蓝牙控制器将关闭某些组件并不时暂停工作；并根据预定的间隔唤醒并恢复工作。它还可以使用函数“esp_bt_controller_wakeup_request”在外部请求时提前唤醒。
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
 * @brief 手动清除扫描重复列表
 *
 * 请注意，当达到筛选器中设备的最大数量时，将自动清除扫描重复列表。可以在menuconfig中配置筛选器中的设备数量。
 *
 * @note 此函数名拼写错误，将在5.x版本中修复。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 */
esp_err_t esp_ble_scan_dupilcate_list_flush(void);

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

