/*
 *		Tests pour malloc
 */

# include <unistd.h>
# include <sys/mman.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "../src/include/malloc.h"


int			test_0_basic(){
	char	*str;
	int		i;

	str = malloc(sizeof(char) * 51);
	for (i=0;i<50;i++){
		str[i] = '*';
	}
	str[50] = 0;
	show_alloc_mem();
	free(str);
	show_alloc_mem();
	return (1);
}

int			test_1_fork(){
	int		pid;
	char	c;
	char	*ptr;
	int		i;

	pid = fork();
	if (pid == 0)
		c = 's';
	else
		c = 'p';
	ptr = malloc(sizeof(char) * 11);
	for (i=0;i<10;i++){
		ptr[i] = c;
	}
	ptr[10] = 0;
	if (pid != 0)
		wait(0);
	if (pid == 0)
	{
		show_alloc_mem();
		free(ptr);
		show_alloc_mem();
		exit(0);
	}
	show_alloc_mem();
	free(ptr);
	show_alloc_mem();
	return (1);
}

int			test_2_fork(){
	int		pid;
	char	c;
	char	*ptr;
	int		i;

	ptr = malloc(sizeof(char) * 11);
	ptr[10] = 0;
	pid = fork();
	if (pid == 0)
		c = 's';
	else
		c = 'p';
	for (i=0;i<10;i++){
		ptr[i] = c;
	}
	printf("%s\n", ptr);
	free(ptr);
	if (pid != 0)
		wait(0);
	if (pid == 0)
		exit(0);
	return (1);
}

int			test_3_strcat(){
	char	*buf;
	
	buf = malloc(sizeof(char) * 20);
	buf[0] = 0;
	ft_putstr( strcat(buf, "salut"));
	show_alloc_mem();
	ft_putstr( strcat(buf, " les kheys"));
	show_alloc_mem();
	free(buf);
	show_alloc_mem();
	return (1);
}

int			test_4_strdup(const char *s){
	char	*buf;

	buf = strdup(s);
	printf("%s\n", buf);
	free(buf);
	return (1);
}

int			test_5_realloc(const char *s1, const char *s2){

	int		i;
	int		n1;
	int		n2;
	char	*buf;

	n1 = strlen(s1);
	buf = malloc(sizeof(char) * (n1 + 1));
	for (i=0;s1[i];i++){
		buf[i] = s1[i];
	}
	buf[n1] = 0;
	printf("%s\n", buf);
	n2 = strlen(s2);
	buf = realloc(buf, sizeof(char) * (n1 + n2 + 1));
	buf[n1 + n2] = 0;
	printf("%s\n", buf);
	for (i=0;s2[i];i++){
		buf[n1 + i] = s2[i];
	}
	printf("%s\n", buf);
	free(buf);
	return (1);
}

int			test_6_null()
{
	char	*buf;

	buf = malloc(0);
	printf("%p\n", buf);
	//show_alloc_mem();
	return (1);
}

int			test_6_huge_size()
{
	char	*buf;

	buf = malloc(0xffffffff);
	printf("%p\n", buf);
	free(buf);
	//show_alloc_mem();
	return (1);
}

int			test_8_many_mallocs(){

	char	*buf[10];
	
	buf[5] = malloc(sizeof(char));
	buf[7] = malloc(sizeof(char) * 4);
	buf[2] = malloc(sizeof(char) * 42);
	buf[0] = malloc(sizeof(char) * 99);
//	free(buf[7]);
	show_alloc_mem();
	buf[3] = malloc(sizeof(char) * 2);
	buf[7] = malloc(sizeof(char) * 41);
	buf[1] = malloc(sizeof(char));
	free(buf[2]);
	buf[2] = malloc(sizeof(char) * 41);
	buf[8] = malloc(sizeof(char) * 200);
	free(buf[3]);
	show_alloc_mem();
	buf[9] = malloc(sizeof(char) * 5);
	free(buf[0]);
	free(buf[7]);
	buf[6] = malloc(sizeof(char) * 900);
	free(buf[1]);
	buf[4] = malloc(sizeof(char) * 32);
	free(buf[6]);
	free(buf[5]);
	free(buf[4]);
	free(buf[2]);
	free(buf[9]);
	buf[3] = malloc(sizeof(char) * 600);
	free(buf[8]);
	free(buf[3]);
	show_alloc_mem();
	return (1);
}


