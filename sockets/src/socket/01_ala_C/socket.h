#ifndef SOCKET_H
#define SOCKET_H

struct socket_t {
    int skt;
    bool closed;
};

int socket_shutdown(struct socket_t *self, int how);

int socket_close(struct socket_t *self);

int socket_deinit(struct socket_t *self);

int socket_recvsome(struct socket_t *self, void *data, unsigned int sz);

int socket_sendsome(struct socket_t *self, void *data, unsigned int sz);

int socket_recvall(struct socket_t *self, void *data, unsigned int sz, bool *imm_closed);


int socket_sendall(struct socket_t *self, void *data, unsigned int sz, bool *imm_closed);

int socket_init_for_connection(struct socket_t *self, const char *hostname, const char *servicename);

int socket_init_for_listen(struct socket_t *self, const char *servicename);


#endif

