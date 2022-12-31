#ifndef MINIZ_HEADER_INCLUDED
#define MINIZ_HEADER_INCLUDED

#include <stdlib.h>

// 定义为完全禁用miniz.c的特定部分：
// 如果定义了这里的所有宏，剩下的唯一功能将是CRC-32、adler-32、tinfl和tdefl。

// 定义MINIZ_NO_STDIO以禁用所有使用和依赖STDIO进行文件I/O的任何函数。
#define MINIZ_NO_STDIO

// 如果指定了MINIZ_NO_TIME，则ZIP存档函数将无法获取当前时间，或者
// get/set文件时间，并且不会调用get/set时间的C运行时函数。
// 目前的不利因素是，写入档案的时间将从1979年开始。
#define MINIZ_NO_TIME

// 定义MINIZ_NO_ARCHIVE_PIS以禁用所有ZIP存档API。
#define MINIZ_NO_ARCHIVE_APIS

// 定义MINIZ_NO_ARCHIVE_APIS以禁用所有与写入相关的ZIP存档API。
#define MINIZ_NO_ARCHIVE_WRITING_APIS

// 定义MINIZ_NO_ZLIB_APIS以删除所有ZLIB样式的压缩/解压缩API。
#define MINIZ_NO_ZLIB_APIS

// 定义MINIZ_NO_ZLIB_COMPATIBLE_NAME以禁用ZLIB名称，以防止与库存ZLIB冲突。
#define MINIZ_NO_ZLIB_COMPATIBLE_NAMES

// 定义MINIZ_NO_MALLOC以禁用对MALLOC、free和realloc的所有调用。
// 注意，如果定义了MINIZ_NO_MALLOC，则用户必须始终提供自定义用户alloc/free/realloc
// 对zlib和归档API的回调，以及一些不提供自定义用户的独立助手API
// 函数（如tdefl_compress_mem_to_heap（）和tinfl_decompress_mem_to_heaap（））将无法工作。
#define MINIZ_NO_MALLOC

#if defined(__TINYC__) && (defined(__linux) || defined(__linux__))
  // TODO:解决方法“错误：在Linux上使用tcc编译时包含文件'sys\utime.h”
  #define MINIZ_NO_TIME
#endif

#if !defined(MINIZ_NO_TIME) && !defined(MINIZ_NO_ARCHIVE_APIS)
  #include <time.h>
#endif

//Xtensa-JD的硬编码选项
#define MINIZ_X86_OR_X64_CPU 0
#define MINIZ_LITTLE_ENDIAN 1
#define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 0
#define MINIZ_HAS_64BIT_REGISTERS 0
#define TINFL_USE_64BIT_BITBUF 0


#if defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__i386) || defined(__i486__) || defined(__i486) || defined(i386) || defined(__ia64__) || defined(__x86_64__)
// MINIZ_X86_OR_X64_CPU仅用于帮助设置以下宏。
#define MINIZ_X86_OR_X64_CPU 1
#endif

#if (__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__) || MINIZ_X86_OR_X64_CPU
// 如果处理器为小端，则将MINIZ_LITTLE_ENDIAN设置为1。
#define MINIZ_LITTLE_ENDIAN 1
#endif

#if MINIZ_X86_OR_X64_CPU
// 在CPU上，将MINIZ_USE_UNALIGNED_LOADS_AND_STORES设置为1，以允许从未对齐的地址高效加载和存储整数。
#define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1
#endif

#if defined(_M_X64) || defined(_WIN64) || defined(__MINGW64__) || defined(_LP64) || defined(__LP64__) || defined(__ia64__) || defined(__x86_64__)
// 如果对64位整数的操作相当快（并且不涉及编译器生成的对帮助函数的调用），请将MINIZ_HAS_64BIT_REGISTERS设置为1。
#define MINIZ_HAS_64BIT_REGISTERS 1
#endif

