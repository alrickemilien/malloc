#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

void print(char *s)
{
	write(1, s, strlen(s));
}

int main()
{
	char *addr;

	write(1, "START\n", 6);
	addr = malloc(16);
	free(NULL);
	free((void *)addr + 5);
	if (realloc((void *)addr + 5, 10) == NULL)
		print("Bonjours\n");
}
