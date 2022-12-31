/*
 *    版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *    在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file 此文件包含尖晶石的定义。
 */

#ifndef SPINEL_HEADER_INCLUDED
#define SPINEL_HEADER_INCLUDED 1

/*
 *   Spinel是一种主机控制器协议，旨在通过通用设备操作系统（OS）主机和网络协处理器（NCP）之间的简单串行连接实现互操作，以控制和管理NCP。
 *
 * ---------------------------------------------------------------------------
 *
 *   框架格式
 *
 *   一个框架被简单地定义为
 *
 *   -标题字节
 *   -一个命令（最多三个字节）
 *   -可选命令有效载荷
 *
 *              +---------+--------+-----+-------------+|八位字节：|1 | 1-3 | n |+---------+---------+---------------+|字段：|HEADER|CMD|CMD_PAYLOAD|+---------+--------+-----+-------------+
 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 *   页眉格式
 *
 *   标头字节细分如下：
 *
 *                    0   1   2   3   4   5   6   7 +---+---+---+---+---+---+---+---+ | FLG | IID | TID | +---+---+---+---+---+---+---+---+
 *
 * 标头字节（“FLG”）的标志字段始终设置为值2（或二进制中的“10”）。任何接收到的这些位设置为任何其他值的帧都不得被视为Spinel帧。
 *
 *   该约定允许Spinel与BTLE HCI线兼容。通过以这种方式定义前两位，我们可以消除Spinel帧和HCI帧（总是以“0x01”或“0x04”开头）之间的歧义，而无需任何额外的帧开销。
 *
 *   接口标识符（IID）是一个介于0和3之间的数字，由操作系统与特定NCP相关联。这允许协议在同一连接下支持多达4个NCP。
 *
 *   标头的最低有效位表示事务标识符（TID）。TID用于将响应与生成它们的命令相关联。
 *
 *   当从主机发送命令时，NCP对该命令的任何回复都将使用相同的TID值。当主机接收到与它发送的命令的TID相匹配的帧时，它可以很容易地将该帧识别为对该命令的实际响应。
 *
 *   TID值为零（0）用于不期望或不需要相关响应的命令，例如从NCP发送到主机的未经请求的更新命令。
 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 *   命令标识符是一个21位无符号整数，使用下面描述的压缩无符号整数格式编码为最多三个字节。根据所讨论命令的语义，帧中可能包含有效载荷。有效载荷的确切组成和长度由命令标识符定义。
 *
 * ---------------------------------------------------------------------------
 *
 *   数据打包
 *
 *   属性的数据序列化是使用一种轻量级数据打包格式执行的，这种格式受到D-Bus的松散启发。序列化的格式由特殊格式的字符串定义。
 *
 *   此包装格式用于表示方便。虽然这种基于字符串的数据类型格式被设计为可以由结构化数据解析器直接使用字符串，但实现Spinel并不需要这样的东西。
 *
 *   目标：
 *
 *   -重量轻，有利于价值观的直接表达。
 *   -使用易于阅读和记忆的格式字符串。
 *   -支持列表和结构。
 *   -允许将属性附加到结构，同时保持向后兼容性。
 *
 *   每个基本数据类型都有一个与之相关的ASCII字符。结构可以表示为这些字符的字符串。例如：
 *
 *   -“C”：单个无符号字节。
 *   -“C6U”：单个无符号字节，后跟128位IPv6地址，后跟以零结尾的UTF8字符串。
 *   -“A（6）”：连接的IPv6地址数组
 *
 *   在每种情况下，数据都完全按照所述进行表示。例如，10个IPv6地址的数组存储为160字节。
 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 *   图元类型
 *
 *   +----------+----------------------+---------------------------------+| Char|名称|描述|+----------+-------------------------------+|“.”| DATATYPE_VOID |空数据类型。内部使用||||。||“b”| DATATYPE_BOOL |布尔值。以|||8位编码为0x00或0x01。||||所有其他值都是非法的。||“C”|DATATYPE_UINT8|无符号8位整数。||“c”|DATATYPE_INT8|有符号8位整数。||“S”| DATATYPE_UINT16 |无符号16位整数。||“s”| DATATYPE_INT16 |有符号16位整数。||“L”| DATATYPE_UINT32 |无符号32位整数。||“l”| DATATYPE_INT32 |有符号32位整数。||“i”|DATATYPE_UINT_PACKED|压缩无符号整数。请参阅下面的描述||“6”|DATATYPE_IPv6ADDR|IPv6地址。（大端）||“E”|DATATYPE_EUI64|EUI-64地址。（大端）||“e”|DATATYPE_EUI48|EUI-48地址。（大端）||“D”|DATATYPE_DATA|任意数据。有关详细信息，请参阅下面的相关部分。||“d”|DATATYPE_DATA_WLEN|具有前缀||||长度的任意数据。有关详细信息，请参见下文||“U”|DATATYPE_UTF8|以零结尾的UTF8编码||||字符串。||“t（…）”|DATATYPE_STRUCT|带有||||前缀长度的结构化数据类型。||“A（…）”|DATATYPE_ARRAY|数据类型数组。复合||||类型。|+----------+----------------------+---------------------------------+
 *
 *   除非另有明确说明，否则所有多字节值都是小端值。
 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 *   压缩无符号整数
 *
 *   对于某些类型的整数，例如命令或属性标识符，通常导线上的值小于127。但是，为了不排除使用大于255的值，我们需要添加一个额外的字节。这样做会给大多数实例增加一个额外的字节，这会增加带宽。
 *
 *   压缩无符号整数格式基于EXI中的无符号整数，除了我们将最大值限制为可以编码为三个字节的最大值（2097151）。
 *
 *   对于所有小于127的值，数字的压缩形式只是直接表示数字的单个字节。对于大于127的值，使用以下过程对值进行编码：
 *
 *   1.无符号整数被分成_n_7位块，并放入_n_个八位字节中，每个八位字节的最高有效位未使用。2.将八位位组从最低有效到最高有效排序。（Little-endian）3.清除最高有效八位字节的最高有效位。设置所有其他八位字节的最低有效位。
 *
 *   其中“n”是可用于表示给定值的最小7位块数。
 *
 *   以值1337为例：
 *
 *                              1337=>0x0539=>[39 0A]=>[B9 0A]
 *
 *   要解码该值，请收集7位块，直到找到具有最高有效位的八位位组。
 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 *   数据Blob
 *
 *   数据块有两种类型：“d”和“d”。
 *
 *   -“d”具有数据前面的数据长度（以字节为单位）（长度编码为类型“S”）。长度字段的大小不包含在长度中。
 *   -“D”没有预设的长度：数据的长度由剩余的待解析字节表示。“D”不是类型签名中类型的最后一个类型是错误的。
 *
 *   这种二分法允许通过消除冗余来进行更有效的编码。如果缓冲区的其余部分是数据blob，那么编码长度将是多余的，因为我们已经知道缓冲区的剩余部分中有多少字节。
 *
 *   在某些情况下，我们使用“d”，即使它是类型签名中的最后一个字段。我们这样做是为了在将来有必要的时候能够在类型签名中附加额外的字段。这通常是嵌入结构的情况，如扫描结果中的情况。
 *
 *   例如，假设我们有一个缓冲区，该缓冲区使用数据类型签名“CLLD”进行编码。在这种情况下，很容易区分数据blob的开始和结束位置：开始是从缓冲区开始的9个字节，其长度是缓冲区的长度减去9。（9是一个字节和两个长字节占用的字节数）
 *
 *   数据类型签名“CLLDU”是非法的，因为我们无法确定最后一个字段（以零结尾的UTF8字符串）的起始位置。但是数据类型“CLLdU”是合法的，因为解析器可以确定数据blob的确切长度——允许它知道下一个字段的开始位置。
 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 *   结构化数据
 *
 *   结构数据类型（“t（…）”）是将多个字段绑定到单个结构中的一种方式。它可以被认为是“d”类型，只是内容中的字段不是不透明的，而是已知的。这对于像扫描结果这样的情况很有用，因为您有由不同层定义的子结构。
 *
 *   例如，考虑类型签名“Lt（ES）t（6C）”。在这种假设情况下，第一个结构由MAC层定义，第二个结构由PHY层定义。由于使用了结构，我们确切地知道该层的组成部分。此外，我们可以在不引入向后兼容性问题的情况下向每个结构添加字段：编码为“Lt（ESU）t（6C）”（注意额外的“U”）的数据将很好地解码为“Lt（ES）t（6C）”。此外，如果我们不关心MAC层而只关心网络层，我们可以解析为“L（）t（6C）”。
 *
 *   注意，编码为“Lt（ES）t（6C）”的数据也将解析为“Ldd”，两层的结构现在都是不透明的数据块。
 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 *   阵列
 *
 *   数组只是一组连接的_n_数据编码。例如，类型“A（6）”只是一个IPv6地址列表，一个接一个。类型“A（6E）”同样是IPv6地址/EUI-64对的级联。
 *
 *   如果数组包含多个字段，则这些字段通常会被一个结构（“t（…）”）包围。这样可以有效地在数组中的每个项前面加上其长度。这对于提高解析性能或允许将来以向后兼容的方式添加其他字段非常有用。如果绝对不会添加额外的字段，则可以省略该结构（每项节省两个字节）。
 *
 *   此规范未定义将数组作为字段嵌入其他字段的方式。
 *
 * ---------------------------------------------------------------------------
 *
 *   脊柱定义兼容性指南：
 *
 *   在尖晶石中，NCP与RCP和主机侧的兼容性策略处理不同。
 *
 *   新的NCP固件应与旧的主机驱动程序一起工作，即NCP实施应保持向后兼容。
 *
 *    -已实现的尖晶石属性或命令格式的现有字段无法更改。
 *
 *    -只要NCP实现将新字段视为可选字段（即，驱动程序不知道并因此不使用新字段，则应继续运行），新字段可以附加在格式末尾（或结构末尾）。
 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 *   对于RCP和主机，“RCP API版本”编号用于检查主机实现和RCP固件之间的兼容性。通常，较新的主机端实现可以与一系列先前或较旧的RCP固件版本一起使用。
 *
 *   -SPINEL_RCP_API_VERSION指定当前尖晶石RCP API版本。任何RCP特定尖晶石定义发生变化时，该数字必须递增。
 *
 *   -SPINEL_MIN_HOST_SUPPORTED_RCP_API_VERSION指定主机端实现支持的最低尖晶石RCP API版本。
 *
 *   -启动时，主机实现查询RCP API版本，并接受从SPINEL_MIN_host_SUPPORTED_RCP_API_version到SPINEL_RCP_API_version的任何版本号。
 *
 * ---------------------------------------------------------------------------
 */

#ifdef SPINEL_PLATFORM_HEADER
#include SPINEL_PLATFORM_HEADER
#else // 如果定义SPINEL_PLATFORM_HEADER
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#endif // 否则SPINEL_PLATFORM_HEADER

// ----------------------------------------------------------------------------

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#if defined(__GNUC__)
#define SPINEL_API_EXTERN extern __attribute__((visibility("default")))
#define SPINEL_API_NONNULL_ALL __attribute__((nonnull))
#define SPINEL_API_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#endif // 如果定义__GNUC__

#endif // 如果是DOXYGEN_SOULD_SKIP_THIS

#ifndef SPINEL_API_EXTERN
#define SPINEL_API_EXTERN extern
#endif

#ifndef SPINEL_API_NONNULL_ALL
#define SPINEL_API_NONNULL_ALL
#endif

#ifndef SPINEL_API_WARN_UNUSED_RESULT
#define SPINEL_API_WARN_UNUSED_RESULT
#endif

// ----------------------------------------------------------------------------

#define SPINEL_PROTOCOL_VERSION_THREAD_MAJOR 4
#define SPINEL_PROTOCOL_VERSION_THREAD_MINOR 3

/**
 * @def SPINEL_RCP_API_VERSION
 *
 * RCP API版本号。
 *
 * 每次RCP使用的任何尖晶石定义发生变化时，该数字必须增加一（与变化是否向后兼容无关）。
 *
 * 有关详细信息，请参阅“Spinel定义兼容性指南”一节。
 *
 */
#define SPINEL_RCP_API_VERSION 4

/**
 * @def SPINEL_MIN_HOST_SUPPORTED_RCP_API_VERSION
 *
 * 主机实现支持的最低RCP API版本。
 *
 * 当主机实现上有不兼容的RCP尖晶石相关更改时，此数字必须增加。
 *
 * 有关详细信息，请参阅“Spinel定义兼容性指南”一节。
 *
 */
#define SPINEL_MIN_HOST_SUPPORTED_RCP_API_VERSION 4

/**
 * @def SPINEL_FRAME_MAX_SIZE
 *
 *  SPINEL帧的最大大小。
 *
 */
#define SPINEL_FRAME_MAX_SIZE 1300

/**
 * @def SPINEL_FRAME_MAX_COMMAND_HEADER_SIZE
 *
 *  SPINEL命令头的最大大小。
 *
 */
#define SPINEL_FRAME_MAX_COMMAND_HEADER_SIZE 4

/**
 * @def SPINEL_FRAME_MAX_PAYLOAD_SIZE
 *
 *  SPINEL命令有效负载的最大大小。
 *
 */
#define SPINEL_FRAME_MAX_COMMAND_PAYLOAD_SIZE (SPINEL_FRAME_MAX_SIZE - SPINEL_FRAME_MAX_COMMAND_HEADER_SIZE)

/**
 * @def SPINEL_ENCRYPTER_EXTRA_DATA_SIZE
 *
 *  spinel Encrypter需要为尖晶石帧缓冲区分配的额外数据的大小。
 *
 */
#define SPINEL_ENCRYPTER_EXTRA_DATA_SIZE 0

/**
 * @def SPINEL_FRAME_BUFFER_SIZE
 *
 *  缓冲区的大小足以容纳一个完整的尖晶石框架，其中包含spinel加密器所需的额外数据。
 *
 */
#define SPINEL_FRAME_BUFFER_SIZE (SPINEL_FRAME_MAX_SIZE + SPINEL_ENCRYPTER_EXTRA_DATA_SIZE)

///使用规范中的位索引生成位掩码的宏
#define SPINEL_BIT_MASK(bit_index, field_bit_count) ((1 << ((field_bit_count)-1)) >> (bit_index))

// ----------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C" {
#endif

enum
{
    SPINEL_STATUS_OK                       = 0,  ///<操作已成功完成。
    SPINEL_STATUS_FAILURE                  = 1,  ///<由于某些未定义的原因，操作失败。
    SPINEL_STATUS_UNIMPLEMENTED            = 2,  ///<尚未执行给定操作。
    SPINEL_STATUS_INVALID_ARGUMENT         = 3,  ///<操作的参数无效。
    SPINEL_STATUS_INVALID_STATE            = 4,  ///<此操作对于当前设备状态无效。
    SPINEL_STATUS_INVALID_COMMAND          = 5,  ///<无法识别此命令。
    SPINEL_STATUS_INVALID_INTERFACE        = 6,  ///<不支持此接口。
    SPINEL_STATUS_INTERNAL_ERROR           = 7,  ///<发生内部运行时错误。
    SPINEL_STATUS_SECURITY_ERROR           = 8,  ///<发生了安全/身份验证错误。
    SPINEL_STATUS_PARSE_ERROR              = 9,  ///<分析命令时出错。
    SPINEL_STATUS_IN_PROGRESS              = 10, ///<此操作正在进行。
    SPINEL_STATUS_NOMEM                    = 11, ///<由于内存压力，操作被阻止。
    SPINEL_STATUS_BUSY                     = 12, ///<设备当前正在执行互斥操作
    SPINEL_STATUS_PROP_NOT_FOUND           = 13, ///<无法识别给定属性。
    SPINEL_STATUS_DROPPED                  = 14, ///<A/数据包已丢弃。
    SPINEL_STATUS_EMPTY                    = 15, ///<操作结果为空。
    SPINEL_STATUS_CMD_TOO_BIG              = 16, ///<命令太大，无法放入内部缓冲区。
    SPINEL_STATUS_NO_ACK                   = 17, ///<数据包未被确认。
    SPINEL_STATUS_CCA_FAILURE              = 18, ///<由于CCA故障，数据包未发送。
    SPINEL_STATUS_ALREADY                  = 19, ///<操作已在进行中。
    SPINEL_STATUS_ITEM_NOT_FOUND           = 20, ///<找不到给定项。
    SPINEL_STATUS_INVALID_COMMAND_FOR_PROP = 21, ///<无法对此属性执行给定的命令。
    SPINEL_STATUS_UNKNOWN_NEIGHBOR         = 22, ///<邻居未知。
    SPINEL_STATUS_NOT_CAPABLE              = 23, ///<目标无法处理请求的操作。
    SPINEL_STATUS_RESPONSE_TIMEOUT         = 24, ///<未收到来自远程节点的响应

    SPINEL_STATUS_JOIN__BEGIN = 104,

    ///与其他对等方关联的一般性失败。
    /**
     *  如果有足够的信息可用于确定稍后的连接失败状态代码之一更准确，则实现者不应使用此状态错误。
     *
     *  \sa SPINEL_PROP_NET_REQUIRE_JOIN_EXISTING\sa SPINEL_PROCP_MESHCOP_JOINER_COMMISIONING
     */
    SPINEL_STATUS_JOIN_FAILURE = SPINEL_STATUS_JOIN__BEGIN + 0,

    ///节点找到其他对等节点，但无法解码其数据包。
    /**
     *  通常，此错误代码表示网络密钥设置不正确。
     *
     *  \sa SPINEL_PROP_NET_REQUIRE_JOIN_EXISTING\sa SPINEL_PROCP_MESHCOP_JOINER_COMMISIONING
     */
    SPINEL_STATUS_JOIN_SECURITY = SPINEL_STATUS_JOIN__BEGIN + 1,

    ///节点在网络上找不到任何其他对等节点。
    /**
     *  \sa SPINEL_PROP_NET_REQUIRE_JOIN_EXISTING\sa SPINEL_PROCP_MESHCOP_JOINER_COMMISIONING
     */
    SPINEL_STATUS_JOIN_NO_PEERS = SPINEL_STATUS_JOIN__BEGIN + 2,

    ///找到的唯一潜在对等节点不兼容。
    /**
     *  \sa SPINEL_PROP_NET_REQUIRE_JOIN_EXISTING
     */
    SPINEL_STATUS_JOIN_INCOMPATIBLE = SPINEL_STATUS_JOIN__BEGIN + 3,

    ///在预期时间内没有响应。
    /**
     *  \sa SPINEL_PROP_MESHCOP_JOINER_COMMISIONING公司
     */
    SPINEL_STATUS_JOIN_RSP_TIMEOUT = SPINEL_STATUS_JOIN__BEGIN + 4,

    ///节点成功调试并获得网络凭据。
    /**
     *  \sa SPINEL_PROP_MESHCOP_JOINER_COMMISIONING公司
     */
    SPINEL_STATUS_JOIN_SUCCESS = SPINEL_STATUS_JOIN__BEGIN + 5,

    SPINEL_STATUS_JOIN__END = 112,

    SPINEL_STATUS_RESET__BEGIN   = 112,
    SPINEL_STATUS_RESET_POWER_ON = SPINEL_STATUS_RESET__BEGIN + 0,
    SPINEL_STATUS_RESET_EXTERNAL = SPINEL_STATUS_RESET__BEGIN + 1,
    SPINEL_STATUS_RESET_SOFTWARE = SPINEL_STATUS_RESET__BEGIN + 2,
    SPINEL_STATUS_RESET_FAULT    = SPINEL_STATUS_RESET__BEGIN + 3,
    SPINEL_STATUS_RESET_CRASH    = SPINEL_STATUS_RESET__BEGIN + 4,
    SPINEL_STATUS_RESET_ASSERT   = SPINEL_STATUS_RESET__BEGIN + 5,
    SPINEL_STATUS_RESET_OTHER    = SPINEL_STATUS_RESET__BEGIN + 6,
    SPINEL_STATUS_RESET_UNKNOWN  = SPINEL_STATUS_RESET__BEGIN + 7,
    SPINEL_STATUS_RESET_WATCHDOG = SPINEL_STATUS_RESET__BEGIN + 8,
    SPINEL_STATUS_RESET__END     = 128,

    SPINEL_STATUS_VENDOR__BEGIN = 15360,
    SPINEL_STATUS_VENDOR__END   = 16384,

    SPINEL_STATUS_STACK_NATIVE__BEGIN = 16384,
    SPINEL_STATUS_STACK_NATIVE__END   = 81920,

    SPINEL_STATUS_EXPERIMENTAL__BEGIN = 2000000,
    SPINEL_STATUS_EXPERIMENTAL__END   = 2097152,
};

typedef uint32_t spinel_status_t;

typedef enum
{
    SPINEL_NET_ROLE_DETACHED = 0,
    SPINEL_NET_ROLE_CHILD    = 1,
    SPINEL_NET_ROLE_ROUTER   = 2,
    SPINEL_NET_ROLE_LEADER   = 3,
} spinel_net_role_t;

typedef enum
{
    SPINEL_IPV6_ICMP_PING_OFFLOAD_DISABLED       = 0,
    SPINEL_IPV6_ICMP_PING_OFFLOAD_UNICAST_ONLY   = 1,
    SPINEL_IPV6_ICMP_PING_OFFLOAD_MULTICAST_ONLY = 2,
    SPINEL_IPV6_ICMP_PING_OFFLOAD_ALL            = 3,
} spinel_ipv6_icmp_ping_offload_mode_t;

typedef enum
{
    SPINEL_SCAN_STATE_IDLE     = 0,
    SPINEL_SCAN_STATE_BEACON   = 1,
    SPINEL_SCAN_STATE_ENERGY   = 2,
    SPINEL_SCAN_STATE_DISCOVER = 3,
} spinel_scan_state_t;

typedef enum
{
    SPINEL_MCU_POWER_STATE_ON        = 0,
    SPINEL_MCU_POWER_STATE_LOW_POWER = 1,
    SPINEL_MCU_POWER_STATE_OFF       = 2,
} spinel_mcu_power_state_t;

// “spinel_power_state_t”枚举和“power_state”`
// 属性已弃用。请使用`MCU_POWER_STATE`
// 相反
typedef enum
{
    SPINEL_POWER_STATE_OFFLINE    = 0,
    SPINEL_POWER_STATE_DEEP_SLEEP = 1,
    SPINEL_POWER_STATE_STANDBY    = 2,
    SPINEL_POWER_STATE_LOW_POWER  = 3,
    SPINEL_POWER_STATE_ONLINE     = 4,
} spinel_power_state_t;

typedef enum
{
    SPINEL_HOST_POWER_STATE_OFFLINE    = 0,
    SPINEL_HOST_POWER_STATE_DEEP_SLEEP = 1,
    SPINEL_HOST_POWER_STATE_RESERVED   = 2,
    SPINEL_HOST_POWER_STATE_LOW_POWER  = 3,
    SPINEL_HOST_POWER_STATE_ONLINE     = 4,
} spinel_host_power_state_t;

typedef enum
{
    SPINEL_MESHCOP_JOINER_STATE_IDLE       = 0,
    SPINEL_MESHCOP_JOINER_STATE_DISCOVER   = 1,
    SPINEL_MESHCOP_JOINER_STATE_CONNECTING = 2,
    SPINEL_MESHCOP_JOINER_STATE_CONNECTED  = 3,
    SPINEL_MESHCOP_JOINER_STATE_ENTRUST    = 4,
    SPINEL_MESHCOP_JOINER_STATE_JOINED     = 5,
} spinel_meshcop_joiner_state_t;

enum
{
    SPINEL_NET_FLAG_ON_MESH       = (1 << 0),
    SPINEL_NET_FLAG_DEFAULT_ROUTE = (1 << 1),
    SPINEL_NET_FLAG_CONFIGURE     = (1 << 2),
    SPINEL_NET_FLAG_DHCP          = (1 << 3),
    SPINEL_NET_FLAG_SLAAC         = (1 << 4),
    SPINEL_NET_FLAG_PREFERRED     = (1 << 5),

    SPINEL_NET_FLAG_PREFERENCE_OFFSET = 6,
    SPINEL_NET_FLAG_PREFERENCE_MASK   = (3 << SPINEL_NET_FLAG_PREFERENCE_OFFSET),
};

enum
{
    SPINEL_NET_FLAG_EXT_DP  = (1 << 6),
    SPINEL_NET_FLAG_EXT_DNS = (1 << 7),
};

enum
{
    SPINEL_ROUTE_PREFERENCE_HIGH   = (1 << SPINEL_NET_FLAG_PREFERENCE_OFFSET),
    SPINEL_ROUTE_PREFERENCE_MEDIUM = (0 << SPINEL_NET_FLAG_PREFERENCE_OFFSET),
    SPINEL_ROUTE_PREFERENCE_LOW    = (3 << SPINEL_NET_FLAG_PREFERENCE_OFFSET),
};

enum
{
    SPINEL_ROUTE_FLAG_NAT64 = (1 << 5),
};

enum
{
    SPINEL_THREAD_MODE_FULL_NETWORK_DATA   = (1 << 0),
    SPINEL_THREAD_MODE_FULL_THREAD_DEV     = (1 << 1),
    SPINEL_THREAD_MODE_SECURE_DATA_REQUEST = (1 << 2),
    SPINEL_THREAD_MODE_RX_ON_WHEN_IDLE     = (1 << 3),
};

