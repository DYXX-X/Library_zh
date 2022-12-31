/**
 * \文件doc_rng.h
 *
 * \简短的随机数生成器（RNG）模块文档文件。
 */
/*
 * 版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

/**
 * @addtogroup rng_module随机数发生器（rng）模块
 *
 * 随机数生成器（RNG）模块提供随机数生成，请参见\c mbedtls_ctr_drbg_Random（）。
 *
 * NIST SP800-90中规定的基于分组密码计数器模式的确定性随机比特发生器（CTR_DBRG）。它需要外部熵源。为此，可以使用\c mbedtls_entropy_func（）。这是一个基于简单熵累加器设计的实现。
 *
 * 所包含的另一个数字生成器不太强大，它使用HAVEGE（HArdware易失性熵收集和扩展）软件启发式，该软件认为主要使用不安全，但如果启用，则为熵池提供额外的随机性。
 *
 * 这意味着似乎没有实用的算法能够以大于1/2的概率猜测输出序列中的下一位。
 *
 * 此模块可用于生成随机数。
 */

