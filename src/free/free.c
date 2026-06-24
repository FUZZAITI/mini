#include "minishell.h"

void free_tokens(t_token *tokens);
void free_env(t_env *env);
void free_cmd(t_cmd *cmd);
void free_arraay(char **array);

void free_tokens(t_token *tokens)
{
	 t_token *tmp;

	 while (tokens)
	 {
		  tmp = tokens->next;
		  free(tokens->content);
		  free(tokens);
		  tokens = tmp;
	 }
}

void free_env(t_env *env)
{
    t_env *tmp;

    while (env)
    {
        tmp = env->next;
        free(env->key);
        free(env->value);
        free(env);
        env = tmp;
    }
}

void free_cmd(t_cmd *cmd)
{
    t_cmd *tmp;

    while (cmd)
    {
        tmp = cmd->next;
        free_arraay(cmd->argv);
        free(cmd->infile);
        free(cmd->outfile);
        free(cmd->delimiter);
        free(cmd);
        cmd = tmp;
    }
}

void free_arraay(char **array)
{
    int i;

    if (!array)
        return ;
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}