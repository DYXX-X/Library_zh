/* 由协议缓冲区编译器生成。不要编辑！*/
/* 生成自：常量。原型*/

#ifndef PROTOBUF_C_constants_2eproto__INCLUDED
#define PROTOBUF_C_constants_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif




/* ---枚举---*/

/*
 * protocomm实例状态的允许值
 */
typedef enum _Status {
  STATUS__Success = 0,
  STATUS__InvalidSecScheme = 1,
  STATUS__InvalidProto = 2,
  STATUS__TooManySessions = 3,
  STATUS__InvalidArgument = 4,
  STATUS__InternalError = 5,
  STATUS__CryptoError = 6,
  STATUS__InvalidSession = 7
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(STATUS)
} Status;

/* ---消息---*/

/* ---每个消息闭包---*/


/* ---服务---*/


/* ---描述符---*/

extern const ProtobufCEnumDescriptor    status__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_constants_2eproto__包含*/
