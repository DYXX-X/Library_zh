/*
 * FreeRTOS内核V10.4.3版权所有（C）2020 Amazon。com，Inc.或其附属公司。保留所有权利。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org https://github.com/FreeRTOS
 *
 */

/*
 * 这是调度程序使用的列表实现。虽然它是为调度程序的需求量身打造的，但它也可供应用程序代码使用。
 *
 * list_ts只能存储指向list_item_ts的指针。每个ListItem_t包含一个数值（xItemValue）。大多数情况下，列表按项目值降序排序。
 *
 * 创建的列表已包含一个列表项。此项的值是可以存储的最大值，因此它始终位于列表的末尾，充当标记。列表成员pxHead始终指向此标记，即使它位于列表的尾部。这是因为尾部包含指向列表真正开头的换行指针。
 *
 * 除了它的值之外，每个列表项还包含指向列表中下一项的指针（pxNext）、指向它所在列表的指针（p xContainer）和指向包含它的对象的指针。为了提高列表操作的效率，包括了后面的两个指针。在包含列表项的对象和列表项本身之间存在有效的双向链接。
 *
 * \page ListIntroduction List Implementation\ingroup FreeRTOSIntro（页面列表简介列表实施）
 */

#ifndef INC_FREERTOS_H
    #error "FreeRTOS.h must be included before list.h"
#endif

#ifndef LIST_H
#define LIST_H

/*
 * 列表结构成员是在中断内修改的，因此应该声明为volatile。然而，它们只能以功能原子的方式进行修改（在调度程序挂起的关键部分内），或者通过引用传递到函数中，或者通过易失性变量进行索引。因此，在迄今为止测试的所有用例中，可以省略volatile限定符，以便在不影响功能行为的情况下提供适度的性能改进。IAR、ARM和GCC编译器在各自的编译器选项设置为最大优化时生成的汇编指令已被检查并视为符合预期。也就是说，随着编译器技术的进步，特别是如果使用了积极的跨模块优化（一个尚未进行过任何扩展的用例），那么需要使用易失性限定符进行正确的优化是可行的。预计编译器会删除必要的代码，因为如果列表结构成员上没有易失性限定符，并且进行了积极的跨模块优化，编译器认为不必要的代码将导致调度器完全和明显的失败。如果曾经经历过这种情况，那么可以通过在FreeRTOSConfig中将configLIST_volatile定义为volatile，将volatile限定符插入列表结构中的相关位置。h（根据此注释块底部的示例）。如果未定义configLIST_VOLATILE，则下面的预处理器指令将简单地彻底#define configLIST_VOL ATILE。
 *
 * 要使用易失性列表结构成员，请将以下行添加到FreeRTOSConfig。h（不带引号）：“#define configLIST_VOLATILE VOLATILE”
 */
#ifndef configLIST_VOLATILE
    #define configLIST_VOLATILE
#endif /* 配置支持_ ROSS_模块_优化*/

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/* 可用于在列表结构中放置已知值的宏，然后检查已知值在应用程序执行期间是否损坏。这些可能会捕获正在内存中覆盖的列表数据结构。它们不会捕捉到由错误配置或使用FreeRTOS导致的数据错误。*/
#if ( configUSE_LIST_DATA_INTEGRITY_CHECK_BYTES == 0 )
    /* 将宏定义为不执行任何操作。*/
    #define listFIRST_LIST_ITEM_INTEGRITY_CHECK_VALUE
    #define listSECOND_LIST_ITEM_INTEGRITY_CHECK_VALUE
    #define listFIRST_LIST_INTEGRITY_CHECK_VALUE
    #define listSECOND_LIST_INTEGRITY_CHECK_VALUE
    #define listSET_FIRST_LIST_ITEM_INTEGRITY_CHECK_VALUE( pxItem )
    #define listSET_SECOND_LIST_ITEM_INTEGRITY_CHECK_VALUE( pxItem )
    #define listSET_LIST_INTEGRITY_CHECK_1_VALUE( pxList )
    #define listSET_LIST_INTEGRITY_CHECK_2_VALUE( pxList )
    #define listTEST_LIST_ITEM_INTEGRITY( pxItem )
    #define listTEST_LIST_INTEGRITY( pxList )
#else /* 如果（configUSE_LIST_DATA_INTEGRITY_CHECK_BYTES==0）*/
    /* 定义将新成员添加到列表结构中的宏。*/
    #define listFIRST_LIST_ITEM_INTEGRITY_CHECK_VALUE     TickType_t xListItemIntegrityValue1;
    #define listSECOND_LIST_ITEM_INTEGRITY_CHECK_VALUE    TickType_t xListItemIntegrityValue2;
    #define listFIRST_LIST_INTEGRITY_CHECK_VALUE          TickType_t xListIntegrityValue1;
    #define listSECOND_LIST_INTEGRITY_CHECK_VALUE         TickType_t xListIntegrityValue2;

