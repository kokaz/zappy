/*
** getopt.c<2> for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Sun May  4 11:11:11 2014 guillaume fillon
** Last update Wed Jul  9 22:49:55 2014 luc sinet
*/

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <err.h>

#include "server.h"

static int	option_part1(int opt, t_world *option, int argc, char *argv[]);
static int	option_part2(int opt, t_world *option, int argc, char *argv[]);
static int	option_part3(int opt, t_world *option, int argc, char *argv[]);

static struct {
  int	c;
  int	(*f)(int opt, t_world *option, int argc, char *argv[]);
}	g_option[] =
  {
    {'h', &option_part1},
    {'c', &option_part1},
    {'t', &option_part1},
    {'p', &option_part1},
    {'x', &option_part1},
    {'y', &option_part1},
    {'n', &option_part2},
    {'v', &option_part3},
    {'?', &option_part3},
    {0, NULL}
  };

static int	option_part1(int opt, t_world *option,
			     UNUSED int argc, UNUSED char *argv[])
{
  if (opt == 'h')
    option->hflg = 1;
  else if (opt == 'c')
    option->slots = stoi(optarg);
  else if  (opt == 't')
    option->delay = stoi(optarg);
  else if (opt == 'x')
    {
      if ((option->width = stoi(optarg)) < 4)
	option->width = 4;
      printf("Too weak value for world width, set to 4\n");
    }
  else if (opt == 'y')
    {
      if ((option->height = stoi(optarg)) < 4)
	option->height = 4;
      printf("Too weak value for world height, set to 4\n");
    }
  else if (opt == 'p')
    option->port = optarg;
  return (0);
}

static int	check_team_name(char *tname, t_team *teams, int nb_teams)
{
  int		i;

  if (teams == NULL)
    return (0);
  for (i = 0; i < nb_teams; ++i)
    {
      if (strcmp(tname, teams[i].name) == 0)
	return (-1);
    }
  return (0);
}

static int	option_part2(int opt, t_world *option, int argc, char *argv[])
{
  int		index;

  if (opt == 'n')
    for (index = optind - 1; index < argc; ++index)
      {
	if (argv[index][0] != '-')
	  {
	    if (check_team_name(argv[index], option->teams,
				option->nb_teams) == -1)
	      continue ;
	    ++option->nb_teams;
	    option->teams =
	      realloc(option->teams, option->nb_teams * sizeof(t_team));
	    if (option->teams == NULL)
	      return (iperror("getopt: malloc", -1));
	    option->teams[option->nb_teams - 1].name = argv[index];
	  }
	else
	  break;
      }
  return (0);
}

static int	option_part3(int opt, t_world *option,
			     UNUSED int argc, UNUSED char *argv[])
{
  if (opt == 'v')
    {
      puts("Copyright (C) 2014 Guillaume Fillon, Luc Sinet\n\n" \
	   "Written by Guillaume Fillon and Luc Sinet.");
      exit(EXIT_SUCCESS);
    }
  if (opt == '?')
    {
      option->unkflg = 1;
      return (-1);
    }
  return (0);
}

int	parse_option(int opt, t_world *option, int argc, char *argv[])
{
  int	i;

  for (i = 0; g_option[i].f != NULL; ++i)
    {
      if (g_option[i].c == opt)
	if (g_option[i].f(opt, option, argc, argv) < 0)
	  return (-1);
    }
  return (0);
}
