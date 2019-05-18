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
    int msgid, pid, *pint;
    int bsent, breceived;

    msgid = msgget(MSGKEY, 0777);

    pid = getpid();
    pint = (int*) msg.mtext;
    *pint = pid;
    msg.mtype = 0;
    msg.mtext[0] = 'H';
    msg.mtext[1] = 'e';
    msg.mtext[2] = 'l';
    msg.mtext[3] = 'l';
    msg.mtext[4] = 'o';
    msg.mtext[5] = ' ';

    printf("before msgsnd, msg.mtype is [%d], msg.mtext is [%s].\n",
		    msg.mtype, msg.mtext);
    bsent = msgsnd(msgid, &msg, sizeof(int), 0);
    printf("after msgsnd, bsent is [%d]\n", bsent);

    printf("before msgrcv, msg.mtype is [%d], msg.mtext is [%s].\n",
		    msg.mtype, msg.mtext);
    /* msgrcv(msgid, &msg, 256, pid, 0);
    printf("after msgrcv, breceived is [%d].\n", breceived);

    printf("client: receive from pid %d\n", *pint); */
}