/* 定义将新结构成员设置为已知值的宏。*/
    #define listSET_FIRST_LIST_ITEM_INTEGRITY_CHECK_VALUE( pxItem )     ( pxItem )->xListItemIntegrityValue1 = pdINTEGRITY_CHECK_VALUE
    #define listSET_SECOND_LIST_ITEM_INTEGRITY_CHECK_VALUE( pxItem )    ( pxItem )->xListItemIntegrityValue2 = pdINTEGRITY_CHECK_VALUE
    #define listSET_LIST_INTEGRITY_CHECK_1_VALUE( pxList )              ( pxList )->xListIntegrityValue1 = pdINTEGRITY_CHECK_VALUE
    #define listSET_LIST_INTEGRITY_CHECK_2_VALUE( pxList )              ( pxList )->xListIntegrityValue2 = pdINTEGRITY_CHECK_VALUE

/* 定义宏，如果其中一个结构成员不包含其预期值，则该宏将进行断言。*/
    #define listTEST_LIST_ITEM_INTEGRITY( pxItem )                      configASSERT( ( ( pxItem )->xListItemIntegrityValue1 == pdINTEGRITY_CHECK_VALUE ) && ( ( pxItem )->xListItemIntegrityValue2 == pdINTEGRITY_CHECK_VALUE ) )
    #define listTEST_LIST_INTEGRITY( pxList )                           configASSERT( ( ( pxList )->xListIntegrityValue1 == pdINTEGRITY_CHECK_VALUE ) && ( ( pxList )->xListIntegrityValue2 == pdINTEGRITY_CHECK_VALUE ) )
#endif /* 配置_LIST_DATA_INTEGRITY_CHECK_BYTES*/


/*
 * 列表可以包含的唯一对象类型的定义。
 */
struct xLIST;
struct xLIST_ITEM
{
    listFIRST_LIST_ITEM_INTEGRITY_CHECK_VALUE               /*<如果configUSE_LIST_DATA_INTEGRITY_CHECK_BYTES设置为1，则设置为已知值。*/
    configLIST_VOLATILE TickType_t xItemValue;              /*<列出的值。在大多数情况下，这用于按降序对列表进行排序。*/
    struct xLIST_ITEM * configLIST_VOLATILE pxNext;         /*<指向列表中下一个ListItem_t的指针。*/
    struct xLIST_ITEM * configLIST_VOLATILE pxPrevious;     /*<指向列表中上一个ListItem_t的指针。*/
    void * pvOwner;                                         /*<指向包含列表项的对象（通常是TCB）的指针。因此，包含列表项的对象和列表项本身之间存在双向链接。*/
    struct xLIST * configLIST_VOLATILE pxContainer;         /*<指向放置此列表项的列表的指针（如果有）。*/
    listSECOND_LIST_ITEM_INTEGRITY_CHECK_VALUE              /*<如果configUSE_LIST_DATA_INTEGRITY_CHECK_BYTES设置为1，则设置为已知值。*/
};
typedef struct xLIST_ITEM ListItem_t;                       /* 出于某种原因，lint希望将其作为两个独立的定义。*/

struct xMINI_LIST_ITEM
{
    listFIRST_LIST_ITEM_INTEGRITY_CHECK_VALUE     /*<如果configUSE_LIST_DATA_INTEGRITY_CHECK_BYTES设置为1，则设置为已知值。*/
    configLIST_VOLATILE TickType_t xItemValue;
    struct xLIST_ITEM * configLIST_VOLATILE pxNext;
    struct xLIST_ITEM * configLIST_VOLATILE pxPrevious;
};
typedef struct xMINI_LIST_ITEM MiniListItem_t;

/*
 * 调度程序使用的队列类型的定义。
 */
typedef struct xLIST
{
    listFIRST_LIST_INTEGRITY_CHECK_VALUE          /*<如果configUSE_LIST_DATA_INTEGRITY_CHECK_BYTES设置为1，则设置为已知值。*/
    volatile UBaseType_t uxNumberOfItems;
    ListItem_t * configLIST_VOLATILE pxIndex;     /*<用于浏览列表。指向调用listGET_OWNER_OF_NEXT_ENTRY（）返回的最后一项。*/
    MiniListItem_t xListEnd;                      /*<列出包含最大可能项目值的项目，这意味着它始终位于列表末尾，因此用作标记。*/
    listSECOND_LIST_INTEGRITY_CHECK_VALUE         /*<如果configUSE_LIST_DATA_INTEGRITY_CHECK_BYTES设置为1，则设置为已知值。*/
} List_t;

