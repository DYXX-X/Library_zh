/*
 * 选项h—用于处理CoAP PDU中的选项的助手
 *
 * 版权所有（C）2010-2013 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/**
 * @file 选项.h
 * @brief CoAP PDU中处理选项的助手
 */

#ifndef COAP_OPTION_H_
#define COAP_OPTION_H_

typedef uint16_t coap_option_num_t;

/**
 * 这里使用面向字节的访问方法，因为在数据缓冲区上滑动复杂结构coap_opt_t可能会导致某些平台上的总线错误。
 */
typedef uint8_t coap_opt_t;
#define PCHAR(p) ((coap_opt_t *)(p))

/**
 * CoAP选项的表示。
 */
typedef struct {
  uint16_t delta;
  size_t length;
  const uint8_t *value;
} coap_option_t;

/**
 * Parses the option pointed to by @p 选择@p结果。此函数返回已解析的字节数，错误时返回@c 0。当遇到非法的增量或长度值时，或者当选项解析将导致读取超过选项时（即超过opt+length），会发出错误信号。
 *
 * @param opt    要分析的选项的开头。
 * @param length @popt的最大长度。
 * @param result 指向coap_option_t结构的指针，如果coap_opt_parse（）>0，则该结构将填充实际值。
 * @return       分析的字节数或出错时的@c 0。
 */
size_t coap_opt_parse(const coap_opt_t *opt,
                      size_t length,
                      coap_option_t *result);

/**
 * 返回给定选项的大小，考虑可能的选项跳转。
 *
 * @param opt 选项跳转或选项的开头。
 * @return    @popt和选项结尾之间的字节数
 *            starting at @p 选择如果出现错误，此函数将返回
 *            @c 0作为选项需要至少一个字节的存储空间。
 */
size_t coap_opt_size(const coap_opt_t *opt);

/**
 * @defgroup opt_filter选项过滤器用于访问选项过滤器的API函数@{
 */

/**
 * 可存储在选项过滤器中的选项类型数低于256。COAP_OPT_FILTER_SHORT+COAP_OPT_FILTER_LONG必须最多为16。每个COAP_option_FILTER_t对象为短选项保留（（COAP_OP_FILTER_SHORT+1）/2）2个字节。
 */
#define COAP_OPT_FILTER_SHORT 6

/**
 * 可以存储在选项筛选器中的选项类型数超过255。COAP_OPT_FILTER_SHORT+COAP_OPT _FILTER_LONG必须最多为16。每个COAP_option_FILTER_t对象为短选项保留COAP_OP_FILTER_LONG 2个字节。
 */
#define COAP_OPT_FILTER_LONG  2

/* 确保COAP_OPT_FILTER_SHORT和COAP_OPT _FILTER_LONG设置正确。*/
#if (COAP_OPT_FILTER_SHORT + COAP_OPT_FILTER_LONG > 16)
#error COAP_OPT_FILTER_SHORT + COAP_OPT_FILTER_LONG must be less or equal 16
#endif /* (COAP_OPT_FILTER_SHORT + COAP_OPT_FILTER_LONG > 16) */

/*
 * 掩码包含一个位向量，该位向量指示使用long_opts[]和随后的short_opts[]中的哪些字段。第一个COAP_OPT_FILTER_LONG位对应于存储在LONG_opts[]元素中的长选项类型。下一个COAP_OPT_FILTER_SHORT位对应于存储在SHORT_opts[]中的短选项类型。
 */
typedef struct coap_opt_filter_t {
  uint16_t mask;
  uint16_t long_opts[COAP_OPT_FILTER_LONG];
  uint8_t short_opts[COAP_OPT_FILTER_SHORT];
} coap_opt_filter_t;

/**包含所有选项的预定义筛选器。*/
#define COAP_OPT_ALL NULL

/**
 * 清除filter@p filter。
 *
 * @param filter 要清除的过滤器。
 */
void
coap_option_filter_clear(coap_opt_filter_t *filter);

