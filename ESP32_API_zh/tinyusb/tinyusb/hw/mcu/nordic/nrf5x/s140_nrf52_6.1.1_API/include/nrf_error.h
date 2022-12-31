/*
 * 版权所有（c）2014-2017，Nordic Semiconductor ASA保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 * 2.二进制形式的再发行，除非嵌入产品中的Nordic Semiconductor ASA集成电路或该产品的软件更新，否则必须在发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 * 3.未经事先书面许可，不得使用Nordic Semiconductor ASA的名称或其贡献者的名称来支持或推广源自本软件的产品。
 *
 * 4.本软件无论是否经过修改，只能与Nordic Semiconductor ASA集成电路一起使用。
 *
 * 5.根据本许可证以二进制形式提供的任何软件不得进行反向工程、反编译、修改和/或反汇编。
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

 /**
  @defgroup nrf_error SoftDevice全局错误代码@{

  @简要的全局错误定义
*/

/* 收割台护罩*/
#ifndef NRF_ERROR_H__
#define NRF_ERROR_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup NRF_ERRORS_BASE错误代码基数定义
 * @{ */
#define NRF_ERROR_BASE_NUM      (0x0)       ///<全局错误基数
#define NRF_ERROR_SDM_BASE_NUM  (0x1000)    ///<SDM错误基数
#define NRF_ERROR_SOC_BASE_NUM  (0x2000)    ///<SoC错误基数
#define NRF_ERROR_STK_BASE_NUM  (0x3000)    ///<STK错误基数
/** @} */

#define NRF_SUCCESS                           (NRF_ERROR_BASE_NUM + 0)  ///<成功命令
#define NRF_ERROR_SVC_HANDLER_MISSING         (NRF_ERROR_BASE_NUM + 1)  ///<缺少SVC处理程序
#define NRF_ERROR_SOFTDEVICE_NOT_ENABLED      (NRF_ERROR_BASE_NUM + 2)  ///<SoftDevice尚未启用
#define NRF_ERROR_INTERNAL                    (NRF_ERROR_BASE_NUM + 3)  ///<内部错误
#define NRF_ERROR_NO_MEM                      (NRF_ERROR_BASE_NUM + 4)  ///<无操作内存
#define NRF_ERROR_NOT_FOUND                   (NRF_ERROR_BASE_NUM + 5)  ///<未找到
#define NRF_ERROR_NOT_SUPPORTED               (NRF_ERROR_BASE_NUM + 6)  ///<不支持
#define NRF_ERROR_INVALID_PARAM               (NRF_ERROR_BASE_NUM + 7)  ///<无效参数
#define NRF_ERROR_INVALID_STATE               (NRF_ERROR_BASE_NUM + 8)  ///<无效状态，在此状态下不允许操作
#define NRF_ERROR_INVALID_LENGTH              (NRF_ERROR_BASE_NUM + 9)  ///<无效长度
#define NRF_ERROR_INVALID_FLAGS               (NRF_ERROR_BASE_NUM + 10) ///<无效标志
#define NRF_ERROR_INVALID_DATA                (NRF_ERROR_BASE_NUM + 11) ///<无效数据
#define NRF_ERROR_DATA_SIZE                   (NRF_ERROR_BASE_NUM + 12) ///<无效数据大小
#define NRF_ERROR_TIMEOUT                     (NRF_ERROR_BASE_NUM + 13) ///<操作超时
#define NRF_ERROR_NULL                        (NRF_ERROR_BASE_NUM + 14) ///<空指针
#define NRF_ERROR_FORBIDDEN                   (NRF_ERROR_BASE_NUM + 15) ///<禁止操作
#define NRF_ERROR_INVALID_ADDR                (NRF_ERROR_BASE_NUM + 16) ///<坏内存地址
#define NRF_ERROR_BUSY                        (NRF_ERROR_BASE_NUM + 17) ///<忙
#define NRF_ERROR_CONN_COUNT                  (NRF_ERROR_BASE_NUM + 18) ///<超过最大连接计数。
#define NRF_ERROR_RESOURCES                   (NRF_ERROR_BASE_NUM + 19) ///<没有足够的资源进行操作

#ifdef __cplusplus
}
#endif
#endif // NRF_ERROR_H__

/**
  @}
*/

