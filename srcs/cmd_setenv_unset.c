/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_setenv_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:09:42 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/16 20:08:10 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**There are four cases for setenv programmed:
**setenv with no arguments - shows cmd_env output;
**setenv FOO - argument without '=' - error message;
**setenv FOO= - argument with '=' but no value;
**setenv FOO=foo - argument with '=' with value;
*/

void				cmd_setenv(char *cmd, int j)
{
	char			**tmp;
	char			**ptr;
	t_signs			s;

	if (cmd[6] == '\0')
	{
		cmd_env(cmd, 0);
		return ;
	}
	s.i = 7;
	if (ft_strchr(&cmd[s.i], '=') == NULL)
	{
		write(STDERR_FILENO,
			"setenv: Environment variable can't be altered\n", 47);
		return ;
	}
	tmp = ft_strsplit(&cmd[s.i], ' ');
	s.i = 0;
	s.j = -1;
	while (tmp[s.i])
		cmd_setenv_environ_1(tmp[s.i++], s, ptr);
	ft_arrdel(tmp);
}

void				cmd_setenv_environ_1(char *name, t_signs s, char **ptr)
{
	extern char		**environ;

	s.i = 0;
	while (name[s.i] != '=' && name[s.i])
		s.i++;
	while (environ[++s.j])
		if (ft_strncmp(environ[s.j], name, s.i) == 0
				&& environ[s.j][s.i] == '=')
			break ;
	if (environ[s.j] != NULL)
		environ[s.j] = cmd_setenv_environ_2(name, s.i, environ[s.j]);
	else if (environ[s.j] == NULL)
	{
		s.i = -1;
		ptr = (char**)ft_xmalloc((s.j + 2) * (sizeof(char*)));
		while (++s.i < s.j)
			ptr[s.i] = environ[s.i];
		ptr[s.i] = ft_strdup(name);
		ptr[s.i + 1] = NULL;
		free(environ);
		environ = ptr;
	}
}

char				*cmd_setenv_environ_2(char *name, int i, char *env)
{
	int				len;

	if (name[i + 1] == '\0')
		ft_bzero(&env[i + 1], ft_strlen(env - i - 1)); //DOES NOT WORK
	else
	{
		len = ft_strlen(name);
		if (ft_strlen(env) < len)
			env = ft_realloc(env, ft_strlen(env), len + 1);
		ft_strcpy(&env[i + 1], &name[i + 1]);
	}
	return (env);
}

void				cmd_unsetenv(char *cmd, int j)
{
	extern char		**environ;
	char			**tmp;
	char			**ptr;
	t_signs			s;

	if (cmd[8] == '\0')
	{
		write(STDERR_FILENO,
			"unsetenv: Too few arguments.\n", 30);
		return ;
	}
	s.i = 8;
	tmp = ft_strsplit(&cmd[s.i], ' ');
	s.i = 0;
	s.j = -1;
	while (tmp[s.i])
		cmd_unsetenv_environ(tmp[s.i++], s, ptr);
	ft_arrdel(tmp);
}

void				cmd_unsetenv_environ(char *name, t_signs s, char **ptr)
{
	extern char		**environ;

	s.i = 0;
	while (name[s.i])
		s.i++;
	while (environ[++s.j])
		if (ft_strncmp(environ[s.j], name, s.i) == 0 //посмотреть функцию strnequ
				&& environ[s.j][s.i] == '=')
			break ;
	if (environ[s.j] != NULL)
	{
		free(environ[s.j]);
		s.w = s.j;
		while (environ[++s.j])
			;
		s.i = -1;
		ptr = (char**)ft_xmalloc((s.j - 1) * (sizeof(char*)));
		while (++s.i < s.w)
			ptr[s.i] = environ[s.i];
		while (++s.i < s.j)
			ptr[s.i] = environ[s.i];
		ptr[s.i] = NULL;
		free(environ);
		environ = ptr;
	}
}
