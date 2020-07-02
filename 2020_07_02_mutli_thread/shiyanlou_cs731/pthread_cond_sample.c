#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

pthread_t threads[2];
char writer_char[2] = {'A', 'B'};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct file_res
{
    pthread_t *writer; /*��ǰ�ļ����Ա��ĸ��߳�д��*/
    int fd;            /*�ļ�������*/
} file_res =
    {
        .writer = &threads[0], /*file��ʼ�����Ա��߳�1д��'A'*/
};

/*�߳�1���߳�2����ں���*/
void *writer_routine(void *arg)
{
    int index = (intptr_t)arg;
    int i = 0;
    int next_index = 0;
    printf("thread %d is running, and will write '%c' to file\n", index, writer_char[index]);

    while (1)
    {
        if (0 != pthread_mutex_lock(&mutex))
            exit(-1);
        for (;;)
        {

            /*�����ǰ�߳̿�дfile, ִ��д����*/
            if (&threads[index] == file_res.writer)
            {
                write(file_res.fd, &writer_char[index],
                      sizeof(writer_char[index]));

                /*������һ����д�߳�*/
                next_index = (index + 1) % 2;
                file_res.writer = &threads[next_index];

                /*ִ��д������break forѭ��ͨ����������֪ͨ�����߳�д*/
                break;
            }

            /*��ǰ�̲߳���д���ȴ������̻߳���*/
            pthread_cond_wait(&cond, &mutex);
        }

        if (0 != pthread_mutex_unlock(&mutex))
            exit(-1);

        /*������һ���߳�*/
        pthread_cond_signal(&cond);
    }
}

int main(int argc, char *argv[])
{

    /*�������ļ�file*/
    char file_name[] = "file";
    if ((file_res.fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0666)) < 0)
    {
        printf("open %s error.\n", file_name);
        exit(-1);
    }

    /*�����߳�1���߳�2*/
    int i;
    for (i = 0; i < (sizeof(threads) / sizeof(pthread_t)); i++)
    {
        if (pthread_create(&threads[i], NULL, writer_routine, (void *)(intptr_t)i))
        {
            printf("create writer thread error\n");
            exit(-1);
        }
    }

    /*���߳��˳�*/
    pthread_exit(NULL);
}
