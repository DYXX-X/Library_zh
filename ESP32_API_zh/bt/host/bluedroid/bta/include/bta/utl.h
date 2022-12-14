/******************************************************************************
 * 版权所有（C）2003-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 基本实用功能。
 *
 ******************************************************************************/
#ifndef UTL_H
#define UTL_H

#include "stack/bt_types.h"
// #包括“bt_utils.h”

/*****************************************************************************
**  常量
*****************************************************************************/
/***设备设置类别***/
#define BTA_UTL_SET_COD_MAJOR_MINOR     0x01
#define BTA_UTL_SET_COD_SERVICE_CLASS   0x02 /* 仅设置输入中的位*/
#define BTA_UTL_CLR_COD_SERVICE_CLASS   0x04
#define BTA_UTL_SET_COD_ALL             0x08 /* 将服务类作为输入（可以清除一些设置位！！）*/
#define BTA_UTL_INIT_COD                0x0a

/*****************************************************************************
**  类型定义
*****************************************************************************/

/**对于utl_set_device_class（）**/
typedef struct {
    UINT8       minor;
    UINT8       major;
    UINT16      service;
} tBTA_UTL_COD;


#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************
**  外部函数声明
*****************************************************************************/

/*******************************************************************************
** 函数utl_str2int
**
** 说明此实用程序函数将字符串转换为整数。字符串中可接受的值为0-9。如果无效字符串或字符串值太大，则返回-1。
**
** 出现错误时返回整数值或-1。
**
*******************************************************************************/
extern INT16 utl_str2int(const char *p_s);

/*******************************************************************************
** 函数utl_strucmp
**
** 说明此实用程序函数比较两个大写字符串。字符串p_s必须大写。字符串p_t如果为小写，则转换为大写。如果p_s首先结束，则子字符串匹配被算作匹配。
**
** 如果字符串匹配，则返回0，否则返回非零。
**
*******************************************************************************/
extern int utl_strucmp(const char *p_s, const char *p_t);

/*******************************************************************************
** 函数utl_itoa
**
** 说明此实用程序函数将UINT16转换为字符串。字符串以NULL结尾。返回字符串的长度。
**
** 返回字符串的长度。
**
*******************************************************************************/
extern UINT8 utl_itoa(UINT16 i, char *p_s);

/*******************************************************************************
** 函数utl_freebuf
**
** 说明如果缓冲区指针不为NULL，则此函数调用osi_free释放传入的缓冲区，并将缓冲区指针初始化为NULL。
**
** 返回Nothing。
**
*******************************************************************************/
extern void utl_freebuf(void **p);

/*******************************************************************************
** 函数utl_set_device_class
**
** 说明此函数更新本地设备类。
**
** 参数：p_cod-指向要设置的设备类的指针
**
**                  cmd-要更新的设备类的字段。BTA_UTL_SET_COD_MAJOR_MINOR，-覆盖主要类、次要类BTA_UTL-SET_COD_SERVICE_class-设置输入BTA_UTL_CLR_COD_SERVICE_class中的位-清除输入BTA_UTP_SET_CODE_COD_ALL中的位–覆盖主要类，次要类，设置服务类BTA_UTP_INIT_COD-覆盖主要、次要和服务类
**
** 如果成功，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN utl_set_device_class(tBTA_UTL_COD *p_cod, UINT8 cmd);

/*******************************************************************************
** 函数utl_get_device_class
**
** 说明此函数获取本地设备类。
**
** 参数：p_cod-指向要访问的设备类的指针
**
** 如果成功，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN utl_get_device_class(tBTA_UTL_COD *p_cod);

/*******************************************************************************
** 函数utl_isintstr
**
** 说明此实用程序函数检查给定字符串是否为整数字符串
**
** 如果成功，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN utl_isintstr(const char *p_s);

/*******************************************************************************
** 函数utl_isdialstr
**
** 说明此实用程序函数检查给定字符串是否仅包含拨号数字
**
** 如果成功，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN utl_isdialstr(const char *p_s);

#ifdef __cplusplus
}
#endif

#endif /* UTL_H */