enum
{
    SPINEL_GPIO_FLAG_DIR_INPUT       = 0,
    SPINEL_GPIO_FLAG_DIR_OUTPUT      = SPINEL_BIT_MASK(0, 8),
    SPINEL_GPIO_FLAG_PULL_UP         = SPINEL_BIT_MASK(1, 8),
    SPINEL_GPIO_FLAG_PULL_DOWN       = SPINEL_BIT_MASK(2, 8),
    SPINEL_GPIO_FLAG_OPEN_DRAIN      = SPINEL_BIT_MASK(2, 8),
    SPINEL_GPIO_FLAG_TRIGGER_NONE    = 0,
    SPINEL_GPIO_FLAG_TRIGGER_RISING  = SPINEL_BIT_MASK(3, 8),
    SPINEL_GPIO_FLAG_TRIGGER_FALLING = SPINEL_BIT_MASK(4, 8),
    SPINEL_GPIO_FLAG_TRIGGER_ANY     = SPINEL_GPIO_FLAG_TRIGGER_RISING | SPINEL_GPIO_FLAG_TRIGGER_FALLING,
};

enum
{
    SPINEL_PROTOCOL_TYPE_BOOTLOADER = 0,
    SPINEL_PROTOCOL_TYPE_ZIGBEE_IP  = 2,
    SPINEL_PROTOCOL_TYPE_THREAD     = 3,
};

enum
{
    SPINEL_MAC_PROMISCUOUS_MODE_OFF     = 0, ///<正常MAC过滤已到位。
    SPINEL_MAC_PROMISCUOUS_MODE_NETWORK = 1, ///<所有匹配网络的MAC数据包都会向堆栈传递。
    SPINEL_MAC_PROMISCUOUS_MODE_FULL    = 2, ///<所有解码的MAC数据包都向堆栈传递。
};

enum
{
    SPINEL_NCP_LOG_LEVEL_EMERG  = 0,
    SPINEL_NCP_LOG_LEVEL_ALERT  = 1,
    SPINEL_NCP_LOG_LEVEL_CRIT   = 2,
    SPINEL_NCP_LOG_LEVEL_ERR    = 3,
    SPINEL_NCP_LOG_LEVEL_WARN   = 4,
    SPINEL_NCP_LOG_LEVEL_NOTICE = 5,
    SPINEL_NCP_LOG_LEVEL_INFO   = 6,
    SPINEL_NCP_LOG_LEVEL_DEBUG  = 7,
};

enum
{
    SPINEL_NCP_LOG_REGION_NONE        = 0,
    SPINEL_NCP_LOG_REGION_OT_API      = 1,
    SPINEL_NCP_LOG_REGION_OT_MLE      = 2,
    SPINEL_NCP_LOG_REGION_OT_ARP      = 3,
    SPINEL_NCP_LOG_REGION_OT_NET_DATA = 4,
    SPINEL_NCP_LOG_REGION_OT_ICMP     = 5,
    SPINEL_NCP_LOG_REGION_OT_IP6      = 6,
    SPINEL_NCP_LOG_REGION_OT_TCP      = 7,
    SPINEL_NCP_LOG_REGION_OT_MAC      = 8,
    SPINEL_NCP_LOG_REGION_OT_MEM      = 9,
    SPINEL_NCP_LOG_REGION_OT_NCP      = 10,
    SPINEL_NCP_LOG_REGION_OT_MESH_COP = 11,
    SPINEL_NCP_LOG_REGION_OT_NET_DIAG = 12,
    SPINEL_NCP_LOG_REGION_OT_PLATFORM = 13,
    SPINEL_NCP_LOG_REGION_OT_COAP     = 14,
    SPINEL_NCP_LOG_REGION_OT_CLI      = 15,
    SPINEL_NCP_LOG_REGION_OT_CORE     = 16,
    SPINEL_NCP_LOG_REGION_OT_UTIL     = 17,
    SPINEL_NCP_LOG_REGION_OT_BBR      = 18,
    SPINEL_NCP_LOG_REGION_OT_MLR      = 19,
    SPINEL_NCP_LOG_REGION_OT_DUA      = 10,
    SPINEL_NCP_LOG_REGION_OT_BR       = 21,
    SPINEL_NCP_LOG_REGION_OT_SRP      = 22,
    SPINEL_NCP_LOG_REGION_OT_DNS      = 23,
};

enum
{
    SPINEL_MESHCOP_COMMISSIONER_STATE_DISABLED = 0,
    SPINEL_MESHCOP_COMMISSIONER_STATE_PETITION = 1,
    SPINEL_MESHCOP_COMMISSIONER_STATE_ACTIVE   = 2,
};

enum
{
    SPINEL_ADDRESS_CACHE_ENTRY_STATE_CACHED      = 0, // 条目已缓存并正在使用。
    SPINEL_ADDRESS_CACHE_ENTRY_STATE_SNOOPED     = 1, // 条目是通过窥探优化创建的。
    SPINEL_ADDRESS_CACHE_ENTRY_STATE_QUERY       = 2, // 条目表示EID的持续查询。
    SPINEL_ADDRESS_CACHE_ENTRY_STATE_RETRY_QUERY = 3, // 条目处于重试模式（以前的查询没有响应）。
};

enum
{
    SPINEL_RADIO_LINK_IEEE_802_15_4 = 0,
    SPINEL_RADIO_LINK_TREL_UDP6     = 1,
};

// 由于以下原因可以接收的状态：
// @参考SPINEL_PROP_THREAD_LINK_METRICS_QUERY
// @参考SPINEL_PROP_THREAD_LINK_METRICS_GMT_ENH_ACK
// @参考SPINEL_PROP_THREAD_LINK_METRICS_MGM_FORWARD
enum
{
    SPINEL_LINK_METRICS_STATUS_SUCCESS                     = 0,
    SPINEL_LINK_METRICS_STATUS_CANNOT_SUPPORT_NEW_SERIES   = 1,
    SPINEL_LINK_METRICS_STATUS_SERIESID_ALREADY_REGISTERED = 2,
    SPINEL_LINK_METRICS_STATUS_SERIESID_NOT_RECOGNIZED     = 3,
    SPINEL_LINK_METRICS_STATUS_NO_MATCHING_FRAMES_RECEIVED = 4,
    SPINEL_LINK_METRICS_STATUS_OTHER_ERROR                 = 254
};

// 度量ID用于：
// @参考SPINEL_PROP_THREAD_LINK_METRICS_QUERY
// @参考SPINEL_PROP_THREAD_LINK_METRICS_QUERY_RESULT
// @参考SPINEL_PROP_THREAD_LINK_METRICS_GMT_ENH_ACK
// @参考SPINEL_PROP_THREAD_LINK_METRICS_MGM_FORWARD
enum
{
    SPINEL_THREAD_LINK_METRIC_PDU_COUNT   = (1 << 0),
    SPINEL_THREAD_LINK_METRIC_LQI         = (1 << 1),
    SPINEL_THREAD_LINK_METRIC_LINK_MARGIN = (1 << 2),
    SPINEL_THREAD_LINK_METRIC_RSSI        = (1 << 3),
};

// 框架类型用于：
// @参考SPINEL_PROP_THREAD_LINK_METRICS_MGM_FORWARD
enum
{
    SPINEL_THREAD_FRAME_TYPE_MLE_LINK_PROBE   = (1 << 0),
    SPINEL_THREAD_FRAME_TYPE_MAC_DATA         = (1 << 1),
    SPINEL_THREAD_FRAME_TYPE_MAC_DATA_REQUEST = (1 << 2),
    SPINEL_THREAD_FRAME_TYPE_MAC_ACK          = (1 << 3),
};

// 参数ID用于：
// @参考SPINEL_PROP_THREAD_MLR_REQUEST
enum
{
    SPINEL_THREAD_MLR_PARAMID_TIMEOUT = 0
};

// 骨干路由器状态用于：
// @参考SPINEL_PROP_THREAD_BACKBONE_ROUTER_LOCAL_STATE
enum
{
    SPINEL_THREAD_BACKBONE_ROUTER_STATE_DISABLED  = 0,
    SPINEL_THREAD_BACKBONE_ROUTER_STATE_SECONDARY = 1,
    SPINEL_THREAD_BACKBONE_ROUTER_STATE_PRIMARY   = 2,
};

typedef enum
{
    SPINEL_SRP_CLIENT_ITEM_STATE_TO_ADD     = 0, // 要添加/注册的项目。
    SPINEL_SRP_CLIENT_ITEM_STATE_ADDING     = 1, // 正在添加/注册项目。
    SPINEL_SRP_CLIENT_ITEM_STATE_TO_REFRESH = 2, // 要刷新的项目（重新注册以续订租约）。
    SPINEL_SRP_CLIENT_ITEM_STATE_REFRESHING = 3, // 正在刷新项目。
    SPINEL_SRP_CLIENT_ITEM_STATE_TO_REMOVE  = 4, // 要删除的项目。
    SPINEL_SRP_CLIENT_ITEM_STATE_REMOVING   = 5, // 正在删除项目。
    SPINEL_SRP_CLIENT_ITEM_STATE_REGISTERED = 6, // 项目已向服务器注册。
    SPINEL_SRP_CLIENT_ITEM_STATE_REMOVED    = 7, // 项目已删除。
} spinel_srp_client_item_state_t;

typedef enum
{
    SPINEL_SRP_CLIENT_ERROR_NONE             = 0, // 没有错误。
    SPINEL_SRP_CLIENT_ERROR_PARSE            = 1, // 由于格式错误，服务器无法解释。
    SPINEL_SRP_CLIENT_ERROR_FAILED           = 2, // 服务器遇到内部故障。
    SPINEL_SRP_CLIENT_ERROR_NOT_FOUND        = 3, // 应该存在的名称不存在。
    SPINEL_SRP_CLIENT_ERROR_NOT_IMPLEMENTED  = 4, // 服务器不支持查询类型。
    SPINEL_SRP_CLIENT_ERROR_SECURITY         = 5, // 服务对区域无效。
    SPINEL_SRP_CLIENT_ERROR_DUPLICATED       = 6, // 一些不应该存在的名字，确实存在。
    SPINEL_SRP_CLIENT_ERROR_RESPONSE_TIMEOUT = 7, // 等待服务器响应时超时（客户端将重试）。
    SPINEL_SRP_CLIENT_ERROR_INVALID_ARGS     = 8, // 无效的参数（例如，错误的服务名称或TXT-DATA）。
    SPINEL_SRP_CLIENT_ERROR_NO_BUFS          = 9, // 没有缓冲区发送SRP更新消息。
} spinel_srp_client_error_t;

typedef struct
{
    uint8_t bytes[8];
} spinel_eui64_t;

typedef struct
{
    uint8_t bytes[8];
} spinel_net_xpanid_t;

typedef struct
{
    uint8_t bytes[16];
} spinel_net_pskc_t;

typedef struct
{
    uint8_t bytes[6];
} spinel_eui48_t;

typedef struct
{
    uint8_t bytes[16];
} spinel_ipv6addr_t;

typedef int          spinel_ssize_t;
typedef unsigned int spinel_size_t;
typedef uint8_t      spinel_tid_t;

enum
{
    SPINEL_MD_FLAG_TX        = 0x0001, //!< 数据包已发送，但未收到。
    SPINEL_MD_FLAG_BAD_FCS   = 0x0004, //!< 接收到带有坏FCS的数据包
    SPINEL_MD_FLAG_DUPE      = 0x0008, //!< 数据包似乎是重复的
    SPINEL_MD_FLAG_ACKED_FP  = 0x0010, //!< 数据包已确认，帧挂起设置
    SPINEL_MD_FLAG_ACKED_SEC = 0x0020, //!< 数据包已通过安全增强ACK确认
    SPINEL_MD_FLAG_RESERVED  = 0xFFC2, //!< 保留用于将来使用的标志。
};

enum
{
    SPINEL_RESET_PLATFORM = 1,
    SPINEL_RESET_STACK    = 2,
};

enum
{
    /**
     * 无操作命令（主机->NCP）
     *
     * 编码：空
     *
     * 促使NCP将成功状态发送回主机。这主要用于活力检查。此命令的命令有效载荷应为空。
     *
     * 此命令没有错误条件。
     *
     */
    SPINEL_CMD_NOOP = 0,

    /**
     * 重置NCP命令（主机->NCP）
     *
     * 编码：空或`C`
     *
     * 使NCP执行软件重置。由于此命令的性质，TID被忽略。主机应等待NCP发出的“CMD_PROP_VALUE_IS”命令，指示“PROP_LAST_STATUS”已设置为“STATUS_RESET_SOFTWARE”。
     *
     * 可选命令有效负载指定重置类型，可以是“SPINEL_reset_PLATFORM”或“SPINER_reset_ACK”。如果未指定，则默认为堆栈重置。
     *
     * 如果发生错误，将发出“PROP_LAST_STATUS”值，并将该值设置为生成的错误状态代码。
     *
     */
    SPINEL_CMD_RESET = 1,

    /**
     * 获取属性值命令（主机->NCP）
     *
     * 编码：`i``i`：属性Id
     *
     * 使NCP为给定的属性标识符发出“CMD_PROP_VALUE_IS”命令。
     *
     * 此命令的有效负载是以压缩无符号整数格式“i”编码的属性标识符。
     *
     * 如果发生错误，将发出“PROP_LAST_STATUS”值，并将该值设置为生成的错误状态代码。
     *
     */
    SPINEL_CMD_PROP_VALUE_GET = 2,

    /**
     * 设置属性值命令（主机->NCP）
     *
     * 编码：`iD``i`：属性iD`D`：值（编码取决于属性）
     *
     * 指示NCP将给定属性设置为特定的给定值，替换之前的任何值。
     *
     * 此命令的有效负载是以压缩无符号整数格式编码的属性标识符，后跟属性值。属性值的确切格式由属性定义。
     *
     * 成功后，将为具有设置值的给定属性标识符或具有值“LAST_STATUS_OK”的“PROP_LAST_STATATUS”发出“CMD_PROP_VALUE_IS”命令。
     *
     * 如果发生错误，将发出“PROP_LAST_STATUS”值，并将该值设置为生成的错误状态代码。
     *
     */
    SPINEL_CMD_PROP_VALUE_SET = 3,

    /**
     * 将值插入属性命令（主机->NCP）
     *
     * 编码：`iD``i`：属性iD`D`：值（编码取决于属性）
     *
     * 指示NCP将给定值插入面向列表的属性，而不删除列表中的其他项。列表中项目的结果顺序由正在操作的单个属性定义。
     *
     * 此命令的有效负载是以压缩无符号整数格式编码的属性标识符，后跟要插入的值。值的确切格式由属性定义。
     *
     * 如果属性的类型签名由数组“a（t（…））”包围的单个结构组成，则值的内容必须包含结构的内容（“…”），而不是整个项的序列化（“t（…”）。具体而言，结构的长度不得预先加值。这有助于消除冗余数据。
     *
     * 成功后，为给定属性发出“CMD_PROP_VALUE_INSERTED”命令，或为值为“LAST_STATUS_OK”的属性“PROP_LAST_STATATUS”发出“CMDPROP_VALUE_is”命令。
     *
     * 如果发生错误，将发出“PROP_LAST_STATUS”值，并将该值设置为生成的错误状态代码。
     *
     */
    SPINEL_CMD_PROP_VALUE_INSERT = 4,

    /**
     * 从属性命令中删除值（主机->NCP）
     *
     * 编码：`iD``i`：属性iD`D`：值（编码取决于属性）

     * 指示NCP从面向列表的属性中删除给定值，而不影响列表中的其他项。列表中项目的结果顺序由正在操作的单个属性定义。
     *
     * 请注意，此命令按值操作，而不是按索引操作！
     *
     * 此命令的有效负载是以压缩无符号整数格式编码的属性标识符，后跟要删除的值。值的确切格式由属性定义。
     *
     * 如果属性的类型签名由数组“a（t（…））”包围的单个结构组成，则值的内容必须包含结构的内容（“…”），而不是整个项的序列化（“t（…”）。特别是，结构的长度不得加在“VALUE”前面。这有助于消除冗余数据。
     *
     * 成功后，为给定属性发出“CMD_PROP_VALUE_REMOVED”命令，或为值为“LAST_STATUS_OK”的属性“PROP_LAST_STATATUS”发出“CMDPROP_VALUE_is”命令。
     *
     * 如果发生错误，将发出“PROP_LAST_STATUS”值，并将该值设置为生成的错误状态代码。
     *
     */
    SPINEL_CMD_PROP_VALUE_REMOVE = 5,

    /**
     * 属性值通知命令（NCP->Host）
     *
     * 编码：`iD``i`：属性iD`D`：值（编码取决于属性）
     *
     * 该命令可以由NCP响应来自主机的先前命令而发送，也可以由NCC以非请求方式发送，以异步通知主机各种状态变化。
     *
     * 此命令的有效负载是以压缩无符号整数格式编码的属性标识符，后跟给定属性的当前值。
     *
     */
    SPINEL_CMD_PROP_VALUE_IS = 6,

    /**
     * 属性值插入通知命令（NCP->Host）
     *
     * 编码：`iD``i`：属性iD`D`：值（编码取决于属性）
     *
     * 该命令可由NCP响应“CMD_PROP_VALUE_INSERT”命令发送，或由NCP以非请求方式发送，以异步通知主机各种状态变化。
     *
     * 此命令的有效负载是以压缩无符号整数格式编码的属性标识符，后跟插入到给定属性中的值。
     *
     * 如果由属性id指定的属性的类型签名由一个数组（`a（t（…））`）包围的单个结构组成，则值的内容必须包含结构的内容（`…`），而不是整个项的序列化（`t（……）`）。特别是，结构的长度不得加在“VALUE”前面。这有助于消除冗余数据。
     *
     * 列表中项目的结果顺序由给定属性定义。
     *
     */
    SPINEL_CMD_PROP_VALUE_INSERTED = 7,

    /**
     * 属性值删除通知命令（NCP->Host）
     *
     * 编码：`iD``i`：属性iD`D`：值（编码取决于属性）
     *
     * 该命令可由NCP响应“CMD_PROP_VALUE_REMOVE”命令发送，或由NCP以非请求方式发送，以异步通知主机各种状态变化。
     *
     * 请注意，此命令按值操作，而不是按索引操作！
     *
     * 此命令的有效负载是以中描述的压缩无符号整数格式编码的属性标识符，后跟从给定属性中删除的值。
     *
     * 如果由属性id指定的属性的类型签名由一个数组（`a（t（…））`）包围的单个结构组成，则值的内容必须包含结构的内容（`…`），而不是整个项的序列化（`t（……）`）。特别是，结构的长度不得加在“VALUE”前面。这有助于消除冗余数据。
     *
     * 列表中项目的结果顺序由给定属性定义。
     *
     */
    SPINEL_CMD_PROP_VALUE_REMOVED = 8,

    SPINEL_CMD_NET_SAVE = 9, // 已弃用

    /**
     * 清除保存的网络设置命令（主机->NCP）
     *
     * 编码：空
     *
     * 从非易失性内存中擦除所有网络凭据和状态。
     *
     * 此操作仅影响非易失性存储器。存储在易失性存储器中的当前网络信息不受影响。
     *
     * 此命令的响应始终是“PROP_LAST_STATUS”的“CMD_PROP_VALUE_is”，指示操作结果。
     *
     */
    SPINEL_CMD_NET_CLEAR = 10,

    SPINEL_CMD_NET_RECALL = 11, // 已弃用

    /**
     * 主机缓冲区卸载是一种可选的NCP功能，当存在时，它允许NCP将数据缓冲区存储在主机处理器上，稍后可以调用。
     *
     * 主机可以通过检查“PROP_CAPS”中是否存在“CAP_HBO”功能来检测此功能的存在。
     *
     * OpenThread当前不支持此功能。
     *
     */

    SPINEL_CMD_HBO_OFFLOAD   = 12,
    SPINEL_CMD_HBO_RECLAIM   = 13,
    SPINEL_CMD_HBO_DROP      = 14,
    SPINEL_CMD_HBO_OFFLOADED = 15,
    SPINEL_CMD_HBO_RECLAIMED = 16,
    SPINEL_CMD_HBO_DROPPED   = 17,

    /**
     * Peek命令（主机->NCP）
     *
     * 编码：`LU``L`：要查看的地址`U`：要读取的字节数
     *
     * 该命令允许NCP从NCP的RAM中获取值，用于调试。成功后，“CMD_PEEK_RET”从NCP发送到主机。失败后，将发出“PROP_LAST_STATUS”并显示相应的错误指示。
     *
     * NCP可能会阻止某些内存区域被访问。
     *
     * 此命令要求具有“CAP_PEEK_POKE”功能。
     *
     */
    SPINEL_CMD_PEEK = 18,

    /**
     * Peek返回命令（NCP->主机）
     *
     * 编码：`LUD``L`：偷看的地址`U`：读取的字节数`D`：内存内容
     *
     * 此命令包含先前调用“CMD_PEEK”所请求的内存内容。
     *
     * 此命令要求具有“CAP_PEEK_POKE”功能。
     *
     */
    SPINEL_CMD_PEEK_RET = 19,

    /**
     * Poke命令（主机->NCP）
     *
     * 编码：`LUD``L`：要插入的地址`U`：要写入的字节数`D`：要写的内容
     *
     * 此命令将字节写入指定的内存地址以进行调试。
     *
     * 此命令要求具有“CAP_PEEK_POKE”功能。
     *
     */
    SPINEL_CMD_POKE = 20,

    SPINEL_CMD_PROP_VALUE_MULTI_GET = 21,
    SPINEL_CMD_PROP_VALUE_MULTI_SET = 22,
    SPINEL_CMD_PROP_VALUES_ARE      = 23,

    SPINEL_CMD_NEST__BEGIN = 15296,
    SPINEL_CMD_NEST__END   = 15360,

    SPINEL_CMD_VENDOR__BEGIN = 15360,
    SPINEL_CMD_VENDOR__END   = 16384,

    SPINEL_CMD_EXPERIMENTAL__BEGIN = 2000000,
    SPINEL_CMD_EXPERIMENTAL__END   = 2097152,
};

typedef uint32_t spinel_command_t;

enum
{
    SPINEL_CAP_LOCK       = 1,
    SPINEL_CAP_NET_SAVE   = 2,
    SPINEL_CAP_HBO        = 3,
    SPINEL_CAP_POWER_SAVE = 4,

    SPINEL_CAP_COUNTERS   = 5,
    SPINEL_CAP_JAM_DETECT = 6,

    SPINEL_CAP_PEEK_POKE = 7,

    SPINEL_CAP_WRITABLE_RAW_STREAM = 8,
    SPINEL_CAP_GPIO                = 9,
    SPINEL_CAP_TRNG                = 10,
    SPINEL_CAP_CMD_MULTI           = 11,
    SPINEL_CAP_UNSOL_UPDATE_FILTER = 12,
    SPINEL_CAP_MCU_POWER_STATE     = 13,
    SPINEL_CAP_PCAP                = 14,

    SPINEL_CAP_802_15_4__BEGIN        = 16,
    SPINEL_CAP_802_15_4_2003          = (SPINEL_CAP_802_15_4__BEGIN + 0),
    SPINEL_CAP_802_15_4_2006          = (SPINEL_CAP_802_15_4__BEGIN + 1),
    SPINEL_CAP_802_15_4_2011          = (SPINEL_CAP_802_15_4__BEGIN + 2),
    SPINEL_CAP_802_15_4_PIB           = (SPINEL_CAP_802_15_4__BEGIN + 5),
    SPINEL_CAP_802_15_4_2450MHZ_OQPSK = (SPINEL_CAP_802_15_4__BEGIN + 8),
    SPINEL_CAP_802_15_4_915MHZ_OQPSK  = (SPINEL_CAP_802_15_4__BEGIN + 9),
    SPINEL_CAP_802_15_4_868MHZ_OQPSK  = (SPINEL_CAP_802_15_4__BEGIN + 10),
    SPINEL_CAP_802_15_4_915MHZ_BPSK   = (SPINEL_CAP_802_15_4__BEGIN + 11),
    SPINEL_CAP_802_15_4_868MHZ_BPSK   = (SPINEL_CAP_802_15_4__BEGIN + 12),
    SPINEL_CAP_802_15_4_915MHZ_ASK    = (SPINEL_CAP_802_15_4__BEGIN + 13),
    SPINEL_CAP_802_15_4_868MHZ_ASK    = (SPINEL_CAP_802_15_4__BEGIN + 14),
    SPINEL_CAP_802_15_4__END          = 32,

    SPINEL_CAP_CONFIG__BEGIN = 32,
    SPINEL_CAP_CONFIG_FTD    = (SPINEL_CAP_CONFIG__BEGIN + 0),
    SPINEL_CAP_CONFIG_MTD    = (SPINEL_CAP_CONFIG__BEGIN + 1),
    SPINEL_CAP_CONFIG_RADIO  = (SPINEL_CAP_CONFIG__BEGIN + 2),
    SPINEL_CAP_CONFIG__END   = 40,

    SPINEL_CAP_ROLE__BEGIN = 48,
    SPINEL_CAP_ROLE_ROUTER = (SPINEL_CAP_ROLE__BEGIN + 0),
    SPINEL_CAP_ROLE_SLEEPY = (SPINEL_CAP_ROLE__BEGIN + 1),
    SPINEL_CAP_ROLE__END   = 52,

    SPINEL_CAP_NET__BEGIN     = 52,
    SPINEL_CAP_NET_THREAD_1_0 = (SPINEL_CAP_NET__BEGIN + 0),
    SPINEL_CAP_NET_THREAD_1_1 = (SPINEL_CAP_NET__BEGIN + 1),
    SPINEL_CAP_NET_THREAD_1_2 = (SPINEL_CAP_NET__BEGIN + 2),
    SPINEL_CAP_NET__END       = 64,

