/* ==========================================
    CMock项目-C版自动模拟生成版权所有（C）2007 Mike Karlesky，Mark VanderVoord，Greg Williams[根据MIT许可证发布。请参阅License.txt了解详细信息]
========================================== */

typedef unsigned short U16;
typedef signed int int32_t;

/* CMock应处理注释中的UTF-8字符。世界是一个多样化的地方！*/
/* 我的µC岩石！开源，而不是©！我的语言没有Ümlauts！ǺƜǝƧǾɱɛ! */ /**! 非法：åäö*/

typedef struct _POINT_T
{
  int x;
  int y;
} POINT_T;

// typedef边case；
// 不是ANSI C，但它已经完成，如果不处理，将打破cmock
typedef void VOID_TYPE_CRAZINESS;

/* 有趣的解析和模拟生成案例*/

void var_args1(int a, ...);
void var_args2(int a, int b, ...);

VOID_TYPE_CRAZINESS void_type_craziness1(int, float, double, char, short, long, long int, long long, void*);
int void_type_craziness2( VOID_TYPE_CRAZINESS );

   void  crazy_whitespace  (   int    lint, double shot  ,  short  stack )  ;

char
 crazy_multiline
(
  int a,
  unsigned int b);

U16  *ptr_return1(int a);
U16*  ptr_return2(int a);
U16 * ptr_return3(int a);

unsigned int** ptr_ptr_return1(unsigned int** a);
unsigned int* *ptr_ptr_return2(unsigned int* *a);
unsigned int **ptr_ptr_return3(unsigned int **a);
unsigned int ** ptr_ptr_return4(unsigned int ** a);

extern unsigned long int incredible_descriptors(register const unsigned short a);

int32_t example_c99_type(int32_t param1);

void I2CIntRegister(uint32_t ui32Base, void (*pfnHandler)(void));

/* 这些是函数指针，而不是使用函数指针的函数声明，因此不应被嘲笑*/
int (* func_pointer)(void);
extern int (*another_func_pointer)(unsigned int argument);
struct struct_to_be_ignored {
  union {
    int i32;
    void *p;
  } variant;
  void (*a_function_pointer_in_a_struct)(void *);
};

typedef struct
{
  uint32_t a;
  struct
  {
    uint32_t bb;
    float bc;
    float bd;
  } b;
  int (*another_function_pointer_in_a_struct) (void);
} another_thing_that_should_get_ignored;

inline int stuff(int num)
{
    int reg = 0x12;
    if (num > 0)
    {
      reg |= (0x0Eu);
    }
    else
    {
      reg |= (0x07u);
    }
    return reg;
}

