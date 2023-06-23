/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:10:31 by szerisen          #+#    #+#             */
/*   Updated: 2023/06/23 18:24:43 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

/*
call_expander: This function is responsible for calling the expander and expander_str functions to expand variables
and perform shell expansions on the command and its redirections. It takes a t_utils pointer and a t_cmds pointer as
arguments. It first expands the command's string using the expander function. Then, it iterates over the command's
redirections and expands each redirection's string using the expander_str function. Finally, it returns the modified command.
*/
/* t_cmds	*call_expander(t_utils *utils, t_cmds *cmd)
{
	t_lexer	*start;

	cmd->str = expander(utils, cmd->str);
	start = cmd->redirections;
	while (cmd->redirections)
	{
		if (cmd->redirections->token != LESS_LESS)
			cmd->redirections->str
				= expander_str(utils, cmd->redirections->str);
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (cmd);
} */
/*
pipe_wait: This function waits for child processes to complete execution when multiple pipes are used. It takes an
array of process IDs (pid) and the number of processes (amount) as arguments. It iterates over the array of process
IDs and waits for each child process to exit using waitpid. After all child processes have exited, it checks the exit
status using WIFEXITED and sets the global g_global.error_num to the exit status of the last child process. It returns EXIT_SUCCESS.
*/
int	pipe_wait(int *pid, int amount)
{
	int	i;
	int	status;

	i = 0;
	while (i < amount)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		g_global.error_code = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}
/*
ft_fork: This function is responsible for forking a child process and executing the command. It takes a t_utils pointer, an array of
pipe file descriptors (end), the input file descriptor (fd_in), and a t_cmds pointer as arguments. It first checks if the utils->reset
flag is set and resets the static variable i if necessary. Then, it forks a child process using fork and assigns the process ID to
utils->pid[i]. If the fork fails, it calls ft_error to handle the error. In the child process, it calls the dup_cmd function to
set up the necessary file descriptors and execute the command. Finally, it increments i and returns EXIT_SUCCESS.
*/
int	ft_fork(t_utils *utils, int end[2], int fd_in, t_cmds *cmd)
{
	static int	i = 0;

	if (utils->reset == true)
	{
		i = 0;
		utils->reset = false;
	}
	utils->pid[i] = fork();
	if (utils->pid[i] < 0)
		ft_error(5, utils);
	if (utils->pid[i] == 0)
		dup_cmd(cmd, utils, end, fd_in);
	i++;
	return (EXIT_SUCCESS);
}
/*
check_fd_heredoc: This function checks the file descriptor for input redirection. It takes a t_utils pointer,
an array of pipe file descriptors (end), and a t_cmds pointer as arguments. If the utils->heredoc flag is set,
indicating the use of a here document, it closes the read end of the pipe (end[0]), opens the here document
file in read-only mode, and returns the file descriptor. Otherwise, it returns end[0], which represents the
standard input file descriptor.
*/
int	check_fd_heredoc(t_utils *utils, int end[2], t_cmds *cmd)
{
	int	fd_in;

	if (utils->heredoc)
	{
		close(end[0]);
		fd_in = open(cmd->hd_file_name, O_RDONLY);
	}
	else
		fd_in = end[0];
	return (fd_in);
}

// This will be called if there are more than one command.
// Calls the ft_fork() function to fork a child process and execute the command.
/*
Initializes fd_in to STDIN_FILENO, representing the standard input file descriptor.
Enters a loop to iterate over the command structures (t_cmds) in utils->cmds.
Calls the call_expander function to expand the command and redirections.
If there is a next command (utils->cmds->next), it creates a pipe using the pipe function and assigns the file descriptors to end.
Sends the here-document if utils->heredoc flag is true.
Calls the ft_fork function to fork a child process and execute the command.
*/
int	executor(t_utils *utils)
{
	int		end[2];
	int		fd_in;
	t_cmds	*curr_cmd;

	fd_in = STDIN_FILENO;
	curr_cmd = utils->cmds;
	while (curr_cmd)
	{
/* 		curr_cmd = call_expander(utils, curr_cmd);*/
		if (curr_cmd->next)
			pipe(end);
		send_heredoc(utils, curr_cmd);
		ft_fork(utils, end, fd_in, curr_cmd);
		close(end[1]);
		if (curr_cmd->prev)
			close(fd_in);
		fd_in = check_fd_heredoc(utils, end, curr_cmd);
		if (curr_cmd->next)
			curr_cmd = curr_cmd->next;
		else
			break ;
	}
	pipe_wait(utils->pid, utils->pipes);
	return (0);
}
/*
Added Additional
*/
/*
This function returns the first node of the t_cmds linked list.
It takes the head of the list (map) as the argument.
It iterates through the list by following the prev pointers until it reaches the first node (where map->prev is NULL).
If the list is empty, it returns NULL.
Otherwise, it returns the pointer to the first node.
*/
t_cmds	*ft_cmdsfirst(t_cmds *map)
{
	int	i;

	i = 0;
	if (!map)
		return (NULL);
	while (map->prev != NULL)
	{
		map = map->prev;
		i++;
	}
	return (map);
}
