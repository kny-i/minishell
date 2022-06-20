#ifndef EXECUTE_H
#define EXECUTE_H

# include "./minishell.h"
# include "./lexer.h"
# include "./env.h"
# include "./parser.h"
typedef struct s_cmd	t_cmd;
typedef struct s_envp    t_envp;

typedef struct s_lexer	t_lexer;
int count_cmd(t_cmd *cmd);

void execute_test(t_cmd **cmd_list, t_envp *envp);

#endif