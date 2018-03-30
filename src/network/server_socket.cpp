#include "easypr/network/server_socket.hpp"

/*************************************************************************
> File Name: server_socket.c
> Author:
> Mail:
> Created Time: 2016��09��27�� ���ڶ� 06ʱ35��47��
************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include <pthread.h>

static int sock;
struct sockaddr_in multicast_addr;
struct sockaddr_in server_addr;
static pthread_t receive_worker;

/**
* @brief ��ʼ��Socket
*
* @param config: �����������
*
* @return �ɹ����� 0, ʧ�ܷ���-1
*/
int server_socket_init(struct socket_config config)
{
	int ret;

	/*
	* ����Socket
	*/
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock<0) {
		printf("create socket failed: %s\n", strerror(errno));
		return -1;
	}

	/*
	* ��ʼ���鲥��ַ�ṹ����Ϊ���ݷ���Ŀ���ַ
	*/
	printf("local_ip = %s\n", config.local_ip);
	memset(&multicast_addr, 0, sizeof(multicast_addr));
	multicast_addr.sin_addr.s_addr = inet_addr(config.multicast_addr);
	multicast_addr.sin_family = AF_INET;
	multicast_addr.sin_port = htons(config.multicast_port);

	/*
	* ��ʼ����������ַ�����ص�ַ
	*/
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_addr.s_addr = inet_addr(config.local_ip);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(config.server_port);

	int on = 1;
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));

	/*
	* ��socket��ַ
	*/
	ret = bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	if (ret < 0) {
		printf("bind socket failed: %s\n", strerror(errno));
		return -1;

	}
	return 0;
}
/*
* @brief ��������
*
* @param buf: Ҫ���͵�����
* @param size: Ҫ�������ݵĳ���
*/
void broadcast_data(const char *buf, size_t size)
{
	/*
	* �������ݵ�ָ���鲥��ַ
	*/
	sendto(sock, buf, size, 0, (struct sockaddr *)&multicast_addr, sizeof(multicast_addr));

}
void *receive_worker_thread(void*)
{
	uint8_t buf[16] = { 0 };
	int nbyte = 0;
	uint8_t crc;
	int i = 0;
	socklen_t addrlen = sizeof(struct sockaddr);
	while (1) {
		/*
		* �������Ը������ն˵�����
		*/
		nbyte = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&server_addr, &addrlen);
		if (nbyte < 0) {
			continue;
		}
/*		if (buf[0] == 0x31)
			setServoAngle(125);
		else
			setServoAngle(70);
*/
	}
	return NULL;

}
int receive_worker_start()
{
	if (pthread_create(&receive_worker, 0, receive_worker_thread, NULL) != 0) {
		printf("could not start worker thread\n");

	}
	pthread_detach(receive_worker);
	return 0;
}

