#ifndef ERI_H
#define ERI_H

#include <stdint.h>

/*
 ERI是每个Xtensa核心的内部总线。它连接到调试接口，允许读取/写入JTAG上可用的相同寄存器。
*/


/**
 * @brief  执行ERI读取
 * @param  addr ：要读取的ERI寄存器
 *
 * @return 读取的值
 */
uint32_t eri_read(int addr);


/**
 * @brief  执行ERI写入
 * @param  addr ：要写入的ERI寄存器
 * @param  data ：要写入的值
 *
 * @return 读取的值
 */
void eri_write(int addr, uint32_t data);


#endif

