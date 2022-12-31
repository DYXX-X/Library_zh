/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */


#ifndef _HTTP_UTILS_H_
#define _HTTP_UTILS_H_
#include <sys/time.h>

/**
 * @brief      将new_str分配给*str指针，如果不为NULL，则重新分配*str
 *
 * @param      str      字符串指针
 * @param      new_str  将此字符串分配给str
 * @param      len      字符串长度，如果new_str以零结尾，则小于0
 *
 * @return
 *  -new_str指针
 *  - NULL
 */
char *http_utils_assign_string(char **str, const char *new_str, int len);

/**
 * @brief      如果new_str不为NULL，则重新分配*str并将new_str附加到它；如果new_str为NULL，则返回*str指针
 *
 * @param      str      字符串指针
 * @param      new_str  将此字符串附加到str
 * @param      len      字符串长度，如果new_str以零结尾，则小于0
 *
 * @return
 *  -*str指针
 */
char *http_utils_append_string(char **str, const char *new_str, int len);

/**
 * @brief      删除字符串开头和结尾的空白
 *
 * @param[in]  str   字符串
 *
 * @return     已修剪新字符串
 */
void http_utils_trim_whitespace(char **str);

/**
 * @brief      获取介于2个字符串之间的字符串。它将为此字符串分配一个新的内存空间，因此您需要在不再使用时释放它
 *
 * @param[in]  str    源字符串
 * @param[in]  begin  开始字符串
 * @param[in]  end    结束字符串
 *
 * @return     开始和结束之间的字符串
 */
char *http_utils_get_string_between(const char *str, const char *begin, const char *end);

/**
 * @brief      将两个字符串合并为一个它将为此字符串分配一个新的内存空间，因此您需要在不再使用时释放它
 *
 * @param[in]  first_str   第一个字符串
 * @param[in]  len_first   长度优先
 * @param[in]  second_str  第二个字符串
 * @param[in]  len_second  长度秒
 *
 * @return
 * -新建字符串指针
 * -NULL：输入无效
 */
char *http_utils_join_string(const char *first_str, size_t len_first, const char *second_str, size_t len_second);

/**
 * @brief      检查“str”是否以“start”开头``
 *
 * @param[in]  str    字符串
 * @param[in]  start  开始
 *
 * @return
 *     -（-1）如果“start”的长度大于“str”的长度``
 *     -（1）如果“start”“NOT”以“start”开头``
 *     -（0）如果“str”以“start”开头``
 */
int http_utils_str_starts_with(const char *str, const char *start);


#define HTTP_MEM_CHECK(TAG, a, action) if (!(a)) {                                                  \
        ESP_LOGE(TAG,"%s(%d): %s", __FUNCTION__, __LINE__, "Memory exhausted");                     \
        action;                                                                                     \
        }

#endif

