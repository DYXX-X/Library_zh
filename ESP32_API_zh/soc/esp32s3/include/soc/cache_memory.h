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
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*IRAM0与缓存IBUS0连接*/
#define IRAM0_ADDRESS_LOW               0x40000000
#define IRAM0_ADDRESS_HIGH              0x44000000
#define IRAM0_CACHE_ADDRESS_LOW         0x42000000
#define IRAM0_CACHE_ADDRESS_HIGH        0x44000000

/*DRAM0与缓存DBUS0连接*/
#define DRAM0_ADDRESS_LOW               0x3C000000
#define DRAM0_ADDRESS_HIGH              0x40000000
#define DRAM0_CACHE_ADDRESS_LOW         0x3C000000
#define DRAM0_CACHE_ADDRESS_HIGH        0x3E000000
#define DRAM0_CACHE_OPERATION_HIGH      DRAM0_CACHE_ADDRESS_HIGH
#define ESP_CACHE_TEMP_ADDR             0x3C800000

#define BUS_SIZE(bus_name)                 (bus_name##_ADDRESS_HIGH - bus_name##_ADDRESS_LOW)
#define ADDRESS_IN_BUS(bus_name, vaddr)    ((vaddr) >= bus_name##_ADDRESS_LOW && (vaddr) < bus_name##_ADDRESS_HIGH)

#define ADDRESS_IN_IRAM0(vaddr)            ADDRESS_IN_BUS(IRAM0, vaddr)
#define ADDRESS_IN_IRAM0_CACHE(vaddr)      ADDRESS_IN_BUS(IRAM0_CACHE, vaddr)
#define ADDRESS_IN_DRAM0(vaddr)            ADDRESS_IN_BUS(DRAM0, vaddr)
#define ADDRESS_IN_DRAM0_CACHE(vaddr)      ADDRESS_IN_BUS(DRAM0_CACHE, vaddr)

#define BUS_IRAM0_CACHE_SIZE              BUS_SIZE(IRAM0_CACHE)
#define BUS_DRAM0_CACHE_SIZE              BUS_SIZE(DRAM0_CACHE)

#define CACHE_IBUS                      0
#define CACHE_IBUS_MMU_START            0
#define CACHE_IBUS_MMU_END              0x800

#define CACHE_DBUS                      1
#define CACHE_DBUS_MMU_START            0
#define CACHE_DBUS_MMU_END              0x800

#define CACHE_IROM_MMU_START            0
#define CACHE_IROM_MMU_END              Cache_Get_IROM_MMU_End()
#define CACHE_IROM_MMU_SIZE             (CACHE_IROM_MMU_END - CACHE_IROM_MMU_START)

#define CACHE_DROM_MMU_START            CACHE_IROM_MMU_END
#define CACHE_DROM_MMU_END              Cache_Get_DROM_MMU_End()
#define CACHE_DROM_MMU_SIZE             (CACHE_DROM_MMU_END - CACHE_DROM_MMU_START)

#define CACHE_DROM_MMU_MAX_END          0x400

#define ICACHE_MMU_SIZE                 0x800
#define DCACHE_MMU_SIZE                 0x800

#define MMU_BUS_START(i)                0
#define MMU_BUS_SIZE(i)                 0x800

#define MMU_INVALID                     BIT(14)
#define MMU_TYPE                        BIT(15)
#define MMU_ACCESS_FLASH                0
#define MMU_ACCESS_SPIRAM               BIT(15)

#define CACHE_MAX_SYNC_NUM 0x400000
#define CACHE_MAX_LOCK_NUM 0x8000

#define FLASH_MMU_TABLE ((volatile uint32_t*) DR_REG_MMU_TABLE)
#define FLASH_MMU_TABLE_SIZE (ICACHE_MMU_SIZE/sizeof(uint32_t))

#define MMU_TABLE_INVALID_VAL 0x4000
#define FLASH_MMU_TABLE_INVALID_VAL DPORT_MMU_TABLE_INVALID_VAL
#define MMU_ADDRESS_MASK 0x3fff
#define MMU_PAGE_SIZE 0x10000
#define INVALID_PHY_PAGE 0xffff

#define BUS_ADDR_SIZE 0x2000000
#define BUS_ADDR_MASK (BUS_ADDR_SIZE - 1)

#define CACHE_ICACHE_LOW_SHIFT         0
#define CACHE_ICACHE_HIGH_SHIFT        2
#define CACHE_DCACHE_LOW_SHIFT         4
#define CACHE_DCACHE_HIGH_SHIFT        6

#define CACHE_MEMORY_IBANK0_ADDR        0x40370000
#define CACHE_MEMORY_IBANK1_ADDR        0x40374000

#define CACHE_MEMORY_DBANK0_ADDR        0x3fcf0000
#define CACHE_MEMORY_DBANK1_ADDR        0x3fcf8000

#ifdef __cplusplus
}
#endif

