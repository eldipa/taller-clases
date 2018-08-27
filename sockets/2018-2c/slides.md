# Sockets

---

## ¿Qué son los sockets?

* Recurso del sistema para comunicar procesos.

    * Pueden estar sobre una red o dentro del mismo sistema.

    * Permite establecer la comunicación sobre un protocolo.

???

Los sockets son recursos del sistema que se utilizan para comunicar procesos sobre una red o dentro del mismo sistema.

Nos provee distintos protocolos según el tipo de comunicación que queremos realizar. Por ejemplo, el protocolo TCP es ideal para un flujo de datos continuo (stream), el protocolo UDP está orientado a datagramas, entre otros.

---

## Creación de sockets

### Primitiva socket()

~~~{.c}
#include <sys/socket.h>

int socket(int domain, int type, int protocol);
~~~

¿Cómo lleno estos datos?

--

int socketFd = socket(AF_INET, SOCK_STREAM, 0);

???

Para crear un socket, llamamos a su primitiva correspondiente, `socket()`. Esta primitiva toma 3 parámetros:
* El dominio, que es la familia de protocolos sobre la que va a funcionar(por ejemplo, sockets IPv4, IPv6, UNIX).
* El tipo de socket, que define el tipo de conexión (por ejemplo, stream, datagramas, paquetes, etc),
* Por último el protocolo a utilizar. Normalmente existe un protocolo por tipo de socket, por lo que se pone esta opción en 0 para que seleccione el default.

Para la gran mayoría de los problemas de esta materia, utilizaremos TCP sobre IPv4

---

### Si hay constructor hay destructor

~~~
#include <unistd.h>

...

close(socketFd);
...
~~~

???

Como cualquier recurso adquirido, debo liberarlo para no perder memoria. Para esto llamamos a `close()` pasándole su *file descriptor*

Ver 00-create.c

---

## Conectar sockets

### Primitiva connect (parte 1)

~~~{.c}
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
~~~

Recibe un socket, una estructura con información de la conexión, y el largo de la estructura.

Ejemplo con ipv4:

~~~{.c}
struct sockaddr_in ip4addr;
ip4addr.sin_family = AF_INET;
ip4addr.sin_port = htons(80);
inet_pton(AF_INET, myAddress, &ip4addr.sin_addr);
 
connect(socketFd, (struct sockaddr*)&ip4addr, sizeof ip4addr);
~~~

???

Ver 01-connect.c

---

### Primitiva getaddrinfo

¿Cómo resuelvo nombres como "fi.uba.ar"?

~~~{.c}
struct addrinfo hints;
struct addrinfo *ai_list;

/* int getaddrinfo(const char *node, const char *service,
      const struct addrinfo *hints, struct addrinfo **res); */
getaddrinfo("fi.uba.ar", "http", &hints, &ai_list);
~~~

Crea una lista de direcciones posibles en `&ai_list`

---

### Primitiva getaddrinfo

#### Utilizando el struct addrinfo

~~~{.c}
// Utilizo `ptr` para iterar la lista
struct addrinfo *ptr;
for (ptr = ai_list; ptr != NULL && are_we_connected == false; ptr = ptr->ai_next) {  
  // intento conectarme con la familia, tipo y protocolo sugeridos
  socketFd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
  // TODO: validar errores de socket()
  s = connect(socketFd, ptr->ai_addr, ptr->ai_addrlen);
  // TODO: validar errores de connect()
  are_we_connected = (s != -1); // nos conectamos?
}
~~~

--

Una vez conectado, puedo liberar la lista de direcciones

~~~{.c}
freeaddrinfo(&ai_list);
~~~

???

El struct `addrinfo` es una lista enlazada con las posibles direcciones a las que nos podemos conectar.

Iteramos esta lista para ver qué dirección nos da como válida.
Notar que nos quedamos con el puntero inicial para después poder liberar los recursos

Ver 02-getaddrinfo.c

---

## Escritura y lectura sobre sockets

Las primitivas `recv` y `send` son análogas a `read` y `write` para archivos.

~~~{.c}
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
ssize_t send(int sockfd, void *buf, size_t len, int flags);
~~~

???

Para leer y escribir datos a través de sockets usamos las primitivas `recv` y `send` respectivamente. Estas primitivas reciben un socket sobre el cuál operar, un buffer, la longitud máxima del buffer, y flags opcionales (el más relevante es MSG_NOSIGNAL).

`recv` devuelve la cantidad de bytes recibidos, mientras que send devuelve la cantidad de bytes enviados. Este número de bytes puede variar por diversos motivos (estado de la red, conexión, etc), y no siempre son iguales a len. El número de reads tampoco tienen que corresponder con el de sends. Por ejemplo, desde un servidor podemos enviar 100 bytes en un solo `send` y un cliente puede recibirlo con 10 `recv`s.

