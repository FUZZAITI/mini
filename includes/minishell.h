#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "../libft/libft.h"
#include <fcntl.h>

extern int  g_exit_status;

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

void init_shell(t_env *env, char *line);
void process_line(char *line, t_env *env);

t_env *env_init(char **envp);
char **env_to_array(t_env *env);
int env_size(t_env *env);
char *get_env_value(char *var_name, t_env *env_list);
t_env *new_env(char *key, char *value);
void add_env_back(t_env **env, t_env *new);

t_token *lexer(char *input);
int handle_word(t_token **tokens, char *str);
int handle_infile(t_token **tokens, char *str);
int handle_outfile(t_token **tokens, char *str);
int find_quote_end(char *str, char quote);
int is_redir(t_type type);
int quotes_closed(char *line);
int check_syntax(t_token *tok, char *line);
void remove_quotes_tokens(t_token *lst);
char *remove_quotes(char *str);
void add_token(t_token **list, char *word, int type);
void add_list(t_token **list,t_token *token);
t_token	*ft_lstlast(t_token *lst);

void free_tokens(t_token *tokens);
void free_env(t_env *env);
void free_cmd(t_cmd *cmd);
void free_arraay(char **array);

void pre_expander(t_token *list, t_env *env_list);
char *get_var_value(char *line, int *i, t_env *env_list);
char *ft_strjoin_free(char *s1, char *s2);
char *handle_expander(char *line, t_env *env_listn, int i, int state);
char *add_char_to_str(char *dest, char carac);
char *ft_strjoin_free(char *s1, char *s2);
void	update_state(char c, int *state);

int count_cmds(t_cmd *cmd);
void execute(t_cmd *cmd_list, t_env *env);
void execute_single(t_cmd *cmd, t_env *env);
void run_builtin(t_cmd *cmd, t_env *env);
void restore_std_fds(int saved_stdin, int saved_stdout);
int setup_redirections(t_cmd *cmd);
char *get_cmd_path(t_cmd *cmd, char **path);
void execve_cmd(t_cmd *cmd, t_env *env, char *path);
char **split_path(t_env *env);
void execute_cmd(t_cmd *cmd, t_env *env);
void execute_single_child(t_cmd *cmd, t_env *env);
pid_t launch_cmd(t_cmd *cmd, t_env *env, int prev_fd, int fd[2]);
void execute_pipeline(t_cmd *cmd, t_env *env, int cmd_count);
void free_array(char **array);

t_cmd *parse(t_token *tok);
int count_args(t_token *tok);
t_cmd *new_cmd(int count);
void handle_cmd_redirect(t_cmd *cmd, t_token *tok);

int is_built_in(char *cmd);
void run_builtin(t_cmd *cmd, t_env *env);
int bulit_pwd();
int built_env(t_env *envp);
int built_echo(t_cmd *cmd);
int bulit_cd(char *cd);
void	built_export(t_cmd *cmd, t_env *env);
void add_env_node_export(t_env *last, char *key, char *value);
int	update_export(t_env *env, char *key, char *value);
void	update_env(t_env *node, char *value);
void bulit_exit();
