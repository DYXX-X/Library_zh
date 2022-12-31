/******************************************************************************
 * 版权所有（C）1999-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

#ifndef _SBC_IF_H
#define _SBC_IF_H

#define PCM_BUFFER_SIZE 512

/*
 SBC_Init-为播放的每个曲目调用一次

 pcm_sample_freq-4000至48000通道-1单声道2立体声位per_sample-8或16返回-0成功
*/

int SBC_init(int pcm_sample_freq, int channels, int bits_per_sample);

/*
 SBC_write-重复调用，pcm_in指针的长度增加，直到磁道完成。

 pcm_in-指向pcm缓冲区长度的指针-任何sbc_out-指向sbc输出缓冲区返回的指针-写入sbc_out的字节数
*/

int SBC_write(unsigned char *pcm_in, int length, unsigned char *sbc_out);

#endif

