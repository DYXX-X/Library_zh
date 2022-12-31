// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef _SSL_CODE_H_
#define _SSL_CODE_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "ssl3.h"
#include "tls1.h"
#include "x509_vfy.h"

/* 用于SSL_set_mode（）——使用BIO时支持的模式*/
#define SSL_MODE_ENABLE_PARTIAL_WRITE       0x00000001L
#define SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER 0x00000002L

/* 用于SSL_set_shutdown（）/SSL-get_shutdown（）；*/
# define SSL_SENT_SHUTDOWN       1
# define SSL_RECEIVED_SHUTDOWN   2

# define SSL_VERIFY_NONE                 0x00
# define SSL_VERIFY_PEER                 0x01
# define SSL_VERIFY_FAIL_IF_NO_PEER_CERT 0x02
# define SSL_VERIFY_CLIENT_ONCE          0x04

/*
 * 以下3种状态保存在ssl->rlayer中。rstate当读取失败时，您不需要这些
 */
# define SSL_ST_READ_HEADER                      0xF0
# define SSL_ST_READ_BODY                        0xF1
# define SSL_ST_READ_DONE                        0xF2

# define SSL_NOTHING            1
# define SSL_WRITING            2
# define SSL_READING            3
# define SSL_X509_LOOKUP        4
# define SSL_ASYNC_PAUSED       5
# define SSL_ASYNC_NO_JOBS      6


# define SSL_ERROR_NONE                  0
# define SSL_ERROR_SSL                   1
# define SSL_ERROR_WANT_READ             2
# define SSL_ERROR_WANT_WRITE            3
# define SSL_ERROR_WANT_X509_LOOKUP      4
# define SSL_ERROR_SYSCALL               5/* 查看错误堆栈/返回值/errno*/
# define SSL_ERROR_ZERO_RETURN           6
# define SSL_ERROR_WANT_CONNECT          7
# define SSL_ERROR_WANT_ACCEPT           8
# define SSL_ERROR_WANT_ASYNC            9
# define SSL_ERROR_WANT_ASYNC_JOB       10

/* 消息流状态*/
typedef enum {
    /* 未进行握手*/
    MSG_FLOW_UNINITED,
    /* 此连接存在永久错误*/
    MSG_FLOW_ERROR,
    /* 我们即将重新谈判*/
    MSG_FLOW_RENEGOTIATE,
    /* 我们正在阅读消息*/
    MSG_FLOW_READING,
    /* 我们正在写消息*/
    MSG_FLOW_WRITING,
    /* 握手已完成*/
    MSG_FLOW_FINISHED
} MSG_FLOW_STATE;

/* SSL子系统状态*/
typedef enum {
    TLS_ST_BEFORE,
    TLS_ST_OK,
    DTLS_ST_CR_HELLO_VERIFY_REQUEST,
    TLS_ST_CR_SRVR_HELLO,
    TLS_ST_CR_CERT,
    TLS_ST_CR_CERT_STATUS,
    TLS_ST_CR_KEY_EXCH,
    TLS_ST_CR_CERT_REQ,
    TLS_ST_CR_SRVR_DONE,
    TLS_ST_CR_SESSION_TICKET,
    TLS_ST_CR_CHANGE,
    TLS_ST_CR_FINISHED,
    TLS_ST_CW_CLNT_HELLO,
    TLS_ST_CW_CERT,
    TLS_ST_CW_KEY_EXCH,
    TLS_ST_CW_CERT_VRFY,
    TLS_ST_CW_CHANGE,
    TLS_ST_CW_NEXT_PROTO,
    TLS_ST_CW_FINISHED,
    TLS_ST_SW_HELLO_REQ,
    TLS_ST_SR_CLNT_HELLO,
    DTLS_ST_SW_HELLO_VERIFY_REQUEST,
    TLS_ST_SW_SRVR_HELLO,
    TLS_ST_SW_CERT,
    TLS_ST_SW_KEY_EXCH,
    TLS_ST_SW_CERT_REQ,
    TLS_ST_SW_SRVR_DONE,
    TLS_ST_SR_CERT,
    TLS_ST_SR_KEY_EXCH,
    TLS_ST_SR_CERT_VRFY,
    TLS_ST_SR_NEXT_PROTO,
    TLS_ST_SR_CHANGE,
    TLS_ST_SR_FINISHED,
    TLS_ST_SW_SESSION_TICKET,
    TLS_ST_SW_CERT_STATUS,
    TLS_ST_SW_CHANGE,
    TLS_ST_SW_FINISHED
} OSSL_HANDSHAKE_STATE;

#ifdef __cplusplus
}
#endif

#endif

