/* miniz。c 2.1.0-公共域deflate/膨胀、zlib子集、ZIP读取/写入/附加、PNG写入请参阅本文件末尾的“unlicense”语句。
   里奇·盖尔德里奇<richgel99@gmail.com>，最后更新于2013年10月13日实施RFC 1950：http://www.ietf.org/rfc/rfc1950.txt和RFC 1951：http://www.ietf.org/rfc/rfc1951.txt

   大多数API都是在miniz中定义的。c是可选的。例如，要禁用与存档相关的函数，只需定义MINIZ_NO_archive_APIS，或者要消除所有stdio用法，请定义MINIZ_NO_stdio（有关更多宏，请参阅下面的列表）。

   * 低水平放气/充气实施说明：

     压缩：使用“tdefl”API。压缩器支持原始、静态和动态块、懒惰或贪婪解析、匹配长度过滤、仅RLE和仅霍夫曼流。它的性能和压缩性能与zlib差不多。

     解压缩：使用“tinfl”API。整个解压器作为一个单函数协程实现：请参见tinfl_decompress（）。它支持解压到32KB（或更大的2次方）的包装缓冲区，或解压到足够容纳整个文件的内存块。

     低级tdefl/tinfl API不使用动态内存分配。

   * zlib样式API注释：

     miniz。c实现了相当大的zlib子集。在许多应用程序中，有足够的功能可以替代zlib：z_stream结构、可选内存分配回调deflateInit/deflateInit2/delate/delateReset/deflateEnd/delateBound充气机单元充气机单元膨胀充气机复位充气机结束压缩、压缩2、压缩绑定、解压缩CRC-32、Adler-32-使用现代的最小代码大小，CPU缓存友好例程。支持原始deflate流或带有adler-32检查的标准zlib流。

     限制：回调API尚未实现。不支持gzip标头或zlib静态字典。我已经尝试过密切模仿zlib的各种类型的流刷新和返回状态代码，但不能保证miniz。c完美地完成了这一点。

   * PNG编写：请参见最初由Alex Evans编写的tdefl_write_image_to_PNG_file_in_memory（）函数。支持1-4字节/像素图像。

   * ZIP存档API说明：

     ZIP存档API的设计考虑到了简单和高效，只需要足够的抽象就可以轻松完成工作。有一些简单的API用于检索文件信息、从现有存档中读取文件、创建新存档、将新文件附加到现有存档，或将存档数据从一个存档复制到另一个存档。它支持位于内存或堆、磁盘上的存档（使用stdio.h），或者您可以指定自定义文件读/写回调。

     -存档读取：只需调用此函数即可从磁盘存档读取单个文件：

      void *mz_zip_extract_archive_file_to_heap(const char*pZip_filname，const char*pArchive_name，size_t pSize，mz_uint zip_flags）；

     对于更复杂的情况，请使用“mz_zip_reader”函数。打开归档文件后，整个中央目录将被定位并按原样读取到内存中，随后的文件访问仅在读取单个文件时发生。

     -存档文件扫描：简单的方法是使用此功能扫描特定文件的加载存档：

     int mz_zip_reader_locate_file(mz_zip_archive *pZip, const char*pName、const char*pComment、mz_uint标志）；

     定位操作也可以选择检查文件注释，这（作为一个示例）可以用于标识存档中同一文件的多个版本。该函数通过中央目录使用简单的线性搜索，因此速度不是很快。

     或者，您可以遍历存档中的所有文件（使用mz_zip_reader_get_num_files（）），并通过调用mz_zip_reader_files_stat（）检索每个文件的详细信息。

     -存档创建：使用“mz_zip_writer”函数。ZIP编写器立即将压缩文件数据写入磁盘，并在内存中构建中央目录的精确映像。当归档完成时，中央目录映像将在归档文件的末尾一次性写入。

     存档写入器可以选择将每个文件的本地标头和文件数据对齐为任意2次方对齐，这在从光学介质读取存档时非常有用。此外，作者还支持在ZIP存档的开头放置任意数据块。任何ZIP工具都可以读取使用这两种功能编写的档案。

     -存档附加：将单个文件添加到存档的简单方法是调用此函数：

      mz_bool mz_zip_add_mem_to_archive_file_in_place(const char *pZip_filename, const char*pArchive_name、const void pBuf、size_t buf_size、const void pComment、mz_uint16 comment_size、mz_uint level_and_flags）；

     如果存档文件不存在，则将创建该存档文件，否则将附加到。请注意，附加是在适当的位置完成的，并且不是原子操作，因此如果操作过程中出现问题，则存档文件可能没有中央目录（尽管本地文件头和文件数据会很好，因此存档文件可以恢复）。

     对于更复杂的存档修改场景：1.最安全的方法是使用mz_zip_reader读取现有存档，使用mz_6zip_writer_add_from_zip_reder（）函数（按原样编译压缩文件数据）只将您希望保留的那些位克隆到新存档中。完成后，删除旧存档并重命名新写入的存档，就完成了。这是安全的，但需要大量临时磁盘空间或堆内存。

     2.或者，您可以使用mz_zip_writer_init_from_reader（）将mz_zip_reader就地转换为mz_zip_writer，根据需要附加新文件，然后完成归档，将更新的中心目录写入原始归档。（这基本上是mz_zip_add_mem_to_archive_file_in_place（）所做的。）但是，如果出现任何问题，使用此方法可能会丢失存档的中心目录。

     -ZIP存档支持限制：不支持zip64或跨越。提取函数只能处理未加密、存储或压缩的文件。需要能够搜索的流。

   * 这是一个头文件库，如stb_image.c。若要仅获取头文件，请剪切并粘贴下面的头，或创建miniz。h、 #define MINIZ_HEADER_FILE_ONLY，然后包含MINIZ。c从中删除。

   * 重要提示：为了获得最佳性能，请确保为您的目标平台自定义以下宏：#define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1#define MINZ_LITTLE_ENDIAN 1#define MINIZ_HAS_64BIT_REGISTERS 1

   * 在使用glibc的平台上，在包含miniz之前，请确保“#define _LARGEFILE64_SOURCE 1”。c以确保miniz使用64位变量：fopen64（）、stat64（）等。否则，您将无法处理大型文件（即，32位stat（）在文件>0x7FFFFFFF字节时失败）。
*/
#pragma once

/* Xtensa-JD的硬编码选项*/
#define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 0
#define MINIZ_LITTLE_ENDIAN 1





/* 定义为完全禁用miniz的特定部分。c： 如果定义了这里的所有宏，剩下的唯一功能将是CRC-32、adler-32、tinfl和tdefl。*/

/* 定义MINIZ_NO_STDIO以禁用所有使用和依赖STDIO进行文件I/O的任何函数。*/
#define MINIZ_NO_STDIO

/* 如果指定了MINIZ_NO_TIME，则ZIP存档函数将无法获取当前时间，或者*/
/* get/set文件时间，并且不会调用get/set时间的C运行时函数。*/
/* 目前的不利因素是，写入档案的时间将从1979年开始。*/
#define MINIZ_NO_TIME

/* 定义MINIZ_NO_ARCHIVE_PIS以禁用所有ZIP存档API。*/
#define MINIZ_NO_ARCHIVE_APIS

/* 定义MINIZ_NO_ARCHIVE_WRITING_APIS以禁用所有与写入相关的ZIP存档API。*/
#define MINIZ_NO_ARCHIVE_WRITING_APIS

/* 定义MINIZ_NO_ZLIB_APIS以删除所有ZLIB样式的压缩/解压缩API。*/
#define MINIZ_NO_ZLIB_APIS

/* 定义MINIZ_NO_ZLIB_COMPATIBLE_NAME以禁用ZLIB名称，以防止与库存ZLIB冲突。*/
#define MINIZ_NO_ZLIB_COMPATIBLE_NAMES

/* 定义MINIZ_NO_MALLOC以禁用对MALLOC、free和realloc的所有调用。请注意，如果定义了MINIZ_NO_MALLOC，则用户必须始终向zlib和存档API提供自定义用户alloc/free/realloc回调，而一些不提供自定义用户函数的独立帮助器API（如tdefl_compress_mem_to_heap（）和tinfl_decompress_mem_to_heaap（））将无法工作。*/
#define MINIZ_NO_MALLOC

#if defined(__TINYC__) && (defined(__linux) || defined(__linux__))
/* TODO:解决方法“错误：在Linux上使用tcc编译时包含文件'sys\utime.h”*/
#define MINIZ_NO_TIME
#endif

#include <stddef.h>

#if !defined(MINIZ_NO_TIME) && !defined(MINIZ_NO_ARCHIVE_APIS)
#include <time.h>
#endif

#if defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__i386) || defined(__i486__) || defined(__i486) || defined(i386) || defined(__ia64__) || defined(__x86_64__)
/* MINIZ_X86_OR_X64_CPU仅用于帮助设置以下宏。*/
#define MINIZ_X86_OR_X64_CPU 1
#else
#define MINIZ_X86_OR_X64_CPU 0
#endif

#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) || MINIZ_X86_OR_X64_CPU
/* 如果处理器为小端，则将MINIZ_LITTLE_ENDIAN设置为1。*/
#define MINIZ_LITTLE_ENDIAN 1
#else
#define MINIZ_LITTLE_ENDIAN 0
#endif

/* 仅当未设置时设置MINIZ_USE_UNALIGNED_LOADS_AND_STORES*/
#if !defined(MINIZ_USE_UNALIGNED_LOADS_AND_STORES)
#if MINIZ_X86_OR_X64_CPU
/* 在CPU上，将MINIZ_USE_UNALIGNED_LOADS_AND_STORES设置为1，以允许从未对齐的地址高效加载和存储整数。*/
#define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1
#define MINIZ_UNALIGNED_USE_MEMCPY
#else
#define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 0
#endif
#endif

