/*
** wrapper.c for PSU_2016_myirc in /home/antoine.cauquil/rendu/network/PSU_2016_myirc/src_client
** 
** Made by bufferking
** Login   <antoine.cauquil@epitech.eu>
** 
** Started on  Mon May 29 17:29:25 2017 bufferking
** Last update Thu Jun  1 11:35:44 2017 
*/

#include "irc_client.h"

const char	*g_cmd_list[] =
  {
    "/quit", "/server", "/nick", "/list", "/join", "/part",
    "/users", "/names", "/msg", "/accept_file"
  };

t_comm_handler	g_cmd_handler[] =
  {
    cmd_quit, cmd_server, cmd_nick, cmd_list
  };

int	cmdlen(void)
{
  int	i;

  i = 0;
  while (g_cmd_handler[i])
    i++;
  return (i);
}

int		send_data(t_server *srv, const char *format, ...)
{
  va_list	args;

  if (srv->sd == -1)
    return (logmsg(MSG, "%s\n", ERROR_NO_SRV));
  va_start(args, format);
  vdprintf(srv->sd, format, args);
  va_end(args);
  return (0);
}

int		recv_data(t_server *srv, char **buffer)
{
  size_t	len;

  len = 0;
  if (getline(buffer, &len, fdopen(srv->sd, "r")) == -1)
    return (print_error("getline"));
  return (len);
}

static int	init_wrapper(t_server *srv, char ***cmd, FILE **in)
{
  int		i;
  
  i = 0;
  srv->sd = -1;
  srv->addr.sin_family = AF_INET;
  if (!(*in = fdopen(0, "r")))
    return (print_error("fdopen"));
  if (!(*cmd = malloc(sizeof(char *) * cmdlen())))
    return (print_error("malloc"));  
  while (i < cmdlen())
    (*cmd)[i++] = NULL;
  return (0);
}

int	client_wrapper(void)
{
  char		*raw;
  char		**cmd;
  size_t	size;
  FILE		*in;
  t_server	srv;
  int		i;
  
  raw = NULL;
  cmdlen();
  size = 0;
  i = 0;
  if (init_wrapper(&srv, &cmd, &in))
    return (EXIT_FAILURE);
  while (i != -1 && getline(&raw, &size, in) != -1)
    {
      i = 0;
      cmd[0] = strtok(raw, " \n");
      while (i < 4)
	cmd[++i] = strtok(NULL, " \n");
      i = -1;
      while (g_cmd_handler[++i])
	if (!(strcmp(g_cmd_list[i], cmd[0])))
	  {
	    if (!srv.sd && strcmp(cmd[0], "/server") && strcmp(cmd[0], "/quit"))
	      logmsg(MSG, "%s\n", ERROR_NO_SRV);
	    else
	      i = g_cmd_handler[i](&srv, cmd);
	    break;
	  }
      if (i == cmdlen())
	send_data(&srv, "%s\n", raw);
    }
  free(cmd);
  free(raw);
  fclose(in);
  return (EXIT_SUCCESS);
}