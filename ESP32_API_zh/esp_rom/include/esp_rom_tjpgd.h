/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/*-----------------------------------------------------------------------------/
/TJpgDec-微型JPEG解压缩器R0.01b（C）ChaN，2012/-------------------------------------------------------------------------------//TJpgDec是一个用于小型嵌入式系统的通用JPEG解压缩器模块。/这是一款免费软件，根据以下条款的许可政策开放用于教育、研究和商业/开发。//版权所有（C）2012，ChaN，保留所有权利。//TJpgDec模块是一个免费软件，不提供任何保修。/无使用限制。在您的责任范围内，您可以将其用于/个人、非营利或商业产品。/源代码的重新分发必须保留上述版权声明/
/-----------------------------------------------------------------------------*/

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 错误代码*/
typedef enum {
    JDR_OK = 0, /* 0:成功*/
    JDR_INTR,   /* 1： 输出功能中断*/
    JDR_INP,    /* 2： 设备错误或输入流错误终止*/
    JDR_MEM1,   /* 3： 映像的内存池不足*/
    JDR_MEM2,   /* 4： 流输入缓冲区不足*/
    JDR_PAR,    /* 5： 参数错误*/
    JDR_FMT1,   /* 6： 数据格式错误（可能是损坏的数据）*/
    JDR_FMT2,   /* 7： 格式正确但不受支持*/
    JDR_FMT3    /* 8： 不支持JPEG标准*/
} esp_rom_tjpgd_result_t;

/* 矩形结构*/
typedef struct {
    uint16_t left;  /* 左端*/
    uint16_t right; /* 右端*/
    uint16_t top;   /* 顶端*/
    uint16_t bottom;/* 底端*/
} esp_rom_tjpgd_rect_t;

typedef struct JDEC_s esp_rom_tjpgd_dec_t;

/**
 * @brief 从输入流读取数据的用户定义输入函数的类型
 * @param dec 指定解压缩会话的解压缩对象
 * @param buffer 指定指向读取缓冲区的指针以存储读取数据。NULL指定从输入流中删除数据
 * @param ndata 指定要从输入流中读取/删除的字节数
 *
 * @return 读取/删除的字节数。当返回零时，esp_rom_tjpgd_prepare和esp_rom_tjpgd_decomp函数将使用JDR_INP中止
 */
typedef uint32_t (*esp_rom_tjpgd_input_function_t)(esp_rom_tjpgd_dec_t *dec, uint8_t *buffer, uint32_t ndata);

/**
 * @brief 用户定义的输出函数，用于将解压缩的像素写入输出设备
 *
 * 此函数是TJpgDec模块的数据输出接口。相应的解压缩会话可以通过传递给jd_prepare函数第5个参数的设备标识符jdec->device的指针来标识。位图在此函数中被发送到帧缓冲区或显示设备。位图中的第一个像素是矩形的左上角，第二个像素是右下角，最后一个像素是该矩形的右下角。矩形的大小从1x1到16x16不等，取决于图像的剪裁、缩放和采样因子。如果矩形超出了帧缓冲区，则应在此函数中对其进行剪裁。
 *
 * 像素格式当前配置为RGB888
 *
 * @param dec 指定解压缩会话的解压缩对象
 * @param bitmap 指定要输出的RGB位图
 * @param rect 指定图像中的矩形区域以输出RGB位图
 *
 * @return 通常返回1。它允许TJpgDec继续解压缩过程。当返回0时，esp_rom_tjpgd_decomp函数将使用JDR_INTR中止。这对于中断解压缩过程非常有用
 */
typedef uint32_t (*esp_rom_tjpgd_output_function_t)(esp_rom_tjpgd_dec_t *dec, void *bitmap, esp_rom_tjpgd_rect_t *rect);

