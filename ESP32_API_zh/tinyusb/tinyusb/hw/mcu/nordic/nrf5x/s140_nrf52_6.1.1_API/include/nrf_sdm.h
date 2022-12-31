/*
 * 版权所有（c）2015-2018，Nordic Semiconductor ASA保留所有权利。
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
  @defgroup nrf_sdm_api软设备管理器api@{

  @SoftDevice管理的简短API。

*/

#ifndef NRF_SDM_H__
#define NRF_SDM_H__

#include <stdint.h>
#include "nrf.h"
#include "nrf_svc.h"
#include "nrf_error.h"
#include "nrf_error_sdm.h"
#include "nrf_soc.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup NRF_SDM_DEFINES定义
 * @{ */
#ifdef NRFSOC_DOXYGEN
///在nrf_mbr.h中声明
#define MBR_SIZE 0
#warning test
#endif

/** @brief 随此头文件分发的SoftDevice二进制文件的主要版本。*/
#define SD_MAJOR_VERSION  (6)

/** @brief 随此头文件分发的SoftDevice二进制文件的次要版本。*/
#define SD_MINOR_VERSION  (1)

/** @brief 随此头文件分发的SoftDevice二进制文件的错误修复版本。*/
#define SD_BUGFIX_VERSION (1)

/** @brief 此固件的SoftDevice变体。*/
#define SD_VARIANT_ID 140

/** @brief 分发此头文件的SoftDevice二进制文件的完整版本号，格式为Mmmbbb的十进制数字，其中：
 *           -M是主要版本（一个或多个数字）
 *           -mmm是次要版本（三位数）-bbb是错误修复版本（三位）。*/
#define SD_VERSION (SD_MAJOR_VERSION * 1000000 + SD_MINOR_VERSION * 1000 + SD_BUGFIX_VERSION)

/** @brief SoftDevice Manager SVC基本编号。*/
#define SDM_SVC_BASE 0x10

/** @brief SoftDevice唯一字符串大小（字节）。*/
#define SD_UNIQUE_STR_SIZE 20

/** @brief 信息字段无效。当信息字段不存在时返回。*/
#define SDM_INFO_FIELD_INVALID (0)

/** @brief 将SoftDevice信息结构位置（地址）定义为与SoftDevice开始位置的偏移量（无MBR）*/
#define SOFTDEVICE_INFO_STRUCT_OFFSET (0x2000)

/** @brief 定义SoftDevice安装在MBR正上方时的绝对SoftDevice信息结构位置（地址）（通常情况下）。*/
#define SOFTDEVICE_INFO_STRUCT_ADDRESS (SOFTDEVICE_INFO_STRUCT_OFFSET + MBR_SIZE)

/** @brief 定义SoftDevice信息结构大小值相对于SoftDevice基地址的偏移量。大小值的类型为uint8_t。*/
#define SD_INFO_STRUCT_SIZE_OFFSET (SOFTDEVICE_INFO_STRUCT_OFFSET)

/** @brief 定义SoftDevice大小值相对于SoftDevice基地址的偏移量。大小值的类型为uint32_t。*/
#define SD_SIZE_OFFSET (SOFTDEVICE_INFO_STRUCT_OFFSET + 0x08)

/** @brief 定义FWID值相对于SoftDevice基地址的偏移量。FWID值的类型为uint16_t。*/
#define SD_FWID_OFFSET (SOFTDEVICE_INFO_STRUCT_OFFSET + 0x0C)

/** @brief 定义SoftDevice ID相对于SoftDevice基地址的偏移量。ID的类型为uint32_t。*/
#define SD_ID_OFFSET (SOFTDEVICE_INFO_STRUCT_OFFSET + 0x10)

/** @brief 定义SoftDevice版本相对于SoftDevice基地址的偏移量，格式与@ref SD_version相同，存储为uint32_t。*/
#define SD_VERSION_OFFSET (SOFTDEVICE_INFO_STRUCT_OFFSET + 0x14)

/** @brief 定义SoftDevice唯一字符串相对于SoftDevice基地址的偏移量。SD_UNIQUE_STR存储为uint8_t数组。数组的大小为@ref SD_UNIQUE_STR_size。
 */
#define SD_UNIQUE_STR_OFFSET (SOFTDEVICE_INFO_STRUCT_OFFSET + 0x18)

/** @brief 定义用于检索实际SoftDevice信息结构大小值的宏
 *         从给定的基地址。当SoftDevice安装在MBR的正上方时（通常情况下），使用@ref MBR_SIZE作为参数。*/
#define SD_INFO_STRUCT_SIZE_GET(baseaddr) (*((uint8_t *) ((baseaddr) + SD_INFO_STRUCT_SIZE_OFFSET)))

/** @brief 定义用于从给定基础检索实际SoftDevice大小值的宏
 *         住址当SoftDevice安装在MBR的正上方时（通常情况下），使用@ref MBR_SIZE作为参数。*/
#define SD_SIZE_GET(baseaddr) (*((uint32_t *) ((baseaddr) + SD_SIZE_OFFSET)))

/** @brief 定义SoftDevice使用的闪存量。
 *         Add @ref 当SoftDevice安装在MBR的正上方时（通常情况下），MBR_SIZE查找第一个可用闪存地址。
 */
#define SD_FLASH_SIZE 0x25000

/** @brief 定义用于从给定基地址检索实际FWID值的宏。使用
 *         @当SoftDevice安装在MBR的正上方时（通常情况下），将MBR_SIZE作为参数。*/
#define SD_FWID_GET(baseaddr) (*((uint16_t *) ((baseaddr) + SD_FWID_OFFSET)))

/** @brief 定义用于从给定基地址检索实际SoftDevice ID的宏。使用
 *         @当SoftDevice安装在MBR的正上方时（通常情况下），将MBR_SIZE作为参数。*/
#define SD_ID_GET(baseaddr) ((SD_INFO_STRUCT_SIZE_GET(baseaddr) > (SD_ID_OFFSET - SOFTDEVICE_INFO_STRUCT_OFFSET)) \
        ? (*((uint32_t *) ((baseaddr) + SD_ID_OFFSET))) : SDM_INFO_FIELD_INVALID)

