#include "../../minishell.h"

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths && paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

static char	*build_cmd_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

char	*resolve_executable(t_shell *shell, char *cmd)
{
	char	**paths;
	char	*full;
	char	*path_env;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = get_env(shell, "PATH");
	if (!path_env || !*path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths && paths[i])
	{
		full = build_cmd_path(paths[i], cmd);
		if (full && access(full, X_OK) == 0)
			return (free_paths(paths), full);
		free(full);
		i++;
	}
	free_paths(paths);
	return (NULL);
}