    SPINEL_CAP_RCP__BEGIN      = 64,
    SPINEL_CAP_RCP_API_VERSION = (SPINEL_CAP_RCP__BEGIN + 0),
    SPINEL_CAP_RCP__END        = 80,

    SPINEL_CAP_OPENTHREAD__BEGIN       = 512,
    SPINEL_CAP_MAC_ALLOWLIST           = (SPINEL_CAP_OPENTHREAD__BEGIN + 0),
    SPINEL_CAP_MAC_RAW                 = (SPINEL_CAP_OPENTHREAD__BEGIN + 1),
    SPINEL_CAP_OOB_STEERING_DATA       = (SPINEL_CAP_OPENTHREAD__BEGIN + 2),
    SPINEL_CAP_CHANNEL_MONITOR         = (SPINEL_CAP_OPENTHREAD__BEGIN + 3),
    SPINEL_CAP_ERROR_RATE_TRACKING     = (SPINEL_CAP_OPENTHREAD__BEGIN + 4),
    SPINEL_CAP_CHANNEL_MANAGER         = (SPINEL_CAP_OPENTHREAD__BEGIN + 5),
    SPINEL_CAP_OPENTHREAD_LOG_METADATA = (SPINEL_CAP_OPENTHREAD__BEGIN + 6),
    SPINEL_CAP_TIME_SYNC               = (SPINEL_CAP_OPENTHREAD__BEGIN + 7),
    SPINEL_CAP_CHILD_SUPERVISION       = (SPINEL_CAP_OPENTHREAD__BEGIN + 8),
    SPINEL_CAP_POSIX                   = (SPINEL_CAP_OPENTHREAD__BEGIN + 9),
    SPINEL_CAP_SLAAC                   = (SPINEL_CAP_OPENTHREAD__BEGIN + 10),
    SPINEL_CAP_RADIO_COEX              = (SPINEL_CAP_OPENTHREAD__BEGIN + 11),
    SPINEL_CAP_MAC_RETRY_HISTOGRAM     = (SPINEL_CAP_OPENTHREAD__BEGIN + 12),
    SPINEL_CAP_MULTI_RADIO             = (SPINEL_CAP_OPENTHREAD__BEGIN + 13),
    SPINEL_CAP_SRP_CLIENT              = (SPINEL_CAP_OPENTHREAD__BEGIN + 14),
    SPINEL_CAP_DUA                     = (SPINEL_CAP_OPENTHREAD__BEGIN + 15),
    SPINEL_CAP_REFERENCE_DEVICE        = (SPINEL_CAP_OPENTHREAD__BEGIN + 16),
    SPINEL_CAP_OPENTHREAD__END         = 640,

    SPINEL_CAP_THREAD__BEGIN          = 1024,
    SPINEL_CAP_THREAD_COMMISSIONER    = (SPINEL_CAP_THREAD__BEGIN + 0),
    SPINEL_CAP_THREAD_TMF_PROXY       = (SPINEL_CAP_THREAD__BEGIN + 1),
    SPINEL_CAP_THREAD_UDP_FORWARD     = (SPINEL_CAP_THREAD__BEGIN + 2),
    SPINEL_CAP_THREAD_JOINER          = (SPINEL_CAP_THREAD__BEGIN + 3),
    SPINEL_CAP_THREAD_BORDER_ROUTER   = (SPINEL_CAP_THREAD__BEGIN + 4),
    SPINEL_CAP_THREAD_SERVICE         = (SPINEL_CAP_THREAD__BEGIN + 5),
    SPINEL_CAP_THREAD_CSL_RECEIVER    = (SPINEL_CAP_THREAD__BEGIN + 6),
    SPINEL_CAP_THREAD_LINK_METRICS    = (SPINEL_CAP_THREAD__BEGIN + 7),
    SPINEL_CAP_THREAD_BACKBONE_ROUTER = (SPINEL_CAP_THREAD__BEGIN + 8),
    SPINEL_CAP_THREAD__END            = 1152,

    SPINEL_CAP_NEST__BEGIN           = 15296,
    SPINEL_CAP_NEST_LEGACY_INTERFACE = (SPINEL_CAP_NEST__BEGIN + 0),
    SPINEL_CAP_NEST_LEGACY_NET_WAKE  = (SPINEL_CAP_NEST__BEGIN + 1),
    SPINEL_CAP_NEST_TRANSMIT_HOOK    = (SPINEL_CAP_NEST__BEGIN + 2),
    SPINEL_CAP_NEST__END             = 15360,

    SPINEL_CAP_VENDOR__BEGIN = 15360,
    SPINEL_CAP_VENDOR__END   = 16384,

    SPINEL_CAP_EXPERIMENTAL__BEGIN = 2000000,
    SPINEL_CAP_EXPERIMENTAL__END   = 2097152,
};

typedef uint32_t spinel_capability_t;

/**
 * 属性键
 *
 * 属性分为几个部分，每个部分都保留了属性标识符的范围：
 *
 *    名称|范围（包含）|描述
 *    -------------|--------------------------------|------------------------核心|0x000-0x01F，0x1000-0x11FF | Spinel核心PHY|0x020-0x02F，0x1200-0x12FF |无线PHY层MAC | 0x030-0x03F，0x1300-0x13FF | MAC层NET | 0x040-0x04F，0x1400-0x14FF |网络线程|0x050-0x05F，0x1500-0x15FF |线程IPv6 | 0x060-0x06F，0x1600-0x16FF | IPv6流|0x070-0x07F，0x1700-0x17FF |流MeshCop | 0x080-0x08F，0x1800-0x18FF |线程网格调试OpenThread | 0x1900-0x19FF | OpenThread特定服务器| 0x0A0-0x0AF | ALOC服务服务器RCP| 0x0B0-0x0FF | RCP特定接口| 0x100-0x1FF |接口（例如UART）PIB | 0x400-0x4FF | 802.15.4 PIB计数器| 0x500-0x7FF |计数器（MAC、IP等）。RCP|0x800-0x8FF|RCP特定属性（扩展）Nest|0x3BC0-0x3BFF|Nest（传统）Vendor |0x3C00-0x3FF| Vendor特定调试|0x4000-0x43FF|调试相关实验|2000000-2097151 |仅用于实验
 *
 */
enum
{
    ///上次操作状态
    /** 格式：`i`-只读
     *
     * 描述上次操作的状态。编码为压缩无符号整数（有关值列表，请参见“SPINEL_STATUS_”）。
     *
     * 此属性通常用于指示几乎所有主机到NCP操作的结果状态。
     *
     * 它在NCP启动时自动发出，其值指示重置原因。它也会在错误时异步发出（例如，NCP用完缓冲区）。
     *
     */
    SPINEL_PROP_LAST_STATUS = 0,

    ///协议版本
    /** 格式：`ii`-只读
     *
     * 描述协议版本信息。此属性包含两个字段，每个字段编码为压缩无符号整数：“i”：主要版本号“i”；次要版本号
     *
     * 版本号由“SPINEL_PROTOCOL_version_THREAD_MAYOR”和“SPINER_PROTOCOL-version_THRAD_MINOR”定义。
     *
     * 本规范描述了主要版本4和次要版本3。
     *
     */
    SPINEL_PROP_PROTOCOL_VERSION = 1,

    ///NCP版本
    /** 格式：`U`-只读
     *
     * 包含描述当前在NCP上运行的固件的字符串。编码为以零结尾的UTF-8字符串。
     *
     */
    SPINEL_PROP_NCP_VERSION = 2,

    ///NCP网络协议类型
    /** 格式：“i”-只读
     *
     * 该值标识此NCP的网络协议。有效的协议类型值由枚举“SPINEL_protocol_type_”定义：
     *
     *   `SPINEL_PROTOCOL_TYPE_BOOTLOADER` = 0 `SPINEL_PROTOCOL_TYPE_ZIGBEE_IP` = 2, `SPINEL_PROTOCOL_TYPE_THREAD` = 3,
     *
     * OpenThread NCP仅支持`SPINEL_PROTOCOL_TYPE_THREAD`
     *
     */
    SPINEL_PROP_INTERFACE_TYPE = 3,

    ///NCP供应商ID
    /** 格式：“i”-只读
     *
     * 供应商ID为零表示未知。
     *
     */
    SPINEL_PROP_VENDOR_ID = 4,

    ///NCP能力列表
    /** 格式：“A（i）”-只读
     *
     * 描述此NCP的支持功能。编码为压缩无符号整数列表。
     *
     * 功能值由SPINEL_CAP_*枚举指定。
     *
     */
    SPINEL_PROP_CAPS = 5,

    ///NCP接口计数
    /** 格式：“C”-只读
     *
     * 提供多个接口。
     *
     * 当前读数始终为1。
     *
     */
    SPINEL_PROP_INTERFACE_COUNT = 6,

    SPINEL_PROP_POWER_STATE = 7, ///<PowerState[C]（已弃用，请改用`MCU_POWER_STATE`）。

    ///NCP硬件地址
    /** 格式：“E”-只读
     *
     * 设备的静态EUI64地址，用作序列号。
     *
     */
    SPINEL_PROP_HWADDR = 8,

    SPINEL_PROP_LOCK          = 9,  ///<PropLock[b]（不支持）
    SPINEL_PROP_HBO_MEM_MAX   = 10, ///<最大卸载内存[S]（不支持）
    SPINEL_PROP_HBO_BLOCK_MAX = 11, ///<最大卸载块[S]（不支持）

    ///主机电源状态
    /** 格式：'C`
     *
     * 描述主机的当前电源状态。当NCP改变电源状态时，主机使用此属性通知NCP。然后NCP可以使用该状态来确定哪些属性需要异步更新。枚举“spinel_host_power_state_t”定义有效值（“spinel_host_power_state_`”）：
     *
     *   `HOST_POWER_STATE_OFFLINE`：主机已物理关闭，无法被NCP唤醒。所有异步命令都被静噪。
     *
     *   `HOST_POWER_STATE_DEEP_SLEEP`：主机处于低功耗状态，可以被NCP唤醒，但可能需要两秒以上才能完全响应。NCP必须避免发送不必要的属性更新，例如子表更新或调试流上的非关键消息。如果NCP需要唤醒主机以获取流量，NCP必须首先采取措施唤醒主机。一旦NCP向主机发出应该唤醒的信号，NCP必须在发送帧之前等待主机的某些活动（表明它完全唤醒）。
     *
     *   `HOST_POWER_STATE_RESERVED`：主机不能设置此值。如果NCP收到，NCP应将其视为“HOST_POWER_STATE_DEEP_SLEEP”的同义词。
     *
     *   `HOST_POWER_STATE_LOW_POWER`：主机处于低功率状态，可以立即被NCP唤醒。NCP应避免发送不必要的属性更新，例如子表更新或调试流上的非关键消息。
     *
     *   `HOST_POWER_STATE_ONLINE`：主机处于唤醒状态且响应迅速。NCP对异步更新不进行特殊过滤。
     *
     *   所有其他值均为RESERVED。它们不得由主机设置。如果NCP收到，NCP应将该值视为“HOST_POWER_STATE_LOW_POWER”的同义词。
     *
     * 设置此电源状态后，从主机到NCP的任何进一步命令将导致“host_power_state”自动恢复为“host_PROWER_state_ONLINE”。
     *
     * 当主机进入低功率状态时，应等待NCP确认命令的响应（使用“CMD_VALUE_is”）。一旦接收到该确认，主机就可以进入低功率状态。
     *
     * 如果NCP具有“CAP_UNSOL_UPDATE_FILTER”功能，则当主机指示其处于低功率状态时，应接受由“PROP_UNSOL_UPDTE_FILTER”屏蔽的任何未经请求的属性更新。恢复到“HOST_POWER_STATE_ONLINE”状态后，“PROP_UNSOL_UPDATE_FILTER”的值必须与主机进入低功率状态之前指定的值保持不变。
     *
     */
    SPINEL_PROP_HOST_POWER_STATE = 12,

    ///NCP的MCU电源状态
    /** 格式：'C'所需功能：CAP_MCU_POWER_SAVE
     *
     * 此属性指定当底层平台的操作系统进入空闲模式（即，所有活动任务/事件都被处理，并且MCU可能进入节能电源状态）时，NCP的微控制器（MCU）的所需电源状态。
     *
     * 电源状态主要决定主机应如何与NCP交互，以及主机在与NCP通信之前是否需要NCP的外部触发器（“poke”）。重置后，MCU电源状态必须为SPINEL_MCU_power_state_ON。
     *
     * 枚举“spinel_mcu_power_state_t”定义有效值（“spinel_mcu_power_state_”常量）：
     *
     *   `SPINEL_CU_POWER_STATE_ON`：NCP的MCU始终保持打开状态并处于活动状态。当NCP的期望功率状态设置为该值时，主机可以向NCP发送消息，而无需任何“戳”或外部触发。MCU应保持打开状态并处于活动状态。注意，“ON”电源状态仅决定MCU的电源模式，与无线电状态无关。
     *
     *   `SPINEL_CU_POWER_STATE_LOW_POWER`：NCP的MCU可以进入低功耗（节能）状态。当NCP的所需功率状态设置为“LOW_power”时，主机在与NCP通信（向NCP发送消息）之前应“触发”NCP（例如，外部触发，如中断）。“poke”机制由平台代码决定（基于NCP与主机的接口）。当电源状态设置为“LOW_power”时，NCP仍可（在任何时候）向主机发送消息。请注意，从NCP接收到消息并不表示NCP的电源状态已经改变，即，当主机想要与NCP通话时，主机将继续“戳”NCP，直到电源状态被明确改变（通过将该属性设置为“ON”）。注意，“LOW_POWER”电源状态仅决定MCU的电源模式，与无线电状态无关。
     *
     *   `SPINEL_CU_POWER_STATE_OFF`：NCP已完全关闭。NCP硬件复位（通过复位引脚）需要将NCP恢复到“SPINEL_MCU_POWER_STATE_ON`。复位后RAM不被保留。
     *
     */
    SPINEL_PROP_MCU_POWER_STATE = 13,

    SPINEL_PROP_BASE_EXT__BEGIN = 0x1000,

    ///GPIO配置
    /** 格式：`A（CCU）`类型：只读（可选使用`CMD_PROP_VALUE_INSERT`读写）
     *
     * 包含以下字段的结构数组：
     *
     * *`C`:GPIO编号`C`：GPIO配置标志`U`：人类可读的GPIO名称
     *
     * 不支持没有相应条目的GPIO。
     *
     * 配置参数包含GPIO的配置标志：
     *
     *       0   1   2   3   4   5   6   7 +---+---+---+---+---+---+---+---+ |DIR|PUP|PDN|TRIGGER| RESERVED | +---+---+---+---+---+---+---+---+ |O/D| +---+
     *
     * *“DIR”：固定方向。输入清除（0），输出设置（1）`PUP`：上拉启用标志`PDN`/`O/D`：标志含义取决于引脚方向：输入：下拉启用。输出：输出为开路漏极`TRIGGER`：描述引脚更改如何从NCP向主机生成异步通知命令（TBD）的枚举。0：此引脚的功能已禁用1：下降沿触发2：上升沿触发3：电平变化触发“RESERVED”：保留位以供将来使用。读取时始终清零并忽略。
     *
     * 作为可选功能，可以使用“CMD_PROP_VALUE_INSERT”命令修改单个引脚的配置。只有GPIO编号和标志字段必须存在，GPIO名称（如果存在）将被忽略。此命令只能用于修改已公开的GPIO的配置，主机无法使用此命令添加其他GPIO。
     */
    SPINEL_PROP_GPIO_CONFIG = SPINEL_PROP_BASE_EXT__BEGIN + 0,

    ///GPIO状态位掩码
    /** 格式：`D`类型：读写
     *
     * 包含标识GPIO状态的位字段。与这些属性相关的数据长度取决于GPIO的数量。如果你有10个GPIO，你就有两个字节。GPIO从最高有效位到最低有效位进行编号，因此0x80是GPIO 0，0x40是GPIO 1，等等。
     *
     * 对于配置为输入的GPIO：
     *
     * *“CMD_PROP_VAUE_GET”：相关位的值描述从引脚读取的逻辑电平`CMD_PROP_VALUE_SET`：这些引脚忽略相关位的值。
     *
     * 对于配置为输出的GPIO：
     *
     * *`CMD_PROP_VAUE_GET`：相关位的值是特定于实现的`CMD_PROP_VALUE_SET`：相关位的值决定输出的新逻辑电平。如果该引脚配置为漏极开路，则将相关位设置为1将导致引脚进入Hi-Z状态。
     *
     * 对于“PROP_GPIO_COONFIG”中未指定的GPIO：
     *
     * *`CMD_PROP_VAUE_GET`：相关位的值是特定于实现的`CMD_PROP_VALUE_SET`：NCP必须忽略相关位的值。
     *
     * 写入时，未指定的位假定为零。
     */
    SPINEL_PROP_GPIO_STATE = SPINEL_PROP_BASE_EXT__BEGIN + 2,

    ///GPIO状态仅设置位掩码
    /** 格式：`D`类型：只读
     *
     * 允许在不影响其他GPIO状态的情况下设置各种输出GPIO的状态。包含一个位字段，用于标识应将其状态设置为1的输出GPIO。
     *
     * 写入时，未指定的位假定为零。必须忽略“PROP_GPIO_COONFIG”中未指定的GPIO的任何位的值。
     */
    SPINEL_PROP_GPIO_STATE_SET = SPINEL_PROP_BASE_EXT__BEGIN + 3,

    ///GPIO状态仅清除位掩码
    /** 格式：`D`类型：只读
     *
     * 允许清除各种输出GPIO的状态，而不影响其他GPIO状态。包含一个位字段，用于标识应将其状态清除为0的输出GPIO。
     *
     * 写入时，未指定的位假定为零。必须忽略“PROP_GPIO_COONFIG”中未指定的GPIO的任何位的值。
     */
    SPINEL_PROP_GPIO_STATE_CLEAR = SPINEL_PROP_BASE_EXT__BEGIN + 4,

    ///来自TRNG的32位随机数，随时可用。
    SPINEL_PROP_TRNG_32 = SPINEL_PROP_BASE_EXT__BEGIN + 5,

    ///来自TRNG的16个随机字节，随时可用。
    SPINEL_PROP_TRNG_128 = SPINEL_PROP_BASE_EXT__BEGIN + 6,

    ///来自TRNG熵源的代表32位熵的原始样本。
    SPINEL_PROP_TRNG_RAW_32 = SPINEL_PROP_BASE_EXT__BEGIN + 7,

    ///NCP未经请求的更新过滤器
    /** 格式：`A（I）`类型：读写（可选插入-删除）所需功能：`CAP_UNSOL_UPDATE_FILTER`
     *
     * 包含从生成未经请求的值更新中排除的属性列表。重置后此属性为空。换句话说，主机可以通过将特定属性id添加到此列表中，选择不主动更新特定属性。主机不应将“PROP_UNSOL_UPDATE_list”中不存在的属性添加到此列表中。如果添加了此类属性，NCP将忽略不支持的属性。
     *
     */
    SPINEL_PROP_UNSOL_UPDATE_FILTER = SPINEL_PROP_BASE_EXT__BEGIN + 8,

    ///能够生成未经请求的价值更新的属性列表。
    /** 格式：`A（I）`类型：只读所需功能：`CAP_UNSOL_UPDATE_FILTER`
     *
     * 包含能够生成未经请求的值更新的属性列表。填充“PROP_UNSOL_UPDATE_FILTER”以禁用所有未经请求的属性更新时，可以使用此列表。
     *
     * 该属性旨在有效地作为给定NCP固件的常量。
     */
    SPINEL_PROP_UNSOL_UPDATE_LIST = SPINEL_PROP_BASE_EXT__BEGIN + 9,

    SPINEL_PROP_BASE_EXT__END = 0x1100,

    SPINEL_PROP_PHY__BEGIN         = 0x20,
    SPINEL_PROP_PHY_ENABLED        = SPINEL_PROP_PHY__BEGIN + 0,  ///<[b]
    SPINEL_PROP_PHY_CHAN           = SPINEL_PROP_PHY__BEGIN + 1,  ///< [C]
    SPINEL_PROP_PHY_CHAN_SUPPORTED = SPINEL_PROP_PHY__BEGIN + 2,  ///< [A(C)]
    SPINEL_PROP_PHY_FREQ           = SPINEL_PROP_PHY__BEGIN + 3,  ///<千赫[L]
    SPINEL_PROP_PHY_CCA_THRESHOLD  = SPINEL_PROP_PHY__BEGIN + 4,  ///<dBm[c]
    SPINEL_PROP_PHY_TX_POWER       = SPINEL_PROP_PHY__BEGIN + 5,  ///<[c]
    SPINEL_PROP_PHY_RSSI           = SPINEL_PROP_PHY__BEGIN + 6,  ///<dBm[c]
    SPINEL_PROP_PHY_RX_SENSITIVITY = SPINEL_PROP_PHY__BEGIN + 7,  ///<dBm[c]
    SPINEL_PROP_PHY_PCAP_ENABLED   = SPINEL_PROP_PHY__BEGIN + 8,  ///<[b]
    SPINEL_PROP_PHY_CHAN_PREFERRED = SPINEL_PROP_PHY__BEGIN + 9,  ///< [A(C)]
    SPINEL_PROP_PHY_FEM_LNA_GAIN   = SPINEL_PROP_PHY__BEGIN + 10, ///<dBm[c]

    ///发出信道的最大功率信号
    /** 格式：`Cc`
     *
     * 第一个字节是信道，然后是最大发射功率，仅写。
     */
    SPINEL_PROP_PHY_CHAN_MAX_POWER = SPINEL_PROP_PHY__BEGIN + 11,
    ///地区代码
    /** 格式：`S`
     *
     * ISO 3166字母-2代码的ascii表示。
     *
     */
    SPINEL_PROP_PHY_REGION_CODE = SPINEL_PROP_PHY__BEGIN + 12,

    SPINEL_PROP_PHY__END = 0x30,

    SPINEL_PROP_PHY_EXT__BEGIN = 0x1200,

    ///信号干扰检测启用
    /** 格式：`b`
     *
     * 指示是否启用或禁用干扰检测。设置为true以启用干扰检测。
     */
    SPINEL_PROP_JAM_DETECT_ENABLE = SPINEL_PROP_PHY_EXT__BEGIN + 0,

    ///检测到信号干扰指示灯
    /** 格式：`b`（只读）
     *
     * 如果检测到无线电干扰，则设置为真。否则设置为false。
     *
     * 启用干扰检测后，通过“CMD_PROP_value_is”异步发出对该属性值的更改。
     */
    SPINEL_PROP_JAM_DETECTED = SPINEL_PROP_PHY_EXT__BEGIN + 1,

    ///干扰检测RSSI阈值
    /** 格式：`c`单位：dBm
     *
     * 该参数描述了阈值RSSI电平（以dBm为单位测量），超过该阈值，干扰检测将认为信道被阻塞。
     */
    SPINEL_PROP_JAM_DETECT_RSSI_THRESHOLD = SPINEL_PROP_PHY_EXT__BEGIN + 2,

    ///干扰检测窗口大小
    /** 格式：`C`单位：秒（1-63）
     *
     * 此参数描述信号干扰检测的窗口期。
     */
    SPINEL_PROP_JAM_DETECT_WINDOW = SPINEL_PROP_PHY_EXT__BEGIN + 3,

    ///干扰检测忙期
    /** 格式：`C`单位：秒（1-63）
     *
     * 此参数描述检测窗口内RSSI必须高于“PROP_JAM_DETECT_RSI_THRESHOLD”才能触发检测的聚合秒数。
     *
     * 当“PROP_JAM_DETECT_BUSY”大于“PROP_JAM_DETECT_WINDW”时，干扰检测功能的行为未定义。
     */
    SPINEL_PROP_JAM_DETECT_BUSY = SPINEL_PROP_PHY_EXT__BEGIN + 4,

    ///干扰检测历史位图（用于调试）
    /** 格式：`X`（只读）
     *
     * 该值提供干扰检测模块的当前状态信息，用于监控/调试。它返回一个64位的值，其中每一位对应一秒的间隔，从最新间隔的位0开始，最早间隔的位63（63秒之前）。如果干扰检测模块在相应的1秒间隔内观察到/检测到高信号电平，则该位设置为1。
     *
     */
    SPINEL_PROP_JAM_DETECT_HISTORY_BITMAP = SPINEL_PROP_PHY_EXT__BEGIN + 5,

    ///通道监测采样间隔
    /** 格式：`L`（只读）单位：毫秒
     *
     * 所需功能：SPINEL_CAP_CHANNEL_MONITOR
     *
     * 如果启用并激活信道监测，则在每个采样间隔执行零持续时间能量扫描，每个信道采集一个RSSI采样。将RSSI样本与预先指定的RSSI阈值进行比较。
     *
     */
    SPINEL_PROP_CHANNEL_MONITOR_SAMPLE_INTERVAL = SPINEL_PROP_PHY_EXT__BEGIN + 6,

    ///信道监测RSSI阈值
    /** 格式：`c`（只读）单位：dBm
     *
     * 所需功能：SPINEL_CAP_CHANNEL_MONITOR
     *
     * 此值指定通道监控模块使用的阈值。信道监测在预先指定的样本数（样本窗口）内保持高于阈值的RSSI样本的平均速率。
     *
     */
    SPINEL_PROP_CHANNEL_MONITOR_RSSI_THRESHOLD = SPINEL_PROP_PHY_EXT__BEGIN + 7,

