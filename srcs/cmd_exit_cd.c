/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:59:04 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/14 17:52:16 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		cmd_exit(char *cmd)
{
	ft_putendl("exit");
	reset_canonical_input();
	free(cmd);
	exit(1);
}

void		cmd_cd(char *cmd, int flag)
{
	flag = 0;
	ft_putendl(cmd);
}
