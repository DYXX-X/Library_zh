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

#include <protocomm_security.h>
#include <esp_err.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief protocomm端点处理程序的函数原型
 */
typedef esp_err_t (*protocomm_req_handler_t)(
    uint32_t        session_id, /*!< 用于识别protocomm客户端的会话ID*/
    const uint8_t  *inbuf,      /*!< 指向用户提供的输入数据缓冲区的指针*/
    ssize_t         inlen,      /*!< 输入缓冲区的长度*/
    uint8_t       **outbuf,     /*!< 指向处理程序分配的输出缓冲区的指针*/
    ssize_t        *outlen,     /*!< 分配的输出缓冲区的长度*/
    void           *priv_data   /*!< 传递给处理程序的私有数据（如果未使用，则为NULL）*/
);

/**
 * @brief   此结构对应于调用API“protocomm_new（）”时返回的protocomm的唯一实例。其余的ProtocommAPI需要将此对象作为第一个参数。
 *
 * @note    protocomm对象的结构保持私有
 */
typedef struct protocomm protocomm_t;

/**
 * @brief   创建新的protocomm实例
 *
 * 此API将返回一个新的动态分配的protocomm实例，protocomm_t结构的所有元素都初始化为NULL。
 *
 * @return
 *  -protocomm_t*：成功时
 *  -NULL：没有内存用于分配新实例
 */
protocomm_t *protocomm_new(void);

/**
 * @brief   删除protocomm实例
 *
 * 此API将释放使用“protocomm_new（）”创建的protocomm实例。
 *
 * @param[in] pc    指向要删除的protocomm实例的指针
 */
void protocomm_delete(protocomm_t *pc);

/**
 * @brief   为protocomm实例添加端点请求处理程序
 *
 * 此API将端点处理程序函数绑定到指定的端点名称，以及在调用时需要传递给处理程序的任何私有数据。
 *
 * @note
 *  -端点必须绑定到使用“protocomm_new（）”创建的有效protocomm实例。
 *  -此函数在内部调用所选传输的已注册“add_endpoint（）”函数，该传输是protocomm_t实例结构的成员。
 *
 * @param[in] pc        指向protocomm实例的指针
 * @param[in] ep_name   端点标识符（名称）字符串
 * @param[in] h         终结点处理程序函数
 * @param[in] priv_data 指向在调用时作为参数传递给处理程序函数的私有数据的指针。如果不需要，则传递NULL。
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_FAIL:添加具有此名称的终结点/终结点时出错已存在
 *  -ESP_ERR_NO_MEM:分配端点资源时出错
 *  -ESP_ERR_INVALID_ARG:空实例/名称/处理程序参数
 */
esp_err_t protocomm_add_endpoint(protocomm_t *pc, const char *ep_name,
                                 protocomm_req_handler_t h, void *priv_data);

/**
 * @brief   删除protocomm实例的端点请求处理程序
 *
 * 此API将删除由端点名称标识的已注册端点处理程序。
 *
 * @note
 *  -此函数在内部调用注册的“remove_endpoint（）”函数，该函数是protocomm_t实例结构的成员。
 *
 * @param[in] pc        指向protocomm实例的指针
 * @param[in] ep_name   端点标识符（名称）字符串
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_NOT_FOUND:具有指定名称的终结点不存在
 *  -ESP_ERR_INVALID_ARG:空实例/名称参数
 */
esp_err_t protocomm_remove_endpoint(protocomm_t *pc, const char *ep_name);

/**
 * @brief   为新的传输会话分配内部资源
 *
 * @note
 *  -端点必须绑定到使用“protocomm_new（）”创建的有效protocomm实例。
 *
 * @param[in]  pc         指向protocomm实例的指针
 * @param[in]  session_id 通信会话的唯一ID
 *
 * @return
 *  -ESP_OK:请求已成功处理
 *  -ESP_ERR_NO_MEM:分配内部资源时出错
 *  -ESP_ERR_INVALID_ARG:空实例/名称参数
 */
esp_err_t protocomm_open_session(protocomm_t *pc, uint32_t session_id);

/**
 * @brief   释放传输会话使用的内部资源
 *
 * @note
 *  -端点必须绑定到使用“protocomm_new（）”创建的有效protocomm实例。
 *
 * @param[in]  pc         指向protocomm实例的指针
 * @param[in]  session_id 通信会话的唯一ID
 *
 * @return
 *  -ESP_OK:请求已成功处理
 *  -ESP_ERR_INVALID_ARG:空实例/名称参数
 */
