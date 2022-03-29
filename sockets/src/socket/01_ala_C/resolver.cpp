#include "resolver.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

int resolver_init(struct resolver_t *self, const char* hostname, const char* servicename, bool passive) {
    struct addrinfo hints;
    self->result = self->next = 0;

    /* Creo una especie de filtro para decir que direcciones me interesan
       En este caso, TCP sobre IPv4 para ser usada por un socket 'activo'
       (no es para un server)
       */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
    hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
    hints.ai_flags = passive ? : AI_PASSIVE : 0;  /* None (or AI_PASSIVE for server) */


    /* Obtengo la (o las) direcciones segun el nombre de host y servicio que
       busco

       De todas las direcciones posibles, solo me interesan aquellas que sean
       IPv4 y TCP (segun lo definido en hints)

       El resultado lo guarda en result
       */
    s = getaddrinfo(hostname, servicename, &hints, &self->result);

    /* Es muy importante chequear los errores.
       En caso de uno, usar gai_strerror para traducir el codigo de error (s)
       a un mensaje humanamente entendible.
       */
    if (s != 0) {
        printf("Error in getaddrinfo: %s\n", gai_strerror(s));
        return 1;  // TODO lanzar una excepcion
    }

    return 0;
}

bool resolver_has_next(struct resolver_t *self) {
    return self->next != NULL;
}

struct addrinfo* resolver_next(struct resolver_t *self) {
    struct addrinfo *ret = self->next;
    self->next = ret->ai_next;
    return ret;
}

void resolver_deinit(struct resolver_t *self) {
    freeaddrinfo(self->result);
}