#ifdef __cplusplus
extern "C" {
#endif

// -------------------zlib样式的API定义。

// 为了与zlib更兼容，miniz.c对某些参数/结构成员使用无符号long。注意：mz_ulong可以是32位或64位！
typedef unsigned long mz_ulong;

// mz_free（）在内部使用mz_free（）宏（默认情况下调用free（），除非您修改了mz_MALLOC宏）来释放从堆中分配的块。
void mz_free(void *p);

#define MZ_ADLER32_INIT (1)
// mz_aler32（）返回初始adler-32值，当使用ptr==NULL调用时使用。
mz_ulong mz_adler32(mz_ulong adler, const unsigned char *ptr, size_t buf_len);

#define MZ_CRC32_INIT (0)
// mz_crc32（）返回使用ptr==NULL调用时要使用的初始CRC-32值。
mz_ulong mz_crc32(mz_ulong crc, const unsigned char *ptr, size_t buf_len);

// 压缩策略。
enum { MZ_DEFAULT_STRATEGY = 0, MZ_FILTERED = 1, MZ_HUFFMAN_ONLY = 2, MZ_RLE = 3, MZ_FIXED = 4 };

// 方法
#define MZ_DEFLATED 8

#ifndef MINIZ_NO_ZLIB_APIS

// 堆分配回调。
// 注意，mz_alloc_func参数类型与zlib的类型完全不同：items/size是size_t，而不是无符号long。
typedef void *(*mz_alloc_func)(void *opaque, size_t items, size_t size);
typedef void (*mz_free_func)(void *opaque, void *address);
typedef void *(*mz_realloc_func)(void *opaque, void *address, size_t items, size_t size);

#define MZ_VERSION          "9.1.15"
#define MZ_VERNUM           0x91F0
#define MZ_VER_MAJOR        9
#define MZ_VER_MINOR        1
#define MZ_VER_REVISION     15
#define MZ_VER_SUBREVISION  0

// 刷新值。对于典型用法，只需要MZ_NO_FLUSH和MZ_FINISH。其他值供高级使用（请参阅zlib文档）。
enum { MZ_NO_FLUSH = 0, MZ_PARTIAL_FLUSH = 1, MZ_SYNC_FLUSH = 2, MZ_FULL_FLUSH = 3, MZ_FINISH = 4, MZ_BLOCK = 5 };

// 返回状态代码。MZ_PARAM_ERROR是非标准的。
enum { MZ_OK = 0, MZ_STREAM_END = 1, MZ_NEED_DICT = 2, MZ_ERRNO = -1, MZ_STREAM_ERROR = -2, MZ_DATA_ERROR = -3, MZ_MEM_ERROR = -4, MZ_BUF_ERROR = -5, MZ_VERSION_ERROR = -6, MZ_PARAM_ERROR = -10000 };

// 压缩级别：0-9是标准zlib样式级别，10是最佳压缩级别（不兼容zlib，可能非常慢），MZ_DEFAULT_Compression=MZ_DEFAULT_LEVEL。
enum { MZ_NO_COMPRESSION = 0, MZ_BEST_SPEED = 1, MZ_BEST_COMPRESSION = 9, MZ_UBER_COMPRESSION = 10, MZ_DEFAULT_LEVEL = 6, MZ_DEFAULT_COMPRESSION = -1 };

// 窗口位
#define MZ_DEFAULT_WINDOW_BITS 15

struct mz_internal_state;

// 压缩/解压缩流结构。
typedef struct mz_stream_s
{
  const unsigned char *next_in;     // 指向要读取的下一个字节的指针
  unsigned int avail_in;            // next_in可用的字节数
  mz_ulong total_in;                // 到目前为止消耗的总字节数

  unsigned char *next_out;          // 指向要写入的下一个字节的指针
  unsigned int avail_out;           // 可写入next_out的字节数
  mz_ulong total_out;               // 到目前为止生成的字节总数

  char *msg;                        // 错误消息（未使用）
  struct mz_internal_state *state;  // 内部状态，由zalloc/zfree分配

  mz_alloc_func zalloc;             // 可选的堆分配函数（默认为malloc）
  mz_free_func zfree;               // 可选的堆释放函数（默认为free）
  void *opaque;                     // 堆分配函数用户指针

  int data_type;                    // data_type（未使用）
  mz_ulong adler;                   // 源数据或未压缩数据的adler32
  mz_ulong reserved;                // 未使用
} mz_stream;

typedef mz_stream *mz_streamp;

// 返回miniz.c的版本字符串。
const char *mz_version(void);

// mz_deflateInit（）使用默认选项初始化压缩器：
// 参数：
//  pStream必须指向已初始化的mz_stream结构。
//  级别必须介于[MZ_NO_COMPRESSION，MZ_BEST_COMPRESSION]之间。
//  级别1启用了专门优化的压缩功能，该功能仅针对性能而非比率进行了优化。
//  （此特殊功能当前仅在定义了MINIZ_USE_UNALIGNED_LOADS_AND_STORES和MINIZ_LITTLE_ENDIAN时启用。）
// 返回值：
//  MZ_OK成功。
//  如果流是假的，则返回MZ_STREAM_ERROR。
//  如果输入参数是假的，则返回MZ_PARAM_ERROR。
//  内存不足时出现MZ_MEM_ERROR。
int mz_deflateInit(mz_streamp pStream, int level);

// mz_deflateInit2（）与mz_deflate（）类似，但具有更多控制：
// 其他参数：
//   方法必须为MZ_DEFLATED
//   window_bits必须是MZ_DEFAULT_window_bits（用zlib页眉/adler-32页脚包装放气流）或-MZ_DEFAULT_WINDW_bits（原始放气/无页眉或页脚）
//   mem_level必须介于[1，9]之间（它已被选中，但被miniz.c忽略）
int mz_deflateInit2(mz_streamp pStream, int level, int method, int window_bits, int mem_level, int strategy);

// 快速重置压缩机，无需重新分配任何内容。与调用mz_deflateEnd（）和mz_deflateInit（）/mz_deflatInit2（）相同。
int mz_deflateReset(mz_streamp pStream);

// mz_deflate（）将输入压缩为输出，消耗尽可能多的输入并产生尽可能多输出。
// 参数：
//   pStream是要读取和写入的流。必须初始化/更新next_in、avail_in、next_out和avail_out成员。
//   冲洗可以是MZ_NO_flush、MZ_PARTIAL_flush/MZ_SYNC_flush，MZ_FULL_flush或MZ_FINISH。
// 返回值：
//   MZ_OK成功时（刷新时，或如果需要更多输入但不可用，和/或有更多输出要写入但输出缓冲区已满）。
//   MZ_STREAM_END，如果所有输入都已消耗，并且所有输出字节都已写入。不再对流调用mz_deflate（）。
//   如果流是假的，则返回MZ_STREAM_ERROR。
//   如果其中一个参数无效，则返回MZ_PARAM_ERROR。
//   MZ_BUF_ERROR，如果由于输入和/或输出缓冲区为空而无法向前推进。（请填满输入缓冲区或释放一些输出空间，然后重试。）
int mz_deflate(mz_streamp pStream, int flush);

// mz_deflateEnd（）取消初始化压缩器：
// 返回值：
//  MZ_OK成功。
//  如果流是假的，则返回MZ_STREAM_ERROR。
int mz_deflateEnd(mz_streamp pStream);

// 假设flush仅设置为mz_NO_flush或mz_FINISH，则mz_deflateBound（）返回deflate（）可能生成的数据量的（非常）保守上限。
mz_ulong mz_deflateBound(mz_streamp pStream, mz_ulong source_len);

// 单次调用压缩函数mz_compress（）和mz_cocompress2（）：
// 成功时返回MZ_OK，失败时返回MZ_deflate（）中的错误代码之一。
int mz_compress(unsigned char *pDest, mz_ulong *pDest_len, const unsigned char *pSource, mz_ulong source_len);
int mz_compress2(unsigned char *pDest, mz_ulong *pDest_len, const unsigned char *pSource, mz_ulong source_len, int level);

// mz_compressBound（）返回一个（非常）保守的上限，该上限是通过调用mz_compless（）可以生成的数据量。
mz_ulong mz_compressBound(mz_ulong source_len);

// 初始化解压缩程序。
int mz_inflateInit(mz_streamp pStream);

// mz_inflateInit2（）类似于mz_inflateInit（），具有一个附加选项，用于控制窗口大小以及流是否已被zlib页眉/页脚包裹：
// window_bits必须是MZ_DEFAULT_window_bits（以解析zlib页眉/页脚）或-MZ_DEFAULT_WINDW_bits（原始放气）。
int mz_inflateInit2(mz_streamp pStream, int window_bits);

// 将输入流解压缩为输出，只消耗所需的输入，并尽可能多地写入输出。
// 参数：
//   pStream是要读取和写入的流。必须初始化/更新next_in、avail_in、next_out和avail_out成员。
//   冲洗可以是MZ_NO_flush、MZ_SYNC_flush或MZ_FINISH。
//   在第一次调用时，如果flush是MZ_FINISH，则假设输入和输出缓冲区的大小都足够大，可以在一次调用中解压缩整个流（这稍微快一点）。
//   MZ_FINISH意味着除了输入缓冲区中已经存在的字节之外，没有更多的源字节可用，并且输出缓冲区足够大，可以容纳剩余的解压缩数据。
// 返回值：
//   MZ_OK成功。需要更多的输入但不可用，和/或需要写入更多的输出但输出缓冲区已满。
//   MZ_STREAM_END，如果所有所需的输入都已用完，并且所有输出字节都已写入。对于zlib流，解压缩数据的adler-32也已验证。
//   如果流是假的，则返回MZ_STREAM_ERROR。
//   如果放气流无效，则返回MZ_DATA_ERROR。
//   如果其中一个参数无效，则返回MZ_PARAM_ERROR。
//   MZ_BUF_ERROR，如果由于输入缓冲区为空，但充气机需要更多输入才能继续，或者如果输出缓冲区不够大，则无法前进。再次调用mz_inflate（）
//   具有更多的输入数据，或者在输出缓冲区中具有更多的空间（除了使用如上所述的单调用解压缩时）。
int mz_inflate(mz_streamp pStream, int flush);

// 取消初始化解压缩程序。
int mz_inflateEnd(mz_streamp pStream);

// 单次调用解压缩。
// 成功时返回MZ_OK，失败时返回MZ_inflate（）中的错误代码之一。
int mz_uncompress(unsigned char *pDest, mz_ulong *pDest_len, const unsigned char *pSource, mz_ulong source_len);

// 返回指定错误代码的字符串描述，如果错误代码无效，则返回NULL。
const char *mz_error(int err);

// 将zlib兼容名称重新定义为miniz等同物，因此miniz。c可以用作miniz的zlib子集的替代品。c支架。
// 如果在同一项目中使用ZLIB，请定义MINIZ_NO_ZLIB_COMPATIBLE_NAME以禁用ZLIB兼容性。
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
  #define Z_NULL                0
  #define Z_NO_FLUSH            MZ_NO_FLUSH
  #define Z_PARTIAL_FLUSH       MZ_PARTIAL_FLUSH
  #define Z_SYNC_FLUSH          MZ_SYNC_FLUSH
  #define Z_FULL_FLUSH          MZ_FULL_FLUSH
  #define Z_FINISH              MZ_FINISH
  #define Z_BLOCK               MZ_BLOCK
  #define Z_OK                  MZ_OK
  #define Z_STREAM_END          MZ_STREAM_END
  #define Z_NEED_DICT           MZ_NEED_DICT
  #define Z_ERRNO               MZ_ERRNO
  #define Z_STREAM_ERROR        MZ_STREAM_ERROR
  #define Z_DATA_ERROR          MZ_DATA_ERROR
  #define Z_MEM_ERROR           MZ_MEM_ERROR
  #define Z_BUF_ERROR           MZ_BUF_ERROR
  #define Z_VERSION_ERROR       MZ_VERSION_ERROR
  #define Z_PARAM_ERROR         MZ_PARAM_ERROR
  #define Z_NO_COMPRESSION      MZ_NO_COMPRESSION
  #define Z_BEST_SPEED          MZ_BEST_SPEED
  #define Z_BEST_COMPRESSION    MZ_BEST_COMPRESSION
  #define Z_DEFAULT_COMPRESSION MZ_DEFAULT_COMPRESSION
  #define Z_DEFAULT_STRATEGY    MZ_DEFAULT_STRATEGY
  #define Z_FILTERED            MZ_FILTERED
  #define Z_HUFFMAN_ONLY        MZ_HUFFMAN_ONLY
  #define Z_RLE                 MZ_RLE
  #define Z_FIXED               MZ_FIXED
  #define Z_DEFLATED            MZ_DEFLATED
  #define Z_DEFAULT_WINDOW_BITS MZ_DEFAULT_WINDOW_BITS
  #define alloc_func            mz_alloc_func
  #define free_func             mz_free_func
  #define internal_state        mz_internal_state
  #define z_stream              mz_stream
  #define deflateInit           mz_deflateInit
  #define deflateInit2          mz_deflateInit2
  #define deflateReset          mz_deflateReset
  #define deflate               mz_deflate
  #define deflateEnd            mz_deflateEnd
  #define deflateBound          mz_deflateBound
  #define compress              mz_compress
  #define compress2             mz_compress2
  #define compressBound         mz_compressBound
  #define inflateInit           mz_inflateInit
  #define inflateInit2          mz_inflateInit2
  #define inflate               mz_inflate
  #define inflateEnd            mz_inflateEnd
  #define uncompress            mz_uncompress
  #define crc32                 mz_crc32
  #define adler32               mz_adler32
  #define MAX_WBITS             15
  #define MAX_MEM_LEVEL         9
  #define zError                mz_error
  #define ZLIB_VERSION          MZ_VERSION
  #define ZLIB_VERNUM           MZ_VERNUM
  #define ZLIB_VER_MAJOR        MZ_VER_MAJOR
  #define ZLIB_VER_MINOR        MZ_VER_MINOR
  #define ZLIB_VER_REVISION     MZ_VER_REVISION
  #define ZLIB_VER_SUBREVISION  MZ_VER_SUBREVISION
  #define zlibVersion           mz_version
  #define zlib_version          mz_version()
#endif // #如果是MINIZ_NO_ZLIB_COMPATIBLE_NAMES

#endif // MINIZ_NO_ZLIB_APIS

// -------------------类型和宏

typedef unsigned char mz_uint8;
typedef signed short mz_int16;
typedef unsigned short mz_uint16;
typedef unsigned int mz_uint32;
typedef unsigned int mz_uint;
typedef long long mz_int64;
typedef unsigned long long mz_uint64;
typedef int mz_bool;

#define MZ_FALSE (0)
#define MZ_TRUE (1)

// 试图解决MSVC的垃圾邮件“警告C4127：条件表达式是常量”消息。
#ifdef _MSC_VER
   #define MZ_MACRO_END while (0, 0)
#else
   #define MZ_MACRO_END while (0)
#endif

// -------------------ZIP存档读取/写入

#ifndef MINIZ_NO_ARCHIVE_APIS

enum
{
  MZ_ZIP_MAX_IO_BUF_SIZE = 64*1024,
  MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE = 260,
  MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_SIZE = 256
};

typedef struct
{
  mz_uint32 m_file_index;
  mz_uint32 m_central_dir_ofs;
  mz_uint16 m_version_made_by;
  mz_uint16 m_version_needed;
  mz_uint16 m_bit_flag;
  mz_uint16 m_method;
#ifndef MINIZ_NO_TIME
  time_t m_time;
#endif
  mz_uint32 m_crc32;
  mz_uint64 m_comp_size;
  mz_uint64 m_uncomp_size;
  mz_uint16 m_internal_attr;
  mz_uint32 m_external_attr;
  mz_uint64 m_local_header_ofs;
  mz_uint32 m_comment_size;
  char m_filename[MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE];
  char m_comment[MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_SIZE];
} mz_zip_archive_file_stat;

typedef size_t (*mz_file_read_func)(void *pOpaque, mz_uint64 file_ofs, void *pBuf, size_t n);
typedef size_t (*mz_file_write_func)(void *pOpaque, mz_uint64 file_ofs, const void *pBuf, size_t n);

struct mz_zip_internal_state_tag;
typedef struct mz_zip_internal_state_tag mz_zip_internal_state;

typedef enum
{
  MZ_ZIP_MODE_INVALID = 0,
  MZ_ZIP_MODE_READING = 1,
  MZ_ZIP_MODE_WRITING = 2,
  MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED = 3
} mz_zip_mode;

typedef struct mz_zip_archive_tag
{
  mz_uint64 m_archive_size;
  mz_uint64 m_central_directory_file_ofs;
  mz_uint m_total_files;
  mz_zip_mode m_zip_mode;

  mz_uint m_file_offset_alignment;

  mz_alloc_func m_pAlloc;
  mz_free_func m_pFree;
  mz_realloc_func m_pRealloc;
  void *m_pAlloc_opaque;

  mz_file_read_func m_pRead;
  mz_file_write_func m_pWrite;
  void *m_pIO_opaque;

  mz_zip_internal_state *m_pState;

} mz_zip_archive;

typedef enum
{
  MZ_ZIP_FLAG_CASE_SENSITIVE                = 0x0100,
  MZ_ZIP_FLAG_IGNORE_PATH                   = 0x0200,
  MZ_ZIP_FLAG_COMPRESSED_DATA               = 0x0400,
  MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY = 0x0800
} mz_zip_flags;

// ZIP存档读取

// 初始化ZIP存档读取器。
// 这些函数读取并验证存档的中心目录。
mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 size, mz_uint32 flags);
mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, const void *pMem, size_t size, mz_uint32 flags);