/**
 * 为@p筛选器中的@p编号设置相应的条目。这
 * function returns @c 如果位被设置为1或出现错误时为@c 0（即，当给定的数字不适合过滤器时）。
 *
 * @param filter 要更改的筛选器对象。
 * @param number 应为其设置位的选项编号。
 *
 * @return       @如果位已设置，则为c 1，否则为@c 0。
 */
int coap_option_filter_set(coap_opt_filter_t *filter, coap_option_num_t number);

/**
 * 清除@p筛选器中@p编号的对应条目。这
 * function returns @c 如果位被设置为1或出现错误时为@c 0（即，当给定的数字不适合过滤器时）。
 *
 * @param filter 要更改的筛选器对象。
 * @param number 应从过滤器中清除的选项编号。
 *
 * @return       @如果位已设置，则为c 1，否则为@c 0。
 */
int coap_option_filter_unset(coap_opt_filter_t *filter,
                             coap_option_num_t number);

/**
 * Checks if @p 数字包含在@p筛选器中。此函数返回
 * @c 如果找到，则为1；如果没有，则为@c 0；如果出现错误，则为@c-1（即，当给定的数字不适合过滤器时）。
 *
 * @param filter 要搜索的筛选器对象。
 * @param number 要搜索的选项编号。
 *
 * @return       @如果找到@p编号，则为c 1；否则为@c 0；如果出现错误，则为@c-1。
 */
int coap_option_filter_get(coap_opt_filter_t *filter, coap_option_num_t number);

/**
 * 遍历PDU选项的迭代器。必须使用coap_option_iterator_init（）初始化此对象。调用coap_option_next（）遍历选项列表，直到coap_option_next（）返回@c NULL。
 *
 * @code
 * coap_opt_t*选项；
 * coap_opt_iterator_topt_iter；
 * coap_option_iterator_init（pdu，&opt_iter，coap_opt_ALL）；
 *
 * while（（选项=coap_option_next（&opt_iter）））{
 *   …使用选项。。。
 * }
 * @endcode
 */
typedef struct {
  size_t length;                /**<PDU剩余长度*/
  coap_option_num_t number;     /**<解码选项编号*/
  unsigned int bad:1;           /**＜如果未设置迭代器对象，则该对象正常*/
  unsigned int filtered:1;      /**<表示是否使用过滤器*/
  coap_opt_t *next_option;      /**<指向未分析的下一个选项的指针*/
  coap_opt_filter_t filter;     /**<选项筛选器*/
} coap_opt_iterator_t;

/**
 * 初始化给定的选项迭代器@poi以指向
 * @p pdu的选项列表。此函数在成功时返回@p oi，否则返回@c NULL（即，当不存在选项时）。注意，在调用coap_option_iterator_init（）之前，必须对选项列表执行长度检查。
 *
 * @param pdu    应遍历其选项的PDU。
 * @param oi     将初始化的迭代器对象。
 * @param filter 可选选项编号过滤器。
 *               With @p 数字！=@c COAP_OPT_ALL，COAP_option_next（）将仅返回与此位掩码匹配的选项。围栏柱选项@c 14、@c 28、@c 42、…始终被跳过。
 *
 * @return       迭代器对象@p oi成功，否则@c NULL。
 */
coap_opt_iterator_t *coap_option_iterator_init(const coap_pdu_t *pdu,
                                               coap_opt_iterator_t *oi,
                                               const coap_opt_filter_t *filter);

/**
 * Updates the iterator @p oi指向下一个选项。此函数返回
 * a pointer to that option or @c 如果不存在更多选项，则为NULL。的内容
 * @p oi将被更新。特别是，@coi->n指定当前选项的
 * ordinal number (counted from @c 1） ，@coi->number是选项的编号
 * value, and @c oi->option指向当前选项本身的开头。当经过最后一个选项时，@coi->选项将为@c NULL。
 *
 * 请注意，跳过的选项在使用coap_option_iterator_init（）指定的筛选器中的对应位为@c0。因此，将始终返回带有不适合此筛选器的数字的选项。
 *
 * @param oi 要更新的选项迭代器。
 *
 * @return   下一个选项或@c NULL（如果没有其他选项）。
 */
