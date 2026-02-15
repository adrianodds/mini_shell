#include "minishell.h"

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*tmp;
	char	*full;
	int		i;
	char	*path_env;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = get_path(envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if(access(full, X_OK) == 0)
		{
			free_args(paths);
			return (full);
		}
		free(full);
		i++;
	}
	free_args(paths);
	return (NULL);
}
