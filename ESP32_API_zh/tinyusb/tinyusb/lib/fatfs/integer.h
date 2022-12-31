/*-------------------------------------------*/
/* FatFs模块的整数类型定义*/
/*-------------------------------------------*/

#ifndef _INTEGER
#define _INTEGER

#ifdef _WIN32	/* FatFs开发平台*/

#include <windows.h>
#include <tchar.h>

#else			/* 嵌入式平台*/

/* 这些类型必须是16位、32位或更大的整数*/
typedef int				INT;
typedef unsigned int	UINT;

/* 这些类型必须是8位整数*/
typedef unsigned char	UCHAR;
typedef unsigned char	BYTE;

/* 这些类型必须是16位整数*/
typedef short			SHORT;
typedef unsigned short	USHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;

/* 这些类型必须是32位整数*/
typedef long			LONG;
typedef unsigned long	ULONG;
typedef unsigned long	DWORD;

#endif

#endif

