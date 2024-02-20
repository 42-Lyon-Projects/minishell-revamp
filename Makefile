NAME = minishell

MAKE_LIBFT = make -C ./dependencies/libft
LIBFT = ./dependencies/libft/build/libft.a

FILES =	main.c							\
		builtins/cd_builtin.c			\
		builtins/echo_builtin.c			\
		builtins/env_builtin.c			\
		builtins/exit_builtin.c			\
		builtins/export_builtin.c		\
		builtins/get_export_values.c	\
		builtins/unset_builtin.c		\
		builtins/pwd_builtin.c			\
		command/command_handler.c		\
		command/command_manager.c		\
		command/command_utils.c			\
		environment/env_getter.c		\
		environment/env_manager.c		\
		environment/env_setter.c		\
		environment/env_transformer.c	\
		exec/exec_dispatcher.c			\
		exec/exec_pipex.c				\
		exec/path_handler.c				\
		exec/exec_utils.c				\
		parsing/on_parsing.c			\
		parsing/post_parsing.c			\
		parsing/pre_parsing.c			\
		parsing/redirection_parsing.c	\
		parsing/redirection_parsing_2.c	\
		heredoc/heredoc_parsing.c		\
		heredoc/heredoc_parsing_2.c		\
		heredoc/heredoc_utils.c			\
		tokens/tokenizer.c				\
		tokens/tokens_handler.c			\
		tokens/tokens_concat.c			\
		tokens/tokens_utils.c			\
		utils/quote_utils.c				\
		utils/str_utils.c				\
		utils/str_utils_2.c				\
		utils/messages_utils.c			\
		utils/debug.c					\
		utils/merge_sort.c				\
		signals/ingore_signal.c			\
		signals/exit_signal.c			\
		signals/pipe_signal.c			\
		signals/signals_manager.c		\
		signals/heredoc_signal.c		\

BUILD_DIRECTORY = ./build/

CC = gcc

FLAGS = -c -g3

SOURCES = $(addprefix "sources/", $(SRCS:.c=.o))
OBJS = $(addprefix $(BUILD_DIRECTORY), $(FILES:.c=.o))

$(NAME): $(BUILD_DIRECTORY) $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT): force
	$(MAKE_LIBFT)

$(BUILD_DIRECTORY)%.o: ./sources/%.c Makefile ./includes/*.h
	$(CC) $(FLAGS) -I ./includes/ -I ./dependencies/libft/.includes/ $< -o $@

$(BUILD_DIRECTORY):
	mkdir -p $(BUILD_DIRECTORY)exec		\
	$(BUILD_DIRECTORY)command			\
	$(BUILD_DIRECTORY)environment		\
	$(BUILD_DIRECTORY)utils				\
	$(BUILD_DIRECTORY)parsing			\
	$(BUILD_DIRECTORY)builtins			\
	$(BUILD_DIRECTORY)tokens			\
	$(BUILD_DIRECTORY)signals			\
	$(BUILD_DIRECTORY)heredoc

all : $(NAME)

clean :
	$(MAKE_LIBFT) clean
	$(RM) $(NAME)
	rm -rf $(BUILD_DIRECTORY)

fclean : clean
	$(MAKE_LIBFT) fclean
	rm -rf $(NAME)

re : fclean all

force :

.PHONY: all clean fclean re force minishell