int			test_9_tiny(){
	char	*buf[10];
	
	buf[5] = malloc(sizeof(char));
	buf[7] = malloc(sizeof(char) * 4);
	buf[2] = malloc(sizeof(char) * 2);
	buf[0] = malloc(sizeof(char) * 9);
	free(buf[7]);
	//show_alloc_mem();
	buf[3] = malloc(sizeof(char) * 2);
	buf[7] = malloc(sizeof(char) * 1);
	buf[1] = malloc(sizeof(char));
	free(buf[2]);
	buf[2] = malloc(sizeof(char) * 1);
	buf[8] = malloc(sizeof(char) * 2);
	free(buf[3]);
	//show_alloc_mem();
	buf[9] = malloc(sizeof(char) * 5);
	free(buf[0]);
	free(buf[7]);
	buf[6] = malloc(sizeof(char) * 9);
	free(buf[1]);
	buf[4] = malloc(sizeof(char) * 32);
	free(buf[6]);
	free(buf[5]);
	free(buf[4]);
	free(buf[2]);
	free(buf[9]);
	buf[3] = malloc(sizeof(char) * 10000);
	free(buf[8]);
	free(buf[3]);
	//show_alloc_mem();
	return (1);
}

int			test_10_malloc_realloc(const char *s){
	int		i;
	char	*buf;
	char	*reabuf;
	int		n;

	n = strlen(s);
	buf = malloc(sizeof(char) * (n + 1));
	for (i=0;s[i];i++){
		buf[i] = s[i];
	}
	buf[n] = 0;
	reabuf = realloc(buf, sizeof(char) * (n + 1));
	reabuf[0] = '*';
	printf("%s\n%s\n", buf, reabuf);
	return (1);
}


int			test_11_malloc_realloc(const char *s){
	int		i;
	char	*buf;
	char	*reabuf;
	char	*tmp;
	int		n;

	n = strlen(s);
	buf = malloc(sizeof(char) * (n + 1));
	for (i=0;s[i];i++){
		buf[i] = s[i];
	}
	buf[n] = 0;
	tmp = malloc(sizeof(char) * 50);
	reabuf = realloc(buf, sizeof(char) * (n + 1 + 10));
	reabuf[0] = '*';
	printf("%s\n%s\n", buf, reabuf);
	return (1);
}

int			test_12_malloc_realloc(const char *s){
	int		i;
	char	*buf;
	char	*reabuf;
	char	*tmp;
	char	*b[10];
	int		n;

	n = strlen(s);
	buf = malloc(sizeof(char) * (n + 1));
	for (i=0;s[i];i++){
		buf[i] = s[i];
	}
	buf[n] = 0;
	b[5] = malloc(sizeof(char));
	b[7] = malloc(sizeof(char) * 4);
	b[2] = malloc(sizeof(char) * 2);
	b[0] = malloc(sizeof(char) * 9);
	free(b[7]);
	//show_alloc_mem();
	b[3] = malloc(sizeof(char) * 2);
	b[7] = malloc(sizeof(char) * 1);
	b[1] = malloc(sizeof(char));
	free(b[2]);
	b[2] = malloc(sizeof(char) * 1);
	b[8] = malloc(sizeof(char) * 2);
	free(b[3]);
	//show_alloc_mem();
	b[9] = malloc(sizeof(char) * 5);
	free(b[0]);
	free(b[7]);
	b[6] = malloc(sizeof(char) * 9);
	free(b[1]);
	b[4] = malloc(sizeof(char) * 32);
	//show_alloc_mem();
	tmp = malloc(sizeof(char) * 50);
	reabuf = realloc(buf, sizeof(char) * (n + 1 + 10));
	reabuf[n + 10] = 0;
	reabuf[0] = '*';
	printf("%s\n%s\n", buf, reabuf);
	free(b[6]);
	free(b[5]);
	free(b[4]);
	free(b[2]);
	free(b[9]);
	b[3] = malloc(sizeof(char) * 10000);
	free(b[8]);
	free(b[3]);

	free(reabuf);
	return (1);
}

int			test_13_realloc_inf(const char *s){
	char	*buf;
	char	*reabuf;
	int		n;
	int		i;

	n = strlen(s);
	buf = malloc(sizeof(char) * (n + 1));
	for (i=0;s[i];i++){
		buf[i] = s[i];
	}
	buf[n] = 0;
	reabuf = realloc(buf, sizeof(char) * 2);
	printf("%s\n", buf);
	reabuf[1] = 0;
	printf("%s\n", buf);
	//show_alloc_mem();
	free(buf);
	//show_alloc_mem();
	return (1);
}

