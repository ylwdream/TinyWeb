/*
 * =====================================================================================
 *
 *       Filename:  open_clientfd.c
 *
 *    Description: 包装客户端的创建socket和connect操作
 *
 *        Version:  1.0
 *        Created:  03/17/2015 07:04:24 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  WYL (), ylwzzu@gmail.com
 *
 * =====================================================================================
 */
#include "tiny.h"

int open_clientfd(char *hostname, int port)
{
    int clientfd;
    struct hostent *hp;
    struct sockaddr_in serveraddr;

    // AF_INT 表示的因特网协议，SOCK_STREAM 表示这个套接字是因特网的一个端点
    // 返回的clientfd是部分打开的，还不能直接对套接字读写
    if((clientfd = socket(AF_INT, SOCK_STREAM, 0)) < 0)
        return -1; //创建套接字失败
    if((hp = gethostbyname(hostname)) == NULL)
        return -2; //DNS错误

    bzero((char*)&serveraddr, sizeof(serveraddr));

    serveraddr.sin_family = AF_INT;
    //成员选择的优先级高于类型转换
    //设置服务器地址，已经是大端格式
    bcopy((char*)hp->h_addr_list[0], (char*)serveraddr.sin_addr.s_addr, hp->h_length);
    serveraddr.sin_port = htons(port);

    if(connect(clientfd, (SA *)&serveraddr, sizeof(SA)) < 0)
        return -3; //链接失败
    return clientfd;
}

