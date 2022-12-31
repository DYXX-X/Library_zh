/* 线路噪声。h——版本1.0
 *
 * Guerrilla行编辑库反对一个行编辑库需要20000行C代码的想法。
 *
 * 请参见线路噪声。c了解更多信息。
 *
 * ------------------------------------------------------------------------
 *
 * 版权所有（c）2010-2014，Salvatore Sanfilippo＜antirez at gmail dot com＞版权所有（c）2010-2013，Pieter Noordhuis＜pcnoordhuis at gmail.com＞
 *
 * 保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 *  *源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 *  *二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __LINENOISE_H
#define __LINENOISE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef struct linenoiseCompletions {
  size_t len;
  char **cvec;
} linenoiseCompletions;

typedef void(linenoiseCompletionCallback)(const char *, linenoiseCompletions *);
typedef char*(linenoiseHintsCallback)(const char *, int *color, int *bold);
typedef void(linenoiseFreeHintsCallback)(void *);
void linenoiseSetCompletionCallback(linenoiseCompletionCallback *);
void linenoiseSetHintsCallback(linenoiseHintsCallback *);
void linenoiseSetFreeHintsCallback(linenoiseFreeHintsCallback *);
void linenoiseAddCompletion(linenoiseCompletions *, const char *);

int linenoiseProbe(void);
char *linenoise(const char *prompt);
void linenoiseFree(void *ptr);
int linenoiseHistoryAdd(const char *line);
int linenoiseHistorySetMaxLen(int len);
int linenoiseHistorySave(const char *filename);
int linenoiseHistoryLoad(const char *filename);
void linenoiseHistoryFree(void);
void linenoiseClearScreen(void);
void linenoiseSetMultiLine(int ml);
void linenoiseSetDumbMode(int set);
bool linenoiseIsDumbMode(void);
void linenoisePrintKeyCodes(void);
void linenoiseAllowEmpty(bool);
int linenoiseSetMaxLineLen(size_t len);

#ifdef __cplusplus
}
#endif

#endif /* __LINENOISE_H */

