/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
/*
 * 参数化测试框架
 *
 * SPI等外设有几个参数，如：freq、mode、DMA等。此框架有助于用同一程序测试不同的参数集。
 *
 * 每个“参数集”都是具有不同参数（频率、模式等）的集。参数组是由多个参数集组成的组。每个单元测试在组中的集合之间执行测试。
 *
 * 测试将按以下顺序执行：1.“pre_test”：初始化上下文2.从参数组中取出一个集合3.“def_param”：如果未设置，则填写参数集的默认值4。
 *
 * 用法示例：
 *
 * 1.定义自己的参数集类型：typedef struct｛const char pset_name[PET_name_LEN]；//测试工作到低于频率，//将频率设置为更高，并删除驱动程序中的检查，以了解系统的运行速度。const int freq_list；//测试频率的列表，以0 int freq-limit结尾；//freq更大（不相等）则这将被忽略spi_dup_t dup；int模式；布尔长度对齐；int测试大小；
 *
 *          int master_limit；//主设备禁用虚拟位并丢弃该频率布尔master_iomux上的读数；int master_dma_chan；
 *
 *          bool slave_ iomux；int slave_dma_chan；int slave_tv_ns；布尔从属未对齐地址；}spitest_param_set_t；
 *
 * 2.定义参数集：spitest_param_set_t mode_pgroup[]=｛//非DMA测试｛.pset_name=“mode 0，no DMA”，.freq_list=test_freq_mode，.master_limit=freq_limit_mode，.dup=FULL_DUPLEX，.master_iomux=true，.slave_iomux＝true，.srave_tv_ns=tv_WITH_ESP_slave，.mode=0，｝，｛.pset_name=“模式1，无DMA”，.freq_list=test_freq_mode，.master_limit=freq_limit_mode，.dup=FULL_DUPLEX，.master_iomux=true，.slave_iomux＝true，.srave_tv_ns=tv_WITH_ESP_slave，.mode=1，｝，//其他配置…｝；
 *
 * 3.定义测试函数，并将其包装在“param_test_func_t”中：static const param_test_func_t master_test_func={.pro_test=test_master_init，.post_test=test_master _deinit，.lop=test_master_loop，.def_param=spitest_def_param，}；
 *
 * 4.在参数组后面用PARAM_group_Declare声明组：PARAM_GGROUP_DECALE（MODE，MODE_pgroup）
 *
 * 5.通过test_SINGLE_BOARD（单板测试）或test_MASTER_SAVE（多板测试）声明测试函数test_MASTR_SLAVE（MODE，MODE_pgroup，“[spi][timeout=120]”，&MASTER_test_func，&SLAVE_test_func）
 *
 *      或TEST_SINGLE_BOARD（定时，定时分组，“[spi][timeout=120]”，&local_TEST_func）
 *
 * 注意：如果标记和测试函数相同，建议定义自己的宏来包装4和5。E、 例如：#define TEST_SPI_MASTER_SLAVE（名称，pgroup）（反斜杠）PARAM_GROUP_DECLARE（名称，pgroup）
 *
 * 然后通过以下方式方便地声明测试：TEST_SPI_MASTER_SLAVE（TIMING，TIMING_pgroup）TEST_SPI-MASTER_SRAVE（MODE，MODE_pgroup）
 *
 */

#define PGROUP_NAME_LEN    20               ///<参数组的名称长度
#define PGROUP_NAME(name) PGROUP_##name     ///<param组名称
#define PTEST_MASTER_NAME(name) PTEST_MASTER_##name ///<主设备的测试功能名称
#define PTEST_SLAVE_NAME(name) PTEST_SLAVE_##name   ///<从设备的测试功能名称

///测试集结构保存名称、参数集数组指针、项目大小和参数集编号。
typedef struct {
    char name[PGROUP_NAME_LEN];   ///<要打印的参数组的名称
    void *param_group;          ///<参数组数组的开始
    int pset_size;              ///<每个参数集的大小
    int pset_num;               ///<参数集总数
} param_group_t;

///框架的测试函数
typedef struct {
    void (*pre_test)(void** contxt);    ///<测试开始前调用初始化函数。在此处输入您的上下文
    void (*post_test)(void* context);   ///<所有测试完成后调用Deinit函数。
    void (*def_param)(void* inout_pset);    ///<函数在执行前填充每个pset结构，如果不使用，则保留NULL。
    void (*loop)(const void* pset, void* context); ///<函数执行每个参数集
} ptest_func_t;

/**
 * 测试框架以执行init、loop和deinit。
 *
 * @param param_group 参数组持有者轮流测试。
 * @param test_func 要执行的函数集。
 */
void test_serializer(const param_group_t *param_group, const ptest_func_t* test_func);

#define PARAM_GROUP_DECLARE_TYPE(group_name, pset_type, pgroup) \
    static const param_group_t PGROUP_NAME(pgroup) = { \
        .name = #group_name, \
        .param_group = (void*)&pgroup, \
        .pset_size = sizeof(pset_type), \
        .pset_num = sizeof(pgroup)/sizeof(pset_type), \
    };

/**
 * 声明参数组
 *
 * @param group_name 要在测试开始时打印的参数组名称
 * @param param_group 参数组结构，应已在上面定义，并且已定义大小和类型。
 */
#define PARAM_GROUP_DECLARE(group_name, param_group) \
    PARAM_GROUP_DECLARE_TYPE(group_name, typeof(param_group[0]), param_group)

/**
 * 在一块板上测试参数组。
 *
 * @param name 要在菜单中打印的测试名称。
 * @param param_group 要测试的参数组。
 * @param tag 环境标签等，例如[spi][timeout=120]
 * @param test_func ``ptest_func_t``将被执行。
 */
#define TEST_SINGLE_BOARD(name, param_group, tag, test_func) \
    TEST_CASE("single board test: "#name, tag) { test_serializer(&PGROUP_NAME(param_group), test_func); }

/**
 * 主从框架测试参数组
 *
 * @param name 要在菜单中打印的测试名称。
 * @param param_group 要测试的参数组。
 * @param tag 环境标签等，例如[spi][timeout=120]
 * @param master_func ``ptest_func_t``由主机执行。
 * @param slave_func ``ptest_func_t``将由slave执行。
 */
#define TEST_MASTER_SLAVE(name, param_group, tag, master_func, slave_func) \
    static void PTEST_MASTER_NAME(name) (void) { test_serializer(&PGROUP_NAME(param_group), master_func); } \
    static void PTEST_SLAVE_NAME(name) (void) { test_serializer(&PGROUP_NAME(param_group), slave_func); } \
    TEST_CASE_MULTIPLE_DEVICES("master slave test: "#name, tag, PTEST_MASTER_NAME(name), PTEST_SLAVE_NAME(name))