    ///通道监测样本窗口
    /** 格式：`L`（只读）单位：样本数
     *
     * 所需功能：SPINEL_CAP_CHANNEL_MONITOR
     *
     * 信道监测模块使用的平均采样窗口长度（以信道采样数为单位）。信道监测将在每个采样间隔对所有信道进行采样。它保持（近似）样本窗口内高于RSSI阈值的RSSI样本的平均速率。
     *
     */
    SPINEL_PROP_CHANNEL_MONITOR_SAMPLE_WINDOW = SPINEL_PROP_PHY_EXT__BEGIN + 8,

    ///信道监测样本计数
    /** 格式：`L`（只读）单位：样本数
     *
     * 所需功能：SPINEL_CAP_CHANNEL_MONITOR
     *
     * 信道监视模块自启动以来（自启用线程网络接口以来）获取的RSSI样本总数（每个信道）。
     *
     */
    SPINEL_PROP_CHANNEL_MONITOR_SAMPLE_COUNT = SPINEL_PROP_PHY_EXT__BEGIN + 9,

    ///信道监测信道占用
    /** 格式：`A（t（CU））`（只读）
     *
     * 所需功能：SPINEL_CAP_CHANNEL_MONITOR
     *
     * 每个项目的数据为：
     *
     *  `C`：频道`U`：频道占用指示器
     *
     * 信道占用率值表示（近似）样本窗口最新RSSI样本内高于RSSI阈值（“坏”RSSI样本）的RSSI样本的平均速率/百分比。
     *
     * 最大值“0xffff”表示所有RSSI样本均高于RSSI阈值（即100%的样本为“坏”）。
     *
     */
    SPINEL_PROP_CHANNEL_MONITOR_CHANNEL_OCCUPANCY = SPINEL_PROP_PHY_EXT__BEGIN + 10,

    ///收音机盖
    /** 格式：`i`（只读）
     *
     * 每个项目的数据为：
     *
     *  `i`：无线电能力。
     *
     */
    SPINEL_PROP_RADIO_CAPS = SPINEL_PROP_PHY_EXT__BEGIN + 11,

    ///所有coex指标相关计数器。
    /** 格式：t（LLLLLLLL）t（LLLL LLLLL）bL（只读）
     *
     * 所需功能：SPINEL_CAP_RADIO_COEX
     *
     * 内容包括两个结构和两个公共变量，第一个结构对应于所有与发射相关的coex计数器，第二个结构提供与接收相关的计数器。
     *
     * 传输结构包括：'L'：NumTxRequest（tx请求数）。'L'：NumTxGrantImmediate（授权处于活动状态时的tx请求数）。'L'：NumTxGrantWait（授权处于非活动状态时的tx请求数）。'L'：NumTxGrantWaitActivated（授予处于非活动状态时最终授予的tx请求数）。'L'：NumTxGrantWaitTimeout（授权处于非活动状态时超时的tx请求数）。'L'：NumTxGrantDeactivedDuringRequest（授权停用时正在进行的tx请求数）。'L'：NumTxDelayedGrant（50us内未授权的tx请求数）。'L'：AvgTxRequestToGrantTime（从tx请求到授权的平均使用时间）。
     *
     * 接收结构包括：'L'：NumRxRequest（rx请求数）。'L'：NumRxGrantImmediate（授权处于活动状态时的rx请求数）。'L'：NumRxGrantWait（授权处于非活动状态时的rx请求数）。'L'：NumRxGrantWaitActivated（授予处于非活动状态时最终授予的rx请求数）。'L'：NumRxGrantWaitTimeout（授权处于非活动状态时超时的rx请求数）。'L'：NumRxGrantDeactivedDuringRequest（授权停用时正在进行的rx请求数）。'L'：NumRxDelayedGrant（50us内未授权的rx请求数）。'L'：AvgRxRequestToGrantTime（从rx请求到授权的平均使用时间）。'L'：NumRxGrantOne（未收到授权而完成的rx请求数）。
     *
     * 两个常见变量：“b”：已停止（Stats集合因饱和而停止）L'：NumGrantGlitch（授权故障的数量）。
     */
    SPINEL_PROP_RADIO_COEX_METRICS = SPINEL_PROP_PHY_EXT__BEGIN + 12,

    ///无线电Coex启用
    /** 格式：`b`
     *
     * 所需功能：SPINEL_CAP_RADIO_COEX
     *
     * 指示是否启用或禁用无线电coex。设置为true以启用无线电coex。
     */
    SPINEL_PROP_RADIO_COEX_ENABLE = SPINEL_PROP_PHY_EXT__BEGIN + 13,

    SPINEL_PROP_PHY_EXT__END = 0x1300,

    SPINEL_PROP_MAC__BEGIN = 0x30,

    ///MAC扫描状态
    /** 格式：`C`
     *
     * 可能的值来自枚举“spinel_scan_state_t”。
     *
     *   SCAN_STATE_IDLE SCAN_STATE_BEACON SCAN_STATE_ENERGY SCAN_STATE_DISCOVER
     *
     * 设置为“SCAN_STATE_BEACON”以启动活动扫描。信标将从`PROP_MAC_SCAN_BEACON`发出。
     *
     * 设置为“SCAN_STATE_ENERGY”以启动能量扫描。信道能量结果将通过发射“PROP_MAC_energy_SCAN_result”（每个信道）报告。
     *
     * 设置为“SCAN_STATE_DISOVER”以启动线程MLE发现扫描操作。将从`PROP_MAC_scan_BEACON`发出发现扫描结果。
     *
     * 扫描完成后，值切换为“SCAN_STATE_IDLE”。
     *
     */
    SPINEL_PROP_MAC_SCAN_STATE = SPINEL_PROP_MAC__BEGIN + 0,

    ///MAC扫描信道掩码
    /** 格式：`A（C）`
     *
     * 要扫描的频道列表。
     *
     */
    SPINEL_PROP_MAC_SCAN_MASK = SPINEL_PROP_MAC__BEGIN + 1,

    ///MAC扫描信道周期
    /** 格式：`S`单位：每个频道毫秒
     *
     */
    SPINEL_PROP_MAC_SCAN_PERIOD = SPINEL_PROP_MAC__BEGIN + 2,

    ///MAC扫描信标
    /** 格式`Cct（ESSc）t（iCUdd）`-仅异步事件
     *
     * 扫描信标具有两个嵌入结构，其中包含关于MAC层和NET层的信息。它们的格式取决于当前使用的MAC和NET层。以下格式适用于具有线程的802.15.4 MAC：
     *
     *  `C`：信道`C`：信标`t`的RSSI：MAC层属性（802.15.4层）`E`：长地址`S`：短地址`S`:PAN-ID`C`；LQI NET层属性`i`：协议号（SPINEL_Protocol_TYPE_值）`C`：标志（SPINEL_beacon_THREAD_FLAG_值）` U`：网络名称`d`：XPANID `d`
     *
     * 未来可能会向每个结构添加额外的参数，因此应注意读取每个结构前面的长度。
     *
     */
    SPINEL_PROP_MAC_SCAN_BEACON = SPINEL_PROP_MAC__BEGIN + 3,

    ///MAC长地址
    /** 格式：`E`
     *
     * 此节点的802.15.4长地址。
     *
     */
    SPINEL_PROP_MAC_15_4_LADDR = SPINEL_PROP_MAC__BEGIN + 4,

    ///MAC短地址
    /** 格式：`S`
     *
     * 此节点的802.15.4短地址。
     *
     */
    SPINEL_PROP_MAC_15_4_SADDR = SPINEL_PROP_MAC__BEGIN + 5,

    /// MAC PAN ID
    /** 格式：`S`
     *
     * 此节点关联的802.15.4 PANID。
     *
     */
    SPINEL_PROP_MAC_15_4_PANID = SPINEL_PROP_MAC__BEGIN + 6,

    ///MAC流原始已启用
    /** 格式：`b`
     *
     * 设置为true以启用从“PROP_STRAM_raw”发出的原始MAC帧。
     *
     */
    SPINEL_PROP_MAC_RAW_STREAM_ENABLED = SPINEL_PROP_MAC__BEGIN + 7,

    ///MAC混杂模式
    /** 格式：`C`
     *
     * 可能的值来自枚举`SPINEL_MAC_PROMISCUUS_MODE_`：
     *
     *   `SPINEL_MAC_PROMISCUUS_MODE_OFF`正常MAC过滤已到位。
     *
     *   `SPINEL_MAC_PROMISCUUS_MODE_NETWORK`匹配网络的所有MAC数据包都将向堆栈传递。
     *
     *   `SPINEL_MAC_PROMISCUUS_MODE_FULL`所有解码的MAC数据包都会向堆栈传递。
     *
     */
    SPINEL_PROP_MAC_PROMISCUOUS_MODE = SPINEL_PROP_MAC__BEGIN + 8,

    ///MAC能量扫描结果
    /** 格式：`Cc`-仅异步事件
     *
     * 此属性在每个扫描通道的能量扫描操作期间发出，格式如下：
     *
     *   `C`：信道`C`：RSSI（单位dBm）
     *
     */
    SPINEL_PROP_MAC_ENERGY_SCAN_RESULT = SPINEL_PROP_MAC__BEGIN + 9,

    ///MAC数据轮询周期
    /** 格式：`L`单位：毫秒（用户指定）数据轮询（802.15.4 MAC数据请求）周期，以毫秒为单位。值为零表示没有用户指定的轮询周期，网络堆栈根据MLE子超时确定最大周期。
     *
     * 如果该值为非零，则指定数据轮询传输之间的最长周期。注意，当期望控制消息时（例如，当等待MLE子ID响应时），网络堆栈可以更频繁地发送数据请求传输。
     *
     */
    SPINEL_PROP_MAC_DATA_POLL_PERIOD = SPINEL_PROP_MAC__BEGIN + 10,

    SPINEL_PROP_MAC__END = 0x40,

    SPINEL_PROP_MAC_EXT__BEGIN = 0x1300,

    ///MAC允许列表
    /** 格式：`A（t（Ec））`所需功能：`CAPMAC_ALLOWLIST`
     *
     * 结构参数：
     *
     *  `E`：节点“c”的EUI64地址：可选RSSI覆盖值。值127指示该地址没有启用RSSI覆盖特性。如果在设置或插入时忽略此值，则假定为127。删除时忽略此参数。
     */
    SPINEL_PROP_MAC_ALLOWLIST = SPINEL_PROP_MAC_EXT__BEGIN + 0,

    ///MAC允许列表启用标志
    /** 格式：`b`所需功能：`CAPMAC_ALLOWLIST`
     *
     */
    SPINEL_PROP_MAC_ALLOWLIST_ENABLED = SPINEL_PROP_MAC_EXT__BEGIN + 1,

    ///MAC扩展地址
    /** 格式：`E`
     *
     *  由线程指定。随机选择，但非易失性EUI-64。
     */
    SPINEL_PROP_MAC_EXTENDED_ADDR = SPINEL_PROP_MAC_EXT__BEGIN + 2,

    ///MAC源匹配启用标志
    /** 格式：`b`所需功能：SPINEL_CAPMAC_RAW或SPINEL_CAP _CONFIG_RADIO
     *
     * 设置为true可启用无线电源匹配，设置为false可禁用无线电源匹配。无线电在生成ACK时使用源匹配功能。短地址列表和扩展地址列表用于设置ACK中的帧挂起位。
     *
     */
    SPINEL_PROP_MAC_SRC_MATCH_ENABLED = SPINEL_PROP_MAC_EXT__BEGIN + 3,

    ///MAC源匹配短地址列表
    /** 格式：`A（S）`所需功能：SPINEL_CAPMAC_RAW或SPINEL_CAP _CONFIG_RADIO
     *
     */
    SPINEL_PROP_MAC_SRC_MATCH_SHORT_ADDRESSES = SPINEL_PROP_MAC_EXT__BEGIN + 4,

    ///MAC源匹配扩展地址列表
    /** 格式：`A（E）`所需功能：SPINEL_CAPMAC_RAW或SPINEL_CAP _CONFIG_RADIO
     *
     */
    SPINEL_PROP_MAC_SRC_MATCH_EXTENDED_ADDRESSES = SPINEL_PROP_MAC_EXT__BEGIN + 5,

    ///MAC Denylist公司
    /** 格式：`A（t（E））`所需功能：`CAPMAC_ALLOWLIST`
     *
     * 结构参数：
     *
     *  `E`：节点的EUI64地址
     *
     */
    SPINEL_PROP_MAC_DENYLIST = SPINEL_PROP_MAC_EXT__BEGIN + 6,

    ///MAC Denylist启用标志
    /** 格式：`b`所需功能：`CAPMAC_ALLOWLIST`
     */
    SPINEL_PROP_MAC_DENYLIST_ENABLED = SPINEL_PROP_MAC_EXT__BEGIN + 7,

    ///MAC接收信号强度滤波器
    /** 格式：`A（t（Ec））`所需功能：`CAPMAC_ALLOWLIST`
     *
     * 结构参数：
     *
     * *“E”：节点的可选EUI64地址。如果未包含，则设置默认RSS`c`：固定RSS。127表示未设置。
     */
    SPINEL_PROP_MAC_FIXED_RSS = SPINEL_PROP_MAC_EXT__BEGIN + 8,

    ///CCA故障率
    /** 格式：`S`
     *
     * 此属性提供当前CCA（清除通道评估）故障率。
     *
     * 对应于100%故障率的最大值“0xffff”。
     *
     */
    SPINEL_PROP_MAC_CCA_FAILURE_RATE = SPINEL_PROP_MAC_EXT__BEGIN + 9,

    ///MAC最大直接重试次数
    /** 格式：`C`
     *
     * 直接帧传输重试的最大（用户指定）次数。
     *
     */
    SPINEL_PROP_MAC_MAX_RETRY_NUMBER_DIRECT = SPINEL_PROP_MAC_EXT__BEGIN + 10,

    ///MAC最大间接重试次数
    /** 格式：`C`所需功能：`SPINEL_CAP_CONFIG_FTD`
     *
     * 间接帧传输重试的最大（用户指定）次数。
     *
     */
    SPINEL_PROP_MAC_MAX_RETRY_NUMBER_INDIRECT = SPINEL_PROP_MAC_EXT__BEGIN + 11,

    SPINEL_PROP_MAC_EXT__END = 0x1400,

    SPINEL_PROP_NET__BEGIN = 0x40,

    ///网络已保存（已调试）
    /** 格式：`b`-只读
     *
     * 如果存储/保存了网络状态，则返回true。
     *
     */
    SPINEL_PROP_NET_SAVED = SPINEL_PROP_NET__BEGIN + 0,

    ///网络接口状态
    /** 格式`b`-读写
     *
     * 网络接口上/下状态。写true使接口上升，写false使接口下降。
     *
     */
    SPINEL_PROP_NET_IF_UP = SPINEL_PROP_NET__BEGIN + 1,

    ///线程堆栈操作状态
    /** 格式`b`-读写
     *
     * 线程堆栈操作状态。写true以启动线程堆栈，写false以停止线程堆栈。
     *
     */
    SPINEL_PROP_NET_STACK_UP = SPINEL_PROP_NET__BEGIN + 2,

    ///线程设备角色
    /** 格式`C`-读写
     *
     * 可能的值来自枚举`spinel_net_role_t`
     *
     *  SPINEL_NET_ROLE_DETACHED = 0, SPINEL_NET_ROLE_CHILD = 1, SPINEL_NET_ROLE_ROUTER = 2, SPINEL_NET_ROLE_LEADER = 3,
     *
     */
    SPINEL_PROP_NET_ROLE = SPINEL_PROP_NET__BEGIN + 3,

    ///线程网络名称
    /** 格式`U`-读写
     *
     */
    SPINEL_PROP_NET_NETWORK_NAME = SPINEL_PROP_NET__BEGIN + 4,

    ///线程网络扩展PAN ID
    /** 格式`D`-读写
     *
     */
    SPINEL_PROP_NET_XPANID = SPINEL_PROP_NET__BEGIN + 5,

    ///线程网络密钥
    /** 格式`D`-读写
     *
     */
    SPINEL_PROP_NET_NETWORK_KEY = SPINEL_PROP_NET__BEGIN + 6,

    ///线程网络密钥序列计数器
    /** 格式`L`-读写
     *
     */
    SPINEL_PROP_NET_KEY_SEQUENCE_COUNTER = SPINEL_PROP_NET__BEGIN + 7,

    ///线程网络分区Id
    /** 格式`L`-读写
     *
     * 此节点所属分区的分区ID。
     *
     */
    SPINEL_PROP_NET_PARTITION_ID = SPINEL_PROP_NET__BEGIN + 8,

    ///要求现有联接
    /** 格式：`b`默认值：`false`
     *
     * 此标志通常用于首次与现有网络关联的节点。如果在“PROP_NET_STACK_UP”设置为“true”之前将其设置为“true”，则将阻止在关联时创建新分区。如果节点无法与现有分区关联，“PROP_LAST_STATUS”将发出一个状态，指示关联失败的原因，而“PROP_NET_STACK_UP”将自动恢复为“false”。
     *
     * 一旦与现有分区关联，此标志将自动恢复为“false”。
     *
     * 当“PROP_NET_STACK_UP”已设置为“true”时，此属性设置为“true”的行为未定义。
     *
     */
    SPINEL_PROP_NET_REQUIRE_JOIN_EXISTING = SPINEL_PROP_NET__BEGIN + 9,

    ///线程网络密钥切换保护时间
    /** 格式`L`-读写
     *
     */
    SPINEL_PROP_NET_KEY_SWITCH_GUARDTIME = SPINEL_PROP_NET__BEGIN + 10,

    ///线程网络PSKc
    /** 格式`D`-读写
     *
     */
    SPINEL_PROP_NET_PSKC = SPINEL_PROP_NET__BEGIN + 11,

    SPINEL_PROP_NET__END = 0x50,

    SPINEL_PROP_NET_EXT__BEGIN = 0x1400,
    SPINEL_PROP_NET_EXT__END   = 0x1500,

    SPINEL_PROP_THREAD__BEGIN = 0x50,

    ///线程负责人IPv6地址
    /** 格式`6`-只读
     *
     */
    SPINEL_PROP_THREAD_LEADER_ADDR = SPINEL_PROP_THREAD__BEGIN + 0,

    ///线程父级信息
    /** 格式：`ESLccCC`-只读
     *
     *  `E`：扩展地址`S`：RLOC16`L`：年龄（从上次收到消息起的秒数）`c`：平均RSS（单位dBm）`c`:上次RSSI（单位dBm`）`c`：链路质量输入`c`:链路质量输出
     *
     */
    SPINEL_PROP_THREAD_PARENT = SPINEL_PROP_THREAD__BEGIN + 1,

    ///线程子表
    /** 格式：[A（t（ESLLCCcCc）]-只读
     *
     * 每个项目的数据为：
     *
     *  `E`：扩展地址`S`：RLOC16`L`：超时（以秒为单位）`L`；年龄（以秒计）`L'：网络数据版本`C`：链路质量in `C`：平均RSS（以dBm为单位）` C`：模式（位标志）` C`：最后RSSI（以dBm为单位）
     *
     */
    SPINEL_PROP_THREAD_CHILD_TABLE = SPINEL_PROP_THREAD__BEGIN + 2,

    ///线程前导路由器Id
    /** 格式`C`-只读
     *
     * 当前领导者的路由器id。
     *
     */
    SPINEL_PROP_THREAD_LEADER_RID = SPINEL_PROP_THREAD__BEGIN + 3,

    ///螺纹引线重量
    /** 格式`C`-只读
     *
     * 当前引线的引线权重。
     *
     */
    SPINEL_PROP_THREAD_LEADER_WEIGHT = SPINEL_PROP_THREAD__BEGIN + 4,

    ///螺纹局部引线重量
    /** 格式`C`-只读
     *
     * 此节点的引线权重。
     *
     */
    SPINEL_PROP_THREAD_LOCAL_LEADER_WEIGHT = SPINEL_PROP_THREAD__BEGIN + 5,

    ///线程本地网络数据
    /** 格式`D`-只读
     *
     */
    SPINEL_PROP_THREAD_NETWORK_DATA = SPINEL_PROP_THREAD__BEGIN + 6,

    ///线程本地网络数据版本
    /** 格式`C`-只读
     *
     */
    SPINEL_PROP_THREAD_NETWORK_DATA_VERSION = SPINEL_PROP_THREAD__BEGIN + 7,

    ///线程本地稳定网络数据
    /** 格式`D`-只读
     *
     */
    SPINEL_PROP_THREAD_STABLE_NETWORK_DATA = SPINEL_PROP_THREAD__BEGIN + 8,

    ///线程本地稳定网络数据版本
    /** 格式`C`-只读
     *
     */
    SPINEL_PROP_THREAD_STABLE_NETWORK_DATA_VERSION = SPINEL_PROP_THREAD__BEGIN + 9,

    ///在网格前缀上
    /** 格式：`A（t（6CbCbSC））`
     *
     * 每个项目的数据为：
     *
     *  `6`：IPv6前缀`C`：前缀长度（位）`b`：稳定标志`C`；TLV标志（SPINEL_NET_flag_definition）`b`:“在本地定义”标志。设置此网络是否在本地定义。假设设置、插入和替换为真。清除网格上网络是否由其他节点定义。INSERT和REMOVE命令忽略此字段`S`：注册此网格前缀项的设备的RLOC16。添加网格上前缀时，不会使用或忽略此值。INSERT和REMOVE命令忽略此字段`C`：TLV标志扩展（线程1.2特性的附加字段）。
     *
     */
    SPINEL_PROP_THREAD_ON_MESH_NETS = SPINEL_PROP_THREAD__BEGIN + 10,

    ///离网管线
    /** 格式：[A（t（6CbCbb））]
     *
     * 每个项目的数据为：
     *
     *  `6`：路由前缀`C`：前缀长度（以位为单位）`b`：稳定标志`C`；路由标志（SPINEL_Route_flag_和SPINEL_RUUTE_PREFERNCE_定义）`b`:“在本地定义”标志。设置此路由信息是否在本地定义为本地网络数据的一部分。假设设置、插入和替换为真。清除路由是否是分区网络数据的一部分`b`：“下一跳是此设备”标志。设置路由的下一跳是否为该设备本身（即，路由是由该设备添加的）。添加外部路由时忽略此值。对于任何添加的路由，下一跳是该设备`S`：注册此路由条目的设备的RLOC16。添加路由时，不使用并忽略此值。
     *
     */
    SPINEL_PROP_THREAD_OFF_MESH_ROUTES = SPINEL_PROP_THREAD__BEGIN + 11,

    ///线程辅助端口
    /** 格式`A（S）`
     *
     * 端口号数组。
     */
    SPINEL_PROP_THREAD_ASSISTING_PORTS = SPINEL_PROP_THREAD__BEGIN + 12,

    ///线程允许本地网络数据更改
    /** 格式`b`-读写
     *
     * 在更改本地网络数据之前设置为true。完成后设置为false。这允许将更改聚合到单个事件中。
     *
     */
    SPINEL_PROP_THREAD_ALLOW_LOCAL_NET_DATA_CHANGE = SPINEL_PROP_THREAD__BEGIN + 13,

    ///线程模式
    /** 格式：`C`
     *
     *  此属性包含此节点的模式TLV值。该位字段中位的含义由线程规范第4.5.2节定义。
     *
     * 值“SPINEL_THREAD_MODE_*”定义位字段
     *
     */
    SPINEL_PROP_THREAD_MODE = SPINEL_PROP_THREAD__BEGIN + 14,

    SPINEL_PROP_THREAD__END = 0x60,

    SPINEL_PROP_THREAD_EXT__BEGIN = 0x1500,

    ///线程子级超时
    /** 格式：`L`单位：秒
     *
     *  在子角色中操作时使用。
     */
    SPINEL_PROP_THREAD_CHILD_TIMEOUT = SPINEL_PROP_THREAD_EXT__BEGIN + 0,

    ///线程RLOC16
    /** 格式：`S`
     *
     */
    SPINEL_PROP_THREAD_RLOC16 = SPINEL_PROP_THREAD_EXT__BEGIN + 1,

    ///线程路由器升级阈值
    /** 格式：`C`
     *
     */
    SPINEL_PROP_THREAD_ROUTER_UPGRADE_THRESHOLD = SPINEL_PROP_THREAD_EXT__BEGIN + 2,

    ///线程上下文重用延迟
    /** 格式：`L`
     *
     */
    SPINEL_PROP_THREAD_CONTEXT_REUSE_DELAY = SPINEL_PROP_THREAD_EXT__BEGIN + 3,

    ///线程网络ID超时
    /** 格式：`C`
     *
     */
    SPINEL_PROP_THREAD_NETWORK_ID_TIMEOUT = SPINEL_PROP_THREAD_EXT__BEGIN + 4,

    ///活动线程路由器ID列表
    /** 格式：`A（C）`
     *
     * 注意，某些实现可能不支持CMD_GET_VALUE路由器ID，但当节点是领导者时，可能支持CMD_REMOVE_VALUE。
     *
     */
    SPINEL_PROP_THREAD_ACTIVE_ROUTER_IDS = SPINEL_PROP_THREAD_EXT__BEGIN + 5,

    ///将使用RLOC16地址的IPv6数据包转发到主机。
    /** 格式：`b`
     *
     * 允许主机直接观察NCP接收的所有IPv6数据包，包括发送到RLOC16地址的数据包。
     *
     * 默认值为false。
     *
     */
    SPINEL_PROP_THREAD_RLOC16_DEBUG_PASSTHRU = SPINEL_PROP_THREAD_EXT__BEGIN + 6,

