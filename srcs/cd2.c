/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 11:42:02 by rschramm          #+#    #+#             */
/*   Updated: 2017/03/20 11:42:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_case_root(t_mini *env, char **split)
{
	char buff[4000];

	chdir(split[1]);
	ft_strdel(&env->my_environ[env->old_pwd]);
	env->my_environ[env->old_pwd] = ft_strxjoin("OLDPWD=",
		env->my_environ[env->pwd] + 4, 0);
	ft_strdel(&env->my_environ[env->pwd]);
	env->my_environ[env->pwd] = ft_strdup(getcwd(buff, sizeof(buff)));
	env->my_environ[env->pwd] = ft_strxjoin("PWD=", env->my_environ[env->pwd],
		2);
}

void	cd_case_home(t_mini *env, char **split)
{
	char	buff[4000];
	char	*tmp;

	if (split[1] && split[1][0] == '~')
	{
		tmp = ft_strdup(split[1]);
		ft_strdel(&split[1]);
		split[1] = ft_strxjoin(env->my_environ[env->home] + 5, tmp + 1, 0);
		ft_strdel(&tmp);
		chdir(split[1]);
	}
	else
		chdir(env->my_environ[env->home] + 5);
	ft_strdel(&env->my_environ[env->old_pwd]);
	env->my_environ[env->old_pwd] = ft_strxjoin("OLDPWD=",
			env->my_environ[env->pwd] + 4, 0);
	ft_strdel(&env->my_environ[env->pwd]);
	env->my_environ[env->pwd] = ft_strdup(getcwd(buff, sizeof(buff)));
	env->my_environ[env->pwd] = ft_strxjoin("PWD=", env->my_environ[env->pwd],
		2);
}
