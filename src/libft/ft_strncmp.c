#include "libft.h"
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	c;
	c = 0;
	while (s1[c] != '\0' && s2[c] != '\0' && (s1[c] == s2[c]))
	{
		c++;
	}
	if ((s1[c] != s2[c]) && (c < n))
		return ((unsigned char)s1[c] - (unsigned char)s2[c]);
	return (0);
}