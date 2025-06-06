/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:51:47 by mikayel           #+#    #+#             */
/*   Updated: 2025/05/27 20:30:16 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_unmatched_quotes(const char *word)
{
	char	quote;

	quote = 0;
	while (*word)
	{
		if ((*word == '\'' || *word == '"') && quote == 0)
			quote = *word;
		else if (*word == quote)
			quote = 0;
		word++;
	}
	return (quote != 0);
}

static bool	word_syntax_check(t_token *tokens, t_token_type last_token_type)
{
	if (check_unmatched_quotes(tokens->value))
	{
		syntax_error("newline");
		return (true);
	}
	else if (last_token_type == TOKEN_PAREN_RIGHT)
	{
		syntax_error(tokens->value);
		return (true);
	}
	return (false);
}

static bool	double_operand_syntax_check(t_token *tokens, 
	t_token_type last_token_type, int *scope_count)
{
	if (last_token_type != TOKEN_WORD && last_token_type != TOKEN_PAREN_RIGHT)
	{
		syntax_error(tokens->value);
		return (true);
	}
	if (tokens->type == TOKEN_PAREN_RIGHT)
	{
		(*scope_count)--;
		if (*scope_count < 0)
        {
            syntax_error(tokens->value);
            return (true);
        }
	}
	return (false);
}

static bool	syntax_error_check_helper(t_token *tokens, t_token_type last_token_type, int *scope_count)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
		{
			if (word_syntax_check(tokens, last_token_type) == true)
				return (true);
		}
		else if (tokens->type == TOKEN_PIPE || tokens->type == TOKEN_AND 
			|| tokens->type == TOKEN_OR || tokens->type == TOKEN_PAREN_RIGHT)
		{
			if (double_operand_syntax_check(tokens, last_token_type, scope_count) == true)
				return (true);
		}
		else if (tokens->type == TOKEN_PAREN_LEFT)
		{
			(*scope_count)++;
			if (last_token_type != TOKEN_PIPE && last_token_type != TOKEN_AND && last_token_type != TOKEN_OR && last_token_type != TOKEN_PAREN_LEFT)
            	return (syntax_error(tokens->value), true);
		}
		last_token_type = tokens->type;
		tokens = tokens->next;
	}
	return (false);
}

bool	syntax_error_check(t_token *tokens)
{
	t_token_type	last_token_type;
	int				scope_count;
    
	scope_count = 0;
	if (tokens->type == TOKEN_PIPE || tokens->type == TOKEN_OR 
		|| tokens->type == TOKEN_AND || tokens->type == TOKEN_PAREN_RIGHT)
		return (syntax_error(tokens->value), true);
	if (tokens->type == TOKEN_PAREN_LEFT)
		scope_count++;
	if (tokens->type == TOKEN_WORD && check_unmatched_quotes(tokens->value))
		return (syntax_error("newline"), true);
	last_token_type = tokens->type;
	tokens = tokens->next;
	if (syntax_error_check_helper(tokens, last_token_type, &scope_count))
		return (true);
	if (scope_count > 0)
		return (syntax_error("newline"), true);
	return (false);
}