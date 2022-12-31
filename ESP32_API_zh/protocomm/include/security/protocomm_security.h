// 版权所有2018 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#include <esp_err.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   用于验证安全会话的占有证明
 */
typedef struct protocomm_security_pop {
    /**
     * 指向包含占有证明数据的缓冲区的指针
     */
    const uint8_t *data;

    /**
     * 占有证明数据的长度（字节）
     */
    uint16_t len;
} protocomm_security_pop_t;

typedef void * protocomm_security_handle_t;

/**
 * @brief   Protocomm安全对象结构。
 *
 * 成员函数用于实现安全协议通信会话。
 *
 * @note    该结构不应有任何动态成员以允许重新进入
 */
typedef struct protocomm_security {
    /**
     * 安全实施的唯一版本号
     */
    int ver;

    /**
     * 初始化/分配安全基础结构的功能
     */
    esp_err_t (*init)(protocomm_security_handle_t *handle);

    /**
     * 用于解除分配安全基础结构的功能
     */
    esp_err_t (*cleanup)(protocomm_security_handle_t handle);

    /**
     * 使用指定的ID启动新的安全传输会话
     */
    esp_err_t (*new_transport_session)(protocomm_security_handle_t handle,
                                       uint32_t session_id);

    /**
     * 关闭具有指定ID的安全传输会话
     */
    esp_err_t (*close_transport_session)(protocomm_security_handle_t handle,
                                         uint32_t session_id);

    /**
     * 用于验证连接请求和建立安全会话的处理程序函数
     */
    esp_err_t (*security_req_handler)(protocomm_security_handle_t handle,
                                      const protocomm_security_pop_t *pop,
                                      uint32_t session_id,
                                      const uint8_t *inbuf, ssize_t inlen,
                                      uint8_t **outbuf, ssize_t *outlen,
                                      void *priv_data);

    /**
     * 实现加密算法的函数
     */
    esp_err_t (*encrypt)(protocomm_security_handle_t handle,
                         uint32_t session_id,
                         const uint8_t *inbuf, ssize_t inlen,
                         uint8_t *outbuf, ssize_t *outlen);

    /**
     * 实现解密算法的函数
     */
    esp_err_t (*decrypt)(protocomm_security_handle_t handle,
                         uint32_t session_id,
                         const uint8_t *inbuf, ssize_t inlen,
                         uint8_t *outbuf, ssize_t *outlen);
} protocomm_security_t;

#ifdef __cplusplus
}
#endif

