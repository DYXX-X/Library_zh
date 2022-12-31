/*
 * SPDX文件版权所有文本：2010 Christian Walter
 *
 * SPDX许可证标识符：BSD-3-条款
 *
 * SPDX文件撰稿人：2016-2021 Espressif Systems（Shanghai）CO LTD
 */
/*
 * FreeModbus库：ESP32端口版权所有（C）2010 Christian Walter<cwalter@embedded-solutions.at>
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES IF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 文件：$Id:port.h，v 1.1 2010/06/06 13:07:20 wolti Exp$
 */

#ifndef PORT_COMMON_H_
#define PORT_COMMON_H_

#include "freertos/FreeRTOS.h"
#include "esp_log.h"                // 用于ESP_LOGE宏
#include "mbconfig.h"

#define INLINE                      inline
#define PR_BEGIN_EXTERN_C           extern "C" {
#define PR_END_EXTERN_C             }

#define MB_PORT_TAG                     "MB_PORT_COMMON"

#define MB_BAUD_RATE_DEFAULT            (115200)
#define MB_QUEUE_LENGTH                 (CONFIG_FMB_QUEUE_LENGTH)

#define MB_SERIAL_TASK_PRIO             (CONFIG_FMB_PORT_TASK_PRIO)
#define MB_SERIAL_TASK_STACK_SIZE       (CONFIG_FMB_PORT_TASK_STACK_SIZE)
#define MB_SERIAL_TOUT                  (3) // 3.5*8=28个刻度，TOUT=3->~24..33个刻度

// 设置传输的缓冲区大小
#define MB_SERIAL_BUF_SIZE              (CONFIG_FMB_SERIAL_BUF_SIZE)

// 串行端口实现的通用定义
#define MB_SERIAL_TX_TOUT_MS            (2200) // 最长允许帧缓冲区传输的最长时间
#define MB_SERIAL_TX_TOUT_TICKS         (pdMS_TO_TICKS(MB_SERIAL_TX_TOUT_MS)) // 传输超时
#define MB_SERIAL_RX_TOUT_MS            (1)
#define MB_SERIAL_RX_TOUT_TICKS         (pdMS_TO_TICKS(MB_SERIAL_RX_TOUT_MS)) // 接收超时

#define MB_SERIAL_RESP_LEN_MIN          (4)

// TCP端口的通用定义
#define MB_TCP_BUF_SIZE                 (256 + 7) // 必须保持完整的Modbus TCP帧。
#define MB_TCP_DEFAULT_PORT             (CONFIG_FMB_TCP_PORT_DEFAULT)
#define MB_TCP_STACK_SIZE               (CONFIG_FMB_PORT_TASK_STACK_SIZE)
#define MB_TCP_TASK_PRIO                (CONFIG_FMB_PORT_TASK_PRIO)

// Modbus堆栈任务的任务相关性
#define MB_PORT_TASK_AFFINITY           (CONFIG_FMB_PORT_TASK_AFFINITY)

#define MB_TCP_READ_TIMEOUT_MS          (100) // 读取超时（毫秒）
#define MB_TCP_READ_TIMEOUT             (pdMS_TO_TICKS(MB_TCP_READ_TIMEOUT_MS))
#define MB_TCP_SEND_TIMEOUT_MS          (500) // 发送事件超时（毫秒）
#define MB_TCP_SEND_TIMEOUT             (pdMS_TO_TICKS(MB_TCP_SEND_TIMEOUT_MS))
#define MB_TCP_PORT_MAX_CONN            (CONFIG_FMB_TCP_PORT_MAX_CONN)

#define MB_TCP_FRAME_LOG_BUFSIZE        (256)

#define MB_PORT_HAS_CLOSE               (1) // 定义在销毁时显式关闭端口

// 定义每1mS的计时器重新加载次数
#define MB_TIMER_TICS_PER_MS            (20UL)

#define MB_TCP_DEBUG                    (LOG_LOCAL_LEVEL >= ESP_LOG_DEBUG) // 在TCP模块中启用旧版调试输出。

#define MB_TCP_GET_FIELD(buffer, field) ((USHORT)((buffer[field] << 8U) | buffer[field + 1]))

#define MB_PORT_CHECK(a, ret_val, str, ...) \
    if (!(a)) { \
        ESP_LOGE(MB_PORT_TAG, "%s(%u): " str, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
        return ret_val; \
    }

#ifdef __cplusplus
PR_BEGIN_EXTERN_C
#endif /* __cplusplus公司*/

#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif

typedef char    BOOL;

typedef unsigned char UCHAR;
typedef char    CHAR;

typedef unsigned short USHORT;
typedef short   SHORT;

typedef unsigned long ULONG;
typedef long    LONG;

#if MB_TCP_DEBUG
typedef enum
{
    MB_LOG_DEBUG,
    MB_LOG_INFO,
    MB_LOG_WARN,
    MB_LOG_ERROR
} eMBPortLogLevel;
#endif

typedef enum
{
    MB_PROTO_TCP,
    MB_PROTO_UDP,
} eMBPortProto;

typedef enum {
    MB_PORT_IPV4 = 0,                     /*!< TCP IPV4寻址*/
    MB_PORT_IPV6 = 1                      /*!< TCP IPV6寻址*/
} eMBPortIpVer;

void vMBPortEnterCritical(void);
void vMBPortExitCritical(void);

#define ENTER_CRITICAL_SECTION( ) { ESP_EARLY_LOGD(MB_PORT_TAG,"%s: Port enter critical.", __func__); \
                                    vMBPortEnterCritical(); }

#define EXIT_CRITICAL_SECTION( )  { vMBPortExitCritical(); \
                                    ESP_EARLY_LOGD(MB_PORT_TAG,"%s: Port exit critical", __func__); }

#define MB_PORT_CHECK_EVENT( event, mask ) ( event & mask )
#define MB_PORT_CLEAR_EVENT( event, mask ) do { event &= ~mask; } while(0)

#define MB_PORT_PARITY_GET(parity) ((parity != UART_PARITY_DISABLE) ? \
                                        ((parity == UART_PARITY_ODD) ? MB_PAR_ODD : MB_PAR_EVEN) : MB_PAR_NONE)

// 传统Modbus日志记录功能
#if MB_TCP_DEBUG
void vMBPortLog( eMBPortLogLevel eLevel, const CHAR * szModule,
                    const CHAR * szFmt, ... );
void prvvMBTCPLogFrame( const CHAR * pucMsg, UCHAR * pucFrame, USHORT usFrameLen );
#endif

void vMBPortSetMode( UCHAR ucMode );
UCHAR ucMBPortGetMode( void );

#ifdef __cplusplus
PR_END_EXTERN_C
#endif /* __cplusplus公司*/

#endif /* PORT_COMMON_H_ */

