/*
* file name: thread_sync_sample2.c
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>

#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)
/*globΪ���̹߳�����Դ*/
static int glob = 0;
/* ��̬��ʼ��һ��ȫ�ֵĻ����� */
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;


/*���̷߳����޸Ĺ�����Դglob*/
static void *thread_routine(void *arg)
{
  int loc, j;
  for (j = 0; j < 10000000; j++) {
    /*�����ٽ���ǰ���ȳ��л�����*/
    pthread_mutex_lock(&mtx);
    loc = glob;
    loc++;
    glob = loc;
    /*�˳��ٽ������ͷŻ�����*/
    pthread_mutex_unlock(&mtx);
  }
  return NULL;
}

int main(int argc, char *argv[])
{
  pthread_t t1, t2;
  int s;
  
  /*���������̲߳��������޸Ĺ�����Դglob*/
  s = pthread_create(&t1, NULL, thread_routine, NULL);
  if (s != 0)
      handle_error_en(s, "pthread_create");
  s = pthread_create(&t2, NULL, thread_routine, NULL);
  if (s != 0)
      handle_error_en(s, "pthread_create");
      
  /*�ȴ����߳��˳�*/    
  s = pthread_join(t1, NULL);
  if (s != 0)
      handle_error_en(s, "pthread_join");
  s = pthread_join(t2, NULL);
  if (s != 0)
      handle_error_en(s, "pthread_join");
  /*������*/    
  printf("glob = %d\n", glob);
  exit(EXIT_SUCCESS);
}
