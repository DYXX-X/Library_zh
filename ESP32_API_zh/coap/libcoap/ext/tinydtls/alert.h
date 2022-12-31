/*******************************************************************************
 * 版权所有（c）2011、2012、2013、2014、2015奥拉夫·伯格曼（TZI）和其他人。保留所有权利。本程序和随附材料根据本发行版附带的Eclipse公共许可证v1.0和Eclipse发行许可证v1.1的条款提供。
 *
 * Eclipse公共许可证位于http://www.eclipse.org/legal/epl-v10.htmlEclipse发行许可证在http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * 贡献者：Olaf Bergmann-初始API和实现Hauke Mehrtens-内存优化、ECC集成
 *
 *******************************************************************************/

/**
 * @file 警报.h
 * @brief DTLS警报协议
 */

#ifndef _DTLS_ALERT_H_
#define _DTLS_ALERT_H_

typedef enum {
  DTLS_ALERT_LEVEL_WARNING=1,
  DTLS_ALERT_LEVEL_FATAL=2
} dtls_alert_level_t;

typedef enum {
  DTLS_ALERT_CLOSE_NOTIFY = 0,			/* 关闭_通知*/
  DTLS_ALERT_UNEXPECTED_MESSAGE = 10,		/* 意外消息*/
  DTLS_ALERT_BAD_RECORD_MAC = 20,		/* 标记_记录_*/
  DTLS_ALERT_RECORD_OVERFLOW = 22,		/* 记录溢出（_O）*/
  DTLS_ALERT_DECOMPRESSION_FAILURE = 30,	/* 解压缩失败*/
  DTLS_ALERT_HANDSHAKE_FAILURE = 40,		/* 握手失败*/
  DTLS_ALERT_BAD_CERTIFICATE = 42,		/* 无效证书（_C）*/
  DTLS_ALERT_UNSUPPORTED_CERTIFICATE = 43,	/* 不支持的证书*/
  DTLS_ALERT_CERTIFICATE_REVOKED = 44,		/* 证书已撤销*/
  DTLS_ALERT_CERTIFICATE_EXPIRED = 45,		/* 证书已过期*/
  DTLS_ALERT_CERTIFICATE_UNKNOWN = 46,		/* 证书未知*/
  DTLS_ALERT_ILLEGAL_PARAMETER = 47,		/* 非法参数*/
  DTLS_ALERT_UNKNOWN_CA = 48,			/* 未知ca*/
  DTLS_ALERT_ACCESS_DENIED = 49,		/* 已访问的*/
  DTLS_ALERT_DECODE_ERROR = 50,			/* 解码错误（_E）*/
  DTLS_ALERT_DECRYPT_ERROR = 51,		/* 解密错误*/
  DTLS_ALERT_PROTOCOL_VERSION = 70,		/* 协议版本*/
  DTLS_ALERT_INSUFFICIENT_SECURITY = 71,	/* 安全性不足*/
  DTLS_ALERT_INTERNAL_ERROR = 80,		/* 内部错误（_E）*/
  DTLS_ALERT_USER_CANCELED = 90,		/* 用户已取消（_C）*/
  DTLS_ALERT_NO_RENEGOTIATION = 100,		/* 不重新协商*/
  DTLS_ALERT_UNSUPPORTED_EXTENSION = 110	/* 不支持的扩展*/
} dtls_alert_t;

#define DTLS_EVENT_CONNECT        0x01DC /**<初始化握手*/
#define DTLS_EVENT_CONNECTED      0x01DE /**<握手或重新协商已完成*/
#define DTLS_EVENT_RENEGOTIATE    0x01DF /**<重新协商已开始*/

static inline int
dtls_alert_create(dtls_alert_level_t level, dtls_alert_t desc)
{
  return -((level << 8) | desc);
}

static inline int
dtls_alert_fatal_create(dtls_alert_t desc)
{
  return dtls_alert_create(DTLS_ALERT_LEVEL_FATAL, desc);
}

#endif /* _DTLS_ALERT_H_ */

