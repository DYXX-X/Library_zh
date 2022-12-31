/*
   wqueue。h基于标准C++库列表模板类的工作线程队列。
   ------------------------------------------版权所有（c）2013 Vic Hargrave根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：http://www.apache.org/licenses/LICENSE-2.0除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
*/

// https://vichargrave.github.io/articles/2013-01/multithreaded-work-queue-in-cpp
// https://github.com/vichargrave/wqueue/blob/master/wqueue.h


#ifndef __wqueue_h__
#define __wqueue_h__

#include <pthread.h>
#include <list>

using namespace std;

template <typename T> class wqueue
{
    list<T>              m_queue;
    pthread_mutex_t      m_mutex;
    pthread_mutexattr_t  m_mutex_attr;
    pthread_cond_t       m_condv;

public:
    wqueue()
    {
        pthread_mutexattr_init(&m_mutex_attr);
        pthread_mutexattr_settype(&m_mutex_attr, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&m_mutex, &m_mutex_attr);
        pthread_cond_init(&m_condv, NULL);
    }

    ~wqueue() {
        pthread_mutex_destroy(&m_mutex);
        pthread_cond_destroy(&m_condv);
    }

    void put(T item) {
        pthread_mutex_lock(&m_mutex);
        m_queue.push_back(item);
        pthread_cond_signal(&m_condv);
        pthread_mutex_unlock(&m_mutex);
    }

    T get(uint32_t tmo) {
        pthread_mutex_lock(&m_mutex);
        if (tmo) {
            while (m_queue.size() == 0) {
                pthread_cond_wait(&m_condv, &m_mutex);
            }
        }

        T item = NULL;

        if (m_queue.size() != 0) {
            item = m_queue.front();
            m_queue.pop_front();
        }

        pthread_mutex_unlock(&m_mutex);
        return item;
    }

    void remove(T item) {
        pthread_mutex_lock(&m_mutex);
        m_queue.remove(item);
        pthread_mutex_unlock(&m_mutex);
    }

    int size() {
        pthread_mutex_lock(&m_mutex);
        int size = m_queue.size();
        pthread_mutex_unlock(&m_mutex);
        return size;
    }
};

#endif

