#ifndef RESOLVER_H
#define RESOLVER_H

struct addrinfo;

struct resolver_t {
    struct addrinfo *result;
    struct addrinfo *next;
};

int resolver_init(struct resolver_t *self, const char* hostname, const char* servicename, bool passive);

bool resolver_has_next(struct resolver_t *self);

struct addrinfo* resolver_next(struct resolver_t *self);

void resolver_deinit(struct resolver_t *self);

#endif
