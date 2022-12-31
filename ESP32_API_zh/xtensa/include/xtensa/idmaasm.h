/* $Id://depot/dev/Foxhill/Xtensa/OS/include/Xtensa/mpusm。小时#5$*/

/*
 * 版权所有（c）2016 Cadence Design Systems，Inc。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _IDMAASM_H_
#define _IDMAASM_H_

#if XCHAL_HAVE_IDMA
#include <xtensa/idma.h>
#endif

/*
 * 用于还原IDMA regs的宏
 *
 * 参数：a_save=>地址寄存器，包含指向IDMA存储区域a_timpl、a_timpl2和a_timpl3的指针。=>地址寄存器临时
 */
//   IDMA_REG_SETTINGS,
//   IDMA_REG_TIMEOUT,
//   IDMA_REG_DESC_START,
//   IDMA_REG_CONTROL,
//   IDMA_REG_USERPRIV,

.macro _idma_restore a_save, a_temp1, a_temp2, a_temp3
#if XCHAL_HAVE_IDMA
	l32i	\a_temp1, \a_save, 0
	movi	\a_temp3, idmareg_base
	movi	\a_temp2, IDMA_REG_SETTINGS
	add	\a_temp2, \a_temp2, \a_temp3
	wer	\a_temp1, \a_temp2
	l32i	\a_temp1, \a_save, 4
	movi	\a_temp2, IDMA_REG_TIMEOUT
	add	\a_temp2, \a_temp2, \a_temp3
	wer	\a_temp1, \a_temp2
	l32i	\a_temp1, \a_save, 8
	movi	\a_temp2, IDMA_REG_DESC_START
	add	\a_temp2, \a_temp2, \a_temp3
	wer	\a_temp1, \a_temp2
	l32i	\a_temp1, \a_save, 12
	movi	\a_temp2, IDMA_REG_CONTROL
	add	\a_temp2, \a_temp2, \a_temp3
	wer	\a_temp1, \a_temp2
	l32i	\a_temp1, \a_save, 16
	movi	\a_temp2, IDMA_REG_USERPRIV
	add	\a_temp2, \a_temp2, \a_temp3
	wer	\a_temp1, \a_temp2
#endif
.endm

#endif //_IDMAASM_H_

