/*
 * SPDX文件版权文本：2019-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void ets_apb_backup_init_lock_func(void(* _apb_backup_lock)(void), void(* _apb_backup_unlock)(void));

#ifdef __cplusplus
}
#endif

