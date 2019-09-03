/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:48:27 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/03 13:01:01 by sschmele         ###   ########.fr       */
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

void        *ft_realloc(void *subj, int len_subj, int len_needed)
{
    void	*ptr;

    if (!(ptr = malloc(len_needed)))
	{
		write(2, "No space left\n", 15);
		exit(1);
	}
    if (len_needed > len_subj)
    {
        ft_memcpy(ptr, subj, len_subj);
        ft_bzero(ptr + len_subj, len_needed - len_subj);
    }
    else
        ft_memcpy(ptr, subj, len_needed);
    free(subj);
    return (ptr);
}

void	    get_terminal_width(unsigned int *term)
{
	struct winsize	sz;

	ioctl(1, TIOCGWINSZ, &sz);
    term[0] = sz.ws_col;
    term[1] = sz.ws_row;
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

void		init_all(unsigned int *all)
{
    all[0] = MAX;
    all[1] = 0;
    all[2] = PROMPT;
    all[3] = PROMPT;
    all[4] = 0;
    get_terminal_width(&all[5]);
    all[7] = 0;
    //printf("%d - %d - %d - %d - %d - %d\n", all[0], all[1], all[2], all[3], all[4], all[5]);
}