#ifndef MINIZ_NO_STDIO
mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, const char *pFilename, mz_uint32 flags);
#endif

// 返回存档中的文件总数。
mz_uint mz_zip_reader_get_num_files(mz_zip_archive *pZip);

// 返回有关存档文件项的详细信息。
mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_index, mz_zip_archive_file_stat *pStat);

// 确定存档文件条目是否为目录条目。
mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_index);
mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_index);

// 检索存档文件项的文件名。
// 返回写入pFilename的字节数，或者如果filename_buf_size为0，则此函数返回完全存储文件名所需的字节数。
mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_index, char *pFilename, mz_uint filename_buf_size);

// 尝试在存档的中心目录中查找文件。
// 有效标志：MZ_ZIP_FLAG_CASE_SENSITIVE、MZ_ZIP_FLAG_IGNORE_PATH
// 如果找不到文件，则返回-1。
int mz_zip_reader_locate_file(mz_zip_archive *pZip, const char *pName, const char *pComment, mz_uint flags);

// 不使用内存分配将存档文件提取到内存缓冲区。
mz_bool mz_zip_reader_extract_to_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_index, void *pBuf, size_t buf_size, mz_uint flags, void *pUser_read_buf, size_t user_read_buf_size);
mz_bool mz_zip_reader_extract_file_to_mem_no_alloc(mz_zip_archive *pZip, const char *pFilename, void *pBuf, size_t buf_size, mz_uint flags, void *pUser_read_buf, size_t user_read_buf_size);

