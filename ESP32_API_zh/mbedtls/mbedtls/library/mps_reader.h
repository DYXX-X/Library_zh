/*
 *  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 *  此文件是mbed TLS的一部分(https://tls.mbed.org)
 */

/**
 * \文件mps_reader.h
 *
 * \简要此文件定义了读取器对象，这些对象与它们的同级写入器对象一起构成了Mbed TLS消息传递堆栈各个层之间的通信以及消息传递堆栈与（D）TLS握手协议实现之间的通信的基础。
 *
 * 读取器提供了一种将传入数据从“生产者”传输到“消费者”的方法，“生产者”以任意大小的块提供数据，“消费者”以同样任意且可能不同的块获取和处理数据。
 *
 * 因此，读者可以被视为数据报到流的转换器，他们从用户那里抽象出以下两个任务：1。指针算法，在较小的块中逐步通过生产者提供的块。2.在消费者请求的数据块比生产者提供的数据块大的情况下，合并传入的数据块。
 *
 * 操作的基本抽象流程如下：
 * -最初，读取器处于“生产模式”。
 * -生产者将传入的数据缓冲区交给读取器，将其从“生产”模式转移到“消费”模式。
 * -消费者随后获取并处理缓冲区内容。一旦完成（或部分完成），而消费者的请求无法实现，生产者就会撤销读取器对传入数据缓冲区的访问，使读取器返回生产模式。
 * -生产者随后收集更多的传入数据并将其交给读取器，直到如果有足够的数据可用于满足最后一个消费者请求，则读取器切换回消费模式。
 * -重复上述步骤。
 *
 * 从生产者和消费者的角度来看，读者的抽象状态如下：
 *
 * -从消费者的角度来看，读者的状态包括以下内容：
 *   -表示通过调用mbedtls_mps_reader_get（）接收的数据的字节流，
 *   -当读取器通过mbedtls_mps_reader_claim（）传递回生产者时，该字节流中的一个标记指示哪些数据可以被视为已处理，因此不需要保留。标记是通过mbedtls_mps_reader_commit（）设置的，它位于当前字节流的末尾。消费者不需要知道消费者模式和生产者模式之间的区别，因为只有当阅读器处于消费模式时，它才与阅读器交互。
 *
 * -从生产者的角度来看，读者的状态是：
 *   -附：读取器处于消费模式。
 *   -未设置：读取器当前未管理任何传入数据缓冲区，所有先前移交的传入数据缓冲已完全处理。需要通过mbedtls_mps_reader_feed（）将更多数据输入读取器。
 *
 *   -累积：读取器当前没有管理传入数据缓冲区，但来自上一个传入数据缓冲的一些数据尚未处理，并且在内部被保留。附着状态属于消费模式，而未设置状态和累积状态属于生产模式。
 *
 * 通过成功调用mbedtls_mps_reader_feed（）完成从Unset或Accumuling状态到Attached状态的转换，而从Attached转换到Unset或Cumuling（取决于已处理的内容）则通过mbedtls-mps_reade_reclaim（）完成。
 *
 * 下图描述了生产者状态进展：
 *
 *        +------------------+reclaim|Unset+<------------------------------+get+--------|-------+|+--------+||||||提要+--------+--+|+-------------------------------><---+|附加|+---------------------------------><---+|提要，有足够的可用数据||||| ||||| |||+-------+-------+|+--------+|+----+----+|||<-------+commit |+--------+reclaim，以前的读取请求||无法完成||+---------+提要，需要更多的数据来服务以前的使用者请求||生产模式|消费模式|
 *
 */

#ifndef MBEDTLS_READER_H
#define MBEDTLS_READER_H

#include <stdio.h>

#include "mps_common.h"
#include "mps_error.h"

struct mbedtls_mps_reader;
typedef struct mbedtls_mps_reader mbedtls_mps_reader;

/*
 * 结构定义
 */

