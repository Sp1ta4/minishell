/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:17:06 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/07 12:48:13 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool     has_n_flag(char *s)
{
	if (!s || !(*s))
		return (false);
	if (*s == '-')
		++s;
	while (*s && *s == 'n')
		++s;
	if (*s)
		return (false);
	return (true);
}

int     ft_echo(t_cmd *cmd)
{
	bool    has_newline;
	int             i;

	i = 1;
	has_newline = has_n_flag(cmd->args[i]);
	if (has_newline)
		++i;
	if (cmd->args[i])
		if (printf("%s", cmd->args[i++]) == -1)
			return (handle_error("echo: write error"));
	while (cmd->args[i])
		if (printf(" %s", cmd->args[i++]) == -1)
			return (handle_error("echo: write error"));
	if (!has_newline)
		if (printf("\n") == -1)
			return (handle_error("echo: write error"));
	return (0);
}