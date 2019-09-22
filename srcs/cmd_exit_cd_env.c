/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit_cd_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:59:04 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/22 19:55:38 by sschmele         ###   ########.fr       */
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
**
**@s exists because of the norm and consists of (used here):
**s.pwd - nb of environ string, where "PWD=" parameter lies;
**s.old - nb of environ string, where "OLDPWD=" parameter lies;
**s.j - is counter in the environ - counter of lines;
**s.main - environ value (after '=' of parameter) we need to change;
**s.len and s.len1 are size_t and needed for returned by ft_strlen values;
**s.w is used just as a temporal variable.
*/

void			cmd_cd(char *cmd, int j)
{
	extern char	**environ;
	t_signs		s;

	s.pwd = 0;
	while (environ[s.pwd] && ft_strncmp(environ[s.pwd], "PWD=", 4) != 0)
		s.pwd++;
	(environ[s.pwd] == NULL) ? cmd_setenv("setenv PWD=", 0) : 0;
	s.old = 0;
	while (environ[s.old] && ft_strncmp(environ[s.old], "OLDPWD=", 7) != 0)
		s.old++;
	if (cmd[2] == '\0')
	{
		s.j = 0;
		while (environ[s.j] && ft_strncmp(environ[s.j], "HOME=", 5) != 0)
			s.j++;
		if (environ[s.j] == NULL || environ[s.j][5] == '\0')
		{
			ft_putendl_fd("minishell: cd: HOME not set.", 2);
			return ;
		}
		s.main = &environ[s.j][5];
	}
	else if (!(cmd[3] == '\0') && !(cmd[3] == '-' && cmd[4] == '\0'))
		s.main = &cmd[3];
	change_dir(cmd, s);
}

void			change_dir(char *cmd, t_signs s)
{
	extern char	**environ;
	char		**ptr;

	if (cmd[2] && (cmd[3] == '-' && cmd[4] == '\0'))
	{
		if (environ[s.old] == NULL || environ[s.old][7] == '\0')
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set.", 2);
			return ;
		}
		s.main = ft_strdup(&environ[s.old][7]);
		ft_putendl(s.main);
	}
	if ((s.w = chdir(s.main)) < 0)
	{
		ft_putstr_fd("minishell: cd: No such file or directory: ", 2);
		ft_putendl_fd(s.main, 2);
		return ;
	}
	if (environ[s.old] == NULL)
		cmd_setenv("setenv OLDPWD=", 0);
	change_environ(cmd, s);
}

void			change_environ(char *cmd, t_signs s)
{
	extern char	**environ;

	s.len = 0;
	if (environ[s.old][7] != '\0')
		ft_bzero(&environ[s.old][7], (s.len = ft_strlen(&environ[s.old][7])));
	if (s.len < (s.len1 = ft_strlen(&environ[s.pwd][4])))
		environ[s.old] = ft_realloc(environ[s.old], 7, 7, s.len1 + 8);
	ft_strcpy(&environ[s.old][7], &environ[s.pwd][4]);
	(environ[s.pwd][4] != '\0') ?
		ft_bzero(&environ[s.pwd][4],
			(s.len = ft_strlen(&environ[s.pwd][4]))) : 0;
	if (s.len < (s.len1 = ft_strlen(s.main)))
		environ[s.pwd] = ft_realloc(environ[s.pwd], 4, 4, s.len1 + 5);
	ft_strcpy(&environ[s.pwd][4], s.main);
	(cmd[2] && (cmd[3] == '-' && cmd[4] == '\0')) ? free(s.main) : 0;
}