/*
 * 访问宏以设置列表项的所有者。列表项的所有者是包含列表项的对象（通常是TCB）。
 *
 * \页面列表SET_LIST_ITEM_OWNER\组链接列表
 */
#define listSET_LIST_ITEM_OWNER( pxListItem, pxOwner )    ( ( pxListItem )->pvOwner = ( void * ) ( pxOwner ) )

/*
 * 访问宏以获取列表项的所有者。列表项的所有者是包含列表项的对象（通常是TCB）。
 *
 * \页面列表GET_LIST_ITEM_OWNER\组链接列表
 */
#define listGET_LIST_ITEM_OWNER( pxListItem )             ( ( pxListItem )->pvOwner )

/*
 * 访问宏以设置列表项的值。在大多数情况下，该值用于按降序对列表进行排序。
 *
 * \页面列表SET_LIST_ITEM_VALUE列表SET_LEST_ITEM_ALUE\组链接列表
 */
#define listSET_LIST_ITEM_VALUE( pxListItem, xValue )     ( ( pxListItem )->xItemValue = ( xValue ) )

/*
 * 访问宏以检索列表项的值。该值可以表示任何内容，例如任务的优先级或应取消阻止任务的时间。
 *
 * \页面列表GET_LIST_ITEM_VALUE列表GET_IST_ITEM_ALUE\组链接列表
 */
#define listGET_LIST_ITEM_VALUE( pxListItem )             ( ( pxListItem )->xItemValue )

/*
 * 访问宏以检索给定列表开头的列表项的值。
 *
 * \页面列表GET_LIST_ITEM_VALUE列表GET_IST_ITEM_ALUE\组链接列表
 */
#define listGET_ITEM_VALUE_OF_HEAD_ENTRY( pxList )        ( ( ( pxList )->xListEnd ).pxNext->xItemValue )

/*
 * 返回列表顶部的列表项。
 *
 * \页面列表GET_HEAD_ENTRY列表GET_HAD_ENTRY \组链接列表
 */
#define listGET_HEAD_ENTRY( pxList )                      ( ( ( pxList )->xListEnd ).pxNext )

/*
 * 返回下一个列表项。
 *
 * \页面列表GET_NEXT列表GET_EXT\ing组链接列表
 */
#define listGET_NEXT( pxListItem )                        ( ( pxListItem )->pxNext )

/*
 * 返回标记列表末尾的列表项
 *
 * \页面列表GET_END_MARKER列表GET_END_MARKER\组链接列表
 */
#define listGET_END_MARKER( pxList )                      ( ( ListItem_t const * ) ( &( ( pxList )->xListEnd ) ) )

/*
 * 访问宏以确定列表是否包含任何项。只有当列表为空时，宏才会具有值true。
 *
 * \页面列表LIST_IS_EMPTY列表List_IS_EMPTY\组链接列表
 */
#define listLIST_IS_EMPTY( pxList )                       ( ( ( pxList )->uxNumberOfItems == ( UBaseType_t ) 0 ) ? pdTRUE : pdFALSE )

/*
 * 访问宏以返回列表中的项目数。
 */
#define listCURRENT_LIST_LENGTH( pxList )                 ( ( pxList )->uxNumberOfItems )

/*
 * 访问函数以获取列表中下一个条目的所有者。
 *
 * 列表成员pxIndex用于遍历列表。调用listGET_OWNER_OF_NEXT_ENTRY将pxIndex递增到列表中的下一项，并返回该项的pxOwner参数。因此，通过多次调用此函数，可以在列表中的每个项目之间移动。
 *
 * 列表项的pxOwner参数是指向拥有列表项的对象的指针。在调度器中，这通常是一个任务控制块。pxOwner参数有效地创建了列表项与其所有者之间的双向链接。
 *
 * @param pxTCB pxTCB被设置为下一列表项的所有者的地址。
 * @param pxList 要从中返回下一个项目所有者的列表。
 *
 * \页面列表GET_OWNER_OF_NEXT_ENTRY列表GET_WNER_OF_NEXT_ENTRY \组链接列表
 */
#define listGET_OWNER_OF_NEXT_ENTRY( pxTCB, pxList )                                           \
    {                                                                                          \
        List_t * const pxConstList = ( pxList );                                               \
        /* 将索引增加到下一项并返回该项，确保*/               \
        /* 我们不会返回列表末尾使用的标记。*/                         \
        ( pxConstList )->pxIndex = ( pxConstList )->pxIndex->pxNext;                           \
        if( ( void * ) ( pxConstList )->pxIndex == ( void * ) &( ( pxConstList )->xListEnd ) ) \
        {                                                                                      \
            ( pxConstList )->pxIndex = ( pxConstList )->pxIndex->pxNext;                       \
        }                                                                                      \
        ( pxTCB ) = ( pxConstList )->pxIndex->pvOwner;                                         \
    }


