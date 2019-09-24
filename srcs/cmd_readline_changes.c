/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_readline_changes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 13:38:26 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/24 21:20:09 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
**If the command consists of 2 or more lines and we try to send an nl-signal
**from the center of the cmd-line, prompt does not separate it but finds the
**end of the cmd-line
*/

void		help_nl_signal(size_t *all, char c)
{
	if (all[4] && all[3] != all[2])
	{
		while (all[3] != all[2])
		{
			write(STDOUT_FILENO, "\033[C", 3);
			all[3]++;
		}
	}
	ft_putchar('\n');
	if (c == 3 && !(all[1] & FL_NL))
		reset_canonical_input();
}

/*
**If we print a new symbol or delete, the whole line is moved - it should
**be displayed in shell
*/

char		*help_str_change(char *cmd, char *swap, int point, char add)
{
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(swap);
	if (add > 0)
	{
		while (swap[++i])
			cmd[point + 1 + i] = swap[i];
		write(STDOUT_FILENO, &add, 1);
		write(STDOUT_FILENO, swap, len);
		while (len--)
			write(STDOUT_FILENO, "\033[D", 3);
	}
	else
	{
		while (swap[++i])
			cmd[point + i] = swap[i];
		cmd[point + i] = '\0';
		write(STDOUT_FILENO, swap, len);
		write(STDOUT_FILENO, " ", 1);
		while (len-- >= 0)
			write(STDOUT_FILENO, "\033[D", 3);
	}
	return (cmd);
}

/*
**Here we add one printable symbol to the command-line.
**There are three possible situations:
** | | is a cell;
** > is a PROMPT
** M is MAX - command line is already malloced to the nb of MAX symbols;
** fact is (all[2] - PROMPT) - the factual line printed that should be saved to
** the command line string;
** point is (all[3] - PROMPT) - the counter after the "< >" usage from keybord
**
** 1) | | >| | | | | |M '\0' | - we start to print to the beginning of the line
**          ^ fact = point = PROMPT
**
** 2) | | >| | | | | |M '\0 | | | | | | - we used ">" and want to start printing
**          ^ fact = PROMPT  ^ point
** from the center of the terminal line
** 3) | | >| a| b| c| d| |M '\0'| | | | | | - we have text, used "<" and want
**           ^ point    ^ fact (4 symbles in command line)
** to start printing from the center or beginning of the command line
*/

char		*str_add_symbol(char *cmd, char add, size_t *all)
{
	size_t	fact;
	size_t	point;
	char	*swap;

	fact = all[2] - PROMPT;
	point = all[3] - PROMPT;
	if (fact >= all[0] - 1)
	{
		cmd = ft_realloc(cmd, all[0], ft_strlen(cmd), all[0] * 2);
		all[0] *= 2;
	}
	if (fact > point)
	{
		swap = ft_strdup(cmd + point);
		cmd[point] = add;
		cmd = help_str_change(cmd, swap, point, add);
		all[3]++;
		free(swap);
	}
	(fact == point) ? all[3]++ : 0;
	(fact <= point) ? cmd[fact] = add : 0;
	all[2]++;
	return (cmd);
}

/*
**Here we delete one printable symbol from the command-line.
**There are three possible situations:
** | | is a cell;
** > is a PROMPT
** M is MAX - command line is already malloced to the nb of MAX symbols;
** fact is (all[2] - PROMPT) - the factual line printed that should be saved to
** the command line string;
** point is (all[3] - PROMPT) - the counter after the "< >" usage from keybord
**
** 1) | | >| a| b| c| d| |M '\0' | - we have text and start to delete from
**                      ^ fact = point = PROMPT
** the end of the line
** 2) | | >| a| b| c| d| |M '\0 | | | | | | - we have text, used "<" and want
**                      ^ fact       ^ point
** to start deleting from the center of the terminal line
** 3) | | >| a| b| c| d| |M '\0'| | | | | | - we have text, used "<" and want
**              ^ point ^ fact
** to start deleting from the center of the command line
*/

char		*str_del_symbol(char *cmd, size_t *all)
{
	size_t	fact;
	size_t	point;
	char	*swap;

	fact = all[2] - PROMPT;
	point = all[3] - PROMPT;
	if (fact == 0)
		return (cmd);
	if (fact < all[0] / 2)
	{
		cmd = ft_realloc(cmd, all[0], ft_strlen(cmd), all[0] / 2);
		all[0] /= 2;
	}
	(fact - 1 == point) ? cmd[--fact] = '\0' : 0;
	if (fact - 1 > point)
	{
		swap = ft_strdup(cmd + point + 1);
		cmd = help_str_change(cmd, swap, point, -1);
		free(swap);
	}
	all[2]--;
	return (cmd);
}
