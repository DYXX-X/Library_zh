/*
                            ____ __ ___ \\/__ __ __ | | _/_ \\/|'_ \/_ ` | __ | | __//\ | | _）|（_ | | | _ \ ___//\ \.__/\ __，_ | \ __ | | | | __ | XML解析器

   版权所有（c）1997-2000 Thai Open Source Software Center Ltd版权所有（c）2000 Clark Cooper<coopercc@users.sourceforge.net>版权所有（c）2002 Fred L.Drake，Jr<fdrake@users.sourceforge.net>版权所有（c）2017 Sebastian Pipping<sebastian@pipping.org>根据MIT许可证获得许可：

   特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

   上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

   THE  SOFTWARE  IS  PROVIDED  "AS  IS",  WITHOUT  WARRANTY  OF  ANY  KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/* 像腹水。h、 除了0xD具有代码BT_S而不是BT_CR*/
/* 0x00位*/ BT_NONXML, BT_NONXML, BT_NONXML, BT_NONXML,
    /* 0x04*/ BT_NONXML, BT_NONXML, BT_NONXML, BT_NONXML,
    /* 0x08*/ BT_NONXML, BT_S, BT_LF, BT_NONXML,
    /* 0x0C*/ BT_NONXML, BT_S, BT_NONXML, BT_NONXML,
    /* 0x10像素*/ BT_NONXML, BT_NONXML, BT_NONXML, BT_NONXML,
    /* 0x14像素*/ BT_NONXML, BT_NONXML, BT_NONXML, BT_NONXML,
    /* 0x18像素*/ BT_NONXML, BT_NONXML, BT_NONXML, BT_NONXML,
    /* 0摄氏度*/ BT_NONXML, BT_NONXML, BT_NONXML, BT_NONXML,
    /* 20倍*/ BT_S, BT_EXCL, BT_QUOT, BT_NUM,
    /* 0时24分*/ BT_OTHER, BT_PERCNT, BT_AMP, BT_APOS,
    /* 第28位*/ BT_LPAR, BT_RPAR, BT_AST, BT_PLUS,
    /* 0x2摄氏度*/ BT_COMMA, BT_MINUS, BT_NAME, BT_SOL,
    /* 0x30*/ BT_DIGIT, BT_DIGIT, BT_DIGIT, BT_DIGIT,
    /* 0x34个*/ BT_DIGIT, BT_DIGIT, BT_DIGIT, BT_DIGIT,
    /* 0x38个*/ BT_DIGIT, BT_DIGIT, BT_COLON, BT_SEMI,
    /* 0x3C级*/ BT_LT, BT_EQUALS, BT_GT, BT_QUEST,
    /* 0x40倍*/ BT_OTHER, BT_HEX, BT_HEX, BT_HEX,
    /* 第44位*/ BT_HEX, BT_HEX, BT_HEX, BT_NMSTRT,
    /* 0x48秒*/ BT_NMSTRT, BT_NMSTRT, BT_NMSTRT, BT_NMSTRT,
    /* 0x4C倍*/ BT_NMSTRT, BT_NMSTRT, BT_NMSTRT, BT_NMSTRT,
    /* 50倍*/ BT_NMSTRT, BT_NMSTRT, BT_NMSTRT, BT_NMSTRT,
    /* 0时54分*/ BT_NMSTRT, BT_NMSTRT, BT_NMSTRT, BT_NMSTRT,
    /* 0x58倍*/ BT_NMSTRT, BT_NMSTRT, BT_NMSTRT, BT_LSQB,
    /* 0x5厘米*/ BT_OTHER, BT_RSQB, BT_OTHER, BT_NMSTRT,
    /* 0x60倍*/ BT_OTHER, BT_HEX, BT_HEX, BT_HEX,
    /* 0x64位*/ BT_HEX, BT_HEX, BT_HEX, BT_NMSTRT,
    /* 0x68像素*/ BT_NMSTRT, BT_NMSTRT, BT_NMSTRT, BT_NMSTRT,
    /* 0x6C*/ BT_NMSTRT, BT_NMSTRT, BT_NMSTRT, BT_NMSTRT,
    /* 0倍70*/ BT_NMSTRT, BT_NMSTRT, BT_NMSTRT, BT_NMSTRT,
    /* 0时74分*/ BT_NMSTRT, BT_NMSTRT, BT_NMSTRT, BT_NMSTRT,
    /* 0秒78*/ BT_NMSTRT, BT_NMSTRT, BT_NMSTRT, BT_OTHER,
    /* 0x7C*/ BT_VERBAR, BT_OTHER, BT_OTHER, BT_OTHER,