    ///路由器角色已启用
    /** 格式`b`
     *
     * 允许主机指示是否启用路由器角色。如果当前角色是路由器，则将此属性设置为“false”将启动作为终端设备的重新连接过程。
     *
     */
    SPINEL_PROP_THREAD_ROUTER_ROLE_ENABLED = SPINEL_PROP_THREAD_EXT__BEGIN + 7,

    ///线程路由器降级阈值
    /** 格式：`C`
     *
     */
    SPINEL_PROP_THREAD_ROUTER_DOWNGRADE_THRESHOLD = SPINEL_PROP_THREAD_EXT__BEGIN + 8,

    ///线程路由器选择抖动
    /** 格式：`C`
     *
     */
    SPINEL_PROP_THREAD_ROUTER_SELECTION_JITTER = SPINEL_PROP_THREAD_EXT__BEGIN + 9,

    ///线程首选路由器Id
    /** 格式：`C`-仅写
     *
     * 指定首选路由器Id。成为路由器/领导者后，节点将尝试使用此路由器Id。如果未设置首选路由器Id或无法使用，则选择随机生成的路由器Id。只有在分离或禁用设备角色时，才能设置此属性。
     *
     */
    SPINEL_PROP_THREAD_PREFERRED_ROUTER_ID = SPINEL_PROP_THREAD_EXT__BEGIN + 10,

    ///线程邻居表
    /** 格式：`A（t（ESLCcCbLLc））`-只读
     *
     * 每个项目的数据为：
     *
     *  `E`：扩展地址`S`：RLOC16`L`：年龄（以秒为单位）`C`：链接质量在`C`：平均RSS（以dBm为单位）` C`：模式（位标志）`b`：如果邻居是孩子，则为`true`，否则为`false``L`：链路帧计数器`L`：MLE帧计数器`c`：最后一个RSSI（单位dBm）
     *
     */
    SPINEL_PROP_THREAD_NEIGHBOR_TABLE = SPINEL_PROP_THREAD_EXT__BEGIN + 11,

    ///线程最大子计数
    /** 格式：`C`
     *
     * 指定当前允许的最大子级数。仅当线程协议操作停止时，才能设置此参数。
     *
     */
    SPINEL_PROP_THREAD_CHILD_COUNT_MAX = SPINEL_PROP_THREAD_EXT__BEGIN + 12,

    ///领导者网络数据
    /** 格式：`D`-只读
     *
     */
    SPINEL_PROP_THREAD_LEADER_NETWORK_DATA = SPINEL_PROP_THREAD_EXT__BEGIN + 13,

    ///稳定的领导者网络数据
    /** 格式：`D`-只读
     *
     */
    SPINEL_PROP_THREAD_STABLE_LEADER_NETWORK_DATA = SPINEL_PROP_THREAD_EXT__BEGIN + 14,

    ///线程连接程序数据
    /** 格式`A（T（ULE））`PSKd，joiner超时，eui64（可选）
     *
     * SPINEL_PROP_MESHCOP_CONDER_JOINERS正在弃用此属性。
     *
     */
    SPINEL_PROP_THREAD_JOINERS = SPINEL_PROP_THREAD_EXT__BEGIN + 15,

    ///线程专员启用
    /** 格式`b`
     *
     * 默认值为“false”。
     *
     * SPINEL_PROP_MESHCOP_CONDER_STATE不推荐使用此属性。
     *
     */
    SPINEL_PROP_THREAD_COMMISSIONER_ENABLED = SPINEL_PROP_THREAD_EXT__BEGIN + 16,

    ///线程TMF代理启用
    /** 格式`b`所需功能：`SPINEL_CAP_THREAD_TMF_PROXY`
     *
     * 此属性已弃用。
     *
     */
    SPINEL_PROP_THREAD_TMF_PROXY_ENABLED = SPINEL_PROP_THREAD_EXT__BEGIN + 17,

    ///线程TMF代理流
    /** 格式`dSS`所需功能：`SPINEL_CAP_THREAD_TMF_PROXY`
     *
     * 此属性已弃用。请参阅“SPINEL_PROP_THREAD_UDP_FORWARD_STREAM”。
     *
     */
    SPINEL_PROP_THREAD_TMF_PROXY_STREAM = SPINEL_PROP_THREAD_EXT__BEGIN + 18,

    ///发现扫描操作期间使用的线程“joiner”标志
    /** 格式`b`
     *
     * 此属性定义发现请求TLV中的Joiner Flag值。
     *
     * 默认值为“false”。
     *
     */
    SPINEL_PROP_THREAD_DISCOVERY_SCAN_JOINER_FLAG = SPINEL_PROP_THREAD_EXT__BEGIN + 19,

    ///为发现扫描操作启用EUI64筛选。
    /** 格式`b`
     *
     * 默认值为`false`
     *
     */
    SPINEL_PROP_THREAD_DISCOVERY_SCAN_ENABLE_FILTERING = SPINEL_PROP_THREAD_EXT__BEGIN + 20,

    ///用于发现扫描操作的PANID（用于PANID筛选）。
    /** 格式：`S`
     *
     * 默认值为0xffff（广播PAN）以禁用PANID过滤
     *
     */
    SPINEL_PROP_THREAD_DISCOVERY_SCAN_PANID = SPINEL_PROP_THREAD_EXT__BEGIN + 21,

    ///MLE发现响应的线程（带外）转向数据。
    /** 格式`E`-仅写
     *
     * 所需功能：SPINEL_CAP_OOB_STEERING_DATA。
     *
     * 写入此属性允许设置/更新带外MLE发现响应引导数据。
     *
     *  -全部为零以清除转向数据（表示没有转向数据）。
     *  -所有0xFF将转向数据/布隆过滤器设置为接受/允许所有。
     *  -然后将特定的EUI64添加到当前转向数据/布隆滤波器。
     *
     */
    SPINEL_PROP_THREAD_STEERING_DATA = SPINEL_PROP_THREAD_EXT__BEGIN + 22,

    ///线程路由器表。
    /** 格式：`A（t（ESCCCCCCb）`-只读
     *
     * 每个项目的数据为：
     *
     *  `E`：IEEE 802.15.4扩展地址`S`：RLOC16`C`：路由器ID `C`；到路由器`C`的下一跳：到路由器`C `的路径成本：链路质量输入`C `：链路质量输出`C `；年龄（自上次听到后的秒数）`b`：是否使用路由器ID建立链路。
     *
     */
    SPINEL_PROP_THREAD_ROUTER_TABLE = SPINEL_PROP_THREAD_EXT__BEGIN + 23,

    ///线程活动操作数据集
    /** 格式：`A（t（iD））`-读写
     *
     * 此属性提供对当前线程活动操作数据集的访问。线程设备维护它在本地存储的操作数据集，以及它所连接的分区当前正在使用的数据集。此属性对应于设备上本地存储的数据集。
     *
     * 操作数据集由一组受支持的属性（例如，频道、网络密钥、网络名称、PAN id等）组成。请注意，并非所有受支持的属性都存在于数据集中（具有值）。
     *
     * “数据集”值被编码为一个结构数组，其中包含属性键对（如“i”）和属性值（如“D”）。属性值必须遵循与相应属性关联的格式。
     *
     * 写入时，必须忽略任何未知/不受支持的属性键。
     *
     * 数据集列表中可以包含以下属性：
     *
     *   SPINEL_PROP_DATASET_ACTIVE_TIMESTAMP SPINEL_PRODUCT_PHY_CHAN SPINEL_PROCP_PHY_CHAN_SUPPORTED（频道掩码页0）SPINEL__PROP_NET_NETWORK_KEY SPINEL_P_NET_NET WORK_NAME SPINEL_PRO NET_XPANID SPINEL-PROP_MAC_15_4_PANID
     *
     */
    SPINEL_PROP_THREAD_ACTIVE_DATASET = SPINEL_PROP_THREAD_EXT__BEGIN + 24,

    ///线程挂起操作数据集
    /** 格式：`A（t（iD））`-读写
     *
     * 此属性提供对当前本地存储的挂起操作数据集的访问。
     *
     * 此属性的格式遵循与SPINEL_PROP_THREAD_ACTIVE_DATASET中相同的规则。
     *
     * 除了SPINEL_PROP_THREAD_ACTIVE_DATASET中支持的属性外，挂起数据集中还可以包含以下属性：
     *
     *   SPINEL_PROP_DATASET_PENDING_TIMESTAMP SPINEL_PROP_DATASET_DELAY_TIMER
     *
     */
    SPINEL_PROP_THREAD_PENDING_DATASET = SPINEL_PROP_THREAD_EXT__BEGIN + 25,

    ///发送MGMT_SET线程活动操作数据集
    /** 格式：`A（t（iD））`-仅写
     *
     * 此属性的格式遵循与SPINEL_PROP_THREAD_ACTIVE_DATASET中相同的规则。
     *
     * 这是只读属性。写入时，它会触发一个MGMT_ACTIVE_SET meshcop命令，将其发送给具有给定数据集的领导者。尖晶石帧响应应为具有MGMT_ACTIVE_SET命令传输状态的“LAST_STATUS”。
     *
     * 除了SPINEL_PROP_THREAD_ACTIVE_DATASET中支持的属性外，数据集中还可以包含以下属性（以允许自定义原始TLV）：
     *
     *    SPINEL_PROP_DATASET_RAW_TLVS
     *
     */
    SPINEL_PROP_THREAD_MGMT_SET_ACTIVE_DATASET = SPINEL_PROP_THREAD_EXT__BEGIN + 26,

    ///发送MGMT_SET线程挂起操作数据集
    /** 格式：`A（t（iD））`-仅写
     *
     * 此属性类似于SPINEL_PROP_THREAD_PENDING_DATASET，遵循相同的格式和规则。
     *
     * 除了SPINEL_PROP_THREAD_PENDING_DATASET中支持的属性外，数据集中还可以包含以下属性（以允许提供自定义原始TLV）。
     *
     *    SPINEL_PROP_DATASET_RAW_TLVS
     *
     */
    SPINEL_PROP_THREAD_MGMT_SET_PENDING_DATASET = SPINEL_PROP_THREAD_EXT__BEGIN + 27,

    ///操作数据集活动时间戳
    /** 格式：`X`-无直接读取或写入
     *
     * 它只能包含在以下与数据集相关的属性之一中：
     *
     *   SPINEL_PROP_THREAD_ACTIVE_DATASET SPINEL_PROP_THREAD_PENDING_DATASET SPINEL_PROP_THREAD_MGMT_SET_ACTIVE_DATASET SPINEL_PROP_THREAD_MGMT_SET_PENDING_DATASET SPINEL_PROP_THREAD_MGMT_GET_ACTIVE_DATASET SPINEL_PROP_THREAD_MGMT_GET_PENDING_DATASET
     *
     */
    SPINEL_PROP_DATASET_ACTIVE_TIMESTAMP = SPINEL_PROP_THREAD_EXT__BEGIN + 28,

    ///操作数据集挂起时间戳
    /** 格式：`X`-无直接读取或写入
     *
     * 它只能包含在“挂起数据集”属性之一中：
     *
     *   SPINEL_PROP_THREAD_PENDING_DATASET SPINEL_PROP_THREAD_MGMT_SET_PENDING_DATASET SPINEL_PROP_THREAD_MGMT_GET_PENDING_DATASET
     *
     */
    SPINEL_PROP_DATASET_PENDING_TIMESTAMP = SPINEL_PROP_THREAD_EXT__BEGIN + 29,

    ///操作数据集延迟计时器
    /** 格式：`L`-无直接读取或写入
     *
     * 延迟计时器（以毫秒为单位）指定时间重命名，直到线程设备用挂起操作数据集中的相应值覆盖活动操作数据集中的值。
     *
     * 它只能包含在“挂起数据集”属性之一中：
     *
     *   SPINEL_PROP_THREAD_PENDING_DATASET SPINEL_PROP_THREAD_MGMT_SET_PENDING_DATASET SPINEL_PROP_THREAD_MGMT_GET_PENDING_DATASET
     *
     */
    SPINEL_PROP_DATASET_DELAY_TIMER = SPINEL_PROP_THREAD_EXT__BEGIN + 30,

    ///操作数据集安全策略
    /** 格式：“SD”-无直接读取或写入
     *
     * 它只能包含在以下与数据集相关的属性之一中：
     *
     *   SPINEL_PROP_THREAD_ACTIVE_DATASET SPINEL_PROP_THREAD_PENDING_DATASET SPINEL_PROP_THREAD_MGMT_SET_ACTIVE_DATASET SPINEL_PROP_THREAD_MGMT_SET_PENDING_DATASET SPINEL_PROP_THREAD_MGMT_GET_ACTIVE_DATASET SPINEL_PROP_THREAD_MGMT_GET_PENDING_DATASET
     *
     * 内容为“S”：密钥轮换时间（以小时为单位）“C”：安全策略标志（如线程1.1第8.10.1.15节所规定）“C’：可选安全策略标志扩展（如线程1.2第8.10.1.16节所规定的）。如果缺少此字段，则使用0xf8。
     *
     */
    SPINEL_PROP_DATASET_SECURITY_POLICY = SPINEL_PROP_THREAD_EXT__BEGIN + 31,

    ///操作数据集其他原始TLV
    /** 格式：`D`-无直接读取或写入
     *
     * 此属性定义可以添加到操作数据集的额外原始TLV。
     *
     * 它只能包含在以下数据集属性之一中：
     *
     *   SPINEL_PROP_THREAD_MGMT_SET_ACTIVE_DATASET SPINEL_PROP_THREAD_MGMT_SET_PENDING_DATASET SPINEL_PROP_THREAD_MGMT_GET_ACTIVE_DATASET SPINEL_PROP_THREAD_MGMT_GET_PENDING_DATASET
     *
     */
    SPINEL_PROP_DATASET_RAW_TLVS = SPINEL_PROP_THREAD_EXT__BEGIN + 32,

    ///子表地址
    /** 格式：`A（t（ESA（6）））`-只读
     *
     * 此属性提供与每个子级关联的所有地址的列表，包括任何已注册的IPv6地址。
     *
     * 每个项目的数据为：
     *
     *  `E`：子“S”的扩展地址：子“A（6）”的RLOC16：子注册的IPv6地址列表（如果有）
     *
     */
    SPINEL_PROP_THREAD_CHILD_TABLE_ADDRESSES = SPINEL_PROP_THREAD_EXT__BEGIN + 33,

    ///邻居表帧和消息错误率
    /** 格式：`A（t（ESSScc））`所需功能：`CAP_ERROR_RATE_TRACKING`
     *
     * 此属性提供链路质量相关信息，包括所有邻居的帧和（IPv6）消息错误率。
     *
     * 关于消息错误率，请注意，较大的（IPv6）消息可以被分段并作为多个MAC帧发送。如果在所有MAC重试尝试之后，消息的任何片段都失败，则消息传输被视为失败。
     *
     * 每个项目的数据为：
     *
     *  `E`：邻居的扩展地址“S”：邻居“S”的RLOC16：帧错误率（0->0%，0xffff->100%）“S”；消息错误率（0->0%，0xff->100%）`c`：平均RSSI（以dBm为单位）`c'：最后RSSI（单位dBm）
     *
     */
    SPINEL_PROP_THREAD_NEIGHBOR_TABLE_ERROR_RATES = SPINEL_PROP_THREAD_EXT__BEGIN + 34,

    ///EID（端点标识符）IPv6地址缓存表
    /** 格式`A（t（6SCCt（bL6）t（bSS））
     *
     * 此属性提供线程EID地址缓存表。
     *
     * 每个项目的数据为：
     *
     *  `6`：目标IPv6地址`S`：目标`C`的RLOC16：年龄（使用顺序，0表示最近使用的条目）`C`：条目状态（值由枚举`SPINEL_ADDRES_CACHE_entry_state_`定义）。
     *
     *  `t`：状态为`SPINEL_ADDRESS_CACHE_ENTRY_state_CACHED``b`时的信息：指示最后一次事务时间和ML-EID是否有效`L`：上次事务时间`6`：网格本地EID
     *
     *  `t`：状态不是`SPINEL_ADDRESS_CACHE_ENTRY_state_CACHED`b`时的信息：指示是否可以收回条目`S`：超时（秒）`S`：重试延迟（适用于查询重试状态）。
     *
     */
    SPINEL_PROP_THREAD_ADDRESS_CACHE_TABLE = SPINEL_PROP_THREAD_EXT__BEGIN + 35,

    ///线程UDP转发流
    /** 格式`dS6S`所需功能：`SPINEL_CAP_THREAD_UDP_FORWARD`
     *
     * 此属性有助于与主机交换UDP数据包。
     *
     *  `d`：UDP负载`S`：远程UDP端口`6`：远程IPv6地址`S`：本地UDP端口
     *
     */
    SPINEL_PROP_THREAD_UDP_FORWARD_STREAM = SPINEL_PROP_THREAD_EXT__BEGIN + 36,

    ///发送MGMT_GET线程活动操作数据集
    /** 格式：`A（t（iD））`-仅写
     *
     * 此属性的格式遵循与SPINEL_PROP_THREAD_MGMT_SET_ACTIVE_DATASET中相同的规则。此属性还允许发送方在格式化“t（iD）”时不包含与属性相关联的值，即，它应接受“t（iD）”或“t（i）”编码（在这两种情况下，都表示关联的数据集属性应作为MGMT_GET命令的一部分请求）。
     *
     * 这是只读属性。写入时，它会触发一个MGMT_ACTIVE_GET meshcop命令，发送给leader，请求格式中与数据集相关的属性。尖晶石帧响应应为具有MGMT_ACTIVE_GET命令传输状态的“LAST_STATUS”。
     *
     * 除了SPINEL_PROP_THREAD_MGMT_SET_ACTIVE_DATASET中支持的属性外，数据集中还可以选择包含以下属性：
     *
     *    SPINEL_PROP_DATASET_DEST_ADDRESS
     *
     */
    SPINEL_PROP_THREAD_MGMT_GET_ACTIVE_DATASET = SPINEL_PROP_THREAD_EXT__BEGIN + 37,

    ///发送MGMT_GET线程挂起操作数据集
    /** 格式：`A（t（iD））`-仅写
     *
     * 此属性的格式遵循与SPINEL_PROP_THREAD_MGMT_GET_ACTIVE_DATASET中相同的规则。
     *
     * 这是只读属性。写入时，它会触发一个MGMT_PENDING_GET meshcop命令，将其发送给具有给定数据集的领导者。尖晶石帧响应应为具有MGMT_PENDING_GET命令传输状态的“LAST_STATUS”。
     *
     */
    SPINEL_PROP_THREAD_MGMT_GET_PENDING_DATASET = SPINEL_PROP_THREAD_EXT__BEGIN + 38,

    ///操作数据集（MGMT_GET）目标IPv6地址
    /** 格式：`6`-无直接读取或写入
     *
     * 此属性指定为“活动数据集”或“挂起数据集”发送MGMT_GET命令时的IPv6目标。如果未提供，则默认使用Leader ALOC地址。
     *
     * 它只能包含在MGMT_GET数据集属性之一中：
     *
     *   SPINEL_PROP_THREAD_MGMT_GET_ACTIVE_DATASET SPINEL_PROP_THREAD_MGMT_GET_PENDING_DATASET
     *
     */
    SPINEL_PROP_DATASET_DEST_ADDRESS = SPINEL_PROP_THREAD_EXT__BEGIN + 39,

    ///线程新操作数据集
    /** 格式：`A（t（iD））`-只读-仅FTD版本
     *
     * 此属性允许主机请求NCP创建并返回一个新的操作数据集，以便在形成新网络时使用。
     *
     * 操作数据集由一组受支持的属性（例如，频道、网络密钥、网络名称、PAN id等）组成。请注意，并非所有受支持的属性都存在于数据集中（具有值）。
     *
     * “数据集”值被编码为一个结构数组，其中包含属性键对（如“i”）和属性值（如“D”）。属性值必须遵循与相应属性关联的格式。
     *
     * 数据集列表中可以包含以下属性：
     *
     *   SPINEL_PROP_DATASET_ACTIVE_TIMESTAMP SPINEL_PRODUCT_PHY_CHAN SPINEL_PROCP_PHY_CHAN_SUPPORTED（频道掩码页0）SPINEL__PROP_NET_NETWORK_KEY SPINEL_P_NET_NET WORK_NAME SPINEL_PRO NET_XPANID SPINEL-PROP_MAC_15_4_PANID
     *
     */
    SPINEL_PROP_THREAD_NEW_DATASET = SPINEL_PROP_THREAD_EXT__BEGIN + 40,

    ///MAC CSL周期
    /** 格式：`S`所需功能：`SPINEL_CAP_THREAD_CSL_REVICER`
     *
     * 以10个符号为单位的CSL周期。值0表示应禁用CSL。
     */
    SPINEL_PROP_THREAD_CSL_PERIOD = SPINEL_PROP_THREAD_EXT__BEGIN + 41,

    ///MAC CSL超时
    /** 格式：`L`所需功能：`SPINEL_CAP_THREAD_CSL_REVICER`
     *
     * CSL超时（秒）。
     */
    SPINEL_PROP_THREAD_CSL_TIMEOUT = SPINEL_PROP_THREAD_EXT__BEGIN + 42,

    ///MAC CSL信道
    /** 格式：`C`所需功能：`SPINEL_CAP_THREAD_CSL_REVICER`
     *
     * 线程v12.0规范第4.6.5.1.2章中所述的CSL通道。值0表示CSL接收（如果启用）发生在线程网络信道上。范围[11，26]中的值是发生CSL接收的备选信道。
     */
    SPINEL_PROP_THREAD_CSL_CHANNEL = SPINEL_PROP_THREAD_EXT__BEGIN + 43,

    ///线程域名
    /** 格式`U`-读写所需功能：`SPINEL_CAP_NET_THREAD_1_2`
     *
     * 此属性从线程1.2.0开始可用。只有在禁用线程协议时，写入此属性才会成功。
     *
     */
    SPINEL_PROP_THREAD_DOMAIN_NAME = SPINEL_PROP_THREAD_EXT__BEGIN + 44,

    ///链接度量查询
    /** 格式：`6CC`-仅写
     *
     * 所需功能：`SPINEL_CAP_THREAD_LINK_METRICS`
     *
     * `6`：IPv6目标地址`C`：系列id（0表示单探测）`C`；请求的度量id列表，编码为单字节的位字段
     *
     *   +---------------+----+|度量|Id |+---------------+-----+|接收的PDU |0||LQI|1||链接边距|2||RSSI|3|+---------------+----+
     *
     * 如果查询成功，NCP将使用
     * @ref SPINEL_PROP_THREAD_LINK_METRICS_QUERY_RESULT.
     *
     */
    SPINEL_PROP_THREAD_LINK_METRICS_QUERY = SPINEL_PROP_THREAD_EXT__BEGIN + 45,

    ///链接度量查询结果
    /** 格式：`6Ct（A（t（CD）））`-仅限未经请求的通知
     *
     * 所需功能：`SPINEL_CAP_THREAD_LINK_METRICS`
     *
     * `6`：IPv6目标地址`C`：状态`t（A（t（CD）））`：结构数组，编码如下：`C'：度量id `D`：度量值
     *
     *   +---------------+----+----------------+|度量|Id |值格式|+----------------+----------------+|接收的PDU |0|`L`（uint32_t）||LQI|1|`C`（uit8_t）| |链接边距|2|`C'（uint8_t+---------------+----+----------------+
     *
     */
    SPINEL_PROP_THREAD_LINK_METRICS_QUERY_RESULT = SPINEL_PROP_THREAD_EXT__BEGIN + 46,

    ///链接度量探测
    /** 格式“6CC”-仅写所需功能：`SPINEL_CAP_THREAD_LINK_METRICS`
     *
     * 向对等端发送MLE链路探测消息。
     *
     * `6`：IPv6目标地址`C`：此探测消息所针对的系列ID `C'：探测消息的长度，有效范围：[0，64]
     *
     */
    SPINEL_PROP_THREAD_LINK_METRICS_PROBE = SPINEL_PROP_THREAD_EXT__BEGIN + 47,

    ///链路度量增强的基于ACK的探测管理
    /** 格式：6Cd-仅写
     *
     * 所需功能：`SPINEL_CAP_THREAD_LINK_METRICS`
     *
     * `6`：IPv6目标地址`C`：指示是注册还是清除探测`0`-clear，`1'-寄存器`C`：以单字节为单位编码为位字段的请求度量ID列表
     *
     *   +---------------+----+|度量|Id |+---------------+-----+|LQI|1||链接边距|2||RSSI|3|+---------------+----+
     *
     * 使用
     * @ref SPINEL_PROP_THREAD_LINK_METRICS_MGMT_RESPONSE.
     *
     * 每当收到Enh ACK IE报告时，都会使用
     * @ref SPINEL_PROP_THREAD_LINK_METRICS_GMT_ENH_ACK_IE属性。
     *
     */
    SPINEL_PROP_THREAD_LINK_METRICS_MGMT_ENH_ACK = SPINEL_PROP_THREAD_EXT__BEGIN + 48,

    ///链接度量增强的基于ACK的探测IE报告
    /** 格式：SEA（t（CD））-仅限未经请求的通知
     *
     * 所需功能：`SPINEL_CAP_THREAD_LINK_METRICS`
     *
     * `S`：探测主题的短地址`E`：探测主体的扩展地址`t（A（t（CD）））`：包含结构数组的结构，编码如下：`C`：度量id `D`：度量值
     *
     *   +---------------+----+----------------+|度量|Id |值格式|+------------+---------------+---------------+|LQI|1|`C`（uint8_t）||链接边距|2|`C'（uint9_t）| |RSSI|3|`C`（int8_t+---------------+----+----------------+
     *
     */
    SPINEL_PROP_THREAD_LINK_METRICS_MGMT_ENH_ACK_IE = SPINEL_PROP_THREAD_EXT__BEGIN + 49,