int			test_14_realloc_null_size(const char *s){
	char	*buf;
	int		i;
	int		n;

	n = strlen(s);
	buf = malloc(sizeof(char) * (n + 1));
	for (i=0;s[i];i++){
		buf[i] = s[i];
	}
	buf[n] = 0;
	//show_alloc_mem();
	buf = realloc(buf, 0);
	//show_alloc_mem();
	return (1);
}

int			test_15_realloc_null_ptr(const char *s){
	char	*buf;
	int		i;
	int		n;

	n = strlen(s);
	buf = realloc(NULL, sizeof(char) * (n + 1));
	for (i=0;s[i];i++){
		buf[i] = s[i];
	}
	buf[n] = 0;
	//show_alloc_mem();
	free(buf);
	//show_alloc_mem();
	return (1);
}

int			test_16_realloc_tiny_to_small(){
	char	*buf;
	int		i;

	buf = (char*)malloc(sizeof(char) * 15);
	for (i=0;i < 15;i++){
		buf[i] = 42;
	}
	//show_alloc_mem();
	buf = realloc(buf, sizeof(char) * (__MALLOC_TINY_LIMIT__ + 1));
	//show_alloc_mem();
	free(buf);
	//show_alloc_mem();
	return (1);
}

int			test_17_realloc_small_to_tiny(){
	char	*buf;
	int		i;

	buf = malloc(sizeof(char) * (__MALLOC_TINY_LIMIT__ + 1));
	for (i=0;i < 15;i++){
		buf[i] = 42;
	}
	//show_alloc_mem();
	buf = (char*)realloc(buf, sizeof(char) * 15);
	//show_alloc_mem();
	free(buf);
	//show_alloc_mem();
	return (1);
}

int			test_18_realloc_small_to_large(){
	char	*buf;
	int		i;

	buf = (char*)malloc(sizeof(char) * (__MALLOC_SMALL_LIMIT__ + 1));
	for (i=0;i < 15;i++){
		buf[i] = 42;
	}
	//show_alloc_mem();
	buf = realloc(buf, sizeof(char) * (__MALLOC_LARGE_LIMIT__ + 1));
	//show_alloc_mem();
	free(buf);
	//show_alloc_mem();
	return (1);
}

int			test_19_realloc_large_to_small(){
	char	*buf;
	int		i;

	buf = malloc(sizeof(char) * (__MALLOC_LARGE_LIMIT__ + 1));
	for (i=0;i < 15;i++){
		buf[i] = 42;
	}
	//show_alloc_mem();
	buf = (char*)realloc(buf, sizeof(char) * (__MALLOC_SMALL_LIMIT__ + 1));
	//show_alloc_mem();
	free(buf);
	//show_alloc_mem();
	return (1);
}

int			test_20_realloc_tiny_to_large(){
	char	*buf;
	int		i;

	buf = (char*)malloc(sizeof(char) * 15);
	for (i=0;i < 15;i++){
		buf[i] = 42;
	}
	//show_alloc_mem();
	buf = realloc(buf, sizeof(char) * (__MALLOC_LARGE_LIMIT__ + 1));
	//show_alloc_mem();
	free(buf);
	//show_alloc_mem();
	return (1);
}

int			test_21_realloc_large_to_tiny(){
	char	*buf;
	int		i;

	buf = malloc(sizeof(char) * (__MALLOC_LARGE_LIMIT__ + 1));
	for (i=0;i < 15;i++){
		buf[i] = 42;
	}
	//show_alloc_mem();
	buf = (char*)realloc(buf, sizeof(char) * 15);
	//show_alloc_mem();
	free(buf);
	//show_alloc_mem();
	return (1);
}

int		main() {


	test_0_basic();
/*	test_1_fork();
	test_2_fork();
	test_3_strcat();
	
	test_4_strdup("coucou");
	//test_5_realloc("des ", "dinosaures");
	test_6_null();
	//test_7_huge_size();*/
	test_8_many_mallocs();
/*	test_9_tiny();
	test_10_malloc_realloc("salut10erferfrferfrfef");
	test_11_malloc_realloc("salut11");
	test_12_malloc_realloc("salut12");
	test_13_realloc_inf("lalala");
	test_14_realloc_null_size("le test 14");
	test_15_realloc_null_ptr("le test 15");
*/
	return (1);
}
