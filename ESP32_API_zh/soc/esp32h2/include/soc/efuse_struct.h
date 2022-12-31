// 版权所有2020 Espressif Systems（上海）私人有限公司
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
#ifndef _SOC_EFUSE_STRUCT_H_
#define _SOC_EFUSE_STRUCT_H_
#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct efuse_dev_s {
    uint32_t pgm_data0;                                          /*存储要编程的数据的寄存器0。*/
    union {
        struct {
            uint32_t rd_dis:                      7;             /*设置此位以禁用从BlOCK4-10读取。*/
            uint32_t dis_rtc_ram_boot:            1;             /*设置此位以禁用从RTC RAM启动。*/
            uint32_t dis_icache:                  1;             /*设置此位以禁用Icache。*/
            uint32_t dis_usb_jtag:                1;             /*设置此位以禁用usb设备模块中的jtag的usb开关功能。*/
            uint32_t dis_download_icache:         1;             /*将此位设置为在下载模式下禁用Icache（boot_mode[3:0]为0 1 2 3 6 7）。*/
            uint32_t dis_usb_device:              1;             /*设置此位以禁用usb设备。*/
            uint32_t dis_force_download:          1;             /*设置此位以禁用强制芯片进入下载模式的功能。*/
            uint32_t dis_usb:                     1;             /*设置此位以禁用USB功能。*/
            uint32_t dis_can:                     1;             /*设置此位以禁用CAN功能。*/
            uint32_t jtag_sel_enable:             1;             /*当reg_dis_usb_jtag和reg_dis_pad_jtag都等于0时，设置此位以启用通过打包gpio10在usb_to_jtag与pad_to_jtag之间的选择。*/
            uint32_t soft_dis_jtag:               3;             /*设置这些位以软方式禁用JTAG（奇数1表示禁用）。JTAG可在HMAC模块中启用。*/
            uint32_t dis_pad_jtag:                1;             /*设置此位以禁用JTAG。JTAG被永久禁用。*/
            uint32_t dis_download_manual_encrypt: 1;             /*设置此位以在下载引导模式下禁用闪存加密。*/
            uint32_t usb_drefh:                   2;             /*控制单端输入阈值vrefh 1.76 V至2 V，步长为80 mV，存储在eFuse中。*/
            uint32_t usb_drefl:                   2;             /*控制存储在eFuse中的单端输入阈值vrefl 0.8 V至1.04 V，步长为80 mV。*/
            uint32_t usb_exchg_pins:              1;             /*设置此位以交换USB D+和D-引脚。*/
            uint32_t vdd_spi_as_gpio:             1;             /*将此位设置为vdd-spi-pin函数作为gpio。*/
            uint32_t btlc_gpio_enable:            2;             /*启用btlc gpio。*/
            uint32_t powerglitch_en:              1;             /*设置此位以启用电源故障功能。*/
            uint32_t power_glitch_dsense:         2;             /*电源故障的延迟配置示例。*/
        };
        uint32_t val;
    } pgm_data1;
    union {
        struct {
            uint32_t rpt4_reserved2:         16;                 /*保留（用于四种备份方法）。*/
            uint32_t wat_delay_sel:           2;                 /*以慢时钟周期为单位选择RTC看门狗超时阈值。0: 40000. 1: 80000. 2: 160000. 3:320000.*/
            uint32_t spi_boot_crypt_cnt:      3;                 /*设置此位以启用SPI引导加密/解密。奇数1：启用。偶数1：禁用。*/
            uint32_t secure_boot_key_revoke0: 1;                 /*设置此位以启用撤销第一个安全启动密钥。*/
            uint32_t secure_boot_key_revoke1: 1;                 /*设置此位以启用撤销第二个安全启动密钥。*/
            uint32_t secure_boot_key_revoke2: 1;                 /*设置此位以启用撤销第三个安全启动密钥。*/
            uint32_t key_purpose_0:           4;                 /*密钥0的目的。*/
            uint32_t key_purpose_1:           4;                 /*钥匙1的用途。*/
        };
        uint32_t val;
    } pgm_data2;
    union {
        struct {
            uint32_t key_purpose_2:                 4;           /*钥匙2的用途。*/
            uint32_t key_purpose_3:                 4;           /*钥匙3的用途。*/
            uint32_t key_purpose_4:                 4;           /*钥匙4的用途。*/
            uint32_t key_purpose_5:                 4;           /*钥匙5的用途。*/
            uint32_t rpt4_reserved3:                4;           /*保留（用于四种备份方法）。*/
            uint32_t secure_boot_en:                1;           /*设置此位以启用安全引导。*/
            uint32_t secure_boot_aggressive_revoke: 1;           /*设置此位以启用撤消攻击性安全引导。*/
            uint32_t rpt4_reserved0:                6;           /*保留（用于四种备份方法）。*/
            uint32_t flash_tpuw:                    4;           /*以毫秒为单位配置通电后的闪存等待时间。如果该值小于15，则等待时间为可配置值*/
        };
        uint32_t val;
    } pgm_data3;
    union {
        struct {
            uint32_t dis_download_mode:        1;                /*将此位设置为禁用下载模式（boot_mode[3:0]=0 1 2 3 6 7）。*/
            uint32_t dis_legacy_spi_boot:      1;                /*设置此位以禁用传统SPI引导模式（boot_mode[3:0]=4）。*/
            uint32_t uart_print_channel:       1;                /*选择默认UART打印通道。0:UART0.1:UART1。*/
            uint32_t flash_ecc_mode:           1;                /*在ROM 0中设置ECC模式：ROM将启用Flash ECC 16至18字节模式。1： ROM将使用16至17字节模式。*/
            uint32_t dis_usb_download_mode:    1;                /*设置此位以通过USB禁用UART下载模式。*/
            uint32_t enable_security_download: 1;                /*设置此位以启用安全UART下载模式。*/
            uint32_t uart_print_control:       2;                /*设置默认UARTboot消息输出模式。00：已启用。01：复位时GPIO8低时启用。10： 重置时GPIO8为高电平时启用。11： 禁用。*/
            uint32_t pin_power_selection:      1;                /*ROM代码中的GPIO33-GPIO37电源选择。0:VDD3P3_CPU。1： VDD_SPI。*/
            uint32_t flash_type:               1;                /*设置SPI闪存的最大行数。0：四行。1： 八行。*/
            uint32_t flash_page_size:          2;                /*设置Flash页面大小。*/
            uint32_t flash_ecc_en:             1;                /*设置1以启用ECC进行闪存引导。*/
            uint32_t force_send_resume:        1;                /*设置此位以强制ROM代码在SPI引导期间发送恢复命令。*/
            uint32_t secure_version:          16;                /*安全版本（由ESP-IDF防回滚功能使用）。*/
            uint32_t rpt4_reserved1:           2;                /*保留（用于四种备份方法）。*/
        };
        uint32_t val;
    } pgm_data4;
    union {
        struct {
            uint32_t rpt4_reserved4:24;                          /*保留（用于四种备份方法）。*/
            uint32_t reserved24:     8;                          /*保留。*/
        };
        uint32_t val;
    } pgm_data5;
    uint32_t pgm_data6;                                          /*存储要编程的数据的寄存器6。*/
    uint32_t pgm_data7;                                          /*存储要编程的数据的寄存器7。*/
    uint32_t pgm_check_value0;                                   /*寄存器0，用于存储要编程的RS代码。*/
    uint32_t pgm_check_value1;                                   /*存储要编程的RS代码的寄存器1。*/
    uint32_t pgm_check_value2;                                   /*存储要编程的RS代码的寄存器2。*/
    uint32_t rd_wr_dis;                                          /*BLOCK0数据寄存器$n。*/
    union {
        struct {
            uint32_t rd_dis:                      7;             /*RD_DIS的值。*/
            uint32_t rpt4_reserved5:              1;             /*保留*/
            uint32_t dis_icache:                  1;             /*DIS_ICACHE的值。*/
            uint32_t dis_usb_jtag:                1;             /*DIS_USB_JTAG的值。*/
            uint32_t dis_download_icache:         1;             /*DIS_DOWNLOAD_CACHE的值。*/
            uint32_t dis_usb_device:              1;             /*DIS_USB_DEVICE的值。*/
            uint32_t dis_force_download:          1;             /*DIS_FORCE_DOWNLOAD的值。*/
            uint32_t dis_usb:                     1;             /*DIS_USB的值。*/
            uint32_t dis_can:                     1;             /*DIS_CAN的值。*/
            uint32_t jtag_sel_enable:             1;             /*JTAG_SEL_ENABLE的值。*/
            uint32_t soft_dis_jtag:               3;             /*SOFT_DIS_JTAG的值。*/
            uint32_t dis_pad_jtag:                1;             /*DIS_PAD_JTAG的值。*/
            uint32_t dis_download_manual_encrypt: 1;             /*DIS_DOWNLOAD_MANUAL_ENCRYPT的值。*/
            uint32_t usb_drefh:                   2;             /*USB_DREFH的值。*/
            uint32_t usb_drefl:                   2;             /*USB_DREFL的值。*/
            uint32_t usb_exchg_pins:              1;             /*USB_EXCHG_PINS的值。*/
            uint32_t vdd_spi_as_gpio:             1;             /*VDD_SPI_AS_GPIO的值。*/
            uint32_t btlc_gpio_enable:            2;             /*BTLC_GPIO_ENABLE的值。*/
            uint32_t powerglitch_en:              1;             /*POWERGLITCH_EN的值。*/
            uint32_t power_glitch_dsense:         2;             /*POWER_GLITCH_DSENSE的值。*/
        };
        uint32_t val;
    } rd_repeat_data0;
    union {
        struct {
            uint32_t rpt4_reserved2:         16;                 /*保留。*/
            uint32_t wdt_delay_sel:           2;                 /*WDT_DELAY_SEL的值。*/
            uint32_t spi_boot_crypt_cnt:      3;                 /*SPI_BOOT_CRYPT_CNT的值。*/
            uint32_t secure_boot_key_revoke0: 1;                 /*SECURE_BOOT_KEY_REVOKE0的值。*/
            uint32_t secure_boot_key_revoke1: 1;                 /*SECURE_BOOT_KEY_REVOKE1的值。*/
            uint32_t secure_boot_key_revoke2: 1;                 /*SECURE_BOOT_KEY_REVOKE2的值。*/
            uint32_t key_purpose_0:           4;                 /*KEY_PURPOSE_0的值。*/
            uint32_t key_purpose_1:           4;                 /*KEY_PURPOSE_1的值。*/
        };
        uint32_t val;
    } rd_repeat_data1;
    union {
        struct {
            uint32_t key_purpose_2:                 4;           /*KEY_PURPOSE_2的值。*/
            uint32_t key_purpose_3:                 4;           /*KEY_PURPOSE_3的值。*/
            uint32_t key_purpose_4:                 4;           /*KEY_PURPOSE_4的值。*/
            uint32_t key_purpose_5:                 4;           /*KEY_PURPOSE_5的值。*/
            uint32_t rpt4_reserved3:                4;           /*保留。*/
            uint32_t secure_boot_en:                1;           /*SECURE_BOOT_EN的值。*/
            uint32_t secure_boot_aggressive_revoke: 1;           /*SECURE_BOOT_AGRESSIVE_REVOKE的值。*/
            uint32_t rpt4_reserved0:                6;           /*保留。*/
            uint32_t flash_tpuw:                    4;           /*FLASH_TPUW的值。*/
        };
        uint32_t val;
    } rd_repeat_data2;
    union {
        struct {
            uint32_t dis_download_mode:        1;                /*DIS_DOWNLOAD_MODE的值。*/
            uint32_t dis_legacy_spi_boot:      1;                /*DIS_LEGACY_SPI_BOOT的值。*/
            uint32_t uart_print_channel:       1;                /*UART_PRINT_CHANNEL的值。*/
            uint32_t flash_ecc_mode:           1;                /*FLASH_ECC_MODE的值。*/
            uint32_t dis_usb_download_mode:    1;                /*DIS_USB_DOWNLOAD_MODE的值。*/
            uint32_t enable_security_download: 1;                /*ENABLE_SECURITY_DOWNLOAD的值。*/
            uint32_t uart_print_control:       2;                /*UART_PRINT_CONTROL的值。*/
            uint32_t pin_power_selection:      1;                /*PIN_POWER_SELECTION的值。*/
            uint32_t flash_type:               1;                /*FLASH_TYPE的值。*/
            uint32_t flash_page_size:          2;                /*FLASH_PAGE_SIZE的值。*/
            uint32_t flash_ecc_en:             1;                /*FLASH_ECC_EN的值。*/
            uint32_t force_send_resume:        1;                /*FORCE_SEND_RESUME的值。*/
            uint32_t secure_version:          16;                /*SECURE_VERSION的值。*/
            uint32_t rpt4_reserved1:           2;                /*保留。*/
        };
        uint32_t val;
    } rd_repeat_data3;
    union {
        struct {
            uint32_t rpt4_reserved4:24;                          /*保留。*/
            uint32_t reserved24:     8;                          /*保留。*/
        };
        uint32_t val;
    } rd_repeat_data4;
    uint32_t rd_mac_spi_sys_0;                                   /*BLOCK1数据寄存器$n。*/
    union {
        struct {
            uint32_t mac_1:         16;                          /*存储MAC地址的高16位。*/
            uint32_t spi_pad_conf_0:16;                          /*存储SPI_PAD_CONF的第0部分。*/
        };
        uint32_t val;
    } rd_mac_spi_sys_1;
    uint32_t rd_mac_spi_sys_2;                                   /*BLOCK1数据寄存器$n。*/
    union {
        struct {
            uint32_t spi_pad_conf_2:  18;                        /*存储SPI_PAD_CONF的第二部分。*/
            uint32_t sys_data_part0_0:14;                        /*存储系统数据第0部分的前14位。*/
        };
        uint32_t val;
    } rd_mac_spi_sys_3;
    uint32_t rd_mac_spi_sys_4;                                   /*BLOCK1数据寄存器$n。*/
    uint32_t rd_mac_spi_sys_5;                                   /*BLOCK1数据寄存器$n。*/
    uint32_t rd_sys_part1_data0;                                 /*注册BLOCK2（系统）的$n。*/
    uint32_t rd_sys_part1_data1;                                 /*注册BLOCK2（系统）的$n。*/
    uint32_t rd_sys_part1_data2;                                 /*注册BLOCK2（系统）的$n。*/
    uint32_t rd_sys_part1_data3;                                 /*注册BLOCK2（系统）的$n。*/
    uint32_t rd_sys_part1_data4;                                 /*注册BLOCK2（系统）的$n。*/
    uint32_t rd_sys_part1_data5;                                 /*注册BLOCK2（系统）的$n。*/
    uint32_t rd_sys_part1_data6;                                 /*注册BLOCK2（系统）的$n。*/
    uint32_t rd_sys_part1_data7;                                 /*注册BLOCK2（系统）的$n。*/
    uint32_t rd_usr_data0;                                       /*注册BLOCK3的$n（用户）。*/
    uint32_t rd_usr_data1;                                       /*注册BLOCK3的$n（用户）。*/
    uint32_t rd_usr_data2;                                       /*注册BLOCK3的$n（用户）。*/
    uint32_t rd_usr_data3;                                       /*注册BLOCK3的$n（用户）。*/
    uint32_t rd_usr_data4;                                       /*注册BLOCK3的$n（用户）。*/
    uint32_t rd_usr_data5;                                       /*注册BLOCK3的$n（用户）。*/
    uint32_t rd_usr_data6;                                       /*注册BLOCK3的$n（用户）。*/
    uint32_t rd_usr_data7;                                       /*注册BLOCK3的$n（用户）。*/
    uint32_t rd_key0_data0;                                      /*注册BLOCK4（KEY0）的$n。*/
    uint32_t rd_key0_data1;                                      /*注册BLOCK4（KEY0）的$n。*/
    uint32_t rd_key0_data2;                                      /*注册BLOCK4（KEY0）的$n。*/
    uint32_t rd_key0_data3;                                      /*注册BLOCK4（KEY0）的$n。*/
    uint32_t rd_key0_data4;                                      /*注册BLOCK4（KEY0）的$n。*/
    uint32_t rd_key0_data5;                                      /*注册BLOCK4（KEY0）的$n。*/
    uint32_t rd_key0_data6;                                      /*注册BLOCK4（KEY0）的$n。*/
    uint32_t rd_key0_data7;                                      /*注册BLOCK4（KEY0）的$n。*/
    uint32_t rd_key1_data0;                                      /*注册BLOCK5（KEY1）的$n。*/
    uint32_t rd_key1_data1;                                      /*注册BLOCK5（KEY1）的$n。*/
    uint32_t rd_key1_data2;                                      /*注册BLOCK5（KEY1）的$n。*/
    uint32_t rd_key1_data3;                                      /*注册BLOCK5（KEY1）的$n。*/
    uint32_t rd_key1_data4;                                      /*注册BLOCK5（KEY1）的$n。*/
    uint32_t rd_key1_data5;                                      /*注册BLOCK5（KEY1）的$n。*/
    uint32_t rd_key1_data6;                                      /*注册BLOCK5（KEY1）的$n。*/
    uint32_t rd_key1_data7;                                      /*注册BLOCK5（KEY1）的$n。*/
    uint32_t rd_key2_data0;                                      /*注册BLOCK6（KEY2）的$n。*/
    uint32_t rd_key2_data1;                                      /*注册BLOCK6（KEY2）的$n。*/
    uint32_t rd_key2_data2;                                      /*注册BLOCK6（KEY2）的$n。*/
    uint32_t rd_key2_data3;                                      /*注册BLOCK6（KEY2）的$n。*/
    uint32_t rd_key2_data4;                                      /*注册BLOCK6（KEY2）的$n。*/
    uint32_t rd_key2_data5;                                      /*注册BLOCK6（KEY2）的$n。*/
    uint32_t rd_key2_data6;                                      /*注册BLOCK6（KEY2）的$n。*/
    uint32_t rd_key2_data7;                                      /*注册BLOCK6（KEY2）的$n。*/
    uint32_t rd_key3_data0;                                      /*注册BLOCK7（KEY3）的$n。*/
    uint32_t rd_key3_data1;                                      /*注册BLOCK7（KEY3）的$n。*/
    uint32_t rd_key3_data2;                                      /*注册BLOCK7（KEY3）的$n。*/
    uint32_t rd_key3_data3;                                      /*注册BLOCK7（KEY3）的$n。*/
    uint32_t rd_key3_data4;                                      /*注册BLOCK7（KEY3）的$n。*/
    uint32_t rd_key3_data5;                                      /*注册BLOCK7（KEY3）的$n。*/
    uint32_t rd_key3_data6;                                      /*注册BLOCK7（KEY3）的$n。*/
    uint32_t rd_key3_data7;                                      /*注册BLOCK7（KEY3）的$n。*/
    uint32_t rd_key4_data0;                                      /*注册BLOCK8（KEY4）的$n。*/
    uint32_t rd_key4_data1;                                      /*注册BLOCK8（KEY4）的$n。*/
    uint32_t rd_key4_data2;                                      /*注册BLOCK8（KEY4）的$n。*/
    uint32_t rd_key4_data3;                                      /*注册BLOCK8（KEY4）的$n。*/
    uint32_t rd_key4_data4;                                      /*注册BLOCK8（KEY4）的$n。*/
    uint32_t rd_key4_data5;                                      /*注册BLOCK8（KEY4）的$n。*/
    uint32_t rd_key4_data6;                                      /*注册BLOCK8（KEY4）的$n。*/
    uint32_t rd_key4_data7;                                      /*注册BLOCK8（KEY4）的$n。*/
    uint32_t rd_key5_data0;                                      /*注册BLOCK9（KEY5）的$n。*/
    uint32_t rd_key5_data1;                                      /*注册BLOCK9（KEY5）的$n。*/
    uint32_t rd_key5_data2;                                      /*注册BLOCK9（KEY5）的$n。*/
    uint32_t rd_key5_data3;                                      /*注册BLOCK9（KEY5）的$n。*/
    uint32_t rd_key5_data4;                                      /*注册BLOCK9（KEY5）的$n。*/
    uint32_t rd_key5_data5;                                      /*注册BLOCK9（KEY5）的$n。*/
    uint32_t rd_key5_data6;                                      /*注册BLOCK9（KEY5）的$n。*/
    uint32_t rd_key5_data7;                                      /*注册BLOCK9（KEY5）的$n。*/
    uint32_t rd_sys_part2_data0;                                 /*注册BLOCK10（系统）的$n。*/
    uint32_t rd_sys_part2_data1;                                 /*注册BLOCK9（KEY5）的$n。*/
    uint32_t rd_sys_part2_data2;                                 /*注册BLOCK10（系统）的$n。*/
    uint32_t rd_sys_part2_data3;                                 /*注册BLOCK10（系统）的$n。*/
    uint32_t rd_sys_part2_data4;                                 /*注册BLOCK10（系统）的$n。*/
    uint32_t rd_sys_part2_data5;                                 /*注册BLOCK10（系统）的$n。*/
    uint32_t rd_sys_part2_data6;                                 /*注册BLOCK10（系统）的$n。*/
    uint32_t rd_sys_part2_data7;                                 /*注册BLOCK10（系统）的$n。*/
    union {
        struct {
            uint32_t rd_dis_err:                      7;         /*如果RD_DIS中的任何位为1，则表示编程错误。*/
            uint32_t rpt4_reserved5_err:              1;         /*如果RPT4_RESERVED5为1，则表示编程错误。*/
            uint32_t dis_icache_err:                  1;         /*如果DIS_ICACHE为1，则表示编程错误。*/
            uint32_t dis_usb_jtag_err:                1;         /*如果DIS_USB_JTAG为1，则表示编程错误。*/
            uint32_t dis_download_icache:             1;         /*如果DIS_DOWNLOAD_CACHE为1，则表示编程错误。*/
            uint32_t dis_usb_device_err:              1;         /*如果DIS_USB_DEVICE为1，则表示编程错误。*/
            uint32_t dis_force_download_err:          1;         /*如果DIS_FORCE_DOWNLOAD为1，则表示编程错误。*/
            uint32_t dis_usb_err:                     1;         /*如果DIS_USB为1，则表示编程错误。*/
            uint32_t dis_can_err:                     1;         /*如果DIS_CAN为1，则表示编程错误。*/
            uint32_t jtag_sel_enable_err:             1;         /*如果JTAG_SEL_ENABLE为1，则表示编程错误。*/
            uint32_t soft_dis_jtag_err:               3;         /*如果SOFT_DIS_JTAG为1，则表示编程错误。*/
            uint32_t dis_pad_jtag_err:                1;         /*如果DIS_PAD_JTAG为1，则表示编程错误。*/
            uint32_t dis_download_manual_encrypt_err: 1;         /*如果DIS_DOWNLOAD_MANUAL_ENCRYPT为1，则表示编程错误。*/
            uint32_t usb_drefh_err:                   2;         /*如果USB_DREFH中的任何位为1，则表示编程错误。*/
            uint32_t usb_drefl_err:                   2;         /*如果USB_DREFL中的任何位为1，则表示编程错误。*/
            uint32_t usb_exchg_pins_err:              1;         /*如果USB_EXCHG_PINS为1，则表示编程错误。*/
            uint32_t vdd_spi_as_gpio_err:             1;         /*如果VDD_SPI_AS_GPIO为1，则表示编程错误。*/
            uint32_t btlc_gpio_enable_err:            2;         /*如果BTLC_GPIO_ENABLE中的任何位为1，则表示编程错误。*/
            uint32_t powerglitch_en_err:              1;         /*如果POWERGLITCH_EN为1，则表示编程错误。*/
            uint32_t power_glitch_dsense_err:         2;         /*如果POWER_GLITCH_DSENSE中的任何位为1，则表示编程错误。*/
        };
        uint32_t val;
    } rd_repeat_err0;
    union {
        struct {
            uint32_t rpt4_reserved2_err:         16;             /*保留。*/
            uint32_t wdt_delay_sel_err:           2;             /*如果WDT_DELAY_SEL中的任何位为1，则表示编程错误。*/
            uint32_t spi_boot_crypt_cnt_err:      3;             /*如果SPI_BOOT_CRYPT_CNT中的任何位为1，则表示编程错误。*/
            uint32_t secure_boot_key_revoke0_err: 1;             /*如果SECURE_BOOT_KEY_REVOKE0为1，则表示编程错误。*/
            uint32_t secure_boot_key_revoke1_err: 1;             /*如果SECURE_BOOT_KEY_REVOKE1为1，则表示编程错误。*/
            uint32_t secure_boot_key_revoke2_err: 1;             /*如果SECURE_BOOT_KEY_REVOKE2为1，则表示编程错误。*/
            uint32_t key_purpose_0_err:           4;             /*如果KEY_PURPOSE_0中的任何位为1，则表示编程错误。*/
            uint32_t key_purpose_1_err:           4;             /*如果KEY_PURPOSE_1中的任何位为1，则表示编程错误。*/
        };
        uint32_t val;
    } rd_repeat_err1;
    union {
        struct {
            uint32_t key_purpose_2_err:                 4;       /*如果KEY_PURPOSE_2中的任何位为1，则表示编程错误。*/
            uint32_t key_purpose_3_err:                 4;       /*如果KEY_PURPOSE_3中的任何位为1，则表示编程错误。*/
            uint32_t key_purpose_4_err:                 4;       /*如果KEY_PURPOSE_4中的任何位为1，则表示编程错误。*/
            uint32_t key_purpose_5_err:                 4;       /*如果KEY_PURPOSE_5中的任何位为1，则表示编程错误。*/
            uint32_t rpt4_reserved3_err:                4;       /*保留。*/
            uint32_t secure_boot_en_err:                1;       /*如果SECURE_BOOT_EN为1，则表示编程错误。*/
            uint32_t secure_boot_aggressive_revoke_err: 1;       /*如果SECURE_BOOT_AGRESSIVE_REVOKE为1，则表示编程错误。*/
            uint32_t rpt4_reserved0_err:                6;       /*保留。*/
            uint32_t flash_tpuw_err:                    4;       /*如果FLASH_TPUM中的任何位为1，则表示编程错误。*/
        };
        uint32_t val;
    } rd_repeat_err2;
    union {
        struct {
            uint32_t dis_download_mode_err:        1;            /*如果DIS_DOWNLOAD_MODE为1，则表示编程错误。*/
            uint32_t dis_legacy_spi_boot_err:      1;            /*如果DIS_LEGACY_SPI_BOOT为1，则表示编程错误。*/
            uint32_t uart_print_channel_err:       1;            /*如果UART_PRINT_CHANNEL为1，则表示编程错误。*/
            uint32_t flash_ecc_mode_err:           1;            /*如果FLASH_ECC_MODE为1，则表示编程错误。*/
            uint32_t dis_usb_download_mode_err:    1;            /*如果DIS_USB_DOWNLOAD_MODE为1，则表示编程错误。*/
            uint32_t enable_security_download_err: 1;            /*如果ENABLE_SECURITY_DOWNLOAD为1，则表示编程错误。*/
            uint32_t uart_print_control_err:       2;            /*如果UART_PRINT_CONTROL中的任何位为1，则表示编程错误。*/
            uint32_t pin_power_selection_err:      1;            /*如果PIN_POWER_SELECTION为1，则表示编程错误。*/
            uint32_t flash_type_err:               1;            /*如果FLASH_TYPE为1，则表示编程错误。*/
            uint32_t flash_page_size:              2;            /*如果FLASH_PAGE_SIZE中的任何位为1，则表示编程错误。*/
            uint32_t flash_ecc_en:                 1;            /*如果FLASH_ECC_EN_ERR为1，则表示编程错误。*/
            uint32_t force_send_resume_err:        1;            /*如果FORCE_SEND_RESUME为1，则表示编程错误。*/
            uint32_t secure_version_err:          16;            /*如果SECURE_VERSION中的任何位为1，则表示编程错误。*/
            uint32_t rpt4_reserved1_err:           2;            /*保留。*/
        };
        uint32_t val;
    } rd_repeat_err3;
    union {
        struct {
            uint32_t rpt4_reserved4_err:24;                      /*保留。*/
            uint32_t reserved24:         8;                      /*保留。*/
        };
        uint32_t val;
    } rd_repeat_err4;
    uint32_t reserved_190;
    uint32_t reserved_194;
    uint32_t reserved_198;
    uint32_t reserved_19c;
    uint32_t reserved_1a0;
    uint32_t reserved_1a4;
    uint32_t reserved_1a8;
    uint32_t reserved_1ac;
    uint32_t reserved_1b0;
    uint32_t reserved_1b4;
    uint32_t reserved_1b8;
    uint32_t reserved_1bc;
    union {
        struct {
            uint32_t mac_spi_8m_err_num: 3;                      /*该信号的值表示错误字节数。*/
            uint32_t mac_spi_8m_fail:    1;                      /*0：表示无故障，MAC_SPI_8M数据可靠1：表示编程用户数据失败，错误字节数超过6。*/
            uint32_t sys_part1_num:      3;                      /*该信号的值表示错误字节数。*/
            uint32_t sys_part1_fail:     1;                      /*0：表示无故障，系统part1的数据可靠1：表示编程用户数据失败，错误字节数超过6。*/
            uint32_t usr_data_err_num:   3;                      /*该信号的值表示错误字节数。*/
            uint32_t usr_data_fail:      1;                      /*0：表示无故障，用户数据可靠1：表示编程用户数据失败，错误字节数超过6。*/
            uint32_t key0_err_num:       3;                      /*该信号的值表示错误字节数。*/
            uint32_t key0_fail:          1;                      /*0：表示没有失败，密钥$n的数据可靠1：表示编程密钥$n失败，错误字节数超过6。*/
            uint32_t key1_err_num:       3;                      /*该信号的值表示错误字节数。*/
            uint32_t key1_fail:          1;                      /*0：表示没有失败，密钥$n的数据可靠1：表示编程密钥$n失败，错误字节数超过6。*/
            uint32_t key2_err_num:       3;                      /*该信号的值表示错误字节数。*/
            uint32_t key2_fail:          1;                      /*0：表示没有失败，密钥$n的数据可靠1：表示编程密钥$n失败，错误字节数超过6。*/
            uint32_t key3_err_num:       3;                      /*该信号的值表示错误字节数。*/
            uint32_t key3_fail:          1;                      /*0：表示没有失败，密钥$n的数据可靠1：表示编程密钥$n失败，错误字节数超过6。*/
            uint32_t key4_err_num:       3;                      /*该信号的值表示错误字节数。*/
            uint32_t key4_fail:          1;                      /*0：表示没有失败，密钥$n的数据可靠1：表示编程密钥$n失败，错误字节数超过6。*/
        };
        uint32_t val;
    } rd_rs_err0;
    union {
        struct {
            uint32_t key5_err_num:      3;                       /*该信号的值表示错误字节数。*/
            uint32_t key5_fail:         1;                       /*0：表示无故障，KEY5的数据可靠1：表示编程用户数据失败，错误字节数超过6。*/
            uint32_t sys_part2_err_num: 3;                       /*该信号的值表示错误字节数。*/
            uint32_t sys_part2_fail:    1;                       /*0：表示无故障，系统部件2的数据可靠1：表示编程用户数据失败，错误字节数超过6。*/
            uint32_t reserved8:        24;                       /*保留。*/
        };
        uint32_t val;
    } rd_rs_err1;
    union {
        struct {
            uint32_t mem_force_pd:     1;                        /*设置此位以强制eFuse SRAM进入省电模式。*/
            uint32_t mem_clk_force_on: 1;                        /*设置此位并强制激活eFuse SRAM的时钟信号。*/
            uint32_t mem_force_pu:     1;                        /*设置此位以强制eFuse SRAM进入工作模式。*/
            uint32_t reserved3:       13;                        /*保留。*/
            uint32_t clk_en:           1;                        /*设置此位并强制启用eFuse存储器的时钟信号。*/
            uint32_t reserved17:      15;                        /*保留。*/
        };
        uint32_t val;
    } clk;
    union {
        struct {
            uint32_t op_code:   16;                              /*0x5A5A：操作编程命令0x5AA5：操作读取命令。*/
            uint32_t reserved16:16;                              /*保留。*/
        };
        uint32_t val;
    } conf;
    union {
        struct {
            uint32_t state:            4;                        /*指示eFuse状态机的状态。*/
            uint32_t otp_load_sw:      1;                        /*OTP_LOAD_SW的值。*/
            uint32_t otp_vddq_c_sync2: 1;                        /*OTP_VDDQ_C_SYNC2的值。*/
            uint32_t otp_strobe_sw:    1;                        /*OTP_STROBE_SW的值。*/
            uint32_t otp_csb_sw:       1;                        /*OTP_CSB_SW的值。*/
            uint32_t otp_pgenb_sw:     1;                        /*OTP_PGENB_SW的值。*/
            uint32_t otp_vddq_is_sw:   1;                        /*OTP_VDDQ_IS_SW的值。*/
            uint32_t repeat_err_cnt:   8;                        /*指示编程BLOCK0期间的错误位数。*/
            uint32_t reserved18:      14;                        /*保留。*/
        };
        uint32_t val;
    } status;
    union {
        struct {
            uint32_t read_cmd:   1;                              /*设置此位以发送读取命令。*/
            uint32_t pgm_cmd:    1;                              /*设置此位以发送编程命令。*/
            uint32_t blk_num:    4;                              /*要编程的块的序列号。值0-10分别对应于块号0-10。*/
            uint32_t reserved6: 26;                              /*保留。*/
        };
        uint32_t val;
    } cmd;
    union {
        struct {
            uint32_t read_done:         1;                       /*read_done中断的原始位信号。*/
            uint32_t pgm_done:          1;                       /*pgm_done中断的原始位信号。*/
            uint32_t reserved2:        30;                       /*保留。*/
        };
        uint32_t val;
    } int_raw;
    union {
        struct {
            uint32_t read_done:        1;                        /*read_done中断的状态信号。*/
            uint32_t pgm_done:         1;                        /*pgm_done中断的状态信号。*/
            uint32_t reserved2:       30;                        /*保留。*/
        };
        uint32_t val;
    } int_st;
    union {
        struct {
            uint32_t read_done:         1;                       /*read_done中断的启用信号。*/
            uint32_t pgm_done:          1;                       /*pgm_done中断的启用信号。*/
            uint32_t reserved2:        30;                       /*保留。*/
        };
        uint32_t val;
    } int_ena;
    union {
        struct {
            uint32_t read_done:         1;                       /*read_done中断的清除信号。*/
            uint32_t pgm_done:          1;                       /*pgm_done中断的清除信号。*/
            uint32_t reserved2:        30;                       /*保留。*/
        };
        uint32_t val;
    } int_clr;
    union {
        struct {
            uint32_t dac_clk_div:     8;                         /*控制编程电压上升时钟的分频因子。*/
            uint32_t dac_clk_pad_sel: 1;                         /*别在意。*/
            uint32_t dac_num:         8;                         /*控制编程电压的上升周期。*/
            uint32_t oe_clr:          1;                         /*降低编程电压的电源。*/
            uint32_t reserved18:     14;                         /*保留。*/
        };
        uint32_t val;
    } dac_conf;
    union {
        struct {
            uint32_t reserved0:    24;                           /*配置读取操作的设置时间。*/
            uint32_t read_init_num: 8;                           /*配置eFuse的初始读取时间。*/
        };
        uint32_t val;
    } rd_tim_conf;
    union {
        struct {
            uint32_t reserved0:  8;                              /*配置编程操作的设置时间。*/
            uint32_t pwr_on_num:16;                              /*配置VDDQ的通电时间。*/
            uint32_t reserved24: 8;                              /*保留。*/
        };
        uint32_t val;
    } wr_tim_conf1;
    union {
        struct {
            uint32_t pwr_off_num:16;                             /*配置VDDQ的断电时间。*/
            uint32_t reserved16: 16;                             /*保留。*/
        };
        uint32_t val;
    } wr_tim_conf2;
    uint32_t reserved_1f8;
    union {
        struct {
            uint32_t date:      28;                              /*存储eFuse版本。*/
            uint32_t reserved28: 4;                              /*保留。*/
        };
        uint32_t val;
    } date;
} efuse_dev_t;
extern efuse_dev_t EFUSE;
#ifdef __cplusplus
}
#endif

#endif  /* _SOC_EFUSE_STRUCT_H_ */