/*
 * 获取列表中第一个条目的所有者的访问函数。列表通常按项目值升序排序。
 *
 * 此函数返回列表中第一项的pxOwner成员。列表项的pxOwner参数是指向拥有列表项的对象的指针。在调度器中，这通常是一个任务控制块。pxOwner参数有效地创建了列表项与其所有者之间的双向链接。
 *
 * @param pxList 要从中返回标题项所有者的列表。
 *
 * \页面列表GET_OWNER_OF_HEAD_ENTRY列表GET_WNER_OF_HEAD_ENTRY \组链接列表
 */
#define listGET_OWNER_OF_HEAD_ENTRY( pxList )            ( ( &( ( pxList )->xListEnd ) )->pxNext->pvOwner )

/*
 * 检查列表项是否在列表中。列表项维护一个指向其所在列表的“容器”指针。这个宏所做的就是检查容器和列表是否匹配。
 *
 * @param pxList 我们想知道列表项是否在其中。
 * @param pxListItem 我们想知道的列表项是否在列表中。
 * @return 如果列表项在列表中，则为pdTRUE，否则为pdFALSE。
 */
#define listIS_CONTAINED_WITHIN( pxList, pxListItem )    ( ( ( pxListItem )->pxContainer == ( pxList ) ) ? ( pdTRUE ) : ( pdFALSE ) )

/*
 * 返回包含列表项的列表（从中引用）。
 *
 * @param pxListItem 正在查询的列表项。
 * @return 指向引用pxListItem的List_t对象的指针
 */
#define listLIST_ITEM_CONTAINER( pxListItem )            ( ( pxListItem )->pxContainer )

/*
 * 这提供了一种了解列表是否已初始化的粗略方法，如pxList->xListEnd。xItemValue通过vListInitialize（）函数设置为portMAX_DELAY。
 */
#define listLIST_IS_INITIALISED( pxList )                ( ( pxList )->xListEnd.xItemValue == portMAX_DELAY )

/*
 * 必须在使用列表之前调用！这将初始化列表结构的所有成员，并将xListEnd项作为列表后面的标记插入列表中。
 *
 * @param pxList 指向正在初始化的列表的指针。
 *
 * \页面vListInitialize vListInitialize\ingroup LinkedList
 */
void vListInitialise( List_t * const pxList ) PRIVILEGED_FUNCTION;

/*
 * 必须在使用列表项之前调用。这会将列表容器设置为空，以便该项不会认为它已经包含在列表中。
 *
 * @param pxItem 指向正在初始化的列表项的指针。
 *
 * \页面vListInitializeItem vListInitializedItem\inggroup LinkedList
 */
void vListInitialiseItem( ListItem_t * const pxItem ) PRIVILEGED_FUNCTION;

/*
 * 将列表项插入列表。项目将按其项目值（项目值降序）确定的位置插入列表。
 *
 * @param pxList 要插入项目的列表。
 *
 * @param pxNewListItem 要放置在列表中的项目。
 *
 * \页面vListInsert vListInsert\ingroup LinkedList
 */
void vListInsert( List_t * const pxList,
                  ListItem_t * const pxNewListItem ) PRIVILEGED_FUNCTION;

/*
 * 将列表项插入列表。该项将插入到一个位置，这样它将是多次调用listGET_OWNER_OF_NEXT_ENTRY返回的列表中的最后一项。
 *
 * 列表成员pxIndex用于遍历列表。调用listGET_OWNER_OF_NEXT_ENTRY将pxIndex递增到列表中的下一项。使用vListInsertEnd在列表中放置项目可以有效地将项目放置在pxIndex指向的列表位置。这意味着在pxIndex参数再次指向要插入的项之前，列表中的每个其他项都将由listGET_OWNER_OF_NEXT_ENTRY返回。
 *
 * @param pxList 要插入项目的列表。
 *
 * @param pxNewListItem 要插入到列表中的列表项。
 *
 * \页面vListInsertEnd vListInsertEnd\ingroup LinkedList
 */
void vListInsertEnd( List_t * const pxList,
                     ListItem_t * const pxNewListItem ) PRIVILEGED_FUNCTION;

/*
 * 从列表中删除项目。列表项具有指向其所在列表的指针，因此只需将列表项传递到函数中。
 *
 * @param uxListRemove 要删除的项目。该项将从其pxContainer参数所指向的列表中删除自身。
 *
 * @return 删除列表项后保留在列表中的项数。
 *
 * \页面uxListRemove uxListDelete\ingroup LinkedList
 */
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove ) PRIVILEGED_FUNCTION;

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* ifndef列表_H*/

