/* 版权所有（c）INRIA和Microsoft Corporation。保留所有权利。根据Apache 2.0许可证许可。*/

/* 此文件由KreMLin生成<https://github.com/FStarLang/kremlin>KreMLin调用：../krml-fc89-fparentthesis-fno shadow-header/mnt/e/everest/verify/hdrB9w-minimal-fparentThesis-fcurly大括号-fno shade-header版权标头。txt-minimal-tmpdir dist/minimal-跳过编译-提取uints-添加include＜inttypes。h> -add include<stdbool。h> -add include“kremlin/internal/compat.h”-add include”kremlin/internal/types.h“-捆绑FStar.UInt64+FStar.UInt32+FStar/UInt16+FStar。UInt8=提取的/prims。krml提取/FStar_Servasives_Native。krml提取/FStar_。krml提取/FStar_Mul。krml提取/FStar_Squash。krml提取/FStar_经典。krml提取/FStar_StrongExcludedMiddle。krml提取/FStar_FunctionalExtensionity。krml提取/FStar_List_Tot_Base。krml提取/FStar_List_Tot_Properties。krml提取/FStar_List_Tot。krml提取/FStar_Seq_Base。krml提取/FStar_Seq_Properties。krml提取/FStar_Seq。krml提取/FStar_Math_Lib。krml提取/FStar_Math_Lemmas。krml提取/FStar_BitVector。krml提取/FStar_Int。krml提取/FStar_Int32.krml提取/FStar_Int。krml提取/FStar_Int16.krml提取/FStar_Prerder。krml提取/FStar_host。krml提取/FStar_RasedLogic。krml提取/FStar_Int64.krml提取/FStar_Set。krml提取/FStar_位置扩展性。krml提取/FStar_医疗扩展性。krml提取/FStar_Set。krml提取/FStar_Monotonic_Heap。krml提取/FSrar_Heap。krml提取/FStar_Map。krml提取/FStar_Monotonic_HyperHeap。krml提取/FStar_Monotonic_HyperStack。krml提取/FStar_TyperStack。krml提取/FStar_Monotonic_见证。krml提取/FStar_TyperStack_ST。krml提取/FStar_TyperStack_All。krml提取/FStar_Date。krml提取/FStar_Universe。krml提取/FStar_GSet。krml提取/FStar_ModifiesGen。krml提取/LowStar_Monotonic_Buffer。krml提取/LowStar_Buffer。krml提取/Spec_Loops。krml提取/LowStar_BufferOps。krml提取/C_ Loops。krml提取/FStar_Int8.krml提取-FStar_Kremlin_Endianness。krml提取/FStar_Int63.krml提取-FStar_Exn。krml提取/FStar_。krml提取/FStar_ All。krml提取/FStar_Dyn。krml提取/FStar_Int63.krml提取/FStar_Int64.krml提取/Pstar_Int32.krml提取-FStar_Int8.krml提取/FStar_Int16.krml提取/FStar_Int_Cast。krml提取/FStar_Int128.krml提取/C_ Endianness。krml提取/FStar_List。krml提取/FStar_Float。krml提取/FStar_IO。krml提取/C。krml提取/FSrar_Char。krml提取/FStar_String。krml提取/LowStar_Modifies。krml提取/C_String。krml提取/FStar_Bytes。krml提取/FStar_TyperStack_IO。krml提取/C_失败。krml提取/TestLib。krml提取/FStar_Int_Cast_Full。krml F版本：059db0c8 KreMLin版本：916c37ac
 */



#ifndef __FStar_UInt64_FStar_UInt32_FStar_UInt16_FStar_UInt8_H
#define __FStar_UInt64_FStar_UInt32_FStar_UInt16_FStar_UInt8_H


#include <inttypes.h>
#include <stdbool.h>
#include "kremlin/internal/compat.h"
#include "kremlin/internal/types.h"

extern Prims_int FStar_UInt64_n;

extern Prims_int FStar_UInt64_v(uint64_t x0);

extern uint64_t FStar_UInt64_uint_to_t(Prims_int x0);

extern uint64_t FStar_UInt64_add(uint64_t x0, uint64_t x1);

extern uint64_t FStar_UInt64_add_underspec(uint64_t x0, uint64_t x1);

extern uint64_t FStar_UInt64_add_mod(uint64_t x0, uint64_t x1);

extern uint64_t FStar_UInt64_sub(uint64_t x0, uint64_t x1);

extern uint64_t FStar_UInt64_sub_underspec(uint64_t x0, uint64_t x1);

extern uint64_t FStar_UInt64_sub_mod(uint64_t x0, uint64_t x1);

extern uint64_t FStar_UInt64_mul(uint64_t x0, uint64_t x1);

extern uint64_t FStar_UInt64_mul_underspec(uint64_t x0, uint64_t x1);

extern uint64_t FStar_UInt64_mul_mod(uint64_t x0, uint64_t x1);

extern uint64_t FStar_UInt64_mul_div(uint64_t x0, uint64_t x1);

