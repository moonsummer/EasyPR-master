/*************************************************************************
> File Name: server_socket.h
> Author:
> Mail:
> Created Time: 2016年09月27日 星期二 06时36分36秒
************************************************************************/

#ifndef _SERVER_SOCKET_H
#define _SERVER_SOCKET_H

#include <stdint.h>
#include <sys/types.h>

struct socket_config {
	char local_ip[16];
	char multicast_addr[16];
	unsigned short multicast_port;
	unsigned short server_port;

};
int server_socket_init(struct socket_config config);
void broadcast_data(const char *buf, size_t size);
int receive_worker_start();
#endif
