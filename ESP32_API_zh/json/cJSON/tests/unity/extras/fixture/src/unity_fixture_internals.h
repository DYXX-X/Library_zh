/* 版权所有（c）2010 James Grenning和对Unity项目的贡献===================================Unity项目-c测试框架版权所有（c）2007 Mike Karlesky，Mark VanderVoord，Greg Williams[根据MIT许可证发布。请参阅License.txt了解详细信息]
 * ========================================== */

#ifndef UNITY_FIXTURE_INTERNALS_H_
#define UNITY_FIXTURE_INTERNALS_H_

#ifdef __cplusplus
extern "C"
{
#endif

struct UNITY_FIXTURE_T
{
    int Verbose;
    unsigned int RepeatCount;
    const char* NameFilter;
    const char* GroupFilter;
};
extern struct UNITY_FIXTURE_T UnityFixture;

typedef void unityfunction(void);
void UnityTestRunner(unityfunction* setup,
                     unityfunction* body,
                     unityfunction* teardown,
                     const char* printableName,
                     const char* group,
                     const char* name,
                     const char* file, unsigned int line);

void UnityIgnoreTest(const char* printableName, const char* group, const char* name);
void UnityMalloc_StartTest(void);
void UnityMalloc_EndTest(void);
int UnityGetCommandLineOptions(int argc, const char* argv[]);
void UnityConcludeFixtureTest(void);

void UnityPointer_Set(void** ptr, void* newValue, UNITY_LINE_TYPE line);
void UnityPointer_UndoAllSets(void);
void UnityPointer_Init(void);
#ifndef UNITY_MAX_POINTERS
#define UNITY_MAX_POINTERS 5
#endif

#ifdef __cplusplus
}
#endif

#endif /* UNITY_FIXTURE_INTERNALS_H_ */

