#ifndef _TCP_TRANSPORT_FIXTURES_H_
#define _TCP_TRANSPORT_FIXTURES_H_

/**
 * @brief 传递套接字选项的结构和类型
 */
enum expected_sock_option_types {
    SOCK_OPT_TYPE_BOOL,
    SOCK_OPT_TYPE_INT,
};
struct expected_sock_option {
    int level;
    int optname;
    int optval;
    enum expected_sock_option_types opttype;
};

/**
 * @brief 超时连接测试的帮助程序测试函数
 *
 * 本例模拟了与其他套接字连接异步运行tcp连接的连接超时，从而消耗了整个套接字侦听器积压工作。重要提示：两个任务必须在同一个内核上运行，侦听器的优先级更高，以确保1）首先localhost_listener（）创建并连接所有套接字，直到最后一个套接字阻塞2）在tcp_connect_task（）尝试连接并因此连接超时而失败
 */
void tcp_transport_test_connection_timeout(esp_transport_handle_t transport_under_test);


/**
 * @brief 帮助程序测试功能，用于检查由传输单独配置的套接字选项
 *
 * 这将设置连接测试以启动两个任务，但与tcp_transport_test_connection_timeout不同，这里我们只允许连接发生或至少在tcp层上打开，这样我们就可以获得内部套接字描述符。当连接正在进行或连接时，我们可以检查tcp_transportAPI配置的套接字选项。
 */
void tcp_transport_test_socket_options(esp_transport_handle_t transport_under_test, bool async,
                                       const struct expected_sock_option *expected_opts, size_t sock_options_len);

#endif //_TCP_TRANSPORT_FIXTURES_H_

