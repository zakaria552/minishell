#╔════════════════════════════════════════════╗
#║         ⚡ MINISHELL OS // v1337 ⚡         ║
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
VPATH 		:= src:src/arena_allocator:src/utils:src/vector
SRC_ARENA	:= arena.c arena_utils.c
SRC_UTILS	:= clean_up.c prompt.c
SRC_VECTOR	:= vector.c utils.c
SRC_PARSING	:= parsing.c
SRC 		:= \
			main.c \
			$(SRC_ARENA) \
			$(SRC_UTILS) \
			$(SRC_VECTOR) \
			$(SRC_PARSING)

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
