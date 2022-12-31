/**
 * @file 用于实现线程同步的SNMP服务器MIB API
 */

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
 *
 * 作者：Dirk Ziegelmeier<dziegel@gmx.de>
 *
 */

#ifndef LWIP_HDR_APPS_SNMP_THREADSYNC_H
#define LWIP_HDR_APPS_SNMP_THREADSYNC_H

#include "lwip/apps/snmp_opts.h"

#ifdef __cplusplus
extern "C" {
#endif

#if LWIP_SNMP /* 如果未配置为在lwipopts.h中使用，则不要构建*/

#include "lwip/apps/snmp_core.h"
#include "lwip/sys.h"

typedef void (*snmp_threadsync_called_fn)(void* arg);
typedef void (*snmp_threadsync_synchronizer_fn)(snmp_threadsync_called_fn fn, void* arg);


/**线程同步运行时数据。仅供内部使用。*/
struct threadsync_data
{
  union {
    snmp_err_t err;
    s16_t s16;
  } retval;
  union {
    const u32_t *root_oid;
    void *value;
  } arg1;
  union {
    u8_t root_oid_len;
    u16_t len;
  } arg2;
  const struct snmp_threadsync_node *threadsync_node;
  struct snmp_node_instance proxy_instance;
};

/**线程同步实例。每个要同步到的线程都需要EXCATLY一次。*/
struct snmp_threadsync_instance
{
  sys_sem_t                       sem;
  sys_mutex_t                     sem_usage_mutex;
  snmp_threadsync_synchronizer_fn sync_fn;
  struct threadsync_data          data;
};

/**SNMP线程同步代理叶节点*/
struct snmp_threadsync_node
{
  /* 继承的“基类”成员*/
  struct snmp_leaf_node           node;

  const struct snmp_leaf_node     *target;
  struct snmp_threadsync_instance *instance;
};

snmp_err_t snmp_threadsync_get_instance(const u32_t *root_oid, u8_t root_oid_len, struct snmp_node_instance* instance);
snmp_err_t snmp_threadsync_get_next_instance(const u32_t *root_oid, u8_t root_oid_len, struct snmp_node_instance* instance);

/**创建线程同步代理节点*/
#define SNMP_CREATE_THREAD_SYNC_NODE(oid, target_leaf_node, threadsync_instance) \
  {{{ SNMP_NODE_THREADSYNC, (oid) }, \
    snmp_threadsync_get_instance, \
    snmp_threadsync_get_next_instance }, \
    (target_leaf_node), \
    (threadsync_instance) }

/**创建线程同步实例数据*/
void snmp_threadsync_init(struct snmp_threadsync_instance *instance, snmp_threadsync_synchronizer_fn sync_fn);

#endif /* LWIP_SNMP */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_APPS_SNMP_THREADSYNC_H */

