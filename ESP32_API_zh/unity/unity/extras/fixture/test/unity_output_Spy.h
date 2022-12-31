/* 版权所有（c）2010 James Grenning和对Unity项目的贡献===================================Unity项目-c测试框架版权所有（c）2007 Mike Karlesky，Mark VanderVoord，Greg Williams[根据MIT许可证发布。请参阅License.txt了解详细信息]
 * ========================================== */

#ifndef D_unity_output_Spy_H
#define D_unity_output_Spy_H

void UnityOutputCharSpy_Create(int s);
void UnityOutputCharSpy_Destroy(void);
void UnityOutputCharSpy_OutputChar(int c);
const char * UnityOutputCharSpy_Get(void);
void UnityOutputCharSpy_Enable(int enable);

#endif

