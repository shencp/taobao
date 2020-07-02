/* filename: main.c
 *  desp: Calling mystrerror() from two different threads
 */

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define handle_error_en(en, msg) \
    do                           \
    {                            \
        errno = en;              \
        perror(msg);             \
        exit(EXIT_FAILURE);      \
    } while (0)

extern char *mystrerror(int err);

static void *threadFunc(void *arg)
{
    char *str;
    printf("Other thread about to call mystrerror()\n");
    /*���̻߳�ȡEPERM��������ַ���Ϣ*/
    str = mystrerror(EINVAL);
    printf("Other thread: str (%p) = %s\n", str, str);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t t;
    int s;
    char *str;
    /*���̻߳�ȡEINVAL��������ַ���Ϣ*/
    str = mystrerror(EPERM);
    printf("Main thread: str (%p) = %s\n", str, str);
    printf("Main thread has called mystrerror()\n");

    s = pthread_create(&t, NULL, threadFunc, NULL);
    if (s != 0)
        handle_error_en(s, "pthread_create");
    s = pthread_join(t, NULL);
    if (s != 0)
        handle_error_en(s, "pthread_join");
    printf("Main thread: str (%p) = %s\n", str, str);

    exit(EXIT_SUCCESS);
}
