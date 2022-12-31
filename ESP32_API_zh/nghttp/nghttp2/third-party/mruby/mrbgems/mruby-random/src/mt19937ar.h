/*
** 1993年7月。h-MT随机函数
**
** 版权所有（C）1997-2016，Makoto Matsumoto和Takuji Nishimura，保留所有权利。
**
** 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
**
** 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
** [MIT许可证：http://www.opensource.org/licenses/mit-license.php ]
**
** 欢迎任何反馈。http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
** email: m-mat @ math.sci.hiroshima-u.ac.jp（删除空格）
**
** 此版本由mruby开发人员修改。如果您发现任何问题，请首先联系我们https://github.com/mruby/mruby/issues
*/

#define N 624

typedef struct {
  unsigned long mt[N];
  int mti;
  union {
    unsigned long int_;
    double double_;
  } gen;

  mrb_int seed;
  mrb_bool has_seed : 1;
} mt_state;

void mrb_random_init_genrand(mt_state *, unsigned long);
unsigned long mrb_random_genrand_int32(mt_state *);
double mrb_random_genrand_real1(mt_state *t);

/* 使用种子初始化mt[N]*/
void init_genrand(unsigned long s);

/* 通过具有数组长度的数组初始化*/
/* init_key是用于初始化密钥的数组*/
/* key_length是其长度*/
/* C++的轻微变化，2004/2/26*/
void init_by_array(unsigned long init_key[], int key_length);

/* 在[0,0xffffffff]-interval上生成随机数*/
unsigned long genrand_int32(void);

/* 在[0,0x7fffffff]间隔上生成随机数*/
long genrand_int31(void);

/* 这些真实版本由Isaku Wada提供，2002/01/09添加*/
/* 在[0,1]-实区间上生成随机数*/
double genrand_real1(void);

/* 在[0,1）-实区间上生成随机数*/
double genrand_real2(void);

/* 在（0,1）-实区间上生成随机数*/
double genrand_real3(void);

/* 在[0,1）上生成53位分辨率的随机数*/
double genrand_res53(void);

