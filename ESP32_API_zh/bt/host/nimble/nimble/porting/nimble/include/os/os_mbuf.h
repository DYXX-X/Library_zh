/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */


/**
 * @addtogroup OS内核@{
 *   @defgroup OSMbuf链式内存缓冲区@{
 */


#ifndef _OS_MBUF_H
#define _OS_MBUF_H

#include "os/os.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 从中分配mbuf的mbuf池。这包含一个指向要分配mbuf的os mempool的指针、池中的元素总数以及非数据包头mbuf中的“用户”数据量。总池大小（字节）应为：os_mbuf_count（omp_databuf_len+sizeof（struct os_mbuf））
 */
struct os_mbuf_pool {
    /**
     * 每个mbuf中数据缓冲区的总长度。这是mempool块的大小，减去mbuf标头
     */
    uint16_t omp_databuf_len;
    /**
     * 要分配mbuf的内存池
     */
    struct os_mempool *omp_pool;

    STAILQ_ENTRY(os_mbuf_pool) omp_next;
};


/**
 * 位于mbuf数据包报头之前的数据包报头结构。
 */
struct os_mbuf_pkthdr {
    /**
     * 数据包的总长度。
     */
    uint16_t omp_len;
    /**
     * 旗帜
     */
    uint16_t omp_flags;

    STAILQ_ENTRY(os_mbuf_pkthdr) omp_next;
};

/**
 * 链式内存缓冲区。
 */
struct os_mbuf {
    /**
     * 指向结构中数据的当前指针
     */
    uint8_t *om_data;
    /**
     * 与此缓冲区相关的标志，请参阅OS_MBUF_F_*定义
     */
    uint8_t om_flags;
    /**
     * 包头长度
     */
    uint8_t om_pkthdr_len;
    /**
     * 此缓冲区中的数据长度
     */
    uint16_t om_len;

    /**
     * 这个mbuf分配的mbuf池
     */
    struct os_mbuf_pool *om_omp;

    SLIST_ENTRY(os_mbuf) om_next;

    /**
     * 指向此缓冲区之后数据开头的指针
     */
    uint8_t om_databuf[0];
};

/**
 * 表示mbufs队列的结构。
 */
struct os_mqueue {
    STAILQ_HEAD(, os_mbuf_pkthdr) mq_head;
    /**队列上有新缓冲区时要发布的事件。*/
    struct ble_npl_event mq_ev;
};

/*
 * 给定标志号，提供其掩码
 *
 * @param __n 掩码中标志的编号
 */
#define OS_MBUF_F_MASK(__n) (1 << (__n))

/*
 * 检查给定的mbuf是否为数据包头mbuf
 *
 * @param __om 要检查的mbuf
 */
#define OS_MBUF_IS_PKTHDR(__om) \
    ((__om)->om_pkthdr_len >= sizeof (struct os_mbuf_pkthdr))

/**获取给定mbuf指针的数据包标头指针*/
#define OS_MBUF_PKTHDR(__om) ((struct os_mbuf_pkthdr *)     \
    ((uint8_t *)&(__om)->om_data + sizeof(struct os_mbuf)))

/**给定mbuf包头指针，返回指向mbuf的指针*/
#define OS_MBUF_PKTHDR_TO_MBUF(__hdr)   \
     (struct os_mbuf *)((uint8_t *)(__hdr) - sizeof(struct os_mbuf))

/**
 * 获取整个mbuf链的长度。指定的mbuf必须具有数据包标头。
 */
#define OS_MBUF_PKTLEN(__om) (OS_MBUF_PKTHDR(__om)->omp_len)

/**
 * 访问mbuf的数据，并将其转换为类型
 *
 * @param __om 要访问和铸造的mbuf
 * @param __type 要将其强制转换为的类型
 */
#define OS_MBUF_DATA(__om, __type) \
     (__type) ((__om)->om_data)

/**
 * 访问mbuf链头部的“用户标头”。
 *
 * @param om                    指向mbuf链头部的指针。
 */
#define OS_MBUF_USRHDR(om)                              \
    (void *)((uint8_t *)om + sizeof (struct os_mbuf) +  \
             sizeof (struct os_mbuf_pkthdr))

