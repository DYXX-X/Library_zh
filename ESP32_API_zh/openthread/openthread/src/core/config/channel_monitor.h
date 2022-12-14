/*
 *  版权所有（c）2019，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file 此文件包括通道监视器的编译时配置。
 *
 */

#ifndef CONFIG_CHANNEL_MONITOR_H_
#define CONFIG_CHANNEL_MONITOR_H_

/**
 * @def OPENTHREAD_CONFIG_CHANNEL_MONITOR_ENABLE
 *
 * 定义为1以启用通道监视器支持。
 *
 */
#ifndef OPENTHREAD_CONFIG_CHANNEL_MONITOR_ENABLE
#define OPENTHREAD_CONFIG_CHANNEL_MONITOR_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_CHANNEL_MONITOR_SAMPLE_INTERVAL
 *
 * 通道监视功能使用的采样间隔（毫秒）。

 * 启用时，执行零持续时间能量扫描，在每个间隔期间每个信道采集一个RSSI样本。
 *
 * 仅在启用信道监控功能时适用（即设置了“OPENTHREAD_CONFIG_Channel_MONITOR_ENABLE”）。
 *
 */
#ifndef OPENTHREAD_CONFIG_CHANNEL_MONITOR_SAMPLE_INTERVAL
#define OPENTHREAD_CONFIG_CHANNEL_MONITOR_SAMPLE_INTERVAL 41000
#endif

/**
 * @def OPENTHREAD_CONFIG_CHANNEL_MONITOR_RSSI_THRESHOLD
 *
 * 信道监测功能使用的RSSI阈值（dBm）。
 *
 * RSSI样本与给定阈值进行比较。信道监测报告在观察窗口（每个信道）内高于该阈值的RSSI样本的平均速率。
 *
 * 建议将该值设置为与收音机使用的CCA阈值相同的值。
 *
 * 仅在启用信道监控功能时适用（即设置了“OPENTHREAD_CONFIG_Channel_MONITOR_ENABLE”）。
 *
 */
#ifndef OPENTHREAD_CONFIG_CHANNEL_MONITOR_RSSI_THRESHOLD
#define OPENTHREAD_CONFIG_CHANNEL_MONITOR_RSSI_THRESHOLD -75
#endif

/**
 * @def OPENTHREAD_CONFIG_CHANNEL_MONITOR_SAMPLE_WINDOW
 *
 * 信道监测功能使用的平均采样窗口长度（以信道采样间隔为单位）。
 *
 * 信道监测将在每个采样间隔对所有信道进行采样。它保持在（大约）该采样窗口内高于RSSI阈值的RSSI采样的平均速率。
 *
 * 仅在启用信道监控功能时适用（即设置了“OPENTHREAD_CONFIG_Channel_MONITOR_ENABLE”）。
 *
 */
#ifndef OPENTHREAD_CONFIG_CHANNEL_MONITOR_SAMPLE_WINDOW
#define OPENTHREAD_CONFIG_CHANNEL_MONITOR_SAMPLE_WINDOW 960
#endif

#endif // CONFIG_CHANNEL_MONITOR_H_

