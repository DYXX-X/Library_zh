/*
** 两级隔离适配内存分配器，3.1版。Matthew Conte编写http://tlsf.baisoku.org
**
** 根据Miguel Masmano的原始文件：http://www.gii.upv.es/tlsf/main/docs
**
** 此实现是根据文档规范编写的，因此不适用GPL限制。
**
** 版权所有（c）2006-2016，Matthew Conte保留所有权利。
**
** 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名来支持或推广源自本软件的产品。
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MATTHEW CONTE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#ifdef ESP_PLATFORM

#include "soc/soc.h"

#if !CONFIG_SPIRAM
#define TLSF_MAX_POOL_SIZE (SOC_DIRAM_DRAM_HIGH - SOC_DIRAM_DRAM_LOW)
#else
#define TLSF_MAX_POOL_SIZE SOC_EXTRAM_DATA_SIZE
#endif

enum tlsf_config
{
	/* 块大小的线性细分数目的log2。较大的值在控制结构中需要更多的内存。通常值为4或5。
	*/
	SL_INDEX_COUNT_LOG2  = 5,

	/* 所有分配大小和地址都与4字节对齐。*/
	ALIGN_SIZE_LOG2 = 2,
	ALIGN_SIZE = (1 << ALIGN_SIZE_LOG2),

	/*
	** 我们支持大小最多为（1<<FL_INDEX_MAX）位的分配。然而，因为我们线性地细分了第二级列表，并且我们的最小大小粒度为4字节，所以为小于SL_INDEX_COUNT 4或（1<<（SL_INDEX_COUNT_LOG2+2））字节的大小创建第一级列表是没有意义的，因为在那里我们将尝试将大小范围拆分为比我们可用的更多的插槽。相反，我们计算最小阈值大小，并将该大小以下的所有块放入第0个第一级列表。
	*/

	/* 调整第一级，我们可以减少TLSF池开销，以换取管理小于4GB的池
	 */
	#if (TLSF_MAX_POOL_SIZE <= (256 * 1024))
	FL_INDEX_MAX = 18, //每个池最多可以有256KB
	#elif (TLSF_MAX_POOL_SIZE <= (512 * 1024))
	FL_INDEX_MAX = 19, //每个池最多可以有512KB
	#elif (TLSF_MAX_POOL_SIZE <= (1 * 1024 * 1024))
	FL_INDEX_MAX = 20, //每个池最多可以有1MB
	#elif (TLSF_MAX_POOL_SIZE <= (2 * 1024 * 1024))
	FL_INDEX_MAX = 21, //每个池最多可容纳2MB
	#elif (TLSF_MAX_POOL_SIZE <= (4 * 1024 * 1024))
	FL_INDEX_MAX = 22, //每个池最多可以有4MB
	#elif (TLSF_MAX_POOL_SIZE <= (8 * 1024 * 1024))
	FL_INDEX_MAX = 23, //每个池最多可以有8MB
	#elif (TLSF_MAX_POOL_SIZE <= (16 * 1024 * 1024))
	FL_INDEX_MAX = 24, //每个池最多可以有16MB
	#else
	#error "Higher TLSF pool sizes should be added for this new config"
	#endif

	SL_INDEX_COUNT = (1 << SL_INDEX_COUNT_LOG2),
	FL_INDEX_SHIFT = (SL_INDEX_COUNT_LOG2 + ALIGN_SIZE_LOG2),
	FL_INDEX_COUNT = (FL_INDEX_MAX - FL_INDEX_SHIFT + 1),

	SMALL_BLOCK_SIZE = (1 << FL_INDEX_SHIFT),
};
#else
enum tlsf_config
{
	//主机测试的特定配置。

	/* 块大小的线性细分数目的log2。较大的值在控制结构中需要更多的内存。通常值为4或5。
	*/
	SL_INDEX_COUNT_LOG2  = 5,

	/* 所有分配大小和地址都与4字节对齐。*/
	ALIGN_SIZE_LOG2 = 2,
	ALIGN_SIZE = (1 << ALIGN_SIZE_LOG2),

	/* 调整第一级，我们可以减少TLSF池开销，以换取管理小于4GB的池
	 */
	FL_INDEX_MAX = 30,

	SL_INDEX_COUNT = (1 << SL_INDEX_COUNT_LOG2),
	FL_INDEX_SHIFT = (SL_INDEX_COUNT_LOG2 + ALIGN_SIZE_LOG2),
	FL_INDEX_COUNT = (FL_INDEX_MAX - FL_INDEX_SHIFT + 1),

	SMALL_BLOCK_SIZE = (1 << FL_INDEX_SHIFT),
};
#endif

