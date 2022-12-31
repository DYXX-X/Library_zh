/**
 *
 * @file tftp_server.h
 *
 * @author   洛根·冈索普<logang@deltatee.com>
 *
 * @brief    普通文件传输协议（RFC 1350）
 *
 * 版权所有（c）Deltatee Enterprises Ltd.2013保留所有权利。
 *
 */

/* 
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 作者：Logan Gunthrope<logang@deltatee.com>
 *
 */

#ifndef LWIP_HDR_APPS_TFTP_SERVER_H
#define LWIP_HDR_APPS_TFTP_SERVER_H

#include "lwip/apps/tftp_opts.h"
#include "lwip/err.h"
#include "lwip/pbuf.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup tftp tftp上下文包含tftp传输的回调函数
 */
struct tftp_context {
  /**
   * 打开文件进行读/写。
   * @param fname 文件名
   * @param mode TFTP RFC 1350的模式字符串（netascii、八位字节、邮件）
   * @param write 指示读（0）或写（！=0）访问的标志
   * @returns 提供给其他函数的文件句柄
   */
  void* (*open)(const char* fname, const char* mode, u8_t write);
  /**
   * 关闭文件句柄
   * @param handle open（）返回的文件句柄
   */
  void (*close)(void* handle);
  /**
   * 从文件读取
   * @param handle open（）返回的文件句柄
   * @param buf 将读取数据复制到的目标缓冲区
   * @param bytes 要复制到buf的字节数
   * @returns &gt；=0：成功&书信电报；0:错误
   */
  int (*read)(void* handle, void* buf, int bytes);
  /**
   * 写入文件
   * @param handle open（）返回的文件句柄
   * @param pbuf PBUF进行了调整，使得有效负载指针指向写入数据的开始。换句话说，TFTP标头被剥离。
   * @returns &gt；=0：成功&书信电报；0:错误
   */
  int (*write)(void* handle, struct pbuf* p);
};

err_t tftp_init(const struct tftp_context* ctx);
void tftp_cleanup(void);

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_APPS_TFTP_SERVER_H */

