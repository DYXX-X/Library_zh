/*
 * Xtensa特殊寄存器符号名称
 */

/* $Id://depot/rel/Foxhill.dot.9/Xtensa/OS/include/Xtensa/specreg。小时#1$*/

/*
 * 版权所有（c）2005-2011 Tensilica Inc。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef XTENSA_SPECREG_H
#define XTENSA_SPECREG_H

/*  特殊寄存器：*/
#define LBEG		0
#define LEND		1
#define LCOUNT		2
#define SAR		3
#define BR		4
#define LITBASE		5
#define SCOMPARE1	12
#define ACCLO		16
#define ACCHI		17
#define MR_0		32
#define MR_1		33
#define MR_2		34
#define MR_3		35
#define PREFCTL		40
#define WINDOWBASE	72
#define WINDOWSTART	73
#define PTEVADDR	83
#define RASID		90
#define ITLBCFG		91
#define DTLBCFG		92
#define IBREAKENABLE	96
#define MEMCTL		97
#define CACHEATTR	98	/* 至T1050，XEA1*/
#define CACHEADRDIS	98	/* LX7+ */
#define ATOMCTL		99
#define DDR		104
#define MECR		110
#define IBREAKA_0	128
#define IBREAKA_1	129
#define DBREAKA_0	144
#define DBREAKA_1	145
#define DBREAKC_0	160
#define DBREAKC_1	161
#define CONFIGID0	176
#define EPC_1		177
#define EPC_2		178
#define EPC_3		179
#define EPC_4		180
#define EPC_5		181
#define EPC_6		182
#define EPC_7		183
#define DEPC		192
#define EPS_2		194
#define EPS_3		195
#define EPS_4		196
#define EPS_5		197
#define EPS_6		198
#define EPS_7		199
#define CONFIGID1	208
#define EXCSAVE_1	209
#define EXCSAVE_2	210
#define EXCSAVE_3	211
#define EXCSAVE_4	212
#define EXCSAVE_5	213
#define EXCSAVE_6	214
#define EXCSAVE_7	215
#define CPENABLE	224
#define INTERRUPT	226
#define INTREAD		INTERRUPT	/* 向后兼容的备用名称*/
#define INTSET		INTERRUPT	/* 向后兼容的备用名称*/
#define INTCLEAR	227
#define INTENABLE	228
#define PS		230
#define VECBASE		231
#define EXCCAUSE	232
#define DEBUGCAUSE	233
#define CCOUNT		234
#define PRID		235
#define ICOUNT		236
#define ICOUNTLEVEL	237
#define EXCVADDR	238
#define CCOMPARE_0	240
#define CCOMPARE_1	241
#define CCOMPARE_2	242
#define MISC_REG_0	244
#define MISC_REG_1	245
#define MISC_REG_2	246
#define MISC_REG_3	247

/*  特殊情况（特殊寄存器系列的基础）：*/
#define MR		32
#define IBREAKA		128
#define DBREAKA		144
#define DBREAKC		160
#define EPC		176
#define EPS		192
#define EXCSAVE		208
#define CCOMPARE	240
#define MISC_REG	244

/*  Tensilica定义的用户寄存器：*/
#if 0
/*#定义…21…24*/	/* (545CK) */
/*#定义…140..143*/	/* (545CK) */
#define EXPSTATE	230	/* 金刚石*/
#define THREADPTR	231	/* threadptr选项*/
#define FCR		232	/* FPU */
#define FSR		233	/* FPU */
#define AE_OVF_SAR	240	/* 高Fi2*/
#define AE_BITHEAD	241	/* 高Fi2*/
#define AE_TS_FTS_BU_BP	242	/* 高Fi2*/
#define AE_SD_NO	243	/* 高Fi2*/
#define VSAR		240	/* VectraLX公司*/
#define ROUND_LO	242	/* VectraLX公司*/
#define ROUND_HI	243	/* VectraLX公司*/
#define CBEGIN		246	/* VectraLX公司*/
#define CEND		247	/* VectraLX公司*/
#endif

#endif /* XTENSA_SPECREG_H */

