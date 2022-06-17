#include "minishell.h"
#include <unistd.h>



int cd_core(t_cmd *cmd, t_envp *env)
{


	char	**args = list_to_args(tmp_cmd);
	char	**env_array = list_to_env(envp);
	if (cmd->args == NULL)
	{
		cd_home(0, env);
	}


	return (0);
}