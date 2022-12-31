/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _TIME_SCENE_SERVER_H_
#define _TIME_SCENE_SERVER_H_

#include "server_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 1.网格基于国际原子时间（TAI）定义时间。时间的基本表示是2000-01-01年00:00:00 TAI之后的秒数（即1999-12-31 T23:59:28 UTC）。2.UTC：协调世界时。有关详细信息，请参阅https://time.is/zh/UTC3.关于TAI和UTC之间传输所使用的算法，请参考网格模型规范第5.1.1节
 */

#define UNKNOWN_TAI_SECONDS         0x0000000000
#define UNKNOWN_TAI_ZONE_CHANGE     0x0000000000
#define UNKNOWN_TAI_DELTA_CHANGE    0x0000000000
#define TAI_UTC_DELTA_MAX_VALUE     0x7FFF
#define TAI_SECONDS_LEN             0x05
#define TAI_OF_ZONE_CHANGE_LEN      0x05
#define TAI_OF_DELTA_CHANGE_LEN     0x05

#define INVALID_SCENE_NUMBER        0x0000
#define SCENE_NUMBER_LEN            0x02

#define SCHEDULE_YEAR_ANY_YEAR      0x64

#define SCHEDULE_DAY_ANY_DAY        0x00

#define SCHEDULE_HOUR_ANY_HOUR      0x18
#define SCHEDULE_HOUR_ONCE_A_DAY    0x19

#define SCHEDULE_SEC_ANY_OF_HOUR    0x3C
#define SCHEDULE_SEC_EVERY_15_MIN   0x3D
#define SCHEDULE_SEC_EVERY_20_MIN   0x3E
#define SCHEDULE_SEC_ONCE_AN_HOUR   0x3F

#define SCHEDULE_SEC_ANY_OF_MIN     0x3C
#define SCHEDULE_SEC_EVERY_15_SEC   0x3D
#define SCHEDULE_SEC_EVERY_20_SEC   0x3E
#define SCHEDULE_SEC_ONCE_AN_MIN    0x3F

#define SCHEDULE_ACT_TURN_OFF       0x00
#define SCHEDULE_ACT_TURN_ON        0x01
#define SCHEDULE_ACT_SCENE_RECALL   0x02
#define SCHEDULE_ACT_NO_ACTION      0x0F

#define SCHEDULE_SCENE_NO_SCENE     0x0000

#define SCHEDULE_ENTRY_MAX_INDEX    0x0F

#define TIME_NONE                   0x00
#define TIME_AUTHORITY              0x01
#define TIME_RELAY                  0x02
#define TIME_CLINET                 0x03

#define SCENE_SUCCESS               0x00
#define SCENE_REG_FULL              0x01
#define SCENE_NOT_FOUND             0x02

/**
 * 时间状态表示当前TAI时间、当前TAI-UTC Delta和本地时区偏移，以及对后者的下一次更改（例如，由于从冬季切换到夏季时间或宣布的闰秒）。它由10个字段组成，总大小为183位。
 */
struct bt_mesh_time_state {
    struct {
        uint8_t  tai_seconds[5];
        uint8_t  subsecond;
        uint8_t  uncertainty;
        uint8_t  time_zone_offset_curr;
        uint8_t  time_zone_offset_new;
        uint8_t  tai_zone_change[5];
        uint16_t time_authority : 1,
                 tai_utc_delta_curr : 15;
        uint16_t tai_utc_delta_new : 15;
        uint8_t  tai_delta_change[5];
    } time;
    uint8_t time_role;
};

struct bt_mesh_time_srv {
    struct bt_mesh_model *model;
    struct bt_mesh_server_rsp_ctrl rsp_ctrl;
    struct bt_mesh_time_state *state;
};

struct bt_mesh_time_setup_srv {
    struct bt_mesh_model *model;
    struct bt_mesh_server_rsp_ctrl rsp_ctrl;
    struct bt_mesh_time_state *state;
};

struct scene_register {
    uint16_t scene_number;
    uint8_t  scene_type;   /* 指示场景值的类型*/
    /**
     * 场景值可以使用并集来表示，稍后，并集包含可以存储在场景中的所有模型状态的结构。
     */
    struct net_buf_simple *scene_value;
};