#if defined(_M_X64) || defined(_WIN64) || defined(__MINGW64__) || defined(_LP64) || defined(__LP64__) || defined(__ia64__) || defined(__x86_64__)
/* 如果对64位整数的操作相当快（并且不涉及编译器生成的对帮助函数的调用），请将MINIZ_HAS_64BIT_REGISTERS设置为1。*/
#define MINIZ_HAS_64BIT_REGISTERS 1
#else
#define MINIZ_HAS_64BIT_REGISTERS 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------zlib样式的API定义。*/

/* 要获得与zlib、miniz的更多兼容性。c对某些参数/结构成员使用无符号long。注意：mz_ulong可以是32位或64位！*/
typedef unsigned long mz_ulong;

/* mz_free（）在内部使用mz_free（）宏（默认情况下调用free（），除非您修改了mz_MALLOC宏）来释放从堆中分配的块。*/
void mz_free(void *p);

#define MZ_ADLER32_INIT (1)
/* mz_aler32（）返回初始adler-32值，当使用ptr==NULL调用时使用。*/
mz_ulong mz_adler32(mz_ulong adler, const unsigned char *ptr, size_t buf_len);

#define MZ_CRC32_INIT (0)
/* mz_crc32（）返回使用ptr==NULL调用时要使用的初始CRC-32值。*/
mz_ulong mz_crc32(mz_ulong crc, const unsigned char *ptr, size_t buf_len);

/* 压缩策略。*/
enum
{
    MZ_DEFAULT_STRATEGY = 0,
    MZ_FILTERED = 1,
    MZ_HUFFMAN_ONLY = 2,
    MZ_RLE = 3,
    MZ_FIXED = 4
};

/* 方法*/
#define MZ_DEFLATED 8

/* 堆分配回调。注意，mz_alloc_func参数类型与zlib的类型完全不同：items/size是size_t，而不是无符号long。*/
typedef void *(*mz_alloc_func)(void *opaque, size_t items, size_t size);
typedef void (*mz_free_func)(void *opaque, void *address);
typedef void *(*mz_realloc_func)(void *opaque, void *address, size_t items, size_t size);

/* 压缩级别：0-9是标准zlib样式级别，10是最佳压缩级别（不兼容zlib，可能非常慢），MZ_DEFAULT_Compression=MZ_DEFAULT_LEVEL。*/
enum
{
    MZ_NO_COMPRESSION = 0,
    MZ_BEST_SPEED = 1,
    MZ_BEST_COMPRESSION = 9,
    MZ_UBER_COMPRESSION = 10,
    MZ_DEFAULT_LEVEL = 6,
    MZ_DEFAULT_COMPRESSION = -1
};

#define MZ_VERSION "10.1.0"
#define MZ_VERNUM 0xA100
#define MZ_VER_MAJOR 10
#define MZ_VER_MINOR 1
#define MZ_VER_REVISION 0
#define MZ_VER_SUBREVISION 0

#ifndef MINIZ_NO_ZLIB_APIS

/* 刷新值。对于典型用法，只需要MZ_NO_FLUSH和MZ_FINISH。其他值供高级使用（请参阅zlib文档）。*/
enum
{
    MZ_NO_FLUSH = 0,
    MZ_PARTIAL_FLUSH = 1,
    MZ_SYNC_FLUSH = 2,
    MZ_FULL_FLUSH = 3,
    MZ_FINISH = 4,
    MZ_BLOCK = 5
};

/* 返回状态代码。MZ_PARAM_ERROR是非标准的。*/
enum
{
    MZ_OK = 0,
    MZ_STREAM_END = 1,
    MZ_NEED_DICT = 2,
    MZ_ERRNO = -1,
    MZ_STREAM_ERROR = -2,
    MZ_DATA_ERROR = -3,
    MZ_MEM_ERROR = -4,
    MZ_BUF_ERROR = -5,
    MZ_VERSION_ERROR = -6,
    MZ_PARAM_ERROR = -10000
};

/* 窗口位*/
#define MZ_DEFAULT_WINDOW_BITS 15

struct mz_internal_state;

/* 压缩/解压缩流结构。*/
typedef struct mz_stream_s
{
    const unsigned char *next_in; /* 指向要读取的下一个字节的指针*/
    unsigned int avail_in;        /* next_in可用的字节数*/
    mz_ulong total_in;            /* 到目前为止消耗的总字节数*/

    unsigned char *next_out; /* 指向要写入的下一个字节的指针*/
    unsigned int avail_out;  /* 可写入next_out的字节数*/
    mz_ulong total_out;      /* 到目前为止生成的字节总数*/

    char *msg;                       /* 错误消息（未使用）*/
    struct mz_internal_state *state; /* 内部状态，由zalloc/zfree分配*/

    mz_alloc_func zalloc; /* 可选的堆分配函数（默认为malloc）*/
    mz_free_func zfree;   /* 可选的堆释放函数（默认为free）*/
    void *opaque;         /* 堆分配函数用户指针*/

    int data_type;     /* data_type（未使用）*/
    mz_ulong adler;    /* 源数据或未压缩数据的adler32*/
    mz_ulong reserved; /* 未使用*/
} mz_stream;

typedef mz_stream *mz_streamp;

/* 返回miniz.c的版本字符串。*/
const char *mz_version(void);

/* mz_deflateInit（）使用默认选项初始化压缩器：*/
/* 参数：*/
/*  pStream必须指向已初始化的mz_stream结构。*/
/*  级别必须介于[MZ_NO_COMPRESSION，MZ_BEST_COMPRESSION]之间。*/
/*  级别1启用了专门优化的压缩功能，该功能仅针对性能而非比率进行了优化。*/
/*  （此特殊功能当前仅在定义了MINIZ_USE_UNALIGNED_LOADS_AND_STORES和MINIZ_LITTLE_ENDIAN时启用。）*/
/* 返回值：*/
/*  MZ_OK成功。*/
/*  如果流是假的，则返回MZ_STREAM_ERROR。*/
/*  如果输入参数是假的，则返回MZ_PARAM_ERROR。*/
/*  内存不足时出现MZ_MEM_ERROR。*/
int mz_deflateInit(mz_streamp pStream, int level);

/* mz_deflateInit2（）与mz_deflate（）类似，但具有更多控制：*/
/* 其他参数：*/
/*   方法必须为MZ_DEFLATED*/
/*   window_bits必须是MZ_DEFAULT_window_bits（用zlib页眉/adler-32页脚包装放气流）或-MZ_DEFAULT_WINDW_bits（原始放气/无页眉或页脚）*/
/*   mem_level必须介于[1，9]之间（它已被选中，但被miniz.c忽略）*/
int mz_deflateInit2(mz_streamp pStream, int level, int method, int window_bits, int mem_level, int strategy);

/* 快速重置压缩机，无需重新分配任何内容。与调用mz_deflateEnd（）和mz_deflateInit（）/mz_deflatInit2（）相同。*/
int mz_deflateReset(mz_streamp pStream);

/* mz_deflate（）将输入压缩为输出，消耗尽可能多的输入并产生尽可能多输出。*/
/* 参数：*/
/*   pStream是要读取和写入的流。必须初始化/更新next_in、avail_in、next_out和avail_out成员。*/
/*   冲洗可以是MZ_NO_flush、MZ_PARTIAL_flush/MZ_SYNC_flush，MZ_FULL_flush或MZ_FINISH。*/
/* 返回值：*/
/*   MZ_OK成功时（刷新时，或如果需要更多输入但不可用，和/或有更多输出要写入但输出缓冲区已满）。*/
/*   MZ_STREAM_END，如果所有输入都已消耗，并且所有输出字节都已写入。不再对流调用mz_deflate（）。*/
/*   如果流是假的，则返回MZ_STREAM_ERROR。*/
/*   如果其中一个参数无效，则返回MZ_PARAM_ERROR。*/
/*   MZ_BUF_ERROR，如果由于输入和/或输出缓冲区为空而无法向前推进。（请填满输入缓冲区或释放一些输出空间，然后重试。）*/
int mz_deflate(mz_streamp pStream, int flush);

/* mz_deflateEnd（）取消初始化压缩器：*/
/* 返回值：*/
/*  MZ_OK成功。*/
/*  如果流是假的，则返回MZ_STREAM_ERROR。*/
int mz_deflateEnd(mz_streamp pStream);

/* 假设flush仅设置为mz_NO_flush或mz_FINISH，则mz_deflateBound（）返回deflate（）可能生成的数据量的（非常）保守上限。*/
mz_ulong mz_deflateBound(mz_streamp pStream, mz_ulong source_len);

/* 单次调用压缩函数mz_compress（）和mz_cocompress2（）：*/
/* 成功时返回MZ_OK，失败时返回MZ_deflate（）中的错误代码之一。*/
int mz_compress(unsigned char *pDest, mz_ulong *pDest_len, const unsigned char *pSource, mz_ulong source_len);
int mz_compress2(unsigned char *pDest, mz_ulong *pDest_len, const unsigned char *pSource, mz_ulong source_len, int level);

/* mz_compressBound（）返回一个（非常）保守的上限，该上限是通过调用mz_compless（）可以生成的数据量。*/
mz_ulong mz_compressBound(mz_ulong source_len);

/* 初始化解压缩程序。*/
int mz_inflateInit(mz_streamp pStream);

/* mz_inflateInit2（）类似于mz_inflateInit（），具有一个附加选项，用于控制窗口大小以及流是否已被zlib页眉/页脚包裹：*/
/* window_bits必须是MZ_DEFAULT_window_bits（以解析zlib页眉/页脚）或-MZ_DEFAULT_WINDW_bits（原始放气）。*/
int mz_inflateInit2(mz_streamp pStream, int window_bits);

/* 快速重置压缩机，无需重新分配任何内容。与调用mz_inflateEnd（），后跟mz_inflateInit（）/mz_inflatInit2（）相同。*/
int mz_inflateReset(mz_streamp pStream);

