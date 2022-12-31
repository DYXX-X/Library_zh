/*
 * 版权所有（c）2015 Kazuho Oku，DeNA Co.，Ltd。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef NEVERBLEED_H
#define NEVERBLEED_H

#include <pthread.h>
#include <sys/un.h>
#include <openssl/engine.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NEVERBLEED_ERRBUF_SIZE (256)
#define NEVERBLEED_AUTH_TOKEN_SIZE 32

typedef struct st_neverbleed_t {
    ENGINE *engine;
    pid_t daemon_pid;
    struct sockaddr_un sun_;
    pthread_key_t thread_key;
    unsigned char auth_token[NEVERBLEED_AUTH_TOKEN_SIZE];
} neverbleed_t;

/**
 * 初始化特权分离引擎（如果成功，则返回0）
 */
int neverbleed_init(neverbleed_t *nb, char *errbuf);
/**
 * 加载私钥文件（如果成功，则返回1）
 */
int neverbleed_load_private_key_file(neverbleed_t *nb, SSL_CTX *ctx, const char *fn, char *errbuf);
/**
 * setuidgid（如果change_socket_ownship为非零，还将更改文件权限，以便“用户”可以连接到守护程序）
 */
int neverbleed_setuidgid(neverbleed_t *nb, const char *user, int change_socket_ownership);

#ifdef __cplusplus
}
#endif

#endif

