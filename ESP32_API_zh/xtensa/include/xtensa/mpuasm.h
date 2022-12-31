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

#ifndef _MPUASM_H_
#define _MPUASM_H_
#include <xtensa/config/core.h>

/*
 * 用于写入MPU映射的宏。
 *
 * 参数：a_map=>包含指向MPU映射a_num_entries指针的地址寄存器=>前面提到的映射a_temp1，a_temp2中的条目数。=>地址寄存器temporariesa_temp3，a_ttemp4
 */

.macro mpu_write_map a_map, a_num_entries, a_temp1, a_temp2, a_temp3, a_temp4
#if XCHAL_HAVE_MPU
	movi	\a_temp1, 0
	wsr.cacheadrdis \a_temp1 // 在所有区域中启用缓存
	wsr.mpuenb	\a_temp1	// 禁用所有前台条目

    // 清除未使用的条目。
    //
    // 目前我们正在清除所有条目，因为当前
    // 即使条目都已禁用，也必须对其进行排序。
    // 如果当所有条目都被禁用时允许无序条目，
    // 通过清除XCHAL_MPU_ENTRIES-n可以提高性能
	// （n=条目数）而不是XCHAL_MPU_entries-1条目。
	//
	movi	\a_temp2, 0
	movi	\a_temp3, XCHAL_MPU_ENTRIES - 1
	j	1f
	.align 16 // 这样做是为了确保
1:
	memw     // todo当前wptlb必须先有memw。说明书必须
	// 以确保两者位于同一缓存行中。这些声明应为
	// 从硬件中删除该限制时，已正确调整
	wptlb	\a_temp2, \a_temp1
	addi	\a_temp2, \a_temp2, 1
	bltu	\a_temp2, \a_temp3, 1b

        // 写下新条目。
	//
	beqz	\a_num_entries, 4f				// 如果没有条目，则跳过循环
	addx8	\a_map, \a_num_entries, \a_map			// 计算所提供地图的结尾
	j		3f
	.align 16
2:	memw     // todo当前wptlb必须先有memw。说明书必须
	// 以确保两者位于同一缓存行中。这些声明应为
	// 从硬件中删除该限制时，已正确调整
	wptlb	\a_temp2, \a_temp4
	addi	\a_temp3, \a_temp3, -1
	beqz	\a_num_entries, 4f		// 循环直到完成
3:	addi	\a_map, \a_map, -8
	l32i	\a_temp2, \a_map, 4			// 获取（acc.rights，memtype）
	l32i	\a_temp4, \a_map, 0			// 获取为（vstart，有效）
	addi	\a_num_entries, \a_num_entries, -1
	extui	\a_temp1, \a_temp2, 0, 5			// 入口索引部分
	xor		\a_temp2, \a_temp2, \a_temp1			// 将其归零
	or		\a_temp2, \a_temp2, \a_temp3			// 设置索引=\a_temp3
	j		2b
4:
#endif
.endm

/*
 * 用于读取MPU地图的宏
 *
 * 参数：a_map_ptr=>指向写入映射的内存的地址寄存器a_timpl，a_timpl2=>地址寄存器temporaries
 */
.macro mpu_read_map a_map_ptr, a_temp1, a_temp2
#if XCHAL_HAVE_MPU
	movi	\a_temp1, XCHAL_MPU_ENTRIES // 将索引设置为最后一个条目+1
	addx8	\a_map_ptr, \a_temp1, \a_map_ptr // 将map ptr设置为最后一个条目+1
1:	addi	\a_temp1, \a_temp1, -1 // 减量指数
	addi	\a_map_ptr, \a_map_ptr, -8 // 减量指数
	rptlb0	\a_temp2, \a_temp1 // 读取条目的1/2
	s32i	\a_temp2, \a_map_ptr, 0 // 写入条目的1/2
	rptlb1	\a_temp2,	\a_temp1
	s32i	\a_temp2, \a_map_ptr, 4
	bnez	\a_temp1, 1b // 循环直到完成
#endif
	.endm

#endif

