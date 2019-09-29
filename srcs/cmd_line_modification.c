/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line_modification.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:15:07 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/29 18:34:29 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*cmd_line_modification_2(char *c, char *cmd_e,
		int *len, t_signs s)
{
	(c[s.i] != 0) ? ft_bzero(c + s.i, ft_strlen(c) - s.i) : 0;
	c = (s.w + 1 > *len) ? ft_realloc(c, *len, ft_strlen(c), s.w + 1) : c;
	(s.main != NULL) ? c = ft_strcat(c, s.main) : 0;
	if (cmd_e != NULL)
		c = ft_strcat(c, (s.fl == 3 && *cmd_e == ' ') ? &cmd_e[1] : cmd_e);
	(cmd_e != NULL) ? free(cmd_e) : 0;
	(s.main != NULL) ? free(s.main) : 0;
	return (c);
}