/**
 * 场景用作存储状态（例如，功率级或光级/颜色）的存储器库。元素的状态值可以存储为场景，并且可以稍后从场景存储器中调用。
 *
 * 场景由“场景编号”（scene Number）表示，该编号是一个16位非零网格宽值。（网格网络中最多可以有65535个场景。）场景的含义以及与其关联的状态存储容器由模型确定。
 *
 * 场景状态更改可能会启动许多并行模型转换。在这种情况下，每个单独的模型都在内部处理转换。
 *
 * 场景变换定义为一组由场景调用操作启动的单独模型变换。当单个模型过渡组中的至少一个过渡正在进行时，场景过渡正在进行。
 */
struct bt_mesh_scenes_state {
    const uint16_t scene_count;
    struct scene_register *scenes;

    /**
     * “当前场景”状态是一个16位值，该值包含当前活动场景的“场景编号”，或者在没有活动场景时为0x0000。
     *
     * 当场景存储操作或场景调用操作成功完成时，当前场景状态值应为该操作期间使用的场景编号。
     *
     * 当“场景删除”操作导致“当前场景编号”从“场景寄存器”状态中删除时，“当前场景状态”应设置为0x0000。
     *
     * 如果标记为“与场景一起存储”的任何元素状态未因场景调用操作而发生更改，则当前场景状态的值应设置为0x0000。
     *
     * 当正在进行场景转换时，当前场景状态的值应设置为0x0000。
     */
    uint16_t current_scene;

    /**
     * “目标场景”状态是一个16位值，在进行场景转换时包含目标“场景编号”。
     *
     * 当场景转换正在进行，并且由于“场景删除”操作，目标场景编号从“场景注册”状态中删除时，目标场景状态应设置为0x0000。
     *
     * 当场景转换正在进行，并且由于场景存储操作，新的场景号存储在场景寄存器中时，目标场景状态应设置为新的场景编号。
     *
     * 当场景转换未进行时，目标场景状态的值应设置为0x0000。
     */
    uint16_t target_scene;

    /* 指示上次操作的状态代码*/
    uint8_t status_code;

    /* 指示是否正在进行场景转换*/
    bool in_progress;
};

struct bt_mesh_scene_srv {
    struct bt_mesh_model *model;
    struct bt_mesh_server_rsp_ctrl rsp_ctrl;
    struct bt_mesh_scenes_state *state;
    struct bt_mesh_last_msg_info last;
    struct bt_mesh_state_transition transition;
};

struct bt_mesh_scene_setup_srv {
    struct bt_mesh_model *model;
    struct bt_mesh_server_rsp_ctrl rsp_ctrl;
    struct bt_mesh_scenes_state *state;
};

struct schedule_register {
    bool     in_use;
    uint64_t year : 7,
             month : 12,
             day : 5,
             hour : 5,
             minute : 6,
             second : 6,
             day_of_week : 7,
             action : 4,
             trans_time : 8;
    uint16_t scene_number;
};

struct bt_mesh_scheduler_state {
    const uint8_t schedule_count;
    struct schedule_register *schedules; /* 最多16个预定条目*/

    /**
     * 调度器的推荐实现应计算下一个计划事件的TAI秒值，并将其放入按时间排序的计划事件队列中。
     *
     * 每秒钟，队列中的第一个事件都会与“时间”状态的值进行比较。如果第一个事件小于或等于“时间”状态，则执行该事件，然后将其从队列中删除。执行后，应检查重复标志，并计算下一次发生的计划事件并将其放入队列。
     *
     * 一秒超时值，并将队列中的第一个事件与时间状态进行比较。如果满足，则执行第一个事件。此外，需要检查重复标志，如果设置了重复标志，则需要将事件放入队列末尾。
     *
     * sys_slist_t事件队列；
     *
     * 对于每个event_queue项，它可以使用以下结构：struct schedule_event｛sys_snode_t node；uint8_t event_index；｝；
     *
     * 此外，我们还需要一个“structk_delayed_worktrack_timer”，它可以用来跟踪计划计时器并处理适当的计划事件。
     */
};

