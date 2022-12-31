/*
 * 使用PSA Crypto API的测试的帮助函数。
 */
/*
 *  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef PSA_CRYPTO_HELPERS_H
#define PSA_CRYPTO_HELPERS_H

#include "test/psa_helpers.h"

#include <psa/crypto.h>
#include <psa_crypto_slot_management.h>

static int test_helper_is_psa_pristine( int line, const char *file )
{
    mbedtls_psa_stats_t stats;
    const char *msg = NULL;

    mbedtls_psa_get_stats( &stats );

    if( stats.volatile_slots != 0 )
        msg = "A volatile slot has not been closed properly.";
    else if( stats.persistent_slots != 0 )
        msg = "A persistent slot has not been closed properly.";
    else if( stats.external_slots != 0 )
        msg = "An external slot has not been closed properly.";
    else if( stats.half_filled_slots != 0 )
        msg = "A half-filled slot has not been cleared properly.";
    else if( stats.locked_slots != 0 )
    {
        msg = "Some slots are still marked as locked.";
    }

    /* 如果测试已经失败，请不要覆盖失败信息。请保持上面的统计信息查找，因为在调试故障时可以方便地对其进行破解。*/
    if( msg != NULL && test_info.result == TEST_RESULT_SUCCESS )
        test_fail( msg, line, file );

    return( msg == NULL );
}

/** 检查是否没有使用PSA Crypto密钥槽。
 */
#define ASSERT_PSA_PRISTINE( )                                    \
    do                                                            \
    {                                                             \
        if( ! test_helper_is_psa_pristine( __LINE__, __FILE__ ) ) \
            goto exit;                                            \
    }                                                             \
    while( 0 )

static void test_helper_psa_done( int line, const char *file )
{
    (void) test_helper_is_psa_pristine( line, file );
    mbedtls_psa_crypto_free( );
}

/** 关闭PSA Crypto子系统。预计会在没有插槽的情况下彻底关闭。
 */
#define PSA_DONE( ) test_helper_psa_done( __LINE__, __FILE__ )



#if defined(RECORD_PSA_STATUS_COVERAGE_LOG)
#include <psa/crypto.h>

/**#RECORD_STATUS记录返回状态的文件的名称。*/
#define STATUS_LOG_FILE_NAME "statuses.log"

static psa_status_t record_status( psa_status_t status,
                                   const char *func,
                                   const char *file, int line,
                                   const char *expr )
{
    /* 我们在首次使用时打开日志文件。我们从不关闭日志文件，因此record_status特性与Asan等资源泄漏检测器不兼容。
     */
    static FILE *log;
    if( log == NULL )
        log = fopen( STATUS_LOG_FILE_NAME, "a" );
    fprintf( log, "%d:%s:%s:%d:%s\n", (int) status, func, file, line, expr );
    return( status );
}

/** 返回值记录包装宏。
 *
 * 评估\p表达式。将记录其值的行写入日志文件#STATUS_log_file_NAME并返回该值。该行是以冒号分隔的字段列表：表达式的```值：字符串：__FILE__：__line_：表达式```
 *
 * 测试代码没有显式调用此宏，因为这将非常具有侵入性。相反，我们通过定义一堆包装宏来插入源代码，如```#define psa_crypto_init（）RECORD_STATUS（“psa_ccrypto_init”，psa_cCrypto_init）```这些宏定义必须存在于`instrument_RECORD_STATUS中。h`在构建测试套件时。
 *
 * \param string字符串，通常是函数名。\param expr要计算的表达式，通常是名称在\p字符串中的函数的调用。此表达式必须返回#psa_status_t类型的值。\return \p expr的值。
 */
#define RECORD_STATUS( string, expr )                                   \
    record_status( ( expr ), string, __FILE__, __LINE__, #expr )

#include "instrument_record_status.h"

#endif /* 已定义（RECORD_PSA_STATUS_COVERAGE_LOG）*/

#endif /* PSA_CRYPTO_HELPERS_H */

