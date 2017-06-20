/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 11:51:37 by rschramm          #+#    #+#             */
/*   Updated: 2017/03/20 11:52:13 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		get_start(char **split)
{
	int x;

	x = 1;
	while (split[x])
	{
		if (split[x][0] != '-')
			return (x);
		x++;
	}
	return (-1);
}

void	del_split(char **split)
{
	int x;

	x = 0;
	while (split[x])
	{
		if (split[x])
			ft_strdel(&split[x]);
		x++;
	}
	free(split);
	split = NULL;
}

int		get_index(char **environ, char *compare, int size)
{
	int x;

	x = 0;
	while (environ[x])
	{
		if (ft_strncmp(environ[x], compare, size) == 0)
			return (x);
		x++;
	}
	return (-1);
}

char	*trim_last_dir(char *dir)
{
	size_t	x;
	char	*new;

	x = 0;
	while (dir[x])
		x++;
	while (dir[x] != '/')
		x--;
	new = ft_strsub(dir, 0, x);
	return (new);
}

int		display_env(t_mini *env)
{
	int x;

	x = 0;
	while (env->my_environ[x])
	{
		ft_printf("[%d]: %s\n", x, env->my_environ[x]);
		x++;
	}
	return (1);
}