struct bt_mesh_scheduler_srv {
    struct bt_mesh_model *model;
    struct bt_mesh_server_rsp_ctrl rsp_ctrl;
    struct bt_mesh_scheduler_state *state;
};

struct bt_mesh_scheduler_setup_srv {
    struct bt_mesh_model *model;
    struct bt_mesh_server_rsp_ctrl rsp_ctrl;
    struct bt_mesh_scheduler_state *state;
};

typedef union {
    struct {
        uint8_t  tai_seconds[5];
        uint8_t  subsecond;
        uint8_t  uncertainty;
        uint16_t time_authority : 1;
        uint16_t tai_utc_delta_curr : 15;
        uint8_t  time_zone_offset_curr;
    } time_set;
    struct {
        uint8_t  tai_seconds[5];
        uint8_t  subsecond;
        uint8_t  uncertainty;
        uint16_t time_authority : 1;
        uint16_t tai_utc_delta_curr : 15;
        uint8_t  time_zone_offset_curr;
    } time_status;
    struct {
        uint8_t time_zone_offset_new;
        uint8_t tai_zone_change[5];
    } time_zone_set;
    struct {
        uint16_t tai_utc_delta_new : 15;
        uint8_t  tai_delta_change[5];
    } tai_utc_delta_set;
    struct {
        uint8_t role;
    } time_role_set;
    struct {
        uint16_t scene_number;
    } scene_store;
    struct {
        uint16_t scene_number;
    } scene_recall;
    struct {
        uint16_t scene_number;
    } scene_delete;
    struct {
        uint64_t index : 4,
                 year : 7,
                 month : 12,
                 day : 5,
                 hour : 5,
                 minute : 6,
                 second : 6,
                 day_of_week : 7,
                 action : 4,
                 trans_time : 8;
        uint16_t scene_number;
    } scheduler_act_set;
} bt_mesh_time_scene_server_state_change_t;

typedef union {
    struct {
        uint8_t index;
    } scheduler_act_get;
} bt_mesh_time_scene_server_recv_get_msg_t;

typedef union {
    struct {
        uint8_t  tai_seconds[5];
        uint8_t  subsecond;
        uint8_t  uncertainty;
        uint16_t time_authority : 1;
        uint16_t tai_utc_delta : 15;
        uint8_t  time_zone_offset;
    } time_set;
    struct {
        uint8_t time_zone_offset_new;
        uint8_t tai_zone_change[5];
    } time_zone_set;
    struct {
        uint16_t tai_utc_delta_new : 15;
        uint16_t padding : 1;
        uint8_t  tai_delta_change[5];
    } tai_utc_delta_set;
    struct {
        uint8_t time_role;
    } time_role_set;
    struct {
        uint16_t scene_number;
    } scene_store;
    struct {
        bool     op_en;
        uint16_t scene_number;
        uint8_t  tid;
        uint8_t  trans_time;
        uint8_t  delay;
    } scene_recall;
    struct {
        uint16_t scene_number;
    } scene_delete;
    struct {
        uint64_t index : 4,
                 year : 7,
                 month : 12,
                 day : 5,
                 hour : 5,
                 minute : 6,
                 second : 6,
                 day_of_week : 7,
                 action : 4,
                 trans_time : 8;
        uint16_t scene_number;
    } scheduler_act_set;
} bt_mesh_time_scene_server_recv_set_msg_t;

typedef union {
    struct {
        uint8_t  tai_seconds[5];
        uint8_t  subsecond;
        uint8_t  uncertainty;
        uint16_t time_authority : 1;
        uint16_t tai_utc_delta : 15;
        uint8_t  time_zone_offset;
    } time_status;
} bt_mesh_time_scene_server_recv_status_msg_t;

void bt_mesh_time_scene_server_lock(void);
void bt_mesh_time_scene_server_unlock(void);

void scene_publish(struct bt_mesh_model *model, struct bt_mesh_msg_ctx *ctx, uint16_t opcode);

#ifdef __cplusplus
}
#endif

#endif /* _TIME_SCENE_SERVER_H_ */

