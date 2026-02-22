#include "minishell.h"

char **duplicate_envp(char **envp)
{
	int	count;
	char	**copy;
	int	i;

	count = 0;
	while(envp[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			copy[i] = NULL;
			free_args(copy);
			return (NULL);
		}
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

int main(int ac, char **av, char **envp)
{
	char *line;
	char **env;
	(void)ac;
	(void)av;
	
	env = duplicate_envp(envp);
	if(!env)
		return (1);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break;
		printf("Teste: %s\n", line);
		add_history(line);
		exec_line(line, &env);
		free(line);
	}
	free_args(env);
	return (0);
}