/* 将输入流解压缩为输出，只消耗所需的输入，并尽可能多地写入输出。*/
/* 参数：*/
/*   pStream是要读取和写入的流。必须初始化/更新next_in、avail_in、next_out和avail_out成员。*/
/*   冲洗可以是MZ_NO_flush、MZ_SYNC_flush或MZ_FINISH。*/
/*   在第一次调用时，如果flush是MZ_FINISH，则假设输入和输出缓冲区的大小都足够大，可以在一次调用中解压缩整个流（这稍微快一点）。*/
/*   MZ_FINISH意味着除了输入缓冲区中已经存在的字节之外，没有更多的源字节可用，并且输出缓冲区足够大，可以容纳剩余的解压缩数据。*/
/* 返回值：*/
/*   MZ_OK成功。需要更多的输入但不可用，和/或需要写入更多的输出但输出缓冲区已满。*/
/*   MZ_STREAM_END，如果所有所需的输入都已用完，并且所有输出字节都已写入。对于zlib流，解压缩数据的adler-32也已验证。*/
/*   如果流是假的，则返回MZ_STREAM_ERROR。*/
/*   如果放气流无效，则返回MZ_DATA_ERROR。*/
/*   如果其中一个参数无效，则返回MZ_PARAM_ERROR。*/
/*   MZ_BUF_ERROR，如果由于输入缓冲区为空，但充气机需要更多输入才能继续，或者如果输出缓冲区不够大，则无法前进。再次调用mz_inflate（）*/
/*   具有更多的输入数据，或者在输出缓冲区中具有更多的空间（除了使用如上所述的单调用解压缩时）。*/
int mz_inflate(mz_streamp pStream, int flush);

/* 取消初始化解压缩程序。*/
int mz_inflateEnd(mz_streamp pStream);

/* 单次调用解压缩。*/
/* 成功时返回MZ_OK，失败时返回MZ_inflate（）中的错误代码之一。*/
int mz_uncompress(unsigned char *pDest, mz_ulong *pDest_len, const unsigned char *pSource, mz_ulong source_len);

/* 返回指定错误代码的字符串描述，如果错误代码无效，则返回NULL。*/
const char *mz_error(int err);

/* 将zlib兼容名称重新定义为miniz等同物，因此miniz。c可以用作miniz的zlib子集的替代品。c支架。*/
/* 如果在同一项目中使用ZLIB，请定义MINIZ_NO_ZLIB_COMPATIBLE_NAME以禁用ZLIB兼容性。*/
#ifndef MINIZ_NO_ZLIB_COMPATIBLE_NAMES
typedef unsigned char Byte;
typedef unsigned int uInt;
typedef mz_ulong uLong;
typedef Byte Bytef;
typedef uInt uIntf;
typedef char charf;
typedef int intf;
typedef void *voidpf;
typedef uLong uLongf;
typedef void *voidp;
typedef void *const voidpc;
#define Z_NULL 0
#define Z_NO_FLUSH MZ_NO_FLUSH
#define Z_PARTIAL_FLUSH MZ_PARTIAL_FLUSH
#define Z_SYNC_FLUSH MZ_SYNC_FLUSH
#define Z_FULL_FLUSH MZ_FULL_FLUSH
#define Z_FINISH MZ_FINISH
#define Z_BLOCK MZ_BLOCK
#define Z_OK MZ_OK
#define Z_STREAM_END MZ_STREAM_END
#define Z_NEED_DICT MZ_NEED_DICT
#define Z_ERRNO MZ_ERRNO
#define Z_STREAM_ERROR MZ_STREAM_ERROR
#define Z_DATA_ERROR MZ_DATA_ERROR
#define Z_MEM_ERROR MZ_MEM_ERROR
#define Z_BUF_ERROR MZ_BUF_ERROR
#define Z_VERSION_ERROR MZ_VERSION_ERROR
#define Z_PARAM_ERROR MZ_PARAM_ERROR
#define Z_NO_COMPRESSION MZ_NO_COMPRESSION
#define Z_BEST_SPEED MZ_BEST_SPEED
#define Z_BEST_COMPRESSION MZ_BEST_COMPRESSION
#define Z_DEFAULT_COMPRESSION MZ_DEFAULT_COMPRESSION
#define Z_DEFAULT_STRATEGY MZ_DEFAULT_STRATEGY
#define Z_FILTERED MZ_FILTERED
#define Z_HUFFMAN_ONLY MZ_HUFFMAN_ONLY
#define Z_RLE MZ_RLE
#define Z_FIXED MZ_FIXED
#define Z_DEFLATED MZ_DEFLATED
#define Z_DEFAULT_WINDOW_BITS MZ_DEFAULT_WINDOW_BITS
#define alloc_func mz_alloc_func
#define free_func mz_free_func
#define internal_state mz_internal_state
#define z_stream mz_stream
#define deflateInit mz_deflateInit
#define deflateInit2 mz_deflateInit2
#define deflateReset mz_deflateReset
#define deflate mz_deflate
#define deflateEnd mz_deflateEnd
#define deflateBound mz_deflateBound
#define compress mz_compress
#define compress2 mz_compress2
#define compressBound mz_compressBound
#define inflateInit mz_inflateInit
#define inflateInit2 mz_inflateInit2
#define inflateReset mz_inflateReset
#define inflate mz_inflate
#define inflateEnd mz_inflateEnd
#define uncompress mz_uncompress
#define crc32 mz_crc32
#define adler32 mz_adler32
#define MAX_WBITS 15
#define MAX_MEM_LEVEL 9
#define zError mz_error
#define ZLIB_VERSION MZ_VERSION
#define ZLIB_VERNUM MZ_VERNUM
#define ZLIB_VER_MAJOR MZ_VER_MAJOR
#define ZLIB_VER_MINOR MZ_VER_MINOR
#define ZLIB_VER_REVISION MZ_VER_REVISION
#define ZLIB_VER_SUBREVISION MZ_VER_SUBREVISION
#define zlibVersion mz_version
#define zlib_version mz_version()
#endif /* #如果是MINIZ_NO_ZLIB_COMPATIBLE_NAMES*/

#endif /* MINIZ_NO_ZLIB_APIS */

#ifdef __cplusplus
}
#endif
#pragma once
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* -------------------类型和宏*/
typedef unsigned char mz_uint8;
typedef signed short mz_int16;
typedef unsigned short mz_uint16;
typedef unsigned int mz_uint32;
typedef unsigned int mz_uint;
typedef int64_t mz_int64;
typedef uint64_t mz_uint64;
typedef int mz_bool;

#define MZ_FALSE (0)
#define MZ_TRUE (1)

/* 解决MSVC的垃圾邮件“警告C4127：条件表达式是常量”消息。*/
#ifdef _MSC_VER
#define MZ_MACRO_END while (0, 0)
#else
#define MZ_MACRO_END while (0)
#endif

#ifdef MINIZ_NO_STDIO
#define MZ_FILE void *
#else
#include <stdio.h>
#define MZ_FILE FILE
#endif /* #如果定义MINIZ_NO_STDIO*/

#ifdef MINIZ_NO_TIME
typedef struct mz_dummy_time_t_tag
{
    int m_dummy;
} mz_dummy_time_t;
#define MZ_TIME_T mz_dummy_time_t
#else
#define MZ_TIME_T time_t
#endif

#define MZ_ASSERT(x)

#ifdef MINIZ_NO_MALLOC
#define MZ_MALLOC(x) NULL
#define MZ_FREE(x) (void)x, ((void)0)
#define MZ_REALLOC(p, x) NULL
#else
#define MZ_MALLOC(x) malloc(x)
#define MZ_FREE(x) free(x)
#define MZ_REALLOC(p, x) realloc(p, x)
#endif

#define MZ_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MZ_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MZ_CLEAR_OBJ(obj) memset(&(obj), 0, sizeof(obj))

#if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
#define MZ_READ_LE16(p) *((const mz_uint16 *)(p))
#define MZ_READ_LE32(p) *((const mz_uint32 *)(p))
#else
#define MZ_READ_LE16(p) ((mz_uint32)(((const mz_uint8 *)(p))[0]) | ((mz_uint32)(((const mz_uint8 *)(p))[1]) << 8U))
#define MZ_READ_LE32(p) ((mz_uint32)(((const mz_uint8 *)(p))[0]) | ((mz_uint32)(((const mz_uint8 *)(p))[1]) << 8U) | ((mz_uint32)(((const mz_uint8 *)(p))[2]) << 16U) | ((mz_uint32)(((const mz_uint8 *)(p))[3]) << 24U))
#endif

#define MZ_READ_LE64(p) (((mz_uint64)MZ_READ_LE32(p)) | (((mz_uint64)MZ_READ_LE32((const mz_uint8 *)(p) + sizeof(mz_uint32))) << 32U))

#ifdef _MSC_VER
#define MZ_FORCEINLINE __forceinline
#elif defined(__GNUC__)
#define MZ_FORCEINLINE __inline__ __attribute__((__always_inline__))
#else
#define MZ_FORCEINLINE inline
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern void *miniz_def_alloc_func(void *opaque, size_t items, size_t size);
extern void miniz_def_free_func(void *opaque, void *address);
extern void *miniz_def_realloc_func(void *opaque, void *address, size_t items, size_t size);

#define MZ_UINT16_MAX (0xFFFFU)
#define MZ_UINT32_MAX (0xFFFFFFFFU)

#ifdef __cplusplus
}
#endif
#pragma once


