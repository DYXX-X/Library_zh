/*
 * 魔术h-PPP幻数定义。
 *
 * 版权所有（c）1984-2000卡内基梅隆大学。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 * 2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 * 3.未经事先书面许可，不得使用“卡耐基梅隆大学”的名称来支持或推广源自本软件的产品。如需获得许可或任何法律详情，请联系卡内基梅隆大学技术转让办公室，地址：宾夕法尼亚州匹兹堡福布斯大道5000号，邮编：15213-3890（412）268-4387，传真：（412）268-7395tech-transfer@andrew.cmu.edu
 *
 * 4.任何形式的再分发都必须保留以下确认：“本产品包括由卡内基梅隆大学计算服务部开发的软件(http://www.cmu.edu/computing/)."
 *
 * CARNEGIE MELLON UNIVERSITY DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * $Id：魔法。h、 v 1.5 2003/06/11 23:56:26 paulus展览$
 */
/*****************************************************************************
* randm公司。h-随机数生成器头文件。
*
* 版权所有（c）2003 Marc Boucher，Services Informatiques（MBSI）inc.版权所有（c）1998 Global Election Systems inc。
*
* 作者特此授予出于任何目的使用、复制、修改、分发和许可本软件及其文档的权利，前提是所有副本中保留现有版权声明，并且本声明和以下免责声明均包含在任何分发中。任何授权用途都不需要书面协议、许可证或版税。
*
* THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS *AS IS* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************** REVISION HISTORY
*
* 03-01-01马克·鲍彻<marc@mbsi.ca>移植到lwIP。
* 98-05-29 Guy Lancaster <glanca@gesn.com>, 全球选举系统公司摘自avos。
*****************************************************************************/

#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#ifndef MAGIC_H
#define MAGIC_H

#ifdef __cplusplus
extern "C" {
#endif

/***********************
*** PUBLIC FUNCTIONS ***
***********************/

/*
 * 初始化随机数生成器。
 */
void magic_init(void);

/*
 * 随机化我们的随机种子值。对于真正的随机事件（如用户操作和网络流量）调用。
 */
void magic_randomize(void);

/*
 * 返回一个新的随机数。
 */
u32_t magic(void);	/* 返回下一个幻数*/

/*
 * 用随机字节填充缓冲区
 *
 * 使用随机池生成随机数据。当使用的速度快于使用magic_churnrand（）提供的随机性时，这会退化为伪随机。因此，重要的是要确保不会直接公布结果，因为人们至少可以在某种程度上预测下一个结果。此外，在第一次使用前获得一粒好种子很重要。
 */
void magic_random_bytes(unsigned char *buf, u32_t buf_len);

/*
 * 返回一个介于0和（2^pow）-1之间的新随机数。
 */
u32_t magic_pow(u8_t pow);

#ifdef __cplusplus
}
#endif

#endif /* MAGIC_H */

#endif /* PPP_SUPPORT */

