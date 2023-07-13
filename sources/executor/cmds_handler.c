/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:01:51 by szerisen          #+#    #+#             */
/*   Updated: 2023/07/13 15:54:18 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_split_str(char **split_str, char *new_str);
char	**resplit_str(char **double_arr);

/*
The function find_cmd is responsible for finding
and executing a command. It takes two parameters: a t_cmds struct
pointer named cmd and a t_utils struct pointer named
utils. The function attempts to execute the command specified
by cmd->str[0] by searching for the command in the system's
 paths. It first checks if the command exists using the
access function with F_OK parameter. If the command is
found, execve is called to replace the current process with
the specified command. If the command is not found, the
function returns a value indicating that the command was not found.
*/
int	find_cmd(t_cmds *cmd, t_utils *utils)
{
	int		i;
	char	*mycmd;

	i = 0;
	while (utils->paths && utils->paths[i])
	{
		mycmd = ft_strjoin(utils->paths[i], cmd->command);
		if (!access(mycmd, F_OK))
			execve(mycmd, cmd->args, utils->envp);
		free(mycmd);
		i++;
	}
	return (cmd_not_found(cmd->command));
}

/*Additional Function command not found is added in error_handling.c*/
int	cmd_not_found(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (127);
}
/*
The function handle_cmd is responsible for handling
 a command. It takes two parameters: a t_cmds struct
pointer named cmd and a t_utils struct pointer named
utils. Inside the function, it performs the following actions:
It checks if there are any redirections specified by
calling check_redirections if cmd->redirections is not NULL.
If the command is a built-in command (indicated by
cmd->builtin not being NULL), it calls the corresponding built-in
command function and exits with the return code of the
 command. If the command is not a built-in command and the command
string is not empty, it calls the find_cmd function to
find and execute the command.
Finally, it exits with the exit code returned by find_cmd
or 0 if no command was executed.
*/

void	handle_cmd(t_cmds *cmd, t_utils *utils)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->redirections && check_redirections(cmd))
	{
		reset_utils(utils);
		free_utils(utils);
		exit(1);
	}
	if (cmd->builtin != NULL)
	{
		exit_code = cmd->builtin(utils, cmd);
		reset_utils(utils);
		free_utils(utils);
		exit(exit_code);
	}
	else if (cmd->command)
		exit_code = find_cmd(cmd, utils);
	reset_utils(utils);
	free_utils(utils);
	exit(exit_code);
}

/*
if the command has a previous command (cmd->prev is not NULL),
 it uses dup2 function to duplicate the input file descriptor
(fd_in) to the standard input file descriptor (STDIN_FILENO).
If there is an issue with the duplication, it calls the
ft_error function with error code 4 and the utils struc
*/
/* It closes the read end of the pipe (end[0]). */
/*
If the command has a next command (cmd->next is not NULL),
it uses dup2 function to duplicate the write end of the pipe (end[1])
to the standard output file descriptor (STDOUT_FILENO). If
there is an issue with the duplication, it calls the ft_error
function with error code 4 and the utils struct.
// It closes the write end of the pipe (end[1]).
// If the command has a previous command, it closes the
input file descriptor (fd_in).
*/
void	dup_cmd(t_cmds *cmd, t_utils *utils, int end[2], int fd_in)
{
	if (cmd->prev && dup2(fd_in, STDIN_FILENO) < 0)
		ft_error(4, utils);
	close(end[0]);
	if (cmd->next && dup2(end[1], STDOUT_FILENO) < 0)
		ft_error(4, utils);
	close(end[1]);
	if (cmd->prev)
		close(fd_in);
	handle_cmd(cmd, utils);
}

/*
The function single_cmd is responsible for handling a single
command. It takes two parameters: a t_cmds struct pointer named cmd and
a t_utils struct pointer named utils. Inside the function, it
performs the following actions:
It calls call_expander to expand any variables or perform
command substitution in the command string.
If the command is a built-in command (specifically mini_cd,
mini_exit, mini_export, or mini_unset), it calls the
corresponding built-in command

WIFEXITED is a macro that checks whether a child
process has exited normally.
status is a variable that likely holds
the status information of a child process.
The WEXITSTATUS macro retrieves the exit
status of a child process.
*/
void	single_cmd(t_cmds *cmd, t_utils *utils)
{
	int	pid;
	int	status;

	if (cmd->builtin == m_cd || cmd->builtin == m_exit
		|| cmd->builtin == m_export || cmd->builtin == m_unset)
	{
		g_global.error_code = cmd->builtin(utils, cmd);
		return ;
	}
	send_heredoc(utils, cmd);
	pid = fork();
	if (pid < 0)
		ft_error(5, utils);
	else if (pid == 0)
		handle_cmd(cmd, utils);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_global.error_code = WEXITSTATUS(status);
}
