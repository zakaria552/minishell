#ifndef PARSING_H
# define PARSING_H

//forward declaration of used structures, 
//actual definitions in arena.h, vector.h and here, respectively
typedef struct s_arena		t_arena;
typedef struct s_vector		t_vector;

//token length counting functions for all types conform to this typedef
typedef ssize_t				(*t_token_length_func)(char *);

typedef enum e_token_type
{
	EMPTY,
	PIPE,
	INPUT_REDIR,
	OUTPUT_REDIR,
	OUTPUT_APPEND,
	HERE_DOC,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
	EXPANSION,
	STRING
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*content;
	int				read_chars;
	t_vector		*redirects;
	char			**args;
}	t_token;

typedef struct s_cmd
{
	char		*cmd;
	t_vector	*args;
	t_vector	*redirects;
	bool		unmatched_quote;
	int			fd_here_doc;
	int			curr_pipe[2];
	int			next_pipe[2];
	int			pid;
	bool		is_last_cmd;
	bool		is_first_cmd;
}	t_cmd;

typedef struct s_redirect
{
	t_token_type	type;
	char			*content;
}	t_redirect;

//tokenize.c
t_vector	*tokenize_input(char *s, t_arena *arena, char delimiter);
const char	*get_token_type(t_token_type type);
//debug, remove before final submission
//void		print_token(t_token *tok);

//concatenate_strings.c
char		*concat_string_types(t_arena *arena, t_vector *vec, int *i, bool *x);
char		*strip_quotes(t_arena *arena, char *str, bool should_strip);

//expansion.c
char		*handle_expansion(t_arena *arena, char *s, char *start);
char		*expand_variable(t_arena *arena, char *s);
void		expand_single_dollar(t_vector *vec, t_arena *arena);

//token_lengths.c
ssize_t		single_quote_length(char *s);
ssize_t		double_quote_length(char *s);
ssize_t		string_length(char *s);
ssize_t		empty_length(char *s);

//token_utils.c
void		empty_empty_expansion(t_vector *tokens, t_arena *arena);
int			is_string_delimiter(char c);
int			is_legal_expansion_char(char c);
ssize_t		expansion_length(char *s);
ssize_t		dummy_length(char *s);

//parsing.c
t_vector	*tokenize_and_parse(char *s, t_arena *arena, char delimiter);
t_vector	*parse_tokens_to_commands(t_arena *arena, t_vector *vec);
bool		is_string_type(t_token *tok);
bool		is_redirect_type(t_token *tok);

//arena_strings.c
char		*arena_strdup(t_arena *arena, char *s);
char		*arena_strjoin(t_arena *arena, char *s1, char *s2);

//command.c
t_cmd		*init_command(t_arena *arena);
void		update_command(t_arena *arena, t_cmd *command, t_vector *vec,\
				int *i);
//debug
//void	print_command(t_cmd *command);
//void	print_vector_commands(t_vector *vec);

//syntax.c
bool		check_all_empty(t_vector *tokens);
bool		check_redirect(t_arena *arena, t_token *token);
bool		check_command(t_arena *arena, t_cmd *command);

//split_string.c
t_vector 	*split_string(char *str, t_arena *arena, bool split);

#endif