/**
 * 检索mbuf中用户标头的长度。
 *
 * @param om                    指向要查询的mbuf的指针。
 */
#define OS_MBUF_USRHDR_LEN(om) \
    ((om)->om_pkthdr_len - sizeof (struct os_mbuf_pkthdr))


/**@第二个INTERNAL_HIDDEN*/

/*
 * 由OS_MBUF_LEADINGSPACE（）宏调用
 */
static inline uint16_t
_os_mbuf_leadingspace(struct os_mbuf *om)
{
    uint16_t startoff;
    uint16_t leadingspace;

    startoff = 0;
    if (OS_MBUF_IS_PKTHDR(om)) {
        startoff = om->om_pkthdr_len;
    }

    leadingspace = (uint16_t) (OS_MBUF_DATA(om, uint8_t *) -
        ((uint8_t *) &om->om_databuf[0] + startoff));

    return (leadingspace);
}

/**@结束秒*/

/**
 * 返回mbuf的前导空格（开头的空格）。既适用于包头，也适用于常规mbuf，因为它占分配给包头的额外空间。
 *
 * @param __omp 是mbuf池（包含数据包标头长度。）
 * @param __om  游泳池里的mbuf是为了获得领先的空间吗
 *
 * @return mbuf中可用的引导空间量
 */
#define OS_MBUF_LEADINGSPACE(__om) _os_mbuf_leadingspace(__om)


/**@第二个INTERNAL_HIDDEN*/

/* 由OS_MBUF_RAILINGSPACE（）宏调用。*/
static inline uint16_t
_os_mbuf_trailingspace(struct os_mbuf *om)
{
    struct os_mbuf_pool *omp;

    omp = om->om_omp;

    return (&om->om_databuf[0] + omp->omp_databuf_len) -
      (om->om_data + om->om_len);
}

/**@结束秒*/

/**
 * 返回mbuf的尾部空格（末尾的空格）。同时适用于包头和常规mbuf。
 *
 * @param __omp 这个mbuf的mbuf池
 * @param __om  那游泳池里的mbuf是用来获得尾随空间的吗
 *
 * @return mbuf中可用的尾部空间量
 */
#define OS_MBUF_TRAILINGSPACE(__om) _os_mbuf_trailingspace(__om)


/**
 * 初始化mqueue。mqueue是绑定到特定任务的事件队列的mbuf队列。Mqueues围绕一个共同的范例形成了一个助手API：等待事件队列，直到至少有一个数据包可用，然后处理数据包队列。
 *
 * 当队列中的mbuf可用时，事件OS_event_T_MQUE_DATA将发布到任务的mbuf队列中。
 *
 * @param mq                    要初始化的mqueue
 * @param ev_cb                 要与mqeue事件关联的回调。通常，此回调会从mqueue中提取每个数据包并处理它们。
 * @param arg                   要与mqueue事件关联的参数。
 *
 * @return                      成功时为0，失败时为非零。
 */
int os_mqueue_init(struct os_mqueue *mq, ble_npl_event_fn *ev_cb, void *arg);

/**
 * 从mbuf队列中移除并返回单个mbuf。不阻塞。
 *
 * @param mq 要从中拉出元素的mbuf队列。
 *
 * @return 队列中的下一个mbuf，如果队列没有mbuf则为NULL。
 */
struct os_mbuf *os_mqueue_get(struct os_mqueue *);

/**
 * 向mqueue添加数据包（即数据包头mbuf）。与mqueue关联的事件被发布到指定的事件q。
 *
 * @param mq                    要将mbuf附加到的mbuf队列。
 * @param evq                   要向其发布事件的事件队列。
 * @param m                     要附加到mbuf队列的mbuf。
 *
 * @return 成功时为0，失败时为非零。
 */
int os_mqueue_put(struct os_mqueue *, struct ble_npl_eventq *, struct os_mbuf *);

