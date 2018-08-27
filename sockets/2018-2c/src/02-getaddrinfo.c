/**
  Ejemplo de uso de getaddrinfo.
**/

#include <stdio.h>
#include <string.h>
#include <stdbool.h> // bool
#include <errno.h> //erno
#include <sys/socket.h> // socket(), connect()
#include <unistd.h> // close()
#include <netdb.h> // getaddrinfo

int main(int argc, char** argv) {
  const char* hostname = "fi.uba.ar";
  const char* servicename = "http";

  // Creamos el socket con soporte a ipv4 y TCP
  int socketFd = socket(AF_INET, SOCK_STREAM, 0);

  // Utilizamos hints para "filtrar" las direcciones que me interesan
  struct addrinfo hints;
  // ai_list será la lista de address info, ptr mi iterados
  struct addrinfo *ai_list, *ptr;

  // Limpio hints
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
  hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
  hints.ai_flags = 0;              /* None (or AI_PASSIVE for server) */

  // El servicio se obtiene consultando el archivo /etc/service
  int s = getaddrinfo(hostname, servicename, &hints, &ai_list);
  // chequeo error
  if (s != 0) { 
    printf("Error in getaddrinfo: %s\n", gai_strerror(s));
    return 1;
  }
  // Ahora conectamos el socket
  bool are_we_connected = false;
  for (ptr = ai_list; ptr != NULL && are_we_connected == false; ptr = ptr->ai_next) {
    // TODO: chequear errores
    socketFd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    int res = connect(socketFd, ptr->ai_addr, ptr->ai_addrlen);
    if (res == -1) {
      printf("Error: %s\n", strerror(errno));
      close(socketFd);
    }
    are_we_connected = (s != -1); // nos conectamos?
  }

  freeaddrinfo(ai_list);

  close(socketFd);
  return 0;
}
