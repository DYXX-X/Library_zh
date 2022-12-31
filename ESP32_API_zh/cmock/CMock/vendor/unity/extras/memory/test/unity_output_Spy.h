/* ==========================================
 *  Unity Project-C测试框架版权所有（C）2007 Mike Karlesky，Mark VanderVoord，Greg Williams[根据MIT许可证发布。请参阅License.txt了解详细信息]
 * ========================================== */

#ifndef UNITY_OUTPUT_SPY_H
#define UNITY_OUTPUT_SPY_H

void UnityOutputCharSpy_Create(int s);
void UnityOutputCharSpy_Destroy(void);
void UnityOutputCharSpy_OutputChar(int c);
const char * UnityOutputCharSpy_Get(void);
void UnityOutputCharSpy_Enable(int enable);

#endif

