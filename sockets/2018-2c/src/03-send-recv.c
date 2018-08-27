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

#define RESPONSE_MAX_LEN 1024

int main(int argc, char** argv) {
  const char* hostname = "fi.uba.ar";
  const char* servicename = "http";
  char response[RESPONSE_MAX_LEN];

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

  /**
   Enviamos un request de http
  **/

  const char* request = "GET / HTTP/1.1\nHost: fi.uba.ar:80\n\n";
  int bytes_sent = 0;
  int request_len = strlen(request);
  while (bytes_sent < request_len && are_we_connected) {
    s = send(socketFd, &request[bytes_sent], request_len - bytes_sent, MSG_NOSIGNAL);
    if (s > 0) {
      bytes_sent += s;
    }
    else {
      printf("Error: %s\n", strerror(errno));
      are_we_connected = false;
    }
  }

  /**
   Leemos la respuesta del servidor
  **/
  int bytes_recv = 0;
  while (are_we_connected) {
    s = recv(socketFd, &response[bytes_recv], RESPONSE_MAX_LEN - bytes_recv - 1, MSG_NOSIGNAL);

    if (s > 0) {
      bytes_recv = s; 

      response[bytes_recv] = 0;
      printf("%s", response);

      //reusamos el mismo buffer, no me interesa tener toda la 
      //respuesta en memoria
      bytes_recv = 0;
    }
    else {
      printf("Error: %s\n", strerror(errno));
      are_we_connected = false;
    }
  }
  printf("\n");

  close(socketFd);
  return 0;
}