/**
 * MSYS是一个系统级mbuf注册表。允许系统在可以同时运行的各种网络堆栈之间共享数据包缓冲区。
 *
 * Mbuf池是在系统初始化代码中创建的，然后当Mbuf从msys中分配出来时，它将根据估计的Mbuf大小来尝试找到最佳匹配。
 *
 * os_msys_register（）向msys注册mbuf池，并允许msys从中分配mbuf。
 *
 * @param new_pool 要向MSYS注册的池
 *
 * @return 成功时为0，失败时为非零
 */
int os_msys_register(struct os_mbuf_pool *);

/**
 * 从msys分配一个mbuf。根据请求的数据大小，os_msys_get（）将选择最适合的mbuf池。
 *
 * @param dsize 存储在mbuf中的数据的估计大小
 * @param leadingspace 要在mbuf中分配的引导空间量
 *
 * @return 成功时为新分配的mbuf，失败时为NULL。
 */
struct os_mbuf *os_msys_get(uint16_t dsize, uint16_t leadingspace);

/**
 * 从msys中注销所有mbuf池。
 */
void os_msys_reset(void);

/**
 * 从MSYS池分配数据包报头结构。有关msys的说明，请参见os_msys_register（）。
 *
 * @param dsize 存储在mbuf中的数据的估计大小
 * @param user_hdr_len 要为数据包标头结构分配的长度
 *
 * @return 成功时为新分配的mbuf，失败时为NULL。
 */
struct os_mbuf *os_msys_get_pkthdr(uint16_t dsize, uint16_t user_hdr_len);

/**
 * 计算分配的所有mbuf池中的块数。
 *
 * @return 以Msys为单位分配的块总数
 */
int os_msys_count(void);

/**
 * 返回Msys中的可用块数
 *
 * @return 可用的可用块数（Msys）
 */
int os_msys_num_free(void);

/**
 * 初始化mbuf池。
 *
 * @param omp     要初始化的mbuf池
 * @param mp      将保存此mbuf池的内存池
 * @param buf_len 缓冲区本身的长度。
 * @param nbufs   池中的缓冲区数
 *
 * @return 成功时为0，失败时为错误代码。
 */
int os_mbuf_pool_init(struct os_mbuf_pool *, struct os_mempool *mp,
        uint16_t, uint16_t);

/**
 * 从mbuf池中获取mbuf。mbuf在返回之前被分配和初始化。
 *
 * @param omp 要从中返回数据包的mbuf池
 * @param leadingspace 默认情况下放置在数据段之前的引导空间量。
 *
 * @return 成功时初始化mbuf，失败时为NULL。
 */
struct os_mbuf *os_mbuf_get(struct os_mbuf_pool *omp, uint16_t);

/**
 * 从os_mbuf_pool中分配一个新的包头mbuf。
 *
 * @param omp 要分配的mbuf池
 * @param user_pkthdr_len 要为调用者保留的数据包标头长度。
 *
 * @return 成功时为新分配的mbuf，失败时为NULL。
 */
struct os_mbuf *os_mbuf_get_pkthdr(struct os_mbuf_pool *omp,
        uint8_t pkthdr_len);

/**
 * 复制一系列mbufs。返回复制链的起点。
 *
 * @param omp 要复制的mbuf池
 * @param om  要复制的mbuf链
 *
 * @return 指向新mbufs链的指针
 */
struct os_mbuf *os_mbuf_dup(struct os_mbuf *m);

/**
 * 在mbuf链中定位指定的绝对偏移。偏移量可以是链条总长度的一倍，但不能大于。
 *
 * @param om                    要寻找的mbuf链的起点。
 * @param off                   要查找的绝对地址。
 * @param out_off               成功后，这将指向返回mbuf内的相对偏移。
 *
 * @return                      成功时包含指定偏移量的mbuf。如果指定的偏移量超出范围，则为NULL。
 */
struct os_mbuf *os_mbuf_off(const struct os_mbuf *om, int off,
                            uint16_t *out_off);


/*
 * 将mbuf链中的数据从一开始的“off”字节开始，继续“len”字节，复制到指定的缓冲区中。
 *
 * @param m 要复制的mbuf链
 * @param off 要开始复制的mbuf链的偏移量
 * @param len 要复制的数据的长度
 * @param dst 要复制到的目标缓冲区
 *
 * @return                      成功时为0；
 *                              -1，如果mbuf不包含足够的数据。
 */
