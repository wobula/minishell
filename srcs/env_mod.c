/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 11:49:16 by rschramm          #+#    #+#             */
/*   Updated: 2017/03/20 11:50:15 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**env_unset(t_mini *env, char **split)
{
	int	index;
	char**new;
	int x;
	int y;

	index = -1;
	x = 0;
	index = get_index(env->my_environ, split[1], ft_strlen(split[1]));
	while (env->my_environ[x])
		x++;
	new = (char**)ft_memalloc(sizeof(char*) * x - 1);
	new[x - 1] = 0;
	x = 0;
	y = 0;
	while (env->my_environ[x])
	{
		if (x != index && (new[y] = ft_strdup(env->my_environ[x])))
			y++;
		x++;
	}
	del_old_env(env);
	return (new);
}

char	**new_entry(t_mini *env, char **split)
{
	int x;
	char**new;

	x = 0;
	while (env->my_environ[x])
		x++;
	new = (char**)ft_memalloc(sizeof(char*) * x + 1);
	new[x] = ft_strxjoin(split[1], "=", 0);
	if (split[2])
		new[x] = ft_strxjoin(new[x], split[2], 1);
	new[x + 1] = 0;
	x = 0;
	while (env->my_environ[x])
	{
		new[x] = ft_strdup(env->my_environ[x]);
		x++;
	}
	del_old_env(env);
	return (new);
}

void	existing_entry(t_mini *env, char **split, int index)
{
	char	*new;
	char	*name;
	int		x;

	x = 0;
	new = NULL;
	while (split[1][x] >= 'A' && split[1][x] <= 'Z')
		x++;
	name = ft_strsub(split[1], 0, x);
	name = ft_strxjoin(name, "=", 1);
	if (split[2])
	{
		new = ft_strxjoin(name, split[2], 0);
		ft_strdel(&env->my_environ[index]);
		env->my_environ[index] = ft_strdup(new);
	}
	else
	{
		ft_strdel(&env->my_environ[index]);
		env->my_environ[index] = ft_strdup(new);
	}
	if (new)
		ft_strdel(&new);
	ft_strdel(&name);
}
