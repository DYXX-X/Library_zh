/*
 *  Copyright (c) 2018, Sam Kumar <samkumar@cs.berkeley.edu> 版权所有（c）2018，加州大学伯克利分校保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CBUF_H_
#define CBUF_H_

/* CIRCULAR BUFFER */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

struct otLinkedBuffer;

/* 表示循环缓冲区。*/
struct cbufhead {
    size_t r_index;
    size_t w_index;
    size_t size;
    uint8_t* buf;
};

/* 初始化循环缓冲区（chdr是存储元数据的头）。*/
void cbuf_init(struct cbufhead* chdr, uint8_t* buf, size_t len);

/* 用于将数据复制到循环缓冲区或从循环缓冲区复制数据的函数类型。*/
typedef void(*cbuf_copier_t)(void*, size_t, const void*, size_t, size_t);

/* cbuf_copier_t的实例化，用于在循环缓冲区和常规缓冲区之间复制数据。*/
void cbuf_copy_into_buffer(void* buffer, size_t buffer_offset, const void* arr, size_t arr_offset, size_t num_bytes);
void cbuf_copy_from_buffer(void* arr, size_t arr_offset, const void* buffer, size_t buffer_offset, size_t num_bytes);

/* cbuf_copier_t的实例化，用于在循环缓冲区和otMessages之间复制数据。*/
void cbuf_copy_into_message(void* buffer, size_t buffer_offset, const void* arr, size_t arr_offset, size_t num_bytes);
void cbuf_copy_from_message(void* arr, size_t arr_offset, const void* buffer, size_t buffer_offset, size_t num_bytes);

/* 使用指定的复印机将数据写入循环缓冲区的背面。*/
size_t cbuf_write(struct cbufhead* chdr, const void* data, size_t data_offset, size_t data_len, cbuf_copier_t copy_from);

/* 使用指定的复印机从循环缓冲区的前部读取数据。*/
size_t cbuf_read(struct cbufhead* chdr, void* data, size_t data_offset, size_t numbytes, int pop, cbuf_copier_t copy_into);

/* 使用指定的复印机从循环缓冲区的前端以指定的偏移量（字节）读取数据。*/
size_t cbuf_read_offset(struct cbufhead* chdr, void* data, size_t data_offset, size_t numbytes, size_t offset, cbuf_copier_t copy_into);

/* 从循环缓冲区的前面丢弃字节。*/
size_t cbuf_pop(struct cbufhead* chdr, size_t numbytes);

/* 返回可从循环缓冲区读取的字节数。*/
size_t cbuf_used_space(struct cbufhead* chdr);

/* 返回循环缓冲区满之前可以写入的字节数。*/
size_t cbuf_free_space(struct cbufhead* chdr);

/* 返回循环缓冲区的总容量（字节）。*/
size_t cbuf_size(struct cbufhead* chdr);

/* 如果循环缓冲区为空，则返回true；如果不为空，返回false。*/
bool cbuf_empty(struct cbufhead* chdr);

/* 填充提供的otLinkedBuffers以引用循环缓冲区中当前的数据。*/
void cbuf_reference(const struct cbufhead* chdr, struct otLinkedBuffer* first, struct otLinkedBuffer* second);

/* 在循环缓冲区的末尾写入DATA，但不使其可供读取。这些数据被称为“无序”。OFFSET是写入这些字节的位置，相对于cbuf_write将写入它们的位置。BITMAP中的每个比特对应于循环缓冲器中的一个字节；设置与包含新写入数据的字节相对应的位。如果写入的第一个字节的索引不为NULL，则将其存储到FIRSTINDEX中。*/
size_t cbuf_reass_write(struct cbufhead* chdr, size_t offset, const void* data, size_t data_offset, size_t numbytes, uint8_t* bitmap, size_t* firstindex, cbuf_copier_t copy_from);

/* 使NUMBYTES从序列字节中取出，以便在循环缓冲区中读取。未复制数据；可用的无序字节是当前位于cbufwrite将写入它们的位置的字节。字节取自缓冲区的未使用空间，可以使用cbuf_reads_write进行设置。*/
size_t cbuf_reass_merge(struct cbufhead* chdr, size_t numbytes, uint8_t* bitmap);

/* 统计指定OFFSET处连续的无序字节数，直到计数达到指定的LIMIT。*/
size_t cbuf_reass_count_set(struct cbufhead* chdr, size_t offset, uint8_t* bitmap, size_t limit);

/* 如果INDEX是超过缓冲区末尾的OFFSET字节中的一个字节的索引，则返回真值。*/
int cbuf_reass_within_offset(struct cbufhead* chdr, size_t offset, size_t index);

#endif