/** @brief 定义用于从给定基地址检索实际SoftDevice版本的宏。
 *         当SoftDevice安装在MBR的正上方时（通常情况下），使用@ref MBR_SIZE作为参数。*/
#define SD_VERSION_GET(baseaddr) ((SD_INFO_STRUCT_SIZE_GET(baseaddr) > (SD_VERSION_OFFSET - SOFTDEVICE_INFO_STRUCT_OFFSET)) \
        ? (*((uint32_t *) ((baseaddr) + SD_VERSION_OFFSET))) : SDM_INFO_FIELD_INVALID)

/** @brief 定义一个宏，用于基于给定的基地址检索SoftDevice唯一str的地址。
 *         当SoftDevice安装在MBR的正上方时（通常情况下），使用@ref MBR_SIZE作为参数。*/
#define SD_UNIQUE_STR_ADDR_GET(baseaddr) ((SD_INFO_STRUCT_SIZE_GET(baseaddr) > (SD_UNIQUE_STR_OFFSET - SOFTDEVICE_INFO_STRUCT_OFFSET)) \
        ? (((uint8_t *) ((baseaddr) + SD_UNIQUE_STR_OFFSET))) : SDM_INFO_FIELD_INVALID)

/**@defgroup NRF_FAULT_ID_RANGES故障ID范围
 * @{ */
#define NRF_FAULT_ID_SD_RANGE_START     0x00000000            /**<SoftDevice ID范围开始。*/
#define NRF_FAULT_ID_APP_RANGE_START    0x00001000            /**<应用程序ID范围开始。*/
/**@} */

/**@defgroup NRF_FAULT_IDS故障ID类型
 * @{ */
#define NRF_FAULT_ID_SD_ASSERT    (NRF_FAULT_ID_SD_RANGE_START  + 1)          /**<SoftDevice断言。info参数保留供将来使用。*/
#define NRF_FAULT_ID_APP_MEMACC   (NRF_FAULT_ID_APP_RANGE_START + 1)          /**<应用程序无效内存访问。如果SoftDevice RAM访问冲突，信息参数将包含0x00000000。在SoftDevice外围寄存器冲突的情况下，信息参数将包含子区域编号PREGION[0]，在其地址范围内，不允许的写入访问导致了内存访问故障。*/
/**@} */

/** @} */

/** @addtogroup NRF_SDM_ENUMS枚举
 * @{ */

/**@brief nRF SoftDevice Manager API SVC编号。*/
enum NRF_SD_SVCS
{
  SD_SOFTDEVICE_ENABLE = SDM_SVC_BASE, /**<：：sd_softdevice_enable*/
  SD_SOFTDEVICE_DISABLE,               /**<：：sd_softdevice_disable*/
  SD_SOFTDEVICE_IS_ENABLED,            /**<：：sd_softdevice_is_enabled*/
  SD_SOFTDEVICE_VECTOR_TABLE_BASE_SET, /**<：：sd_softdevice_vector_table_base_set*/
  SVC_SDM_LAST                         /**<上一个SDM SVC的占位符*/
};

