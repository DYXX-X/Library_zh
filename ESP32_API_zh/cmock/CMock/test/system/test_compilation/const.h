/* ==========================================
    CMock项目-C版自动模拟生成版权所有（C）2007 Mike Karlesky，Mark VanderVoord，Greg Williams[根据MIT许可证发布。请参阅License.txt了解详细信息]
========================================== */

#if defined(__GNUC__) && !defined(__ICC)
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

struct _DUMMY_T { unsigned int a; float b; };

void const_variants1( const char* a, int const, unsigned short const * c );

void const_variants2(
	struct _DUMMY_T const * const param1,
	const unsigned long int const * const param2,
	const struct _DUMMY_T const * param3 );

const int * const_retval1(void);        /* 常量int指针的nicity版本*/
int const * const_retval2(void);        /* 指向常量int的指针的正式版本*/
//int * const const_retval3(void);        /* int常量指针的正式版本*/
//int const * const const_retval4(void);  /* 指向常量int的常量指针的正式版本*/

const int* const_retval5(void);         /* 指向常量int的指针的粘性左nicity版本*/
int const* const_retval6(void);         /* 指向常量int的指针的粘性左正式版本*/
//int* const const_retval7(void);         /* 用于指向int的常量指针的粘性左正式版本*/
//int const* const const_retval8(void);   /* 指向常量int的常量指针的粘性左正式版本*/

const int *const_retval9(void);         /* 指向常量int的指针的粘性右nicity版本*/
int const *const_retvalA(void);         /* 指向常量int的指针的粘性右正式版本*/
//int *const const_retvalB(void);         /* 指向int的常量指针的粘性右正式版本*/
//int const *const const_retvalC(void);   /* 指向常量int的常量指针的粘性右正式版本*/

