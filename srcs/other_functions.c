/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:48:27 by sschmele          #+#    #+#             */
/*   Updated: 2019/08/28 17:30:21 by sschmele         ###   ########.fr       */
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
    ft_memcpy(ptr, subj, len_subj);
    ft_bzero(ptr + len_subj, len_needed - len_subj);
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