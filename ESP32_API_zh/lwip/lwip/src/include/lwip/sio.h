/*
 * 版权所有（c）2001-2004瑞典计算机科学研究所。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 */

/*
 * 这是特定于平台的串行IO模块的接口，需要由需要SLIP或PPP的平台实现
 */

#ifndef SIO_H
#define SIO_H

#include "lwip/arch.h"
#include "lwip/opt.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 如果您想在其他地方或其他地方定义sio_fd_t，请在cc中定义它。h文件。*/
#ifndef __sio_fd_t_defined
typedef void * sio_fd_t;
#endif

/* 以下函数可以定义为cc中的其他函数。h文件或在自定义sio中实现。c文件。*/

#ifndef sio_open
/**
 * 打开串行设备进行通信。
 *
 * @param devnum 设备编号
 * @return 如果成功，则处理到串行设备，否则为NULL
 */
sio_fd_t sio_open(u8_t devnum);
#endif

#ifndef sio_send
/**
 * 向串行设备发送单个字符。
 *
 * @param c 要发送的字符
 * @param fd 串行设备句柄
 *
 * @note 此函数将阻止，直到可以发送字符。
 */
void sio_send(u8_t c, sio_fd_t fd);
#endif

#ifndef sio_recv
/**
 * 从串行设备接收单个字符。
 *
 * @param fd 串行设备句柄
 *
 * @note 此功能将阻止，直到收到字符。
 */
u8_t sio_recv(sio_fd_t fd);
#endif

#ifndef sio_read
/**
 * 从串行设备读取。
 *
 * @param fd 串行设备句柄
 * @param data 用于接收的数据缓冲区指针
 * @param len 要接收的数据的最大长度（字节）
 * @return 实际接收的字节数-如果被sio_read_abort中止，则可能为0
 *
 * @note 此功能将被阻止，直到可以接收到数据。可以通过调用sio_read_abort（）来取消阻塞。
 */
u32_t sio_read(sio_fd_t fd, u8_t *data, u32_t len);
#endif

#ifndef sio_tryread
/**
 * 尝试从串行设备读取。与sio_read相同，但如果没有可用数据且从不阻塞，则立即返回。
 *
 * @param fd 串行设备句柄
 * @param data 用于接收的数据缓冲区指针
 * @param len 要接收的数据的最大长度（字节）
 * @return 实际接收的字节数
 */
u32_t sio_tryread(sio_fd_t fd, u8_t *data, u32_t len);
#endif

#ifndef sio_write
/**
 * 写入串行设备。
 *
 * @param fd 串行设备句柄
 * @param data 指向要发送的数据的指针
 * @param len 要发送的数据长度（字节）
 * @return 实际发送的字节数
 *
 * @note 此功能将阻止，直到可以发送所有数据。
 */
u32_t sio_write(sio_fd_t fd, u8_t *data, u32_t len);
#endif

#ifndef sio_read_abort
/**
 * 中止阻塞的sio_read（）调用。
 *
 * @param fd 串行设备句柄
 */
void sio_read_abort(sio_fd_t fd);
#endif

#ifdef __cplusplus
}
#endif

#endif /* SIO_H */