// 将存档文件提取到内存缓冲区。
mz_bool mz_zip_reader_extract_to_mem(mz_zip_archive *pZip, mz_uint file_index, void *pBuf, size_t buf_size, mz_uint flags);
mz_bool mz_zip_reader_extract_file_to_mem(mz_zip_archive *pZip, const char *pFilename, void *pBuf, size_t buf_size, mz_uint flags);

// 将存档文件提取到动态分配的堆缓冲区。
void *mz_zip_reader_extract_to_heap(mz_zip_archive *pZip, mz_uint file_index, size_t *pSize, mz_uint flags);
void *mz_zip_reader_extract_file_to_heap(mz_zip_archive *pZip, const char *pFilename, size_t *pSize, mz_uint flags);

// 使用回调函数提取存档文件以输出文件的数据。
mz_bool mz_zip_reader_extract_to_callback(mz_zip_archive *pZip, mz_uint file_index, mz_file_write_func pCallback, void *pOpaque, mz_uint flags);
mz_bool mz_zip_reader_extract_file_to_callback(mz_zip_archive *pZip, const char *pFilename, mz_file_write_func pCallback, void *pOpaque, mz_uint flags);

#ifndef MINIZ_NO_STDIO
// 将存档文件提取到磁盘文件，并设置其上次访问和修改时间。
// 此函数仅提取文件，而不是存档目录记录。
mz_bool mz_zip_reader_extract_to_file(mz_zip_archive *pZip, mz_uint file_index, const char *pDst_filename, mz_uint flags);
mz_bool mz_zip_reader_extract_file_to_file(mz_zip_archive *pZip, const char *pArchive_filename, const char *pDst_filename, mz_uint flags);
#endif

