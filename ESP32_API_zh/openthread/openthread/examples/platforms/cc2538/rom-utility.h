/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ROM_UTILITY_H_
#define ROM_UTILITY_H_

#define ROM_API_TABLE_ADDR 0x00000048

typedef uint32_t (*volatile FPTR_CRC32_T)(uint8_t * /*p数据*/, uint32_t /*字节计数*/);
typedef uint32_t (*volatile FPTR_GETFLSIZE_T)(void);
typedef uint32_t (*volatile FPTR_GETCHIPID_T)(void);
typedef int32_t (*volatile FPTR_PAGEERASE_T)(uint32_t /*闪存地址*/, uint32_t /*大小*/);
typedef int32_t (*volatile FPTR_PROGFLASH_T)(uint32_t * /*pRamData（pRamData）*/, uint32_t /*FlashAdr公司*/, uint32_t /*字节计数*/);
typedef void (*volatile FPTR_RESETDEV_T)(void);
typedef void *(*volatile FPTR_MEMSET_T)(void * /*s*/, int32_t /*c*/, uint32_t /*n*/);
typedef void *(*volatile FPTR_MEMCPY_T)(void * /*第1页*/, const void * /*第2页*/, uint32_t /*n*/);
typedef int32_t (*volatile FPTR_MEMCMP_T)(const void * /*第1页*/, const void * /*第2页*/, uint32_t /*n*/);
typedef void *(*volatile FPTR_MEMMOVE_T)(void * /*第1页*/, const void * /*第2页*/, uint32_t /*n*/);

typedef struct
{
    FPTR_CRC32_T     Crc32;
    FPTR_GETFLSIZE_T GetFlashSize;
    FPTR_GETCHIPID_T GetChipId;
    FPTR_PAGEERASE_T PageErase;
    FPTR_PROGFLASH_T ProgramFlash;
    FPTR_RESETDEV_T  ResetDevice;
    FPTR_MEMSET_T    memset;
    FPTR_MEMCPY_T    memcpy;
    FPTR_MEMCMP_T    memcmp;
    FPTR_MEMMOVE_T   memmove;
} ROM_API_T;

// clang格式关闭

#define P_ROM_API               ((ROM_API_T*)ROM_API_TABLE_ADDR)

#define ROM_Crc32(a,b)          P_ROM_API->Crc32(a,b)
#define ROM_GetFlashSize()      P_ROM_API->GetFlashSize()
#define ROM_GetChipId()         P_ROM_API->GetChipId()
#define ROM_PageErase(a,b)      P_ROM_API->PageErase(a,b)
#define ROM_ProgramFlash(a,b,c) P_ROM_API->ProgramFlash(a,b,c)
#define ROM_ResetDevice()       P_ROM_API->ResetDevice()
#define ROM_Memset(a,b,c)       P_ROM_API->memset(a,b,c)
#define ROM_Memcpy(a,b,c)       P_ROM_API->memcpy(a,b,c)
#define ROM_Memcmp(a,b,c)       P_ROM_API->memcmp(a,b,c)
#define ROM_Memmove(a,b,c)      P_ROM_API->memmove(a,b,c)

// clang格式打开

#endif // ROM_UTILITY_H_

