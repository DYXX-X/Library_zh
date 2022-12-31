// 版权所有2019 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef volatile struct emac_mac_dev_s {
    union {
        struct {
            uint32_t pltf : 2;          /*这些比特控制添加到每个传输帧开头的前导码字节数。前导码减少仅在MAC以全双工模式操作时发生。2’b00:7字节的前导码。2’b01:5字节的前导码。2’b10:3字节的前导码。*/
            uint32_t rx : 1;            /*当该位被设置时，MAC的接收机状态机被启用以从MII接收帧。当该比特被重置时，MAC接收状态机在完成当前帧的接收之后被禁用。*/
            uint32_t tx : 1;            /*当该位被设置时，MAC的传输状态机被启用以在MII上传输。当该比特被重置时，MAC传输状态机在完成当前帧的传输之后被禁用。*/
            uint32_t deferralcheck : 1; /*延期检查。*/
            uint32_t backofflimit : 2;  /*后退限制确定了在冲突后重试期间MAC在重新调度传输尝试之前等待的时隙时间延迟的随机整数（r）（对于10/100Mbps为512位时间）。此位仅适用于半双工模式。00:k=分钟（n 10）。01：k=最小值（n 8）。10： k=最小值（n 4）。11： k＝min（n 1）n＝重传尝试。随机整数r取值范围为0~2000。*/
            uint32_t padcrcstrip : 1;   /*当设置该位时，只有当长度字段的值小于1536字节时，MAC才去除传入帧上的Pad或FCS字段。长度字段大于或等于1536字节的所有接收帧被传递到应用程序，而不剥离Pad或FCS字段。当重置此位时，MAC将所有传入帧传递给主机，而不修改它们。*/
            uint32_t reserved8 : 1;
            uint32_t retry : 1;         /*当设置该位时，MAC仅尝试一次传输。当MII接口上发生冲突时，MAC忽略当前帧传输，并在传输帧状态中报告具有过度冲突错误的帧中止。当重置该位时，MAC尝试根据BL字段的设置重试（位[6:5]）。此位仅适用于半双工模式。*/
            uint32_t rxipcoffload : 1;  /*当设置该位时，MAC计算所有接收到的以太网帧有效载荷的补和的16位补。它还检查接收到的帧的IPv4报头校验和（假定为接收到的以太网帧的字节25/26或29/30（VLAN标记））是否正确，并在接收状态字中给出状态。MAC还附加为IP报头数据报有效载荷计算的16位校验和（IPv4报头之后的字节），并将其附加到传输到应用程序的以太网帧（当取消选择类型2 COE时）。重置此位时，禁用此功能。*/
            uint32_t duplex : 1;        /*当设置该位时，MAC以全双工模式操作，在全双工模式下它可以同时发送和接收。在全双工模式下，该位为只读，默认值为1’b1。*/
            uint32_t loopback : 1;      /*当设置该位时，MAC在回送模式MII中操作。MII接收时钟输入（CLK_RX）是环回正常工作所必需的，因为传输时钟未在内部环回。*/
            uint32_t rxown : 1;         /*当在半双工模式中断言TX_EN时，MAC禁用帧的接收。当重置该位时，MAC接收PHY在发送时给出的所有分组。如果MAC在全双工模式下运行，则此位不适用。*/
            uint32_t fespeed : 1;       /*该位选择MII RMII接口中的速度。0:10 Mbps。1： 100 Mbps。*/
            uint32_t mii : 1;           /*该位选择以太网线路速度。对于10或100 Mbps的操作，应将其设置为1。在10或100 Mbps的操作中，该位与FES（EMACFESPEED）位一起选择精确的线速度。在仅10/100 Mbps的操作中，位始终为1。*/
            uint32_t disablecrs : 1;    /*当设置为高时，该比特使得MAC发射机在半双工模式下的帧传输期间忽略MII CRS信号。此请求不会导致在此类传输过程中因载波丢失或无载波而产生错误。当该比特较低时，MAC发射机由于载波侦听而产生这样的错误，甚至可以中止传输。*/
            uint32_t interframegap : 3; /*这些比特控制传输期间帧之间的最小IFG。3'b000:96位时间。3'b0001:88比特次。3’b010：80位时间。3'b111:40比特次。在半双工模式中，最小IFG只能配置64位时间（IFG＝100）。不考虑较低的值。*/
            uint32_t jumboframe : 1;    /*当设置此位时，MAC允许9 018字节的巨型帧（VLAN标记帧为9 022字节），而不报告接收帧状态中的巨型帧错误。*/
            uint32_t reserved21 : 1;
            uint32_t jabber : 1;   /*当设置该位时，MAC禁用发射机上的jabber定时器。MAC可以传输高达16383字节的帧。当重置该位时，如果应用程序在传输期间发送超过2048字节的数据（如果JE设置为高，则为10 240），则MAC切断发射机。*/
            uint32_t watchdog : 1; /*设置此位时，MAC禁用接收器上的看门狗定时器。MAC可以接收高达16383字节的帧。当重置该位时，MAC不允许超过2048字节（如果JE设置为高，则为10 240）的接收帧或寄存器（看门狗超时寄存器）中编程的值。MAC切断在看门狗限制字节数之后接收的任何字节。*/
            uint32_t reserved24 : 1;
            uint32_t reserved25 : 1;
            uint32_t reserved26 : 1;
            uint32_t ass2kp : 1; /*当设置时，MAC将长度高达2000字节的所有帧视为正常分组。当比特[20]（JE）未被设置时，MAC将大小大于2K字节的所有接收帧视为巨型帧。当该位被重置且位[20]（JE）未被设置时，MAC将大小大于1518字节（标记为1522字节）的所有接收帧视为巨型帧。设置位[20]时，设置该位对巨帧状态没有影响。*/
            uint32_t sairc : 3;  /*此字段控制所有传输帧的源地址插入或替换。位[30]根据位[29:28]：2’b0x的值指定哪个MAC地址寄存器（0或1）用于源地址插入或替换：输入信号mti_sa_ctrl_i和ati_sa_ctrl_i控制sa字段生成。2’b10：如果比特[30]设置为0，则MAC将MAC地址0寄存器的内容插入所有传输帧的SA字段中。如果比特[30]被设置为1，则MAC将MAC地址1寄存器的内容插入所有发送帧的SA字段中。2’b11：如果比特[30]设置为0，则MAC替换所有传输帧的SA字段中的MAC地址0寄存器的内容。如果Bit[30]设置为1，则MAC替换所有发送帧的SA字段中的MAC地址1寄存器的内容。*/
            uint32_t reserved31 : 1;
        };
        uint32_t val;
    } gmacconfig;
    union {
        struct {
            uint32_t pmode : 1; /*当设置此位时，地址过滤器模块传递所有传入帧，而不考虑目的地或源地址。当PR（PRI_RATIO）被设置时，接收状态字的SA或DA过滤器失败状态位总是被清除。*/
            uint32_t reserved1 : 1;
            uint32_t reserved2 : 1;
            uint32_t daif : 1; /*当设置该位时，地址检查块在反向过滤模式下操作，用于单播和多播帧的DA地址比较。当重置时，执行帧的正常过滤。*/
            uint32_t pam : 1;  /*设置此位时，表示所有接收到的具有多播目标地址的帧（目标地址字段中的第一位为“1”）都已通过。*/
            uint32_t dbf : 1;  /*当设置该位时，AFM（地址过滤模块）模块阻止所有传入的广播帧。此外，它覆盖所有其他过滤器设置。当重置该位时，AFM模块通过所有接收的广播帧。*/
            uint32_t pcf : 2;  /*这些位控制所有控制帧（包括单播和多播暂停帧）的转发。2’00：MAC过滤所有控制帧，防止其到达应用程序。2'b01:MAC将除暂停帧外的所有控制帧转发给应用程序，即使它们未通过地址过滤器。2’b10：MAC将所有控制帧转发给应用程序，即使它们未通过地址过滤器。2’b11:MAC转发通过地址过滤器的控制帧。以下条件应适用于暂停帧处理：条件1：MAC处于全双工模式，通过将寄存器（流控制寄存器）的位2（RFE）设置为1启用流控制。条件2：接收帧的目标地址（DA）与特殊多播地址或MAC匹配设置寄存器（流量控制寄存器）的位3（UP）时的地址0。条件3：接收帧的类型字段为0x8808，OPCODE字段为0x0001。*/
            uint32_t saif : 1; /*当设置该位时，地址检查块在SA地址比较的反向过滤模式下操作。SA与SA寄存器匹配的帧被标记为SA地址过滤器失败。当重置此位时，SA与SA寄存器不匹配的帧被标记为SA地址过滤器失败。*/
            uint32_t safe : 1; /*当设置该位时，MAC将接收帧的SA字段与启用的SA寄存器中编程的值进行比较。如果比较失败，则MAC丢弃该帧。当重置该位时，MAC根据SA地址比较将接收到的帧转发给具有Rx状态的更新SAF位的应用。*/
            uint32_t reserved10 : 1;
            uint32_t reserved11 : 5;
            uint32_t reserved16 : 1;
            uint32_t reserved17 : 3;
            uint32_t reserved20 : 1;
            uint32_t reserved21 : 1;
            uint32_t reserved22 : 9;
            uint32_t receive_all : 1; /*当设置该位时，MAC接收器模块传递所有接收到的帧，而不管它们是否传递地址过滤器到应用。SA或DA过滤的结果在接收状态字中的相应位中更新（通过或失败）。当重置此位时，接收器模块仅将那些通过SA或DA地址过滤器的帧传递给应用程序。*/
        };
        uint32_t val;
    } gmacff;
    uint32_t reserved_1008;
    uint32_t reserved_100c;
    union {
        struct {
            uint32_t miibusy : 1;   /*在写入PHY加法器寄存器和PHY数据寄存器之前，该位应读取逻辑0。在PHY寄存器访问期间，软件将该位设置为1’b1，以指示正在进行读取或写入访问。PHY数据寄存器在MAC清除该位之前无效。因此，PHY数据寄存器（MII数据）应保持有效，直到MAC在PHY写入操作期间清除该位。类似地，对于读取操作，寄存器5的内容在该位被清除之前是无效的。只有在上一个操作完成后，才能执行后续的读或写操作。因为在读或写操作完成之后没有从PHY到MAC的确认，所以即使PHY不存在。*/
            uint32_t miiwrite : 1;  /*当设置此位时，向PHY指示这是使用MII数据寄存器的写入操作。如果未设置此位，则表示这是一个将数据放入MII数据寄存器的读取操作。*/
            uint32_t miicsrclk : 4; /*CSR时钟范围：1.0MHz~2.5MHz。4'b00000：当APB时钟频率为80MHz时，MDC时钟频率为APB CLK/42 4'b00011：当APA时钟频率为40MHz时。*/
            uint32_t miireg : 5;    /*这些位选择所选PHY设备中的所需MII寄存器。*/
            uint32_t miidev : 5;    /*该字段指示正在访问32个可能的PHY设备中的哪一个。*/
            uint32_t reserved16 : 16;
        };
        uint32_t val;
    } emacgmiiaddr;
    union {
        struct {
            uint32_t mii_data : 16; /*该字段包含在管理读取操作之后从PHY读取的16位数据值或在管理写入操作之前要写入PHY的16位的数据值。*/
            uint32_t reserved16 : 16;
        };
        uint32_t val;
    } emacmiidata;
    union {
        struct {
            uint32_t fcbba : 1; /*如果设置了TFCE位，则该位在全双工模式下启动暂停帧，并在半双工模式下激活背压功能。在全双工模式下，在写入流量控制寄存器之前，该位应读取为1’b0。要启动暂停帧，应用程序必须将此位设置为1’b1。在传输控制帧期间，此位继续设置，以表示正在进行帧传输。暂停帧传输完成后，MAC将此位重置为1’b0。在清除此位之前，不应写入流量控制寄存器。在半双工模式中，当该位被设置（并且TFCE被设置）时，MAC断言背压。在MAC接收到新帧时的背压期间，发射机开始发送导致冲突的JAM模式。当MAC配置为全双工模式时，BPA（背压激活）将自动禁用。*/
            uint32_t tfce : 1;  /*在全双工模式中，当设置该位时，MAC启用流控制操作以发送暂停帧。当重置该位时，MAC中的流控制操作被禁用，并且MAC不发送任何暂停帧。在半双工模式中，当设置该位时，MAC启用背压操作。当重置该位时，背压功能被禁用。*/
            uint32_t rfce : 1;  /*当设置该位时，MAC解码接收到的暂停帧，并在指定（暂停）时间内禁用其发射机。当重置该位时，暂停帧的解码功能被禁用。*/
            uint32_t upfd : 1;  /*当暂停帧具有IEEE Std 802.3中指定的唯一多播地址时，将对其进行处理。当设置此位时，MAC也可以检测具有站点单播地址的暂停帧。该单播地址应与EMACADDR0高寄存器和EMACADDRO低寄存器中的规定一致。当重置此位时，MAC仅检测具有唯一多播地址的暂停帧。*/
            uint32_t plt : 2;   /*此字段配置暂停帧的暂停计时器自动重传的阈值。阈值应始终小于以位[31:16]配置的暂停时间。例如，如果PT＝100H（256个时隙时间）并且PLT＝01，则在发送第一暂停帧之后，在228（256-28）个时隙时间自动发送第二暂停帧。以下列表提供了不同值的阈值：2’b00：阈值为暂停时间减去4个时隙时间（PT-4时隙时间）。2’b01：阈值为暂停时间减去28个时隙时间（PT-28个时隙时间）。2’b10：阈值为暂停时间减去144个时隙时间（PT-144时隙时间）。2’b11：阈值为暂停时间减去256个时隙时间（PT-256时隙时间）。时隙时间被定义为在MII接口上传输512位（64字节）所花费的时间。*/
            uint32_t reserved6 : 1;
            uint32_t dzpq : 1; /*当设置该位时，它禁止在FIFO层的流控制信号无效时自动生成零数量暂停帧。当该位复位时，启用自动零量暂停帧生成的正常操作。*/
            uint32_t reserved8 : 8;
            uint32_t pause_time : 16; /*此字段保存传输控制帧中暂停时间字段中使用的值。如果将暂停时间位配置为与MII时钟域双重同步，则应仅在目标时钟域中至少四个时钟周期之后才执行对该寄存器的连续写入。*/
        };
        uint32_t val;
    } gmacfc;
    uint32_t reserved_101c;
    uint32_t reserved_1020;
    union {
        struct {
            uint32_t macrpes : 1;  /*当为高时，该位指示MAC MII接收协议引擎正在积极地接收数据并且不处于空闲状态。*/
            uint32_t macrffcs : 2; /*当该字段为高时，表示MAC接收帧控制器模块的FIFO读写控制器的活动状态。MACRFFCS[1]表示FIFO读取控制器的状态。MACRFFCS[0]表示小型FIFO写入控制器的状态。*/
            uint32_t reserved3 : 1;
            uint32_t mtlrfwcas : 1; /*当该位为高时，表示MTL Rx FIFO写入控制器处于活动状态，并将接收到的帧传输到FIFO。*/
            uint32_t mtlrfrcs : 2;  /*此字段给出Rx FIFO读控制器的状态：2’b000:IDLE状态。2’b01：读取帧数据。2’b10：读取帧状态（或时间戳）。2’b11：刷新帧数据和状态。*/
            uint32_t reserved7 : 1;
            uint32_t mtlrffls : 2; /*此字段给出Rx FIFO的填充级别状态：2’b000：Rx FIFO空。2’b01：Rx FIFO填充水平低于流量控制停用阈值。2’b10：Rx FIFO填充水平高于流量控制激活阈值。2’b11：Rx FIFO满。*/
            uint32_t reserved10 : 6;
            uint32_t mactpes : 1;  /*当为高时，该位指示MAC MII传输协议引擎正在主动传输数据并且不处于空闲状态。*/
            uint32_t mactfcs : 2;  /*该字段指示MAC传输帧控制器模块的状态：2’b00:IDLE状态。2’b01：等待前一帧或IFG或退避期的状态结束。2’b10：生成并发送暂停帧（在全双工模式下）。2’b11：传输输入帧。*/
            uint32_t mactp : 1;    /*当为高时，该位指示MAC发射机处于暂停状态（处于全双工模式），因此不调度任何帧进行传输。*/
            uint32_t mtltfrcs : 2; /*该字段指示Tx FIFO读取控制器的状态：2’b00:IDLE状态。2’b01：读取状态（向MAC发射机传输数据）。2’b10：等待来自MAC发射机的TxStatus。2’b11：写入接收到的TxStatus或刷新Tx FIFO。*/
            uint32_t mtltfwcs : 1; /*当该位为高时，表示MTL Tx FIFO写入控制器处于活动状态，正在向Tx FIFO传输数据。*/
            uint32_t reserved23 : 1;
            uint32_t mtltfnes : 1; /*当该位为高时，表示MTL Tx FIFO不为空，并且有一些数据留作传输。*/
            uint32_t mtltsffs : 1; /*当为高时，该位表示MTL TxStatus FIFO已满。因此，MTL不能接受更多的帧进行传输。*/
            uint32_t reserved26 : 6;
        };
        uint32_t val;
    } emacdebug;
    uint32_t pmt_rwuffr; /*MSB（第31位）必须为零。位j[30:0]是字节掩码。如果字节掩码的位1/2/3/4（字节数）被设置，CRC块处理输入分组的滤波器1/2/3/4偏移+j（PWKPTR为0/1/2/3）。RWKPTR为0：过滤器0字节掩码。设置位后，模式仅适用于多播数据包*/
    union {
        struct {
            uint32_t pwrdwn : 1;   /*当设置时，MAC接收器丢弃所有接收到的帧，直到它接收到预期的魔术包或远程唤醒帧。只有当MGKPKTEN GLBLUCAST或RWKPKTEN位设置为高时，才能设置该位。*/
            uint32_t mgkpkten : 1; /*当设置时，由于魔术包接收而能够生成电源管理事件。*/
            uint32_t rwkpkten : 1; /*当设置时，由于远程唤醒帧接收而启用电源管理事件的生成*/
            uint32_t reserved3 : 2;
            uint32_t mgkprcvd : 1; /*当设置该位时，该位指示由于接收到魔术包而产生电源管理事件。该位由读入该寄存器清除。*/
            uint32_t rwkprcvd : 1; /*当设置该位时，该位指示由于接收到远程唤醒帧而生成电源管理事件。该位由读入该寄存器清除。*/
            uint32_t reserved7 : 2;
            uint32_t glblucast : 1; /*当设置时，启用由MAC（DAFilter）地址识别过滤的任何单播分组作为远程唤醒帧。*/
            uint32_t reserved10 : 14;
            uint32_t rwkptr : 5; /*指针的最大值为7，详细信息请参阅PMT_RUFFR。*/
            uint32_t reserved29 : 2;
            uint32_t rwkfiltrst : 1; /*当该位被置位时，它将RWKPTR寄存器重置为3’8000。*/
        };
        uint32_t val;
    } pmt_csr;
    union {
        struct {
            uint32_t tlpien : 1; /*当设置该位时，该位指示由于LPIEN位的设置，MAC发射机已进入LPI状态。通过读取该寄存器来清除该位。*/
            uint32_t tlpiex : 1; /*当设置时，该位指示在用户清除了LPIEN位并且LPI_TW_Timer已过期之后，MAC发射机已退出LPI状态。通过读取该寄存器来清除该位。*/
            uint32_t rlpien : 1; /*当设置时，该位指示MAC接收机已接收到LPI模式并进入LPI状态。通过读取该寄存器来清除该位。*/
            uint32_t rlpiex : 1; /*当设置时，该位指示MAC接收机已停止在MII接口上接收LPI模式，退出LPI状态并恢复正常接收。通过读取该寄存器来清除该位。*/
            uint32_t reserved4 : 4;
            uint32_t tlpist : 1; /*当设置时，该位指示MAC正在MII接口上发送LPI模式。*/
            uint32_t rlpist : 1; /*当设置时，该位指示MAC正在MII接口上接收LPI模式。*/
            uint32_t reserved10 : 6;
            uint32_t lpien : 1; /*当设置时，该位指示MAC发射机进入LPI状态。重置时，该位指示MAC退出LPI状态并恢复正常传输。当LPITXA位被设置并且MAC由于新分组的到达而退出LPI状态时，该位被清除。*/
            uint32_t pls : 1;   /*该位指示PHY的链路状态。当设置时，链路被认为是正常的（向上），而当重置时，链路则被认为是关闭的。*/
            uint32_t reserved18 : 1;
            uint32_t lpitxa : 1; /*当MAC在发送侧进入或退出LPI模式时，该位控制MAC的行为。如果LPITXA和LPIEN比特被设置为1，则MAC仅在所有未完成帧和未决帧被发送之后才进入LPI模式。当应用程序发送任何帧时，MAC退出LPI模式。当该位为0时，LPIEN位直接控制MAC进入或退出LPI模式时的行为。*/
            uint32_t reserved20 : 12;
        };
        uint32_t val;
    } gmaclpi_crs;
    union {
        struct {
            uint32_t lpi_tw_timer : 16; /*该字段指定MAC在停止向PHY发送LPI模式之后和恢复正常传输之前等待的最短时间（以微秒为单位）。TLPIEX状态位在该计时器到期后设置。*/
            uint32_t lpi_ls_timer : 10; /*该字段指定在LPI模式可以被发送到PHY之前，来自PHY的链路状态应该处于正常（OKAY）的最短时间（以毫秒为单位）。即使设置了LPIEN位，MAC也不发送LPI模式，除非LPI_LS_Timer达到编程的终端计数。LPI_LS_Timer的默认值为IEEE标准中定义的1000（1秒）。*/
            uint32_t reserved26 : 6;
        };
        uint32_t val;
    } gmaclpitimerscontrol;
    union {
        struct {
            uint32_t reserved0 : 1;
            uint32_t reserved1 : 1;
            uint32_t reserved2 : 1;
            uint32_t pmtints : 1; /*当在断电模式下接收到魔术包或远程唤醒帧时，设置该位（参见PMT控制和状态寄存器中的位[5]和位[6]）。由于PMT控制和状态寄存器的读取操作，当两个位[6:5]都被清除时，该位被清除。只有在核心配置期间选择可选PMT模块时，此位才有效。*/
            uint32_t reserved4 : 1;
            uint32_t reserved5 : 1;
            uint32_t reserved6 : 1;
            uint32_t reserved7 : 1;
            uint32_t reserved8 : 1;
            uint32_t reserved9 : 1;
            uint32_t lpiis : 1; /*当启用节能以太网功能时，该位被设置为MAC发送器或接收器中的任何LPI状态入口或出口。该位在读取寄存器（LPI控制和状态寄存器）的位[0]时被清除。*/
            uint32_t reserved11 : 1;
            uint32_t reserved12 : 20;
        };
        uint32_t val;
    } emacints;
    union {
        struct {
            uint32_t reserved0 : 1;
            uint32_t reserved1 : 1;
            uint32_t reserved2 : 1;
            uint32_t pmtintmask : 1; /*当设置该位时，由于寄存器（中断状态寄存器）中PMT中断状态位的设置，该位禁用中断信号的断言。*/
            uint32_t reserved4 : 5;
            uint32_t reserved9 : 1;
            uint32_t lpiintmask : 1; /*当设置该位时，由于寄存器（中断状态寄存器）中LPI中断状态位的设置，该位禁用中断信号的断言。*/
            uint32_t reserved11 : 21;
        };
        uint32_t val;
    } emacintmask;
    union {
        struct {
            uint32_t address0_hi : 16; /*该字段包含第一个6字节MAC地址的高位16位（47:32）。MAC使用此字段来过滤接收的帧，并在传输流控制（暂停）帧中插入MAC地址。*/
            uint32_t reserved16 : 15;
            uint32_t address_enable0 : 1; /*此位始终设置为1。*/
        };
        uint32_t val;
    } emacaddr0high;
    uint32_t emacaddr0low; /*该字段包含第一个6字节MAC地址的低32位。这由MAC用于过滤接收到的帧并将MAC地址插入到传输流控制（暂停）帧中。*/
    union {
        struct {
            uint32_t mac_address1_hi : 16; /*该字段包含第二个6字节MAC地址的高位16位bits[47:32]。*/
            uint32_t reserved16 : 8;
            uint32_t mask_byte_control : 6; /*这些位是用于比较每个EMACADDR1字节的掩码控制位。当设置为高时，MAC不将接收的DA或SA的相应字节与EMACADDR1寄存器的内容进行比较。每个位控制字节掩码如下：位[29]：EMACADDR1高[15:8]。位[28]：EMACADDR1高[7:0]。位[27]：EMACADDR1低[31:24]。位[24]：EMACADDR1低[7:0]。您可以通过屏蔽地址的一个或多个字节来过滤一组地址（称为组地址过滤）。*/
            uint32_t source_address : 1;    /*当设置该位时，EMACADDR1[47:0]用于与接收帧的SA字段进行比较。当重置该位时，EMACADDR1[47:0]用于与接收帧的DA字段进行比较。*/
            uint32_t address_enable1 : 1;   /*当设置该位时，地址过滤器模块使用第二MAC地址进行完美过滤。当重置该位时，地址过滤器模块忽略用于过滤的地址。*/
        };
        uint32_t val;
    } emacaddr1high;
    uint32_t emacaddr1low; /*该字段包含第二个6字节MAC地址的低32位。此字段的内容未定义，因此需要在初始化过程之后配置寄存器。*/
    union {
        struct {
            uint32_t mac_address2_hi : 16; /*该字段包含第三个6字节MAC地址的高位16位bits[47:32]。*/
            uint32_t reserved16 : 8;
            uint32_t mask_byte_control2 : 6; /*这些位是用于比较每个EMACADDR2字节的掩码控制位。当设置为高时，MAC不将接收的DA或SA的相应字节与EMACADDR2寄存器的内容进行比较。每个位控制字节掩码如下：位[29]：EMACADDR2高[15:8]。位[28]：EMACADDR2高[7:0]。位[27]：EMACADDR2低[31:24]。位[24]：EMACADDR2低[7:0]。您可以通过屏蔽地址的一个或多个字节来过滤一组地址（称为组地址过滤）。*/
            uint32_t source_address2 : 1;    /*当设置该位时，EMACADDR2[47:0]用于与接收帧的SA字段进行比较。当重置该位时，EMACADDR2[47:0]用于与接收帧的DA字段进行比较。*/
            uint32_t address_enable2 : 1;    /*当设置该位时，地址过滤器模块使用第三MAC地址进行完美过滤。当重置该位时，地址过滤器模块忽略用于过滤的地址。*/
        };
        uint32_t val;
    } emacaddr2high;
    uint32_t emacaddr2low; /*该字段包含第三个6字节MAC地址的低32位。此字段的内容未定义，因此需要在初始化过程后配置寄存器。*/
    union {
        struct {
            uint32_t mac_address3_hi : 16; /*该字段包含第四个6字节MAC地址的高位16位bits[47:32]。*/
            uint32_t reserved16 : 8;
            uint32_t mask_byte_control3 : 6; /*这些位是用于比较每个EMACADDR3字节的掩码控制位。当设置为高时，MAC不将接收的DA或SA的相应字节与EMACADDR3寄存器的内容进行比较。每个位控制字节掩码如下：位[29]：EMACADDR3高[15:8]。位[28]：EMACADDR3高[7:0]。位[27]：EMACADDR3低[31:24]。位[24]：EMACADDR3低[7:0]。您可以通过屏蔽地址的一个或多个字节来过滤一组地址（称为组地址过滤）。*/
            uint32_t source_address3 : 1;    /*当设置该位时，EMACADDR3[47:0]用于与接收帧的SA字段进行比较。当重置该位时，EMACADDR3[47:0]用于与接收帧的DA字段进行比较。*/
            uint32_t address_enable3 : 1;    /*当设置该位时，地址过滤器模块使用第四MAC地址进行完美过滤。当重置该位时，地址过滤器模块忽略用于过滤的地址。*/
        };
        uint32_t val;
    } emacaddr3high;
    uint32_t emacaddr3low; /*该字段包含第四个6字节MAC地址的低32位。此字段的内容未定义，因此需要在初始化过程之后配置寄存器。*/
    union {
        struct {
            uint32_t mac_address4_hi : 16; /*该字段包含第五个6字节MAC地址的高位16位bits[47:32]。*/
            uint32_t reserved16 : 8;
            uint32_t mask_byte_control4 : 6; /*这些位是用于比较每个EMACADDR4字节的掩码控制位。当设置为高时，MAC不将接收的DA或SA的相应字节与EMACADDR4寄存器的内容进行比较。每个位控制字节掩码如下：位[29]：EMACADDR4高[15:8]。位[28]：EMACADDR4高[7:0]。位[27]：EMACADDR4低[31:24]。位[24]：EMACADDR4低[7:0]。您可以通过屏蔽地址的一个或多个字节来过滤一组地址（称为组地址过滤）。*/
            uint32_t source_address4 : 1;    /*当设置该位时，EMACADDR4[47:0]用于与接收帧的SA字段进行比较。当该位复位时，EMACADDR4[47:0]用于与接收帧的DA字段进行比较。*/
            uint32_t address_enable4 : 1;    /*当设置该位时，地址过滤器模块使用第五MAC地址进行完美过滤。当重置该位时，地址过滤器模块忽略用于过滤的地址。*/
        };
        uint32_t val;
    } emacaddr4high;
    uint32_t emacaddr4low; /*该字段包含第五个6字节MAC地址的低32位。此字段的内容未定义，因此需要在初始化过程后配置寄存器。*/
    union {
        struct {
            uint32_t mac_address5_hi : 16; /*该字段包含第六个6字节MAC地址的高位16位bits[47:32]。*/
            uint32_t reserved16 : 8;
            uint32_t mask_byte_control5 : 6; /*这些位是用于比较每个EMACADDR5字节的掩码控制位。当设置为高时，MAC不将接收的DA或SA的相应字节与EMACADDR5寄存器的内容进行比较。每个位控制字节掩码如下：位[29]：EMACADDR5高[15:8]。位[28]：EMACADDR5高[7:0]。位[27]：EMACADDR5低[31:24]。位[24]：EMACADDR5低[7:0]。您可以通过屏蔽地址的一个或多个字节来过滤一组地址（称为组地址过滤）。*/
            uint32_t source_address5 : 1;    /*当设置该位时，EMACADDR5[47:0]用于与接收帧的SA字段进行比较。当该位复位时，EMACADDR5[47:0]用于与接收帧的DA字段进行比较。*/
            uint32_t address_enable5 : 1;    /*当设置该位时，地址过滤器模块使用第六MAC地址进行完美过滤。当重置该位时，地址过滤器模块忽略用于过滤的地址。*/
        };
        uint32_t val;
    } emacaddr5high;
    uint32_t emacaddr5low; /*该字段包含第六个6字节MAC地址的低32位。此字段的内容未定义，因此需要在初始化过程后配置寄存器。*/
    union {
        struct {
            uint32_t mac_address6_hi : 16; /*该字段包含第七个6字节MAC地址的高位16位bits[47:32]。*/
            uint32_t reserved16 : 8;
            uint32_t mask_byte_control6 : 6; /*这些位是用于比较每个EMACADDR6字节的掩码控制位。当设置为高时，MAC不将接收的DA或SA的相应字节与EMACADDR6寄存器的内容进行比较。每个位控制字节掩码如下：位[29]：EMACADDR6高[15:8]。位[28]：EMACADDR6高[7:0]。位[27]：EMACADDR6低[31:24]。位[24]：EMACADDR6低[7:0]。您可以通过屏蔽地址的一个或多个字节来过滤一组地址（称为组地址过滤）。*/
            uint32_t source_address6 : 1;    /*当设置该位时，EMACADDR6[47:0]用于与接收帧的SA字段进行比较。当该位复位时，EMACADDR6[47:0]用于与接收帧的DA字段进行比较。*/
            uint32_t address_enable6 : 1;    /*当设置该位时，地址过滤器模块使用第七MAC地址进行完美过滤。当重置该位时，地址过滤器模块忽略用于过滤的地址。*/
        };
        uint32_t val;
    } emacaddr6high;
    uint32_t emacaddr6low; /*该字段包含第七个6字节MAC地址的低32位。此字段的内容未定义，因此需要在初始化过程之后配置寄存器。*/
    union {
        struct {
            uint32_t mac_address7_hi : 16; /*该字段包含第八个6字节MAC地址的高位16位bits[47:32]。*/
            uint32_t reserved16 : 8;
            uint32_t mask_byte_control7 : 6; /*这些位是用于比较每个EMACADDR7字节的掩码控制位。当设置为高时，MAC不将接收的DA或SA的相应字节与EMACADDR7寄存器的内容进行比较。每个位控制字节掩码如下：位[29]：EMACADDR7高[15:8]。位[28]：EMACADDR7高[7:0]。位[27]：EMACADDR7低[31:24]。位[24]：EMACADDR7低[7:0]。您可以通过屏蔽地址的一个或多个字节来过滤一组地址（称为组地址过滤）。*/
            uint32_t source_address7 : 1;    /*当设置该位时，EMACADDR7[47:0]用于与接收帧的SA字段进行比较。当该位复位时，EMACADDR7[47:0]用于与接收帧的DA字段进行比较。*/
            uint32_t address_enable7 : 1;    /*当设置该位时，地址过滤器模块使用第八MAC地址进行完美过滤。当重置该位时，地址过滤器模块忽略用于过滤的地址。*/
        };
        uint32_t val;
    } emacaddr7high;
    uint32_t emacaddr7low; /*该字段包含第八个6字节MAC地址的低32位。此字段的内容未定义，因此需要在初始化过程之后配置寄存器。*/
    uint32_t reserved_1080;
    uint32_t reserved_1084;
    uint32_t reserved_1088;
    uint32_t reserved_108c;
    uint32_t reserved_1090;
    uint32_t reserved_1094;
    uint32_t reserved_1098;
    uint32_t reserved_109c;
    uint32_t reserved_10a0;
    uint32_t reserved_10a4;
    uint32_t reserved_10a8;
    uint32_t reserved_10ac;
    uint32_t reserved_10b0;
    uint32_t reserved_10b4;
    uint32_t reserved_10b8;
    uint32_t reserved_10bc;
    uint32_t reserved_10c0;
    uint32_t reserved_10c4;
    uint32_t reserved_10c8;
    uint32_t reserved_10cc;
    uint32_t reserved_10d0;
    uint32_t reserved_10d4;
    union {
        struct {
            uint32_t link_mode : 1;  /*该位指示链路的当前操作模式：1’b0：半双工模式。1’b1：全双工模式。*/
            uint32_t link_speed : 2; /*该位表示链路的当前速度：2’b00:2.5 MHz。2’b01:25兆赫。2’b10:125兆赫。*/
            uint32_t reserved3 : 1;
            uint32_t jabber_timeout : 1; /*该位指示在接收的帧中是否存在抖动超时错误（1’b1）。*/
            uint32_t reserved5 : 1;
            uint32_t reserved6 : 10;
            uint32_t reserved16 : 1;
            uint32_t reserved17 : 15;
        };
        uint32_t val;
    } emaccstatus;
    union {
        struct {
            uint32_t wdogto : 14; /*当设置了位[16]（PWE）并且重置了EMACCONFIG_REG的位[23]（WD）时，该字段用作接收帧的看门狗超时。如果接收帧的长度超过该字段的值，则终止该帧并将其声明为错误帧。*/
            uint32_t reserved14 : 2;
            uint32_t pwdogen : 1; /*当该位被设置并且EMACCONFIG_REG的位[23]（WD）被重置时，WTO字段（位[13:0]）被用作接收帧的看门狗超时。当该位被清除时，接收帧的看门狗超时由EMACCONFIG_REG中位[23]（WD）和位[20]（JE）的设置控制。*/
            uint32_t reserved17 : 15;
        };
        uint32_t val;
    } emacwdogto;
} emac_mac_dev_t;

extern emac_mac_dev_t EMAC_MAC;

#ifdef __cplusplus
}
#endif

