/**
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_SVC_DIS_
#define H_BLE_SVC_DIS_

/**
 * 例子：
 *
 *    char firmware_revision[20]=“？.？.？”；结构image_version iv；如果（！imgr_my_version（&iv））｛snprintf（firmware_revision，sizeof（firmware _revision），“%u.%u.%u”，iv.iv_major，iv.iv minor，iv.iv-revision）；｝ble_svc_dis_manufacturer_name_set（“MyNewt”）；ble_svc_dis_firmware_revision_set（固件_revision）；
 *
 */

#define BLE_SVC_DIS_UUID16					0x180A
#define BLE_SVC_DIS_CHR_UUID16_SYSTEM_ID			0x2A23
#define BLE_SVC_DIS_CHR_UUID16_MODEL_NUMBER			0x2A24
#define BLE_SVC_DIS_CHR_UUID16_SERIAL_NUMBER			0x2A25
#define BLE_SVC_DIS_CHR_UUID16_FIRMWARE_REVISION 		0x2A26
#define BLE_SVC_DIS_CHR_UUID16_HARDWARE_REVISION 		0x2A27
#define BLE_SVC_DIS_CHR_UUID16_SOFTWARE_REVISION 		0x2A28
#define BLE_SVC_DIS_CHR_UUID16_MANUFACTURER_NAME		0x2A29

/**
 * 主要特征的结构保存数据
 */
struct ble_svc_dis_data {
    /**
     * 型号。表示设备供应商分配的型号。
     */
    const char *model_number;
    /**
     * 序列号。表示设备特定实例的序列号。
     */
    const char *serial_number;
    /**
     * 固件版本。表示设备内固件的固件版本。
     */
    const char *firmware_revision;
    /**
     * 硬件版本。表示设备内硬件的硬件版本。
     */
    const char *hardware_revision;
    /**
     * 软件版本。表示设备内软件的软件版本。
     */
    const char *software_revision;
    /**
     * 制造商名称。表示设备制造商的名称。
     */
    const char *manufacturer_name;
    /**
     * 系统ID表示设备的系统ID。
     */
    const char *system_id;
};

/**
 * 主要特征的可变保持数据。
 */
extern struct ble_svc_dis_data ble_svc_dis_data;

/**
 * 服务初始化。在包初始化期间自动调用。
 */
void ble_svc_dis_init(void);

const char *ble_svc_dis_model_number(void);
int ble_svc_dis_model_number_set(const char *value);
const char *ble_svc_dis_serial_number(void);
int ble_svc_dis_serial_number_set(const char *value);
const char *ble_svc_dis_firmware_revision(void);
int ble_svc_dis_firmware_revision_set(const char *value);
const char *ble_svc_dis_hardware_revision(void);
int ble_svc_dis_hardware_revision_set(const char *value);
const char *ble_svc_dis_software_revision(void);
int ble_svc_dis_software_revision_set(const char *value);
const char *ble_svc_dis_manufacturer_name(void);
int ble_svc_dis_manufacturer_name_set(const char *value);
const char *ble_svc_dis_system_id(void);
int ble_svc_dis_system_id_set(const char *value);

#endif

