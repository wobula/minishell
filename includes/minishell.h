/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 15:05:27 by rschramm          #+#    #+#             */
/*   Updated: 2017/03/20 13:27:19 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include "../libft/includes/libft.h"

typedef struct	s_mini
{
	int			home;
	int			pwd;
	int			old_pwd;
	int			pat;
	char		*path;
	char		**my_environ;
}				t_mini;

void			cd_main(t_mini *env, char **split);
char			*find_path(char *path, char *exe);
char			*find_env_path(t_mini *env, char *exe);
void			cd_case_old_pwd(t_mini *env);
void			cd_case_root(t_mini *env, char **split);
void			cd_case_home(t_mini *env, char **split);
void			cd_case_args(t_mini *env, char **split);
void			cd_args(t_mini *env, char **split);
void			cd_none(t_mini *env);
void			cd_main(t_mini *env, char **split);
char			**get_env(char **environ);
void			env_set(t_mini *env, char **split);
void			env_main(t_mini *env, char **split);
int				env_check(char **split);
void			del_old_env(t_mini *env);
char			**env_unset(t_mini *env, char **split);
char			**new_entry(t_mini *env, char **split);
void			existing_entry(t_mini *env, char **split, int index);
void			run_program(t_mini *env, char **split);
int				get_start(char **split);
void			del_split(char **split);
int				get_index(char **environ, char *compare, int size);
char			*trim_last_dir(char *dir);
int				display_env(t_mini *env);

#endif
