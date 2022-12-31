/*
 * 版权所有（c）2012-2017，Nordic Semiconductor ASA保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 * 2.二进制形式的再发行，除非嵌入产品中的Nordic Semiconductor ASA集成电路或该产品的软件更新，否则必须在发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 * 3.未经事先书面许可，不得使用Nordic Semiconductor ASA的名称或其贡献者的名称来支持或推广源自本软件的产品。
 *
 * 4.本软件无论是否经过修改，只能与Nordic Semiconductor ASA集成电路一起使用。
 *
 * 5.根据本许可证以二进制形式提供的任何软件不得进行反向工程、反编译、修改和/或反汇编。
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
  @添加组BLE_COMMON@{
  @defgroup ble_types通用类型和宏定义@{

  @BLE SoftDevice的常见类型和宏定义。
 */

#ifndef BLE_TYPES_H__
#define BLE_TYPES_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup BLE_TYPES_DEFINES定义
 * @{ */

/** @defgroup BLE_CONN_HANDLES BLE连接句柄
 * @{ */
#define BLE_CONN_HANDLE_INVALID 0xFFFF  /**<连接句柄无效。*/
#define BLE_CONN_HANDLE_ALL     0xFFFE  /**<适用于所有连接句柄。*/
/** @} */


/** @defgroup BLE_UUID_VALUES为BLE UUID分配的值
 * @{ */
/* 通用UUID，适用于所有服务*/
#define BLE_UUID_UNKNOWN                              0x0000 /**<保留UUID。*/
#define BLE_UUID_SERVICE_PRIMARY                      0x2800 /**<主要服务。*/
#define BLE_UUID_SERVICE_SECONDARY                    0x2801 /**<辅助服务。*/
#define BLE_UUID_SERVICE_INCLUDE                      0x2802 /**<包括。*/
#define BLE_UUID_CHARACTERISTIC                       0x2803 /**<特征。*/
#define BLE_UUID_DESCRIPTOR_CHAR_EXT_PROP             0x2900 /**<特征扩展属性描述符。*/
#define BLE_UUID_DESCRIPTOR_CHAR_USER_DESC            0x2901 /**<特征用户描述描述符。*/
#define BLE_UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG        0x2902 /**<客户端特征配置描述符。*/
#define BLE_UUID_DESCRIPTOR_SERVER_CHAR_CONFIG        0x2903 /**<服务器特征配置描述符。*/
#define BLE_UUID_DESCRIPTOR_CHAR_PRESENTATION_FORMAT  0x2904 /**<特征表示格式描述符。*/
#define BLE_UUID_DESCRIPTOR_CHAR_AGGREGATE_FORMAT     0x2905 /**<特征聚合格式描述符。*/
/* GATT特定UUID*/
#define BLE_UUID_GATT                                 0x1801 /**<通用属性配置文件。*/
#define BLE_UUID_GATT_CHARACTERISTIC_SERVICE_CHANGED  0x2A05 /**<服务更改特征。*/
/* GAP特定UUID*/
#define BLE_UUID_GAP                                  0x1800 /**<通用访问配置文件。*/
#define BLE_UUID_GAP_CHARACTERISTIC_DEVICE_NAME       0x2A00 /**<设备名称特征。*/
#define BLE_UUID_GAP_CHARACTERISTIC_APPEARANCE        0x2A01 /**<外观特征。*/
#define BLE_UUID_GAP_CHARACTERISTIC_RECONN_ADDR       0x2A03 /**<重新连接地址特征。*/
#define BLE_UUID_GAP_CHARACTERISTIC_PPCP              0x2A04 /**<外围首选连接参数特性。*/
#define BLE_UUID_GAP_CHARACTERISTIC_CAR               0x2AA6 /**<中心地址解析特性。*/
#define BLE_UUID_GAP_CHARACTERISTIC_RPA_ONLY          0x2AC9 /**<仅可解析的专用地址特征。*/
/** @} */


/** @defgroup BLE_UUID_TYPES UUID类型
 * @{ */
#define BLE_UUID_TYPE_UNKNOWN       0x00 /**<UUID类型无效。*/
#define BLE_UUID_TYPE_BLE           0x01 /**<蓝牙SIG UUID（16位）。*/
#define BLE_UUID_TYPE_VENDOR_BEGIN  0x02 /**<供应商UUID类型从此索引（128位）开始。*/
/** @} */


/** @defgroup BLE_APPERANCES蓝牙外观值
 *  @note 检索自http://developer.bluetooth.org/gatt/characteristics/Pages/CharacteristicViewer.aspx?u=org.bluetooth.characteristic.gap.appearance.xml
 * @{ */
#define BLE_APPEARANCE_UNKNOWN                                0 /**<未知。*/
#define BLE_APPEARANCE_GENERIC_PHONE                         64 /**<通用电话。*/
#define BLE_APPEARANCE_GENERIC_COMPUTER                     128 /**<通用计算机。*/
#define BLE_APPEARANCE_GENERIC_WATCH                        192 /**<通用监视。*/
#define BLE_APPEARANCE_WATCH_SPORTS_WATCH                   193 /**<手表：运动手表。*/
#define BLE_APPEARANCE_GENERIC_CLOCK                        256 /**<通用时钟。*/
#define BLE_APPEARANCE_GENERIC_DISPLAY                      320 /**<通用显示。*/
#define BLE_APPEARANCE_GENERIC_REMOTE_CONTROL               384 /**<通用远程控制。*/
#define BLE_APPEARANCE_GENERIC_EYE_GLASSES                  448 /**<普通眼镜。*/
#define BLE_APPEARANCE_GENERIC_TAG                          512 /**<通用标记。*/
#define BLE_APPEARANCE_GENERIC_KEYRING                      576 /**<通用钥匙环。*/
#define BLE_APPEARANCE_GENERIC_MEDIA_PLAYER                 640 /**<通用媒体播放器。*/
#define BLE_APPEARANCE_GENERIC_BARCODE_SCANNER              704 /**<通用条形码扫描仪。*/
#define BLE_APPEARANCE_GENERIC_THERMOMETER                  768 /**<通用温度计。*/
#define BLE_APPEARANCE_THERMOMETER_EAR                      769 /**<温度计：耳朵。*/
#define BLE_APPEARANCE_GENERIC_HEART_RATE_SENSOR            832 /**<通用心率传感器。*/
#define BLE_APPEARANCE_HEART_RATE_SENSOR_HEART_RATE_BELT    833 /**<心率传感器：心率带。*/
#define BLE_APPEARANCE_GENERIC_BLOOD_PRESSURE               896 /**<一般血压。*/
#define BLE_APPEARANCE_BLOOD_PRESSURE_ARM                   897 /**<血压：手臂。*/
#define BLE_APPEARANCE_BLOOD_PRESSURE_WRIST                 898 /**<血压：手腕。*/
#define BLE_APPEARANCE_GENERIC_HID                          960 /**<人机接口设备（HID）。*/
#define BLE_APPEARANCE_HID_KEYBOARD                         961 /**<键盘（HID子类型）。*/
#define BLE_APPEARANCE_HID_MOUSE                            962 /**<鼠标（HID子类型）。*/
#define BLE_APPEARANCE_HID_JOYSTICK                         963 /**<操纵杆（HID子类型）。*/
#define BLE_APPEARANCE_HID_GAMEPAD                          964 /**<Gamepad（HID子类型）。*/
#define BLE_APPEARANCE_HID_DIGITIZERSUBTYPE                 965 /**<数字化仪平板电脑（HID子类型）。*/
#define BLE_APPEARANCE_HID_CARD_READER                      966 /**<读卡器（HID子类型）。*/
#define BLE_APPEARANCE_HID_DIGITAL_PEN                      967 /**<数码笔（HID子类型）。*/
#define BLE_APPEARANCE_HID_BARCODE                          968 /**<条形码扫描仪（HID子类型）。*/
#define BLE_APPEARANCE_GENERIC_GLUCOSE_METER               1024 /**<通用血糖仪。*/
#define BLE_APPEARANCE_GENERIC_RUNNING_WALKING_SENSOR      1088 /**<通用跑步步行传感器。*/
#define BLE_APPEARANCE_RUNNING_WALKING_SENSOR_IN_SHOE      1089 /**<跑步行走传感器：鞋内。*/
#define BLE_APPEARANCE_RUNNING_WALKING_SENSOR_ON_SHOE      1090 /**<跑步行走传感器：鞋上。*/
#define BLE_APPEARANCE_RUNNING_WALKING_SENSOR_ON_HIP       1091 /**<跑步行走传感器：臀部。*/
#define BLE_APPEARANCE_GENERIC_CYCLING                     1152 /**<通用循环。*/
#define BLE_APPEARANCE_CYCLING_CYCLING_COMPUTER            1153 /**<骑自行车：骑电脑。*/
#define BLE_APPEARANCE_CYCLING_SPEED_SENSOR                1154 /**<循环：速度传感器。*/
#define BLE_APPEARANCE_CYCLING_CADENCE_SENSOR              1155 /**<自行车：Cadence传感器。*/
#define BLE_APPEARANCE_CYCLING_POWER_SENSOR                1156 /**<循环：功率传感器。*/
#define BLE_APPEARANCE_CYCLING_SPEED_CADENCE_SENSOR        1157 /**<自行车：速度和速度传感器。*/
#define BLE_APPEARANCE_GENERIC_PULSE_OXIMETER              3136 /**<通用脉搏血氧计。*/
#define BLE_APPEARANCE_PULSE_OXIMETER_FINGERTIP            3137 /**<指尖（脉搏血氧计亚型）。*/
#define BLE_APPEARANCE_PULSE_OXIMETER_WRIST_WORN           3138 /**<手腕磨损（脉搏血氧计亚型）。*/
#define BLE_APPEARANCE_GENERIC_WEIGHT_SCALE                3200 /**<通用体重秤。*/
#define BLE_APPEARANCE_GENERIC_OUTDOOR_SPORTS_ACT          5184 /**<一般户外运动活动。*/
#define BLE_APPEARANCE_OUTDOOR_SPORTS_ACT_LOC_DISP         5185 /**<位置显示设备（户外运动活动子类型）。*/
#define BLE_APPEARANCE_OUTDOOR_SPORTS_ACT_LOC_AND_NAV_DISP 5186 /**<位置和导航显示设备（户外运动活动子类型）。*/
#define BLE_APPEARANCE_OUTDOOR_SPORTS_ACT_LOC_POD          5187 /**<LocationPod（户外运动活动子类型）。*/
#define BLE_APPEARANCE_OUTDOOR_SPORTS_ACT_LOC_AND_NAV_POD  5188 /**<位置和导航吊舱（户外运动活动子类型）。*/
/** @} */

/** @brief 将ble_uuid_struct的.type和.uuid字段设置为指定的uuid值。*/
#define BLE_UUID_BLE_ASSIGN(instance, value) do {\
            instance.type = BLE_UUID_TYPE_BLE; \
            instance.uuid = value;} while(0)

