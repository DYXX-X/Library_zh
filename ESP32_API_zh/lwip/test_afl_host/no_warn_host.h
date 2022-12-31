// 注意：这些undef和define用于在主机gcc/clang上编译esp32 idf时抑制警告和错误
#undef  __nonnull
#define __warning__ deprecated
#define IRAM_ATTR
#define __ESP_ATTR_H__

