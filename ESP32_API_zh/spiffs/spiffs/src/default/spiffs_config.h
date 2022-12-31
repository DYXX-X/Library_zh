/*
 * 溢出配置h
 *
 *  创建日期：2013年7月3日作者：petera
 */

#ifndef SPIFFS_CONFIG_H_
#define SPIFFS_CONFIG_H_

// ----------- 8< ------------
// 以下内容用于spiffs的linux测试构建
// 这些可能/应该/必须在目标中删除/更改/替换
#include "params_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#ifdef _SPIFFS_TEST
#include "testrunner.h"
#endif
// ----------- >8 ------------

// 编译时开关

// 设置泛型spiffs调试输出调用。
#ifndef SPIFFS_DBG
#define SPIFFS_DBG(_f, ...) //打印f（_f，##__VA_ARGS__）
#endif
// 设置垃圾收集的spiffs调试输出调用。
#ifndef SPIFFS_GC_DBG
#define SPIFFS_GC_DBG(_f, ...) //打印f（_f，##__VA_ARGS__）
#endif
// 设置缓存的spiffs调试输出调用。
#ifndef SPIFFS_CACHE_DBG
#define SPIFFS_CACHE_DBG(_f, ...) //打印f（_f，##__VA_ARGS__）
#endif
// 为系统一致性检查设置spiffs调试输出调用。
#ifndef SPIFFS_CHECK_DBG
#define SPIFFS_CHECK_DBG(_f, ...) //打印f（_f，##__VA_ARGS__）
#endif
// 为所有api调用设置spiffs调试输出调用。
#ifndef SPIFFS_API_DBG
#define SPIFFS_API_DBG(_f, ...) //打印f（_f，##__VA_ARGS__）
#endif



// 定义spiffs调试打印格式器
// 一些通用的有符号数
#ifndef _SPIPRIi
#define _SPIPRIi   "%d"
#endif
// 住址
#ifndef _SPIPRIad
#define _SPIPRIad  "%08x"
#endif
// 块
#ifndef _SPIPRIbl
#define _SPIPRIbl  "%04x"
#endif
// 页
#ifndef _SPIPRIpg
#define _SPIPRIpg  "%04x"
#endif
// 跨度指数
#ifndef _SPIPRIsp
#define _SPIPRIsp  "%04x"
#endif
// 文件描述符
#ifndef _SPIPRIfd
#define _SPIPRIfd  "%d"
#endif
// 文件对象id
#ifndef _SPIPRIid
#define _SPIPRIid  "%04x"
#endif
// 文件标志
#ifndef _SPIPRIfl
#define _SPIPRIfl  "%02x"
#endif


// 启用/禁用API函数以确定确切的字节数
// 用于文件描述符和缓存缓冲区。一旦决定了配置，
// 这可以被禁用以减少闪光。
#ifndef SPIFFS_BUFFER_HELP
#define SPIFFS_BUFFER_HELP              0
#endif

// 启用/禁用nucleus文件系统操作的内存读取缓存。
// 如果启用，则必须为SPIFFS_mount中的缓存提供内存区域。
#ifndef  SPIFFS_CACHE
#define SPIFFS_CACHE                    1
#endif
#if SPIFFS_CACHE
// 为hydrogen中的文件描述符启用内存写缓存
#ifndef  SPIFFS_CACHE_WR
#define SPIFFS_CACHE_WR                 1
#endif

// 启用/禁用缓存统计信息。仅用于调试/测试目的。
#ifndef  SPIFFS_CACHE_STATS
#define SPIFFS_CACHE_STATS              1
#endif
#endif

// 始终检查每个访问页面的标题，以确保状态一致。
// 如果启用，它将增加读取次数，增加闪存。
#ifndef SPIFFS_PAGE_CHECK
#define SPIFFS_PAGE_CHECK               1
#endif

