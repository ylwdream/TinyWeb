/*
 * =====================================================================================
 *
 *       Filename:  open_listenfd.c
 *
 *    Description:  服务器封装了sock,band,listen 函数，建立监听套接字
 *
 *        Version:  1.0
 *        Created:  03/18/2015 09:03:21 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  WYL (502), ylwzzu@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "tiny.h"

int open_listenfd(int port)
{
	int listenfd, optval = 1;
	struct sockaddr_in serveraddr;

	if((listenfd = sock(AF_INT, SOCK_STREAM, 0)) < 0)
		return -1;  //创建socket失败


	/* 能够使两个套接字和一个地址绑定，SO_RESUMEADDR */
	if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,
				  (const void *)&optval, sizeof(int)) < 0)
		return -1;
	
	bzero((char*)&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INT;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); /* 表示服务器任意ip地址都可以 */
	serveraddr.sin_port = htons(port);
	
	if(bind(listenfd, (SA *)&serveraddr, sizeof(serveraddr)) < 0)
		return -2; // bind函数错误

	if(listen(listenfd, LISTENQ) <0)
	{
		errno = -3;
		fprintf(stderr, "error: %d, listen error\n", errno);
	}
	
	return listenfd;
}