struct mbedtls_mps_reader
{
    unsigned char *frag;  /*!< 读取器管理的传入数据片段；它通过mbedtls_mps_reader_feed（）提供给读取器。读取器不拥有片段，也不对其执行任何分配操作，但具有对其的读写访问权限。
                           *
                           *   当且仅当\c frag不是\c NULL时，读取器处于消耗模式。*/
    mbedtls_mps_stored_size_t frag_len;
                          /*!< 当前片段的长度。如果\c frag==\c NULL，则必须为0。*/
    mbedtls_mps_stored_size_t commit;
                          /*!< 如果不存在累加器，则最后一次提交相对于片段中第一个字节的偏移量。如果存在累加器，则将其视为当前片段的前缀，并且该变量包含从累加器开始的偏移量。
                           *
                           *   仅当读取器处于消费模式时，即\c frag！=\c空；否则，其值为\c 0。*/
    mbedtls_mps_stored_size_t end;
                          /*!< 如果不存在累加器，则通过调用mbedtls_mps_reader_get（）传递给用户的最后一个块的结尾相对于片段中的第一个字节的偏移量。如果存在累加器，则将其视为当前片段的前缀，并且该变量包含从累加器开始的偏移量。
                           *
                           *   仅当读取器处于消费模式时，即\c frag！=\c空；否则，其值为\c 0。*/
    mbedtls_mps_stored_size_t pending;
                          /*!< 上次调用mbedtls_mps_reader_get（）时丢失的传入数据量。特别是，如果上次调用成功，则为\c 0。如果在对mbedtls_mps_reader_get（）的调用失败后回收读取器，则此变量用于让读取器记住应该累积多少数据，以便下次调用mbedtls-mps_reader_get（）成功。仅当读取器处于消费模式时，即\c frag！=\c空；否则，其值为\c 0。*/

    /* 只有当我们需要暂停读卡器时，才需要累加器。通过将其移动到单独的结构并在此处使用指针，可以节省几个字节。*/

    unsigned char *acc;   /*!< 如果当前片段无法提供通过mbedtls_mps_reader_get（）的读取请求，则累加器用于收集传入数据。*/
    mbedtls_mps_stored_size_t acc_len;
                           /*!< 蓄能器的总尺寸。*/
    mbedtls_mps_stored_size_t acc_available;
                          /*!< 当前在累加器中收集的字节数。这在生产和消费模式中都使用：在生产时，它会增加，直到达到下面的值。在消费时，它用于判断是否可以从累加器提供get请求。不能大于\c acc_len。*/
    union
    {
        mbedtls_mps_stored_size_t acc_remaining;
                              /*!< 这表示仍要在累加器中收集的数据量。它仅用于生产模式。最多必须为acc_len-acc_available。*/
        mbedtls_mps_stored_size_t frag_offset;
                              /*!< 如果存在累加器并且正在使用，则该字段指示当前片段从累加器开始的偏移。如果没有累加器或未使用累加器，则为\c 0。它仅用于消耗模式。不能大于\c acc_available。*/
    } acc_share;
};

/*
 * API组织：读取器对象通常由某个较低层准备和维护，并传递给上层使用，API自然会根据哪个层应该使用各自的函数进行拆分。
 */

/*
 * 维护API（下层）
 */

/**
 * \brief初始化读取器对象
 *
 * \param reader要初始化的读取器。\param acc当通过mbedtls_mps_reader_get（）的get请求超过mbedtls-mps_readeer_feed（）提供的缓冲区时，用作临时累加器的缓冲区。此缓冲区归调用者所有，在读取器的生命周期内，读取器只能用于读取和写入。因此，调用方有责任在读卡器的整个生命周期内维护（而不是触摸）缓冲区，并在读卡机被销毁后适当地归零和释放内存。\param acc_len \p acc的大小（以字节为单位）。
 *
 * \成功时返回\c 0。\失败时返回否定的\c MBEDTLS_error_READER_XXX错误代码。
 */
int mbedtls_mps_reader_init( mbedtls_mps_reader *reader,
                             unsigned char *acc,
                             mbedtls_mps_size_t acc_len );

/**
 * \brief释放读取器对象
 *
 * \param reader要释放的读取器。
 *
 * \成功时返回\c 0。\失败时返回否定的\c MBEDTLS_error_READER_XXX错误代码。
 */
int mbedtls_mps_reader_free( mbedtls_mps_reader *reader );