// 定义要执行的gc运行的最大次数，以达到所需的可用页面。
#ifndef SPIFFS_GC_MAX_RUNS
#define SPIFFS_GC_MAX_RUNS              5
#endif

// 启用/禁用gc统计信息。仅用于调试/测试目的。
#ifndef SPIFFS_GC_STATS
#define SPIFFS_GC_STATS                 1
#endif

// 垃圾收集检查一个块中的所有页面
// 到一个方块得分。删除的页面通常会得到正面评分
// 使用过的页面通常给出一个负分数（因为这些页面必须移动）。
// 为了获得公平的磨损平衡，擦除年龄也包括在分数中，
// 其因子通常是最积极的。
// 得分越大，街区越有可能
// 选择用于垃圾收集。

// 垃圾收集启发式-用于删除页面的权重。
#ifndef SPIFFS_GC_HEUR_W_DELET
#define SPIFFS_GC_HEUR_W_DELET          (5)
#endif
// 垃圾收集启发式-用于已用页面的权重。
#ifndef SPIFFS_GC_HEUR_W_USED
#define SPIFFS_GC_HEUR_W_USED           (-1)
#endif
// 垃圾收集启发式-用于时间间隔的权重
// 最后擦除和擦除此块。
#ifndef SPIFFS_GC_HEUR_W_ERASE_AGE
#define SPIFFS_GC_HEUR_W_ERASE_AGE      (50)
#endif

// 对象名称最大长度。请注意，此长度包括
// 零终止字符，表示最大字符串数
// 最多可以是SPIFFS_OBC_NAME_LEN-1。
#ifndef SPIFFS_OBJ_NAME_LEN
#define SPIFFS_OBJ_NAME_LEN             (32)
#endif

// 与对象关联的元数据的最大长度。
// 设置为非零值可以启用元数据相关API
// 更改磁盘格式，因此更改不向后兼容。
//
// 请注意：元长度不得超过
// 逻辑页面大小-（SPIFFS_OBY_NAME_LEN+64）
//
// 这源于以下内容：
// 逻辑页面大小-（SPIFFS_OBY_NAME_LEN+sizeof（SPIFFS_page_header）+
// spiffs_object_ix_header字段+至少一些LUT条目）
#ifndef SPIFFS_OBJ_META_LEN
#define SPIFFS_OBJ_META_LEN             (0)
#endif

// 复制数据时使用的堆栈上分配的缓冲区大小。
// 值越低，读取/写入次数越多。不意味着要更大
// 而不是逻辑页面大小。
#ifndef SPIFFS_COPY_BUFFER_STACK
#define SPIFFS_COPY_BUFFER_STACK        (64)
#endif

// 使其具有可识别的溢出文件系统。这将查找
// 所有部门都有一个魔法，可以确定这是一个有效的溢出系统还是
// 不在装载点上。如果没有，则必须在安装之前调用SPIFFS_format
// 再一次
#ifndef SPIFFS_USE_MAGIC
#define SPIFFS_USE_MAGIC                (0)
#endif

#if SPIFFS_USE_MAGIC
// 仅在启用SPIFFS_USE_MAGIC时有效。如果SPIFFS_USE_MAGIC_LENGTH为
// 启用后，魔力也将取决于文件系统的长度。
// 例如，配置和格式化为4兆字节的文件系统不会
// 可以接受使用将文件系统定义为2的配置进行安装
// 兆字节。
#ifndef SPIFFS_USE_MAGIC_LENGTH
#define SPIFFS_USE_MAGIC_LENGTH         (0)
#endif
#endif

// SPIFFS_LOCK和SPIFFS_UNLOCK在api级别保护溢出不可重入
// 这些应该在多线程系统上定义

// 如果您在多线程系统上运行，请定义它以输入互斥体
#ifndef SPIFFS_LOCK
#define SPIFFS_LOCK(fs)
#endif
// 如果在多线程系统上运行，请定义此项以退出互斥体
#ifndef SPIFFS_UNLOCK
#define SPIFFS_UNLOCK(fs)
#endif

