#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int c, char *v[]) {
    if (c < 2) return printf("Usage: %s <port>\n", v[0]), 1;

    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in a = {AF_INET, htons(atoi(v[1])), htonl(INADDR_ANY)};
    bind(s, (void*)&a, sizeof(a));
    listen(s, 1);

    int ns = accept(s, 0, 0), f, n;
    char b[4096];
    read(ns, b, sizeof(b));
    f = open(b, O_RDONLY);
    while ((n = read(f, b, sizeof(b))) > 0) write(ns, b, n);
    puts("Transfer done.");
    close(f); close(ns); close(s);
}