Ver 03-send-recv

---

## Como recibir conexiones

### Cambios en getaddrinfo

~~~{.c}
// Antes: hints.ai_flags = 0;
hints.ai_flags = AI_PASSIVE;
...
// Antes: getaddrinfo("fi.uba.ar", "http", &hints, &ai_list);
s = getaddrinfo(NULL, port, &hints, &ptr);
~~~

???

¿Cómo se arman las conexiones del lado del servidor? Es muy similar a cómo se arma un cliente. Antes indicabamos, mediante getaddrinfo o inet_pton, el host y el puerto a quienes nos queremos conectar. Ahora asignamos el host como `NULL` para poder recibir conexiones de cualquier IP.
Además, utilizamos un *hint* nuevo: AI_PASSIVE.
En la jerga de sockets, un socket que recibe conexiones se le dice *pasivo*.

--

### Primitivas bind() y listen()

~~~{.c}
// Antes: connect(socketFd, ptr->ai_addr, ptr->ai_addrlen);
s = bind(socketFd, ptr->ai_addr, ptr->ai_addrlen);
// Indico cuantos clientes puedo tener en espera
s = listen(socketFd, 20);
~~~

???

En vez de utilizar connect, utilizamos bind, para tomar un puerto disponible en nuestra interfaz de red, y después listen, para habilitar una cola de tamaño N para las conexiones entrantes.

---

## Los declaro servidor y cliente

### Accept()

~~~{.c}
// socketFd es el "aceptador", el socket pasivo que realizó bind y listen
// peerFd es un nuevo socket, 
int peerFd = accept(socketFd, NULL, NULL);
~~~

Cuando ejecutamos accept, el servidor se bloquea hasta que un cliente se conecte. Cuando un cliente se conecta, accept se conecta (o se cierra el canal), accept devuelve un nuevo socket.

Utilizaremos este nuevo socket para comunicarnos

(Ver "establecimiento de un canal" en las diapositivas de Martín Di Paola)

---

## Cierre de canales

Un socket es bidireccional, en el mismo socket podemos escribir o leer datos.

Tanto del lado del servidor como del lado del cliente podemos cerrar el canal de comunicación de un socket.

~~~{.c}
shutdown(socketFd, modo);
~~~

Siendo `modo`:

* `SHUT_WR`: cierra el canal de escritura

* `SHUT_RD`: cierra el canal de lectura

* `SHUT_RDWR`: cierra ambos canales

---

## Protocolos

Existen distintas formas de codificar los mensajes que enviamos con nuestros sockets.

* Protocolos binarios / de texto

* Longitud fija / variable

---

### Protocolos binarios

#### Longitud fija

Ej: 4 bytes para el padrón y 20 bytes para el nombre

~~~
[\0][\0][\1][\64]Luis Huergo[\0][\0][\0][\0][\0][\0][\0][\0][\0]
~~~

#### Longitud variable (largo preconcatenado)

Ej: 4 bytes para el padron, 2 bytes para la longitud del nombre, y el nombre.

~~~
[\0][\0][\1][\64][\0][\11]Luis Huergo
~~~

???

Los protocolos binarios requieren menos transformaciones, son más sencillos de serializar y deserializar, son más eficientes con la memoria y más eficientes de procesar. En contrapuesta, se debe tener en cuenta el padding de las estructuras, el endianness, el tamaño de los números (es bueno usar tipos declarados en stdint.h) y los signos.

### Protocolos de texto

### Longitud fija

~~~
00300Luis_Huergo_____
~~~

### Longitud variable (delimitador)

Retomamos un ejemplo ya usado: cabecera HTTP

~~~
GET / HTTP/1.1\n
Host: fi.uba.ar:80\n
\n
~~~

???

En contrapuesta a los protocolos binarios, los protocolos de texto son más ineficientes, lentos y requieren serializar el modelo a texto plano. No dependen del endianness y del padding, pero puede variar según el encoding y los caracteres delimitadores (que pueden variar según el S.O.)

---

## Herramientas útiles

### Netcat

Netcat en modo cliente

~~~{.bash}
nc [host] [puerto]
~~~

Netcat en modo servidor

~~~{.bash}
nc -l [puerto]
~~~

### Netstat

~~~{.bash}
netstat -tuaon
~~~

???

Netcat: Recordar que con <ctrl> + D se indica que se llegó a fin de archivo y se cierra la conexión
Netstat: *t*: tcp, *u*: udp, *a*: all, *n*: info numérica, *o*: timers

---

# ¿Preguntas?