coap_opt_t *coap_option_next(coap_opt_iterator_t *oi);

/**
 * Retrieves the first option of number @p 来自@p pdu的数字@p oi必须指向一个coap_opt_iterator_t对象，该对象将由该函数初始化，以仅过滤带有number@p number的选项。此函数返回带有此数字的第一个选项，如果找不到，则返回@c NULL。
 *
 * @param pdu  要分析选项的PDU。
 * @param number 要搜索的选项编号。
 * @param oi   要使用的迭代器对象。
 *
 * @return     指向数字@p number的第一个选项的指针，如果找不到则返回@c NULL。
 */
coap_opt_t *coap_check_option(const coap_pdu_t *pdu,
                              coap_option_num_t number,
                              coap_opt_iterator_t *oi);

/**
 * Encodes the given delta and length values into @p 选择此函数返回编码@p delta和@p length或@c 0所需的字节数。请注意，结果指示必须提前多少字节@popt才能编码选项值。
 *
 * @param opt    写入@p delta和@p length的选项缓冲区空间。
 * @param maxlen @popt的最大长度。
 * @param delta  要编码的实际增量值。
 * @param length 要编码的实际长度值。
 *
 * @return       使用的字节数或出错时的@c 0。
 */
size_t coap_opt_setheader(coap_opt_t *opt,
                          size_t maxlen,
                          uint16_t delta,
                          size_t length);

/**
 * 使用给定的@p增量和
 * @p 长
 *
 * @param delta  选项delta。
 * @param length 选项长度。
 *
 * @return       编码此选项所需的字节数。
 */
size_t coap_opt_encode_size(uint16_t delta, size_t length);

/**
 * Encodes option with given @p 增量到@popt。此函数返回
 * number of bytes written to @p opt或@c 0出错。这种情况尤其发生
 * when @p opt没有提供足够的空间来存储选项值、增量和选项跳转。
 *
 * @param opt    写入@p val的选项缓冲区空间。
 * @param n      @p opt.的最大长度。
 * @param delta  选项delta。
 * @param val    要复制到@popt的选项值。
 * @param length @p值的实际长度。
 *
 * @return       错误时写入@popt或@c 0的字节数。返回值始终小于@p n。
 */
size_t coap_opt_encode(coap_opt_t *opt,
                       size_t n,
                       uint16_t delta,
                       const uint8_t *val,
                       size_t length);

/**
 * Returns the length of the given option. @p opt必须指向选项跳转或选项的开头。当@popt不是选项或@popt的实际长度（也可以是@c 0）时，此函数返回@c 0。
 *
 * @note ｛在出现错误时使用@c0的基本原理是，在大多数情况下，此函数的结果用于跳过下一个coap_opt_length（）字节。｝
 *
 * @param opt  应返回其长度的选项。
 *
 * @return     未定义选项的长度或@c 0。
 */
uint32_t coap_opt_length(const coap_opt_t *opt);

/**
 * Returns a pointer to the value of the given option. @p opt必须指向选项跳转或选项的开头。如果
 * @p opt不是有效选项。
 *
 * @param opt 应返回其值的选项。
 *
 * @return    指向选项值的指针或出错时的@c NULL。
 */
const uint8_t *coap_opt_value(const coap_opt_t *opt);

/**
 * 表示要安装的CoAP选项的链接列表。
 *
 * @code
 * coap_optlist_t*optlist_chain=空；
 * coap_pdu_t*pdu=coap_new_pdu（会话）；
 *
 * …其他设置代码。。。
 * coap_insert_optlist（&optlist_chain，
 *                    COAP_OBSERVE_ESTABLISH, NULL));
 *
 * coap_add_optlist_pdu（pdu，&optlist_chain）；
 * …其他代码。。。
 * coap_delete_optlist（optlist_chain）；
 * @endcode
 */
typedef struct coap_optlist_t {
  struct coap_optlist_t *next;  /**<optlist链中的下一个条目*/
  uint16_t number;              /**<选项编号（无增量编码）*/
  size_t length;                /**<选项值长度*/
  uint8_t *data;                /**<选项数据*/
} coap_optlist_t;

