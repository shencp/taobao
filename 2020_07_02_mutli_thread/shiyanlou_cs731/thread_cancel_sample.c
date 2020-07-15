/*
 * file name:thread_cancel_sample.c
 */

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define handle_error_en(en, msg)                                               \
    do {                                                                       \
        errno = en;                                                            \
        perror(msg);                                                           \
        exit(EXIT_FAILURE);                                                    \
    } while (0)

static void *thread_routine(void *arg) {
    int j;

    printf("New thread started\n"); /*�����п�����һ���߳�ȡ���� */
    for (j = 1;; j++) {
        printf("Loop %d\n", j); /*����Ҳ������һ���߳�ȡ����*/
        sleep(1);               /*������һ���߳�ȡ����*/
    }
    /* �߳�ִ�������޷�����˴� */
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t thr;
    int s;
    void *res;
    /*�������߳�*/
    s = pthread_create(&thr, NULL, thread_routine, NULL);
    if (s != 0)
        handle_error_en(s, "pthread_create");

    /*�����̷߳�һ���*/
    sleep(3);

    /*ȡ���½��߳�*/
    s = pthread_cancel(thr);
    if (s != 0)
        handle_error_en(s, "pthread_cancel");
    /*�ȴ����߳��˳�*/
    s = pthread_join(thr, &res);
    if (s != 0)
        handle_error_en(s, "pthread_join");
    /*�ж����߳���ֹ�Ƿ�����Ӧȡ���������ֹ��*/
    if (res == PTHREAD_CANCELED)
        printf("Thread was canceled\n");
    else
        printf("Thread was not canceled (should not happen!)\n");

    return 0;
}
