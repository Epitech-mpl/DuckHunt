/*
** remote.c for DuckHunt in /home/olivie_f/dev/DuckHunt
** 
** Made by Samuel Olivier
** Login   <olivie_f@epitech.net>
** 
** Started on  Fri Mar 27 10:30:28 2015 Samuel Olivier
** Last update Fri Mar 27 10:55:55 2015 Samuel Olivier
*/

#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <stdio.h>
#include <errno.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

#include "remote.h"

static void		remote_read(t_remote *this);
static int		read_float(t_remote *this, float *x, float *y);

t_remote		*new_remote()
{
  t_remote		*this;
  struct sockaddr_in	addr;
  socklen_t		addr_len;

  if ((this = malloc(sizeof(*this))) == NULL) {
    perror("malloc()");
    return (NULL);
  }
  bzero(this, sizeof(*this));
  this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (this->server_socket == -1) {
    perror("socket()");
    free(this);
    return (NULL);
  }
  this->server_addr.sin_family = AF_INET;
  this->server_addr.sin_addr.s_addr = INADDR_ANY;
  this->server_addr.sin_port = htons(DEFAULT_PORT_NUMBER);
  if (bind(this->server_socket, (struct sockaddr *)&(this->server_addr),
	   sizeof(this->server_addr)) < 0) {
    this->server_addr.sin_port = htons(0);
    if (bind(this->server_socket, (struct sockaddr *)&(this->server_addr),
	     sizeof(this->server_addr)) < 0) {
      perror("bind()");
      close(this->server_socket);
      free(this);
      return (NULL);
    }
  }
  if (listen(this->server_socket, 2) == -1) {
    perror("listen()");
    close(this->server_socket);
    free(this);
    return (NULL);
  }
  addr_len = sizeof(addr);
  getsockname(this->server_socket, (struct sockaddr*)&addr, &addr_len);
  printf("[DEBUG] Server listenning on port %d\n", ntohs(addr.sin_port));
  this->client_socket = -1;
  return this;
}

void		delete_remote(t_remote* this)
{
  if (this->client_socket != -1) {
    close(this->client_socket);
  }
  if (this->server_socket != -1) {
    close(this->server_socket);
  }
  free(this->buffer);
  free(this);
}

int		remote_check_input(t_remote *this, float *x, float *y)
{
  fd_set		read_set;
  int			watching_fd;
  struct timeval	timeout;
  int			select_res;
  socklen_t		len;

  watching_fd = (this->client_socket == -1) ? this->server_socket :
    this->client_socket;
  FD_ZERO(&read_set);
  FD_SET(watching_fd, &read_set);
  timeout.tv_sec = 0;
  timeout.tv_usec = 20000;
  select_res = select(watching_fd + 1, &read_set, NULL, NULL, &timeout);
  if (select_res == -1) {
    return 0;
  } else if (select_res > 0 && FD_ISSET(watching_fd, &read_set)) {
    if (this->client_socket == -1) {
      len = sizeof(this->client_addr);
      this->client_socket = accept(this->server_socket,
				   (struct sockaddr*)&(this->client_addr),
				   &len);
      if (this->client_socket != -1) {
	printf("[DEBUG] New client\n");
      }
    } else {
      remote_read(this);
      return (read_float(this, x, y));
    }
  }
  return (0);
}

static int	read_float(t_remote *this, float *x, float *y)
{
  int		i;
  int		ok;
  int		first;

  i = 0;
  ok = 0;
  while (i < this->buffer_size && ok != 2) {
    if (ok == 0 && this->buffer[i] == ' ') {
      ok = 1;
      first = i;
    } else if (ok == 1 && this->buffer[i] == '\n') {
      ok = 2;
    }
    ++i;
  }
  if (ok != 2) {
    return (0);
  }
  this->buffer[first] = 0;
  *x = atof(this->buffer);
  this->buffer[i - 1] = 0;
  *y = atof(&(this->buffer[first + 1]));
  this->buffer_size -= i;
  bcopy(&(this->buffer[i]), this->buffer, this->buffer_size);
  this->buffer = realloc(this->buffer, this->buffer_size);
  return 1;
}

static void	remote_read(t_remote *this)
{
  char		buffer[42];
  int		nb_read;

  nb_read = read(this->client_socket, buffer, sizeof(buffer));
  if (nb_read == 0) {
    close(this->client_socket);
    free(this->buffer);
    this->buffer = NULL;
    this->buffer_size = 0;
    this->client_socket = -1;
    printf("[DEBUG] Client left\n");
  } else {
    this->buffer = realloc(this->buffer, this->buffer_size + nb_read);
    memcpy(&(this->buffer[this->buffer_size]), buffer, nb_read);
    this->buffer_size += nb_read;
  }
}
