/*
 *  Copyright (c) 2018, Sam Kumar <samkumar@cs.berkeley.edu> 版权所有（c）2018，加州大学伯克利分校保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef BITMAP_H_
#define BITMAP_H_

#include <stdint.h>
#include <stdlib.h>

/* 计算存储指定位数所需的字节数。*/
#define BITS_TO_BYTES(bits) (((bits) >> 3) + (((bits) & 0x7) ? 1 : 0))

/* 将位图初始化为全零。*/
void bmp_init(uint8_t* buf, size_t numbytes);

/* 设置指定的位范围。START是要设置的第一位的索引。LEN是要设置的位数。*/
void bmp_setrange(uint8_t* buf, size_t start, size_t len);

/* 清除指定的位范围。START是要清除的第一位的索引。LEN是要清除的位数。*/
void bmp_clrrange(uint8_t* buf, size_t start, size_t len);

/* 统计BUF中从START开始的设置位数。BUF的长度为BUFLEN，以字节为单位。统计设置位数，直到它（1）找到未设置的位数，在这种情况下，它返回设置位数。*/
size_t bmp_countset(uint8_t* buf, size_t buflen, size_t start, size_t limit);

/* 如果位图全为零，则返回1，否则返回0。*/
int bmp_isempty(uint8_t* buf, size_t buflen);

/* 以十六进制打印位图（用于调试）。*/
void bmp_print(uint8_t* buf, size_t buflen);

#endif

