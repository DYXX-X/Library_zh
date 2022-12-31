/*
** mruby/version.h-mruby版本定义
**
** 参见mruby.h中的版权声明
*/

#ifndef MRUBY_VERSION_H
#define MRUBY_VERSION_H

#include "common.h"

/**
 * mruby版本定义宏
 */
MRB_BEGIN_DECL

/*
 * 传入的表达式。
 */
#define MRB_STRINGIZE0(expr) #expr

/*
 * 将表达式传递给MRB_STRINGIZE0。
 */
#define MRB_STRINGIZE(expr) MRB_STRINGIZE0(expr)

/*
 * mruby使用的Ruby版本。
 */
#define MRUBY_RUBY_VERSION "2.0"

/*
 * Ruby引擎。
 */
#define MRUBY_RUBY_ENGINE  "mruby"

/*
 * 主要版本号。
 */
#define MRUBY_RELEASE_MAJOR 2

/*
 * 次要版本号。
 */
#define MRUBY_RELEASE_MINOR 0

/*
 * 发布版本号很小。
 */
#define MRUBY_RELEASE_TEENY 1

/*
 * mruby版本。
 */
#define MRUBY_VERSION MRB_STRINGIZE(MRUBY_RELEASE_MAJOR) "." MRB_STRINGIZE(MRUBY_RELEASE_MINOR) "." MRB_STRINGIZE(MRUBY_RELEASE_TEENY)

/*
 * 版本号。
 */
#define MRUBY_RELEASE_NO (MRUBY_RELEASE_MAJOR * 100 * 100 + MRUBY_RELEASE_MINOR * 100 + MRUBY_RELEASE_TEENY)

/*
 * 发布年份。
 */
#define MRUBY_RELEASE_YEAR 2019

/*
 * 发布月份。
 */
#define MRUBY_RELEASE_MONTH 4

/*
 * 发布日。
 */
#define MRUBY_RELEASE_DAY 4

/*
 * 发布日期为字符串。
 */
#define MRUBY_RELEASE_DATE MRB_STRINGIZE(MRUBY_RELEASE_YEAR) "-" MRB_STRINGIZE(MRUBY_RELEASE_MONTH) "-" MRB_STRINGIZE(MRUBY_RELEASE_DAY)

/*
 * mruby最初创建的年份。
 */
#define MRUBY_BIRTH_YEAR 2010

/*
 * MRuby的作者。
 */
#define MRUBY_AUTHOR "mruby developers"

/*
 * mruby的版本和发布日期。
 */
#define MRUBY_DESCRIPTION      \
  "mruby " MRUBY_VERSION       \
  " (" MRUBY_RELEASE_DATE ") " \

/*
 * 鲁比先生的版权信息。
 */
#define MRUBY_COPYRIGHT                \
  "mruby - Copyright (c) "             \
  MRB_STRINGIZE(MRUBY_BIRTH_YEAR)"-"   \
  MRB_STRINGIZE(MRUBY_RELEASE_YEAR)" " \
  MRUBY_AUTHOR                         \

MRB_END_DECL

#endif  /* MRUBY_VERSION_H */

