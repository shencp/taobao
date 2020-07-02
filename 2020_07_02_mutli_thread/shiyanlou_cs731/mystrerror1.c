/* filename: mystrerror1.c
 *  desp: An implementation of mystrerror() that is not thread-safe
 */

#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define MAX_ERROR_LEN 256

/*ȫ�־�̬�ڴ��*/
static char buf[MAX_ERROR_LEN];

/*mystrerror�����ɴ�����errno��ʾ���ַ���,*/
char *mystrerror(int err)
{
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
