#╔════════════════════════════════════════════╗
#║         ⚡ MINISHELL OS // v1337 ⚡         ║
#║       Booting Build Protocol :: INIT       ║
#╚════════════════════════════════════════════╝

## Binary name
NAME		:= minishell

## Compiler config
CC			:= cc 
CFLAGS		:= -Wall -Wextra -Werror
HEADERS		:= -I ./include -I libft

## Sources
OBJ_DIR 	:= obj
VPATH 		:= src:src/arena_allocator
SRC_ARENA	:= arena.c arena_utils.c
SRC 		:= \
			main.c \
			$(SRC_ARENA)

OBJS 		:= $(SRC:%.c=$(OBJ_DIR)/%.o)

## External modules
LIBFT_DIR 	:= libft
LIBFT 		:= $(LIBFT_DIR)/libft

#╔════════════════════════════════════════════╗
#║           🛠️  Build Protocols             ║
#╚════════════════════════════════════════════╝

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(HEADERS) $^ -o $@

$(OBJ_DIR)/%.o: %.c
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