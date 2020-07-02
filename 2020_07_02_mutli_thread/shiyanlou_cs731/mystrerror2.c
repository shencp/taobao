#define _GNU_SOURCE
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static pthread_once_t once = PTHREAD_ONCE_INIT;
static pthread_key_t strerrorKey;

#define handle_error_en(en, msg) \
    do                           \
    {                            \
        errno = en;              \
        perror(msg);             \
        exit(EXIT_FAILURE);      \
    } while (0)
#define handle_error(msg)   \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

#define MAX_ERROR_LEN 256

/*�߳��������ݵ���������*/
static void destructor(void *buf) { free(buf); }

static void createKey(void)
{
    int s;
    /*��phtread_once�����ﴴ���������ݵ�key��
  �ĸ��߳��ȵ��þ��ĸ��̴߳���key*/
    s = pthread_key_create(&strerrorKey, destructor);
    if (s != 0)
        handle_error_en(s, "pthread_key_create");
}

char *mystrerror(int err)
{
    int s;
    char *buf;

    /*һ���Գ�ʼ������*/
    s = pthread_once(&once, createKey);
    if (s != 0)
        handle_error_en(s, "pthread_once");

    /*��ȡ�߳���������*/
    buf = pthread_getspecific(strerrorKey);
    if (buf == NULL)
    { /*��һ�λ�ȡΪNULL, �߳���Ҫ�����ڴ�*/
        buf = malloc(MAX_ERROR_LEN);
        if (buf == NULL)
            handle_error("malloc");
        /*�������������ڴ�*/
        s = pthread_setspecific(strerrorKey, buf);
        if (s != 0)
            handle_error_en(s, "pthread_setspecific");
    }

    if (err < 0 || err >= _sys_nerr || _sys_errlist[err] == NULL)
    {
        snprintf(buf, MAX_ERROR_LEN, "Unknown error %d", err);
    }
    else
    {
        strncpy(buf, _sys_errlist[err], MAX_ERROR_LEN - 1);
        buf[MAX_ERROR_LEN - 1] = '\0'; /* Ensure null termination */
    }

    return buf;
}
