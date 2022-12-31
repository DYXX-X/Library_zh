/****************************************************************************
 * 工具/cxd56/mkspk.h
 *
 * 版权所有（C）20072008 Sony Corporation
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用NuttX名称或其贡献者的名称来支持或推广源自本软件的产品。
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

/****************************************************************************
 * 包含的文件
 ****************************************************************************/

#include "clefia.h"
#include "elf32.h"

/****************************************************************************
 * 预处理器定义
 ****************************************************************************/

#define EI_MAG0            0      /* 文件标识*/
#define EI_MAG1            1
#define EI_MAG2            2
#define EI_MAG3            3

#define SHT_SYMTAB         2
#define SHT_STRTAB         3

#define PT_LOAD            1

#define alignup(x, a) (((x) + ((a) - 1)) & ~((a) - 1))
#define swap(a, b) { (a) ^= (b); (b) ^= (a); (a) ^= (b); }

/****************************************************************************
 * 公共类型
 ****************************************************************************/

struct spk_header
  {
    uint8_t magic[4];
    uint8_t cpu;
    uint8_t reserved[11];
    uint32_t entry;
    uint32_t stack;
    uint16_t core;
    uint16_t binaries;
    uint16_t phoffs;
    uint16_t mode;
  };

struct spk_prog_info
  {
    uint32_t load_address;
    uint32_t offset;
    uint32_t size;
    uint32_t memsize;
  };

struct elf_file
  {
    Elf32_Ehdr *ehdr;
    Elf32_Phdr *phdr;
    Elf32_Shdr *shdr;
    Elf32_Sym *symtab;
    int nsyms;
    char *shstring;
    char *string;
    char *data;
  };

