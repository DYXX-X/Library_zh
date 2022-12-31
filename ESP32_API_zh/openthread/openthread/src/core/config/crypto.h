/*
 *  版权所有（c）2021，The OpenThread Authors。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CONFIG_CRYPTO_H_
#define CONFIG_CRYPTO_H_

/**
 * @def OPENTHREAD_CONFIG_CRYPTO_LIB
 *
 * 为OpenThread选择加密后端库。
 *
 * 有几个选项可用
 * - @sa OPENTHREAD_CONFIG_CRYPTO_LIB_MBEDTLS
 * - @sa OPENTHREAD_CONFIG_CRYPTO_LIB_PSA
 * - @sa OPENTHREAD_CONFIG_CRYPTO_LIB_PLATFORM
 *
 */
#ifndef OPENTHREAD_CONFIG_CRYPTO_LIB
#define OPENTHREAD_CONFIG_CRYPTO_LIB OPENTHREAD_CONFIG_CRYPTO_LIB_MBEDTLS
#endif

/**使用mbedtls作为加密库*/
#define OPENTHREAD_CONFIG_CRYPTO_LIB_MBEDTLS 0
/**使用ARM平台安全库作为加密库*/
#define OPENTHREAD_CONFIG_CRYPTO_LIB_PSA 1
/**使用平台提供的加密库*/
#define OPENTHREAD_CONFIG_CRYPTO_LIB_PLATFORM 2

#if OPENTHREAD_CONFIG_CRYPTO_LIB == OPENTHREAD_CONFIG_CRYPTO_LIB_PLATFORM

/**
 * @def OPENTHREAD_CONFIG_AES_CONTEXT_SIZE
 *
 * AES上下文字节数组的大小。仅适用于OPENTHREAD_CONFIG_CRYPTO_LAB_PORMATION。
 *
 */
#ifndef OPENTHREAD_CONFIG_AES_CONTEXT_SIZE
#error "OPENTHREAD_CONFIG_AES_CONTEXT_SIZE is missing"
#endif

/**
 * @def OPENTHREAD_CONFIG_HMAC_SHA256_CONTEXT_SIZE
 *
 * HMAC_SHA256上下文字节数组的大小。仅适用于OPENTHREAD_CONFIG_CRYPTO_LAB_PORMATION。
 *
 */
#ifndef OPENTHREAD_CONFIG_HMAC_SHA256_CONTEXT_SIZE
#error "OPENTHREAD_CONFIG_HMAC_SHA256_CONTEXT_SIZE is missing"
#endif

/**
 * @def OPENTHREAD_CONFIG_HKDF_CONTEXT_SIZE
 *
 * HKDF上下文字节数组的大小。仅适用于OPENTHREAD_CONFIG_CRYPTO_LAB_PORMATION。
 *
 */
#ifndef OPENTHREAD_CONFIG_HKDF_CONTEXT_SIZE
#error "OPENTHREAD_CONFIG_HKDF_CONTEXT_SIZE is missing"
#endif

/**
 * @def OPENTHREAD_CONFIG_SHA256_CONTEXT_SIZE
 *
 * SHA256上下文字节数组的大小。仅适用于OPENTHREAD_CONFIG_CRYPTO_LAB_PORMATION。
 *
 */
#ifndef OPENTHREAD_CONFIG_SHA256_CONTEXT_SIZE
#error "OPENTHREAD_CONFIG_SHA256_CONTEXT_SIZE is missing"
#endif

#endif // OPENTHREAD_CONFIG_CRYPTO_LIB == OPENTHREAD_CONFIG_CRYPTO_LIB_PLATFORM

#endif // CONFIG_CRYPTO_H_
