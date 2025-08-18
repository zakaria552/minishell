#╔════════════════════════════════════════════╗
#║         ⚡ MINISHELL OS // v1337 ⚡        ║
#║       Booting Build Protocol :: INIT       ║
#╚════════════════════════════════════════════╝

## Binary name
NAME		:= minishell

## Compiler config
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g
HEADERS		:= -I ./include -I ./libft

## Sources
OBJ_DIR 	:= obj
VPATH 		:= src:src/arena_allocator:src/utils:src/vector:src/parsing:src/execution:src/builtins:src/signal
SRC_ARENA	:= arena.c arena_utils.c
SRC_UTILS	:= error_handlers.c prompt.c
SRC_VECTOR	:= vector.c utils.c
SRC_SIGNAL	:= signal.c
SRC_PARSING	:= tokenize.c token_lengths.c parsing.c arena_strings.c command.c\
				syntax.c
SRC_EXEC	:= io_redirets.c execute.c execute_builtins.c binary_path.c here_doc_handler.c
SRC_BUILTINS:= local_vars.c local_var_utils.c b_utils.c env_op_builtins.c exit.c
SRC 		:= \
			main.c \
			$(SRC_ARENA) \
			$(SRC_UTILS) \
			$(SRC_VECTOR) \
			$(SRC_PARSING) \
			$(SRC_EXEC) \
			$(SRC_SIGNAL) \
			$(SRC_BUILTINS)

OBJS 		:= $(SRC:%.c=$(OBJ_DIR)/%.o)

## External modules
LIBFT_DIR 	:= ./libft
LIBFT 		:= $(LIBFT_DIR)/libft
LINKER_LIBS	:= -lreadline

#╔════════════════════════════════════════════╗
#║           🛠️  Build Protocols             ║
#╚════════════════════════════════════════════╝

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) 
	$(CC) $(CFLAGS) $(HEADERS) $^ -o $@ $(LINKER_LIBS)

$(OBJ_DIR)/%.o: %.c $(LIBFT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFT):
	@git clone -q --depth 1 \
	--branch v1.0.0 \
	--single-branch \
	git@github.com:zakaria552/libft.git $(LIBFT_DIR) > /dev/null 2>&1
	make -C $(LIBFT_DIR) all

#╔════════════════════════════════════════════╗
#║             💣 Killcode protocals         ║
#╚════════════════════════════════════════════╝

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make clean -C $(LIBFT_DIR)

re: fclean all

#╔════════════════════════════════════════════╗
#║        👾 Callable Protocols              ║
#╚════════════════════════════════════════════╝

.PHONY: all clean fclean
