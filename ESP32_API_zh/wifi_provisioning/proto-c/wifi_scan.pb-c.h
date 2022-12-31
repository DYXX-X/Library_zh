/* 由协议缓冲区编译器生成。不要编辑！*/
/* 生成自：wifi_scan.proto*/

#ifndef PROTOBUF_C_wifi_5fscan_2eproto__INCLUDED
#define PROTOBUF_C_wifi_5fscan_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003001 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "constants.pb-c.h"
#include "wifi_constants.pb-c.h"

typedef struct _CmdScanStart CmdScanStart;
typedef struct _RespScanStart RespScanStart;
typedef struct _CmdScanStatus CmdScanStatus;
typedef struct _RespScanStatus RespScanStatus;
typedef struct _CmdScanResult CmdScanResult;
typedef struct _WiFiScanResult WiFiScanResult;
typedef struct _RespScanResult RespScanResult;
typedef struct _WiFiScanPayload WiFiScanPayload;


/* ---枚举---*/

typedef enum _WiFiScanMsgType {
  WI_FI_SCAN_MSG_TYPE__TypeCmdScanStart = 0,
  WI_FI_SCAN_MSG_TYPE__TypeRespScanStart = 1,
  WI_FI_SCAN_MSG_TYPE__TypeCmdScanStatus = 2,
  WI_FI_SCAN_MSG_TYPE__TypeRespScanStatus = 3,
  WI_FI_SCAN_MSG_TYPE__TypeCmdScanResult = 4,
  WI_FI_SCAN_MSG_TYPE__TypeRespScanResult = 5
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(WI_FI_SCAN_MSG_TYPE)
} WiFiScanMsgType;

/* ---消息---*/

struct  _CmdScanStart
{
  ProtobufCMessage base;
  protobuf_c_boolean blocking;
  protobuf_c_boolean passive;
  uint32_t group_channels;
  uint32_t period_ms;
};
#define CMD_SCAN_START__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&cmd_scan_start__descriptor) \
    , 0, 0, 0, 0 }


struct  _RespScanStart
{
  ProtobufCMessage base;
};
#define RESP_SCAN_START__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&resp_scan_start__descriptor) \
     }


struct  _CmdScanStatus
{
  ProtobufCMessage base;
};
#define CMD_SCAN_STATUS__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&cmd_scan_status__descriptor) \
     }


struct  _RespScanStatus
{
  ProtobufCMessage base;
  protobuf_c_boolean scan_finished;
  uint32_t result_count;
};
#define RESP_SCAN_STATUS__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&resp_scan_status__descriptor) \
    , 0, 0 }


struct  _CmdScanResult
{
  ProtobufCMessage base;
  uint32_t start_index;
  uint32_t count;
};
#define CMD_SCAN_RESULT__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&cmd_scan_result__descriptor) \
    , 0, 0 }


struct  _WiFiScanResult
{
  ProtobufCMessage base;
  ProtobufCBinaryData ssid;
  uint32_t channel;
  int32_t rssi;
  ProtobufCBinaryData bssid;
  WifiAuthMode auth;
};
#define WI_FI_SCAN_RESULT__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&wi_fi_scan_result__descriptor) \
    , {0,NULL}, 0, 0, {0,NULL}, WIFI_AUTH_MODE__Open }


struct  _RespScanResult
{
  ProtobufCMessage base;
  size_t n_entries;
  WiFiScanResult **entries;
};
#define RESP_SCAN_RESULT__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&resp_scan_result__descriptor) \
    , 0,NULL }


typedef enum {
  WI_FI_SCAN_PAYLOAD__PAYLOAD__NOT_SET = 0,
  WI_FI_SCAN_PAYLOAD__PAYLOAD_CMD_SCAN_START = 10,
  WI_FI_SCAN_PAYLOAD__PAYLOAD_RESP_SCAN_START = 11,
  WI_FI_SCAN_PAYLOAD__PAYLOAD_CMD_SCAN_STATUS = 12,
  WI_FI_SCAN_PAYLOAD__PAYLOAD_RESP_SCAN_STATUS = 13,
  WI_FI_SCAN_PAYLOAD__PAYLOAD_CMD_SCAN_RESULT = 14,
  WI_FI_SCAN_PAYLOAD__PAYLOAD_RESP_SCAN_RESULT = 15
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(WI_FI_SCAN_PAYLOAD__PAYLOAD)
} WiFiScanPayload__PayloadCase;