// 结束存档读取，释放所有分配，如果使用了mz_zip_reader_init_file（），则关闭输入存档文件。
mz_bool mz_zip_reader_end(mz_zip_archive *pZip);

// ZIP存档写入

#ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

// 初始化ZIP存档编写器。
mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_size);
mz_bool mz_zip_writer_init_heap(mz_zip_archive *pZip, size_t size_to_reserve_at_beginning, size_t initial_allocation_size);

#ifndef MINIZ_NO_STDIO
mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, const char *pFilename, mz_uint64 size_to_reserve_at_beginning);
#endif

// 将ZIP存档读取器对象转换为写入器对象，以允许对现有存档进行有效的就地文件附加。
// 对于使用mz_zip_reader_init_file打开的归档文件，pFilename必须是归档文件的文件名，以便可以重新打开进行写入。如果无法重新打开文件，将调用mz_zip_reader_end（）。
// 对于使用mz_zip_reader_init_mem打开的存档，内存块必须使用realloc回调（默认为realloc，除非您已覆盖它）来增长。
// 最后，对于使用mz_zip_reader_init打开的存档，mz_zip_archive的用户提供的m_pWrite函数不能为NULL。
// 注意：除非您知道自己在做什么，否则不建议修改就地存档，因为如果执行停止或之前出现问题
// 存档完成后，文件的中心目录将被删除。
mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, const char *pFilename);

// 将内存缓冲区的内容添加到存档中。这些函数将当前本地时间记录到存档中。
// 若要添加目录条目，请使用以正斜杠结尾且缓冲区为空的存档名称调用此方法。
// level_and_flags—压缩级别（0-10，请参见MZ_BEST_SPEED、MZ_BEST_compression等）与零个或多个MZ_zip_flags逻辑“或”，或仅设置为MZ_DEFAULT_COMPRESION。
mz_bool mz_zip_writer_add_mem(mz_zip_archive *pZip, const char *pArchive_name, const void *pBuf, size_t buf_size, mz_uint level_and_flags);
mz_bool mz_zip_writer_add_mem_ex(mz_zip_archive *pZip, const char *pArchive_name, const void *pBuf, size_t buf_size, const void *pComment, mz_uint16 comment_size, mz_uint level_and_flags, mz_uint64 uncomp_size, mz_uint32 uncomp_crc32);

#ifndef MINIZ_NO_STDIO
// 将磁盘文件的内容添加到存档中。此函数还将磁盘文件的修改时间记录到存档中。
// level_and_flags—压缩级别（0-10，请参见MZ_BEST_SPEED、MZ_BEST_compression等）与零个或多个MZ_zip_flags逻辑“或”，或仅设置为MZ_DEFAULT_COMPRESION。
mz_bool mz_zip_writer_add_file(mz_zip_archive *pZip, const char *pArchive_name, const char *pSrc_filename, const void *pComment, mz_uint16 comment_size, mz_uint level_and_flags);
#endif

// 通过从另一个存档中完全克隆数据，将文件添加到存档中。
// 此函数完全克隆源文件的压缩数据（无需重新压缩），以及其完整文件名、额外数据和注释字段。
mz_bool mz_zip_writer_add_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *pSource_zip, mz_uint file_index);

// 通过写入中央目录记录，然后是中央目录记录的结尾来完成归档。
// 归档完成后，对mz_zip_archive结构的唯一有效调用是mz_zip_writer_end（）。
// 存档必须通过调用此函数手动完成才能生效。
mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip);
mz_bool mz_zip_writer_finalize_heap_archive(mz_zip_archive *pZip, void **pBuf, size_t *pSize);

// 结束存档写入，释放所有分配，如果使用了mz_zip_writer_init_file（），则关闭输出文件。
// 请注意，要使存档有效，必须在结束前完成存档。
mz_bool mz_zip_writer_end(mz_zip_archive *pZip);

