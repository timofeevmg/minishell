#include "minishell.h"

void executor(void)
{
	if (!ft_strncmp(g_msh.pars->args[0], "echo", 4))
		g_msh.ret = echo_func(g_msh.pars->args);
	else if (!ft_strncmp(g_msh.pars->args[0], "cd", 2))
		g_msh.ret = cd_func(g_msh.pars->args);
	else if (!ft_strncmp(g_msh.pars->args[0], "pwd", 2))
		g_msh.ret = pwd_func();
	else if (!ft_strncmp(g_msh.pars->args[0], "export", 2))
		g_msh.ret = export_func(g_msh.pars->args);
//	else if (!ft_strncmp(g_msh.pars.args[0], "unset", 2))
//		ret = unset_func(g_msh.pars.args);
	else if (!ft_strncmp(g_msh.pars->args[0], "env", 2))
		g_msh.ret = env_func();
//	else if (!ft_strncmp(g_msh.pars.args[0], "exit", 2))
//		ret = exit_func(g_msh.pars.args);
	else
		g_msh.ret = exec_func(g_msh.pars->args);
}