/**
 * \简短地传递数据块以供读者管理。
 *
 * \param reader要使用的读取器上下文。读取器必须处于生产模式。\param buf读取器要管理的缓冲区。\param buflen缓冲区的大小（以字节为单位）。
 *
 * \成功时返回\c 0。在这种情况下，读取器将移动到消费模式，并获得\p buf的读取权限，直到调用mbedtls_mps_reader_reclaim（）。调用方有责任确保\p buf持续存在，并且在成功调用mbedtls_mps_reader_feed（）和mbedtls-mps_reader_claim（）之间不会更改。\如果需要更多的输入数据来完成之前对MBEDTLS_MPS_READER_get（）的请求，则返回\c MBEDTLS_ERROR_MPS_READER_NEED_MORE。在这种情况下，读取器保持在生产模式，不拥有所提供缓冲区的所有权（而是进行内部复制）。\针对不同类型的失败返回另一个否定的\c MBEDTLS_error_READER_XXX错误代码。
 */
int mbedtls_mps_reader_feed( mbedtls_mps_reader *reader,
                             unsigned char *buf,
                             mbedtls_mps_size_t buflen );

/**
 * \简要回收读取器对当前输入缓冲区的访问。
 *
 * \param reader要使用的读取器上下文。读取器必须处于消耗模式。\param paused如果不是\c NULL，将修改地址\ppaused处的整数，以指示读取器是否已暂停（值\c 1）（值\c0）。如果有未提交的数据，并且之前对mbedtls_mps_reader_get（）的请求超出了输入缓冲区的界限，则会暂停。
 *
 * \成功时返回\c 0。\失败时返回否定的\c MBEDTLS_error_READER_XXX错误代码。
 */
int mbedtls_mps_reader_reclaim( mbedtls_mps_reader *reader,
                                int *paused );

/*
 * 使用API（上层）
 */

/**
 * \向读者简要请求数据。
 *
 * \param reader要使用的读取器上下文。读取器必须处于消耗模式。\param desired需要读取的数据量，以字节为单位。\param buffer存储缓冲区指针的地址。该地址不能为\c NULL。\param buflen存储实际缓冲区长度的地址，或\c NULL。
 *
 * \成功时返回\c 0。在这种情况下，\c*buf保存大小为\c buflen（如果\c buflen！=\c NULL）或\c所需（如果\cbuflen==\c空）的缓冲区的地址。在下一次调用mbedtls_mps_reader_claim（）之前，用户可以读取缓冲区并保证数据的稳定性。\如果没有足够的数据可用于服务获取请求，则返回#MBEDTLS_ERROR_MPS_READER_OUT_OF_DATA。在这种情况下，读取器保持完整并处于消费模式，消费者应在mbedtls_mps_reader_reclaim（）和mbedtls-mps_readeer_feed（）成功循环后重试调用。如果在这样一个周期之后，消费者请求不同数量的数据，则结果是实现定义的；只有在mbedtls_mps_reader_reclaim（）和mbedtls-mps_readeer_feed（）循环后请求相同数量的数据时，才能保证进度。\对于不同类型的失败，返回另一个负的\c MBEDTLS_error_READER_XXX错误代码。
 *
 * \注意：将\c NULL作为\p buflen传递是表示不允许碎片化的一种方便方法。它在功能上等同于将有效地址作为buflen传递，然后检查所需的\c buflen==\c。
 */
int mbedtls_mps_reader_get( mbedtls_mps_reader *reader,
                            mbedtls_mps_size_t desired,
                            unsigned char **buffer,
                            mbedtls_mps_size_t *buflen );

/**
 * \brief将从mbedtls_mps_reader_get（）获得的数据标记为已处理。
 *
 *                此调用表示在调用mbedtls_mps_reader_claim（）时，从先前对mbedtls-mps_reader_get（）的调用中接收到的所有数据都已或将被处理，因此不需要备份。
 *
 *                在调用mbedtls_mps_reader_claim（）之前，此函数没有用户可观察到的效果。特别是，从mbedtls_mps_reader_get（）接收的缓冲区在调用mbedtls-mps_reader_claim（）之前保持有效。
 *
 * \param reader要使用的读取器上下文。
 *
 * \成功时返回\c 0。\失败时返回否定的\c MBEDTLS_error_READER_XXX错误代码。
 *
 */
int mbedtls_mps_reader_commit( mbedtls_mps_reader *reader );

#endif /* MBEDTLS_READER_H */