esp_err_t protocomm_close_session(protocomm_t *pc, uint32_t session_id);

/**
 * @brief   调用端点会话的注册处理程序以处理传入数据并生成响应
 *
 * @note
 *  -端点必须绑定到使用“protocomm_new（）”创建的有效protocomm实例。
 *  -结果输出缓冲区必须由调用者释放。
 *
 * @param[in]  pc         指向protocomm实例的指针
 * @param[in]  ep_name    端点标识符（名称）字符串
 * @param[in]  session_id 通信会话的唯一ID
 * @param[in]  inbuf      输入缓冲区包含要由注册处理程序处理的输入请求数据
 * @param[in]  inlen      输入缓冲区的长度
 * @param[out] outbuf     指向内部分配的输出缓冲区的指针，其中存储从注册处理程序输出的结果响应数据
 * @param[out] outlen     分配的输出缓冲区的缓冲区长度
 *
 * @return
 *  -ESP_OK:请求已成功处理
 *  -ESP_FAIL：执行注册的处理程序时发生内部错误
 *  -ESP_ERR_NO_MEM:分配内部资源时出错
 *  -ESP_ERR_NOT_FOUND:具有指定名称的终结点不存在
 *  -ESP_ERR_INVALID_ARG:空实例/名称参数
 */
esp_err_t protocomm_req_handle(protocomm_t *pc, const char *ep_name, uint32_t session_id,
                               const uint8_t *inbuf, ssize_t inlen,
                               uint8_t **outbuf, ssize_t *outlen);

/**
 * @brief   为protocomm实例添加端点安全性
 *
 * 此API将安全会话建立者绑定到指定的端点名称，以及验证会话客户端所需的任何拥有证明。
 *
 * @note
 *  -端点必须绑定到使用“protocomm_new（）”创建的有效protocomm实例。
 *  -安全性的选择可以是任何“protocomm_security_t”实例。选项“protocomm_security0”和“protocomm-security1”随时可用。
 *
 * @param[in] pc        指向protocomm实例的指针
 * @param[in] ep_name   端点标识符（名称）字符串
 * @param[in] sec       指向端点安全实例的指针
 * @param[in] pop       指向用于验证客户端的占有证明的指针
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_FAIL:添加具有此名称的终结点/终结点时出错已存在
 *  -ESP_ERR_INVALID_STATE:安全终结点已设置
 *  -ESP_ERR_NO_MEM:分配端点资源时出错
 *  -ESP_ERR_INVALID_ARG:空实例/名称/处理程序参数
 */
esp_err_t protocomm_set_security(protocomm_t *pc, const char *ep_name,
                                 const protocomm_security_t *sec,
                                 const protocomm_security_pop_t *pop);

/**
 * @brief   删除protocomm实例的端点安全性
 *
 * 此API将删除由端点名称标识的已注册安全端点。
 *
 * @param[in] pc        指向protocomm实例的指针
 * @param[in] ep_name   端点标识符（名称）字符串
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_NOT_FOUND:具有指定名称的终结点不存在
 *  -ESP_ERR_INVALID_ARG:空实例/名称参数
 */
esp_err_t protocomm_unset_security(protocomm_t *pc, const char *ep_name);

/**
 * @brief   设置版本验证的终结点
 *
 * 此API可用于设置客户端可通过端点验证的特定于应用程序的协议版本。
 *
 * @note
 *  -端点必须绑定到使用“protocomm_new（）”创建的有效protocomm实例。

 * @param[in] pc        指向protocomm实例的指针
 * @param[in] ep_name   端点标识符（名称）字符串
 * @param[in] version   版本标识符（名称）字符串
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_FAIL:添加具有此名称的终结点/终结点时出错已存在
 *  -ESP_ERR_INVALID_STATE:版本终结点已设置
 *  -ESP_ERR_NO_MEM:分配端点资源时出错
 *  -ESP_ERR_INVALID_ARG:空实例/名称/处理程序参数
 */
esp_err_t protocomm_set_version(protocomm_t *pc, const char *ep_name,
                                const char *version);

/**
 * @brief   从protocomm实例中删除版本验证终结点
 *
 * 此API将删除由端点名称标识的已注册版本端点。
 *
 * @param[in] pc        指向protocomm实例的指针
 * @param[in] ep_name   端点标识符（名称）字符串
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_NOT_FOUND:具有指定名称的终结点不存在
 *  -ESP_ERR_INVALID_ARG:空实例/名称参数
 */
esp_err_t protocomm_unset_version(protocomm_t *pc, const char *ep_name);

#ifdef __cplusplus
}
#endif

