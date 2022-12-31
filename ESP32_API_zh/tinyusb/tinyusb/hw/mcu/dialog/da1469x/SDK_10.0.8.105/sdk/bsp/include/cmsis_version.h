/**************************************************************************//**
 * @file     cmsis_version.h
 * @brief    CMSIS Core(M) Version definitions
 * @version  V5.0.2
 * @date     19. April 2017
 ******************************************************************************/
/*
 * 版权所有（c）2009-2017 ARM Limited。保留所有权利。
 *
 * SPDX许可证标识符：Apache-2.0
 *
 * 根据Apache许可证2.0版（许可证）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按原样分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#if   defined ( __ICCARM__ )
  #pragma system_include         /* 将文件视为MISRA检查的系统包含文件*/
#elif defined (__clang__)
  #pragma clang system_header   /* 将文件视为系统包含文件*/
#endif

#ifndef __CMSIS_VERSION_H
#define __CMSIS_VERSION_H

/*  CMSIS版本定义*/
#define __CM_CMSIS_VERSION_MAIN  ( 5U)                                      /*!< [31:16]CMSIS Core（M）主版本*/
#define __CM_CMSIS_VERSION_SUB   ( 1U)                                      /*!< [15:0]CMSIS Core（M）子版本*/
#define __CM_CMSIS_VERSION       ((__CM_CMSIS_VERSION_MAIN << 16U) | \
                                   __CM_CMSIS_VERSION_SUB           )       /*!< CMSIS Core（M）版本号*/
#endif

