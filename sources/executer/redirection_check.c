/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:01:56 by szerisen          #+#    #+#             */
/*   Updated: 2023/05/29 19:48:43 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

/*
The function check_append_outfile takes a t_lexer pointer named redirections as input and checks the type of output redirection (> or >>). 
If the redirection is >> (GREAT_GREAT), it opens the file in append mode (O_APPEND) using open. Otherwise, it opens the file in write mode 
(O_TRUNC). The function returns the file descriptor (fd) corresponding to the opened file.
*/
int	check_append_outfile(t_lexer *redirections)
{
	int	fd;

	if (redirections->token == GREAT_GREAT)
		fd = open(redirections->str,
				O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(redirections->str,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (fd);
}
/*
The function handle_infile takes a char pointer named file as input and handles input file redirection. 
It opens the file in read-only mode (O_RDONLY) using open. If the file opening fails, it prints an error 
message and returns EXIT_FAILURE. If the file is successfully opened, it duplicates the file descriptor 
(fd) to the standard input file descriptor (STDIN_FILENO) using dup2. Finally, it closes the file descriptor 
if it's greater than zero and returns EXIT_SUCCESS.
*/
int	handle_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: infile: No such file or directory\n",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

/*
The function handle_outfile takes a t_lexer pointer named redirection as input and handles output file redirection. It calls 
the check_append_outfile function to open the file with the appropriate mode. If the file opening fails, it prints an 
error message and returns EXIT_FAILURE. If the file is successfully opened, it duplicates the file descriptor to the 
standard output file descriptor (STDOUT_FILENO) using dup2. Finally, it closes the file descriptor if it's greater 
*/

int	handle_outfile(t_lexer *redirection)
{
	int	fd;

	fd = check_append_outfile(redirection);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: outfile: Error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}
/*
	This function checks for redirections
	If the redirection is LESS (<), it calls the handle_infile() function with 
	the file name specified in cmd->redirections->str. This function handles the input 
	file redirection by opening the file in read-only mode, duplicating the file descriptor 
	to the standard input file descriptor (STDIN_FILENO) using dup2(), and closing the file descriptor.
*/
int	check_redirections(t_cmds *cmd)
{
	t_lexer	*start;

	start = cmd->redirections;
	while (cmd->redirections)
	{
		if (cmd->redirections->token == LESS)
		{
			if (handle_infile(cmd->redirections->str))
				return (EXIT_FAILURE);
		}
		/*
		If the redirection is GREAT (>) or GREAT_GREAT (>>), it calls the handle_outfile() function 
		with the current redirections element. This function handles the output file redirection by 
		opening the file in either truncate or append mode, duplicating the file descriptor to the standard 
		output file descriptor (STDOUT_FILENO) using dup2(), and closing the file descriptor.
		*/
		else if (cmd->redirections->token == GREAT
			|| cmd->redirections->token == GREAT_GREAT)
		{
			if (handle_outfile(cmd->redirections))
				return (EXIT_FAILURE);
		}
		/*
		if the redirection is LESS_LESS (<<), it calls the handle_infile() function with the here document file
		name specified in cmd->hd_file_name. 
		This function handles the here document redirection in a similar way to input file redirection.
		*/
		else if (cmd->redirections->token == LESS_LESS)
		{
			if (handle_infile(cmd->hd_file_name))
				return (EXIT_FAILURE);
		}
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (EXIT_SUCCESS);
}
