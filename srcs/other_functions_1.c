/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_functions_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:48:27 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/22 19:26:13 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		*ft_xmalloc(size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
	{
		write(2, "No space left\n", 15);
		exit(1);
	}
	ft_bzero(ptr, size);
	return (ptr);
}

void		*ft_realloc(void *subj, size_t len_subj,
	size_t len, size_t len_needed)
{
	void	*ptr;

	if (!(ptr = malloc(len_needed)))
	{
		write(2, "No space left\n", 15);
		exit(1);
	}
	if (len_needed > len_subj)
	{
		ft_memcpy(ptr, subj, len);
		ft_bzero(ptr + len, len_needed - len);
	}
	else
		ft_memcpy(ptr, subj, len_needed);
	free(subj);
	return (ptr);
}

void		get_terminal_width(size_t *term)
{
	struct winsize	sz;

	ioctl(1, TIOCGWINSZ, &sz);
	term[0] = sz.ws_col;
	term[1] = sz.ws_row;
}

int			count_env(void)
{
	extern char		**environ;
	int				i;

	i = 0;
	while (environ[i])
		i++;
	return (i);
}

/*
**The structure all consists of:
**all[0] = maximal command string size;
**all[1] = signal-flags;
**all[2] = counter of the cursor: how much in input and deleted -
**printable symbols in fact;
**all[3] = counter of the cursor: to input or delete
**in the final command-string;
**all[4] = nb of strings printed;
**all[5] = terminal width;
**all[6] = terminal rows number;
**all[7] = usable in different functions;
*/

void		init_all(size_t *all)
{
	all[0] = MAX;
	all[1] = 0;
	all[2] = PROMPT;
	all[3] = PROMPT;
	all[4] = 0;
	get_terminal_width(&all[5]);
	all[7] = 0;
}
