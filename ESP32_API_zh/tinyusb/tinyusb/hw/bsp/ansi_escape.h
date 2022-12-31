/* 
 * MIT许可证（MIT）
 *
 * 版权所有（c）2019 Ha Thach（tinyusb.org）
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * 此文件是TinyUSB堆栈的一部分。
 */

/** \inggroup group_board\defgroup group_ansi_esc ansi Esacpe代码
 *  @{ */

#ifndef _TUSB_ANSI_ESC_CODE_H_
#define _TUSB_ANSI_ESC_CODE_H_


#ifdef __cplusplus
 extern "C" {
#endif

#define CSI_CODE(seq)   "\33[" seq
#define CSI_SGR(x)      CSI_CODE(#x) "m"

//-------------光标移动-------------//
/** \defgroup group_ans_cursor光标移动
 *  @{ */
#define ANSI_CURSOR_UP(n)        CSI_CODE(#n "A")          ///<向上移动光标
#define ANSI_CURSOR_DOWN(n)      CSI_CODE(#n "B")          ///<向下移动光标
#define ANSI_CURSOR_FORWARD(n)   CSI_CODE(#n "C")          ///<向前移动光标
#define ANSI_CURSOR_BACKWARD(n)  CSI_CODE(#n "D")          ///<向后移动光标
#define ANSI_CURSOR_LINE_DOWN(n) CSI_CODE(#n "E")          ///<将光标向下移动到行（n）的开头
#define ANSI_CURSOR_LINE_UP(n)   CSI_CODE(#n "F")          ///<将光标向上移动到行（n）的开头
#define ANSI_CURSOR_POSITION(n, m) CSI_CODE(#n ";" #m "H") ///<将光标移动到位置（n，m）
/** @} */

//-------------屏幕-------------//
/** \defgroup group_ans_screen屏幕控件
 *  @{ */
#define ANSI_ERASE_SCREEN(n)     CSI_CODE(#n "J") ///<擦除屏幕
#define ANSI_ERASE_LINE(n)       CSI_CODE(#n "K") ///<擦除行（n）
#define ANSI_SCROLL_UP(n)        CSI_CODE(#n "S") ///<向上滚动整页（n）行
#define ANSI_SCROLL_DOWN(n)      CSI_CODE(#n "T") ///<向下滚动整页（n）行
/** @} */

//-------------文本颜色-------------//
/** \defgroup group_ans_text文本颜色
 *  @{ */
#define ANSI_TEXT_BLACK          CSI_SGR(30)
#define ANSI_TEXT_RED            CSI_SGR(31)
#define ANSI_TEXT_GREEN          CSI_SGR(32)
#define ANSI_TEXT_YELLOW         CSI_SGR(33)
#define ANSI_TEXT_BLUE           CSI_SGR(34)
#define ANSI_TEXT_MAGENTA        CSI_SGR(35)
#define ANSI_TEXT_CYAN           CSI_SGR(36)
#define ANSI_TEXT_WHITE          CSI_SGR(37)
#define ANSI_TEXT_DEFAULT        CSI_SGR(39)
/** @} */

//-------------背景色-------------//
/** \defgroup group_ans_background背景色
 *  @{ */
#define ANSI_BG_BLACK            CSI_SGR(40)
#define ANSI_BG_RED              CSI_SGR(41)
#define ANSI_BG_GREEN            CSI_SGR(42)
#define ANSI_BG_YELLOW           CSI_SGR(43)
#define ANSI_BG_BLUE             CSI_SGR(44)
#define ANSI_BG_MAGENTA          CSI_SGR(45)
#define ANSI_BG_CYAN             CSI_SGR(46)
#define ANSI_BG_WHITE            CSI_SGR(47)
#define ANSI_BG_DEFAULT          CSI_SGR(49)
/** @} */

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_ANSI_ESC_CODE_H_ */

/** @} */

