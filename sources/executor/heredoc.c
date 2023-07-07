/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerisen <szerisen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:01:53 by szerisen          #+#    #+#             */
/*   Updated: 2023/07/07 14:36:58 by szerisen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*It opens the file using open with the 
O_CREAT, O_RDWR, and O_TRUNC flags,
 creates a loop that reads input lines 
 until the here document's end condition is met
 (either when the user enters the same line 
 as the here document or
 when the global flag g_global.stop_heredoc 
 is set to true).
 Here I am writing the line to the file 
 opened using write function
 passing newline to separate the input from the user.
*/
int	create_heredoc(t_redir *heredoc, char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline(HEREDOC_MSG);
	while (line && ft_strncmp(heredoc->path, line, ft_strlen(heredoc->path))
		&& !g_global.stop_heredoc)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(HEREDOC_MSG);
	}
	free(line);
	if (g_global.stop_heredoc || !line)
		return (EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}

/*
g_global.stop_heredoc = 0;
This flag is used to control the termination 
condition of the here document loop in the
create_heredoc function. When this flag is 
set to a non-zero value,
the loop in create_heredoc will exit,
 stopping the creation of the here document.

g_global.in_heredoc = 1;
This flag is used to control the termination 
condition of the here document loop in the
create_heredoc function. When this flag is 
set to a non-zero value,
the loop in create_heredoc will exit, 
stopping the creation of the here document.

This flag is used to indicate whether the 
program is currently inside a here document.
It is set to 1 (true) when entering the 
ft_heredoc function and creating a
here document, and set back to 0 (false)
*/
int	ft_heredoc(t_utils *utils, t_redir *heredoc, char *file_name)
{
	int		sl;

	sl = EXIT_SUCCESS;
	g_global.stop_heredoc = 0;
	g_global.in_heredoc = 1;
	sl = create_heredoc(heredoc, file_name);
	g_global.in_heredoc = 0;
	utils->heredoc = true;
	return (sl);
}

/*
generates a unique filename for the here document file.
It uses a static variable i to keep track of the number of generated filenames.
The function converts i to a string and appends it to the prefix
"build/.tmp_heredoc_file_". It then returns the generated filename.
*/
char	*generate_heredoc_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin("build/.tmp_heredoc_file_", num);
	free(num);
	return (file_name);
}

/*
It starts by saving the initial value of 
"cmd->redirection" in the variable
"start". This is doen to ensure that the 
'cmd->redirection' pionter is reset
to the beginning of the list.
/*
Initializes the variable sl to EXIT_SUCCESS. 
This variable will store the success or
failure status of the ft_heredoc function, 
which is called for each here document.
*/
/*
Inside the loop, it checks if the current 
redirection token
is LESS_LESS, indicating a here document.
*/
/*
It frees the previously stored 
'cmd->hd_file_name' (if any)
to avoid memory leaks

if (cmd->hd_file_name)
	free(cmd->hd_file_name); */
/*
It generates a new uniques filename 
for the here document file using the
generate_heredoc_filename funciton 
and assigns it to 'cmd->hd_file_name'
*/
/*
It calls the ft_heredoc function to 
create the here document. The ft_heredoc
function handles the processing of a 
single here document, and it is called
with the utils pointer, the current 
redirection (cmd->redirections), and
the generated filename (cmd->hd_file_name)
as arguments. The result of the 
ft_heredoc function is stored in the sl variable
*/
/*
if the ft_heredoc function returns a 
non-zero value (EXIT_FAILURE), it sets
g_global.error_num to 1 to indicate 
an error and returns reset_utils(utils).
This is done to handle any failure 
during here document processing.
*/
int	send_heredoc(t_utils *utils, t_cmds *cmd)
{
	t_redir	*redir;
	int		sl;

	redir = cmd->redirections;
	sl = EXIT_SUCCESS;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			cmd->hd_file_name = generate_heredoc_filename();
			sl = ft_heredoc(utils, redir, cmd->hd_file_name);
			if (sl)
			{
				g_global.error_code = 1;
			}
		}
		redir = redir->next;
	}
	return (EXIT_SUCCESS);
}
