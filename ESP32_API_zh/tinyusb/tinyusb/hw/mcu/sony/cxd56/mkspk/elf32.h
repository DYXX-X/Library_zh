/****************************************************************************
 * 包含/elf32.h
 *
 *   版权所有（C）2012 Gregory Nutt。保留所有权利。作者：Gregory Nutt<gnutt@nuttx.org>
 *
 * 参考：System V Application Binary Interface，4.1版，1997年3月18日，The Santa Cruz Operation，Inc。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用NuttX名称或其贡献者的名称来支持或推广源自本软件的产品。
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#ifndef __INCLUDE_ELF32_H
#define __INCLUDE_ELF32_H

/****************************************************************************
 * 包含的文件
 ****************************************************************************/

#include <stdint.h>

/****************************************************************************
 * 预处理器定义
 ****************************************************************************/

#define EI_NIDENT          16     /* e_ident[]的大小*/

#define ELF32_ST_BIND(i)   ((i) >> 4)
#define ELF32_ST_TYPE(i)   ((i) & 0xf)
#define ELF32_ST_INFO(b,t) (((b) << 4) | ((t) & 0xf))

/* Elf32_Rel*：：r_info的定义*/

#define ELF32_R_SYM(i)    ((i) >> 8)
#define ELF32_R_TYPE(i)   ((i) & 0xff)
#define ELF32_R_INFO(s,t) (((s)<< 8) | ((t) & 0xff))

#define ELF_R_SYM(i)      ELF32_R_SYM(i)

/****************************************************************************
 * 公共类型定义
 ****************************************************************************/

/* 图4.2:32位数据类型*/

typedef uint32_t  Elf32_Addr;  /* 未签名的程序地址*/
typedef uint16_t  Elf32_Half;  /* 无符号中整数*/
typedef uint32_t  Elf32_Off;   /* 无符号文件偏移量*/
typedef int32_t   Elf32_Sword; /* 有符号大整数*/
typedef uint32_t  Elf32_Word;  /* 无符号大整数*/

/* 图4-3：ELF总管*/

typedef struct
{
  unsigned char e_ident[EI_NIDENT];
  Elf32_Half    e_type;
  Elf32_Half    e_machine;
  Elf32_Word    e_version;
  Elf32_Addr    e_entry;
  Elf32_Off     e_phoff;
  Elf32_Off     e_shoff;
  Elf32_Word    e_flags;
  Elf32_Half    e_ehsize;
  Elf32_Half    e_phentsize;
  Elf32_Half    e_phnum;
  Elf32_Half    e_shentsize;
  Elf32_Half    e_shnum;
  Elf32_Half    e_shstrndx;
} Elf32_Ehdr;

/* 图4-8：截面标题*/

typedef struct
{
  Elf32_Word    sh_name;
  Elf32_Word    sh_type;
  Elf32_Word    sh_flags;
  Elf32_Addr    sh_addr;
  Elf32_Off     sh_offset;
  Elf32_Word    sh_size;
  Elf32_Word    sh_link;
  Elf32_Word    sh_info;
  Elf32_Word    sh_addralign;
  Elf32_Word    sh_entsize;
} Elf32_Shdr;

/* 图4-15：符号表条目*/

typedef struct
{
  Elf32_Word    st_name;
  Elf32_Addr    st_value;
  Elf32_Word    st_size;
  unsigned char st_info;
  unsigned char st_other;
  Elf32_Half    st_shndx;
} Elf32_Sym;

/* 图4-19：重新定位条目*/

typedef struct
{
  Elf32_Addr   r_offset;
  Elf32_Word   r_info;
} Elf32_Rel;

typedef struct
{
  Elf32_Addr   r_offset;
  Elf32_Word   r_info;
  Elf32_Sword  r_addend;
} Elf32_Rela;

/* 图5-1：程序标题*/

typedef struct
{
  Elf32_Word   p_type;
  Elf32_Off    p_offset;
  Elf32_Addr   p_vaddr;
  Elf32_Addr   p_paddr;
  Elf32_Word   p_filesz;
  Elf32_Word   p_memsz;
  Elf32_Word   p_flags;
  Elf32_Word   p_align;
} Elf32_Phdr;

/* 图5-9：动态结构*/

typedef struct
{
  Elf32_Sword  d_tag;
  union
  {
    Elf32_Word d_val;
    Elf32_Addr d_ptr;
  } d_un;
} Elf32_Dyn;

typedef Elf32_Addr  Elf_Addr;
typedef Elf32_Ehdr  Elf_Ehdr;
typedef Elf32_Rel   Elf_Rel;
typedef Elf32_Rela  Elf_Rela;
typedef Elf32_Sym   Elf_Sym;
typedef Elf32_Shdr  Elf_Shdr;
typedef Elf32_Word  Elf_Word;

#endif /* __INCLUDE_ELF32_H */

