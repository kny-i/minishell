#include <libc.h>


int	main()
{
	extern char	**environ;
	int i;

	i = 0;
	while (environ[i] != NULL)
	{
		printf("line [%d] = [%s]\n", i, environ[i]);
		i++;
	}
	return 0;
}