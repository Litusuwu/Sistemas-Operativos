//int socket(int domain, int type, int protocol);
//int binf(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>
#include <string.h>

#define SV_SOCK_PATH "/tmp/us_xfr"
#define BUF_SIZE 100
#define BACKLOG 5

int main(int argc, char *argv[]){
    struct sockaddr_un addr;
    int sfd, cfd;
    ssize_t numRead;
    char buf[BUF_SIZE];

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sfd == -1)perror("socket");
    if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT)
    perror("remove");

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

    if (bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
    perror("bind");

    if (listen(sfd, BACKLOG) == -1)
        perror("listen");

    for (;;) { /* Handle client connections iteratively */

    /* Accept a connection. The connection is returned on a new
       socket, 'cfd'; the listening socket ('sfd') remains open
       and can be used to accept further connections. */

        cfd = accept(sfd, NULL, NULL);
        if (cfd == -1)
            perror("accept");

    /* Transfer data from connected socket to stdout until EOF */

    while ((numRead = read(cfd, buf, BUF_SIZE)) > 0)
        if (write(STDOUT_FILENO, buf, numRead) != numRead)
            perror("partial/failed write");

        if (numRead == -1)
            perror("read");

        if (close(cfd) == -1)
            perror("close");
    }   

}
