#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

//线程等待
void* thr_entry(void* arg){
    pthread_detach(pthread_self());
    sleep(3);
    char* ptr="hello";
    pthread_exit(ptr);//退出线程
    pthread_cancel((pthread_t)arg);
    while(1){
        printf("i am common thread-----%s\n",(char*)arg);
        sleep(1);
   }
    return NULL;
}

int main()
{
    pthread_t mtid;
    mtid=pthread_self();
    //int pthread_create(pthread_t *thread,const pthread_attr_t *attr,
    //                   void*(*start_routine)(void*),void *arg);
    pthread_t tid;
    char* param="this is input param";
    int ret=pthread_create(&tid,NULL,thr_entry,(void*)mtid);
    if(ret!=0)
    {
        printf("pthread create error\n");
        return -1;
    }
    pthread_detach(tid);
    void* retval;
    //ret=pthread_join(tid,&retval);
    //if(ret==EINVAL){
      //  printf("thread is not joinable\n");
    //}
    printf("tid:%p\n",tid);
    while(1){
        printf("i am main thread-----\n");
        sleep(1);
    }
    return 0;
}
