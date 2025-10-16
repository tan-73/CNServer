#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int c, char *v[]) {
    if (c < 4) return printf("Usage: %s <ip> <filename> <port>\n", v[0]), 1;

    int s = socket(AF_INET, SOCK_STREAM, 0), n;
    struct sockaddr_in a = {AF_INET, htons(atoi(v[3]))};
    a.sin_addr.s_addr = inet_addr(v[1]);

    connect(s, (void*)&a, sizeof(a));
    write(s, v[2], strlen(v[2]) + 1);

    char b[4096];
    while ((n = read(s, b, sizeof(b))) > 0) write(1, b, n);
    close(s);
}
