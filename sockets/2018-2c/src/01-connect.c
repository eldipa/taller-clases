/**
  Ejemplo de conexión de sockets.
  En este ejemplo el cliente se conecta a una ip remota (correspondiente a
  fi.uba.ar).
**/

#include <stdio.h>
#include <sys/socket.h> // socket(), connect()
#include <unistd.h> // close()
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h> // inet_pton

int main(int argc, char** argv) {
  char* myAddress = "157.92.49.38";

  // Creamos el socket con soporte a ipv4 y TCP
  int socketFd = socket(AF_INET, SOCK_STREAM, 0);

  // Armamos la dirección a la que nos vamos a conectar
  // Usamos sockaddr_in para direcciones ipv4
  // También existe sockaddr_in6 para ipv6
  struct sockaddr_in ip4addr;
  ip4addr.sin_family = AF_INET;
  // htons cambia el endianness de host a big endian (network)
  ip4addr.sin_port = htons(80);
  // inet_pton traduce del formato numerico con puntos a sin_addr
  inet_pton(AF_INET, myAddress, &ip4addr.sin_addr);

  // Ahora conectamos el socket

  // int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
  int res = connect(socketFd, (struct sockaddr*)&ip4addr, sizeof ip4addr);

  // Valido si hubo error
  if (res) {
    perror("Hubo un error en connect");
  }
  close(socketFd);
  return 0;
}