// 如果仅存在一个具有常量配置的spiffs实例，则启用
// 在目标上。这将减少计算、闪存和内存访问。
// 必须在下面定义配置的部分，而不是在装载时。
#ifndef SPIFFS_SINGLETON
#define SPIFFS_SINGLETON 0
#endif

#if SPIFFS_SINGLETON
// 不是在配置结构中提供参数，单例构建必须
// 在下面的定义中给出参数。
#ifndef SPIFFS_CFG_PHYS_SZ
#define SPIFFS_CFG_PHYS_SZ(ignore)        (1024*1024*2)
#endif
#ifndef SPIFFS_CFG_PHYS_ERASE_SZ
#define SPIFFS_CFG_PHYS_ERASE_SZ(ignore)  (65536)
#endif
#ifndef SPIFFS_CFG_PHYS_ADDR
#define SPIFFS_CFG_PHYS_ADDR(ignore)      (0)
#endif
#ifndef SPIFFS_CFG_LOG_PAGE_SZ
#define SPIFFS_CFG_LOG_PAGE_SZ(ignore)    (256)
#endif
#ifndef SPIFFS_CFG_LOG_BLOCK_SZ
#define SPIFFS_CFG_LOG_BLOCK_SZ(ignore)   (65536)
#endif
#endif

// 如果目标需要索引表的对齐数据，请启用此选项
#ifndef SPIFFS_ALIGNED_OBJECT_INDEX_TABLES
#define SPIFFS_ALIGNED_OBJECT_INDEX_TABLES       0
#endif

// 如果希望使用spiffs结构调用HAL回调，请启用此选项
#ifndef SPIFFS_HAL_CALLBACK_EXTRA
#define SPIFFS_HAL_CALLBACK_EXTRA         0
#endif

// 如果要向所有文件句柄添加整数偏移量，请启用此选项
// （spiffs_file）。如果在
// 相同的目标，以便识别文件句柄的溢出实例
// 属于。
// 注意：当
// 安装，必须定义。
#ifndef SPIFFS_FILEHDL_OFFSET
#define SPIFFS_FILEHDL_OFFSET                 0
#endif

// 启用此选项可编译spiffs的只读版本。
// 这将减少溢出的二进制大小。包含修改的所有代码
// 将不会编译文件系统的。某些配置将被忽略。
// 用于擦除和写入spi闪存的HAL函数可能为空。隐藏物
// 可以禁用，以进一步减少二进制大小（和ram节省）。
// 修改fs的函数将返回SPIFFS_ERROR_RO_NOT_IMPL。
// 如果由于擦除操作中止而无法装载文件系统，并且
// SPIFFS_USE_MAGIC已启用，SPIFFS_ERROR_RO_ABORTED_OPERATION将
// 返回。
// 可能对例如bootloader等有用。
#ifndef SPIFFS_READ_ONLY
#define SPIFFS_READ_ONLY                      0
#endif

// 启用此选项可以使用fd缓冲区添加临时文件缓存。
// 缓存的效果是SPIFFS_open在
// 某些情况下。这将使spiff更容易找到文件
// 频繁打开，减少spi闪存的读数
// 查找这些文件。
// 这将使每个fd增加6个字节。如果文件以模式打开
// 通过一定程度的时间局部性，优化了系统。
// 示例可以是让spiffs提供web内容，其中一个文件是css。
// 每个打开的html文件都会访问css，这意味着它是
// 几乎每打开一次文件就访问一次。另一个例子可以是
// 经常打开、写入和关闭的日志文件。
// 缓存的大小是它附带的给定文件描述符的数量
// 关于fd更新机制。缓存存在于关闭的文件描述符中。
// 关闭时，fd知道文件的位置。而不是忘记
// 这样，临时缓存将继续处理该文件的更新，即使
// fd关闭。如果再次打开文件，则会找到文件的位置
// 直接地如果所有可用的描述符都打开，则所有缓存都将
// 迷路的
#ifndef SPIFFS_TEMPORAL_FD_CACHE
#define SPIFFS_TEMPORAL_FD_CACHE              1
#endif