extern uint64_t FStar_UInt64_div(uint64_t x0, uint64_t x1);

extern uint64_t FStar_UInt64_rem(uint64_t x0, uint64_t x1);

extern uint64_t FStar_UInt64_logand(uint64_t x0, uint64_t x1);

extern uint64_t FStar_UInt64_logxor(uint64_t x0, uint64_t x1);

extern uint64_t FStar_UInt64_logor(uint64_t x0, uint64_t x1);

extern uint64_t FStar_UInt64_lognot(uint64_t x0);

extern uint64_t FStar_UInt64_shift_right(uint64_t x0, uint32_t x1);

extern uint64_t FStar_UInt64_shift_left(uint64_t x0, uint32_t x1);

extern bool FStar_UInt64_eq(uint64_t x0, uint64_t x1);

extern bool FStar_UInt64_gt(uint64_t x0, uint64_t x1);

extern bool FStar_UInt64_gte(uint64_t x0, uint64_t x1);

extern bool FStar_UInt64_lt(uint64_t x0, uint64_t x1);

extern bool FStar_UInt64_lte(uint64_t x0, uint64_t x1);

extern uint64_t FStar_UInt64_minus(uint64_t x0);

extern uint32_t FStar_UInt64_n_minus_one;

uint64_t FStar_UInt64_eq_mask(uint64_t a, uint64_t b);

uint64_t FStar_UInt64_gte_mask(uint64_t a, uint64_t b);

extern Prims_string FStar_UInt64_to_string(uint64_t x0);

extern uint64_t FStar_UInt64_of_string(Prims_string x0);

extern Prims_int FStar_UInt32_n;

extern Prims_int FStar_UInt32_v(uint32_t x0);

extern uint32_t FStar_UInt32_uint_to_t(Prims_int x0);

extern uint32_t FStar_UInt32_add(uint32_t x0, uint32_t x1);

extern uint32_t FStar_UInt32_add_underspec(uint32_t x0, uint32_t x1);

extern uint32_t FStar_UInt32_add_mod(uint32_t x0, uint32_t x1);

extern uint32_t FStar_UInt32_sub(uint32_t x0, uint32_t x1);

extern uint32_t FStar_UInt32_sub_underspec(uint32_t x0, uint32_t x1);

extern uint32_t FStar_UInt32_sub_mod(uint32_t x0, uint32_t x1);

extern uint32_t FStar_UInt32_mul(uint32_t x0, uint32_t x1);

extern uint32_t FStar_UInt32_mul_underspec(uint32_t x0, uint32_t x1);

extern uint32_t FStar_UInt32_mul_mod(uint32_t x0, uint32_t x1);

extern uint32_t FStar_UInt32_mul_div(uint32_t x0, uint32_t x1);

extern uint32_t FStar_UInt32_div(uint32_t x0, uint32_t x1);

extern uint32_t FStar_UInt32_rem(uint32_t x0, uint32_t x1);

extern uint32_t FStar_UInt32_logand(uint32_t x0, uint32_t x1);

extern uint32_t FStar_UInt32_logxor(uint32_t x0, uint32_t x1);

extern uint32_t FStar_UInt32_logor(uint32_t x0, uint32_t x1);

extern uint32_t FStar_UInt32_lognot(uint32_t x0);

extern uint32_t FStar_UInt32_shift_right(uint32_t x0, uint32_t x1);

extern uint32_t FStar_UInt32_shift_left(uint32_t x0, uint32_t x1);

extern bool FStar_UInt32_eq(uint32_t x0, uint32_t x1);

extern bool FStar_UInt32_gt(uint32_t x0, uint32_t x1);

extern bool FStar_UInt32_gte(uint32_t x0, uint32_t x1);

extern bool FStar_UInt32_lt(uint32_t x0, uint32_t x1);

extern bool FStar_UInt32_lte(uint32_t x0, uint32_t x1);

extern uint32_t FStar_UInt32_minus(uint32_t x0);

extern uint32_t FStar_UInt32_n_minus_one;

uint32_t FStar_UInt32_eq_mask(uint32_t a, uint32_t b);

uint32_t FStar_UInt32_gte_mask(uint32_t a, uint32_t b);

extern Prims_string FStar_UInt32_to_string(uint32_t x0);

extern uint32_t FStar_UInt32_of_string(Prims_string x0);

extern Prims_int FStar_UInt16_n;

extern Prims_int FStar_UInt16_v(uint16_t x0);

extern uint16_t FStar_UInt16_uint_to_t(Prims_int x0);

extern uint16_t FStar_UInt16_add(uint16_t x0, uint16_t x1);

extern uint16_t FStar_UInt16_add_underspec(uint16_t x0, uint16_t x1);

extern uint16_t FStar_UInt16_add_mod(uint16_t x0, uint16_t x1);

extern uint16_t FStar_UInt16_sub(uint16_t x0, uint16_t x1);

extern uint16_t FStar_UInt16_sub_underspec(uint16_t x0, uint16_t x1);

