/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 11:50:51 by rschramm          #+#    #+#             */
/*   Updated: 2017/03/23 08:02:06 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**trim_quotes(char **split)
{
	char	buff[4000];
	int		x;
	int		y;
	int		z;

	x = 1;
	y = 0;
	z = 0;
	while (split[x])
	{
		while (split[x][y] != '\0')
		{
			if (split[x][y] != 34 && split[x][y] != 39)
			{
				buff[z] = split[x][y];
				z++;
			}
			y++;
		}
		buff[z] = '\0';
		ft_strdel(&split[x]);
		split[x] = ft_strdup(buff);
		z = 0;
		y = 0;
		x++;
	}
	return (split);
}

char	*root_or_directory(t_mini *env, char *split)
{
	char *new;

	if ((ft_charfind(split, '/')) > -1)
		new = ft_strdup(split);
	else
		new = ft_strxjoin(env->path, split, 0);
	ft_strdel(&split);
	return (new);
}

char	*substitute(t_mini *env, char *str)
{
	int	index;
	char*new;

	new = NULL;
	if ((index = get_index(env->my_environ, str + 1, ft_strlen(str + 1))) > -1)
		new = ft_strdup(env->my_environ[index] + ft_strlen(str + 1) + 1);
	ft_strdel(&str);
	return (new);
}

char	**dollar_sign(t_mini *env, char **split)
{
	int x;

	x = 0;
	while (split[x])
	{
		if (split[x][0] == '$')
			split[x] = substitute(env, split[x]);
		x++;
	}
	return (split);
}

void	run_program(t_mini *env, char **split)
{
	pid_t	pid;
	int		ex;
	char	*tmp;
	char	*path;

	tmp = ft_strdup(split[0]);
	split = dollar_sign(env, split);
	path = find_env_path(env, split[0]);
	split = trim_quotes(split);
	if (access(path, X_OK) != 0)
	{
		ft_printf("rsh: command not found: %s\n", tmp);
		ft_strdel(&tmp);
		ft_strdel(&path);
		return ;
	}
	ft_strdel(&tmp);
	if ((pid = fork()) == -1 && ft_printf("fork error"))
		return ;
	if (pid == 0)
	{
		execve(path, split, env->my_environ);
		ft_strdel(&path);
		_exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(-1, &ex, 0);
		ft_strdel(&path);
		if (WIFEXITED(ex))
			return ;
	}
}
