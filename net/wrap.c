#include <errno.h>
#include <stdio.h>
// #include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

void perr_exit(const char *s)
{
  perror(s);
  exit(-1);
}

int Socket(int domain, int type, int protocol)
{
  int n;

  if ((n = socket(domain, type, protocol)) < 0)
    perr_exit("socket error");

  return n;
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
  int n;

again:
  if ((n = accept(sockfd, addr, addrlen)) < 0)
    if (errno == EINTR || errno == ECONNABORTED)
      goto again;
    else
      perr_exit("accept error");
  return n;
}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
  int n;

  if ((n = bind(sockfd, addr, addrlen)) < 0)
    perr_exit("bind error");

  return n;
}

int Listen(int sockfd, int backlog)
{
  int n;

  if ((n = listen(sockfd, backlog)) < 0)
    perr_exit("listen error");

  return n;
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
  int n;

  if ((n = connect(sockfd, addr, addrlen)) < 0)
    perr_exit("connect error");

  return n;
}

int Close(int fd)
{
  int n;

  if ((n = close(fd)))
    perr_exit("close error");

  return n;
}

ssize_t Read(int fd, void *buf, size_t count)
{
  int n;

again:
  if ((n = read(fd, buf, count)) < 0)
    if (errno == EINTR)
      goto again;

  return n;
}

ssize_t Write(int fd, const void *buf, size_t count)
{
  int n;

again:
  if ((n = write(fd, buf, count)) < 0)
    if (errno == EINTR)
      goto again;

  return n;
}

ssize_t Readn(int fd, const void *buf, size_t count)
{
  ssize_t nleft = count;
  ssize_t nread = 0;
  char *ptr = (char *)buf;

  while (nleft > 0)
  {
    if ((nread = read(fd, ptr, nleft)) < 0)
      if (errno == EINTR)
        nread = 0;
      else
        return -1;
    else if (nread == 0)
      break;

    nleft -= nread;
    ptr += nread;
  }

  return count - nleft;
}

ssize_t Writen(int fd, const void *buf, size_t count)
{
  ssize_t nleft = count;
  ssize_t nwritten = 0;
  char *ptr = (char *)buf;

  while (nleft > 0)
  {
    if ((nwritten = write(fd, buf, nleft)) < 0)
      if (errno == EINTR)
        nwritten = 0;
      else
        return -1;

    nleft -= nwritten;
    ptr += nwritten;
  }

  return count - nwritten;
}