int os_mbuf_copydata(const struct os_mbuf *m, int off, int len, void *dst);

/**
 * 将数据附加到mbuf
 *
 * @param om   要将数据附加到的mbuf
 * @param data 要附加到mbuf的数据
 * @param len  要附加的数据的长度
 *
 * @return 成功时为0，失败时为错误代码
 */
int os_mbuf_append(struct os_mbuf *m, const void *, uint16_t);

/**
 * 从一个mbuf读取数据并将其附加到另一个mbf。出现错误时，可能会部分追加指定的数据范围。两个mbuf都不需要包含mbuf数据包报头。
 *
 * @param dst                   要附加到的mbuf。
 * @param src                   要从中复制数据的mbuf。
 * @param src_off               要读取的源mbuf链内的绝对偏移量。
 * @param len                   要追加的字节数。
 *
 * @return                      成功时为0；如果指定范围超出源mbuf链的末端，则返回OS_EINVAL。
 */
int os_mbuf_appendfrom(struct os_mbuf *dst, const struct os_mbuf *src,
                       uint16_t src_off, uint16_t len);

/**
 * 释放一个mbuf回到游泳池
 *
 * @param omp 要释放回的Mbuf池
 * @param om  Mbuf将释放回游泳池
 *
 * @return 成功时为0，失败时为-1
 */
int os_mbuf_free(struct os_mbuf *mb);

/**
 * 释放一系列mbufs
 *
 * @param omp mbuf池将mbuf链释放到
 * @param om  链的起始mbuf将自由返回到池中
 *
 * @return 成功时为0，失败时为-1
 */
int os_mbuf_free_chain(struct os_mbuf *om);

/**
 * 调整燃烧室的长度，从燃烧室的头部或尾部修剪。
 *
 * @param mp 要调整的mbuf链条
 * @param req_len 从mbuf修剪的长度。如果为正，则从mbuf头部修剪，如果为负，则从mb尾部修剪。
 */
void os_mbuf_adj(struct os_mbuf *mp, int req_len);


/**
 * 将mbuf链的指定区域与平面缓冲区进行内存比较。
 *
 * @param om                    要比较的mbuf链的起点。
 * @param off                   mbuf链中开始比较的偏移量。
 * @param data                  要比较的平面缓冲区。
 * @param len                   平面缓冲区的长度。
 *
 * @return                      如果两个存储区域相同，则为0；如果不匹配，则返回memcmp代码；如果mbuf太短，则返回INT_MAX。
 */
int os_mbuf_cmpf(const struct os_mbuf *om, int off, const void *data, int len);

/**
 * 比较两个mbuf链的内容。通过两个偏移参数和len参数指定要比较的两个链的范围。mbuf链都不需要包含数据包标头。
 *
 * @param om1                   第一个要比较的mbuf链。
 * @param offset1               om1内开始比较的绝对偏移量。
 * @param om2                   要比较的第二个mbuf链。
 * @param offset2               om2内开始比较的绝对偏移量。
 * @param len                   要比较的字节数。
 *
 * @return                      如果两个mbuf段相同，则为0；如果段内容不同，则返回memcmp（）代码；INT_MAX，如果指定范围超出其对应mbuf链的末端。
 */
int os_mbuf_cmpm(const struct os_mbuf *om1, uint16_t offset1,
                 const struct os_mbuf *om2, uint16_t offset2,
                 uint16_t len);

/**
 * 通过向前端添加数据来增加mbuf链的长度。如果前导mbuf中的空间不足，则分配额外的mbuf并根据需要预先准备。如果此函数未能分配mbuf，则释放整个链。
 *
 * 指定的mbuf链不需要包含数据包标头。
 *
 * @param omp                   要从中分配的mbuf池。
 * @param om                    燃烧链的头部。
 * @param len                   要前置的字节数。
 *
 * @return                      成功链的新负责人；失败时为NULL。
 */
