#include <arpa/inet.h>
#include <sys/epoll.h>
#include <time.h>

#include "wrap.h"

static const int BUFLEN = 4096;
static const int MAX_EVENTS = 1024;
static const int SERV_PORT = 8000;

struct myevent_s {
  int fd;                                           // 监听的描述符
  int events;                                       // 监听的事件
  void* arg;                                        // 泛型参数
  void (*callback)(int fd, int events, void* arg);  // 回调函数
  int status;        // 是否在监听，1是，0否
  char buf[BUFLEN];  // 缓冲区
  int len;           // 缓冲区长度
  int last_active;   // 记录每次加入红黑树g_efd的事件
};

// 将结构体myevent_s的成员初始化
void eventset(struct myevent_s* ev, int fd, void (*callback)(int, int, void*),
              void* arg) {
  ev->fd = fd;
  ev->callback = callback;
  ev->arg = arg;
  ev->events = 0;
  ev->status = 0;
  ev->last_active = time(NULL);
}

// 向 epoll 红黑树添加一个文件描述符
void eventadd(int efd, int events, struct myevent_s* ev) {
  struct epoll_event epv = {0, {0}};
  int opt;
  epv.data.ptr = ev;
  epv.events = ev->events = events;

  if (ev->status == 1) {
    opt = EPOLL_CTL_MOD;
  } else {
    opt = EPOLL_CTL_ADD;
    ev->status = 1;
  }

  if (epoll_ctl(efd, opt, ev->fd, &epv) < 0)
    printf("event add failed [fd=%d], events[%d]\n", ev->fd, events);
  else
    printf("event add OK [fd=%d], opt=%d, events[%0X]\n", ev->fd, opt, events);

  return;
}

// 从 epoll 红黑树删除一个文件描述符
void eventdel(int efd, struct myevent_s * ev) {
  struct epoll_event epv = {0, {0}};
  
  if(ev->status != 1)
    return;

  int opt = 
  if(epoll_ctl(efd, ))
}

// 全局变量
static int g_efd;