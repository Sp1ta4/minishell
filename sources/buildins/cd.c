/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:42:32 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/02 19:23:22 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_home(char *name, t_ht *env)
{
	char *temp_path;
	
	temp_path = ht_get(env, "HOME");
	if (!temp_path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (EXIT_FAILURE);
	}
	if (ht_add(env, "OLDPWD", ht_get(env, "PWD")) == false)
		return (handle_error(name));
	if (ht_add(env, "PWD", temp_path) == false)
		return (handle_error(name));
	return (0);
}

int	cd_oldpwd(char *name, t_ht *env)
{
	char *temp_path;
	
	temp_path = ht_get(env, "OLDPWD");
	if (!temp_path)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (EXIT_FAILURE);
	}
	if (chdir(temp_path) == -1)
		return (handle_error(name));
	ft_putendl_fd(temp_path, 2);
	if (ht_add(env, "OLDPWD", ht_get(env, "PWD")) == false)
		return (handle_error(name));
	temp_path = getcwd(NULL, 0);
	if (!temp_path)
		return (handle_error(name));
	if (ht_add(env, "PWD", temp_path) == false)
	{
		free(temp_path);
		return (handle_error(name));
	}
	free(temp_path);
	return (0);
}

int	cd_directory(char *name, char *dir, t_ht *env)
{
	char *temp_path;
	
	if (chdir(dir) == -1)
		return (handle_error(name));
	if (ht_add(env, "OLDPWD", ht_get(env, "PWD")) == false)
		return (handle_error(name));
	temp_path = getcwd(NULL, 0);
	if (!temp_path)
		return (handle_error(name));
	if (ht_add(env, "PWD", temp_path) == false)
	{
		free(temp_path);
		return (handle_error(name));
	}
	free(temp_path);
	return (0);
}

int ft_cd(t_cmd *cmd, t_ht *env)
{
    if (cmd->args[1])
    {
		if (cmd->args[2])
		{
			ft_putstr_fd("minishell: cd: too many arguments\n", 2);
			return (EXIT_FAILURE);
		}
		if (ft_strcmp(cmd->args[1], "-") == 0)
			return (cd_oldpwd(cmd->name, env));
		return (cd_directory(cmd->name, cmd->args[1], env));
	}
	return (cd_home(cmd->name, env));
}