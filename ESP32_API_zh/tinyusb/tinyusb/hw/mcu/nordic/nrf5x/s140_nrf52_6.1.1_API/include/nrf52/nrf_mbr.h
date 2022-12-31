/*
 * 版权所有（c）2014-2017，Nordic Semiconductor ASA保留所有权利。
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
  @defgroup nrf_mbr_api主引导记录api@{

  @用于更新SoftDevice和BootLoader的简短API

*/

#ifndef NRF_MBR_H__
#define NRF_MBR_H__

#include "nrf_svc.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup NRF_MBR_DEFINES定义
 * @{ */

/**@brief MBR SVC基数。*/
#define MBR_SVC_BASE            (0x18)

/**@brief 页面大小（大写）。*/
#define MBR_PAGE_SIZE_IN_WORDS  (1024)

/** @brief 将SoftDevice写入闪存时必须为MBR保留的大小。这是写入SoftDevice十六进制文件的第一个字节的偏移量。*/
#define MBR_SIZE                (0x1000)

/** @brief 引导加载程序地址的位置（在闪存中）。*/
#define MBR_BOOTLOADER_ADDR      (0xFF8)

/** @brief 引导加载程序地址的位置（在UICR中）。*/
#define MBR_UICR_BOOTLOADER_ADDR (&(NRF_UICR->NRFFW[0]))

/** @brief MBR参数页地址的位置（在闪存中）。*/
#define MBR_PARAM_PAGE_ADDR      (0xFFC)

/** @brief MBR参数页地址的位置（在UICR中）。*/
#define MBR_UICR_PARAM_PAGE_ADDR (&(NRF_UICR->NRFFW[1]))


/** @} */

/** @addtogroup NRF_MBR_ENUMS枚举
 * @{ */

/**@brief nRF主引导记录API SVC编号。*/
enum NRF_MBR_SVCS
{
  SD_MBR_COMMAND = MBR_SVC_BASE, /**<：：sd_mbr_command*/
};

/**@brief ：sd_mbr_command_t的可能值。命令*/
enum NRF_MBR_COMMANDS
{
  SD_MBR_COMMAND_COPY_BL,                 /**<复制新的BootLoader@请参见：：sd_mbr_command_copy_bl_t*/
  SD_MBR_COMMAND_COPY_SD,                 /**<复制新的SoftDevice@请参见：：sd_mbr_command_copy_sd_t*/
  SD_MBR_COMMAND_INIT_SD,                 /**<初始化向SD转发中断，并在SD中运行重置功能。：sd_mbr_command_t params中不需要任何参数。*/
  SD_MBR_COMMAND_COMPARE,                 /**<此命令与memcmp类似@请参见：：sd_mbr_command_compare_t*/
  SD_MBR_COMMAND_VECTOR_TABLE_BASE_SET,   /**<更改重置后MBR启动的地址@请参见：：sd_mbr_command_vector_table_base_set_t*/
  SD_MBR_COMMAND_RESERVED,
  SD_MBR_COMMAND_IRQ_FORWARD_ADDRESS_SET, /**<开始将所有中断转发到此地址@请参阅：：sd_mbr_command_inrq_forward_address_set_t*/
};

/** @} */

/** @addtogroup NRF_MBR_TYPES类型
 * @{ */

/**@brief 此命令复制新SoftDevice的一部分
 *
 * 复制前将擦除目标区域。如果dst位于闪存页的中间，则整个闪存页将被擦除。如果（dst+len）位于闪存页的中间，则整个闪存页将被擦除。
 *
 * 此功能的用户负责设置BPROT寄存器。
 *
 * @retval ：：NRF_SUCCESS表示正确复制了内存块的内容。
 * @retval ：：NRF_ERROR_INTERNAL表示复制后未正确验证内存块的内容。
 */
typedef struct
{
  uint32_t *src;  /**<指向要复制的数据源的指针。*/
  uint32_t *dst;  /**<指向要复制内容的目标的指针。*/
  uint32_t len;   /**<要复制的32位字的数量。必须是@ref MBR_PAGE_SIZE_IN_WORDS单词的倍数。*/
} sd_mbr_command_copy_sd_t;


/**@brief 该命令的工作方式与memcmp类似，但采用的是单词长度。
 *
 * @retval ：：NRF_SUCCESS表示两个内存块的内容相等。
 * @retval ：：NRF_ERROR_NULL表示内存块的内容不相等。
 */
typedef struct
{
  uint32_t *ptr1; /**<指向内存块的指针。*/
  uint32_t *ptr2; /**<指向内存块的指针。*/
  uint32_t len;   /**<要比较的32位字的数量。*/
} sd_mbr_command_compare_t;


/**@brief 此命令复制新的BootLoader。
 *
 * The MBR assumes that either @ref MBR_BOOTLOADER_ADDR或@ref MBR_UICR_BOOTLOADER_ADDR设置为将复制引导加载器的地址。如果设置了两个地址，MBR将优先考虑
 * @ref MBR_BOOTLOADER_ADDR.
 *
 * 此函数将擦除引导加载程序目标。如果（destination+bl_len）位于闪存页的中间，则整个闪存页将被擦除。
 *
 * This command requires that @ref PARAM_PAGE_ADDR或@ref MBR_UICR_PARAM_PAGE_ADDR被设置，
 * see @ref sd_mbr_command。
 *
 * 此命令将使用闪存保护外围设备（BPROT或ACL）来保护不打算写入的闪存。
 *
 * 成功后，此函数将不会返回。它将正常从重置向量启动新的引导加载程序。
 *
 * @retval ：：NRF_ERROR_INTERNAL表示不应发生的内部错误。
 * @retval ：：NRF_ERROR_FORBIDDEN（如果未设置引导加载程序地址）。
 * @retval ：：NRF_ERROR_INVALID_LENGTH，如果参数试图在闪存区域外读写。
 * @retval ：：NRF_ERROR_NO_MEM未提供MBR参数页。请参见@ref sd_mbr_command。
 */
typedef struct
{
  uint32_t *bl_src;  /**<指向要复制的引导加载程序的源的指针。*/
  uint32_t bl_len;   /**<要为BootLoader复制的32位字的数量。*/
} sd_mbr_command_copy_bl_t;

/**@brief 更改重置后MBR启动的地址
 *
 * 一旦调用了该函数，MBR将在重置后开始将中断转发到该地址。
 *
 * To restore default forwarding, this function should be called with @ref 地址设置为0。如果存在引导加载程序，则中断将被转发到引导加载程序。如果没有，中断将被转发到SoftDevice。
 *
 * 可以在@ref MBR_bootloader_ADDR或
 * @ref MBR_UICR_BOOTLOADER_ADDR。如果设置了两个地址，MBR将优先考虑
 * @ref MBR_BOOTLOADER_ADDR.
 *
 * This command requires that @ref PARAM_PAGE_ADDR或@ref MBR_UICR_PARAM_PAGE_ADDR被设置，
 * see @ref sd_mbr_command。
 *
 * 成功后，此函数将不会返回。它将重置设备。
 *
 * @retval ：：NRF_ERROR_INTERNAL表示不应发生的内部错误。
 * @retval ：：NRF_ERROR_INVALID_ADDR，如果参数地址超出闪存大小。
 * @retval ：：NRF_ERROR_NO_MEM未提供MBR参数页。请参见@ref sd_mbr_command。
 */
typedef struct
{
  uint32_t address; /**<转发中断的中断向量表的基地址。*/
} sd_mbr_command_vector_table_base_set_t;

/**@brief 为从MBR转发的中断设置中断向量表的基地址
 *
 * 与sd_mbr_command_vector_table_base_set_t不同，此函数不会重置，重置后mbr启动的位置也不会改变。
 *
 * @retval ::NRF_SUCCESS
 */
typedef struct
{
  uint32_t address; /**<转发中断的中断向量表的基地址。*/
} sd_mbr_command_irq_forward_address_set_t;

/**@brief 包含调用：：sd_mbr_command时使用的数据的输入结构
 *
 * 根据设置的命令值，相应的params值类型也必须为
 * set. See @ref 命令类型和相应参数值类型的NRF_MBR_command。If命令
 * @ref SD_MBR_COMMAND_INIT_SD已设置，无需在参数下设置任何值。
 */
typedef struct
{
  uint32_t command;  /**<要发出的命令类型。请参见@ref NRF_MBR_COMMAND。*/
  union
  {
    sd_mbr_command_copy_sd_t copy_sd;  /**<复制SoftDevice的参数。*/
    sd_mbr_command_compare_t compare;  /**<验证参数。*/
    sd_mbr_command_copy_bl_t copy_bl;  /**<复制BootLoader的参数。需要参数页。*/
    sd_mbr_command_vector_table_base_set_t base_set; /**<矢量表基集的参数。需要参数页。*/
    sd_mbr_command_irq_forward_address_set_t irq_forward_address_set; /**<irq转发地址集的参数*/
  } params; /**<命令参数。*/
} sd_mbr_command_t;

/** @} */

/** @addtogroup NRF_MBR_FUNCTIONS函数
 * @{ */

/**@brief 发出主引导记录命令
 *
 * 更新SoftDevice和引导加载程序时使用的命令。
 *
 * The @ref SD_MBR_COMMAND_COPY_BL和@ref SD_MBR_COMMAND_VECTOR_TABLE_BASE_SET要求MBR在重置IC时保留参数。这是在单独的闪存页面中完成的。闪存页面的位置应由应用程序提供
 * @ref MBR_PARAM_PAGE_ADDR或@ref MBR_UICR_PARAM_PAGE_ADDR。如果设置了两个地址，MBR
 * will prioritize @ref MBR_PARAM_PAGE_ADDR。此页面将由MBR清除，用于在重置之前存储命令。指定地址后，应用程序不能使用它所引用的页面。如果应用程序未提供地址，即
 * @ref MBR_PARAM_PAGE_ADDR和@ref MBR_UICR_PARAM_PAGE_ADDR为0xFFFFFFFF，使用闪存的MBR命令将不可用，并返回@ref NRF_ERROR_NO_MEM。
 *
 * @param[in]  param 指向描述命令的结构的指针。
 *
 * @note 有关完整的返回值集，请参见：：sd_mbr_command_copy_sd_t、：：sd_mbr_command _copy_bl_t、：sd_mbr _command-compare_t、：：：sd-mbr_commands_vector_table_base_set_t、：
 *
 * @retval ：：NRF_ERROR_NO_MEM未提供MBR参数页
 * @retval ：：NRF_ERROR_INVALID_PARAM（如果给定的命令无效）。
*/
SVCALL(SD_MBR_COMMAND, uint32_t, sd_mbr_command(sd_mbr_command_t* param));

/** @} */

#ifdef __cplusplus
}
#endif
#endif // NRF_MBR_H__

/**
  @}
*/

