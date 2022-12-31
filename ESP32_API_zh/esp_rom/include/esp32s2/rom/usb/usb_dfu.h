/***************************************************************************
 * 版权所有（c）20152016 Intel Corporation。版权所有（c）2017 PHYTEC Messtechnik GmbH
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * *源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。未经事先书面许可，不得使用“英特尔公司”的名称或其贡献者的名称来支持或推广源自此软件的产品。
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ***************************************************************************/

/**
 * @file
 * @brief USB设备固件升级（DFU）公共标头
 *
 * 标题遵循1.1版设备固件升级的设备类规范
 */

#pragma once

#include <stdint.h>
#include <stddef.h>
#include "usb_device.h"

#ifdef __cplusplus
extern "C" {
#endif

/**DFU类子类*/
#define DFU_SUBCLASS            0x01

/**DFU类运行时协议*/
#define DFU_RT_PROTOCOL         0x01

/**DFU类DFU模式协议*/
#define DFU_MODE_PROTOCOL       0x02

/**
 * @brief DFU类特定请求
 */
#define DFU_DETACH          0x00
#define DFU_DNLOAD          0x01
#define DFU_UPLOAD          0x02
#define DFU_GETSTATUS           0x03
#define DFU_CLRSTATUS           0x04
#define DFU_GETSTATE            0x05
#define DFU_ABORT           0x06

/**DFU FUNCTIONAL描述符类型*/
#define DFU_FUNC_DESC           0x21

/**DFU属性DFU功能描述符*/
#define DFU_ATTR_WILL_DETACH        0x08
#define DFU_ATTR_MANIFESTATION_TOLERANT 0x04
#define DFU_ATTR_CAN_UPLOAD     0x02
#define DFU_ATTR_CAN_DNLOAD     0x01

/**DFU规范发布*/
#define DFU_VERSION         0x0110

/**运行时函数描述符*/
struct dfu_runtime_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bmAttributes;
    uint16_t wDetachTimeOut;
    uint16_t wTransferSize;
    uint16_t bcdDFUVersion;
} __packed;

/**bDFU_GETSTATUS响应的状态值*/
enum dfu_status {
    statusOK,
    errTARGET,
    errFILE,
    errWRITE,
    errERASE,
    errCHECK_ERASED,
    errPROG,
    errVERIFY,
    errADDRESS,
    errNOTDONE,
    errFIRMWARE,
    errVENDOR,
    errUSB,
    errPOR,
    errUNKNOWN,
    errSTALLEDPKT
};

/**bDFU_GETSTATUS响应的状态值*/
enum dfu_state {
    appIDLE,
    appDETACH,
    dfuIDLE,
    dfuDNLOAD_SYNC,
    dfuDNBUSY,
    dfuDNLOAD_IDLE,
    dfuMANIFEST_SYNC,
    dfuMANIFEST,
    dfuMANIFEST_WAIT_RST,
    dfuUPLOAD_IDLE,
    dfuERROR,
};

/*
 这些回调是公开的，因此ACM驱动程序可以调用它们来处理到DFU的切换。
*/

int dfu_class_handle_req(struct usb_setup_packet *pSetup,
                         int32_t *data_len, uint8_t **data);
void dfu_status_cb(enum usb_dc_status_code status, uint8_t *param);
int usb_dfu_init(void);
int dfu_custom_handle_req(struct usb_setup_packet *pSetup,
                          int32_t *data_len, uint8_t **data);


typedef void(*usb_dfu_detach_routine_t)(int delay);
void usb_dfu_set_detach_cb(usb_dfu_detach_routine_t cb);


#ifdef __cplusplus
}
#endif

