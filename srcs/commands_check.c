/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 11:50:11 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/03 13:04:42 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void         check_command(char *cmd)
{
    ft_putendl(cmd);
    (ft_strncmp(cmd, "exit", 4) == 0) ? cmd_exit(cmd) : 0;
}