struct os_mbuf *os_mbuf_prepend(struct os_mbuf *om, int len);

/**
 * 在指定的mbuf链中预先添加一块空数据，并确保该块是连续的。如果任一操作失败，则释放指定的mbuf链并返回NULL。
 *
 * @param om                    要准备的mbuf链。
 * @param len                   要前置和上拉的字节数。
 *
 * @return                      修改后的mbuf成功；失败时为NULL（mbuf链被释放）。
 */
struct os_mbuf *os_mbuf_prepend_pullup(struct os_mbuf *om, uint16_t len);

/**
 * 从指定的目标偏移量开始，将平面缓冲区的内容复制到mbuf链中。如果mbuf对于源数据来说太小，则会根据需要进行扩展。如果目标mbuf包含包报头，则更新报头长度。
 *
 * @param omp                   要从中分配的mbuf池。
 * @param om                    要复制到的mbuf链。
 * @param off                   要复制到的链中的偏移量。
 * @param src                   要从中复制的源缓冲区。
 * @param len                   要复制的字节数。
 *
 * @return                      成功时为0；失败时为非零。
 */
int os_mbuf_copyinto(struct os_mbuf *om, int off, const void *src, int len);

/**
 * 将第二个mbuf链连接到第一个mbuf链的末端。如果第一个链包含数据包标头，则标头的长度将被更新。如果第二个链具有数据包报头，则清除其报头。
 *
 * @param first                 正在连接的mbuf链。
 * @param second                连接的mbuf链。
 */
void os_mbuf_concat(struct os_mbuf *first, struct os_mbuf *second);


/**
 * 按指定的量增加mbuf链的长度。如果最后一个缓冲区中没有足够的空间，则会分配一个新的缓冲区并将其附加到链中。请求的数据超过单个缓冲区的容量是错误的。
 *
 * @param omp
 * @param om                    要延伸的链条的头部。
 * @param len                   要扩展的字节数。
 *
 * @return                      指向成功的新数据的指针；失败时为NULL。
 */
void *os_mbuf_extend(struct os_mbuf *om, uint16_t len);

/**
 * 重新排列mbuf链，使len字节连续，并在mbuf的数据区域中（这样OS_mbuf_data（）将处理大小为len的结构）。成功时返回生成的mbuf链条，释放它，失败时返回NULL。
 *
 * 如果有空间，它将向相邻区域添加“max_protohdr-len”额外字节，以避免下次调用。
 *
 * @param omp 将mbuf从中取出的mbuf池
 * @param om 使相邻的mbuf链
 * @param len 链中要连续的字节数
 *
 * @return 成功时为连续mbuf链，失败时为NULL。
 */
struct os_mbuf *os_mbuf_pullup(struct os_mbuf *om, uint16_t len);


/**
 * 从链的前部移除并释放空mbufs。如果链包含数据包标头，则将保留它。
 *
 * @param om                    要修剪的mbuf链条。
 *
 * @return                      修剪后的mbuf链的头部。
 */
struct os_mbuf *os_mbuf_trim_front(struct os_mbuf *om);

/**
 * 利用结果链中所有mbuf中的所有可用缓冲空间，从m1和m2创建一个单链mbuf。换句话说，确保在生成的链中的任何mbuf中没有前导空间，而仅在链中的最后一个mbuf上有尾随空间。如果不需要，可以释放任一链中的Mbufs。未分配mbufs。请注意，来自m2的mbufs被添加到m1的末尾。如果m1具有数据包报头，则保留它并更新长度。如果m2具有分组报头，则丢弃它。如果m1为NULL，则返回NULL，m2保持不变。
 *
 * @param m1 指向要打包的第一个mbuf链的指针
 * @param m2 指向要打包的第二个mbuf链的指针
 *
 * @return structos_mbuf*指向结果mbuf链的指针
 */
struct os_mbuf *os_mbuf_pack_chains(struct os_mbuf *m1, struct os_mbuf *m2);

#ifdef __cplusplus
}
#endif

#endif /* _OS_MBUF_H */


/**
 *   @} OSMbuf公司
 * @} 操作系统核心
 */

