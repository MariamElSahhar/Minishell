/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:08:09 by szerisen          #+#    #+#             */
/*   Updated: 2023/07/06 18:34:47 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void	minishell_loop(t_utils *utils, char **envp);
/*
This function initializes the utils structure with default values and sets up the environment.
It sets various variables and flags in the utils structure to their initial values.
It calls the parse_envp function to parse the environment variables and store them in the utils structure.
It calls the init_signals function to set up signal handling for the minishell.
*/
int	implement_utils(t_utils *utils)
{
	utils->cmds = NULL;
	utils->reset = false;
	utils->pid = NULL;
	utils->heredoc = false;
	g_global.stop_heredoc = 0;
	g_global.in_cmd = 0;
	g_global.in_heredoc = 0;
	parse_envp(utils);
	return (1);
}
/*
The reset_utils function is called to reset the utils structure and restart the minishell loop if needed.

This function resets the utils structure and restarts the minishell loop if needed.
It frees the memory allocated for the command list (cmdss), arguments (args), process IDs (pid), and paths (paths).
It calls the implement_utils function to re-initialize the utils structure with default values and set up the environment.
Finally, it calls the minishell_loop function to restart the minishell loop.
*/

void	free_cmd(t_cmds *cmd)
{
	t_redir	*ptr;
	t_redir	*del;

	if (cmd->hd_file_name)
		free(cmd->hd_file_name);
	if (cmd->args)
		free_double_ptr((void **) cmd->args);
	ptr = cmd->redirections;
	while (ptr)
	{
		del = ptr;
		ptr = ptr->next;
		if (del->path)
			free(del->path);
		free(del);
	}
	free(cmd);
}

void	free_utils(t_utils *utils)
{
	t_cmds	*ptr;
	t_cmds	*del;

	ptr = utils->cmds;
	while (ptr)
	{
		del = ptr;
		ptr = ptr->next;
		free_cmd(del);
	}
	if (utils->input)
		free(utils->input);
	if (utils->pid)
		free(utils->pid);
	if (utils->pwd)
		free(utils->pwd);
	if (utils->old_pwd)
		free(utils->old_pwd);
	free_double_ptr((void **)utils->envp);
	free_double_ptr((void **)utils->paths);
	// free_arr(utils->paths);
}

int	reset_utils(t_utils *utils)
{
	free_utils(utils);
	// implement_utils(utils);
	utils->reset = true;
	return (1);
}
/*
The prepare_executor function is responsible for setting up the executor to execute commands entered by the user.
It sets up signal handling and calls the appropriate functions depending on whether there are pipes or not.
This function sets up the executor to execute commands entered by the user.
It sets up the signal handling for the execution of commands, specifically handling the SIGQUIT signal (usually triggered by pressing Ctrl+).
It sets the in_cmd flag in the g_global structure to indicate that the minishell is currently executing a command.
If there are no pipes in the command, it calls the single_cmd function to execute the single command stored in the command list (cmdss).
If there are pipes in the command, it allocates memory for an array of process IDs (pid) to track the child processes.
It calls the executor function to execute the commands with pipes, which handles the creation of pipes, forking child processes, and connecting
them with pipes for communication.
*/
int	prepare_executor(t_utils *utils)
{
	signal(SIGQUIT, sigquit_handler);
	g_global.in_cmd = 1;
	if (utils->pipes == 0)
		single_cmd(utils->cmds, utils);
	else
	{
		utils->pid = ft_calloc(utils->pipes + 2, sizeof(int));
		if (!utils->pid)
			return (ft_error(1, utils));
		executor(utils);
	}
	g_global.in_cmd = 0;
	return (EXIT_SUCCESS);
}
/*
This function represents the main loop of the minishell program.
It reads user input using the readline function and stores it in utils->args.
It trims any leading or trailing whitespace from the input using ft_strtrim.
If the input is empty (only contains whitespace), it returns to the reset_utils function to reset the minishell state and restart the loop.
The input is added to the command history using add_history from the readline library.
The count_quotes function is called to check if the quotes in the input are balanced. If they are unbalanced, an error is returned.
The token_reader function is called to tokenize the input string into individual tokens and create a linked list of tokens (utils->lexer_list).
The parser function is called to parse the tokens and build a syntax tree.
The prepare_executor function is called to execute the commands based on the parsed input.
Finally, the reset_utils function is called to reset the minishell state and restart the loop.

*/
void	minishell_loop(t_utils *utils, char **envp)
{
	// while (1)
	// {
		// utils->input = readline(READLINE_MSG);
		utils->envp = ft_arrdup(envp);
		find_pwd(utils);
		implement_utils(utils);
		char input [] = "echo $?";
		utils->input = ft_strdup(input);
		if (!utils->input)
		{
			// ft_putendl_fd("exit", STDOUT_FILENO);
			reset_utils(utils);
			// rl_replace_line("exit", 0);
			exit(EXIT_SUCCESS);
		}
		if (utils->input[0] == '\0')
		{
			reset_utils(utils);
			// continue ;
		}
		// add_history(utils->input);
		// parse_input(utils);
		if (parse_input(utils))
		{
			printf("execution:\n");
			prepare_executor(utils);
		}
		reset_utils(utils);
		printf("reset utils\n");
		// free(input);
	// }
}