#ifdef __cplusplus
extern "C" {
#endif
/* -------------------低级压缩API定义*/

/* 将TDEFL_LESS_MEMORY设置为1以使用更少的内存（压缩速度会稍慢，原始/动态块的输出频率会更高）。*/
#define TDEFL_LESS_MEMORY 1

/* tdefl_init（）压缩标志逻辑“或”在一起（低12位包含每个字典搜索的最大探测数）：*/
/* TDEFL_DEFAULT_MAX_PROBES：压缩器默认为每个字典搜索128个字典探测。0=仅霍夫曼，1=霍夫曼+LZ（最快/垃圾压缩），4095=霍夫曼+IZ（最慢/最佳压缩）。*/
enum
{
    TDEFL_HUFFMAN_ONLY = 0,
    TDEFL_DEFAULT_MAX_PROBES = 128,
    TDEFL_MAX_PROBES_MASK = 0xFFF
};

/* TDEFL_WRITE_ZLIB_HEADER：如果设置，压缩器将在deflate数据之前输出ZLIB标头，并在末尾输出源数据的Adler-32。否则，您将获得原始放气数据。*/
/* TDEFL_COMPUTE_ADLER32：始终计算输入数据的adler-32（即使不写入zlib标头）。*/
/* TDEFL_GREED_PARSING_FLAG：设置为使用更快的贪婪解析，而不是更高效的懒惰解析。*/
/* TDEFL_NONDESTINITIC_PARSING_FLAG：启用以将压缩器的初始化时间减至最小，但给定相同的输入（取决于内存内容），输出可能会因运行而异。*/
/* TDEFL_RLE_MATCHES：仅查找RLE匹配（距离为1的匹配）*/
/* TDEFL_FILTER_MATCHES：如果启用，丢弃匹配<=5个字符。*/
/* TDEFL_FORCE_ALL_STATIC_BLOCKS：禁用优化霍夫曼表的使用。*/
/* TDEFL_FORCE_ALL_RAW_BLOCKS：仅使用原始（未压缩）放气块。*/
/* 低12位被保留以控制每次字典查找的最大哈希探测数（请参阅TDEFL_max_probes_MASK）。*/
enum
{
    TDEFL_WRITE_ZLIB_HEADER = 0x01000,
    TDEFL_COMPUTE_ADLER32 = 0x02000,
    TDEFL_GREEDY_PARSING_FLAG = 0x04000,
    TDEFL_NONDETERMINISTIC_PARSING_FLAG = 0x08000,
    TDEFL_RLE_MATCHES = 0x10000,
    TDEFL_FILTER_MATCHES = 0x20000,
    TDEFL_FORCE_ALL_STATIC_BLOCKS = 0x40000,
    TDEFL_FORCE_ALL_RAW_BLOCKS = 0x80000
};

/* 高级压缩功能：*/
/* tdefl_compress_mem_to_heap（）将内存中的块压缩为通过malloc（）分配的堆块。*/
/* 进入时：*/
/*  pSrc_buf，src_buf_len：要压缩的源块的指针和大小。*/
/*  flags：最大匹配查找器探测（默认值为128）与上述标志进行逻辑“或”运算。较高的探针速度较慢，但可改善压缩。*/
/* 返回时：*/
/*  函数返回指向压缩数据的指针，失败时返回NULL。*/
/*  *pOut_len将设置为压缩数据的大小，对于不可压缩数据，该大小可能大于src_buf_len。*/
/*  当不再需要时，调用者必须释放（）返回的块。*/
void *tdefl_compress_mem_to_heap(const void *pSrc_buf, size_t src_buf_len, size_t *pOut_len, int flags);

/* tdefl_compress_mem_to_mem（）将内存中的一个块压缩为内存中的另一个块。*/
/* 失败时返回0。*/
size_t tdefl_compress_mem_to_mem(void *pOut_buf, size_t out_buf_len, const void *pSrc_buf, size_t src_buf_len, int flags);

/* 将图像压缩为内存中的压缩PNG文件。*/
/* 进入时：*/
/*  pImage、w、h和num_chans描述要压缩的图像。num_chans可以是1、2、3或4。*/
/*  每个扫描线的图像间距（以字节为单位）将为w*num_chans。顶部扫描线上最左侧的像素首先存储在内存中。*/
/*  级别可以在[0,10]之间，使用MZ_NO_COMPRESSION、MZ_BEST_SPEED、MZ_BEST_COMPRESSION等，或者适当的默认值为MZ_default_level*/
/*  如果flip为true，图像将在Y轴上翻转（对OpenGL应用程序有用）。*/
/* 返回时：*/
/*  函数返回指向压缩数据的指针，失败时返回NULL。*/
/*  *pLen_out将被设置为PNG图像文件的大小。*/
/*  当不再需要时，调用者必须mz_free（）返回的堆块（通常大于*pLen_out）。*/
void *tdefl_write_image_to_png_file_in_memory_ex(const void *pImage, int w, int h, int num_chans, size_t *pLen_out, mz_uint level, mz_bool flip);
void *tdefl_write_image_to_png_file_in_memory(const void *pImage, int w, int h, int num_chans, size_t *pLen_out);

/* 输出流接口。压缩器使用此接口写入压缩数据。一次通常称为TDEFL_OUT_BUF_SIZE。*/
typedef mz_bool (*tdefl_put_buf_func_ptr)(const void *pBuf, int len, void *pUser);

/* tdefl_compress_mem_to_output（）将块压缩为输出流。上述助手在内部使用此函数。*/
mz_bool tdefl_compress_mem_to_output(const void *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, void *pPut_buf_user, int flags);

enum
{
    TDEFL_MAX_HUFF_TABLES = 3,
    TDEFL_MAX_HUFF_SYMBOLS_0 = 288,
    TDEFL_MAX_HUFF_SYMBOLS_1 = 32,
    TDEFL_MAX_HUFF_SYMBOLS_2 = 19,
    TDEFL_LZ_DICT_SIZE = (8*1024),
    TDEFL_LZ_DICT_SIZE_MASK = TDEFL_LZ_DICT_SIZE - 1,
    TDEFL_MIN_MATCH_LEN = 3,
    TDEFL_MAX_MATCH_LEN = 258
};

/* TDEFL_OUT_BUF_SIZE必须足够大，以容纳单个完整的压缩输出块（使用静态/固定霍夫曼代码）。*/
#if TDEFL_LESS_MEMORY
enum
{
    TDEFL_LZ_CODE_BUF_SIZE = 8 * 1024,
    TDEFL_OUT_BUF_SIZE = (TDEFL_LZ_CODE_BUF_SIZE * 13) / 10,
    TDEFL_MAX_HUFF_SYMBOLS = 288,
    TDEFL_LZ_HASH_BITS = 12,
    TDEFL_LEVEL1_HASH_SIZE_MASK = 4095,
    TDEFL_LZ_HASH_SHIFT = (TDEFL_LZ_HASH_BITS + 2) / 3,
    TDEFL_LZ_HASH_SIZE = 1 << TDEFL_LZ_HASH_BITS
};
#else
enum
{
    TDEFL_LZ_CODE_BUF_SIZE = 64 * 1024,
    TDEFL_OUT_BUF_SIZE = (TDEFL_LZ_CODE_BUF_SIZE * 13) / 10,
    TDEFL_MAX_HUFF_SYMBOLS = 288,
    TDEFL_LZ_HASH_BITS = 15,
    TDEFL_LEVEL1_HASH_SIZE_MASK = 4095,
    TDEFL_LZ_HASH_SHIFT = (TDEFL_LZ_HASH_BITS + 2) / 3,
    TDEFL_LZ_HASH_SIZE = 1 << TDEFL_LZ_HASH_BITS
};
#endif

/* 如果上面的帮助函数不够灵活，可以直接使用下面的低级tdefl函数。与上面的helper函数不同，低级函数不进行任何堆分配。*/
typedef enum {
    TDEFL_STATUS_BAD_PARAM = -2,
    TDEFL_STATUS_PUT_BUF_FAILED = -1,
    TDEFL_STATUS_OKAY = 0,
    TDEFL_STATUS_DONE = 1
} tdefl_status;

/* 必须映射到MZ_NO_FLUSH、MZ_SYNC_FLUSH等枚举*/
typedef enum {
    TDEFL_NO_FLUSH = 0,
    TDEFL_SYNC_FLUSH = 2,
    TDEFL_FULL_FLUSH = 3,
    TDEFL_FINISH = 4
} tdefl_flush;

/* tdefl的压缩状态结构。*/
typedef struct
{
    tdefl_put_buf_func_ptr m_pPut_buf_func;
    void *m_pPut_buf_user;
    mz_uint m_flags, m_max_probes[2];
    int m_greedy_parsing;
    mz_uint m_adler32, m_lookahead_pos, m_lookahead_size, m_dict_size;
    mz_uint8 *m_pLZ_code_buf, *m_pLZ_flags, *m_pOutput_buf, *m_pOutput_buf_end;
    mz_uint m_num_flags_left, m_total_lz_bytes, m_lz_code_buf_dict_pos, m_bits_in, m_bit_buffer;
    mz_uint m_saved_match_dist, m_saved_match_len, m_saved_lit, m_output_flush_ofs, m_output_flush_remaining, m_finished, m_block_index, m_wants_to_finish;
    tdefl_status m_prev_return_status;
    const void *m_pIn_buf;
    void *m_pOut_buf;
    size_t *m_pIn_buf_size, *m_pOut_buf_size;
    tdefl_flush m_flush;
    const mz_uint8 *m_pSrc;
    size_t m_src_buf_left, m_out_buf_ofs;
    mz_uint8 m_dict[TDEFL_LZ_DICT_SIZE + TDEFL_MAX_MATCH_LEN - 1];
    mz_uint16 m_huff_count[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
    mz_uint16 m_huff_codes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
    mz_uint8 m_huff_code_sizes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
    mz_uint8 m_lz_code_buf[TDEFL_LZ_CODE_BUF_SIZE];
    mz_uint16 m_next[TDEFL_LZ_DICT_SIZE];
    mz_uint16 m_hash[TDEFL_LZ_HASH_SIZE];
    mz_uint8 m_output_buf[TDEFL_OUT_BUF_SIZE];
} tdefl_compressor;

/* 初始化压缩器。*/
/* 没有相应的deinit（）函数，因为tdeflAPI不会动态分配内存。*/
/* pBut_buf_func：如果为NULL，则输出数据将提供给指定的回调。在这种情况下，用户应该调用tdefl_compress_buffer（）API进行压缩。*/
/* 如果pBut_buf_func为NULL，则用户应始终调用tdefl_compress（）API。*/
/* flags：请参阅以上枚举（TDEFL_HUFFMAN_ONLY、TDEFL_WRITE_ZLIB_HEADER等）*/
tdefl_status tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, void *pPut_buf_user, int flags);

/* 压缩数据块，尽可能多地消耗指定的输入缓冲区，并将尽可能多的压缩数据写入指定的输出缓冲区。*/
tdefl_status tdefl_compress(tdefl_compressor *d, const void *pIn_buf, size_t *pIn_buf_size, void *pOut_buf, size_t *pOut_buf_size, tdefl_flush flush);

/* tdefl_compress_buffer（）仅在使用非NULL tdefl_put_buf_func_ptr调用tdefl_init（）时可用。*/
/* tdefl_compress_buffer（）始终消耗整个输入缓冲区。*/
tdefl_status tdefl_compress_buffer(tdefl_compressor *d, const void *pIn_buf, size_t in_buf_size, tdefl_flush flush);

tdefl_status tdefl_get_prev_return_status(tdefl_compressor *d);
mz_uint32 tdefl_get_adler32(tdefl_compressor *d);

/* 给定zlib样式的压缩参数，创建tdefl_compress（）标志。*/
/* 级别可能在[0,10]之间（其中10是绝对最大压缩，但在某些文件上可能会慢得多）*/
/* window_bits可以是-15（原始放气）或15（zlib）*/
/* 策略可以是MZ_DEFAULT_strategy、MZ_FILTED、MZ_HUFFMAN_ONLY、MZ_RLE或MZ_FIXED*/
mz_uint tdefl_create_comp_flags_from_zip_params(int level, int window_bits, int strategy);

#ifndef MINIZ_NO_MALLOC
/* 在C中分配tdefl_compressor结构，以便*/
/* 无需担心tdefl_API的非C语言绑定*/
/* 结构规模和分配机制。*/
tdefl_compressor *tdefl_compressor_alloc(void);
void tdefl_compressor_free(tdefl_compressor *pComp);
#endif

#ifdef __cplusplus
}
#endif
#pragma once

