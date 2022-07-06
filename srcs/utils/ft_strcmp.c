#include "utils.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (1);
	while (*s1 == *s2 && *s1 != '\0' && *s2 != '\0')
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