    ///链接度量正向跟踪系列管理
    /** 格式：6CCC-仅写
     *
     * 所需功能：`SPINEL_CAP_THREAD_LINK_METRICS`
     *
     * `6`：IPv6目标地址`C`：序列id `C`；跟踪帧类型，编码为单字节中的位字段，如果等于零，则停止计费并删除序列`C'：请求的度量id，编码为单个字节中的比特字段
     *
     *   +------------------+----+|帧类型|Id|+-------------------+----+|MLE链路探测|0||MAC数据|1||MAC请求|2||MAC ACK|3|+------------------+----+
     *
     *   +---------------+----+|度量|Id |+---------------+-----+|接收的PDU |0||LQI|1||链接边距|2||RSSI|3|+---------------+----+
     *
     * 使用
     * @ref SPINEL_PROP_THREAD_LINK_METRICS_MGMT_RESPONSE.
     *
     */
    SPINEL_PROP_THREAD_LINK_METRICS_MGMT_FORWARD = SPINEL_PROP_THREAD_EXT__BEGIN + 50,

    ///链接度量管理响应
    /** 格式：6C-仅限未经请求的通知
     *
     * 所需功能：`SPINEL_CAP_THREAD_LINK_METRICS`
     *
     * `6`：IPv6源地址`C`：已接收状态
     *
     */
    SPINEL_PROP_THREAD_LINK_METRICS_MGMT_RESPONSE = SPINEL_PROP_THREAD_EXT__BEGIN + 51,

    ///多播侦听器注册请求
    /** 格式`t（A（6））A（t（CD））`-仅写所需功能：`SPINEL_CAP_NET_THREAD_1_2`
     *
     * `t（A（6））`：IPv6多播地址数组`A（t（CD））`；包含可选参数的结构数组，如下`C`：参数id `D`：参数值
     *
     *   +----------------------------------------------------------------+|Id:SPINEL_THREAD_MLR_PARAMID_TIMEOUT ||类型：`L`||描述：超时（秒）。如果忽略此可选参数，则将使用BBR的默认值。||特殊值：||0导致给定地址被删除||0xFFFFFFFF是永久和持久注册|+----------------------------------------------------------------+
     *
     * 写入此属性将启动主BBR上多播侦听器表的更新。如果写入成功，稍后将通过SPINEL_PROP_THREAD_MLR_RESPONSE属性通知网络操作的结果。如果写入失败，则无MLR。req，并且不会发生通过SPINEL_PROP_THREAD_MLR_RESPONSE属性的通知动作。
     *
     */
    SPINEL_PROP_THREAD_MLR_REQUEST = SPINEL_PROP_THREAD_EXT__BEGIN + 52,

    ///多播侦听器注册响应
    /** 格式`CCt（A（6））`-仅限未经请求的通知所需功能：`SPINEL_CAP_NET_THREAD_1_2`
     *
     * `C`：状态`C`：MlrStatus（多播侦听器注册状态）`A（6）`：无法在主BBR上更新的IPv6地址阵列
     *
     * 当NCP接收到MLR时，该属性被异步通知。rsp之前对SPINEL_PROP_THREAD_MLR_REQUEST属性的写入。
     */
    SPINEL_PROP_THREAD_MLR_RESPONSE = SPINEL_PROP_THREAD_EXT__BEGIN + 53,

    ///为线程域单播地址指定的接口标识符。
    /** 格式：`A（C）`-读写
     *
     *   `A（C）`：接口标识符（8字节）。
     *
     * 所需功能：SPINEL_CAP_DUA
     *
     * 如果在没有指定参数的情况下写入此属性，将清除线程域单播地址的接口标识符。如果在NCP设备上清除了DUA接口标识符，则将在没有指定参数的情况下成功返回get尖晶石属性命令。
     *
     */
    SPINEL_PROP_THREAD_DUA_ID = SPINEL_PROP_THREAD_EXT__BEGIN + 54,

    ///线程1.2线程网络中的主骨干路由器信息。
    /** 格式：`SSLC`-只读
     *
     * 所需功能：`SPINEL_CAP_NET_THREAD_1_2`
     *
     * `S`：服务器`S`：重新注册延迟（秒）`L`：多播侦听器注册超时（秒）`C`：序列号。
     *
     */
    SPINEL_PROP_THREAD_BACKBONE_ROUTER_PRIMARY = SPINEL_PROP_THREAD_EXT__BEGIN + 55,

    ///线程1.2骨干路由器本地状态。
    /** 格式：`C`-读写
     *
     * 所需功能：`SPINEL_CAP_THREAD_BACKBONE_ROUTER`
     *
     * 有效值由SPINEL_THREAD_BACKBONE_ROUTER_STATE_<STATE>枚举指定。如果将SPINEL_THREAD_Backbone_ROUTER_STATE_disabled写入此属性，则将禁用主干功能，否则启用。
     *
     */
    SPINEL_PROP_THREAD_BACKBONE_ROUTER_LOCAL_STATE = SPINEL_PROP_THREAD_EXT__BEGIN + 56,

    ///本地线程1.2骨干路由器配置。
    /** 格式：SLC-读写
     *
     * 所需功能：`SPINEL_CAP_THREAD_BACKBONE_ROUTER`
     *
     * `S`：重新注册延迟（秒）`L`：多播侦听器注册超时（秒）`C`：序列号。
     *
     */
    SPINEL_PROP_THREAD_BACKBONE_ROUTER_LOCAL_CONFIG = SPINEL_PROP_THREAD_EXT__BEGIN + 57,

    ///注册本地线程1.2骨干路由器配置。
    /** 格式：空（仅写）。
     *
     * 所需功能：`SPINEL_CAP_THREAD_BACKBONE_ROUTER`
     *
     * 写入此属性（使用任何值）将注册本地骨干路由器配置。
     *
     */
    SPINEL_PROP_THREAD_BACKBONE_ROUTER_LOCAL_REGISTER = SPINEL_PROP_THREAD_EXT__BEGIN + 58,

    ///线程1.2骨干路由器注册抖动。
    /** 格式：`C`-读写
     *
     * 所需功能：`SPINEL_CAP_THREAD_BACKBONE_ROUTER`
     *
     * `C`：骨干路由器注册抖动。
     *
     */
    SPINEL_PROP_THREAD_BACKBONE_ROUTER_LOCAL_REGISTRATION_JITTER = SPINEL_PROP_THREAD_EXT__BEGIN + 59,

    SPINEL_PROP_THREAD_EXT__END = 0x1600,

    SPINEL_PROP_IPV6__BEGIN = 0x60,

    ///链接本地IPv6地址
    /** 格式：`6`-只读
     *
     */
    SPINEL_PROP_IPV6_LL_ADDR = SPINEL_PROP_IPV6__BEGIN + 0, ///< [6]

    ///网格本地IPv6地址
    /** 格式：`6`-只读
     *
     */
    SPINEL_PROP_IPV6_ML_ADDR = SPINEL_PROP_IPV6__BEGIN + 1,

    ///网格本地前缀
    /** 格式：`6C`-读写
     *
     * 提供网格本地前缀
     *
     *   `6`：网格本地前缀`C`：前缀长度（线程为64位）。
     *
     */
    SPINEL_PROP_IPV6_ML_PREFIX = SPINEL_PROP_IPV6__BEGIN + 2,

    ///IPv6（单播）地址表
    /** 格式：`A（t（6CLLC））`
     *
     * 此属性提供所有单播地址。
     *
     * 结构阵列包含：
     *
     *  `6`：IPv6地址`C`：网络前缀长度（以位为单位）`L`：有效生存期`L'：首选生存期
     *
     */
    SPINEL_PROP_IPV6_ADDRESS_TABLE = SPINEL_PROP_IPV6__BEGIN + 3,

    ///IPv6路由表-已弃用
    SPINEL_PROP_IPV6_ROUTE_TABLE = SPINEL_PROP_IPV6__BEGIN + 4,

    ///IPv6 ICMP Ping卸载
    /** 格式：`b`
     *
     * 允许NCP直接响应ICMP ping请求。如果启用此选项，ping请求ICMP数据包将不会传递给主机。
     *
     * 默认值为“false”。
     */
    SPINEL_PROP_IPV6_ICMP_PING_OFFLOAD = SPINEL_PROP_IPV6__BEGIN + 5,

    ///IPv6多播地址表
    /** 格式：`A（t（6））`
     *
     * 此属性提供所有多播地址。
     *
     */
    SPINEL_PROP_IPV6_MULTICAST_ADDRESS_TABLE = SPINEL_PROP_IPV6__BEGIN + 6,

    ///IPv6 ICMP Ping卸载
    /** 格式：`C`
     *
     * 允许NCP直接响应ICMP ping请求。如果启用此选项，ping请求ICMP数据包将不会传递给主机。
     *
     * 此属性允许启用仅发送到单播、仅发送到多播或同时发送到两者的响应。有效值由枚举“spinel_ipv6_icmp_ping_offload_mode_t”定义。
     *
     *   SPINEL_IPV6_ICMP_PING_OFFLOAD_DISABLED       = 0 SPINEL_IPV6_ICMP_PING_OFFLOAD_UNICAST_ONLY = 1 SPINEL_IPV6_ICMP_PING_OFFLOAD_MULTICAST_ONLY = 2 SPINEL_IPV6_ICMP_PING_OFFLOAD_ALL = 3
     *
     * 默认值为`NET_IPV6_ICMP_PING_OFFLOAD_DISABLED`。
     *
     */
    SPINEL_PROP_IPV6_ICMP_PING_OFFLOAD_MODE = SPINEL_PROP_IPV6__BEGIN + 7, ///<[b]

    SPINEL_PROP_IPV6__END = 0x70,

    SPINEL_PROP_IPV6_EXT__BEGIN = 0x1600,
    SPINEL_PROP_IPV6_EXT__END   = 0x1700,

    SPINEL_PROP_STREAM__BEGIN = 0x70,

    ///调试流
    /** 格式：`U`（流，只读）
     *
     * 此属性是流属性，这意味着您无法显式获取此属性的值。该流提供可在主机日志中显示的可读调试输出。
     *
     * 换行符的位置不由主机承担：NCP负责在需要的地方插入换行符，就像任何其他文本流一样。
     *
     * 要接收调试流，请等待NCP对该属性的“CMD_PROP_VALUE_IS”命令。
     *
     */
    SPINEL_PROP_STREAM_DEBUG = SPINEL_PROP_STREAM__BEGIN + 0,

    ///原始数据流
    /** 格式：`dD`（流，只读）所需功能：SPINEL_CAPMAC_RAW或SPINEL_CAP _CONFIG_RADIO
     *
     * 该流提供向无线电发送和从无线电接收原始15.4帧的能力。帧元数据和数据的确切格式取决于所使用的MAC和PHY。
     *
     * 此属性是流属性，这意味着您无法显式获取此属性的值。要接收流量，请等待NCP中具有此属性id的“CMD_PROP_VALUE_IS”命令。
     *
     * 此属性的常规格式为：
     *
     *    `d`：帧数据`d`：帧元数据
     *
     * 帧元数据是可选的。帧元数据可能为空或部分指定。必须接受部分指定的元数据。默认值用于所有未指定的字段。
     *
     * 帧元数据字段由以下字段组成：
     *
     *   `c`：接收信号强度（RSSI）（单位：dBm）-默认值为-128`c`：噪声下限（单位：dB）-默认为-128`S`：标志（见下文）`d`：PHY特定的数据/结构`d`：供应商特定的数据或结构
     *
     * 标志字段由以下枚举位字段定义：
     *
     *   SPINEL_MD_FLAG_TX=0x0001：数据包已发送，但未收到。SPINEL_MD_FLAG_BAD_FCS=0x0004:接收到带有错误FCS的数据包SPINEL_DM_FLAG_DUPE=0x008:数据包似乎是重复的SPINEL_MM_FLAG_RESERVED=0xFFF2：保留用于将来使用的标志。
     *
     * 线程设备的PHY特定数据格式包含以下可选字段：

     *   `C`：802.15.4信道（接收信道）`C`：IEEE 802.15.4 LQI `L`：时间戳毫秒`S`：时间时间戳微秒，偏移到毫秒
     *
     * 使用“CMD_PROP_VALUE_SET”写入此流的帧将通过无线电发送。这允许呼叫者直接使用收音机。
     *
     * “CMD_PROP_VALUE_SET”的帧元数据包含以下可选字段。默认值用于所有未指定的字段。
     *
     *  `C`：信道（对于帧tx）`C`：声明CCA失败之前的最大回退尝试次数（如果未指定，则使用线程堆栈默认值）`C'：传输失败后允许的最大重试次数（如果没有指定，则采用线程堆栈默认）`b`：设置为true以启用此数据包的CSMA-CA，否则为false。（默认为true）`b`：设置为true表示它是重传数据包，否则为false。（默认为false）`b`：设置为true表示SubMac应跳过AES处理，否则为false。（默认为false）。
     *
     */
    SPINEL_PROP_STREAM_RAW = SPINEL_PROP_STREAM__BEGIN + 1,

    ///（IPv6）网络流
    /** 格式：`dD`（流，只读）
     *
     * 该流提供了向当前连接的网络发送和从当前连接网络接收（IPv6）数据分组的能力。数据包被安全地发送或接收（加密和认证）。
     *
     * 此属性是流属性，这意味着您无法显式获取此属性的值。要接收流量，请等待NCP中具有此属性id的“CMD_PROP_VALUE_IS”命令。
     *
     * 若要发送网络数据包，请使用数据包的值对此属性调用“CMD_PROP_VALUE_SET”。
     *
     * 此属性的常规格式为：
     *
     *    `d`：分组数据`d`：分组元数据
     *
     * 数据包元数据是可选的。数据包元数据可能为空或部分指定。必须接受部分指定的元数据。默认值用于所有未指定的字段。
     *
     * 对于OpenThread，元数据当前为空。
     *
     */
    SPINEL_PROP_STREAM_NET = SPINEL_PROP_STREAM__BEGIN + 2,

    ///（IPv6）网络流不安全
    /** 格式：`dD`（流，只读）
     *
     * 该流提供了向附近设备发送和从附近设备接收未加密和未经验证的数据包的能力，用于设备调试。
     *
     * 此属性是流属性，这意味着您无法显式获取此属性的值。要接收流量，请等待NCP中具有此属性id的“CMD_PROP_VALUE_IS”命令。
     *
     * 若要发送网络数据包，请使用数据包的值对此属性调用“CMD_PROP_VALUE_SET”。
     *
     * 此属性的常规格式为：
     *
     *    `d`：分组数据`d`：分组元数据
     *
     * 数据包元数据是可选的。数据包元数据可能为空或部分指定。必须接受部分指定的元数据。默认值用于所有未指定的字段。
     *
     * 对于OpenThread，元数据当前为空。
     *
     */
    SPINEL_PROP_STREAM_NET_INSECURE = SPINEL_PROP_STREAM__BEGIN + 3,

    ///日志流
    /** 格式：`UD`（流，只读）
     *
     * 此属性是一个只读流属性，它提供来自NCP的格式化日志字符串。此属性使用新的日志字符串提供异步“CMD_PROP_VALUE_IS”更新，并包括可选的元数据。
     *
     *   `U`：日志字符串`D`：日志元数据（可选）。
     *
     * 日志字符串之后的任何数据都被视为元数据，并且是可选的。“SPINEL_CAP_OPENTHREAD_LOG_METADATA”功能的存在表明OPENTHREAD日志元数据格式的使用如下：
     *
     *    `C`：日志级别（根据枚举`SPINEL_NCP_Log_level_<level>`中的定义）`i`：OpenThread日志区域（根据枚举` SPINEL_NACP_Log_region_<region>中的定义`X`：日志时间戳=<timestamp_base>+<current_time_ms>
     *
     */
    SPINEL_PROP_STREAM_LOG = SPINEL_PROP_STREAM__BEGIN + 4,

    SPINEL_PROP_STREAM__END = 0x80,

    SPINEL_PROP_STREAM_EXT__BEGIN = 0x1700,
    SPINEL_PROP_STREAM_EXT__END   = 0x1800,

    SPINEL_PROP_MESHCOP__BEGIN = 0x80,

    // 线程连接程序状态
    /** 格式`C`-只读
     *
     * 所需功能：SPINEL_CAP_THREAD_JOINER
     *
     * 有效值由`spinel_meshcop_joiner_state_t`（`spinel_meshcop_joiner_state_<state>`）枚举指定。
     *
     */
    SPINEL_PROP_MESHCOP_JOINER_STATE = SPINEL_PROP_MESHCOP__BEGIN + 0, ///<[C]

    ///Thread Joiner调试命令和参数
    /** 格式“b”或“bU（UUUUU）”（括号中的字段是可选的）-仅写
     *
     * 此属性启动或停止Joiner的调试过程
     *
     * 所需功能：SPINEL_CAP_THREAD_JOINER
     *
     * 写入此属性将启动/停止Joiner调试过程。立即的“VALUE_IS”响应表示启动/停止Joiner调试过程的成功/失败。
     *
     * 成功启动操作后，通过异步“VALUE_is（LAST_STATUS）”更新报告连接过程结果，更新时使用以下错误状态值之一：
     *
     *     -SPINEL_STATUS_JOIN_SSUCCESS连接进程成功。
     *     -SPINEL_STATUS_JOIN_SECURITY由于安全凭据，加入进程失败。
     *     -SPINEL_STATUS_JOIN_NO_PEERS未发现可连接网络。
     *     -如果响应超时，则返回SPINEL_STATUS_JOIN_RSP_TIMEOUT。
     *     -SPINEL_STATUS_JOIN_FAILURE联接失败。
     *
     * 帧格式：
     *
     *  `b`：启动或停止调试过程（真启动）。
     *
     * 只有在开始调试时。
     *
     *  `U`：Joiner的PSKd。
     *
     * 接下来的字段都是可选的。如果未提供，将使用OpenThread默认值。
     *
     *  `U`：设置URL（如果不需要，请使用空字符串）`U`：供应商名称。如果未指定或字符串为空，请使用OpenThread默认值（PACKAGE_NAME）`U`：供应商型号。如果未指定或为空字符串，请使用OpenThread默认值（OpenThread_CONFIG_PLATFORM_INFO）`U`：供应商Sw版本。如果未指定或为空字符串，请使用OpenThread默认值（PACKAGE_VERSION）`U`：供应商数据字符串。如果未指定，则不会追加。
     *
     */
    SPINEL_PROP_MESHCOP_JOINER_COMMISSIONING = SPINEL_PROP_MESHCOP__BEGIN + 1,

    // 线程专员状态
    /** 格式`C`
     *
     * 所需能力：SPINEL_CAP_THREAD_CONCTIONER
     *
     * 有效值由SPINEL_MESHCOP_COMMISSIONER_STATE_<STATE>枚举指定。
     *
     */
    SPINEL_PROP_MESHCOP_COMMISSIONER_STATE = SPINEL_PROP_MESHCOP__BEGIN + 2,

    // 线程专员连接程序
    /** 格式`A（t（t（E|CX）UL））`-获取、插入或删除。
     *
     * 所需能力：SPINEL_CAP_THREAD_CONCTIONER
     *
     * 每个阵列条目的数据为：
     *
     *  `t（）`|`t（E）`|` t（CX）`：联接信息结构（格式不同）。
     *
     *   -“t（）”或空结构表示任何joiner。
     *   -“t（E）”指定Joiner EUI-64。
     *   -`t（CX）指定Joiner Discerner，`C`是Discerner长度（以位为单位），`X`是Discrner值。
     *
     * 结构后面跟着：
     *
     *  `L`：删除Joiner的超时（写入时应以秒为单位，读取时以毫秒为单位）`U`：PSKd
     *
     * 对于CMD_PROP_VALUE_REMOVE，超时和PSKd是可选的。
     *
     */
    SPINEL_PROP_MESHCOP_COMMISSIONER_JOINERS = SPINEL_PROP_MESHCOP__BEGIN + 3,

    // 线程专员设置URL
    /** 格式`U`
     *
     * 所需能力：SPINEL_CAP_THREAD_CONCTIONER
     *
     */
    SPINEL_PROP_MESHCOP_COMMISSIONER_PROVISIONING_URL = SPINEL_PROP_MESHCOP__BEGIN + 4,

    // 线程专员会话ID
    /** 格式`S-只读
     *
     * 所需能力：SPINEL_CAP_THREAD_CONCTIONER
     *
     */
    SPINEL_PROP_MESHCOP_COMMISSIONER_SESSION_ID = SPINEL_PROP_MESHCOP__BEGIN + 5,

    ///螺纹连接器识别器
    /** 格式`CX`-读写
     *
     * 所需功能：SPINEL_CAP_THREAD_JOINER
     *
     * 此属性表示Joiner Discerner。
     *
     * Joiner Discerner用于计算调试/连接过程中使用的Joiner ID。
     *
     * 默认情况下（当未提供或清除识别器时），Joiner ID作为通过工厂分配的IEEE EUI-64计算SHA-256的结果的前64位导出。请注意，这是线程规范预期的主要行为。
     *
     * 格式：
     *
     *   “C”：Joiner Discerner位长度（位数）`X`：Joiner Discerner值（64位无符号）-仅在长度非零时出现/适用。
     *
     * 写入此属性时，可以将长度设置为零，以清除之前设置的任何Joiner Discerner值。
     *
     * 读取此属性时，如果当前没有设置Joiner Discerner，则返回零作为长度（没有值字段）。
     *
     */
    SPINEL_PROP_MESHCOP_JOINER_DISCERNER = SPINEL_PROP_MESHCOP__BEGIN + 6,

    SPINEL_PROP_MESHCOP__END = 0x90,

    SPINEL_PROP_MESHCOP_EXT__BEGIN = 0x1800,

    // 线程专员宣布开始
    /** 格式`LCS6`-仅写
     *
     * 所需能力：SPINEL_CAP_THREAD_CONCTIONER
     *
     * 写入此属性将发送带有指定参数的AnnounceBegin消息。响应是带有操作状态的“LAST_STATUS”更新。
     *
     *   `L`：信道掩码`C`：每个信道的消息数`S`：两个连续MLE通告传输之间的时间（毫秒）`6`：IPv6目标
     *
     */
    SPINEL_PROP_MESHCOP_COMMISSIONER_ANNOUNCE_BEGIN = SPINEL_PROP_MESHCOP_EXT__BEGIN + 0,

    // 线程专员能量扫描查询
    /** 格式`LCS6 `-仅写
     *
     * 所需能力：SPINEL_CAP_THREAD_CONCTIONER
     *
     * 写入此属性将发送带有指定参数的能量扫描查询消息。响应是具有操作状态的“LAST_STATUS”。能量扫描结果通过“SPINEL_PROP_MESHCOP_CONDER_energy_scan_RESULT”更新异步发送。
     *
     * 格式为：
     *
     *   `L`：信道掩码`C`：每个信道的能量测量次数`S`：能量测量之间的时间（毫秒）`S`；每个能量测量的扫描持续时间（毫秒数）`6`：IPv6目标。
     *
     */
    SPINEL_PROP_MESHCOP_COMMISSIONER_ENERGY_SCAN = SPINEL_PROP_MESHCOP_EXT__BEGIN + 1,

    // 线程专员能量扫描结果
    /** 格式`Ld`-仅异步事件
     *
     * 所需能力：SPINEL_CAP_THREAD_CONCTIONER
     *
     * 此属性提供异步“CMD_PROP_VALUE_INSERTED”更新，以报告先前发送的能量扫描查询消息的能量扫描结果（请参阅“SPINEL_PROP_MESHCOP_CONDER_energy_scan'”）。
     *
     * 格式为：
     *
     *   `L`：信道掩码`d`：能量测量数据（注意`d`编码包括长度）
     *
     */
    SPINEL_PROP_MESHCOP_COMMISSIONER_ENERGY_SCAN_RESULT = SPINEL_PROP_MESHCOP_EXT__BEGIN + 2,

    // 线程专员PAN ID查询
    /** 格式`SL6`-仅写
     *
     * 所需能力：SPINEL_CAP_THREAD_CONCTIONER
     *
     * 写入此属性将发送带有指定参数的PAN ID查询消息。响应是具有操作状态的“LAST_STATUS”。PAN ID冲突结果通过“SPINEL_PROP_MESHCOP_CONCOMCER_PAN_ID_Conflict_RESULT”更新异步发出。
     *
     * 格式为：
     *
     *   `S`：要查询的PAN ID `L`：通道掩码`6`：IPv6目标
     *
     */
    SPINEL_PROP_MESHCOP_COMMISSIONER_PAN_ID_QUERY = SPINEL_PROP_MESHCOP_EXT__BEGIN + 3,

    // 线程专员PAN ID冲突结果
    /** 格式“SL”-仅异步事件
     *
     * 所需能力：SPINEL_CAP_THREAD_CONCTIONER
     *
     * 此属性提供异步“CMD_PROP_VALUE_INSERTED”更新，以报告先前发送的PAN ID查询消息的PAN ID冲突结果（请参阅“SPINEL_PROP_MESHCOP_CONCOMPER_PAN_ID_Query”）。
     *
     * 格式为：
     *
     *   `S`：PAN ID `L`：通道掩码
     *
     */
    SPINEL_PROP_MESHCOP_COMMISSIONER_PAN_ID_CONFLICT_RESULT = SPINEL_PROP_MESHCOP_EXT__BEGIN + 4,

