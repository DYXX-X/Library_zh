#ifndef ESP_MDNS_NETWORKING_H_
#define ESP_MDNS_NETWORKING_H_

/*
 * MDNS服务器网络--专用包括
 *
 */
#include "mdns.h"
#include "mdns_private.h"


/**
 * @brief  队列RX数据包操作
 */
esp_err_t _mdns_send_rx_action(mdns_rx_packet_t * packet);

/**
 * @brief  启动PCB
 */
esp_err_t _mdns_pcb_init(mdns_if_t tcpip_if, mdns_ip_protocol_t ip_protocol);

/**
 * @brief  停止PCB
 */
esp_err_t _mdns_pcb_deinit(mdns_if_t tcpip_if, mdns_ip_protocol_t ip_protocol);

/**
 * @brief  通过UDP发送数据包
 *
 * @param  server       服务器
 * @param  data         包含数据包数据的字节数组
 * @param  len          分组数据长度
 *
 * @return 发送数据包的长度或错误时为0
 */
size_t _mdns_udp_pcb_write(mdns_if_t tcpip_if, mdns_ip_protocol_t ip_protocol, const esp_ip_addr_t *ip, uint16_t port, uint8_t * data, size_t len);

/**
 * @brief  获取指向mDNS数据包的数据指针
 */
void* _mdns_get_packet_data(mdns_rx_packet_t *packet);

/**
 * @brief  获取数据长度c
 */
size_t _mdns_get_packet_len(mdns_rx_packet_t *packet);

/**
 * @brief  释放mDNS数据包
 */
void _mdns_packet_free(mdns_rx_packet_t *packet);

#endif /* ESP_MDNS_NETWORKING_H_ */

