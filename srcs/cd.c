/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 11:39:00 by rschramm          #+#    #+#             */
/*   Updated: 2017/03/23 09:28:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_case_old_pwd(t_mini *env)
{
	char buff[4000];

	chdir(env->my_environ[env->old_pwd] + 7);
	ft_strdel(&env->my_environ[env->old_pwd]);
	env->my_environ[env->old_pwd] = ft_strxjoin("OLDPWD=",
		env->my_environ[env->pwd] + 4, 0);
	ft_strdel(&env->my_environ[env->pwd]);
	env->my_environ[env->pwd] = ft_strdup(getcwd(buff, sizeof(buff)));
	env->my_environ[env->pwd] = ft_strxjoin("PWD=", env->my_environ[env->pwd], 2);
}

void	cd_case_args(t_mini *env, char **split)
{
	int		arg_start;
	char	buff[4000];

	arg_start = get_start(split);
	chdir(split[arg_start]);
	ft_strdel(&env->my_environ[env->old_pwd]);
	env->my_environ[env->old_pwd] = ft_strxjoin("OLDPWD=",
		env->my_environ[env->pwd] + 4, 0);
	ft_strdel(&env->my_environ[env->pwd]);
	env->my_environ[env->pwd] = ft_strdup(getcwd(buff, sizeof(buff)));
	env->my_environ[env->pwd] = ft_strxjoin("PWD=",
		env->my_environ[env->pwd], 2);
}

void	cd_args(t_mini *env, char **split)
{
	if (split[1][0] == '/')
		cd_case_root(env, split);
	else if ((split[1][0] == '-' && split[1][1] == 'L') ||
		split[1][0] == '~')
		cd_case_home(env, split);
	else if (split[1][0] == '-' && split[1][1] == '\0')
		cd_case_old_pwd(env);
	else
		cd_case_args(env, split);
}

void	cd_main(t_mini *env, char **split)
{
	if (split[1])
	{
		if (split[1])
			cd_args(env, split);
	}
	else
		cd_case_home(env, split);
}
