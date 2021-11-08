#ifndef WRAP_H
#define WRAP_H

void perr_exit(const char *s);
int Socket(int domain, int type, int protocol);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int Listen(int sockfd, int backlog);
int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int Close(int fd);
ssize_t Read(int fd, void *buf, size_t count);
ssize_t Write(int fd, const void *buf, size_t count);
ssize_t Readn(int fd, const void *buf, size_t count);
ssize_t Writen(int fd, const void *buf, size_t count);
ssize_t ReadLine(int fd, void *buf, int maxlen);

#endif