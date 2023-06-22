NAME = minishell
MKDIR = mkdir  // specifies the command used to create directories, which is "mkdir"

CC = gcc

LIBFTP = libraries/libft
PATHB = build/
PATHO = build/objs/
PATHS = sources/
PATHSL = sources/lexer/
# PATHSP = sources/parser/
PATHSB = sources/builtins/
PATHSEX = sources/expander/
PATHSU = sources/utils/
PATHSE = sources/error/
PATHP = sources/pipex/
PATHEX = sources/executor/

BUILD_PATHS = $(PATHB) $(PATHO)

sources	=	sources/main.c \
		sources/signals.c \
		sources/lexer/handle_quotes.c \
		sources/lexer/handle_token.c \
		sources/lexer/token_reader.c \
		sources/builtins/builtins.c \
		sources/builtins/m_cd.c \
		sources/builtins/m_echo.c \
		sources/builtins/m_env.c \
		sources/builtins/m_exit.c \
		sources/builtins/m_export.c \
		sources/builtins/m_pwd.c \
		sources/builtins/m_unset.c \
		sources/builtins/utils_builtins.c \
		sources/utils/minishell_loop.c \
		sources/utils/parse_envp.c \
		sources/utils/t_lexer_clear_utils.c \
		sources/utils/t_lexer_utils.c \
		sources/utils/t_cmds_utils.c \
		sources/utils/utils.c \
		sources/error/error_handling.c \
		sources/error/ft_error.c \
		sources/executor/redirection_check.c \
		sources/executor/executor.c \
		sources/executor/cmds_handler.c \
		sources/executor/heredoc.c \
		sources/executor/executor_utils.c \

OBJS	=	$(addprefix $(PATHO), $(notdir $(patsubst %.c, %.o, $(sources))))

FLAGS	=	-Wall -Werror -Wextra -g #-fsanitize=address

LIBFT	=	./libraries/libft/libft.a

HEADER	=	.includes/builtins.h \
			.includes/color.h \
			.includes/error.h \
			.includes/executor.h \
			.includes/lexer.h \
			.includes/minishell.h \
			.includes/parser.h \
			.includes/utils.h 

READLINE_DIR = $(shell brew --prefix readline)

READLINE_LIB = -lreadline -lhistory -L $(READLINE_DIR)/lib
	
INCLUDES =-Iincludes -I$(PATHP) -I$(LIBFTP) -I$(READLINE_DIR)/include 

all: $(BUILD_PATHS) $(NAME)

$(PATHO)%.o:: $(PATHS)%.c
	@echo "Compiling ${notdir $<}			in	$(PATHS)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSL)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}			in	$(PATHSL)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

# $(PATHO)%.o:: $(PATHSP)%.c $(HEADERS)
# 	@echo "Compiling ${notdir $<}			in	$(PATHSP)"
# 	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSB)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}			in	$(PATHSB)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSEX)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}			in	$(PATHSEX)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSU)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}			in	$(PATHSU)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSE)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}			in	$(PATHSE)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHEX)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}			in	$(PATHEX)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(NAME): $(LIBFT) $(OBJS) $(HEADERS)
	@$(CC) $(FLAGS) $(LIBFT) $(OBJS) $(READLINE_LIB) -o $(NAME)

	@echo "Success"

$(LIBFT):
	@$(MAKE) -C ./libraries/libft

$(PATHB):
	@$(MKDIR) $(PATHB)

$(PATHO):
	@$(MKDIR) $(PATHO)

clean:
	@echo "Cleaning"
	@rm -f $(OBJS)
	@rm -f $(PATHB).tmp*
	@rmdir $(PATHO) $(PATHB)
	@make fclean -C libraries/libft

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re: fclean all

.PRECIOUS: $(PATHO)%.o