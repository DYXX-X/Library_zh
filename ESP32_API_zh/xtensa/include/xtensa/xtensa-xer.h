/* xer常数。h——描述通过wer和rer访问的外部寄存器的各种常数。

      TODO:查找更好的前缀。还根据实际存在的内核和中断的数量对某些常量进行条件化。
*/

/*
 * 版权所有（c）1999-2008 Tensilica Inc。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <xtensa/config/core.h>

#define NUM_INTERRUPTS 27
#define NUM_CORES       4

/* NMI（BInterrupt2）和中断0..n-1（BIinterrupt3+）RER读取WER写入的路由
 */

#define XER_MIROUT           0x0000
#define XER_MIROUT_LAST      (XER_MIROUT + NUM_INTERRUPTS)


/* IPI至核心M（所有16个原因）。

   RER读取WER清除
 */
#define XER_MIPICAUSE        0x0100
#define XER_MIPICAUSE_FIELD_A_FIRST 0x0
#define XER_MIPICAUSE_FIELD_A_LAST  0x0
#define XER_MIPICAUSE_FIELD_B_FIRST 0x1
#define XER_MIPICAUSE_FIELD_B_LAST  0x3
#define XER_MIPICAUSE_FIELD_C_FIRST 0x4
#define XER_MIPICAUSE_FIELD_C_LAST  0x7
#define XER_MIPICAUSE_FIELD_D_FIRST 0x8
#define XER_MIPICAUSE_FIELD_D_LAST  0xF


/* 原因位0..15的IPI

   RER无效WER集合
*/
#define XER_MIPISET          0x0140
#define XER_MIPISET_LAST     0x014F


/* 全局启用

   RER读取WER清除
*/
#define XER_MIENG            0x0180


/* 全局启用

   RER无效WER集合
*/
#define XER_MIENG_SET        0x0184

/* 全局断言

   RER读取WER清除
*/
#define XER_MIASG            0x0188


/* 全局启用

   RER无效WER集合
*/
#define XER_MIASG_SET        0x018C


/* IPI分区寄存器

   RER读WER写
*/
#define XER_PART            0x0190
#define XER_IPI0            0x0
#define XER_IPI1            0x1
#define XER_IPI2            0x2
#define XER_IPI3            0x3

#define XER_PART_ROUTE_IPI(NUM, FIELD) ((NUM) << ((FIELD) << 2))

#define XER_PART_ROUTE_IPI_CAUSE(TO_A, TO_B, TO_C, TO_D)		\
  (XER_PART_ROUTE_IPI(TO_A, XER_IPI0) |					\
   XER_PART_ROUTE_IPI(TO_B, XER_IPI1) |					\
   XER_PART_ROUTE_IPI(TO_C, XER_IPI2) |					\
   XER_PART_ROUTE_IPI(TO_D, XER_IPI3))

#define XER_IPI_WAKE_EXT_INTERRUPT XCHAL_EXTINT0_NUM
#define XER_IPI_WAKE_CAUSE  XER_MIPICAUSE_FIELD_C_FIRST
#define XER_IPI_WAKE_ADDRESS    (XER_MIPISET + XER_IPI_WAKE_CAUSE)
#define XER_DEFAULT_IPI_ROUTING XER_PART_ROUTE_IPI_CAUSE(XER_IPI1, XER_IPI0, XER_IPI2, XER_IPI3)


/* 系统配置ID

   RER读取WER无效
*/
#define XER_SYSCFGID        0x01A0


/* 运行暂停到从属处理器

   RER读WER写
*/
#define XER_MPSCORE        0x0200


/* 缓存一致性开启

   RER读WER写
*/
#define XER_CCON           0x0220