struct  _WiFiScanPayload
{
  ProtobufCMessage base;
  WiFiScanMsgType msg;
  Status status;
  WiFiScanPayload__PayloadCase payload_case;
  union {
    CmdScanStart *cmd_scan_start;
    RespScanStart *resp_scan_start;
    CmdScanStatus *cmd_scan_status;
    RespScanStatus *resp_scan_status;
    CmdScanResult *cmd_scan_result;
    RespScanResult *resp_scan_result;
  };
};
#define WI_FI_SCAN_PAYLOAD__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&wi_fi_scan_payload__descriptor) \
    , WI_FI_SCAN_MSG_TYPE__TypeCmdScanStart, STATUS__Success, WI_FI_SCAN_PAYLOAD__PAYLOAD__NOT_SET, {0} }


/* CmdScanStart方法*/
void   cmd_scan_start__init
                     (CmdScanStart         *message);
size_t cmd_scan_start__get_packed_size
                     (const CmdScanStart   *message);
size_t cmd_scan_start__pack
                     (const CmdScanStart   *message,
                      uint8_t             *out);
size_t cmd_scan_start__pack_to_buffer
                     (const CmdScanStart   *message,
                      ProtobufCBuffer     *buffer);
CmdScanStart *
       cmd_scan_start__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   cmd_scan_start__free_unpacked
                     (CmdScanStart *message,
                      ProtobufCAllocator *allocator);
/* RespScanStart方法*/
void   resp_scan_start__init
                     (RespScanStart         *message);
size_t resp_scan_start__get_packed_size
                     (const RespScanStart   *message);
size_t resp_scan_start__pack
                     (const RespScanStart   *message,
                      uint8_t             *out);
size_t resp_scan_start__pack_to_buffer
                     (const RespScanStart   *message,
                      ProtobufCBuffer     *buffer);
RespScanStart *
       resp_scan_start__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   resp_scan_start__free_unpacked
                     (RespScanStart *message,
                      ProtobufCAllocator *allocator);
/* CmdScanStatus方法*/
void   cmd_scan_status__init
                     (CmdScanStatus         *message);
size_t cmd_scan_status__get_packed_size
                     (const CmdScanStatus   *message);
size_t cmd_scan_status__pack
                     (const CmdScanStatus   *message,
                      uint8_t             *out);
size_t cmd_scan_status__pack_to_buffer
                     (const CmdScanStatus   *message,
                      ProtobufCBuffer     *buffer);
CmdScanStatus *
       cmd_scan_status__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   cmd_scan_status__free_unpacked
                     (CmdScanStatus *message,
                      ProtobufCAllocator *allocator);
/* RespScanStatus方法*/
void   resp_scan_status__init
                     (RespScanStatus         *message);
size_t resp_scan_status__get_packed_size
                     (const RespScanStatus   *message);
size_t resp_scan_status__pack
                     (const RespScanStatus   *message,
                      uint8_t             *out);
size_t resp_scan_status__pack_to_buffer
                     (const RespScanStatus   *message,
                      ProtobufCBuffer     *buffer);
RespScanStatus *
       resp_scan_status__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   resp_scan_status__free_unpacked
                     (RespScanStatus *message,
                      ProtobufCAllocator *allocator);
/* CmdScanResult方法*/
void   cmd_scan_result__init
                     (CmdScanResult         *message);
size_t cmd_scan_result__get_packed_size
                     (const CmdScanResult   *message);
size_t cmd_scan_result__pack
                     (const CmdScanResult   *message,
                      uint8_t             *out);
