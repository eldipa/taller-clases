#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include "common_skt.h"

int socket_shutdown(struct socket_t *self, int how) {
    return shutdown(self->skt, how);
}

int socket_close(struct socket_t *self) {
    self->closed = true;
    return close(self->skt);
}

int socket_deinit(struct socket_t *self) {
    if (not self->closed) {
        shutdown(self->skt, how);
        return close(self->skt);
    }
}

int socket_recvsome(struct socket_t *self, void *data, unsigned int sz) {
    // TODO checkear errores
    return recv(self->skt, (char*)data, sz, 0);
}

int socket_sendsome(struct socket_t *self, void *data, unsigned int sz) {
    // TODO checkear errores
    return send(self->skt, (char*)data, sz, MSG_NOSIGNAL);
}

int socket_recvall(struct socket_t *self, void *data, unsigned int sz, bool *imm_closed) {
    int ret = -1;
    int s;
    unsigned int received = 0;
    *imm_closed = false;

    while (received < sz) {
        s = recv(self->skt, (char*)data + received, sz - received, 0);
        if (s == 0) {
            // TODO puede ser o no un error
            perror("socket unexpected closed");
            *imm_closed = received == 0;
            return 0;
        }
        else if (s < 0) {
            // TODO 99% casi seguro que es un error
            return s;
        }
        else {
            received += s;
        }
    }

    return sz;
}


int socket_sendall(struct socket_t *self, void *data, unsigned int sz, bool *imm_closed) {
    int ret = -1;
    int s;
    unsigned int sent = 0;
    *imm_closed = false;

    while (sent < sz) {
        s = send(self->skt, (char*)data + sent, sz - sent, MSG_NOSIGNAL);
        if (s == 0) {
            // TODO puede ser o no un error
            perror("socket unexpected closed");
            *imm_closed = sent == 0;
            return 0;
        }
        else if (s < 0) {
            if (errno == EPIPE) {
                // TODO puede ser o no un error
                perror("socket unexpected closed");
                *imm_closed = sent == 0;
                return 0;
            }

            // TODO 99% casi seguro que es un error
            return s;
        }
        else {
            sent += s;
        }
    }

    return sz;
}

int socket_connect(struct socket_t *self, const char *hostname, const char *servicename) {
    struct resolver_t resolver;
    if (resolver_init(&resolver, hostname, servicename, false) != 0)
        return -1;

    int skt = -1;
    while (resolver_has_next(&resolver)) {
        struct addrinfo *addr = resolver_next(&resolver);
        /* Creamos el socket definiendo la familia (deberia ser AF_INET IPv4),
           el tipo de socket (deberia ser SOCK_STREAM TCP) y el protocolo (0) */
        skt = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (skt == -1) {
            printf("Error: %s\n", strerror(errno));
        }
        else
        {
            /* Nos conectamos.
               ai_addr encapsula la IP y el puerto del server.
               La estructura es automaticamente creada por getaddrinfo */
            s = connect(skt, addr->ai_addr, addr->ai_addrlen);
            if (s == -1) {
                printf("Error: %s\n", strerror(errno));
                close(skt);
            }

            if (s != -1) { // nos conectamos?
                self->skt = skt;
                resolver_deinit(&resolver);
                return 0;
            }
        }
    }

    resolver_deinit(&resolver);
    return -1;
}

int socket_setup_listener(struct socket_t *self, const char *servicename) {
    struct resolver_t resolver;
    if (resolver_init(&resolver, hostname, servicename, false) != 0)
        return -1;

    int skt = -1;
    while (resolver_has_next(&resolver)) {
        struct addrinfo *addr = resolver_next(&resolver);
        /* Creamos el socket definiendo la familia (deberia ser AF_INET IPv4),
           el tipo de socket (deberia ser SOCK_STREAM TCP) y el protocolo (0) */
        skt = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (skt == -1) {
            printf("Error: %s\n", strerror(errno));
        }
        else
        {
            int val = 1;
            s = setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
            if (s == -1) {
                printf("Error: %s\n", strerror(errno));
                close(skt);
                continue;
            }

            s = bind(skt, addr->ai_addr, addr->ai_addrlen);
            if (s == -1) {
                printf("Error: %s\n", strerror(errno));
                close(skt);
                continue;
            }

            s = listen(skt, 20);
            if (s == -1) {
                printf("Error: %s\n", strerror(errno));
                close(skt);
                continue;
            }

            if (s != -1) { // setupeamos el socket? escuchando?
                self->skt = skt;
                return 0;
            }
        }
    }

    return -1;
}


