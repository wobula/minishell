/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*       path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 14:52:20 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/13 18:25:28 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_new_path(char *path, char *exe, int start, int stop)
{
	char *new_path;

	new_path = ft_strsub(path, start, stop - start);
	new_path = ft_strxjoin(new_path, "/", 1);
	new_path = ft_strxjoin(new_path, exe, 1);
	return (new_path);
}

char	*find_path(char *path, char *exe)
{
	int x;
	int start;
	int stop;
	char*new_path;

	x = 5;
	start = 5;
	stop = 0;
	while (path[x])
	{
		if (path[x + 1] == ':' || path[x + 1] == '\0')
		{
			stop = x + 1;
			new_path = get_new_path(path, exe, start, stop);
			if (access(new_path, X_OK) == 0)
				return (new_path);
			start = x + 2;
			ft_strdel(&new_path);
		}
		x++;
	}
	return (NULL);
}

char	*find_env_path(t_mini *env, char *exe)
{
	char*new;

	new = NULL;	
	env->pat = get_index(env->my_environ, "PATH", 4);
	if (env->pat > -1)
		new = find_path(env->my_environ[env->pat], exe);
	if (!new)
		new = ft_strdup(exe);
	return (new);
}