struct JDEC_s {
    uint32_t dctr;              /* 输入缓冲区中可用的字节数*/
    uint8_t *dptr;              /* 当前数据读取指针*/
    uint8_t *inbuf;             /* 比特流输入缓冲器*/
    uint8_t dmsk;               /* 当前读取字节中的当前位*/
    uint8_t scale;              /* 输出缩放比率*/
    uint8_t msx, msy;           /* 以块为单位的MCU大小（宽度、高度）*/
    uint8_t qtid[3];            /* 每个组件的量化表ID*/
    int16_t dcv[3];             /* 每个组件的上一个直流元件*/
    uint16_t nrst;              /* 重新启动搜索*/
    uint32_t width, height;     /* 输入图像的大小（像素）*/
    uint8_t *huffbits[2][2];    /* 霍夫曼比特分布表[id][dcac]*/
    uint16_t *huffcode[2][2];   /* 霍夫曼码字表[id][dcac]*/
    uint8_t *huffdata[2][2];    /* 霍夫曼解码数据表[id][dcac]*/
    int32_t *qttbl[4];          /* 解列表[id]*/
    void *workbuf;              /* IDCT和RGB输出的工作缓冲区*/
    uint8_t *mcubuf;            /* MCU的工作缓冲区*/
    void *pool;                 /* 指向可用内存池的指针*/
    uint32_t sz_pool;           /* 内存池大小（可用字节）*/
    esp_rom_tjpgd_input_function_t infunc; /* 指向jpeg流输入函数的指针*/
    void *device;               /* 指向会话的I/O设备标识符的指针*/
};

/* TJpgDec API函数*/

/**
 * @brief 分析JPEG数据并为后续解压缩过程创建解压缩对象。
 * @param dec 指定要初始化的解压缩对象。解压缩对象用于随后的解压缩过程。
 * @param infunc 指定用户定义的数据输入函数。
 * @param work 指定指向此会话工作区的指针。它应该与单词边界对齐，否则会导致异常。
 * @param sz_work 以字节为单位指定工作区的大小。TJpgDec需要多达3092字节的工作区，这取决于JPEG图像的内置参数表。因此，对于大多数情况，3092字节的工作区就足够了。
 * @param dev 指定指向此会话的用户定义设备标识符的指针。它存储在解压缩对象中的成员设备中。I/O功能可以引用它来标识当前会话。当I/O设备在项目中固定或不需要此功能时，请设置为NULL，而不必考虑此问题。
 *
 * @return
 *      -JDR_OK函数成功，解压缩对象有效。
 *      -JDR_INP由于硬错误或错误的流终止，输入函数中发生错误。
 *      -JDR_MEM1此JPEG图像的工作区不足。
 *      -JDR_MEM2此JPEG图像的输入缓冲区不足。JD_SZBUF可能太小。
 *      -JDR_PAR参数错误。给定的工作区指针为空。
 *      -JDR_FMT1数据格式错误。JPEG数据可以折叠。
 *      -JDR_FMT2正确格式，但不受支持。可能是灰度图像。
 *      -JDR_FMT3不支持JPEG标准。可能是渐进式JPEG图像。
 */
esp_rom_tjpgd_result_t esp_rom_tjpgd_prepare(esp_rom_tjpgd_dec_t *dec, esp_rom_tjpgd_input_function_t infunc, void *work, uint32_t sz_work, void *dev);

/**
 * @brief 解压缩JPEG图像并将其作为RGB数据输出。
 * @param dec 指定有效的解压缩器对象。
 * @param outfunc 指定用户定义的数据输出函数。esp_rom_tjpgd_decomp函数调用此函数以RGB格式输出解压缩的JPEG图像。
 * @param scale 指定输出的缩放因子N。输出图像的缩放比例为1/2^N（N=0到3）。
 *
 * @return
 *      -JDR_OK函数成功。
 *      -JDR_INTR解压缩过程被输出函数中断。
 *      -JDR_INP由于硬错误或错误的流终止，输入函数中发生错误。
 *      -JDR_PAR参数错误。给定的比例因子无效。
 *      -JDR_FMT1数据格式错误。JPEG数据可以合并。
 */
esp_rom_tjpgd_result_t esp_rom_tjpgd_decomp(esp_rom_tjpgd_dec_t *dec, esp_rom_tjpgd_output_function_t outfunc, uint8_t scale);

#ifdef __cplusplus
}
#endif

