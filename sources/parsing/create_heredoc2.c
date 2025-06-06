/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:35:37 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/06 22:56:12 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void set_echoctl(bool enable)
// {
// 	struct termios term;

// 	if (tcgetattr(STDIN_FILENO, &term) == -1)
// 		return;
// 	if (enable)
// 		term.c_lflag |= ECHOCTL;
// 	else
// 		term.c_lflag &= ~ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }

void do_child_process(const char *delimiter, const char *filename)
{
	signal(SIGINT, SIG_DFL);
	// setup_signals_child();
	signal(SIGQUIT, SIG_IGN);
	exit(write_heredoc_to_file(delimiter, filename));
}

int	run_heredoc_process(const char *delimiter, const char *filename)
{
	pid_t	process_id;
	int		status;

	setup_signals_parent_exec();
	process_id = fork();
	if (process_id == -1)
		return (EXIT_FAILURE);
	if (process_id == 0)
		do_child_process(delimiter, filename);
	else
	{
		waitpid(process_id, &status, 0);
		setup_signals();
		if (WIFSIGNALED(status))
		{
			signal_status = WTERMSIG(status);
			return (WTERMSIG(status) + 128);
		}
		if (WIFEXITED(status))
			return (WEXITSTATUS(status)); // ✅ Ctrl+D treated as valid
	}
	return (EXIT_FAILURE);
}

int	add_heredoc_file(t_shell *shell, const char *filename)
{
	t_heredoc	*new_node = malloc(sizeof(t_heredoc));
	if (!new_node)
		return (perror("malloc"), 1);
	new_node->filename = strdup(filename);
	if (!new_node->filename)
	{
		free(new_node);
		return (perror("strdup"), 1);
	}
	new_node->next = shell->heredocs;
	shell->heredocs = new_node;
	return (0);
}

void	cleanup_heredocs(t_shell *shell)
{
	t_heredoc	*tmp;

	while (shell->heredocs)
	{
		tmp = shell->heredocs;
		shell->heredocs = shell->heredocs->next;
		unlink(tmp->filename);
		free(tmp->filename);
		free(tmp);
	}
	shell->heredocs = NULL;
}