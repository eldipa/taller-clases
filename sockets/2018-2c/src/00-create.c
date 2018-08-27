/*
  Ejemplo de creación de socket.
  Ejecutar la aplicación con valgrind, notar que no hay
  file descriptors abiertos
  Ejecutar con strace y notar que la función socket() devuelve el
  file descriptor 3. Este mismo file descriptor luego es cerrado por close().
*/

#include <sys/socket.h> // socket()
#include <unistd.h> // close()

int main(int argc, char** argv) {
  int socketFd = socket(AF_INET, SOCK_STREAM, 0);
  close(socketFd);
  return 0;
}
