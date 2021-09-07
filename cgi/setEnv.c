#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include "global.h"
#include "cgic.h"

int cgiMain(int argc, const char *argv[])
{
    int res, msgid, i = 0;
    key_t key = ftok("/home", 1);
    char value[32] = "";
    char *keys[6] = {"temMAX", "temMIN", "humMAX", "humMIN", "illMAX", "illMIN"};
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
    msgbuf.msgtype = 5L;

    for (i = 0; i < sizeof(keys)/sizeof(keys[0]); i++)
    {
        cgiFormString(keys[i], value, sizeof(value));
        msgbuf.text[i] = (unsigned int)(atoi(value));
    }
    msgsnd(msgid, &msgbuf, sizeof(msgbuf.text), 0);

    cgiHeaderContentType("text/html");

    return 0;
}