    // 线程专员发送MGMT_Commissioner_GET
    /** 格式`d`-仅写
     *
     * 所需能力：SPINEL_CAP_THREAD_CONCTIONER
     *
     * 写入此属性将发送一个带有指定参数的MGMT_CONDER_GET消息。响应是具有操作状态的“LAST_STATUS”。
     *
     * 格式为：
     *
     *   `d`：要获取的TLV类型列表
     *
     */
    SPINEL_PROP_MESHCOP_COMMISSIONER_MGMT_GET = SPINEL_PROP_MESHCOP_EXT__BEGIN + 5,

    // 线程专员发送MGMT_Commissioner_SET
    /** 格式`d`-仅写
     *
     * 所需能力：SPINEL_CAP_THREAD_CONCTIONER
     *
     * 写入此属性将发送一个带有指定参数的MGMT_CONDER_SET消息。响应是具有操作状态的“LAST_STATUS”。
     *
     * 格式为：
     *
     *   `d`：TLV编码数据
     *
     */
    SPINEL_PROP_MESHCOP_COMMISSIONER_MGMT_SET = SPINEL_PROP_MESHCOP_EXT__BEGIN + 6,

    // 线程专员生成PSKc
    /** 格式：`UUd`-仅写
     *
     * 所需能力：SPINEL_CAP_THREAD_CONCTIONER
     *
     * 写入此属性允许用户根据给定的调试密码短语、网络名称和扩展PAN Id生成PSKc。
     *
     * 书面值格式为：
     *
     *   `U`：调试通行短语`U`：网络名称`d`：扩展PAN ID。
     *
     * 成功时的响应将是“VALUE_IS”命令，PSKc格式如下：
     *
     *   `D`：PSKc
     *
     * 出现故障时，将发出“LAST_STATUS”并显示错误状态。
     *
     */
    SPINEL_PROP_MESHCOP_COMMISSIONER_GENERATE_PSKC = SPINEL_PROP_MESHCOP_EXT__BEGIN + 7,

    SPINEL_PROP_MESHCOP_EXT__END = 0x1900,

    SPINEL_PROP_OPENTHREAD__BEGIN = 0x1900,

    ///频道管理器-频道更改新频道
    /** 格式：`C`（读写）
     *
     * 所需功能：SPINEL_CAP_CHANNEL_MANAGER
     *
     * 设置此属性会触发频道管理器启动频道更改过程。网络在指定延迟后切换到给定信道（请参阅“channel_MANAGER_delay”）。
     *
     * 对该属性的后续写入将取消正在进行的（先前请求的）频道更改。
     *
     */
    SPINEL_PROP_CHANNEL_MANAGER_NEW_CHANNEL = SPINEL_PROP_OPENTHREAD__BEGIN + 0,

    ///频道管理器-频道更改延迟
    /** 格式“S”单位：秒
     *
     * 所需功能：SPINEL_CAP_CHANNEL_MANAGER
     *
     * 此属性指定用于频道更改请求的延迟（以秒为单位）。
     *
     * 延迟最好应长于线程网络内所有休眠终端设备使用的最大数据轮询间隔。
     *
     */
    SPINEL_PROP_CHANNEL_MANAGER_DELAY = SPINEL_PROP_OPENTHREAD__BEGIN + 1,

    ///Channel Manager支持的频道
    /** 格式“A（C）”
     *
     * 所需功能：SPINEL_CAP_CHANNEL_MANAGER
     *
     * 此属性指定支持的频道列表。
     *
     */
    SPINEL_PROP_CHANNEL_MANAGER_SUPPORTED_CHANNELS = SPINEL_PROP_OPENTHREAD__BEGIN + 2,

    ///Channel Manager喜爱的频道
    /** 格式“A（C）”
     *
     * 所需功能：SPINEL_CAP_CHANNEL_MANAGER
     *
     * 此属性指定首选频道列表（当要求“ChannelManager'选择频道时）
     *
     */
    SPINEL_PROP_CHANNEL_MANAGER_FAVORED_CHANNELS = SPINEL_PROP_OPENTHREAD__BEGIN + 3,

    ///通道管理器通道选择触发器
    /** 格式“b”
     *
     * 所需功能：SPINEL_CAP_CHANNEL_MANAGER
     *
     * 写入此属性会触发“ChannelManager”上选择新频道的请求。
     *
     * 一旦触发频道选择，频道管理器将执行以下3个步骤：
     *
     * 1） “ChannelManager”决定频道更改是否有用。如果此属性的输入布尔值设置为“true”（跳过质量检查），则可以跳过此检查。该步骤使用设备上收集的链路质量度量，例如CCA故障率、每个邻居的帧和消息错误率等，以确定当前信道质量是否处于证明信道改变合理的水平。
     *
     * 2） 如果第一步通过，则“ChannelManager”选择一个可能更好的频道。它使用“ChannelMonitor”模块收集的信道质量数据。在此步骤中使用受支持和受支持的频道。
     *
     * 3） 如果新选择的频道与当前频道不同，则“ChannelManager”请求/启动频道更改过程。
     *
     * 读取此属性始终会产生“false”。
     *
     */
    SPINEL_PROP_CHANNEL_MANAGER_CHANNEL_SELECT = SPINEL_PROP_OPENTHREAD__BEGIN + 4,

    ///频道管理器自动频道选择已启用
    /** 格式“b”
     *
     * 所需功能：SPINEL_CAP_CHANNEL_MANAGER
     *
     * 此属性指示“ChannelManager”上是否启用/禁用自动频道选择功能。
     *
     * 启用后，“ChannelManager”将定期检查并尝试选择新频道。周期间隔由`SPINEL_PROP_CHANNEL_MANAGER_AUTO_SELECT_interval`指定。
     *
     */
    SPINEL_PROP_CHANNEL_MANAGER_AUTO_SELECT_ENABLED = SPINEL_PROP_OPENTHREAD__BEGIN + 5,

    ///频道管理器自动频道选择间隔
    /** 格式“L”单位：秒
     *
     * 所需功能：SPINEL_CAP_CHANNEL_MANAGER
     *
     * 此属性指定自动频道选择检查间隔（以秒为单位）。
     *
     */
    SPINEL_PROP_CHANNEL_MANAGER_AUTO_SELECT_INTERVAL = SPINEL_PROP_OPENTHREAD__BEGIN + 6,

    ///线程网络时间。
    /** 格式：`Xc`-只读
     *
     * 每个项目的数据为：
     *
     *  `X`：线程网络时间，以微秒为单位`c`：时间同步状态。
     *
     */
    SPINEL_PROP_THREAD_NETWORK_TIME = SPINEL_PROP_OPENTHREAD__BEGIN + 7,

    ///线程时间同步周期
    /** 格式：`S`-读写
     *
     * 每个项目的数据为：
     *
     *  `S`：时间同步周期，以秒为单位。
     *
     */
    SPINEL_PROP_TIME_SYNC_PERIOD = SPINEL_PROP_OPENTHREAD__BEGIN + 8,

    ///路由器的线程时间同步XTAL精度阈值
    /** 格式：`S`-读写
     *
     * 每个项目的数据为：
     *
     *  `S`：路由器的XTAL精度阈值，单位为PPM。
     *
     */
    SPINEL_PROP_TIME_SYNC_XTAL_THRESHOLD = SPINEL_PROP_OPENTHREAD__BEGIN + 9,

    ///儿童监护间隔
    /** 格式：“S”-读写单位：秒
     *
     * 所需功能：`SPINEL_CAP_CHILD_SUPERVISION`
     *
     * 子监控间隔（秒）。零表示禁用儿童监护。
     *
     * 启用后，儿童监督功能可确保在给定的监督间隔内，至少向每一个昏昏欲睡的儿童发送一条消息。如果没有其他消息，则将监督消息（具有空负载的数据消息）排入队列并发送给子级。
     *
     * 此属性仅适用于FTD生成。
     *
     */
    SPINEL_PROP_CHILD_SUPERVISION_INTERVAL = SPINEL_PROP_OPENTHREAD__BEGIN + 10,

    ///儿童监督检查超时
    /** 格式：“S”-读写单位：秒
     *
     * 所需功能：`SPINEL_CAP_CHILD_SUPERVISION`
     *
     * 子监控检查超时间隔（秒）。零表示禁用对孩子的监督检查。
     *
     * 监督检查仅适用于困倦的儿童。启用后，如果子级在指定的检查超时内没有收到父级的消息，则它将通过启动与父级的MLE子级更新请求/响应交换来启动重新连接过程。
     *
     * 此属性可用于FTD和MTD版本。
     *
     */
    SPINEL_PROP_CHILD_SUPERVISION_CHECK_TIMEOUT = SPINEL_PROP_OPENTHREAD__BEGIN + 11,

    // RCP（仅无线电模式下的NCP）版本
    /** 格式`U`-只读
     *
     * 所需功能：SPINEL_CAP_POSIX
     *
     * 此属性提供由POSIX应用程序控制的RCP（无线电模式下的NCP）的版本字符串。它仅在“POSIX”平台中可用（即启用了“OPENTHREAD_platform_POSIX”）。
     *
     */
    SPINEL_PROP_RCP_VERSION = SPINEL_PROP_OPENTHREAD__BEGIN + 12,

    ///线程父响应信息
    /** 格式：`ESccCCCb`-仅异步事件
     *
     *  `E`：扩展地址`S`：RLOC16`c`：即时RSSI`c'：父优先级`c`：链路质量3`c`；链路质量2`c`:链路质量1`b'：是否附加了接收父响应帧的节点
     *
     * 此属性向主机发送父响应帧信息。此属性仅适用于FTD生成。
     *
     */
    SPINEL_PROP_PARENT_RESPONSE_INFO = SPINEL_PROP_OPENTHREAD__BEGIN + 13,

    ///SLAAC已启用
    /** 格式`b`-读写所需功能：`SPINEL_CAP_SLAAC`
     *
     * 此属性允许主机在运行时启用/禁用NCP上的SLAAC模块。启用SLAAC模块后，SLAAC地址（基于网络数据中的网格前缀）将添加到接口。当SLAAC模块被禁用时，之前添加的任何SLAAC地址都将被删除。
     *
     */
    SPINEL_PROP_SLAAC_ENABLED = SPINEL_PROP_OPENTHREAD__BEGIN + 14,

    // 支持的无线电链接（按设备）
    /**
     * 格式`A（i）`-只读
     *
     * 此属性返回设备本身支持的无线电链接列表。枚举“SPINEL_RADIO_LINK_｛TYPE｝”值表示不同的无线电链路类型。
     *
     */
    SPINEL_PROP_SUPPORTED_RADIO_LINKS = SPINEL_PROP_OPENTHREAD__BEGIN + 15,

    ///邻居表多无线电链路信息
    /** 格式：`A（t（ESA（t（iC）））`-只读所需功能：`SPINEL_CAP_MULTI_RADIO`。
     *
     * 每个项表示有关邻居的信息：
     *
     *  `E`：邻居的扩展地址`s`：邻居RLOC16
     *
     *  随后是指示邻居支持哪些无线电链路的无线电链路信息结构的阵列：
     *
     *    `i`：无线电链路类型（枚举`SPINEL_Radio_link_{type}`）`C`：与无线电链路相关的首选项值。
     *
     */
    SPINEL_PROP_NEIGHBOR_TABLE_MULTI_RADIO_INFO = SPINEL_PROP_OPENTHREAD__BEGIN + 16,

    ///SRP客户端启动
    /** 格式：`b（6Sb）`-仅写所需功能：`SPINEL_CAP_SRP_CLIENT`。
     *
     * 写入此属性允许用户启动或停止给定SRP服务器的SRP客户端操作。
     *
     * 书面值格式为：
     *
     *   `b`：TRUE启动客户端，FALSE停止客户端。
     *
     * 用于启动SRP客户端时，还应包括以下字段：
     *
     *   `6`：SRP服务器IPv6地址`U`：SRP服务器端口号`b`：布尔值，指示是否发出SRP客户端事件（使用`SPINEL_PROP_SRP_client_EVENT`）。
     *
     */
    SPINEL_PROP_SRP_CLIENT_START = SPINEL_PROP_OPENTHREAD__BEGIN + 17,

    ///SRP客户端租赁间隔
    /** 格式：`L`-读/写所需功能：`SPINEL_CAP_SRP_CLIENT`。
     *
     * SRP更新请求中使用的租用间隔（秒）。
     *
     */
    SPINEL_PROP_SRP_CLIENT_LEASE_INTERVAL = SPINEL_PROP_OPENTHREAD__BEGIN + 18,

    ///SRP客户端密钥租用间隔
    /** 格式：`L`-读/写所需功能：`SPINEL_CAP_SRP_CLIENT`。
     *
     * SRP更新请求中使用的密钥租用间隔（秒）。
     *
     */
    SPINEL_PROP_SRP_CLIENT_KEY_LEASE_INTERVAL = SPINEL_PROP_OPENTHREAD__BEGIN + 19,

    ///SRP客户端主机信息
    /** 格式：`UCt（A（6））`-只读所需功能：`SPINEL_CAP_SRP_CLIENT`。
     *
     * 格式为：
     *
     *   `U`：主机名`C`：主机状态（来自“spinel_srp_client_item_state_t”的值）`t（A（6））`：包含主机IPv6地址数组的结构。
     *
     */
    SPINEL_PROP_SRP_CLIENT_HOST_INFO = SPINEL_PROP_OPENTHREAD__BEGIN + 20,

    ///SRP客户端主机名（标签）。
    /** 格式：`U`-读/写所需功能：`SPINEL_CAP_SRP_CLIENT`。
     *
     */
    SPINEL_PROP_SRP_CLIENT_HOST_NAME = SPINEL_PROP_OPENTHREAD__BEGIN + 21,

    ///SRP客户端主机地址
    /** 格式：`A（6）`-读/写所需功能：`SPINEL_CAP_SRP_CLIENT`。
     *
     */
    SPINEL_PROP_SRP_CLIENT_HOST_ADDRESSES = SPINEL_PROP_OPENTHREAD__BEGIN + 22,

    ///SRP客户服务
    /** 格式：`A（t（UUSSSd））`-读取/插入/删除所需功能：`SPINEL_CAP_SRP_CLIENT`。
     *
     * 此属性提供服务列表/数组。
     *
     * “SPINEL_CMD_PROP_VALUE_GET”和/或“SPINE_CMD_PROP_VALUE _INSERT”操作的每个项目的数据如下：
     *
     *   `U`：服务名称标签（例如，“_chip.udp”，而不是完整域名。`U`：服务器实例名称标签（而不是完整名称）`S`：服务端口号`S`：服务优先级`S`：服务重量。
     *
     * 对于“SPINEL_CMD_PROP_VALUE_REMOVE”命令，使用以下格式：
     *
     *   `U`：服务名称标签（例如，“_chip.udp”，而不是完整域名。`U`：服务器实例名称标签（而不是完整名称）`b`：指示是否清除服务条目（可选）。
     *
     * 最后一个布尔值（`b`）字段是可选的。当包含时，它在“true”上指示清除服务（立即在客户端上清除服务，而不与服务器交互），在“false”上指示删除服务（通知服务器并等待在服务器上删除服务条目）。如果未包含，则值为“false”。
     *
     */
    SPINEL_PROP_SRP_CLIENT_SERVICES = SPINEL_PROP_OPENTHREAD__BEGIN + 23,

    ///SRP客户端主机和服务删除
    /** 格式：`bb`：仅写所需功能：`SPINEL_CAP_SRP_CLIENT`。
     *
     * 使用写入此属性将启动主机信息和所有服务的删除过程。有关详细信息，请参阅`otSrpClientRemoveHostAndServices（）`。
     *
     * 格式为：
     *
     *    `b`：一个布尔值，指示是否也应清除主机密钥租约`b`：一个布尔值，指示在未注册主机信息时是否向服务器发送更新。
     *
     */
    SPINEL_PROP_SRP_CLIENT_HOST_SERVICES_REMOVE = SPINEL_PROP_OPENTHREAD__BEGIN + 24,

    ///SRP客户端主机和服务清除
    /** 格式：空：仅写所需功能：`SPINEL_CAP_SRP_CLIENT`。
     *
     * 写入此属性将清除所有主机信息和所有服务。有关详细信息，请参阅`otSrpClientClearHostAndServices（）`。
     *
     */
    SPINEL_PROP_SRP_CLIENT_HOST_SERVICES_CLEAR = SPINEL_PROP_OPENTHREAD__BEGIN + 25,

    ///SRP客户端事件
    /** 格式：t（）：仅异步事件所需功能：`SPINEL_CAP_SRP_CLIENT`。
     *
     * 当SRP客户端发生通知某些状态更改或错误的事件时，将异步发出此属性。
     *
     * 此属性的一般格式如下：
     *
     *    `S：错误代码（请参见“spinel_srp_client_Error_t”枚举）`d`：主机信息数据`d`：活动服务`d`：已删除服务。
     *
     * 主机信息数据包含：
     *
     *   `U`：主机名`C`：主机状态（来自“spinel_srp_client_item_state_t”的值）`t（A（6））`：包含主机IPv6地址数组的结构。
     *
     * 活动或删除的服务数据是服务阵列“A（t（UUSSSd））”，每个服务格式为：
     *
     *   `U`：服务名称标签（例如，“_chip.udp”，而不是完整域名。`U`：服务器实例名称标签（而不是完整名称）`S`：服务端口号`S`：服务优先级`S`：服务重量`d`：编码的TXT-DATA。
     *
     */
    SPINEL_PROP_SRP_CLIENT_EVENT = SPINEL_PROP_OPENTHREAD__BEGIN + 26,

    ///SRP客户端服务密钥包含已启用
    /** 格式`b`：读写所需功能：`SPINEL_CAP_SRP_CLIENT`和`SPINE_CAP_REFERENCE_DEVICE`。
     *
     * 此布尔属性指示是否启用“服务密钥记录包含”模式。
     *
     * 启用后，SRP客户端将在其发送的SRP更新消息中的服务描述说明中包含KEY记录。
     *
     * KEY记录在“服务描述说明”中是可选的（它是必需的，并且始终包含在“主机描述说明”内）。SRP客户端的默认行为是不包含它。此函数仅用于覆盖测试的默认行为。
     *
     */
    SPINEL_PROP_SRP_CLIENT_SERVICE_KEY_ENABLED = SPINEL_PROP_OPENTHREAD__BEGIN + 27,

    SPINEL_PROP_OPENTHREAD__END = 0x2000,

    SPINEL_PROP_SERVER__BEGIN = 0xA0,

    ///服务器允许本地网络数据更改
    /** 格式`b`-读写
     *
     * 所需功能：SPINEL_CAP_THREAD_SERVICE
     *
     * 在更改本地服务器网络数据之前设置为true。完成后设置为false。这允许将更改聚合到单个事件中。
     *
     */
    SPINEL_PROP_SERVER_ALLOW_LOCAL_DATA_CHANGE = SPINEL_PROP_SERVER__BEGIN + 0,

    // 服务器服务
    /** 格式：`A（t（LdbdS））`
     *
     * 此属性提供设备上注册的所有服务
     *
     * 所需功能：SPINEL_CAP_THREAD_SERVICE
     *
     * 结构阵列包含：
     *
     *  `L`：企业编号`d`：服务数据`b`：稳定`d`；服务器数据`S`：RLOC
     *
     */
    SPINEL_PROP_SERVER_SERVICES = SPINEL_PROP_SERVER__BEGIN + 1,

    // 服务器领导者服务
    /** 格式：`A（t（CLdbdS））`
     *
     * 此属性提供在leader上注册的所有服务
     *
     * 结构阵列包含：
     *
     *  `C`：服务ID `L`：企业编号`d`：服务数据`b`：稳定`d`；服务器数据`S`：RLOC
     *
     */
    SPINEL_PROP_SERVER_LEADER_SERVICES = SPINEL_PROP_SERVER__BEGIN + 2,

    SPINEL_PROP_SERVER__END = 0xB0,

    SPINEL_PROP_RCP__BEGIN = 0xB0,

    ///RCP API版本号
    /** 格式：`i`（只读）
     *
     * 所需功能：SPINEL_CAP_RADIO和SPINEL_CAP _RCP_API_VERSION。
     *
     * 此属性提供RCP API版本号。
     *
     * 请参阅“脊柱定义兼容性指南”一节。
     *
     */
    SPINEL_PROP_RCP_API_VERSION = SPINEL_PROP_RCP__BEGIN + 0,

    SPINEL_PROP_RCP__END = 0xFF,

    SPINEL_PROP_INTERFACE__BEGIN = 0x100,

    ///UART比特率
    /** 格式：`L`
     *
     *  如果NCP使用UART与主机通信，则此属性允许主机更改串行连接的比特率。值编码为“L”，它是一个小端32位无符号整数。主机不应假定支持所有可能的数值。
     *
     *  如果由NCP实现，该属性应在软件重置期间保持不变，并在硬件重置时被遗忘。
     *
     *  此属性仅在Spinel使用UART时实现。此属性是可选的。
     *
     *  当改变比特率时，将以先前的比特率接收所有帧，直到接收到此命令的响应帧。一旦主机接收到成功的响应帧，将以新的比特率发送所有其他帧。
     */
    SPINEL_PROP_UART_BITRATE = SPINEL_PROP_INTERFACE__BEGIN + 0,

    ///UART软件流控制
    /** 格式：`b`
     *
     *  如果NCP使用UART与主机通信，则此属性允许主机确定是否应使用软件流控制（XON/XOFF样式），以及（可选）打开或关闭它。
     *
     *  此属性仅在Spinel使用UART时实现。此属性是可选的。
     */
    SPINEL_PROP_UART_XON_XOFF = SPINEL_PROP_INTERFACE__BEGIN + 1,

    SPINEL_PROP_INTERFACE__END = 0x200,

    SPINEL_PROP_15_4_PIB__BEGIN = 0x400,
    // 用于直接访问802.15.4 PID。
    // 单个寄存器使用
    // `SPINEL_PROP_15_4_PIB__BEGIN+[PIB_IDENTIFIER]`
    // 仅当设置了SPINEL_CAP_15_4_PIB时才受支持。
    //
    // 为简洁起见，整个802.15.4 PIB空间为
    // 这里没有定义，但有几个选项属性
    // 为了说明和方便而定义。
    SPINEL_PROP_15_4_PIB_PHY_CHANNELS_SUPPORTED = SPINEL_PROP_15_4_PIB__BEGIN + 0x01, ///< [A(L)]
    SPINEL_PROP_15_4_PIB_MAC_PROMISCUOUS_MODE   = SPINEL_PROP_15_4_PIB__BEGIN + 0x51, ///<[b]
    SPINEL_PROP_15_4_PIB_MAC_SECURITY_ENABLED   = SPINEL_PROP_15_4_PIB__BEGIN + 0x5d, ///<[b]
    SPINEL_PROP_15_4_PIB__END                   = 0x500,

    SPINEL_PROP_CNTR__BEGIN = 0x500,

    ///计数器复位
    /** 格式：空（仅写）。
     *
     * 写入此属性（使用任何值）会将所有MAC、MLE、IP和NCP计数器重置为零。
     *
     */
    SPINEL_PROP_CNTR_RESET = SPINEL_PROP_CNTR__BEGIN + 0,

    ///传输的总数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_TX_PKT_TOTAL = SPINEL_PROP_CNTR__BEGIN + 1,

    ///具有ack请求的传输数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_TX_PKT_ACK_REQ = SPINEL_PROP_CNTR__BEGIN + 2,

    ///已确认的传输数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_TX_PKT_ACKED = SPINEL_PROP_CNTR__BEGIN + 3,

    ///无确认请求的传输数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_TX_PKT_NO_ACK_REQ = SPINEL_PROP_CNTR__BEGIN + 4,

    ///传输数据的数量。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_TX_PKT_DATA = SPINEL_PROP_CNTR__BEGIN + 5,

    ///传输的数据轮询数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_TX_PKT_DATA_POLL = SPINEL_PROP_CNTR__BEGIN + 6,

    ///发送的信标数量。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_TX_PKT_BEACON = SPINEL_PROP_CNTR__BEGIN + 7,

    ///发送的信标请求数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_TX_PKT_BEACON_REQ = SPINEL_PROP_CNTR__BEGIN + 8,

    ///传输的其他类型帧的数量。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_TX_PKT_OTHER = SPINEL_PROP_CNTR__BEGIN + 9,

    ///重传次数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_TX_PKT_RETRY = SPINEL_PROP_CNTR__BEGIN + 10,

    ///CCA失败次数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_TX_ERR_CCA = SPINEL_PROP_CNTR__BEGIN + 11,

    ///传输的单播数据包数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_TX_PKT_UNICAST = SPINEL_PROP_CNTR__BEGIN + 12,

    ///传输的广播数据包数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_TX_PKT_BROADCAST = SPINEL_PROP_CNTR__BEGIN + 13,

    ///由于中止错误导致的帧传输失败数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_TX_ERR_ABORT = SPINEL_PROP_CNTR__BEGIN + 14,

    ///收到的数据包总数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_PKT_TOTAL = SPINEL_PROP_CNTR__BEGIN + 100,

    ///接收数据的数量。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_PKT_DATA = SPINEL_PROP_CNTR__BEGIN + 101,

    ///收到的数据轮询数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_PKT_DATA_POLL = SPINEL_PROP_CNTR__BEGIN + 102,

    ///接收的信标数量。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_PKT_BEACON = SPINEL_PROP_CNTR__BEGIN + 103,

    ///接收到的信标请求数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_PKT_BEACON_REQ = SPINEL_PROP_CNTR__BEGIN + 104,

    ///接收的其他类型帧的数量。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_PKT_OTHER = SPINEL_PROP_CNTR__BEGIN + 105,

