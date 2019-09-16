/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env_set_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:09:42 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/13 16:10:44 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				cmd_env(char *cmd, int flag)
{
	int				i;
	extern char		**environ;


	i = 0;
	// if (special_signs_check(cmd + i) == -1)
	// 	return (-1);
	while (environ[i])
		ft_putendl(environ[i++]);
}

void				cmd_setenv(char *cmd, int flag)
{
	ft_putendl(cmd);
}

void				cmd_unsetenv(char *cmd, int flag)
{
	ft_putendl(cmd);
}