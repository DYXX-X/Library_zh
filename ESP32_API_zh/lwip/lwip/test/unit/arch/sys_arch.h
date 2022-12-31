/*
 * 版权所有（c）2017 Simon Goldschmidt保留所有权利。
 * 
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT  SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY  OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 * 
 * 作者：Simon Goldschmidt
 *
 */
#ifndef LWIP_HDR_TEST_SYS_ARCH_H
#define LWIP_HDR_TEST_SYS_ARCH_H

typedef int sys_sem_t;
#define sys_sem_valid(sema) ((sema) != NULL)

typedef int sys_mutex_t;
#define sys_mutex_valid(mutex) (((mutex) != NULL)

struct lwip_mbox {
  void* sem;
  void** q_mem;
  unsigned int head, tail;
  int size;
  int used;
};
typedef struct lwip_mbox sys_mbox_t;
#define SYS_MBOX_NULL NULL
#define sys_mbox_valid(mbox) ((mbox != NULL) && ((mbox)->sem != NULL)  && ((mbox)->sem != (void*)-1))
#define sys_mbox_valid_val(mbox) (((mbox).sem != NULL)  && ((mbox).sem != (void*)-1))

/* DWORD（线程id）用于sys_thread_t，但我们不包括窗口。小时*/
typedef u32_t sys_thread_t;

#define SYS_ARCH_DECL_PROTECT(lev)
#define SYS_ARCH_PROTECT(lev)
#define SYS_ARCH_UNPROTECT(lev)

/* 要实现在阻塞mbox或信号量时执行某些操作，请将一个函数传递给test_sys_arch_wait_callback（），如果再次等待，则返回“0”，如果现在应该执行某些操作（用于断言）则返回“1”
 */
typedef int (*test_sys_arch_waiting_fn)(sys_sem_t* wait_sem, sys_mbox_t* wait_mbox);
void test_sys_arch_wait_callback(test_sys_arch_waiting_fn waiting_fn);

/* 当前时间*/
extern u32_t lwip_sys_now;

#endif /* LWIP_HDR_TEST_SYS_ARCH_H */


