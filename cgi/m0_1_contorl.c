#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include "global.h"
#include "cgic.h"

#define LED 1
#define BEEP 2
#define SEG 3
#define FAN 4

int cgiMain(int argc, const char *argv[])
{
    int res, msgid;
    key_t key = ftok("/home", 1);
    char type[32] = "";
    char value[32] = "";
    unsigned int code;
    struct msg msgbuf;

    if (key < 0)
    {
        perror("ftok");
        return -1;
    }

    // 初始化消息队列
    msgid = msgget(key, IPC_CREAT | 0664);
    if (msgid < 0)
    {
        perror("msgget");
        return -1;
    }
    memset(&msgbuf, 0, sizeof(msgbuf));

    // 获取网页请求
    cgiFormString("type", type, sizeof(type));

    switch (atoi(type))
    {
    case LED:
        msgbuf.msgtype = 1L;
        cgiFormString("led", value, sizeof(value));
        break;
    case BEEP:
        msgbuf.msgtype = 2L;
        cgiFormString("beep", value, sizeof(value));
        break;
    case SEG:
        msgbuf.msgtype = 3L;
        cgiFormString("seg", value, sizeof(value));
        if(atoi(value))
        {
            cgiFormString("segvalue", value, sizeof(value));
        }
        break;
    case FAN:
        msgbuf.msgtype = 4L;
        cgiFormString("fan", value, sizeof(value));
        break;
    default:
        break;
    }
    code = atoi(value);
    msgbuf.text[0] = code;
    msgsnd(msgid, &msgbuf, sizeof(msgbuf.text), 0);

    cgiHeaderContentType("text/html");
    
    return 0;
}