    ///允许列表筛选的接收数据包数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_PKT_FILT_WL = SPINEL_PROP_CNTR__BEGIN + 106,

    ///通过目标检查筛选的接收数据包数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_PKT_FILT_DA = SPINEL_PROP_CNTR__BEGIN + 107,

    ///收到的空数据包数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_ERR_EMPTY = SPINEL_PROP_CNTR__BEGIN + 108,

    ///从未知邻居接收的数据包数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_ERR_UKWN_NBR = SPINEL_PROP_CNTR__BEGIN + 109,

    ///源地址无效的接收数据包数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_ERR_NVLD_SADDR = SPINEL_PROP_CNTR__BEGIN + 110,

    ///收到的具有安全错误的数据包数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_ERR_SECURITY = SPINEL_PROP_CNTR__BEGIN + 111,

    ///具有校验和错误的接收数据包数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_ERR_BAD_FCS = SPINEL_PROP_CNTR__BEGIN + 112,

    ///包含其他错误的接收数据包数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_ERR_OTHER = SPINEL_PROP_CNTR__BEGIN + 113,

    ///收到的重复次数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_PKT_DUP = SPINEL_PROP_CNTR__BEGIN + 114,

    ///接收的单播数据包数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_PKT_UNICAST = SPINEL_PROP_CNTR__BEGIN + 115,

    ///接收的广播数据包数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_PKT_BROADCAST = SPINEL_PROP_CNTR__BEGIN + 116,

    ///安全传输的IP消息总数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_TX_IP_SEC_TOTAL = SPINEL_PROP_CNTR__BEGIN + 200,

    ///不安全传输的IP消息总数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_TX_IP_INSEC_TOTAL = SPINEL_PROP_CNTR__BEGIN + 201,

    ///丢弃（未传输）的IP消息数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_TX_IP_DROPPED = SPINEL_PROP_CNTR__BEGIN + 202,

    ///安全接收的IP消息总数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_IP_SEC_TOTAL = SPINEL_PROP_CNTR__BEGIN + 203,

    ///收到的不安全IP消息的总数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_IP_INSEC_TOTAL = SPINEL_PROP_CNTR__BEGIN + 204,

    ///丢弃的已接收IP消息数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_IP_DROPPED = SPINEL_PROP_CNTR__BEGIN + 205,

    ///透射尖晶石框架的数量。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_TX_SPINEL_TOTAL = SPINEL_PROP_CNTR__BEGIN + 300,

    ///收到的尖晶石帧数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_SPINEL_TOTAL = SPINEL_PROP_CNTR__BEGIN + 301,

    ///收到的有错误的尖晶石帧数。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_SPINEL_ERR = SPINEL_PROP_CNTR__BEGIN + 302,

    ///收到的无序尖晶石帧的数量（tid增加超过1）。
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_RX_SPINEL_OUT_OF_ORDER_TID = SPINEL_PROP_CNTR__BEGIN + 303,

    ///成功的Tx IP数据包数
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_IP_TX_SUCCESS = SPINEL_PROP_CNTR__BEGIN + 304,

    ///成功的Rx IP数据包数
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_IP_RX_SUCCESS = SPINEL_PROP_CNTR__BEGIN + 305,

    ///失败的Tx IP数据包数
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_IP_TX_FAILURE = SPINEL_PROP_CNTR__BEGIN + 306,

    ///失败的Rx IP数据包数
    /**格式：`L`（只读）*/
    SPINEL_PROP_CNTR_IP_RX_FAILURE = SPINEL_PROP_CNTR__BEGIN + 307,

    ///消息缓冲区计数器信息
    /** 格式：`SSSSSSSSSSSSS`（只读）`S`，（TotalBuffers）池中缓冲区的数量`S`，（FreeBuffers）可用消息缓冲区的数量`S`，（6loSendMessages）6lo发送队列中的消息数`S`，（6loSendBuffers）6lo发送队列中的缓冲区数`S`，（6loReloadingMessages）6LoWPAN重新组装队列中的消息数`S`，（6loReloadingBuffers）6LoWPAN重新组装队列中的缓冲区数`S`，（Ip6Messages）IPv6发送队列中的消息数`S`，（Ip6Buffers）IPv6发送队列中的缓冲区数`S`，（MplMessages）MPL发送队列中的消息数`S`，（MplBuffers）MPL发送队列中的缓冲区数`S`，（MleMessage）MLE发送队列中的消息数`S`，（MleBuffers）MLE发送队列中的缓冲区数`S`，（ArpMessages）ARP发送队列中的消息数`S`，（ArpBuffers）ARP发送队列中的缓冲区数`S`，（CoapMessages）CoAP发送队列中的消息数`S`，（CoapBuffers）CoAP发送队列中的缓冲区数。
     */
    SPINEL_PROP_MSG_BUFFER_COUNTERS = SPINEL_PROP_CNTR__BEGIN + 400,

    ///所有MAC相关计数器。
    /** 格式：t（A（L））t（A）
     *
     * 内容包括两个结构，第一个结构对应于所有与发送相关的MAC计数器，第二个结构提供与接收相关的计数器。
     *
     * 传输结构包括：
     *
     *   'L'：TxTotal（传输总数）。'L'：TxUnicast（单播传输的总数）。'L'：TxBroadcast（广播传输总数）。'L'：TxAckRequested（具有ack请求的传输次数）。'L'：TxAcked（已确认的传输数）。'L'：TxNoAckRequested（无确认请求的传输次数）。'L'：TxData（传输数据的数量）。'L'：TxDataPoll（传输数据轮询的数量）。'L'：TxBeacon（发送的信标数量）。'L'：TxBeacon request（发送的信标请求数）。'L'：TxOther（传输的其他类型帧的数量）。'L'：TxRetry（重传次数）。'L'：TxErrCca（CCA失败次数）。'L'：TxErrAbort（由于中止错误导致的帧传输失败数）。'L'：TxErrBusyChannel（由于繁忙信道而丢失的帧数）。'L'：TxDirectMaxRetryExpiry（直接消息的过期重传重试次数）。'L'：TxIndirectMaxRetryExpiry（间接消息的过期重传重试次数）。
     *
     * 接收结构包括：
     *
     *   'L'：RxTotal（接收的数据包总数）。'L'：RxUnicast（接收的单播数据包总数）。'L'：RxBroadcast（接收的广播数据包总数）。'L'：RxData（接收数据的数量）。'L'：RxDataPoll（收到的数据轮询数）。'L'：RxBeacon（接收的信标数量）。'L'：RxBeacon请求（接收的信标请求的数量）。'L'：RxOther（接收的其他类型帧的数量）。'L'：RxAddressFiltered（通过地址筛选器（allowlist或denylist）筛选的接收数据包数）。'L'：RxDestAddrFiltered（通过目标检查筛选的接收数据包数）。'L'：RxDuplicated（收到的重复数据包数）。'L'：RxErrNoFrame（没有或格式不正确内容的接收数据包数）。'L'：RxErrUnknownNeighbor（从未知邻居接收的数据包数）。'L'：RxErrInvalidSrcAddr（源地址无效的接收数据包数）。'L'：RxErrSec（收到的具有安全错误的数据包数）。'L'：RxErrFcs（收到的FCS错误数据包数）。'L'：RxErrOther（包含其他错误的接收数据包数）。
     *
     * 使用任何值写入此属性都会将所有MAC计数器重置为零。
     *
     */
    SPINEL_PROP_CNTR_ALL_MAC_COUNTERS = SPINEL_PROP_CNTR__BEGIN + 401,

    ///线程MLE计数器。
    /** 格式：`SSSSSSSSS`
     *
     *   “S”：DisabledRole（设备进入OT_device_ROLE_DISABLED角色的次数）。”S“：DetachedRole（设备进入OT_device_ROLE_DETACHED角色的次数）。”S“：ChildRole（设备进入OT_device_ROLE_CHILD角色的次数）。”S“：RouterRole（设备进入OT_device_ROLE_ROUTER角色的次数）。”S“：LeaderRole（设备进入OT_device_ROLE_LEADER角色的次数）。”S“：AttachAttempts（设备分离时的连接尝试次数）。”S‘：PartitionIdChanges（分区ID的更改数）。’S“：BetterPartitionAttachAttempts（附加到更好分区的尝试次数）。”S'：ParentChanges（设备更改其父项的次数）。
     *
     * 使用任何值写入此属性都会将所有MLE计数器重置为零。
     *
     */
    SPINEL_PROP_CNTR_MLE_COUNTERS = SPINEL_PROP_CNTR__BEGIN + 402,

    ///线程IPv6计数器。
    /** 格式：`t（LL）t（LL）`
     *
     * 内容包括两个结构，第一个结构对应于所有与发送相关的MAC计数器，第二个结构提供与接收相关的计数器。
     *
     * 传输结构包括：“L”：TxSuccess（成功传输的IPv6数据包数）L'：TxFailure（传输失败的IPv6数据包数）。
     *
     * 接收结构包括：“L”：RxSuccess（成功接收的IPv6数据包数）L'：RxFailure（无法接收的IPv6数据包数）。
     *
     * 使用任何值写入此属性都会将所有IPv6计数器重置为零。
     *
     */
    SPINEL_PROP_CNTR_ALL_IP_COUNTERS = SPINEL_PROP_CNTR__BEGIN + 403,

    ///MAC重试直方图。
    /** 格式：t（A（L））t（A）
     *
     * 所需功能：SPINEL_CAPMAC_RETRY_HISTOGRAM
     *
     * 其内容包括两个结构，第一个是与直接消息的重传次数相对应的直方图，第二个是提供间接消息重传次数的直方图。
     *
     * 第一个结构包括：“L”：DirectRetry[0]（0次重试后的数据包数）L'：DirectRetry[1]（1次重试后的数据包数）……'L'：DirectRetry[n]（n次重试后的数据包数）。
     *
     * 阵列的大小为OPENTHREAD_COONFIGMAC_RETRY_SUCCESSHISTOGRAM_MAX_size_COUNT_DIRECT。
     *
     * 第二个结构包括：'L'：IndirectRetry[0]（0次重试后的数据包数）。'L'：IndirectRetry[1]（1次重试后的数据包数）……'L'：IndirectRetry[m]（m次重试后的数据包数）。
     *
     * 阵列的大小为OPENTHREAD_COONFIGMAC_RETRY_SUCCESSHISTOGRAM_MAX_size_COUNT_INDIRECT。
     *
     * 使用任何值写入此属性将重置MAC重试直方图。
     *
     */
    SPINEL_PROP_CNTR_MAC_RETRY_HISTOGRAM = SPINEL_PROP_CNTR__BEGIN + 404,

    SPINEL_PROP_CNTR__END = 0x800,

    SPINEL_PROP_RCP_EXT__BEGIN = 0x800,

    ///MAC密钥
    /** 格式：`CCddd`。
     *
     *  `C`:MAC密钥ID模式`C`：MAC密钥ID `d`：上一个MAC密钥材料数据`d`；当前MAC密钥材料材料数据`d `：下一个MAC关键材料数据
     *
     * Spinel属性用于设置/从RCP获取MAC密钥材料。
     *
     */
    SPINEL_PROP_RCP_MAC_KEY = SPINEL_PROP_RCP_EXT__BEGIN + 0,

    ///MAC帧计数器
    /** 格式：`L`。
     *
     *  `L`：MAC帧计数器
     *
     * Spinel属性用于将MAC帧计数器设置为RCP。
     *
     */
    SPINEL_PROP_RCP_MAC_FRAME_COUNTER = SPINEL_PROP_RCP_EXT__BEGIN + 1,

    ///接收和传输Spinel帧时的时间戳
    /** 格式：`X`。
     *
     *  `X`：Spinel帧传输时间戳
     *
     * Spinel属性用于从RCP获取时间戳，以计算主机和RCP计时器的差异。
     *
     */
    SPINEL_PROP_RCP_TIMESTAMP = SPINEL_PROP_RCP_EXT__BEGIN + 2,

    SPINEL_PROP_RCP_EXT__END = 0x900,

    SPINEL_PROP_NEST__BEGIN = 0x3BC0,

    SPINEL_PROP_NEST_STREAM_MFG = SPINEL_PROP_NEST__BEGIN + 0,

    ///传统网络ULA前缀（8字节）
    /**格式：“D”*/
    SPINEL_PROP_NEST_LEGACY_ULA_PREFIX = SPINEL_PROP_NEST__BEGIN + 1,

    ///使用传统协议加入的最后一个节点的EUI64（如果没有，则返回全部零EUI64）。
    /**格式：'E'*/
    SPINEL_PROP_NEST_LEGACY_LAST_NODE_JOINED = SPINEL_PROP_NEST__BEGIN + 2,

    SPINEL_PROP_NEST__END = 0x3C00,

    SPINEL_PROP_VENDOR__BEGIN = 0x3C00,
    SPINEL_PROP_VENDOR__END   = 0x4000,

    SPINEL_PROP_DEBUG__BEGIN = 0x4000,

    ///测试平台断言
    /** 格式：“b”（只读）
     *
     * 读取此属性将导致对NCP的断言。这是为了测试底层平台/NCP的断言功能。理想情况下，断言应该使NCP复位，但如果不支持，则返回“false”布尔值作为响应。
     *
     */
    SPINEL_PROP_DEBUG_TEST_ASSERT = SPINEL_PROP_DEBUG__BEGIN + 0,

    ///NCP日志级别。
    /**格式：`C`*/
    SPINEL_PROP_DEBUG_NCP_LOG_LEVEL = SPINEL_PROP_DEBUG__BEGIN + 1,

    ///测试平台看门狗
    /** 格式：空（只读）
     *
     * 读取此属性将导致NCP启动“while（true）；”从而触发看门狗。
     *
     * 这用于测试底层平台/NCP上的看门狗功能。
     *
     */
    SPINEL_PROP_DEBUG_TEST_WATCHDOG = SPINEL_PROP_DEBUG__BEGIN + 2,

    ///NCP时间戳基础
    /** 格式：X（仅写）
     *
     * 此属性控制用于日志时间戳字段计算的时基值。
     *
     */
    SPINEL_PROP_DEBUG_LOG_TIMESTAMP_BASE = SPINEL_PROP_DEBUG__BEGIN + 3,

    ///TREL无线电链路-测试模式启用
    /** 格式`b`（读写）
     *
     * 此属性仅用于测试TREL（线程无线电封装链路）无线电类型（模拟期间）。它允许临时禁用和（重新）启用TREL接口。当禁用TREL接口时，通过TREL接口的所有流量都会被无声地丢弃（以模拟无线电/接口故障情况）。
     *
     * 此属性仅在支持TREL无线电链路类型时可用。
     *
     */
    SPINEL_PROP_DEBUG_TREL_TEST_MODE_ENABLE = SPINEL_PROP_DEBUG__BEGIN + 4,

    SPINEL_PROP_DEBUG__END = 0x4400,

    SPINEL_PROP_EXPERIMENTAL__BEGIN = 2000000,
    SPINEL_PROP_EXPERIMENTAL__END   = 2097152,
};

typedef uint32_t spinel_prop_key_t;

// ----------------------------------------------------------------------------

#define SPINEL_HEADER_FLAG 0x80

#define SPINEL_HEADER_TID_SHIFT 0
#define SPINEL_HEADER_TID_MASK (15 << SPINEL_HEADER_TID_SHIFT)

#define SPINEL_HEADER_IID_SHIFT 4
#define SPINEL_HEADER_IID_MASK (3 << SPINEL_HEADER_IID_SHIFT)

#define SPINEL_HEADER_IID_0 (0 << SPINEL_HEADER_IID_SHIFT)
#define SPINEL_HEADER_IID_1 (1 << SPINEL_HEADER_IID_SHIFT)
#define SPINEL_HEADER_IID_2 (2 << SPINEL_HEADER_IID_SHIFT)
#define SPINEL_HEADER_IID_3 (3 << SPINEL_HEADER_IID_SHIFT)

#define SPINEL_HEADER_GET_IID(x) (((x)&SPINEL_HEADER_IID_MASK) >> SPINEL_HEADER_IID_SHIFT)
#define SPINEL_HEADER_GET_TID(x) (spinel_tid_t)(((x)&SPINEL_HEADER_TID_MASK) >> SPINEL_HEADER_TID_SHIFT)

#define SPINEL_GET_NEXT_TID(x) (spinel_tid_t)((x) >= 0xF ? 1 : (x) + 1)

#define SPINEL_BEACON_THREAD_FLAG_VERSION_SHIFT 4

#define SPINEL_BEACON_THREAD_FLAG_VERSION_MASK (0xf << SPINEL_BEACON_THREAD_FLAG_VERSION_SHIFT)

#define SPINEL_BEACON_THREAD_FLAG_JOINABLE (1 << 0)

#define SPINEL_BEACON_THREAD_FLAG_NATIVE (1 << 3)

// ----------------------------------------------------------------------------

enum
{
    SPINEL_DATATYPE_NULL_C        = 0,
    SPINEL_DATATYPE_VOID_C        = '.',
    SPINEL_DATATYPE_BOOL_C        = 'b',
    SPINEL_DATATYPE_UINT8_C       = 'C',
    SPINEL_DATATYPE_INT8_C        = 'c',
    SPINEL_DATATYPE_UINT16_C      = 'S',
    SPINEL_DATATYPE_INT16_C       = 's',
    SPINEL_DATATYPE_UINT32_C      = 'L',
    SPINEL_DATATYPE_INT32_C       = 'l',
    SPINEL_DATATYPE_UINT64_C      = 'X',
    SPINEL_DATATYPE_INT64_C       = 'x',
    SPINEL_DATATYPE_UINT_PACKED_C = 'i',
    SPINEL_DATATYPE_IPv6ADDR_C    = '6',
    SPINEL_DATATYPE_EUI64_C       = 'E',
    SPINEL_DATATYPE_EUI48_C       = 'e',
    SPINEL_DATATYPE_DATA_WLEN_C   = 'd',
    SPINEL_DATATYPE_DATA_C        = 'D',
    SPINEL_DATATYPE_UTF8_C        = 'U', //!< 零终止UTF8编码字符串
    SPINEL_DATATYPE_STRUCT_C      = 't',
    SPINEL_DATATYPE_ARRAY_C       = 'A',
};

typedef char spinel_datatype_t;

#define SPINEL_DATATYPE_NULL_S ""
#define SPINEL_DATATYPE_VOID_S "."
#define SPINEL_DATATYPE_BOOL_S "b"
#define SPINEL_DATATYPE_UINT8_S "C"
#define SPINEL_DATATYPE_INT8_S "c"
#define SPINEL_DATATYPE_UINT16_S "S"
#define SPINEL_DATATYPE_INT16_S "s"
#define SPINEL_DATATYPE_UINT32_S "L"
#define SPINEL_DATATYPE_INT32_S "l"
#define SPINEL_DATATYPE_UINT64_S "X"
#define SPINEL_DATATYPE_INT64_S "x"
#define SPINEL_DATATYPE_UINT_PACKED_S "i"
#define SPINEL_DATATYPE_IPv6ADDR_S "6"
#define SPINEL_DATATYPE_EUI64_S "E"
#define SPINEL_DATATYPE_EUI48_S "e"
#define SPINEL_DATATYPE_DATA_WLEN_S "d"
#define SPINEL_DATATYPE_DATA_S "D"
#define SPINEL_DATATYPE_UTF8_S "U" //!< 零终止UTF8编码字符串

#define SPINEL_DATATYPE_ARRAY_S(x) "A(" x ")"
#define SPINEL_DATATYPE_STRUCT_S(x) "t(" x ")"

#define SPINEL_DATATYPE_ARRAY_STRUCT_S(x) SPINEL_DATATYPE_ARRAY_S(SPINEL_DATATYPE_STRUCT_WLEN_S(x))

#define SPINEL_DATATYPE_COMMAND_S                   \
    SPINEL_DATATYPE_UINT8_S           /* 收割台，收割台*/ \
        SPINEL_DATATYPE_UINT_PACKED_S /* 命令*/

#define SPINEL_DATATYPE_COMMAND_PROP_S                    \
    SPINEL_DATATYPE_COMMAND_S         /* prop命令*/ \
        SPINEL_DATATYPE_UINT_PACKED_S /* 属性id*/

#define SPINEL_MAX_UINT_PACKED 2097151

SPINEL_API_EXTERN spinel_ssize_t spinel_datatype_pack(uint8_t *     data_out,
                                                      spinel_size_t data_len_max,
                                                      const char *  pack_format,
                                                      ...);
SPINEL_API_EXTERN spinel_ssize_t spinel_datatype_vpack(uint8_t *     data_out,
                                                       spinel_size_t data_len_max,
                                                       const char *  pack_format,
                                                       va_list       args);
SPINEL_API_EXTERN spinel_ssize_t spinel_datatype_unpack(const uint8_t *data_in,
                                                        spinel_size_t  data_len,
                                                        const char *   pack_format,
                                                        ...);
/**
 * 此函数解析尖晶石数据，类似于sscanf（）。
 *
 * 该函数实际上调用spinel_datatype_vunpack_in_place（）来解析数据。
 *
 * @param[in]   data_in     指向要分析的数据的指针。
 * @param[in]   data_len    @p data_in的长度（以字节为单位）。
 * @param[in]   pack_format 包含格式字符串的C字符串遵循尖晶石的相同规范。
 * @param[in]   ...         其他参数取决于格式字符串@p pack_format。
 *
 * @returns 分析的长度（字节）。
 *
 * @note 此函数的行为与“spinel_datatype_unpack（）”不同：
 *       -此函数需要指针指向数据类型的复合数据参数，而“spinel_datatype_unpack（）”需要指针指向的数据类型的指针。例如，如果“SPINEL_DATATYPE_EUI64_C”存在于
 *         @p pack_format，此函数要求变量参数中包含“spinel_eui64_t*”，而“spinel_datatype_unpack（）”要求包含“spinel _eui64_t”。
 *       -对于“SPINEL_DATATYPE_UTF8_C”，此函数需要两个参数，第一个参数类型为“char*”，第二个参数类型“size_t”，以指示第一个参数中提供的缓冲区的长度，就像“strncpy（）”一样，而“SPINEL_DATATYPE_unpack（）”只需要“const char”。
 *
 * @sa spinel_datatype_vunpack_in_place（）
 *
 */
SPINEL_API_EXTERN spinel_ssize_t spinel_datatype_unpack_in_place(const uint8_t *data_in,
                                                                 spinel_size_t  data_len,
                                                                 const char *   pack_format,
                                                                 ...);
SPINEL_API_EXTERN spinel_ssize_t spinel_datatype_vunpack(const uint8_t *data_in,
                                                         spinel_size_t  data_len,
                                                         const char *   pack_format,
                                                         va_list        args);
/**
 * 此函数解析尖晶石数据，类似于vsscanf（）。
 *
 * @param[in]   data_in     指向要分析的数据的指针。
 * @param[in]   data_len    @p data_in的长度（以字节为单位）。
 * @param[in]   pack_format 包含格式字符串的C字符串遵循尖晶石的相同规范。
 * @param[in]   args        标识变量参数列表的值。
 *
 * @returns 分析的长度（字节）。
 *
 * @note 此函数的行为与“spinel_datatype_vunpack（）”不同：
 *       -此函数需要指针指向数据类型的复合数据参数，而“spinel_datatype_vunpack（）”需要指针指向的数据类型的指针。例如，如果“SPINEL_DATATYPE_EUI64_C”存在于
 *         @p pack_format，此函数要求变量参数中包含“spinel_eui64_t*”，而“spinel_datatype_vunpack（）”要求包含“spinel _eui64_t”。
 *       -对于“SPINEL_DATATYPE_UTF8_C”，此函数需要两个参数，第一个参数类型为“char*”，第二个参数类型“size_t”，以指示第一个参数中提供的缓冲区的长度，就像“strncpy（）”一样，而“SPINEL_DATATYPE_vunpack（）”只需要“const char”。
 *
 * @sa spinel_datatype_unpack_in_place（）
 *
 */
SPINEL_API_EXTERN spinel_ssize_t spinel_datatype_vunpack_in_place(const uint8_t *data_in,
                                                                  spinel_size_t  data_len,
                                                                  const char *   pack_format,
                                                                  va_list        args);

SPINEL_API_EXTERN spinel_ssize_t spinel_packed_uint_decode(const uint8_t *bytes,
                                                           spinel_size_t  len,
                                                           unsigned int * value_ptr);
SPINEL_API_EXTERN spinel_ssize_t spinel_packed_uint_encode(uint8_t *bytes, spinel_size_t len, unsigned int value);
SPINEL_API_EXTERN spinel_ssize_t spinel_packed_uint_size(unsigned int value);

SPINEL_API_EXTERN const char *spinel_next_packed_datatype(const char *pack_format);

// ----------------------------------------------------------------------------

SPINEL_API_EXTERN const char *spinel_command_to_cstr(spinel_command_t command);

SPINEL_API_EXTERN const char *spinel_prop_key_to_cstr(spinel_prop_key_t prop_key);

SPINEL_API_EXTERN const char *spinel_net_role_to_cstr(uint8_t net_role);

SPINEL_API_EXTERN const char *spinel_mcu_power_state_to_cstr(uint8_t mcu_power_state);

SPINEL_API_EXTERN const char *spinel_status_to_cstr(spinel_status_t status);

SPINEL_API_EXTERN const char *spinel_capability_to_cstr(spinel_capability_t capability);

SPINEL_API_EXTERN const char *spinel_radio_link_to_cstr(uint32_t radio);

SPINEL_API_EXTERN const char *spinel_link_metrics_status_to_cstr(uint8_t status);

// ----------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif

#endif /* 定义（SPINEL_HEADER_INCLUDED）*/

