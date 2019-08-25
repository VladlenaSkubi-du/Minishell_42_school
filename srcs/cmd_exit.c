/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:29:35 by sschmele          #+#    #+#             */
/*   Updated: 2019/08/25 18:16:16 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void        cmd_exit(char *cmd)
{
    ft_putendl("exit");
    reset_canonical_input();
    free(cmd);
    exit(1);
}