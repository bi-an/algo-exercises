#include "wrap.h"
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h> // STDOUT_FILENO

static const int SERV_PORT = 6666;
static const int MAX_LINE = 80;

int main(int argc, char **argv)
{
  struct sockaddr_in serv_addr;
  int sockfd, n;
  char buf[MAX_LINE];

  if (argc != 2)
    perr_exit("./client IP");

  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);
  serv_addr.sin_port = htons(SERV_PORT);

  sockfd = Socket(AF_INET, SOCK_STREAM, 0);

  Connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
  printf("--------------- connected --------------\n");

  while(fgets(buf, sizeof(buf), stdin) != NULL) {
      Write(sockfd, buf, strlen(buf));
      if((n = Read(sockfd, buf, sizeof(buf))) == 0) {
          printf("the peer has been closed\n");
          break;
      } else {
          Write(STDOUT_FILENO, buf, n);
      }
  }

  Close(sockfd);

  return 0;
}