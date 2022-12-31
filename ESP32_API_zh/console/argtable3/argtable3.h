/*******************************************************************************
 * 此文件是argtable3库的一部分。
 *
 * 版权所有（C）1998-20012003-20112013 Stewart Heitmann
 * <sheitmann@users.sourceforge.net> 保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。未经事先书面许可，不得使用STEWART HEITMANN的名称或其贡献者的名称来支持或推广源自本软件的产品。
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL STEWART HEITMANN BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#ifndef ARGTABLE3
#define ARGTABLE3

#include <stdio.h>      /* FILE */
#include <time.h>       /* 结构tm*/

#ifdef __cplusplus
extern "C" {
#endif

#define ARG_REX_ICASE 1

/* arg_hdr的位掩码。旗帜*/
enum
{
    ARG_TERMINATOR=0x1,
    ARG_HASVALUE=0x2,
    ARG_HASOPTVALUE=0x4
};

typedef void (arg_resetfn)(void *parent);
typedef int  (arg_scanfn)(void *parent, const char *argval);
typedef int  (arg_checkfn)(void *parent);
typedef void (arg_errorfn)(void *parent, FILE *fp, int error, const char *argval, const char *progname);


/*
* arg_hdr结构定义所有arg_xxx结构通用的属性。argtable库要求每个arg_xxx结构都有一个arg_hdr结构作为其第一个数据成员。然后，argtable库函数使用这些数据来标识命令行选项的属性，例如其选项标记、数据类型字符串和词汇表字符串等。此外，arg_hdr结构包含指向每个arg_xxx结构提供的自定义函数的指针，这些函数执行解析特定arg_xxx参数、执行解析后检查、，以及报告错误。这些函数是单个arg_xxx源代码的私有函数，是指向它们的指针。这些函数由arg_xxx结构的构造函数初始化。如果需要，用户可以在构建后更改它们，但最初的意图是由构造函数设置它们并保持不变。
*/
struct arg_hdr
{
    char         flag;        /* 修改器标志：ARG_TERMINATOR、ARG_HASVALUE。*/
    const char  *shortopts;   /* 定义短选项的字符串*/
    const char  *longopts;    /* 字符串定义长选项*/
    const char  *datatype;    /* 参数数据类型的说明*/
    const char  *glossary;    /* arg_print_glossary函数所示的选项说明*/
    int          mincount;    /* 接受此选项的最小出现次数*/
    int          maxcount;    /* 如果接受此选项，则出现的最大次数*/
    void        *parent;      /* 指向父arg_xxx结构的指针*/
    arg_resetfn *resetfn;     /* 指向父arg_xxx重置函数的指针*/
    arg_scanfn  *scanfn;      /* 指向父arg_xxx扫描函数的指针*/
    arg_checkfn *checkfn;     /* 指向父arg_xxx检查函数的指针*/
    arg_errorfn *errorfn;     /* 指向父arg_xxx错误函数的指针*/
    void        *priv;        /* 指向arg_xxx函数使用的私有标头数据的指针*/
};

struct arg_rem
{
    struct arg_hdr hdr;      /* 必需的argtable标头结构*/
};

struct arg_lit
{
    struct arg_hdr hdr;      /* 必需的argtable标头结构*/
    int count;               /* 匹配的命令行参数数*/
};

struct arg_int
{
    struct arg_hdr hdr;      /* 必需的argtable标头结构*/
    int count;               /* 匹配的命令行参数数*/
    int *ival;               /* 解析的参数值数组*/
};

struct arg_dbl
{
    struct arg_hdr hdr;      /* 必需的argtable标头结构*/
    int count;               /* 匹配的命令行参数数*/
    double *dval;            /* 解析的参数值数组*/
};

struct arg_str
{
    struct arg_hdr hdr;      /* 必需的argtable标头结构*/
    int count;               /* 匹配的命令行参数数*/
    const char **sval;       /* 解析的参数值数组*/
};

struct arg_rex
{
    struct arg_hdr hdr;      /* 必需的argtable标头结构*/
    int count;               /* 匹配的命令行参数数*/
    const char **sval;       /* 解析的参数值数组*/
};

struct arg_file
{
    struct arg_hdr hdr;      /* 必需的argtable标头结构*/
    int count;               /* 匹配的命令行参数数*/
    const char **filename;   /* 解析文件名数组（例如：/home/foo.bar）*/
    const char **basename;   /* 解析的基名称数组（例如：foo.bar）*/
    const char **extension;  /* 已解析扩展的数组（例如：.bar）*/
};

struct arg_date
{
    struct arg_hdr hdr;      /* 必需的argtable标头结构*/
    const char *format;      /* 用于分析日期的strptime格式字符串*/
    int count;               /* 匹配的命令行参数数*/
    struct tm *tmval;        /* 分析的时间值数组*/
};

enum {ARG_ELIMIT=1, ARG_EMALLOC, ARG_ENOMATCH, ARG_ELONGOPT, ARG_EMISSARG};
struct arg_end
{
    struct arg_hdr hdr;      /* 必需的argtable标头结构*/
    int count;               /* 遇到的错误数*/
    int *error;              /* 错误代码数组*/
    void **parent;           /* 指向违规arg_xxx结构的指针数组*/
    const char **argval;     /* 指向违规argv[]字符串的指针数组*/
};


/****arg_xxx构造函数*********************************/

struct arg_rem* arg_rem(const char* datatype, const char* glossary);

struct arg_lit* arg_lit0(const char* shortopts,
    const char* longopts,
    const char* glossary);
struct arg_lit* arg_lit1(const char* shortopts,
    const char* longopts,
    const char *glossary);
struct arg_lit* arg_litn(const char* shortopts,
    const char* longopts,
    int mincount,
    int maxcount,
    const char *glossary);

struct arg_key* arg_key0(const char* keyword,
    int flags,
    const char* glossary);
struct arg_key* arg_key1(const char* keyword,
    int flags,
    const char* glossary);
struct arg_key* arg_keyn(const char* keyword,
    int flags,
    int mincount,
    int maxcount,
    const char* glossary);

struct arg_int* arg_int0(const char* shortopts,
    const char* longopts,
    const char* datatype,
    const char* glossary);
struct arg_int* arg_int1(const char* shortopts,
    const char* longopts,
    const char* datatype,
    const char *glossary);
struct arg_int* arg_intn(const char* shortopts,
    const char* longopts,
    const char *datatype,
    int mincount,
    int maxcount,
    const char *glossary);

struct arg_dbl* arg_dbl0(const char* shortopts,
    const char* longopts,
    const char* datatype,
    const char* glossary);
struct arg_dbl* arg_dbl1(const char* shortopts,
    const char* longopts,
    const char* datatype,
    const char *glossary);
struct arg_dbl* arg_dbln(const char* shortopts,
    const char* longopts,
    const char *datatype,
    int mincount,
    int maxcount,
    const char *glossary);

struct arg_str* arg_str0(const char* shortopts,
    const char* longopts,
    const char* datatype,
    const char* glossary);
struct arg_str* arg_str1(const char* shortopts,
    const char* longopts,
    const char* datatype,
    const char *glossary);
struct arg_str* arg_strn(const char* shortopts,
    const char* longopts,
    const char* datatype,
    int mincount,
    int maxcount,
    const char *glossary);

struct arg_rex* arg_rex0(const char* shortopts,
    const char* longopts,
    const char* pattern,
    const char* datatype,
    int flags,
    const char* glossary);
struct arg_rex* arg_rex1(const char* shortopts,
    const char* longopts,
    const char* pattern,
    const char* datatype,
    int flags,
    const char *glossary);
struct arg_rex* arg_rexn(const char* shortopts,
    const char* longopts,
    const char* pattern,
    const char* datatype,
    int mincount,
    int maxcount,
    int flags,
    const char *glossary);

struct arg_file* arg_file0(const char* shortopts,
    const char* longopts,
    const char* datatype,
    const char* glossary);
struct arg_file* arg_file1(const char* shortopts,
    const char* longopts,
    const char* datatype,
    const char *glossary);
struct arg_file* arg_filen(const char* shortopts,
    const char* longopts,
    const char* datatype,
    int mincount,
    int maxcount,
    const char *glossary);

struct arg_date* arg_date0(const char* shortopts,
    const char* longopts,
    const char* format,
    const char* datatype,
    const char* glossary);
struct arg_date* arg_date1(const char* shortopts,
    const char* longopts,
    const char* format,
    const char* datatype,
    const char *glossary);
struct arg_date* arg_daten(const char* shortopts,
    const char* longopts,
    const char* format,
    const char* datatype,
    int mincount,
    int maxcount,
    const char *glossary);

struct arg_end* arg_end(int maxerrors);


/****其他功能*******************************************/
int arg_nullcheck(void **argtable);
int arg_parse(int argc, char **argv, void **argtable);
void arg_print_option(FILE *fp, const char *shortopts, const char *longopts, const char *datatype, const char *suffix);
void arg_print_syntax(FILE *fp, void **argtable, const char *suffix);
void arg_print_syntaxv(FILE *fp, void **argtable, const char *suffix);
void arg_print_glossary(FILE *fp, void **argtable, const char *format);
void arg_print_glossary_gnu(FILE *fp, void **argtable);
void arg_print_errors(FILE* fp, struct arg_end* end, const char* progname);
void arg_freetable(void **argtable, size_t n);
void arg_print_formatted(FILE *fp, const unsigned lmargin, const unsigned rmargin, const char *text);

/****已弃用的函数，仅用于向后兼容********/
void arg_free(void **argtable);

#ifdef __cplusplus
}
#endif
#endif

