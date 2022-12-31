/****************************************************************************
 * 工具/cxd56/clefia.h
 *
 * 版权所有（C）20072008 Sony Corporation
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用NuttX名称或其贡献者的名称来支持或推广源自本软件的产品。
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef _TOOLS_CXD56_CLEFIA_H_
#define _TOOLS_CXD56_CLEFIA_H_

/****************************************************************************
 * 公共类型
 ****************************************************************************/

struct cipher
  {
    int mode;
    int dir;
    uint8_t rk[8 * 26 + 16];
    uint8_t vector[16];
    int round;
    uint8_t k1[16];
    uint8_t k2[16];
  };

/****************************************************************************
 * 公共功能原型
 ****************************************************************************/

struct cipher *cipher_init(uint8_t * key, uint8_t * iv);
void cipher_deinit(struct cipher *c);
int cipher_calc_cmac(struct cipher *c, void *data, int size, void *cmac);
void bytexor(unsigned char *dst, const unsigned char *a,
             const unsigned char *b, int bytelen);
int clefiakeyset(unsigned char *rk, const unsigned char *skey);
void clefiaencrypt(unsigned char *ct, const unsigned char *pt,
                   const unsigned char *rk, const int r);

#endif