extern uint16_t FStar_UInt16_sub_mod(uint16_t x0, uint16_t x1);

extern uint16_t FStar_UInt16_mul(uint16_t x0, uint16_t x1);

extern uint16_t FStar_UInt16_mul_underspec(uint16_t x0, uint16_t x1);

extern uint16_t FStar_UInt16_mul_mod(uint16_t x0, uint16_t x1);

extern uint16_t FStar_UInt16_mul_div(uint16_t x0, uint16_t x1);

extern uint16_t FStar_UInt16_div(uint16_t x0, uint16_t x1);

extern uint16_t FStar_UInt16_rem(uint16_t x0, uint16_t x1);

extern uint16_t FStar_UInt16_logand(uint16_t x0, uint16_t x1);

extern uint16_t FStar_UInt16_logxor(uint16_t x0, uint16_t x1);

extern uint16_t FStar_UInt16_logor(uint16_t x0, uint16_t x1);

extern uint16_t FStar_UInt16_lognot(uint16_t x0);

extern uint16_t FStar_UInt16_shift_right(uint16_t x0, uint32_t x1);

extern uint16_t FStar_UInt16_shift_left(uint16_t x0, uint32_t x1);

extern bool FStar_UInt16_eq(uint16_t x0, uint16_t x1);

extern bool FStar_UInt16_gt(uint16_t x0, uint16_t x1);

extern bool FStar_UInt16_gte(uint16_t x0, uint16_t x1);

extern bool FStar_UInt16_lt(uint16_t x0, uint16_t x1);

extern bool FStar_UInt16_lte(uint16_t x0, uint16_t x1);

extern uint16_t FStar_UInt16_minus(uint16_t x0);

extern uint32_t FStar_UInt16_n_minus_one;

uint16_t FStar_UInt16_eq_mask(uint16_t a, uint16_t b);

uint16_t FStar_UInt16_gte_mask(uint16_t a, uint16_t b);

extern Prims_string FStar_UInt16_to_string(uint16_t x0);

extern uint16_t FStar_UInt16_of_string(Prims_string x0);

extern Prims_int FStar_UInt8_n;

extern Prims_int FStar_UInt8_v(uint8_t x0);

extern uint8_t FStar_UInt8_uint_to_t(Prims_int x0);

extern uint8_t FStar_UInt8_add(uint8_t x0, uint8_t x1);

extern uint8_t FStar_UInt8_add_underspec(uint8_t x0, uint8_t x1);

extern uint8_t FStar_UInt8_add_mod(uint8_t x0, uint8_t x1);

extern uint8_t FStar_UInt8_sub(uint8_t x0, uint8_t x1);

extern uint8_t FStar_UInt8_sub_underspec(uint8_t x0, uint8_t x1);

extern uint8_t FStar_UInt8_sub_mod(uint8_t x0, uint8_t x1);

extern uint8_t FStar_UInt8_mul(uint8_t x0, uint8_t x1);

extern uint8_t FStar_UInt8_mul_underspec(uint8_t x0, uint8_t x1);

extern uint8_t FStar_UInt8_mul_mod(uint8_t x0, uint8_t x1);

extern uint8_t FStar_UInt8_mul_div(uint8_t x0, uint8_t x1);

extern uint8_t FStar_UInt8_div(uint8_t x0, uint8_t x1);

extern uint8_t FStar_UInt8_rem(uint8_t x0, uint8_t x1);

extern uint8_t FStar_UInt8_logand(uint8_t x0, uint8_t x1);

extern uint8_t FStar_UInt8_logxor(uint8_t x0, uint8_t x1);

extern uint8_t FStar_UInt8_logor(uint8_t x0, uint8_t x1);

extern uint8_t FStar_UInt8_lognot(uint8_t x0);

extern uint8_t FStar_UInt8_shift_right(uint8_t x0, uint32_t x1);

extern uint8_t FStar_UInt8_shift_left(uint8_t x0, uint32_t x1);

extern bool FStar_UInt8_eq(uint8_t x0, uint8_t x1);

extern bool FStar_UInt8_gt(uint8_t x0, uint8_t x1);

extern bool FStar_UInt8_gte(uint8_t x0, uint8_t x1);

extern bool FStar_UInt8_lt(uint8_t x0, uint8_t x1);

extern bool FStar_UInt8_lte(uint8_t x0, uint8_t x1);

extern uint8_t FStar_UInt8_minus(uint8_t x0);

extern uint32_t FStar_UInt8_n_minus_one;

uint8_t FStar_UInt8_eq_mask(uint8_t a, uint8_t b);

uint8_t FStar_UInt8_gte_mask(uint8_t a, uint8_t b);

extern Prims_string FStar_UInt8_to_string(uint8_t x0);

extern uint8_t FStar_UInt8_of_string(Prims_string x0);

typedef uint8_t FStar_UInt8_byte;

#define __FStar_UInt64_FStar_UInt32_FStar_UInt16_FStar_UInt8_H_DEFINED
#endif

