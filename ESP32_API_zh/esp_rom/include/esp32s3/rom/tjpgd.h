/*----------------------------------------------------------------------------/
/TJpgDec-微型JPEG解压缩器包括文件（C）ChaN，2012
/----------------------------------------------------------------------------*/
#ifndef _TJPGDEC
#define _TJPGDEC
/*---------------------------------------------------------------------------*/
/* 系统配置*/

#define JD_SZBUF        512 /* 流输入缓冲区的大小*/
#define JD_FORMAT       0   /* 输出像素格式0:RGB888（3字节/像素），1:RGB565（1字/像素）*/
#define JD_USE_SCALE    1   /* 使用除垢功能进行输出*/
#define JD_TBLCLIP      1   /* 使用表饱和（可能会快一点，但会增加1K字节的代码大小）*/

/*---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/* 这些类型必须是16位、32位或更大的整数*/
typedef int             INT;
typedef unsigned int    UINT;

/* 这些类型必须是8位整数*/
typedef char            CHAR;
typedef unsigned char   UCHAR;
typedef unsigned char   BYTE;

/* 这些类型必须是16位整数*/
typedef short           SHORT;
typedef unsigned short  USHORT;
typedef unsigned short  WORD;
typedef unsigned short  WCHAR;

/* 这些类型必须是32位整数*/
typedef long            LONG;
typedef unsigned long   ULONG;
typedef unsigned long   DWORD;


/* 错误代码*/
typedef enum {
    JDR_OK = 0, /* 0:成功*/
    JDR_INTR,   /* 1： 输出功能中断*/
    JDR_INP,    /* 2： 设备错误或输入流错误终止*/
    JDR_MEM1,   /* 3： 映像的内存池不足*/
    JDR_MEM2,   /* 4： 流输入缓冲区不足*/
    JDR_PAR,    /* 5： 参数错误*/
    JDR_FMT1,   /* 6： 数据格式错误（可能是损坏的数据）*/
    JDR_FMT2,   /* 7： 格式正确但不受支持*/
    JDR_FMT3    /* 8： 不支持JPEG标准*/
} JRESULT;



/* 矩形结构*/
typedef struct {
    WORD left, right, top, bottom;
} JRECT;



/* 解压缩器对象结构*/
typedef struct JDEC JDEC;
struct JDEC {
    UINT dctr;              /* 输入缓冲区中可用的字节数*/
    BYTE *dptr;             /* 当前数据读取指针*/
    BYTE *inbuf;            /* 比特流输入缓冲器*/
    BYTE dmsk;              /* 当前读取字节中的当前位*/
    BYTE scale;             /* 输出缩放比率*/
    BYTE msx, msy;          /* 以块为单位的MCU大小（宽度、高度）*/
    BYTE qtid[3];           /* 每个组件的量化表ID*/
    SHORT dcv[3];           /* 每个组件的上一个直流元件*/
    WORD nrst;              /* 重新启动搜索*/
    UINT width, height;     /* 输入图像的大小（像素）*/
    BYTE *huffbits[2][2];   /* 霍夫曼比特分布表[id][dcac]*/
    WORD *huffcode[2][2];   /* 霍夫曼码字表[id][dcac]*/
    BYTE *huffdata[2][2];   /* 霍夫曼解码数据表[id][dcac]*/
    LONG *qttbl[4];         /* 解列表[id]*/
    void *workbuf;          /* IDCT和RGB输出的工作缓冲区*/
    BYTE *mcubuf;           /* MCU的工作缓冲区*/
    void *pool;             /* 指向可用内存池的指针*/
    UINT sz_pool;           /* 内存池大小（可用字节）*/
    UINT (*infunc)(JDEC *, BYTE *, UINT); /* 指向jpeg流输入函数的指针*/
    void *device;           /* 指向会话的I/O设备标识符的指针*/
};

/* TJpgDec API函数*/
JRESULT jd_prepare (JDEC *, UINT(*)(JDEC *, BYTE *, UINT), void *, UINT, void *);
JRESULT jd_decomp (JDEC *, UINT(*)(JDEC *, void *, JRECT *), BYTE);


#ifdef __cplusplus
}
#endif

#endif /* _TJPGDEC */

