/*
 * 版权所有（c）2010 Serge A.Zaitsev
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file jsmn.h
 * @brief JSMN（Jasmine）JSON解析器的定义。
 *
 * 有关JSMN的更多信息：
 * @see http://zserge.com/jsmn.html
 */

#ifndef __JSMN_H_
#define __JSMN_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * JSON类型标识符。基本类型有：o Object o Array o String o其他原语：number、boolean（true/false）或null
 */
typedef enum {
	JSMN_UNDEFINED = 0,
	JSMN_OBJECT = 1,
	JSMN_ARRAY = 2,
	JSMN_STRING = 3,
	JSMN_PRIMITIVE = 4
} jsmntype_t;

enum jsmnerr {
	/* 没有提供足够的令牌*/
	JSMN_ERROR_NOMEM = -1,
	/* JSON字符串中的字符无效*/
	JSMN_ERROR_INVAL = -2,
	/* 字符串不是完整的JSON数据包，需要更多字节*/
	JSMN_ERROR_PART = -3
};

/**
 * JSON令牌描述。
 * @param		type	type (object, 数组、字符串等）
 * @param		start	start position JSON数据字符串
 * @param		end		end position JSON数据字符串
 */
typedef struct {
	jsmntype_t type;
	int start;
	int end;
	int size;
#ifdef JSMN_PARENT_LINKS
	int parent;
#endif
} jsmntok_t;

/**
 * JSON解析器。包含可用的令牌块数组。还存储当前正在解析的字符串以及该字符串中的当前位置
 */
typedef struct {
	unsigned int pos; /* JSON字符串中的偏移量*/
	unsigned int toknext; /* 要分配的下一个令牌*/
	int toksuper; /* 上级标记节点，例如父对象或数组*/
} jsmn_parser;

/**
 * 在令牌数组上创建JSON解析器
 */
void jsmn_init(jsmn_parser *parser);

/**
 * 运行JSON解析器。它将一个JSON数据字符串解析为一个标记数组，每个标记描述一个JSON对象。
 */
int jsmn_parse(jsmn_parser *parser, const char *js, size_t len,
		jsmntok_t *tokens, unsigned int num_tokens);

#ifdef __cplusplus
}
#endif

#endif /* __JSMN_H_ */

