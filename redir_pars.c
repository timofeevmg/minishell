#include "minishell.h"

void	space_pars_rd(t_pars *pars)
{
	while (pars->s[pars->i] == ' ')
		pars->i++;
	pars->s = ft_cutstr_begin(pars->s, pars->i);
	pars->i = 0;
}

void	dollar_pars_rd(t_pars *pars)
{
	char	*env_name;
	char	*env_val;

	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
	env_name = get_env_name(pars);
	env_val = env_value(g_msh.envp, env_name);
	free(env_name);
	env_name = NULL;
	pars->rds = ft_strjoin_fr(pars->rds, env_val);
	free(env_val);
	env_val = NULL;
}

void	strongquotes_pars_rd(t_pars *pars)
{
	char	*sq_str;

	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
	//check for 2nd ' -> search line
	sq_str = get_sq_str(pars);
	pars->rds = ft_strjoin_fr(pars->rds, sq_str);
	free(sq_str);
	sq_str = NULL;
}

void	weakquotes_pars_rd(t_pars *pars)
{
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
	while (pars->s[pars->i] != '\"')
	{
		if (pars->s[pars->i] == '\\' && pars->s[pars->i + 1] == '\\')
		{
			pars->s = ft_cutstr_begin(pars->s, (pars->i + 2));
			pars->rds = ft_strjoin_fr(pars->rds, "\\");
			pars->i = 0;
		}
		else if (pars->s[pars->i] == '\\' && pars->s[pars->i + 1] == '\"')
		{
			pars->s = ft_cutstr_begin(pars->s, (pars->i + 2));
			pars->rds = ft_strjoin_fr(pars->rds, "\"");
			pars->i = 0;
		}
		else if (pars->s[pars->i] == '\\' && pars->s[pars->i + 1] == '$')
		{
			pars->s = ft_cutstr_begin(pars->s, (pars->i + 2));
			pars->rds = ft_strjoin_fr(pars->rds, "$");
			pars->i = 0;
		}
		else
		{
			pars->rds = ft_add_char2str(pars->rds, pars->s[pars->i]);
			pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
			pars->i = 0;
		}
	}
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
}

void	backslash_pars_rd(t_pars *pars)
{
	pars->rds = ft_add_char2str(pars->rds, pars->s[1]);
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 2));
	pars->i = 0;
}

void	enlarge_rds(t_pars *pars)
{
 	pars->rds = ft_add_char2str(pars->rds, pars->s[pars->i]);
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
}

void	redir_pars(t_pars *pars)
{
	while(ft_strchr("<>", pars->s[pars->i]))
	{
		pars->rds = ft_add_char2str(pars->rds, pars->s[pars->i]);
		pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
		pars->i = 0;
	}
	pars->rds = ft_add_char2str(pars->rds, ' ');
	if (pars->s[pars->i] == ' ')
		space_pars_rd(pars);
	while (pars->s[pars->i] != '\0' && pars->s[pars->i] != ' ')
	{
		if (pars->s[pars->i] == '$')
			dollar_pars_rd(pars);
		if (pars->s[pars->i] == '\'')
			strongquotes_pars_rd(pars);
		else if (pars->s[pars->i] == '\"')
			weakquotes_pars_rd(pars);
		else if (pars->s[pars->i] == '\\')//check if no symbol after '\'
			backslash_pars_rd(pars);
		else
			enlarge_rds(pars);
	}
	pars->rds = ft_add_char2str(pars->rds, ' ');
}