/** @} */

/** @addtogroup NRF_SDM_DEFINES定义
 * @{ */

/**@defgroup NRF_CLOCK_LF_ACCURACY时钟精度
 * @{ */

#define NRF_CLOCK_LF_ACCURACY_250_PPM (0) /**<默认值：250 ppm*/
#define NRF_CLOCK_LF_ACCURACY_500_PPM (1) /**<500 ppm*/
#define NRF_CLOCK_LF_ACCURACY_150_PPM (2) /**<150 ppm*/
#define NRF_CLOCK_LF_ACCURACY_100_PPM (3) /**<100 ppm*/
#define NRF_CLOCK_LF_ACCURACY_75_PPM  (4) /**<75 ppm*/
#define NRF_CLOCK_LF_ACCURACY_50_PPM  (5) /**<50 ppm*/
#define NRF_CLOCK_LF_ACCURACY_30_PPM  (6) /**<30 ppm*/
#define NRF_CLOCK_LF_ACCURACY_20_PPM  (7) /**<20 ppm*/
#define NRF_CLOCK_LF_ACCURACY_10_PPM  (8) /**<10 ppm*/
#define NRF_CLOCK_LF_ACCURACY_5_PPM   (9) /**<5 ppm*/
#define NRF_CLOCK_LF_ACCURACY_2_PPM  (10) /**<2 ppm*/
#define NRF_CLOCK_LF_ACCURACY_1_PPM  (11) /**<1 ppm*/

/** @} */

/**@defgroup NRF_CLOCK_LF_SRC可能的LFCLK振荡器源
 * @{ */

#define NRF_CLOCK_LF_SRC_RC      (0)                        /**<LFCLK RC振荡器。*/
#define NRF_CLOCK_LF_SRC_XTAL    (1)                        /**<LFCLK晶体振荡器。*/
#define NRF_CLOCK_LF_SRC_SYNTH   (2)                        /**<由HFCLK合成的LFCLK。*/

/** @} */

/** @} */

/** @addtogroup NRF_SDM_TYPES类型
 * @{ */

/**@brief 表示LFCLK振荡器源的类型。*/
typedef struct
{
  uint8_t source;         /**<低频振荡器时钟源，请参见@ref NRF_clock_LF_SRC。*/
  uint8_t rc_ctiv;        /**< 仅适用于：：NRF_CLOCK_LF_SRC_RC:以1/4秒为单位的校准计时器间隔（nRF52:1-32）。
                               @注意：为避免时钟过度漂移，0.5摄氏度是一个校准计时器间隔内允许的最大温度变化。应选择间隔以确保这一点。

                                  @注意：如果源不是：：NRF_CLOCK_LF_SRC_RC，则必须为0。*/
  uint8_t rc_temp_ctiv;   /**<  仅适用于：：NRF_CLOCK_LF_SRC_RC：如果温度没有变化，RC振荡器的校准频率（以校准间隔数计）。0：即使温度没有变化，也要始终校准。1： 仅在温度发生变化时进行校准（仅限传统-nRF51）。2-33：检查温度，仅在温度发生变化时进行校准，但在任何情况下，校准将每rc_temp_ctiv间隔进行一次。

                                @注意：如果源不是：：NRF_CLOCK_LF_SRC_RC，则必须为0。

                                @注意：对于nRF52，应用程序必须确保至少每8秒校准一次，以确保+/-500 ppm的时钟稳定性。nRF52上的：：NRF_CLOCK_LF_SRC_RC的建议配置为RC_ctiv=16和RC_temp_ctiv=2。这将确保至少每8秒校准一次，并且每4秒温度变化0.5摄氏度。有关更多信息，请参阅所用nRF52设备的产品规范。*/
  uint8_t accuracy;       /**<LL中用于计算定时窗口的外部时钟精度，请参见@ref NRF_clock_LF_accuracy。*/
} nrf_clock_lf_cfg_t;

