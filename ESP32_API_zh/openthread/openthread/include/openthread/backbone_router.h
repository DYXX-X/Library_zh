/*
 *  版权所有（c）2019，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread骨干路由器API（线程1.2）
 */

#ifndef OPENTHREAD_BACKBONE_ROUTER_H_
#define OPENTHREAD_BACKBONE_ROUTER_H_

#include <openthread/instance.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api骨干路由器
 *
 * @brief 此模块包括OpenThread骨干路由器服务的功能。
 *
 * @{
 *
 */

/**
 * 此结构表示骨干路由器配置。
 *
 */
typedef struct otBackboneRouterConfig
{
    uint16_t mServer16;            ///<仅在获取线程网络中的主骨干路由器信息时使用
    uint16_t mReregistrationDelay; ///<重新注册延迟（秒）
    uint32_t mMlrTimeout;          ///<多播侦听器注册超时（秒）
    uint8_t  mSequenceNumber;      ///<序列号
} otBackboneRouterConfig;

/**
 * 此函数获取线程网络中的主骨干路由器信息。
 *
 * @param[in]   aInstance            指向OpenThread实例的指针。
 * @param[out]  aConfig              指向放置主骨干路由器信息的位置的指针。
 *
 * @retval OT_ERROR_NONE已成功获取主骨干路由器信息。
 * @retval OT_ERROR_NOT_FOUND不存在主骨干路由器。
 *
 */
otError otBackboneRouterGetPrimary(otInstance *aInstance, otBackboneRouterConfig *aConfig);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_BACKBONE_ROUTER_H_

