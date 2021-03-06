#include "minishell.h"

char	**cd_pwd(char *pwd)
{
	char	**tmp;

	if (!pwd)
		error_func(ERROR_MEM, 1, 0, NULL);
	tmp = ft_split("export PWD OLDPWD", ' ');
	if (!tmp)
		error_func(ERROR_MEM, 1, 0, NULL);
	free(tmp[1]);
	tmp[1] = ft_strdup(pwd);
	if (!tmp[1])
		error_func(ERROR_MEM, 1, 0, NULL);
	free(pwd);
	return (tmp);
}

int	cd_home(void)
{
	char	**arr;
	int		i;

	i = env_finder(g_msh.envp, "HOME");
	if (i == -1)
		return (error_func("minishell: cd: HOME not set", 1, 1, NULL));
	arr = ft_split("cd a", ' ');
	if (!arr)
		error_func(ERROR_MEM, 1, 0, NULL);
	free(arr[1]);
	arr[1] = env_value(g_msh.envp, "HOME");
	cd_func(arr);
	free_envc(arr, 1);
	return (0);
}

void	switch_pwd_oldpwd(void)
{
	char	**pwd;
	char	*tmp;

	tmp = env_value(g_msh.envp, "PWD");
	if (!tmp)
	{
		tmp = ft_strdup("");
		if (!tmp)
			error_func(ERROR_MEM, 1, 0, NULL);
	}
	pwd = cd_pwd(ft_strjoin("OLDPWD=", tmp));
	free(tmp);
	free(pwd[2]);
	tmp = getcwd(NULL, 0);
	if (!tmp)
		error_func(ERROR_MEM, 1, 0, NULL);
	pwd[2] = ft_strjoin("PWD=", tmp);
	if (!pwd[2])
		error_func(ERROR_MEM, 1, 0, NULL);
	export_func(pwd);
	free(tmp);
	free_envc(pwd, 2);
}

int	cd_func(char **av)
{
	int	code;

	if (!av[1])
		return (cd_home());
	code = chdir(av[1]);
	if (code == -1)
		return (error_func(NULL, 1, 1, av[1]));
	switch_pwd_oldpwd();
	return (0);
}
