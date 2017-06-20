/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 11:42:46 by rschramm          #+#    #+#             */
/*   Updated: 2017/03/21 14:25:59 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_env(char **environ)
{
	char**new;
	int	x;
	int size;

	x = 0;
	size = 0;
	while (environ[x])
		x++;
	new = (char**)ft_memalloc(sizeof(char*) * x);
	new[x] = 0;
	x = 0;
	while (environ[x])
	{
		new[x] = ft_strdup(environ[x]);
		x++;
	}
	return (new);
}

void	env_set(t_mini *env, char **split)
{
	int index;

	if (!split[1] && ft_printf("usage: setenv [name] [value]\n"))
		return ;
	index = -1;
	index = get_index(env->my_environ, split[1], ft_strlen(split[1]));
	if (index == -1)
		env->my_environ = new_entry(env, split);
	else
		existing_entry(env, split, index);
}

void	env_main(t_mini *env, char **split)
{
	if (ft_strcmp(split[0], "setenv") == 0)
		env_set(env, split);
	else if (ft_strcmp(split[0], "unsetenv") == 0)
	{
		if (split[1])
			env->my_environ = env_unset(env, split);
		else
			ft_printf("usage: unsetenv [name] [value]\n");
	}
	else if (ft_strcmp(split[0], "env") == 0)
		display_env(env);
	else
		display_env(env);
}

int		env_check(char **split)
{
	int x;

	x = 0;
	while (split && split[0] && split[0][x] != '\n' && split[0][x] != '\0')
	{
		if (split[0][x] == 'e' && split[0][x + 1] == 'n' && split[0]
				[x + 2] == 'v')
			return (1);
		x++;
	}
	return (0);
}

void	del_old_env(t_mini *env)
{
	int x;

	x = 0;
	while (env->my_environ[x])
	{
		ft_strdel(&env->my_environ[x]);
		x++;
	}
	free(env->my_environ);
	env->my_environ = NULL;
}