/* -------------------低级解压缩API定义*/

#ifdef __cplusplus
extern "C" {
#endif
/* tinfl_decompress（）使用的解压缩标志。*/
/* TINFL_FLAG_PARSE_ZLIB_HEADER：如果设置，则输入具有有效的ZLIB标头，并以adler32校验和结尾（这是有效的ZLIB流）。否则，输入为原始放气流。*/
/* TINFL_FLAG_HAS_MORE_INPUT：如果设置，则在提供的输入缓冲区末尾之外有更多可用的输入字节。如果清除，则输入缓冲区包含所有剩余的输入。*/
/* TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF：如果设置，输出缓冲区足够大，可以容纳整个解压缩流。如果清除，则输出缓冲区至少为字典的大小（通常为32KB）。*/
/* TINFL_FLAG_COMPUTE_ALER32：强制对解压缩字节进行adler-32校验和计算。*/
enum
{
    TINFL_FLAG_PARSE_ZLIB_HEADER = 1,
    TINFL_FLAG_HAS_MORE_INPUT = 2,
    TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF = 4,
    TINFL_FLAG_COMPUTE_ADLER32 = 8
};

/* 高级解压缩功能：*/
/* tinfl_decompress_mem_to_heap（）将内存中的块解压缩为通过malloc（）分配的堆块。*/
/* 进入时：*/
/*  pSrc_buf，src_buf_len：要解压缩的Deflate或zlib源数据的指针和大小。*/
/* 返回时：*/
/*  函数返回指向解压缩数据的指针，失败时返回NULL。*/
/*  *pOut_len将设置为解压缩数据的大小，对于不可压缩数据，该大小可能大于src_buf_len。*/
/*  当不再需要时，调用者必须对返回的块调用mz_free（）。*/
void *tinfl_decompress_mem_to_heap(const void *pSrc_buf, size_t src_buf_len, size_t *pOut_len, int flags);

/* tinfl_decompress_mem_to_mem（）将内存中的一个块解压缩为内存中的另一个块。*/
/* 失败时返回TINFL_DECOMPRES_MEM_TO_MEM_FAILED，或成功时写入的字节数。*/
#define TINFL_DECOMPRESS_MEM_TO_MEM_FAILED ((size_t)(-1))
size_t tinfl_decompress_mem_to_mem(void *pOut_buf, size_t out_buf_len, const void *pSrc_buf, size_t src_buf_len, int flags);

/* tinfl_decompress_mem_to_callback（）将内存中的一个块解压缩到一个内部32KB缓冲区，然后将调用用户提供的回调函数来刷新缓冲区。*/
/* 成功时返回1，失败时返回0。*/
typedef int (*tinfl_put_buf_func_ptr)(const void *pBuf, int len, void *pUser);
int tinfl_decompress_mem_to_callback(const void *pIn_buf, size_t *pIn_buf_size, tinfl_put_buf_func_ptr pPut_buf_func, void *pPut_buf_user, int flags);

struct tinfl_decompressor_tag;
typedef struct tinfl_decompressor_tag tinfl_decompressor;

#ifndef MINIZ_NO_MALLOC
/* 在C中分配tinfl_decompressor结构，以便*/
/* 不需要担心tinfl_API的非C语言绑定*/
/* 结构规模和分配机制。*/
tinfl_decompressor *tinfl_decompressor_alloc(void);
void tinfl_decompressor_free(tinfl_decompressor *pDecomp);
#endif

/* LZ字典的最大大小。*/
#define TINFL_LZ_DICT_SIZE 32768

/* 返回状态。*/
typedef enum {
    /* 此标志表示充气机需要1个或多个输入字节才能前进，但调用者表示没有更多可用字节。压缩数据*/
    /* 可能已损坏。如果你用更多的字节再次调用充气机，它将尝试继续处理输入，但这是一个BAD信号（数据损坏或调用错误）。*/
    /* 如果在没有输入的情况下再次调用它，则只需再次获得TINFL_STATUS_FAILED_CANNOT_MAKE_PROGRESS。*/
    TINFL_STATUS_FAILED_CANNOT_MAKE_PROGRESS = -4,

    /* 此标志表示一个或多个输入参数明显是假的。（您可以尝试再次调用它，但如果出现此错误，则调用代码错误。）*/
    TINFL_STATUS_BAD_PARAM = -3,

    /* 此标志表示充气机已完成，但未压缩数据的adler32检查不匹配。如果再次调用它，它将返回TINFL_STATUS_DONE。*/
    TINFL_STATUS_ADLER32_MISMATCH = -2,

    /* 该标志表示充气机出现故障（错误代码、输入损坏等）。如果您再次调用它而没有通过tinfl_init（）进行重置，它将继续返回相同的状态失败代码。*/
    TINFL_STATUS_FAILED = -1,

    /* 任何小于TINFL_status_DONE的状态代码都必须表示失败。*/

    /* 此标志表示充气机已返回其所能的每个未压缩数据字节，已消耗其所需的每个字节，已成功到达放气流的结尾，并且*/
    /* 如果zlib headers和adler32检查已启用，则它已成功检查未压缩数据的adler32。如果再次调用它，则只需反复获取TINFL_STATUS_DONE。*/
    TINFL_STATUS_DONE = 0,

    /* 此标志表示充气机必须有更多的输入数据（甚至1字节），然后才能继续前进，或者您需要清除TINFL_flag_HAS_more_input*/
    /* 如果没有更多的源数据，则在下次调用时标记。如果源数据以某种方式损坏，充气机也有可能（但不太可能）继续要求输入*/
    /* 继续，因此确保正确设置TINFL_FLAG_HAS_MORE_INPUT标志。*/
    TINFL_STATUS_NEEDS_MORE_INPUT = 1,

    /* 此标志表示充气机肯定有1个或多个字节的未压缩数据可用，但它不能将这些数据写入输出缓冲区。*/
    /* 请注意，如果源压缩数据已损坏，充气机可能会向调用者返回大量未压缩数据。我一直假设您知道需要多少未压缩数据*/
    /* （准确的或最坏的情况），并将停止调用充气机，并在收到太多后失败。在您不知道需要多少字节的纯流传输场景中，这可能是不可能的*/
    /* 所以我可能需要添加一些代码来解决这个问题。*/
    TINFL_STATUS_HAS_MORE_OUTPUT = 2
} tinfl_status;

/* 将解压缩程序初始化为其初始状态。*/
#define tinfl_init(r)     \
    do                    \
    {                     \
        (r)->m_state = 0; \
    }                     \
    MZ_MACRO_END
#define tinfl_get_adler32(r) (r)->m_check_adler32

/* 主要的低级解压器协程函数。这是解压缩实际需要的唯一函数。所有其他功能都只是提高可用性的高级助手。*/
/* 这是一个通用API，即它可以用作构建任何所需的更高级别解压缩API的构建块。在极限情况下，它可以每输入或输出一个字节调用一次。*/
tinfl_status tinfl_decompress(tinfl_decompressor *r, const mz_uint8 *pIn_buf_next, size_t *pIn_buf_size, mz_uint8 *pOut_buf_start, mz_uint8 *pOut_buf_next, size_t *pOut_buf_size, const mz_uint32 decomp_flags);

/* 随后是内部/私有位。*/
enum
{
    TINFL_MAX_HUFF_TABLES = 3,
    TINFL_MAX_HUFF_SYMBOLS_0 = 288,
    TINFL_MAX_HUFF_SYMBOLS_1 = 32,
    TINFL_MAX_HUFF_SYMBOLS_2 = 19,
    TINFL_FAST_LOOKUP_BITS = 10,
    TINFL_FAST_LOOKUP_SIZE = 1 << TINFL_FAST_LOOKUP_BITS
};

typedef struct
{
    mz_uint8 m_code_size[TINFL_MAX_HUFF_SYMBOLS_0];
    mz_int16 m_look_up[TINFL_FAST_LOOKUP_SIZE], m_tree[TINFL_MAX_HUFF_SYMBOLS_0 * 2];
} tinfl_huff_table;

#if MINIZ_HAS_64BIT_REGISTERS
#define TINFL_USE_64BIT_BITBUF 1
#else
#define TINFL_USE_64BIT_BITBUF 0
#endif

#if TINFL_USE_64BIT_BITBUF
typedef mz_uint64 tinfl_bit_buf_t;
#define TINFL_BITBUF_SIZE (64)
#else
typedef mz_uint32 tinfl_bit_buf_t;
#define TINFL_BITBUF_SIZE (32)
#endif

struct tinfl_decompressor_tag
{
    mz_uint32 m_state, m_num_bits, m_zhdr0, m_zhdr1, m_z_adler32, m_final, m_type, m_check_adler32, m_dist, m_counter, m_num_extra, m_table_sizes[TINFL_MAX_HUFF_TABLES];
    tinfl_bit_buf_t m_bit_buf;
    size_t m_dist_from_out_buf_start;
    tinfl_huff_table m_tables[TINFL_MAX_HUFF_TABLES];
    mz_uint8 m_raw_header[4], m_len_codes[TINFL_MAX_HUFF_SYMBOLS_0 + TINFL_MAX_HUFF_SYMBOLS_1 + 137];
};

#ifdef __cplusplus
}
#endif