// 其他。高级助手函数：

// mz_zip_add_mem_to_archive_file_in_place（）有效地（但不是原子地）将内存blob附加到zip存档。
// level_and_flags—压缩级别（0-10，请参见MZ_BEST_SPEED、MZ_BEST_compression等）与零个或多个MZ_zip_flags逻辑“或”，或仅设置为MZ_DEFAULT_COMPRESION。
mz_bool mz_zip_add_mem_to_archive_file_in_place(const char *pZip_filename, const char *pArchive_name, const void *pBuf, size_t buf_size, const void *pComment, mz_uint16 comment_size, mz_uint level_and_flags);

// 将单个文件从归档文件读取到堆块中。
// 失败时返回NULL。
//
// 注意：由于MINIZ_NO_MALLOC，此功能将无法工作。
//
void *mz_zip_extract_archive_file_to_heap(const char *pZip_filename, const char *pArchive_name, size_t *pSize, mz_uint zip_flags)  __attribute__((warning("miniz is compiled without malloc so this function does not work")));

#endif // #如果是MINIZ_NO_ARCHIVE_WRITING_APIS

#endif // #如果是MINIZ_NO_ARCHIVE_APIS

// -------------------低级解压缩API定义

// tinfl_decompress（）使用的解压缩标志。
// TINFL_FLAG_PARSE_ZLIB_HEADER：如果设置，则输入具有有效的ZLIB标头，并以adler32校验和结尾（这是有效的ZLIB流）。否则，输入为原始放气流。
// TINFL_FLAG_HAS_MORE_INPUT：如果设置，则在提供的输入缓冲区末尾之外有更多可用的输入字节。如果清除，则输入缓冲区包含所有剩余的输入。
// TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF：如果设置，输出缓冲区足够大，可以容纳整个解压缩流。如果清除，则输出缓冲区至少为字典的大小（通常为32KB）。
// TINFL_FLAG_COMPUTE_ALER32：强制对解压缩字节进行adler-32校验和计算。
enum
{
  TINFL_FLAG_PARSE_ZLIB_HEADER = 1,
  TINFL_FLAG_HAS_MORE_INPUT = 2,
  TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF = 4,
  TINFL_FLAG_COMPUTE_ADLER32 = 8
};

// 高级解压缩功能：
// tinfl_decompress_mem_to_heap（）将内存中的块解压缩为通过malloc（）分配的堆块。
// 进入时：
//  pSrc_buf，src_buf_len：要解压缩的Deflate或zlib源数据的指针和大小。
// 返回时：
//  函数返回指向解压缩数据的指针，失败时返回NULL。
//  *pOut_len将设置为解压缩数据的大小，对于不可压缩数据，该大小可能大于src_buf_len。
//  当不再需要时，调用者必须对返回的块调用mz_free（）。
//
// 注意：由于MINIZ_NO_MALLOC，此功能将无法工作。
//
void *tinfl_decompress_mem_to_heap(const void *pSrc_buf, size_t src_buf_len, size_t *pOut_len, int flags) __attribute__((warning("miniz is compiled without malloc so this function does not work")));

// tinfl_decompress_mem_to_mem（）将内存中的一个块解压缩为内存中的另一个块。
// 失败时返回TINFL_DECOMPRES_MEM_TO_MEM_FAILED，或成功时写入的字节数。
#define TINFL_DECOMPRESS_MEM_TO_MEM_FAILED ((size_t)(-1))
size_t tinfl_decompress_mem_to_mem(void *pOut_buf, size_t out_buf_len, const void *pSrc_buf, size_t src_buf_len, int flags);

// tinfl_decompress_mem_to_callback（）将内存中的一个块解压缩到一个内部32KB缓冲区，然后将调用用户提供的回调函数来刷新缓冲区。
//
// 注意：由于MINIZ_NO_MALLOC，此功能将无法工作。
//
// 成功时返回1，失败时返回0或-1。
typedef int (*tinfl_put_buf_func_ptr)(const void* pBuf, int len, void *pUser);
int tinfl_decompress_mem_to_callback(const void *pIn_buf, size_t *pIn_buf_size, tinfl_put_buf_func_ptr pPut_buf_func, void *pPut_buf_user, int flags) __attribute__((warning("miniz is compiled without malloc so this function does not work")));;

struct tinfl_decompressor_tag; typedef struct tinfl_decompressor_tag tinfl_decompressor;

// LZ字典的最大大小。
#define TINFL_LZ_DICT_SIZE 32768

// 返回状态。
typedef enum
{
  TINFL_STATUS_BAD_PARAM = -3,
  TINFL_STATUS_ADLER32_MISMATCH = -2,
  TINFL_STATUS_FAILED = -1,
  TINFL_STATUS_DONE = 0,
  TINFL_STATUS_NEEDS_MORE_INPUT = 1,
  TINFL_STATUS_HAS_MORE_OUTPUT = 2
} tinfl_status;

// 将解压缩程序初始化为其初始状态。
#define tinfl_init(r) do { (r)->m_state = 0; } MZ_MACRO_END
#define tinfl_get_adler32(r) (r)->m_check_adler32

// 主要的低级解压器协程函数。这是解压缩实际需要的唯一函数。所有其他功能都只是提高可用性的高级助手。
// 这是一个通用API，即它可以用作构建任何所需的更高级别解压缩API的构建块。在极限情况下，它可以每输入或输出一个字节调用一次。
tinfl_status tinfl_decompress(tinfl_decompressor *r, const mz_uint8 *pIn_buf_next, size_t *pIn_buf_size, mz_uint8 *pOut_buf_start, mz_uint8 *pOut_buf_next, size_t *pOut_buf_size, const mz_uint32 decomp_flags);

