/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 11:50:11 by sschmele          #+#    #+#             */
/*   Updated: 2019/08/25 13:54:14 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int         check_command(char **cmd)
{
    if (ft_strcmp(cmd[0], "exit") == 0)
        return (1);
    else
        ft_putendl("COMMAND_CHECK");
    return (0);
}