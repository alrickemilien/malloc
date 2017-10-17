#include <unistd.h>

void	ft_putnbr_hex(int octet, int rem)
{
	char const *base = "0123456789abcdef";

	if (rem > 1)
		ft_putnbr_hex(octet >> 4, rem - 1);
	write(1, base + (octet % 16), 1);
}

void	ft_print_octets(unsigned char const *addr, size_t size, size_t i)
{
	int		a;

	a = 0;
	while (a < 16 && a + i < size)
	{
		ft_putnbr_hex(*(addr + i + a), 2);
		if (a % 2)
			write(1, " ", 1);
		a++;
	}
	while (a < 16)
	{
		write(1, "  ", 2);
		if (a % 2)
			write(1, " ", 1);
		a++;
	}
}

void	memory_putchar(const unsigned char *addr)
{
	const char c = *addr;

	if (c >= ' ' && c <= '~')
		write(1, &c, 1);
	else
		write(1, ".", 1);
}

void	ft_print_characters(const unsigned char *addr, size_t size, size_t i)
{
	int		a;

	a = 0;
	while (a < 16 && a + i < size)
	{
		memory_putchar(addr + a + i);
		a++;
	}
}

void	print_memory(const void *addr, size_t size)
{
	size_t			i;

	if (!addr)
		return ;
	i = 0;
	while (i < size)
	{
		ft_print_octets((const unsigned char *)addr, size, i);
		ft_print_characters((const unsigned char *)addr, size, i);
		write(1, "\n", 1);
		i += 16;
	}
}