// 随后是内部/私有位。
enum
{
  TINFL_MAX_HUFF_TABLES = 3, TINFL_MAX_HUFF_SYMBOLS_0 = 288, TINFL_MAX_HUFF_SYMBOLS_1 = 32, TINFL_MAX_HUFF_SYMBOLS_2 = 19,
  TINFL_FAST_LOOKUP_BITS = 10, TINFL_FAST_LOOKUP_SIZE = 1 << TINFL_FAST_LOOKUP_BITS
};

typedef struct
{
  mz_uint8 m_code_size[TINFL_MAX_HUFF_SYMBOLS_0];
  mz_int16 m_look_up[TINFL_FAST_LOOKUP_SIZE], m_tree[TINFL_MAX_HUFF_SYMBOLS_0 * 2];
} tinfl_huff_table;

#if MINIZ_HAS_64BIT_REGISTERS
  #define TINFL_USE_64BIT_BITBUF 1
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

// -------------------低级压缩API定义

// 将TDEFL_LESS_MEMORY设置为1以使用更少的内存（压缩速度会稍慢，原始/动态块的输出频率会更高）。
#define TDEFL_LESS_MEMORY 1

// tdefl_init（）压缩标志逻辑“或”在一起（低12位包含每个字典搜索的最大探测数）：
// TDEFL_DEFAULT_MAX_PROBES：压缩器默认为每个字典搜索128个字典探测。0=仅霍夫曼，1=霍夫曼+LZ（最快/垃圾压缩），4095=霍夫曼+IZ（最慢/最佳压缩）。
enum
{
  TDEFL_HUFFMAN_ONLY = 0, TDEFL_DEFAULT_MAX_PROBES = 128, TDEFL_MAX_PROBES_MASK = 0xFFF
};

// TDEFL_WRITE_ZLIB_HEADER：如果设置，压缩器将在deflate数据之前输出ZLIB标头，并在末尾输出源数据的Adler-32。否则，您将获得原始放气数据。
// TDEFL_COMPUTE_ADLER32：始终计算输入数据的adler-32（即使不写入zlib标头）。
// TDEFL_GREED_PARSING_FLAG：设置为使用更快的贪婪解析，而不是更高效的懒惰解析。
// TDEFL_NONDESTINITIC_PARSING_FLAG：启用以将压缩器的初始化时间减至最小，但给定相同的输入（取决于内存内容），输出可能会因运行而异。
// TDEFL_RLE_MATCHES：仅查找RLE匹配（距离为1的匹配）
// TDEFL_FILTER_MATCHES：如果启用，丢弃匹配<=5个字符。
// TDEFL_FORCE_ALL_STATIC_BLOCKS：禁用优化霍夫曼表的使用。
// TDEFL_FORCE_ALL_RAW_BLOCKS：仅使用原始（未压缩）放气块。
// 低12位被保留以控制每次字典查找的最大哈希探测数（请参阅TDEFL_max_probes_MASK）。
enum
{
  TDEFL_WRITE_ZLIB_HEADER             = 0x01000,
  TDEFL_COMPUTE_ADLER32               = 0x02000,
  TDEFL_GREEDY_PARSING_FLAG           = 0x04000,
  TDEFL_NONDETERMINISTIC_PARSING_FLAG = 0x08000,
  TDEFL_RLE_MATCHES                   = 0x10000,
  TDEFL_FILTER_MATCHES                = 0x20000,
  TDEFL_FORCE_ALL_STATIC_BLOCKS       = 0x40000,
  TDEFL_FORCE_ALL_RAW_BLOCKS          = 0x80000
};

// 高级压缩功能：
// tdefl_compress_mem_to_heap（）将内存中的块压缩为通过malloc（）分配的堆块。
// 进入时：
//  pSrc_buf，src_buf_len：要压缩的源块的指针和大小。
//  flags：最大匹配查找器探测（默认值为128）与上述标志进行逻辑“或”运算。较高的探针速度较慢，但可改善压缩。
// 返回时：
//  函数返回指向压缩数据的指针，失败时返回NULL。
//  *pOut_len将设置为压缩数据的大小，对于不可压缩数据，该大小可能大于src_buf_len。
//  当不再需要时，调用者必须释放（）返回的块。
//
// 注意：由于MINIZ_NO_MALLOC，此功能将无法工作。
//
void *tdefl_compress_mem_to_heap(const void *pSrc_buf, size_t src_buf_len, size_t *pOut_len, int flags)  __attribute__((warning("miniz is compiled without malloc so this function does not work")));;

// tdefl_compress_mem_to_mem（）将内存中的一个块压缩为内存中的另一个块。
// 失败时返回0。
size_t tdefl_compress_mem_to_mem(void *pOut_buf, size_t out_buf_len, const void *pSrc_buf, size_t src_buf_len, int flags);

// 将图像压缩为内存中的压缩PNG文件。
// 进入时：
//  pImage、w、h和num_chans描述要压缩的图像。num_chans可以是1、2、3或4。
//  每个扫描线的图像间距（以字节为单位）将为w*num_chans。顶部扫描线上最左侧的像素首先存储在内存中。
//  级别可以在[0,10]之间，使用MZ_NO_COMPRESSION、MZ_BEST_SPEED、MZ_BEST_COMPRESSION等，或者适当的默认值为MZ_default_level
//  如果flip为true，图像将在Y轴上翻转（对OpenGL应用程序有用）。
// 返回时：
//  函数返回指向压缩数据的指针，失败时返回NULL。
//  *pLen_out将被设置为PNG图像文件的大小。
//  当不再需要时，调用者必须mz_free（）返回的堆块（通常大于*pLen_out）。
void *tdefl_write_image_to_png_file_in_memory_ex(const void *pImage, int w, int h, int num_chans, size_t *pLen_out, mz_uint level, mz_bool flip);
void *tdefl_write_image_to_png_file_in_memory(const void *pImage, int w, int h, int num_chans, size_t *pLen_out);