/**
 * 创建新的optlist条目。
 *
 * 注意：在可能的情况下，需要将选项数据去掉前导零（大端），以减少PDU中所需的数据量，并且在某些情况下，如果不去掉，可能会超过光电二极管的最大数据大小，因此是非法的。这是通过使用coap_encode_var_safe（）或coap_encode _var_ssafe8（）完成的。
 *
 * @param number    选项编号（COAP_option_*）
 * @param length    选项长度
 * @param data      期权价值数据
 *
 * @return          指向新optlist项的指针，如果出现错误，则返回@c NULL
 */
coap_optlist_t *coap_new_optlist(uint16_t number,
                                 size_t length,
                                 const uint8_t *data);

/**
 * The current optlist of @p optlist_chain首先被排序（根据RFC7272排序要求），然后被添加到@ppdu。
 *
 * @param pdu  要从链列表中添加选项的pdu
 * @param optlist_chain 要添加到pdu的optlist的链接列表
 *
 * @return     @c 1（如果成功）或@c 0（如果失败）；
 */
int coap_add_optlist_pdu(coap_pdu_t *pdu, coap_optlist_t** optlist_chain);

/**
 * Adds @p optlist到给定的@p optlist_chain。在初始调用coap_insert_optlist（）之前，optlist_chain变量设置为NULL。当不再需要optlist_chain时，需要使用coap_delete_optlist（）删除它。
 *
 * @param optlist_chain 要向其中添加optlist的链
 * @param optlist  要添加到队列的optlist
 *
 * @return         @如果成功，则为c 1，否则为@c 0。
 */
int coap_insert_optlist(coap_optlist_t **optlist_chain,
                        coap_optlist_t *optlist);

/**
 * Removes all entries from the @p optlist_chain，释放内存使用。
 *
 * @param optlist_chain 要从中删除所有条目的optlist链
 */
void coap_delete_optlist(coap_optlist_t *optlist_chain);

/** @} */

/**
 * Sets the corresponding bit for @p 键入@p筛选器。此函数返回@c
 * 1 if bit was set or @c -1错误（即当给定类型不适合过滤器时）。
 *
 * @deprecated 请改用coap_option_filter_set（）。
 *
 * @param filter 要更改的筛选器对象。
 * @param type   应为其设置位的类型。
 *
 * @return       @如果位已设置，则为c 1，否则为@c-1。
 */
COAP_STATIC_INLINE COAP_DEPRECATED int
coap_option_setb(coap_opt_filter_t *filter, uint16_t type) {
  return coap_option_filter_set(filter, type) ? 1 : -1;
}

/**
 * Clears the corresponding bit for @p 键入@p筛选器。此函数返回
 * @c 如果位被清除，则为1；如果出现错误，则为@c-1（即，当给定类型不适合过滤器时）。
 *
 * @deprecated 请改用coap_option_filter_unset（）。
 *
 * @param filter 要更改的筛选器对象。
 * @param type   应清除其位的类型。
 *
 * @return       @如果位已设置，则为c 1，否则为@c-1。
 */
COAP_STATIC_INLINE COAP_DEPRECATED int
coap_option_clrb(coap_opt_filter_t *filter, uint16_t type) {
  return coap_option_filter_unset(filter, type) ? 1 : -1;
}

/**
 * Gets the corresponding bit for @p 键入@p筛选器。此函数返回@c
 * 1 if the bit is set @c 如果不是，则为0；如果错误，则为@c-1（即，当给定类型不适合过滤器时）。
 *
 * @deprecated 请改用coap_option_filter_get（）。
 *
 * @param filter 要从中读取位的筛选器对象。
 * @param type   应读取其位的类型。
 *
 * @return       @如果位已设置，则为c 1；如果未设置，则@c 0；如果错误，则为@c-1。
 */
COAP_STATIC_INLINE COAP_DEPRECATED int
coap_option_getb(coap_opt_filter_t *filter, uint16_t type) {
  return coap_option_filter_get(filter, type);
}

#endif /* COAP_OPTION_H_ */