#pragma once


/* -------------------ZIP存档读取/写入*/

#ifndef MINIZ_NO_ARCHIVE_APIS

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    /* 注意：可以根据需要减少这些枚举以节省内存或堆栈空间-它们非常保守。*/
    MZ_ZIP_MAX_IO_BUF_SIZE = 64 * 1024,
    MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE = 512,
    MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_SIZE = 512
};

typedef struct
{
    /* 中央目录文件索引。*/
    mz_uint32 m_file_index;

    /* 存档中心目录中此项的字节偏移量。注意，我们目前只支持中央目录中最多UINT_MAX或更少的字节。*/
    mz_uint64 m_central_dir_ofs;

    /* 这些字段直接从zip的中心目录复制。*/
    mz_uint16 m_version_made_by;
    mz_uint16 m_version_needed;
    mz_uint16 m_bit_flag;
    mz_uint16 m_method;

#ifndef MINIZ_NO_TIME
    MZ_TIME_T m_time;
#endif

    /* 未压缩数据的CRC-32。*/
    mz_uint32 m_crc32;

    /* 文件的压缩大小。*/
    mz_uint64 m_comp_size;

    /* 文件的未压缩大小。注意，我见过一些旧的归档文件，其中目录条目的未压缩大小为512字节，但当您尝试解压缩它们时，实际上得到了0字节。*/
    mz_uint64 m_uncomp_size;

    /* Zip内部和外部文件属性。*/
    mz_uint16 m_internal_attr;
    mz_uint32 m_external_attr;

    /* 条目的本地头文件偏移量（字节）。*/
    mz_uint64 m_local_header_ofs;

    /* 注释的大小（以字节为单位）。*/
    mz_uint32 m_comment_size;

    /* MZ_TRUE（如果条目似乎是目录）。*/
    mz_bool m_is_directory;

    /* MZ_TRUE，如果条目使用加密/强加密（miniz_zip不支持）*/
    mz_bool m_is_encrypted;

    /* MZ_TRUE（如果文件未加密）、补丁文件以及使用我们支持的压缩方法。*/
    mz_bool m_is_supported;

    /* 文件名。如果字符串以“/”结尾，则为子目录条目。*/
    /* 保证为零终止，可以截断以适合。*/
    char m_filename[MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE];

    /* 注释字段。*/
    /* 保证为零终止，可以截断以适合。*/
    char m_comment[MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_SIZE];

} mz_zip_archive_file_stat;

typedef size_t (*mz_file_read_func)(void *pOpaque, mz_uint64 file_ofs, void *pBuf, size_t n);
typedef size_t (*mz_file_write_func)(void *pOpaque, mz_uint64 file_ofs, const void *pBuf, size_t n);
typedef mz_bool (*mz_file_needs_keepalive)(void *pOpaque);

struct mz_zip_internal_state_tag;
typedef struct mz_zip_internal_state_tag mz_zip_internal_state;

typedef enum {
    MZ_ZIP_MODE_INVALID = 0,
    MZ_ZIP_MODE_READING = 1,
    MZ_ZIP_MODE_WRITING = 2,
    MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED = 3
} mz_zip_mode;

typedef enum {
    MZ_ZIP_FLAG_CASE_SENSITIVE = 0x0100,
    MZ_ZIP_FLAG_IGNORE_PATH = 0x0200,
    MZ_ZIP_FLAG_COMPRESSED_DATA = 0x0400,
    MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY = 0x0800,
    MZ_ZIP_FLAG_VALIDATE_LOCATE_FILE_FLAG = 0x1000, /* 如果启用，将在每个文件经过验证时对其调用mzzip_reader_cate_file（），以确保func在中央目录中找到该文件（用于测试）*/
    MZ_ZIP_FLAG_VALIDATE_HEADERS_ONLY = 0x2000,     /* 验证本地标头，但不要解压缩整个文件并检查crc32*/
    MZ_ZIP_FLAG_WRITE_ZIP64 = 0x4000,               /* 始终使用zip64文件格式，而不是自动切换到zip64的原始zip文件格式。将作为标志参数与mz_zip_writer_init*_v2一起使用*/
    MZ_ZIP_FLAG_WRITE_ALLOW_READING = 0x8000,
    MZ_ZIP_FLAG_ASCII_FILENAME = 0x10000
} mz_zip_flags;

typedef enum {
    MZ_ZIP_TYPE_INVALID = 0,
    MZ_ZIP_TYPE_USER,
    MZ_ZIP_TYPE_MEMORY,
    MZ_ZIP_TYPE_HEAP,
    MZ_ZIP_TYPE_FILE,
    MZ_ZIP_TYPE_CFILE,
    MZ_ZIP_TOTAL_TYPES
} mz_zip_type;

/* miniz错误代码。如果添加或修改此枚举，请确保更新mz_zip_get_error_string（）。*/
typedef enum {
    MZ_ZIP_NO_ERROR = 0,
    MZ_ZIP_UNDEFINED_ERROR,
    MZ_ZIP_TOO_MANY_FILES,
    MZ_ZIP_FILE_TOO_LARGE,
    MZ_ZIP_UNSUPPORTED_METHOD,
    MZ_ZIP_UNSUPPORTED_ENCRYPTION,
    MZ_ZIP_UNSUPPORTED_FEATURE,
    MZ_ZIP_FAILED_FINDING_CENTRAL_DIR,
    MZ_ZIP_NOT_AN_ARCHIVE,
    MZ_ZIP_INVALID_HEADER_OR_CORRUPTED,
    MZ_ZIP_UNSUPPORTED_MULTIDISK,
    MZ_ZIP_DECOMPRESSION_FAILED,
    MZ_ZIP_COMPRESSION_FAILED,
    MZ_ZIP_UNEXPECTED_DECOMPRESSED_SIZE,
    MZ_ZIP_CRC_CHECK_FAILED,
    MZ_ZIP_UNSUPPORTED_CDIR_SIZE,
    MZ_ZIP_ALLOC_FAILED,
    MZ_ZIP_FILE_OPEN_FAILED,
    MZ_ZIP_FILE_CREATE_FAILED,
    MZ_ZIP_FILE_WRITE_FAILED,
    MZ_ZIP_FILE_READ_FAILED,
    MZ_ZIP_FILE_CLOSE_FAILED,
    MZ_ZIP_FILE_SEEK_FAILED,
    MZ_ZIP_FILE_STAT_FAILED,
    MZ_ZIP_INVALID_PARAMETER,
    MZ_ZIP_INVALID_FILENAME,
    MZ_ZIP_BUF_TOO_SMALL,
    MZ_ZIP_INTERNAL_ERROR,
    MZ_ZIP_FILE_NOT_FOUND,
    MZ_ZIP_ARCHIVE_TOO_LARGE,
    MZ_ZIP_VALIDATION_FAILED,
    MZ_ZIP_WRITE_CALLBACK_FAILED,
    MZ_ZIP_TOTAL_ERRORS
} mz_zip_error;

typedef struct
{
    mz_uint64 m_archive_size;
    mz_uint64 m_central_directory_file_ofs;

    /* 在zip64模式下，我们最多只支持UINT32_MAX文件。*/
    mz_uint32 m_total_files;
    mz_zip_mode m_zip_mode;
    mz_zip_type m_zip_type;
    mz_zip_error m_last_error;

    mz_uint64 m_file_offset_alignment;

    mz_alloc_func m_pAlloc;
    mz_free_func m_pFree;
    mz_realloc_func m_pRealloc;
    void *m_pAlloc_opaque;

    mz_file_read_func m_pRead;
    mz_file_write_func m_pWrite;
    mz_file_needs_keepalive m_pNeeds_keepalive;
    void *m_pIO_opaque;

    mz_zip_internal_state *m_pState;

} mz_zip_archive;

typedef struct
{
    mz_zip_archive *pZip;
    mz_uint flags;

    int status;
#ifndef MINIZ_DISABLE_ZIP_READER_CRC32_CHECKS
    mz_uint file_crc32;
#endif
    mz_uint64 read_buf_size, read_buf_ofs, read_buf_avail, comp_remaining, out_buf_ofs, cur_file_ofs;
    mz_zip_archive_file_stat file_stat;
    void *pRead_buf;
    void *pWrite_buf;

    size_t out_blk_remain;

    tinfl_decompressor inflator;

} mz_zip_reader_extract_iter_state;