// 输出流接口。压缩器使用此接口写入压缩数据。一次通常称为TDEFL_OUT_BUF_SIZE。
typedef mz_bool (*tdefl_put_buf_func_ptr)(const void* pBuf, int len, void *pUser);

// tdefl_compress_mem_to_output（）将块压缩为输出流。上述助手在内部使用此函数。
//
// 注意：由于MINIZ_NO_MALLOC，此功能将无法工作。
//
mz_bool tdefl_compress_mem_to_output(const void *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, void *pPut_buf_user, int flags)  __attribute__((warning("miniz is compiled without malloc so this function does not work")));;

enum { TDEFL_MAX_HUFF_TABLES = 3, TDEFL_MAX_HUFF_SYMBOLS_0 = 288, TDEFL_MAX_HUFF_SYMBOLS_1 = 32, TDEFL_MAX_HUFF_SYMBOLS_2 = 19, TDEFL_LZ_DICT_SIZE = 32768, TDEFL_LZ_DICT_SIZE_MASK = TDEFL_LZ_DICT_SIZE - 1, TDEFL_MIN_MATCH_LEN = 3, TDEFL_MAX_MATCH_LEN = 258 };

// TDEFL_OUT_BUF_SIZE必须足够大，以容纳单个完整的压缩输出块（使用静态/固定霍夫曼代码）。
#if TDEFL_LESS_MEMORY
enum { TDEFL_LZ_CODE_BUF_SIZE = 24 * 1024, TDEFL_OUT_BUF_SIZE = (TDEFL_LZ_CODE_BUF_SIZE * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_BITS = 12, TDEFL_LEVEL1_HASH_SIZE_MASK = 4095, TDEFL_LZ_HASH_SHIFT = (TDEFL_LZ_HASH_BITS + 2) / 3, TDEFL_LZ_HASH_SIZE = 1 << TDEFL_LZ_HASH_BITS };
#else
enum { TDEFL_LZ_CODE_BUF_SIZE = 64 * 1024, TDEFL_OUT_BUF_SIZE = (TDEFL_LZ_CODE_BUF_SIZE * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_BITS = 15, TDEFL_LEVEL1_HASH_SIZE_MASK = 4095, TDEFL_LZ_HASH_SHIFT = (TDEFL_LZ_HASH_BITS + 2) / 3, TDEFL_LZ_HASH_SIZE = 1 << TDEFL_LZ_HASH_BITS };
#endif

// 如果上面的帮助函数不够灵活，可以直接使用下面的低级tdefl函数。与上面的helper函数不同，低级函数不进行任何堆分配。
typedef enum
{
  TDEFL_STATUS_BAD_PARAM = -2,
  TDEFL_STATUS_PUT_BUF_FAILED = -1,
  TDEFL_STATUS_OKAY = 0,
  TDEFL_STATUS_DONE = 1,
} tdefl_status;

// 必须映射到MZ_NO_FLUSH、MZ_SYNC_FLUSH等枚举
typedef enum
{
  TDEFL_NO_FLUSH = 0,
  TDEFL_SYNC_FLUSH = 2,
  TDEFL_FULL_FLUSH = 3,
  TDEFL_FINISH = 4
} tdefl_flush;

// tdefl的压缩状态结构。
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

// 初始化压缩器。
// 没有相应的deinit（）函数，因为tdeflAPI不会动态分配内存。
// pBut_buf_func：如果为NULL，则输出数据将提供给指定的回调。在这种情况下，用户应该调用tdefl_compress_buffer（）API进行压缩。
// 如果pBut_buf_func为NULL，则用户应始终调用tdefl_compress（）API。
// flags：请参阅以上枚举（TDEFL_HUFFMAN_ONLY、TDEFL_WRITE_ZLIB_HEADER等）
tdefl_status tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, void *pPut_buf_user, int flags);

// 压缩数据块，尽可能多地消耗指定的输入缓冲区，并将尽可能多的压缩数据写入指定的输出缓冲区。
tdefl_status tdefl_compress(tdefl_compressor *d, const void *pIn_buf, size_t *pIn_buf_size, void *pOut_buf, size_t *pOut_buf_size, tdefl_flush flush);

// tdefl_compress_buffer（）仅在使用非NULL tdefl_put_buf_func_ptr调用tdefl_init（）时可用。
// tdefl_compress_buffer（）始终消耗整个输入缓冲区。
tdefl_status tdefl_compress_buffer(tdefl_compressor *d, const void *pIn_buf, size_t in_buf_size, tdefl_flush flush);

tdefl_status tdefl_get_prev_return_status(tdefl_compressor *d);
mz_uint32 tdefl_get_adler32(tdefl_compressor *d);

// 如果未定义MINIZ_NO_ZLIB_APIS，则无法使用tdefl_create_comp_flags_from_zip_params，因为它使用了一些宏。
#ifndef MINIZ_NO_ZLIB_APIS
// 给定zlib样式的压缩参数，创建tdefl_compress（）标志。
// 级别可能在[0,10]之间（其中10是绝对最大压缩，但在某些文件上可能会慢得多）
// window_bits可以是-15（原始放气）或15（zlib）
// 策略可以是MZ_DEFAULT_strategy、MZ_FILTED、MZ_HUFFMAN_ONLY、MZ_RLE或MZ_FIXED
mz_uint tdefl_create_comp_flags_from_zip_params(int level, int window_bits, int strategy);
#endif // #如果是MINIZ_NO_ZLIB_APIS

#ifdef __cplusplus
}
#endif

#endif // MINIZ_HEADER_INCLUDED

