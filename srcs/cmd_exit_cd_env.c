/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit_cd_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:59:04 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/20 20:36:02 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**@j came to all these functions as "flag" meaning we have flags in fucntions
**and use the parameter for that. But in minishell commands env, setenv and
**unsetenv do not have flags. Therefore, not to declare new parameters,
**this one is reused. That is a bad practise but excuse me.
*/

void			cmd_env(char *cmd, int j)
{
	extern char	**environ;

	j = 0;
	while (environ[j])
		ft_putendl(environ[j++]);
}

void			cmd_exit(char *cmd)
{
	ft_putendl("exit");
	reset_canonical_input();
	free(cmd);
	exit(1);
}

/*
**The following situations are possible:
**"cd\0" and HOME is undefined - nothing happends;
**"cd\0" and HOME is defined - change;
**"cd -" - change to the old direction if it is defined;
**"cd [path]" - change to the path direction
*/

void			cmd_cd(char *cmd, int j)
{
	extern char	**environ;
	int			i;
	char		*old;
	char		*pwd;
	char		*home;

	i = 3;
	j = 0;
	while (ft_strncmp(environ[j], "OLDPWD", 6) != 0)
		j++;
	old = &environ[j][0];
	j = 0;
	while (ft_strncmp(environ[j], "PWD", 3) != 0)
		j++;
	pwd = &environ[j][0];
	j = 0;
	if (cmd[i] == '\0')
	{
		while (ft_strncmp(environ[j], "HOME", 4) != 0)
			j++;
		home = &environ[j][0];
		if (home[5] == '\0')
			return ;
	}
	change_dir(cmd, old, pwd, home);
}

void			change_dir(char *cmd, char *old, char *pwd, char *home)
{
	extern char	**environ;
	int			len_1;
	int			len_2;
	char		*what;

	if (cmd[3] == '\0')
		what = &home[5];
	else if (cmd[3] == '-' && cmd[3 + 1] == '\0')
	{
		what = ft_strdup(&old[7]);
		ft_putendl(what);
	}
	else
		what = &cmd[3];
	if ((len_1 = chdir(what)) < 0)
	{
		ft_putendl("cmd_cd: no such file or directory: ");
		ft_putendl(what);
		return ;
	}
	ft_bzero(&old[7], (len_1 = ft_strlen(&old[7])));
	(len_1 < (len_2 = ft_strlen(&pwd[4]))) ?
		old = ft_realloc(old, len_1, len_2 + 1) : 0;
	ft_strcpy(&old[7], &pwd[4]);
	ft_bzero(&pwd[4], (len_1 = ft_strlen(&pwd[4])));
	(len_1 < (len_2 = ft_strlen(what))) ?
		pwd = ft_realloc(pwd, len_1, len_2 + 1) : 0;
	ft_strcpy(&pwd[4], what);
	(cmd[3] == '-' && cmd[3 + 1] == '\0') ? free(what) : 0;
}
