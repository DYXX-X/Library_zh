/*
 *  Copyright (c) 2018, Sam Kumar <samkumar@cs.berkeley.edu> 版权所有（c）2018，加州大学伯克利分校保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LBUF_H_
#define LBUF_H_

#include <stddef.h>
#include <stdint.h>

struct otLinkedBuffer;

/* LINKED BUFFER */

struct lbufhead {
    struct otLinkedBuffer* head;
    struct otLinkedBuffer* tail;
    size_t offset;
    size_t length;
};

/* 初始化链接缓冲区。*/
void lbuf_init(struct lbufhead* buffer);

/* 将缓冲区的内容作为链接缓冲区链返回，如果缓冲区没有头，则返回NULL。*/
static inline struct otLinkedBuffer* lbuf_head(struct lbufhead* buffer) {
    return buffer->head;
}

/* 通过将NEWENTRY的内容附加到当前链的末尾，将其添加到缓冲区。*/
void lbuf_append(struct lbufhead* buffer, struct otLinkedBuffer* newentry);

/* 将缓冲区的最后一个条目扩展指定的字节数。*/
void lbuf_extend(struct lbufhead* buffer, size_t numbytes);

/* 从缓冲区中删除第一个NUMBYTES字节，并返回删除的字节数（如果缓冲区中的字节数少于NUMBYTES）。对于缓冲区中不再被引用且可以回收的每个条目，NTRAVERSED递增一次。*/
size_t lbuf_pop(struct lbufhead* buffer, size_t numbytes, int* ntraversed);

/* 给定一个索引范围（由开头的OFFSET和长度NUMBYTES指定），该函数定位引用相应字节的链接缓冲区条目链。指向范围中第一个条目的指针存储在first中，并且在范围开始之前条目中的字节数存储在FIRSTOFFSET中。指向范围中最后一个项目的指针存储在last中，该项目中范围结束后的字节数存储在LASTEXTRA中。成功时返回0，失败时返回1。失败时，未设置FIRST、LAST、FIRSTOFFSET和LASTEXTRA。唯一的失败条件是缓冲区中没有足够的字节来执行完全遍历。*/
int lbuf_getrange(struct lbufhead* buffer, size_t offset, size_t numbytes,
                  struct otLinkedBuffer** first, size_t* firstoffset,
                  struct otLinkedBuffer** last, size_t* lastextra);

/* 返回缓冲区中存储的总字节数。*/
size_t lbuf_used_space(struct lbufhead* buffer);

#endif

