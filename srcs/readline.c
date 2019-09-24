/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 11:39:51 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/24 17:10:30 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Here we go further to the analysis of the ready cmd-line or come back to the
**main-fucntion and print prompt.
*/

int					nl_signals(char c, char *cmd, size_t *all)
{
	char			*ptr;
	char			*fin;

	help_nl_signal(all, c);
	if ((c == '\n' || c == 10 || c == 13) && !(all[1] & FL_NL))
	{
		reset_canonical_input();
		fin = ft_strdup(cmd);
		free(cmd);
		ptr = ft_strtrim(fin);
		free(fin);
		if (ptr[0] == '\0')
		{
			free(ptr);
			return (1);
		}
		if ((cmd = ptr) == ptr && all[1] & FL_SCMD)
			many_commands(cmd);
		else
			cmd = check_command(cmd, ft_strlen(cmd));
	}
	free(cmd);
	return (1);
}

/*
**Here we print and add a printable symble to the command-line.
*/

char				*printable_parce(char c, char *cmd, size_t *all)
{
	if (all[3] > all[2])
	{
		while (all[2] != all[3])
			cmd = str_add_symbol(cmd, ' ', all);
	}
	(all[2] <= all[3]) ? write(STDOUT_FILENO, &c, 1) : 0;
	cmd = str_add_symbol(cmd, c, all);
	all[1] = (c == ';') ? all[1] |= FL_SCMD : all[1];
	return (cmd);
}

/*
**Here we react to a "<" and ">" signal.
*/

void				esc_leftright(char c, size_t *all)
{
	(c == 91 && (all[1] & FL_ESC)) ? all[1] |= FL_OSQBRK : 0;
	if ((c == 'D' || c == 'B') && (all[1] & FL_ESC) &&
		(all[1] & FL_OSQBRK) && all[3] > PROMPT)
	{
		all[3]--;
		write(STDOUT_FILENO, "\033[D", 3);
	}
	else if ((c == 'C' || c == 'A') && (all[1] & FL_ESC) &&
		(all[1] & FL_OSQBRK) && all[3] < all[5] - 1)
	{
		all[3]++;
		write(STDOUT_FILENO, "\033[C", 3);
	}
}

/*
**Here we print ' ' instead of the printable symbol
**and delete a printable symble from the command-line.
*/

char				*del_symbol(char *cmd, size_t *all)
{
	all[3]--;
	write(STDOUT_FILENO, "\033[D \033[D", 7);
	cmd = str_del_symbol(cmd, all);
	return (cmd);
}

/*
**We read one symbol input by the user, check the following:
**"^D" signal -> function cmd_exit;
**"^C" signal or the command starts with # or : -> function
**nl_signals without processing the command, just new prompt printed;
**"^J" or "^M" or "Enter" signal -> function nl_signals with
**further command processing starting from check_command function;
**">" and "<" signals but only within one-line-command;
**"Delete" signal with deleting from the cmd-line;
**Printing of printable symbols with writing to the cmd-line.
**
**FLAGS in all[1]:
**FL_NL - next line without command-line analysis;
**FL_SCMD - there are several commands
**FL_ESC - there was '\033' detected;
**FL_OSQBRK - there was an open square bracket '['.
**
**The main reactions are learned from bash-shell.
*/

int					readline(void)
{
	char			*cmd;
	size_t			all[8];
	unsigned char	c;

	init_all(all);
	cmd = (char*)ft_xmalloc(all[0]);
	while (1)
	{
		read(STDIN_FILENO, &c, 1);
		(c == 4 && !cmd[0]) ? cmd_exit(cmd) : 0;
		if (c == 3 || c == 10 || c == 13 || c == '\n')
			return (nl_signals(c, cmd, all));
		if (ft_isprint(c) && !(all[1] & FL_ESC))
			cmd = printable_parce(c, cmd, all);
		(c == '\033') ? all[1] |= FL_ESC : 0;
		(all[1] & FL_ESC) ? esc_leftright(c, all) : 0;
		((c == 'D' || c == 'C' || c == 'A' || c == 'B') &&
			(all[1] & FL_ESC)) ? all[1] ^= FL_ESC : 0;
		all[4] = (all[2] >= all[5]) ? all[2] / all[5] : 0;
		(c == 127 && all[2] > 0 && all[3] > PROMPT) ?
			cmd = del_symbol(cmd, all) : 0;
		if (ft_isprint(c) == 0)
			;
	}
	return (0);
}