/* --------ZIP读取*/

/* 初始化ZIP存档读取器。*/
/* 这些函数读取并验证存档的中心目录。*/
mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 size, mz_uint flags);

mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, const void *pMem, size_t size, mz_uint flags);

#ifndef MINIZ_NO_STDIO
/* 从磁盘文件读取存档。*/
/* file_start_ofs是存档实际开始的文件偏移量，或0。*/
/* actualarchive_size是存档的实际总大小，可能小于文件在磁盘上的实际大小。如果为零，则将整个文件视为存档。*/
mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, const char *pFilename, mz_uint32 flags);
mz_bool mz_zip_reader_init_file_v2(mz_zip_archive *pZip, const char *pFilename, mz_uint flags, mz_uint64 file_start_ofs, mz_uint64 archive_size);

/* 从当前文件位置开始，从已打开的FILE读取存档。*/
/* 假设存档文件为archive_size字节长。如果archive_size小于0，则假定文件的整个其余部分包含存档。*/
/* 调用mz_zip_reader_end（）时，FILE不会关闭。*/
mz_bool mz_zip_reader_init_cfile(mz_zip_archive *pZip, MZ_FILE *pFile, mz_uint64 archive_size, mz_uint flags);
#endif

/* 结束存档读取，释放所有分配，如果使用了mz_zip_reader_init_file（），则关闭输入存档文件。*/
mz_bool mz_zip_reader_end(mz_zip_archive *pZip);

/* --------ZIP读写*/

/* 将mz_zip_archive结构清除为全零。*/
/* 重要提示：必须在将结构传递给任何mz_zip函数之前完成此操作。*/
void mz_zip_zero_struct(mz_zip_archive *pZip);

mz_zip_mode mz_zip_get_mode(mz_zip_archive *pZip);
mz_zip_type mz_zip_get_type(mz_zip_archive *pZip);

/* 返回存档中的文件总数。*/
mz_uint mz_zip_reader_get_num_files(mz_zip_archive *pZip);

mz_uint64 mz_zip_get_archive_size(mz_zip_archive *pZip);
mz_uint64 mz_zip_get_archive_file_start_offset(mz_zip_archive *pZip);
MZ_FILE *mz_zip_get_cfile(mz_zip_archive *pZip);

/* 从文件偏移量file_ofs开始，将n字节的原始存档数据读取到pBuf。*/
size_t mz_zip_read_archive_data(mz_zip_archive *pZip, mz_uint64 file_ofs, void *pBuf, size_t n);

/* 所有mz_zip函数都在mz_zip_archive结构中设置m_last_error字段。这些函数检索/操作此字段。*/
/* 请注意，m_last_error功能不是线程安全的。*/
mz_zip_error mz_zip_set_last_error(mz_zip_archive *pZip, mz_zip_error err_num);
mz_zip_error mz_zip_peek_last_error(mz_zip_archive *pZip);
mz_zip_error mz_zip_clear_last_error(mz_zip_archive *pZip);
mz_zip_error mz_zip_get_last_error(mz_zip_archive *pZip);
const char *mz_zip_get_error_string(mz_zip_error mz_err);

/* MZ_TRUE（如果存档文件条目是目录条目）。*/
mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_index);

/* MZ_TRUE（如果文件已加密/强加密）。*/
mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_index);

/* MZ_TRUE，如果支持压缩方法，并且文件未加密，并且文件不是压缩补丁文件。*/
mz_bool mz_zip_reader_is_file_supported(mz_zip_archive *pZip, mz_uint file_index);

/* 检索存档文件项的文件名。*/
/* 返回写入pFilename的字节数，或者如果filename_buf_size为0，则此函数返回完全存储文件名所需的字节数。*/
mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_index, char *pFilename, mz_uint filename_buf_size);

/* 尝试在存档的中心目录中查找文件。*/
/* 有效标志：MZ_ZIP_FLAG_CASE_SENSITIVE、MZ_ZIP_FLAG_IGNORE_PATH*/
/* 如果找不到文件，则返回-1。*/
int mz_zip_reader_locate_file(mz_zip_archive *pZip, const char *pName, const char *pComment, mz_uint flags);
int mz_zip_reader_locate_file_v2(mz_zip_archive *pZip, const char *pName, const char *pComment, mz_uint flags, mz_uint32 *file_index);

/* 返回有关存档文件项的详细信息。*/
mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_index, mz_zip_archive_file_stat *pStat);

/* 如果文件为zip64格式，则返回MZ_TRUE。*/
/* 如果文件包含中心目录的zip64结尾标记，或者在中心目录中包含任何zip64扩展文件信息字段，则该文件被视为zip64。*/
mz_bool mz_zip_is_zip64(mz_zip_archive *pZip);

/* 返回中央目录的总大小（以字节为单位）。*/
/* 当前支持的最大大小为<=MZ_UINT32_max。*/
size_t mz_zip_get_central_dir_size(mz_zip_archive *pZip);

/* 不使用内存分配将存档文件提取到内存缓冲区。*/
/* 堆栈上必须至少有足够的空间来存储充气机的状态（约34KB）。*/
mz_bool mz_zip_reader_extract_to_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_index, void *pBuf, size_t buf_size, mz_uint flags, void *pUser_read_buf, size_t user_read_buf_size);
mz_bool mz_zip_reader_extract_file_to_mem_no_alloc(mz_zip_archive *pZip, const char *pFilename, void *pBuf, size_t buf_size, mz_uint flags, void *pUser_read_buf, size_t user_read_buf_size);

/* 将存档文件提取到内存缓冲区。*/
mz_bool mz_zip_reader_extract_to_mem(mz_zip_archive *pZip, mz_uint file_index, void *pBuf, size_t buf_size, mz_uint flags);
mz_bool mz_zip_reader_extract_file_to_mem(mz_zip_archive *pZip, const char *pFilename, void *pBuf, size_t buf_size, mz_uint flags);

/* 将存档文件提取到动态分配的堆缓冲区。*/
/* 内存将通过mz_zip_archive的alloc/realloc函数分配。*/
/* 返回NULL并设置失败时的最后一个错误。*/
void *mz_zip_reader_extract_to_heap(mz_zip_archive *pZip, mz_uint file_index, size_t *pSize, mz_uint flags);
void *mz_zip_reader_extract_file_to_heap(mz_zip_archive *pZip, const char *pFilename, size_t *pSize, mz_uint flags);

/* 使用回调函数提取存档文件以输出文件的数据。*/
mz_bool mz_zip_reader_extract_to_callback(mz_zip_archive *pZip, mz_uint file_index, mz_file_write_func pCallback, void *pOpaque, mz_uint flags);
mz_bool mz_zip_reader_extract_file_to_callback(mz_zip_archive *pZip, const char *pFilename, mz_file_write_func pCallback, void *pOpaque, mz_uint flags);

/* 迭代提取文件*/
mz_zip_reader_extract_iter_state* mz_zip_reader_extract_iter_new(mz_zip_archive *pZip, mz_uint file_index, mz_uint flags);
mz_zip_reader_extract_iter_state* mz_zip_reader_extract_file_iter_new(mz_zip_archive *pZip, const char *pFilename, mz_uint flags);
size_t mz_zip_reader_extract_iter_read(mz_zip_reader_extract_iter_state* pState, void* pvBuf, size_t buf_size);
mz_bool mz_zip_reader_extract_iter_free(mz_zip_reader_extract_iter_state* pState);

#ifndef MINIZ_NO_STDIO
/* 将存档文件提取到磁盘文件，并设置其上次访问和修改时间。*/
/* 此函数仅提取文件，而不是存档目录记录。*/
mz_bool mz_zip_reader_extract_to_file(mz_zip_archive *pZip, mz_uint file_index, const char *pDst_filename, mz_uint flags);
mz_bool mz_zip_reader_extract_file_to_file(mz_zip_archive *pZip, const char *pArchive_filename, const char *pDst_filename, mz_uint flags);

/* 从目标file流中的当前位置开始提取存档文件。*/
mz_bool mz_zip_reader_extract_to_cfile(mz_zip_archive *pZip, mz_uint file_index, MZ_FILE *File, mz_uint flags);
mz_bool mz_zip_reader_extract_file_to_cfile(mz_zip_archive *pZip, const char *pArchive_filename, MZ_FILE *pFile, mz_uint flags);
#endif

#if 0
/* TODO */
	typedef void *mz_zip_streaming_extract_state_ptr;
	mz_zip_streaming_extract_state_ptr mz_zip_streaming_extract_begin(mz_zip_archive *pZip, mz_uint file_index, mz_uint flags);
	uint64_t mz_zip_streaming_extract_get_size(mz_zip_archive *pZip, mz_zip_streaming_extract_state_ptr pState);
	uint64_t mz_zip_streaming_extract_get_cur_ofs(mz_zip_archive *pZip, mz_zip_streaming_extract_state_ptr pState);
	mz_bool mz_zip_streaming_extract_seek(mz_zip_archive *pZip, mz_zip_streaming_extract_state_ptr pState, uint64_t new_ofs);
	size_t mz_zip_streaming_extract_read(mz_zip_archive *pZip, mz_zip_streaming_extract_state_ptr pState, void *pBuf, size_t buf_size);
	mz_bool mz_zip_streaming_extract_end(mz_zip_archive *pZip, mz_zip_streaming_extract_state_ptr pState);
#endif

/* 此函数比较存档的本地标头、可选的本地zip64扩展信息块以及压缩数据后的可选描述符与中央目录中的数据。*/
/* 它还验证每个文件是否可以成功解压缩，除非指定了MZ_ZIP_FLAG_VALIDATE_HEADERS_ONLY。*/
mz_bool mz_zip_validate_file(mz_zip_archive *pZip, mz_uint file_index, mz_uint flags);

