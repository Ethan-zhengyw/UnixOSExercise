#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGKEY 2

struct msgform {
    long mtype;
    char mtext[7];
};

main()
{
    struct msgform msg;
    int msgid, pid;
    int bsent, breceived;

    msgid = msgget(MSGKEY, 0777);

    pid = getpid();

    printf("before msgrcv, msg.mtype is [%d], msg.mtext is [%s].\n",
		    msg.mtype, msg.mtext);
    msgrcv(msgid, &msg, 6, 0, 0);
    printf("before msgrcv, msg.mtype is [%d], msg.mtext is [%s].\n",
		    msg.mtype, msg.mtext);
}
