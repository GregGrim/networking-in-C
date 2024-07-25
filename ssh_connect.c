#include "sock_init.h"
#include "xplatform_socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libssh/libssh.h>

int main(int argc, char *argv[]) {
    const char *hostname = 0;
    int port = 22;
    if (argc < 2) {
        fprintf(stderr, "Usage: ssh_connect hostname port.\n");
        return 1;
    }
    hostname = argv[1];
    if (argc > 2) port = atol(argv[2]);

    ssh_session ssh = ssh_new();
    if (!ssh) {
        fprintf(stderr, "ssh_new() failed.\n");
        return 1;
    }

    ssh_options_set(ssh, SSH_OPTIONS_HOST, hostname);
    ssh_options_set(ssh, SSH_OPTIONS_PORT, &port);

    int verbosity = SSH_LOG_PROTOCOL;
    ssh_options_set(ssh, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);

    int ret = ssh_connect(ssh);
    if (ret != SSH_OK) {
        fprintf(stderr, "ssh_connect() failed.\n%s\n", ssh_get_error(ssh));
        return -1;
    }

    printf("Connected to %s on port %d.\n", hostname, port);

    printf("Banner:\n%s\n", ssh_get_serverbanner(ssh));

    ssh_disconnect(ssh);
    ssh_free(ssh);

    return 0;
}