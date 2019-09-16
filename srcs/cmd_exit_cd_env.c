/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit_cd_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:59:04 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/16 19:47:24 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**@j came to all these functions as "flag" meaning we have flags in fucntions
**and use the parameter for that. But in minishell commands env, setenv and
**unsetenv do not have flags. Therefore, not to declare new parameters,
**this one is reused. That is a bad practise but excuse me.
*/

void		cmd_env(char *cmd, int j)
{
	extern char		**environ;

	j = 0;
	while (environ[j])
		ft_putendl(environ[j++]);
}

void		cmd_exit(char *cmd)
{
	ft_putendl("exit");
	reset_canonical_input();
	free(cmd);
	exit(1);
}

void		cmd_cd(char *cmd, int flag)
{
	int		i;

	i = 3;

	ft_putendl(cmd);
}
