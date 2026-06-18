#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "../libft/libft.h"

#define NORMAL 0
#define S_QUOTE 1
#define D_QUOTE 2

typedef enum e_type {
    WORD,      
    PIPE,      
    APPEND,
    HEREDOC,
    REDIR_OUT,
    REDIR_IN,  
    ENV        
} t_type;

typedef struct s_token {
    char            *content;
    t_type           type;
    struct s_token  *next;
} t_token;

typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
}   t_env;

typedef struct s_cmd
{
    char            **argv;
    char            *infile;
    char            *outfile;
    int             append;
    int             heredoc;
    char            *delimiter;
    struct s_cmd    *next;
} t_cmd;

void add_list(t_token **list,t_token *token);
void add_token(t_token **list, char *word, int type);
int handle_word(t_token **list, char *str);
int handle_redirect(t_token **tokens, char *str);
int find_quote_end(char *str, char quote);
t_token *lexer(char *input);
t_token	*ft_lstlast(t_token *lst);
void print_tokens(t_token *list);


int is_redir(t_type type);
int quotes_closed(char *line);
int check_syntax(t_token *tok, char *line);
void remove_quotes_tokens(t_token *lst);
int len_quotes(char *line);
char *remove_quote(char *token);

void handle_cmd_redirect(t_cmd *cmd, t_token *tok);
t_cmd *new_cmd(int count);
int count_args(t_token *tok);
t_cmd *parse(t_token *tok);
void print_cmds(t_cmd *cmd);

void execute_cmd(t_cmd *cmd, char **env);
void free_tokens(t_token *tokens);


int is_built_in(char *cmd);
int bulit_pwd();
void bulit_exit();
int bulit_cd(char *cd);
int built_echo(t_cmd *cmd);
int built_env(char **envp);



int count_cmds(t_cmd *cmd);
void execute(t_cmd *cmd_list, char  **env);
void execute_single(t_cmd *cmd, char **env);