size_t cmd_scan_result__pack_to_buffer
                     (const CmdScanResult   *message,
                      ProtobufCBuffer     *buffer);
CmdScanResult *
       cmd_scan_result__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   cmd_scan_result__free_unpacked
                     (CmdScanResult *message,
                      ProtobufCAllocator *allocator);
/* WiFiScanResult方法*/
void   wi_fi_scan_result__init
                     (WiFiScanResult         *message);
size_t wi_fi_scan_result__get_packed_size
                     (const WiFiScanResult   *message);
size_t wi_fi_scan_result__pack
                     (const WiFiScanResult   *message,
                      uint8_t             *out);
size_t wi_fi_scan_result__pack_to_buffer
                     (const WiFiScanResult   *message,
                      ProtobufCBuffer     *buffer);
WiFiScanResult *
       wi_fi_scan_result__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   wi_fi_scan_result__free_unpacked
                     (WiFiScanResult *message,
                      ProtobufCAllocator *allocator);
/* RespScanResult方法*/
void   resp_scan_result__init
                     (RespScanResult         *message);
size_t resp_scan_result__get_packed_size
                     (const RespScanResult   *message);
size_t resp_scan_result__pack
                     (const RespScanResult   *message,
                      uint8_t             *out);
size_t resp_scan_result__pack_to_buffer
                     (const RespScanResult   *message,
                      ProtobufCBuffer     *buffer);
RespScanResult *
       resp_scan_result__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   resp_scan_result__free_unpacked
                     (RespScanResult *message,
                      ProtobufCAllocator *allocator);
/* WiFiScanPayload方法*/
void   wi_fi_scan_payload__init
                     (WiFiScanPayload         *message);
size_t wi_fi_scan_payload__get_packed_size
                     (const WiFiScanPayload   *message);
size_t wi_fi_scan_payload__pack
                     (const WiFiScanPayload   *message,
                      uint8_t             *out);
size_t wi_fi_scan_payload__pack_to_buffer
                     (const WiFiScanPayload   *message,
                      ProtobufCBuffer     *buffer);
WiFiScanPayload *
       wi_fi_scan_payload__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   wi_fi_scan_payload__free_unpacked
                     (WiFiScanPayload *message,
                      ProtobufCAllocator *allocator);
/* ---每个消息闭包---*/

typedef void (*CmdScanStart_Closure)
                 (const CmdScanStart *message,
                  void *closure_data);
typedef void (*RespScanStart_Closure)
                 (const RespScanStart *message,
                  void *closure_data);
typedef void (*CmdScanStatus_Closure)
                 (const CmdScanStatus *message,
                  void *closure_data);
typedef void (*RespScanStatus_Closure)
                 (const RespScanStatus *message,
                  void *closure_data);
typedef void (*CmdScanResult_Closure)
                 (const CmdScanResult *message,
                  void *closure_data);
typedef void (*WiFiScanResult_Closure)
                 (const WiFiScanResult *message,
                  void *closure_data);
typedef void (*RespScanResult_Closure)
                 (const RespScanResult *message,
                  void *closure_data);
typedef void (*WiFiScanPayload_Closure)
                 (const WiFiScanPayload *message,
                  void *closure_data);

/* ---服务---*/


/* ---描述符---*/

extern const ProtobufCEnumDescriptor    wi_fi_scan_msg_type__descriptor;
extern const ProtobufCMessageDescriptor cmd_scan_start__descriptor;
extern const ProtobufCMessageDescriptor resp_scan_start__descriptor;
extern const ProtobufCMessageDescriptor cmd_scan_status__descriptor;
extern const ProtobufCMessageDescriptor resp_scan_status__descriptor;
extern const ProtobufCMessageDescriptor cmd_scan_result__descriptor;
extern const ProtobufCMessageDescriptor wi_fi_scan_result__descriptor;
extern const ProtobufCMessageDescriptor resp_scan_result__descriptor;
extern const ProtobufCMessageDescriptor wi_fi_scan_payload__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_wif_5fscan_2eproto__包含*/