/**@brief 故障处理程序类型。
 *
 * 当应用程序或SoftDevice中发生某些不可恢复的错误时，将调用故障处理程序。发生这种情况时，协议栈将处于未定义状态，恢复的唯一方法是执行重置，例如使用CMSIS NVIC_SystemReset（）。如果应用程序从故障处理程序返回，SoftDevice将调用NVIC_SystemReset（）。
 *
 * @note 此回调在HardFault上下文中执行，因此无法从故障回调调用SVC函数。
 *
 * @param[in] id 故障标识符。请参见@ref NRF_FAULT_IDS。
 * @param[in] pc 触发故障的指令的程序计数器。
 * @param[in] info 有关故障的可选附加信息。有关详细信息，请参阅每个故障标识符。
 *
 * @note 当id设置为@ref NRF_FAULT_id_APP_MEMACC时，pc将包含CPU检测到故障时正在执行的指令的地址。CPU程序计数器可能在触发故障的指令之后前进了多达2条指令（无分支）。
 */
typedef void (*nrf_fault_handler_t)(uint32_t id, uint32_t pc, uint32_t info);

/** @} */

/** @addtogroup NRF_SDM_FUNCTIONS函数
 * @{ */

/**@brief 启用SoftDevice并扩展协议堆栈。
 *
 * @note 调用此函数时，如果低频时钟源已在运行，则必须小心：如果低频时钟的源与当前运行的源不同，则将停止。然后，将启动新的时钟源。
 *
 * @note 当返回错误时，此函数无效。
 *
 * @post 如果返回代码为：：NRF_SUCCESS
 *       -SoC库和协议栈API可用。
 *       -部分RAM将不可用（参见相关SDS文件）。
 *       -某些外围设备将不可用或仅通过SoC API可用（请参阅相关SDS文档）。
 *       -中断不会从受保护的外围设备或中断到达。
 *       -必须使用nrf_nvic_函数而不是CMSIS nvic_函数来可靠使用SoftDevice。
 *       -SoftDevice可能会影响中断延迟（请参阅相关SDS文档）。
 *       -选择的低频时钟源将运行。
 *
 * @param p_clock_lf_cfg 低频时钟源和精度。如果为NULL，则时钟将配置为RC_ctiv=16和.RC_temp_ctiv=2的RC源。在XTAL源的情况下，所选时钟源的PPM精度必须大于或等于XTAL时钟的实际特性。
 * @param fault_handler 发生故障时要调用的回调不能为NULL。
 *
 * @retval ::NRF_SUCCESS
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效或为NULL。
 * @retval ：：NRF_ERROR_INVALID_STATE SoftDevice已启用，无法更新时钟源和故障处理程序。
 * @retval ：：NRF_ERROR_SDM_INCORRECT_INTERUPT_CONFIGURATION SoftDevice中断已启用，或已启用的中断具有非法优先级。
 * @retval ：：NRF_ERROR_SDM_LFCLK_SOURCE_UNKNOWN选择了未知的低频时钟源。
 * @retval ：：NRF_ERROR_INVALID_PARAM p_clock_lf_cfg中提供的时钟源配置无效。
 */
SVCALL(SD_SOFTDEVICE_ENABLE, uint32_t, sd_softdevice_enable(nrf_clock_lf_cfg_t const * p_clock_lf_cfg, nrf_fault_handler_t fault_handler));


/**@brief 禁用SoftDevice并扩展协议堆栈。
 *
 * 禁用SoftDevice的Idempent函数。
 *
 * @post SoC库和协议栈API不可用。
 * @post 所有受SoftDevice保护的中断将被禁用并初始化为优先级0（最高）。
 * @post SoftDevice使用的所有外围设备将重置为默认值。
 * @post 所有RAM都可用。
 * @post 所有中断都被转发到应用程序。
 * @post 在：sd_softdevice_enable中选择的LFCLK源将保持运行。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_SOFTDEVICE_DISABLE, uint32_t, sd_softdevice_disable(void));

/**@brief 检查SoftDevice是否已启用。
 *
 * @param[out]  p_softdevice_enabled 如果SoftDevice已启用：1否则为0。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_SOFTDEVICE_IS_ENABLED, uint32_t, sd_softdevice_is_enabled(uint8_t * p_softdevice_enabled));

/**@brief 为从SoftDevice转发的中断设置中断向量表的基地址
 *
 * 此函数仅在启动加载器时调用。
 *
 * @param[in] address 转发中断的中断向量表的基地址。

 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_SOFTDEVICE_VECTOR_TABLE_BASE_SET, uint32_t, sd_softdevice_vector_table_base_set(uint32_t address));

/** @} */

#ifdef __cplusplus
}
#endif
#endif // NRF_SDM_H__

/**
  @}
*/

