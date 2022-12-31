/*
 *  版权所有（c）2019，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 该文件包括平台OTNS实用程序的抽象。
 *
 *   OTNS是一个OpenThread网络模拟器，它使用OpenThread模拟实例模拟线程网络，并提供这些模拟网络的可视化和管理。提到https://github.com/openthread/ot-ns有关OTNS的更多信息。
 */

#ifndef OPENTHREAD_PLATFORM_OTNS_H_
#define OPENTHREAD_PLATFORM_OTNS_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup 平板天线
 *
 * @brief 该模块包括OTNS的平台抽象。
 *
 * @{
 *
 */

/**
 * 此功能将状态信息导出到OTNS。
 *
 * 状态信息由OTNS可识别格式的以空结尾的字符串表示。对“otPlatOtnsStatus”的每次调用都可以发送多个状态，以“；”分隔，e、 x.“parid=577fbc37；lrid=5”。每个状态包含由“=”分隔的键和值。状态值可以使用'，'，e.x.“ping_request=fde:ad00:beef:0:459e:d7b4:b65e:5480,4112000”进一步分隔为多个字段。
 *
 * 新状态应遵循这些约定。
 *
 * 目前，OTNS仅支持虚拟时间模拟。
 *
 * @param[in]  aStatus  状态字符串。
 *
 */
void otPlatOtnsStatus(const char *aStatus);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_PLATFORM_OTNS_H_