// 临时文件缓存命中分数。每次打开文件时，所有缓存的文件
// 将失去一分。如果在缓存中找到打开的文件，则该条目将
// 获得SPIFFS_TEMPORAL_CCACHE_HIT_SCORE点。可以用这个做实验
// 应用程序的特定访问模式的值。但是，它必须
// 介于1（经常命中缓存条目没有增益）和255之间。
#ifndef SPIFFS_TEMPORAL_CACHE_HIT_SCORE
#define SPIFFS_TEMPORAL_CACHE_HIT_SCORE       4
#endif

// 启用以能够将对象索引映射到内存。
// 这允许在读取的情况下进行更快、更具确定性的读取
// 大文件时，通过四处查找来更改文件偏移。
// 映射文件索引时，将扫描文件系统中的索引页
// 并且该信息将被存储在用户提供的存储器中。阅读时
// 可以查找内存映射，而不是在
// 中等的这样，用户可以用内存和性能进行权衡。
// 可以映射尚未编写的全部、部分或未来部分。这个
// 内存阵列将由spiff拥有，并在垃圾处理期间相应更新
// 收集或修改索引时。当
// 文件以某种方式被修改。索引缓冲区绑定到文件
// 描述符。
#ifndef SPIFFS_IX_MAP
#define SPIFFS_IX_MAP                         1
#endif

// 将SPIFFS_TEST_VISUALISATION设置为非零以启用SPIFFS_vis功能
// 在api中。此函数将使用给定的printf可视化所有文件系统
// 作用
#ifndef SPIFFS_TEST_VISUALISATION
#define SPIFFS_TEST_VISUALISATION         1
#endif
#if SPIFFS_TEST_VISUALISATION
#ifndef spiffs_printf
#define spiffs_printf(...)                printf(__VA_ARGS__)
#endif
// 自由页的spiffs_printf参数
#ifndef SPIFFS_TEST_VIS_FREE_STR
#define SPIFFS_TEST_VIS_FREE_STR          "_"
#endif
// 已删除页面的spiffs_printf参数
#ifndef SPIFFS_TEST_VIS_DELE_STR
#define SPIFFS_TEST_VIS_DELE_STR          "/"
#endif
// 给定对象id的索引页的spiffs_printf参数
#ifndef SPIFFS_TEST_VIS_INDX_STR
#define SPIFFS_TEST_VIS_INDX_STR(id)      "i"
#endif
// 给定对象id的数据页的spiffs_printf参数
#ifndef SPIFFS_TEST_VIS_DATA_STR
#define SPIFFS_TEST_VIS_DATA_STR(id)      "d"
#endif
#endif

// 类型取决于配置，如闪存字节数
// 总共给spiffs文件系统（spiffs_file_system_size），
// 逻辑块大小（log_block_size）和逻辑页面大小
// （log_page_size）

// 块索引类型。确保此类型的大小可以容纳
// 所有块的最大数量，即spiffs_file_system_size/log_block_size
typedef u16_t spiffs_block_ix;
// 页面索引类型。确保此类型的大小可以容纳
// 所有页面的最高页数-即spiffs_file_system_size/log_page_size
typedef u16_t spiffs_page_ix;
// 对象id类型-最高有效位保留给索引标志。确保
// 这种类型的大小可以保持整个系统上的最高对象id，
// i、 e.2+（spiffs_file_system_size/（2*log_page_size））*2
typedef u16_t spiffs_obj_id;
// 对象跨度索引类型。确保此类型的大小可以
// 保持系统上可能的最大跨度索引-
// i、 e.（spiffs_file_system_size/log_page_size）-1
typedef u16_t spiffs_span_ix;

#endif /* SPIFFS_CONFIG_H_ */