/** @brief 将类型和uuid成员从src复制到dst ble_uuid_t指针。两个指针都必须为有效/非空。*/
#define BLE_UUID_COPY_PTR(dst, src) do {\
            (dst)->type = (src)->type; \
            (dst)->uuid = (src)->uuid;} while(0)

/** @brief 将类型和uuid成员从src复制到dst ble_uuid_t结构。*/
#define BLE_UUID_COPY_INST(dst, src) do {\
            (dst).type = (src).type; \
            (dst).uuid = (src).uuid;} while(0)

/** @brief 比较两个（有效、非空）ble_uuid_t指针的类型和uuid成员是否相等。*/
#define BLE_UUID_EQ(p_uuid1, p_uuid2) \
            (((p_uuid1)->type == (p_uuid2)->type) && ((p_uuid1)->uuid == (p_uuid2)->uuid))

/** @brief 比较两个（有效、非空）ble_uuid_t指针的类型和uuid成员的差异。*/
#define BLE_UUID_NEQ(p_uuid1, p_uuid2) \
            (((p_uuid1)->type != (p_uuid2)->type) || ((p_uuid1)->uuid != (p_uuid2)->uuid))

/** @} */

/** @addtogroup BLE_TYPES_STRUCTURES结构
 * @{ */

/** @brief 128位UUID值。*/
typedef struct
{
  uint8_t uuid128[16]; /**<Little Endian UUID字节。*/
} ble_uuid128_t;

/** @brief  蓝牙低能UUID类型，封装16位和128位UUID。*/
typedef struct
{
  uint16_t    uuid; /**<16位UUID值或128位UUID的八位字节12-13。*/
  uint8_t     type; /**<UUID类型，请参见@ref BLE_UUID_TYPES。如果类型为@ref BLE_UUID_type_UNKNOWN，则UUID的值未定义。*/
} ble_uuid_t;

/**@brief 数据结构。*/
typedef struct
{
  uint8_t     *p_data;  /**<指向提供给/来自应用程序的数据缓冲区的指针。*/
  uint16_t     len;     /**<数据缓冲区的长度，以字节为单位。*/
} ble_data_t;

/** @} */
#ifdef __cplusplus
}
#endif

#endif /* BLE_TYPES_H__ */

/**
  @} @}
*/

