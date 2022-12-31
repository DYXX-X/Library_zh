// 版权所有2017-2021 Espressif Systems（Shanghai）PTE LTD
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
#ifndef _SOC_EXTMEM_STRUCT_H_
#define _SOC_EXTMEM_STRUCT_H_


#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct extmem_dev_s {
    union {
        struct {
            uint32_t dcache_enable                 :    1;  /*该位用于激活数据缓存。0：禁用，1：启用*/
            uint32_t reserved1                     :    1;  /*保留*/
            uint32_t dcache_size_mode              :    1;  /*该位用于配置缓存内存大小。0:32KB，1:64KB*/
            uint32_t dcache_blocksize_mode         :    2;  /*该位用于配置缓存块大小。0:16字节，1:32字节，2:64字节*/
            uint32_t reserved5                     :    27;
        };
        uint32_t val;
    } dcache_ctrl;
    union {
        struct {
            uint32_t dcache_shut_core0_bus         :    1;  /*该位用于禁用core0 dbus，0：启用，1：禁用*/
            uint32_t dcache_shut_core1_bus         :    1;  /*该位用于禁用core1 dbus，0：启用，1：禁用*/
            uint32_t reserved2                     :    30;
        };
        uint32_t val;
    } dcache_ctrl1;
    union {
        struct {
            uint32_t dcache_tag_mem_force_on       :    1;  /*该位用于关闭dcache标签内存的时钟门控。1： 关闭门控，0：打开时钟门控。*/
            uint32_t dcache_tag_mem_force_pd       :    1;  /*该位用于关闭dcache标记内存，0：遵循rtc_lslp_pd，1：关闭电源*/
            uint32_t dcache_tag_mem_force_pu       :    1;  /*该位用于为dcache标记内存加电，0：遵循rtc_lslp_pd，1：加电*/
            uint32_t reserved3                     :    29;
        };
        uint32_t val;
    } dcache_tag_power_ctrl;
    union {
        struct {
            uint32_t dcache_prelock_sct0_en        :    1;  /*该位用于启用预锁定功能的第一部分。*/
            uint32_t dcache_prelock_sct1_en        :    1;  /*该位用于启用预锁定功能的第二部分。*/
            uint32_t reserved2                     :    30;
        };
        uint32_t val;
    } dcache_prelock_ctrl;
    uint32_t dcache_prelock_sct0_addr;
    uint32_t dcache_prelock_sct1_addr;
    union {
        struct {
            uint32_t dcache_prelock_sct1_size      :    16;  /*这些位用于配置数据锁定的第二长度，该长度与DCACHE_PRELOCK_SCT1_ADDR_REG组合*/
            uint32_t dcache_prelock_sct0_size      :    16;  /*这些位用于配置数据锁定的第一个长度，该长度与DCACHE_PRELOCK_SCT0_ADDR_REG组合*/
        };
        uint32_t val;
    } dcache_prelock_sct_size;
    union {
        struct {
            uint32_t dcache_lock_ena               :    1;  /*该位用于启用锁定操作。锁定操作完成后，将由硬件清除。*/
            uint32_t dcache_unlock_ena             :    1;  /*该位用于启用解锁操作。解锁操作完成后，将由硬件清除。*/
            uint32_t dcache_lock_done              :    1;  /*该位用于指示解锁/锁定操作完成。*/
            uint32_t reserved3                     :    29;
        };
        uint32_t val;
    } dcache_lock_ctrl;
    uint32_t dcache_lock_addr;
    union {
        struct {
            uint32_t dcache_lock_size              :    16;  /*这些位用于配置锁定操作的长度。这些位是缓存块的计数。应与DCACHE_LOCK_ADDR_REG组合使用。*/
            uint32_t reserved16                    :    16;
        };
        uint32_t val;
    } dcache_lock_size;
    union {
        struct {
            uint32_t dcache_invalidate_ena         :    1;  /*该位用于启用无效操作。无效操作完成后，将由硬件清除。*/
            uint32_t dcache_writeback_ena          :    1;  /*该位用于启用写回操作。写回操作完成后，它将由硬件清除。*/
            uint32_t dcache_clean_ena              :    1;  /*钻头用于实现清洁操作。清洁操作完成后，将由硬件清除。*/
            uint32_t dcache_sync_done              :    1;  /*该位用于指示清除/写回/无效操作已完成。*/
            uint32_t reserved4                     :    28;
        };
        uint32_t val;
    } dcache_sync_ctrl;
    uint32_t dcache_sync_addr;
    union {
        struct {
            uint32_t dcache_sync_size              :    23;  /*这些位用于配置同步操作的长度。这些位是缓存块的计数。它应与DCACHE_SYNC_ADDR_REG组合。*/
            uint32_t reserved23                    :    9;
        };
        uint32_t val;
    } dcache_sync_size;
    union {
        struct {
            uint32_t dcache_occupy_ena             :    1;  /*该位用于启用占用操作。发出Auot Invalidate Operation后，将由硬件清除。*/
            uint32_t dcache_occupy_done            :    1;  /*该位用于指示占用操作已完成。*/
            uint32_t reserved2                     :    30;
        };
        uint32_t val;
    } dcache_occupy_ctrl;
    uint32_t dcache_occupy_addr;
    union {
        struct {
            uint32_t dcache_occupy_size            :    16;  /*这些位用于配置占用操作的长度。这些位是缓存块的计数。它应与DCACHE_OCCUPY_ADDR_REG组合使用。*/
            uint32_t reserved16                    :    16;
        };
        uint32_t val;
    } dcache_occupy_size;
    union {
        struct {
            uint32_t dcache_preload_ena            :    1;  /*钻头用于启用预加载操作。预加载操作完成后，将由硬件清除。*/
            uint32_t dcache_preload_done           :    1;  /*该位用于指示预加载操作完成。*/
            uint32_t dcache_preload_order          :    1;  /*钻头用于配置预加载操作的方向。1： 降序，0：升序。*/
            uint32_t reserved3                     :    29;
        };
        uint32_t val;
    } dcache_preload_ctrl;
    uint32_t dcache_preload_addr;
    union {
        struct {
            uint32_t dcache_preload_size           :    16;  /*这些位用于配置预加载操作的长度。这些位是缓存块的计数。它应与DCACHE_PRELOAD_ADDR_REG组合使用。。*/
            uint32_t reserved16                    :    16;
        };
        uint32_t val;
    } dcache_preload_size;
    union {
        struct {
            uint32_t dcache_autoload_sct0_ena      :    1;  /*这些位用于启用自动加载操作的第一部分。*/
            uint32_t dcache_autoload_sct1_ena      :    1;  /*这些位用于启用自动加载操作的第二部分。*/
            uint32_t dcache_autoload_ena           :    1;  /*该位用于启用和禁用自动加载操作。它与dcache_autoload_done结合使用。1： 启用，0：禁用。*/
            uint32_t dcache_autoload_done          :    1;  /*该位用于指示自动加载操作已完成。*/
            uint32_t dcache_autoload_order         :    1;  /*这些位用于配置自动加载的方向。1： 降序，0：升序。*/
            uint32_t dcache_autoload_rqst          :    2;  /*这些位用于配置自动加载的触发条件。0/3:缓存未命中，1:缓存命中，2:缓存未命中和命中。*/
            uint32_t dcache_autoload_size          :    2;  /*这些位用于为发出自动加载操作配置缓存块的编号。*/
            uint32_t dcache_autoload_buffer_clear  :    1;  /*该位用于清除dcache中的自动加载缓冲区。*/
            uint32_t reserved10                    :    22;
        };
        uint32_t val;
    } dcache_autoload_ctrl;
    uint32_t dcache_autoload_sct0_addr;
    union {
        struct {
            uint32_t dcache_autoload_sct0_size     :    27;  /*这些位用于配置自动加载操作的第一段的长度。它应该与dcache_autoload_sct0_ena结合使用。*/
            uint32_t reserved27                    :    5;
        };
        uint32_t val;
    } dcache_autoload_sct0_size;
    uint32_t dcache_autoload_sct1_addr;
    union {
        struct {
            uint32_t dcache_autoload_sct1_size     :    27;  /*这些位用于配置自动加载操作的第二段的长度。它应该与dcache_autoload_sct1_ena结合使用。*/
            uint32_t reserved27                    :    5;
        };
        uint32_t val;
    } dcache_autoload_sct1_size;
    union {
        struct {
            uint32_t icache_enable                 :    1;  /*该位用于激活数据缓存。0：禁用，1：启用*/
            uint32_t icache_way_mode               :    1;  /*该位用于配置缓存方式模式。0:4路，1:8路*/
            uint32_t icache_size_mode              :    1;  /*该位用于配置缓存内存大小。0:16KB，1:32KB*/
            uint32_t icache_blocksize_mode         :    1;  /*该位用于配置缓存块大小。0:16字节，1:32字节*/
            uint32_t reserved4                     :    28;
        };
        uint32_t val;
    } icache_ctrl;
    union {
        struct {
            uint32_t icache_shut_core0_bus         :    1;  /*该位用于禁用core0 ibus，0：启用，1：禁用*/
            uint32_t icache_shut_core1_bus         :    1;  /*该位用于禁用core1 ibus，0：启用，1：禁用*/
            uint32_t reserved2                     :    30;
        };
        uint32_t val;
    } icache_ctrl1;
    union {
        struct {
            uint32_t icache_tag_mem_force_on       :    1;  /*该位用于关闭icache标签存储器的时钟门控。1： 关闭门控，0：打开时钟门控。*/
            uint32_t icache_tag_mem_force_pd       :    1;  /*该位用于关闭icache标记内存，0：遵循rtc_lslp，1：关闭电源*/
            uint32_t icache_tag_mem_force_pu       :    1;  /*该位用于为icache标记内存加电，0：遵循rtc_lslp，1：加电*/
            uint32_t reserved3                     :    29;
        };
        uint32_t val;
    } icache_tag_power_ctrl;
    union {
        struct {
            uint32_t icache_prelock_sct0_en        :    1;  /*该位用于启用预锁定功能的第一部分。*/
            uint32_t icache_prelock_sct1_en        :    1;  /*该位用于启用预锁定功能的第二部分。*/
            uint32_t reserved2                     :    30;
        };
        uint32_t val;
    } icache_prelock_ctrl;
    uint32_t icache_prelock_sct0_addr;
    uint32_t icache_prelock_sct1_addr;
    union {
        struct {
            uint32_t icache_prelock_sct1_size      :    16;  /*这些位用于配置数据锁定的第二长度，该长度与ICACHE_PRELOCK_SCT1_ADDR_REG组合*/
            uint32_t icache_prelock_sct0_size      :    16;  /*这些位用于配置数据锁定的第一个长度，该长度与ICACHE_PRELOCK_SCT0_ADDR_REG组合*/
        };
        uint32_t val;
    } icache_prelock_sct_size;
    union {
        struct {
            uint32_t icache_lock_ena               :    1;  /*该位用于启用锁定操作。锁定操作完成后，将由硬件清除。*/
            uint32_t icache_unlock_ena             :    1;  /*该位用于启用解锁操作。解锁操作完成后，将由硬件清除。*/
            uint32_t icache_lock_done              :    1;  /*该位用于指示解锁/锁定操作完成。*/
            uint32_t reserved3                     :    29;
        };
        uint32_t val;
    } icache_lock_ctrl;
    uint32_t icache_lock_addr;
    union {
        struct {
            uint32_t icache_lock_size              :    16;  /*这些位用于配置锁定操作的长度。这些位是缓存块的计数。应与ICACHE_LOCK_ADDR_REG组合使用。*/
            uint32_t reserved16                    :    16;
        };
        uint32_t val;
    } icache_lock_size;
    union {
        struct {
            uint32_t icache_invalidate_ena         :    1;  /*该位用于启用无效操作。无效操作完成后，将由硬件清除。*/
            uint32_t icache_sync_done              :    1;  /*该位用于指示无效操作已完成。*/
            uint32_t reserved2                     :    30;
        };
        uint32_t val;
    } icache_sync_ctrl;
    uint32_t icache_sync_addr;
    union {
        struct {
            uint32_t icache_sync_size              :    23;  /*这些位用于配置同步操作的长度。这些位是缓存块的计数。应与ICACHE_SYNC_ADDR_REG组合使用。*/
            uint32_t reserved23                    :    9;
        };
        uint32_t val;
    } icache_sync_size;
    union {
        struct {
            uint32_t icache_preload_ena            :    1;  /*钻头用于启用预加载操作。预加载操作完成后，将由硬件清除。*/
            uint32_t icache_preload_done           :    1;  /*该位用于指示预加载操作完成。*/
            uint32_t icache_preload_order          :    1;  /*钻头用于配置预加载操作的方向。1： 降序，0：升序。*/
            uint32_t reserved3                     :    29;
        };
        uint32_t val;
    } icache_preload_ctrl;
    uint32_t icache_preload_addr;
    union {
        struct {
            uint32_t icache_preload_size           :    16;  /*这些位用于配置预加载操作的长度。这些位是缓存块的计数。它应与ICACHE_PRELOAD_ADDR_REG组合使用。。*/
            uint32_t reserved16                    :    16;
        };
        uint32_t val;
    } icache_preload_size;
    union {
        struct {
            uint32_t icache_autoload_sct0_ena      :    1;  /*这些位用于启用自动加载操作的第一部分。*/
            uint32_t icache_autoload_sct1_ena      :    1;  /*这些位用于启用自动加载操作的第二部分。*/
            uint32_t icache_autoload_ena           :    1;  /*该位用于启用和禁用自动加载操作。它与icache_autoload_done结合使用。1： 启用，0：禁用。*/
            uint32_t icache_autoload_done          :    1;  /*该位用于指示自动加载操作已完成。*/
            uint32_t icache_autoload_order         :    1;  /*这些位用于配置自动加载的方向。1： 降序，0：升序。*/
            uint32_t icache_autoload_rqst          :    2;  /*这些位用于配置自动加载的触发条件。0/3:缓存未命中，1:缓存命中，2:缓存未命中和命中。*/
            uint32_t icache_autoload_size          :    2;  /*这些位用于为发出自动加载操作配置缓存块的编号。*/
            uint32_t icache_autoload_buffer_clear  :    1;  /*该位用于清除icache中的自动加载缓冲区。*/
            uint32_t reserved10                    :    22;
        };
        uint32_t val;
    } icache_autoload_ctrl;
    uint32_t icache_autoload_sct0_addr;
    union {
        struct {
            uint32_t icache_autoload_sct0_size     :    27;  /*这些位用于配置自动加载操作的第一段的长度。它应该与icache_autoload_sct0_ena结合使用。*/
            uint32_t reserved27                    :    5;
        };
        uint32_t val;
    } icache_autoload_sct0_size;
    uint32_t icache_autoload_sct1_addr;
    union {
        struct {
            uint32_t icache_autoload_sct1_size     :    27;  /*这些位用于配置自动加载操作的第二段的长度。它应该与icache_autoload_sct1_ena结合使用。*/
            uint32_t reserved27                    :    5;
        };
        uint32_t val;
    } icache_autoload_sct1_size;
    uint32_t ibus_to_flash_start_vaddr;
    uint32_t ibus_to_flash_end_vaddr;
    uint32_t dbus_to_flash_start_vaddr;
    uint32_t dbus_to_flash_end_vaddr;
    union {
        struct {
            uint32_t dcache_acs_cnt_clr            :    1;  /*该位用于清除数据缓存计数器。*/
            uint32_t icache_acs_cnt_clr            :    1;  /*钻头用于清除icache计数器。*/
            uint32_t reserved2                     :    30;
        };
        uint32_t val;
    } cache_acs_cnt_clr;
    uint32_t ibus_acs_miss_cnt;
    uint32_t ibus_acs_cnt;
    uint32_t dbus_acs_flash_miss_cnt;
    uint32_t dbus_acs_spiram_miss_cnt;
    uint32_t dbus_acs_cnt;
    union {
        struct {
            uint32_t icache_sync_op_fault          :    1;  /*该位用于通过同步配置故障启用中断。*/
            uint32_t icache_preload_op_fault       :    1;  /*该位用于通过预加载配置故障启用中断。*/
            uint32_t dcache_sync_op_fault          :    1;  /*该位用于通过同步配置故障启用中断。*/
            uint32_t dcache_preload_op_fault       :    1;  /*该位用于通过预加载配置故障启用中断。*/
            uint32_t dcache_write_flash            :    1;  /*该位用于通过dcache尝试写入闪存来启用中断。*/
            uint32_t mmu_entry_fault               :    1;  /*该位用于通过mmu条目故障启用中断。*/
            uint32_t dcache_occupy_exc             :    1;  /*该位用于通过dcache来启用中断，该dcache试图替换一行，该行的所有块都已被占用模式占用。*/
            uint32_t ibus_cnt_ovf                  :    1;  /*该位用于通过ibus计数器溢出启用中断。*/
            uint32_t dbus_cnt_ovf                  :    1;  /*该位用于通过dbus计数器溢出启用中断。*/
            uint32_t reserved9                     :    23;
        };
        uint32_t val;
    } cache_ilg_int_ena;
    union {
        struct {
            uint32_t icache_sync_op_fault          :    1;  /*该位用于清除同步配置故障引起的中断。*/
            uint32_t icache_preload_op_fault       :    1;  /*该位用于清除预加载配置故障导致的中断。*/
            uint32_t dcache_sync_op_fault          :    1;  /*该位用于清除同步配置故障引起的中断。*/
            uint32_t dcache_preload_op_fault       :    1;  /*该位用于清除预加载配置故障导致的中断。*/
            uint32_t dcache_write_flash            :    1;  /*该位用于通过dcache尝试写入闪存来清除中断。*/
            uint32_t mmu_entry_fault               :    1;  /*该位用于清除mmu条目故障引起的中断。*/
            uint32_t dcache_occupy_exc             :    1;  /*该位用于通过dcache清除中断，dcache试图替换一条所有块都已被占用模式占用的线。*/
            uint32_t ibus_cnt_ovf                  :    1;  /*该位用于通过ibus计数器溢出清除中断。*/
            uint32_t dbus_cnt_ovf                  :    1;  /*该位用于清除dbus计数器溢出引起的中断。*/
            uint32_t reserved9                     :    23;
        };
        uint32_t val;
    } cache_ilg_int_clr;
    union {
        struct {
            uint32_t icache_sync_op_fault_st       :    1;  /*该位用于指示同步配置故障导致的中断。*/
            uint32_t icache_preload_op_fault_st    :    1;  /*该位用于指示预加载配置故障导致的中断。*/
            uint32_t dcache_sync_op_fault_st       :    1;  /*该位用于指示同步配置故障导致的中断。*/
            uint32_t dcache_preload_op_fault_st    :    1;  /*该位用于指示预加载配置故障导致的中断。*/
            uint32_t dcache_write_flash_st         :    1;  /*该位用于指示dcache尝试写入闪存时的中断。*/
            uint32_t mmu_entry_fault_st            :    1;  /*该位用于通过mmu条目故障指示中断。*/
            uint32_t dcache_occupy_exc_st          :    1;  /*该位用于通过dcache指示中断，该dcache试图替换一行，该行的所有块都已被占用模式占用。*/
            uint32_t ibus_acs_cnt_ovf_st           :    1;  /*该位用于指示ibus访问闪存/螺旋计数器溢出导致的中断。*/
            uint32_t ibus_acs_miss_cnt_ovf_st      :    1;  /*该位用于指示ibus访问flash/spiram未命中计数器溢出导致的中断。*/
            uint32_t dbus_acs_cnt_ovf_st           :    1;  /*该位用于指示dbus访问闪存/螺旋计数器溢出导致的中断。*/
            uint32_t dbus_acs_flash_miss_cnt_ovf_st:    1;  /*该位用于指示dbus访问闪存未命中计数器溢出导致的中断。*/
            uint32_t dbus_acs_spiram_miss_cnt_ovf_st:    1;  /*该位用于指示dbus访问spiram未命中计数器溢出导致的中断。*/
            uint32_t reserved12                    :    20;
        };
        uint32_t val;
    } cache_ilg_int_st;
    union {
        struct {
            uint32_t core0_ibus_acs_msk_ic         :    1;  /*该位用于通过cpu访问icache启用中断，而相应的ibu被禁用，包括推测访问。*/
            uint32_t core0_ibus_wr_ic              :    1;  /*该位用于启用ibus尝试写入icache的中断*/
            uint32_t core0_ibus_reject             :    1;  /*该位用于在认证失败时启用中断。*/
            uint32_t core0_dbus_acs_msk_dc         :    1;  /*该位用于通过cpu访问dcache启用中断，而相应的dbus被禁用，包括推测访问。*/
            uint32_t core0_dbus_reject             :    1;  /*该位用于在认证失败时启用中断。*/
            uint32_t reserved5                     :    27;
        };
        uint32_t val;
    } core0_acs_cache_int_ena;
    union {
        struct {
            uint32_t core0_ibus_acs_msk_ic         :    1;  /*当禁用相应的ibu或禁用icache（包括推测访问）时，该位用于清除cpu访问icache的中断。*/
            uint32_t core0_ibus_wr_ic              :    1;  /*该位用于清除ibus试图写入icache的中断*/
            uint32_t core0_ibus_reject             :    1;  /*该位用于在验证失败时清除中断。*/
            uint32_t core0_dbus_acs_msk_dc         :    1;  /*当禁用相应的dbus或禁用dcache（包括推测访问）时，该位用于清除cpu访问dcache的中断。*/
            uint32_t core0_dbus_reject             :    1;  /*该位用于在验证失败时清除中断。*/
            uint32_t reserved5                     :    27;
        };
        uint32_t val;
    } core0_acs_cache_int_clr;
    union {
        struct {
            uint32_t core0_ibus_acs_msk_icache_st  :    1;  /*当禁用core0.ibus或禁用icache（包括推测访问）时，该位用于指示cpu访问icache的中断。*/
            uint32_t core0_ibus_wr_icache_st       :    1;  /*该位用于指示ibus尝试写入icache时的中断*/
            uint32_t core0_ibus_reject_st          :    1;  /*该位用于指示认证失败导致的中断。*/
            uint32_t core0_dbus_acs_msk_dcache_st  :    1;  /*当禁用core0_dbus或禁用dcache（包括推测访问）时，该位用于指示cpu访问dcache的中断。*/
            uint32_t core0_dbus_reject_st          :    1;  /*该位用于指示认证失败导致的中断。*/
            uint32_t reserved5                     :    27;
        };
        uint32_t val;
    } core0_acs_cache_int_st;
    union {
        struct {
            uint32_t core1_ibus_acs_msk_ic         :    1;  /*该位用于通过cpu访问icache启用中断，而相应的ibu被禁用，包括推测访问。*/
            uint32_t core1_ibus_wr_ic              :    1;  /*该位用于启用ibus尝试写入icache的中断*/
            uint32_t core1_ibus_reject             :    1;  /*该位用于在认证失败时启用中断。*/
            uint32_t core1_dbus_acs_msk_dc         :    1;  /*该位用于通过cpu访问dcache启用中断，而相应的dbus被禁用，包括推测访问。*/
            uint32_t core1_dbus_reject             :    1;  /*该位用于在认证失败时启用中断。*/
            uint32_t reserved5                     :    27;
        };
        uint32_t val;
    } core1_acs_cache_int_ena;
    union {
        struct {
            uint32_t core1_ibus_acs_msk_ic         :    1;  /*当禁用相应的ibu或禁用icache（包括推测访问）时，该位用于清除cpu访问icache的中断。*/
            uint32_t core1_ibus_wr_ic              :    1;  /*该位用于清除ibus试图写入icache的中断*/
            uint32_t core1_ibus_reject             :    1;  /*该位用于在验证失败时清除中断。*/
            uint32_t core1_dbus_acs_msk_dc         :    1;  /*当禁用相应的dbus或禁用dcache（包括推测访问）时，该位用于清除cpu访问dcache的中断。*/
            uint32_t core1_dbus_reject             :    1;  /*该位用于在验证失败时清除中断。*/
            uint32_t reserved5                     :    27;
        };
        uint32_t val;
    } core1_acs_cache_int_clr;
    union {
        struct {
            uint32_t core1_ibus_acs_msk_icache_st  :    1;  /*当禁用core1_ibus或禁用icache（包括推测访问）时，该位用于指示cpu访问icache的中断。*/
            uint32_t core1_ibus_wr_icache_st       :    1;  /*该位用于指示ibus尝试写入icache时的中断*/
            uint32_t core1_ibus_reject_st          :    1;  /*该位用于指示认证失败导致的中断。*/
            uint32_t core1_dbus_acs_msk_dcache_st  :    1;  /*当禁用core1_dbus或禁用dcache（包括推测访问）时，该位用于指示cpu访问dcache的中断。*/
            uint32_t core1_dbus_reject_st          :    1;  /*该位用于指示认证失败导致的中断。*/
            uint32_t reserved5                     :    27;
        };
        uint32_t val;
    } core1_acs_cache_int_st;
    union {
        struct {
            uint32_t core0_dbus_tag_attr           :    3;  /*当认证失败时，这些位用于指示来自外部存储器的数据的属性。0：无效，1：可执行，2：可读取，4：可写入。*/
            uint32_t core0_dbus_attr               :    3;  /*这些位用于指示验证失败时CPU访问dbus的属性。0：无效，1：可执行，2：可读取，4：可写入。*/
            uint32_t core0_dbus_world              :    1;  /*该位用于指示身份验证失败时CPU访问dbus的情况。0:世界0，1:世界1*/
            uint32_t reserved7                     :    25;
        };
        uint32_t val;
    } core0_dbus_reject_st;
    uint32_t core0_dbus_reject_vaddr;
    union {
        struct {
            uint32_t core0_ibus_tag_attr           :    3;  /*当认证失败时，这些位用于指示来自外部存储器的数据的属性。0：无效，1：可执行，2：可读取，4：可写入。*/
            uint32_t core0_ibus_attr               :    3;  /*这些位用于指示验证失败时CPU访问ibus的属性。0：无效，1：可执行，2：可读取*/
            uint32_t core0_ibus_world              :    1;  /*该位用于指示身份验证失败时CPU访问ibus的世界。0:世界0，1:世界1*/
            uint32_t reserved7                     :    25;
        };
        uint32_t val;
    } core0_ibus_reject_st;
    uint32_t core0_ibus_reject_vaddr;
    union {
        struct {
            uint32_t core1_dbus_tag_attr           :    3;  /*当认证失败时，这些位用于指示来自外部存储器的数据的属性。0：无效，1：可执行，2：可读取，4：可写入。*/
            uint32_t core1_dbus_attr               :    3;  /*这些位用于指示验证失败时CPU访问dbus的属性。0：无效，1：可执行，2：可读取，4：可写入。*/
            uint32_t core1_dbus_world              :    1;  /*该位用于指示身份验证失败时CPU访问dbus的情况。0:世界0，1:世界1*/
            uint32_t reserved7                     :    25;
        };
        uint32_t val;
    } core1_dbus_reject_st;
    uint32_t core1_dbus_reject_vaddr;
    union {
        struct {
            uint32_t core1_ibus_tag_attr           :    3;  /*当认证失败时，这些位用于指示来自外部存储器的数据的属性。0：无效，1：可执行，2：可读取，4：可写入。*/
            uint32_t core1_ibus_attr               :    3;  /*这些位用于指示验证失败时CPU访问ibus的属性。0：无效，1：可执行，2：可读取*/
            uint32_t core1_ibus_world              :    1;  /*该位用于指示身份验证失败时CPU访问ibus的世界。0:世界0，1:世界1*/
            uint32_t reserved7                     :    25;
        };
        uint32_t val;
    } core1_ibus_reject_st;
    uint32_t core1_ibus_reject_vaddr;
    union {
        struct {
            uint32_t cache_mmu_fault_content       :    16;  /*这些位用于指示导致mmu故障的mmu条目的内容。。*/
            uint32_t cache_mmu_fault_code          :    4;  /*最右边的3位用于指示导致mmu故障发生的操作。0：默认值，1：cpu未命中，2：预加载未命中，3：写回，4：cpu未命中逐出恢复地址，5：加载未命中逐出还原地址，6：外部dma tx，7：外部dma rx。最高有效位用于指示该操作发生在哪个icache中。*/
            uint32_t reserved20                    :    12;
        };
        uint32_t val;
    } cache_mmu_fault_content;
    uint32_t cache_mmu_fault_vaddr;
    union {
        struct {
            uint32_t cache_flash_wrap_around       :    1;  /*该位用于在从闪存读取数据时启用环绕模式。*/
            uint32_t cache_sram_rd_wrap_around     :    1;  /*该位用于在从spiram读取数据时启用环绕模式。*/
            uint32_t reserved2                     :    30;
        };
        uint32_t val;
    } cache_wrap_around_ctrl;
    union {
        struct {
            uint32_t cache_mmu_mem_force_on        :    1;  /*该位用于在访问mmu内存时启用时钟门控以节省电源，0：启用，1：禁用*/
            uint32_t cache_mmu_mem_force_pd        :    1;  /*该位用于关闭mmu内存，0：follow_rtc_lslp_pd，1：关闭电源*/
            uint32_t cache_mmu_mem_force_pu        :    1;  /*该位用于关闭mmu内存，0:follow_rtc_lslp_pd，1:power-up*/
            uint32_t reserved3                     :    29;
        };
        uint32_t val;
    } cache_mmu_power_ctrl;
    union {
        struct {
            uint32_t icache_state                  :    12;  /*该位用于指示icache主fsm是否处于空闲状态。1： 处于空闲状态，0：不处于空闲状态*/
            uint32_t dcache_state                  :    12;  /*该位用于指示dcache主fsm是否处于空闲状态。1： 处于空闲状态，0：不处于空闲状态*/
            uint32_t reserved24                    :    8;
        };
        uint32_t val;
    } cache_state;
    union {
        struct {
            uint32_t record_disable_db_encrypt     :    1;  /*保留。*/
            uint32_t record_disable_g0cb_decrypt   :    1;  /*保留。*/
            uint32_t reserved2                     :    30;
        };
        uint32_t val;
    } cache_encrypt_decrypt_record_disable;
    union {
        struct {
            uint32_t clk_force_on_manual_crypt     :    1;  /*该位用于关闭手动密码时钟的时钟门控。1： 关闭门控，0：打开时钟门控。*/
            uint32_t clk_force_on_auto_crypt       :    1;  /*该位用于关闭自动密码时钟的时钟门控。1： 关闭门控，0：打开时钟门控。*/
            uint32_t clk_force_on_crypt            :    1;  /*该位用于关闭外部存储器加密和解密时钟的时钟门控。1： 关闭门控，0：打开时钟门控。*/
            uint32_t reserved3                     :    29;
        };
        uint32_t val;
    } cache_encrypt_decrypt_clk_force_on;
    union {
        struct {
            uint32_t alloc_wb_hold_arbiter         :    1;  /*保留。*/
            uint32_t reserved1                     :    31;
        };
        uint32_t val;
    } cache_bridge_arbiter_ctrl;
    union {
        struct {
            uint32_t icache_preload_ist            :    1;  /*该位用于通过icache预加载完成指示中断。*/
            uint32_t icache_preload_iena           :    1;  /*该位用于通过icache预加载完成启用中断。*/
            uint32_t icache_preload_iclr           :    1;  /*该位用于通过完成缓存预加载来清除中断。*/
            uint32_t dcache_preload_ist            :    1;  /*该位用于通过dcache预加载完成指示中断。*/
            uint32_t dcache_preload_iena           :    1;  /*该位用于通过dcache预加载完成来启用中断。*/
            uint32_t dcache_preload_iclr           :    1;  /*该位用于通过dcache预加载完成来清除中断。*/
            uint32_t reserved6                     :    26;
        };
        uint32_t val;
    } cache_preload_int_ctrl;
    union {
        struct {
            uint32_t icache_sync_ist               :    1;  /*该位用于通过icache同步完成指示中断。*/
            uint32_t icache_sync_iena              :    1;  /*该位用于通过完成icache同步来启用中断。*/
            uint32_t icache_sync_iclr              :    1;  /*该位用于通过完成icache同步来清除中断。*/
            uint32_t dcache_sync_ist               :    1;  /*该位用于通过数据缓存同步完成指示中断。*/
            uint32_t dcache_sync_iena              :    1;  /*该位用于通过完成数据缓存同步来启用中断。*/
            uint32_t dcache_sync_iclr              :    1;  /*该位用于通过完成数据缓存同步来清除中断。*/
            uint32_t reserved6                     :    26;
        };
        uint32_t val;
    } cache_sync_int_ctrl;
    union {
        struct {
            uint32_t cache_mmu_owner               :    24;  /*这些位用于指定MMU的所有者。bit0:icache，bit1:dcache，bit2:dma，bit3:保留。*/
            uint32_t reserved24                    :    8;
        };
        uint32_t val;
    } cache_mmu_owner;
    union {
        struct {
            uint32_t cache_ignore_preload_mmu_entry_fault:    1;  /*该位用于通过预加载操作禁用检查mmu条目故障。*/
            uint32_t cache_ignore_sync_mmu_entry_fault:    1;  /*该位用于通过同步操作禁用检查mmu条目故障。*/
            uint32_t cache_trace_ena               :    1;  /*该位用于启用缓存跟踪功能。*/
            uint32_t reserved3                     :    29;
        };
        uint32_t val;
    } cache_conf_misc;
    union {
        struct {
            uint32_t dcache_freeze_ena             :    1;  /*该位用于启用数据缓存冻结模式*/
            uint32_t dcache_freeze_mode            :    1;  /*该位用于配置冻结模式，0：如果CPU未命中则断言忙1：如果CPU没有命中则断言命中*/
            uint32_t dcache_freeze_done            :    1;  /*该位用于指示数据缓存冻结成功*/
            uint32_t reserved3                     :    29;
        };
        uint32_t val;
    } dcache_freeze;
    union {
        struct {
            uint32_t icache_freeze_ena             :    1;  /*该位用于启用icache冻结模式*/
            uint32_t icache_freeze_mode            :    1;  /*该位用于配置冻结模式，0：如果CPU未命中则断言忙1：如果CPU没有命中则断言命中*/
            uint32_t icache_freeze_done            :    1;  /*该位用于指示icache冻结成功*/
            uint32_t reserved3                     :    29;
        };
        uint32_t val;
    } icache_freeze;
    union {
        struct {
            uint32_t icache_atomic_operate_ena     :    1;  /*该位用于激活icache原子操作保护。在这种情况下，同步/锁定操作不能中断未完成的工作。在invalidateAll操作期间，此功能不起作用。*/
            uint32_t reserved1                     :    31;
        };
        uint32_t val;
    } icache_atomic_operate_ena;
    union {
        struct {
            uint32_t dcache_atomic_operate_ena     :    1;  /*该位用于激活dcache原子操作保护。在这种情况下，同步/锁定/占用操作不能中断未完成的工作。在invalidateAll操作期间，此功能不起作用。*/
            uint32_t reserved1                     :    31;
        };
        uint32_t val;
    } dcache_atomic_operate_ena;
    union {
        struct {
            uint32_t cache_request_bypass          :    1;  /*该位用于禁用可能导致性能问题的请求记录*/
            uint32_t reserved1                     :    31;
        };
        uint32_t val;
    } cache_request;
    union {
        struct {
            uint32_t clk_en                        :    1;  /*保留。*/
            uint32_t reserved1                     :    31;
        };
        uint32_t val;
    } clock_gate;
    uint32_t reserved_168;
    uint32_t reserved_16c;
    uint32_t reserved_170;
    uint32_t reserved_174;
    uint32_t reserved_178;
    uint32_t reserved_17c;
    union {
        struct {
            uint32_t icache_tag_object             :    1;  /*设置此位以将icache标记内存设置为对象。此位应与此寄存器中的其他字段保持一致。*/
            uint32_t dcache_tag_object             :    1;  /*设置此位以将dcache标记内存设置为对象。此位应与此寄存器中的其他字段保持一致。*/
            uint32_t reserved2                     :    30;  /*保留*/
        };
        uint32_t val;
    } cache_tag_object_ctrl;
    union {
        struct {
            uint32_t cache_tag_way_object          :    3;  /*设置此位以选择访问标记对象的方式。0:路0，1:路1，2:路2，3:路3，..，7:路7。*/
            uint32_t reserved3                     :    29;  /*保留*/
        };
        uint32_t val;
    } cache_tag_way_object;
    uint32_t cache_vaddr;
    uint32_t cache_tag_content;
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
    uint32_t reserved_1c0;
    uint32_t reserved_1c4;
    uint32_t reserved_1c8;
    uint32_t reserved_1cc;
    uint32_t reserved_1d0;
    uint32_t reserved_1d4;
    uint32_t reserved_1d8;
    uint32_t reserved_1dc;
    uint32_t reserved_1e0;
    uint32_t reserved_1e4;
    uint32_t reserved_1e8;
    uint32_t reserved_1ec;
    uint32_t reserved_1f0;
    uint32_t reserved_1f4;
    uint32_t reserved_1f8;
    uint32_t reserved_1fc;
    uint32_t reserved_200;
    uint32_t reserved_204;
    uint32_t reserved_208;
    uint32_t reserved_20c;
    uint32_t reserved_210;
    uint32_t reserved_214;
    uint32_t reserved_218;
    uint32_t reserved_21c;
    uint32_t reserved_220;
    uint32_t reserved_224;
    uint32_t reserved_228;
    uint32_t reserved_22c;
    uint32_t reserved_230;
    uint32_t reserved_234;
    uint32_t reserved_238;
    uint32_t reserved_23c;
    uint32_t reserved_240;
    uint32_t reserved_244;
    uint32_t reserved_248;
    uint32_t reserved_24c;
    uint32_t reserved_250;
    uint32_t reserved_254;
    uint32_t reserved_258;
    uint32_t reserved_25c;
    uint32_t reserved_260;
    uint32_t reserved_264;
    uint32_t reserved_268;
    uint32_t reserved_26c;
    uint32_t reserved_270;
    uint32_t reserved_274;
    uint32_t reserved_278;
    uint32_t reserved_27c;
    uint32_t reserved_280;
    uint32_t reserved_284;
    uint32_t reserved_288;
    uint32_t reserved_28c;
    uint32_t reserved_290;
    uint32_t reserved_294;
    uint32_t reserved_298;
    uint32_t reserved_29c;
    uint32_t reserved_2a0;
    uint32_t reserved_2a4;
    uint32_t reserved_2a8;
    uint32_t reserved_2ac;
    uint32_t reserved_2b0;
    uint32_t reserved_2b4;
    uint32_t reserved_2b8;
    uint32_t reserved_2bc;
    uint32_t reserved_2c0;
    uint32_t reserved_2c4;
    uint32_t reserved_2c8;
    uint32_t reserved_2cc;
    uint32_t reserved_2d0;
    uint32_t reserved_2d4;
    uint32_t reserved_2d8;
    uint32_t reserved_2dc;
    uint32_t reserved_2e0;
    uint32_t reserved_2e4;
    uint32_t reserved_2e8;
    uint32_t reserved_2ec;
    uint32_t reserved_2f0;
    uint32_t reserved_2f4;
    uint32_t reserved_2f8;
    uint32_t reserved_2fc;
    uint32_t reserved_300;
    uint32_t reserved_304;
    uint32_t reserved_308;
    uint32_t reserved_30c;
    uint32_t reserved_310;
    uint32_t reserved_314;
    uint32_t reserved_318;
    uint32_t reserved_31c;
    uint32_t reserved_320;
    uint32_t reserved_324;
    uint32_t reserved_328;
    uint32_t reserved_32c;
    uint32_t reserved_330;
    uint32_t reserved_334;
    uint32_t reserved_338;
    uint32_t reserved_33c;
    uint32_t reserved_340;
    uint32_t reserved_344;
    uint32_t reserved_348;
    uint32_t reserved_34c;
    uint32_t reserved_350;
    uint32_t reserved_354;
    uint32_t reserved_358;
    uint32_t reserved_35c;
    uint32_t reserved_360;
    uint32_t reserved_364;
    uint32_t reserved_368;
    uint32_t reserved_36c;
    uint32_t reserved_370;
    uint32_t reserved_374;
    uint32_t reserved_378;
    uint32_t reserved_37c;
    uint32_t reserved_380;
    uint32_t reserved_384;
    uint32_t reserved_388;
    uint32_t reserved_38c;
    uint32_t reserved_390;
    uint32_t reserved_394;
    uint32_t reserved_398;
    uint32_t reserved_39c;
    uint32_t reserved_3a0;
    uint32_t reserved_3a4;
    uint32_t reserved_3a8;
    uint32_t reserved_3ac;
    uint32_t reserved_3b0;
    uint32_t reserved_3b4;
    uint32_t reserved_3b8;
    uint32_t reserved_3bc;
    uint32_t reserved_3c0;
    uint32_t reserved_3c4;
    uint32_t reserved_3c8;
    uint32_t reserved_3cc;
    uint32_t reserved_3d0;
    uint32_t reserved_3d4;
    uint32_t reserved_3d8;
    uint32_t reserved_3dc;
    uint32_t reserved_3e0;
    uint32_t reserved_3e4;
    uint32_t reserved_3e8;
    uint32_t reserved_3ec;
    uint32_t reserved_3f0;
    uint32_t reserved_3f4;
    uint32_t reserved_3f8;
    union {
        struct {
            uint32_t extmem_reg_date               :    28;  /*版本信息。*/
            uint32_t reserved28                    :    4;
        };
        uint32_t val;
    } date;
} extmem_dev_t;
extern extmem_dev_t EXTMEM;
#ifdef __cplusplus
}
#endif



#endif /*_SOC_EXTMEM_STRUCT_H_ */

