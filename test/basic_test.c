#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "../libft/libft.h"


int main() {
  struct rlimit rlim;

  /*
  * * Recuper la taille maximale du segment de données d'un processus
  */
  getrlimit(RLIMIT_DATA, &rlim);

  srand(time(NULL));

  for (;;) {
    void *ptr = malloc(rand() % rlim.rlim_cur);

    void *ptr_reallocated = realloc(ptr, rand() % rlim.rlim_cur);

    free(ptr);

    if (ptr != ptr_reallocated) {
      free(ptr_reallocated);
    }

    ft_putstr("freeptr done\n");
  }

  return 0;
}