/* 通过对每个文件调用mz_zip_validate_file（）来验证整个存档。*/
mz_bool mz_zip_validate_archive(mz_zip_archive *pZip, mz_uint flags);

/* 其他实用程序/助手，适用于ZIP读写*/
mz_bool mz_zip_validate_mem_archive(const void *pMem, size_t size, mz_uint flags, mz_zip_error *pErr);
mz_bool mz_zip_validate_file_archive(const char *pFilename, mz_uint flags, mz_zip_error *pErr);

/* 通用结束函数-调用mz_zip_reader_end（）或mz_zip_writer_end（）。*/
mz_bool mz_zip_end(mz_zip_archive *pZip);

/* --------ZIP写入*/

#ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

/* 初始化ZIP存档编写器。*/
/*在调用mz_zip_writer_init或mz_zip_writer_init_v2之前，设置pZip->m_pWrite（和pZip->mpIO_oopaque）*/
/*输出是可流式的，即mz_file_write_func中的file_ofs始终只增加n*/
mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_size);
mz_bool mz_zip_writer_init_v2(mz_zip_archive *pZip, mz_uint64 existing_size, mz_uint flags);

mz_bool mz_zip_writer_init_heap(mz_zip_archive *pZip, size_t size_to_reserve_at_beginning, size_t initial_allocation_size);
mz_bool mz_zip_writer_init_heap_v2(mz_zip_archive *pZip, size_t size_to_reserve_at_beginning, size_t initial_allocation_size, mz_uint flags);

#ifndef MINIZ_NO_STDIO
mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, const char *pFilename, mz_uint64 size_to_reserve_at_beginning);
mz_bool mz_zip_writer_init_file_v2(mz_zip_archive *pZip, const char *pFilename, mz_uint64 size_to_reserve_at_beginning, mz_uint flags);
mz_bool mz_zip_writer_init_cfile(mz_zip_archive *pZip, MZ_FILE *pFile, mz_uint flags);
#endif

/* 将ZIP存档读取器对象转换为写入器对象，以允许对现有存档进行有效的就地文件附加。*/
/* 对于使用mz_zip_reader_init_file打开的归档文件，pFilename必须是归档文件的文件名，以便可以重新打开进行写入。如果无法重新打开文件，将调用mz_zip_reader_end（）。*/
/* 对于使用mz_zip_reader_init_mem打开的存档，内存块必须使用realloc回调（默认为realloc，除非您已覆盖它）来增长。*/
/* 最后，对于使用mz_zip_reader_init打开的存档，mz_zip_archive的用户提供的m_pWrite函数不能为NULL。*/
/* 注意：除非您知道自己在做什么，否则不建议修改就地存档，因为如果执行停止或之前出现问题*/
/* 存档完成后，文件的中心目录将被删除。*/
mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, const char *pFilename);
mz_bool mz_zip_writer_init_from_reader_v2(mz_zip_archive *pZip, const char *pFilename, mz_uint flags);

/* 将内存缓冲区的内容添加到存档中。这些函数将当前本地时间记录到存档中。*/
/* 若要添加目录条目，请使用以正斜杠结尾的存档名称和空缓冲区调用此方法。*/
/* level_and_flags—压缩级别（0-10，请参见MZ_BEST_SPEED、MZ_BEST_compression等）与零个或多个MZ_zip_flags逻辑“或”，或仅设置为MZ_DEFAULT_COMPRESION。*/
mz_bool mz_zip_writer_add_mem(mz_zip_archive *pZip, const char *pArchive_name, const void *pBuf, size_t buf_size, mz_uint level_and_flags);

/* 与mz_zip_writer_add_mem（）类似，不同的是您可以指定文件注释字段，并可选地为函数提供已压缩的数据。*/
/* 仅当指定了MZ_ZIP_FLAG_COMPRESSED_DATA标志时，才使用uncomp_size/uncomp_crc32。*/
mz_bool mz_zip_writer_add_mem_ex(mz_zip_archive *pZip, const char *pArchive_name, const void *pBuf, size_t buf_size, const void *pComment, mz_uint16 comment_size, mz_uint level_and_flags,
                                 mz_uint64 uncomp_size, mz_uint32 uncomp_crc32);

mz_bool mz_zip_writer_add_mem_ex_v2(mz_zip_archive *pZip, const char *pArchive_name, const void *pBuf, size_t buf_size, const void *pComment, mz_uint16 comment_size, mz_uint level_and_flags,
                                    mz_uint64 uncomp_size, mz_uint32 uncomp_crc32, MZ_TIME_T *last_modified, const char *user_extra_data_local, mz_uint user_extra_data_local_len,
                                    const char *user_extra_data_central, mz_uint user_extra_data_central_len);

/* 将文件内容添加到存档中。此函数还将磁盘文件的修改时间记录到存档中。*/
/* 文件数据通过读取回调函数提供。使用mz_zip_writer_add_（c）文件直接添加文件。*/
mz_bool mz_zip_writer_add_read_buf_callback(mz_zip_archive *pZip, const char *pArchive_name, mz_file_read_func read_callback, void* callback_opaque, mz_uint64 size_to_add,
	const MZ_TIME_T *pFile_time, const void *pComment, mz_uint16 comment_size, mz_uint level_and_flags, const char *user_extra_data_local, mz_uint user_extra_data_local_len,
	const char *user_extra_data_central, mz_uint user_extra_data_central_len);

#ifndef MINIZ_NO_STDIO
/* 将磁盘文件的内容添加到存档中。此函数还将磁盘文件的修改时间记录到存档中。*/
/* level_and_flags—压缩级别（0-10，请参见MZ_BEST_SPEED、MZ_BEST_compression等）与零个或多个MZ_zip_flags逻辑“或”，或仅设置为MZ_DEFAULT_COMPRESION。*/
mz_bool mz_zip_writer_add_file(mz_zip_archive *pZip, const char *pArchive_name, const char *pSrc_filename, const void *pComment, mz_uint16 comment_size, mz_uint level_and_flags);

/* 与mz_zip_writer_add_file（）类似，除了从指定的file流读取文件数据。*/
mz_bool mz_zip_writer_add_cfile(mz_zip_archive *pZip, const char *pArchive_name, MZ_FILE *pSrc_file, mz_uint64 size_to_add,
                                const MZ_TIME_T *pFile_time, const void *pComment, mz_uint16 comment_size, mz_uint level_and_flags, const char *user_extra_data_local, mz_uint user_extra_data_local_len,
                                const char *user_extra_data_central, mz_uint user_extra_data_central_len);
#endif

/* 通过从另一个存档中完全克隆数据，将文件添加到存档中。*/
/* 此函数完全克隆源文件的压缩数据（无需重新压缩）、完整文件名、额外数据（它可以添加或修改zip64本地头额外数据字段）以及压缩数据后面的可选描述符。*/
mz_bool mz_zip_writer_add_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *pSource_zip, mz_uint src_file_index);

/* 通过写入中央目录记录，然后是中央目录记录的结尾来完成归档。*/
/* 归档完成后，对mz_zip_archive结构的唯一有效调用是mz_zip_writer_end（）。*/
/* 存档必须通过调用此函数手动完成才能生效。*/
mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip);

/* 完成堆存档，返回堆块及其大小。*/
/* 堆块将使用mz_zip_archive的alloc/realloc回调进行分配。*/
mz_bool mz_zip_writer_finalize_heap_archive(mz_zip_archive *pZip, void **ppBuf, size_t *pSize);

/* 结束存档写入，释放所有分配，如果使用了mz_zip_writer_init_file（），则关闭输出文件。*/
/* 请注意，要使存档有效，它必须*在结束前已完成（此功能不会为您完成）。*/
mz_bool mz_zip_writer_end(mz_zip_archive *pZip);

/* --------其他。高级助手函数：*/

/* mz_zip_add_mem_to_archive_file_in_place（）有效地（但不是原子地）将内存blob附加到zip存档。*/
/* 注意，这不是完全安全的操作。如果它以某种方式崩溃或消亡，您的存档可能会处于错误状态（没有中央目录）。*/
/* level_and_flags—压缩级别（0-10，请参见MZ_BEST_SPEED、MZ_BEST_compression等）与零个或多个MZ_zip_flags逻辑“或”，或仅设置为MZ_DEFAULT_COMPRESION。*/
/* TODO:也许添加一个选项，以便在添加失败的情况下保留现有的中央目录？如果出现问题，我们可以截断文件（这样旧的中央目录将位于末尾）。*/
mz_bool mz_zip_add_mem_to_archive_file_in_place(const char *pZip_filename, const char *pArchive_name, const void *pBuf, size_t buf_size, const void *pComment, mz_uint16 comment_size, mz_uint level_and_flags);
mz_bool mz_zip_add_mem_to_archive_file_in_place_v2(const char *pZip_filename, const char *pArchive_name, const void *pBuf, size_t buf_size, const void *pComment, mz_uint16 comment_size, mz_uint level_and_flags, mz_zip_error *pErr);

/* 将单个文件从归档文件读取到堆块中。*/
/* 如果pComment不为NULL，则只提取具有指定注释的文件。*/
/* 失败时返回NULL。*/
void *mz_zip_extract_archive_file_to_heap(const char *pZip_filename, const char *pArchive_name, size_t *pSize, mz_uint flags);
void *mz_zip_extract_archive_file_to_heap_v2(const char *pZip_filename, const char *pArchive_name, const char *pComment, size_t *pSize, mz_uint flags, mz_zip_error *pErr);

#endif /* #如果是MINIZ_NO_ARCHIVE_WRITING_APIS*/

#ifdef __cplusplus
}
#endif

#endif /* MINIZ_NO_ARCHIVE_APIS */

