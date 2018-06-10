#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "../libft/libft.h"
#include "../src/include/malloc.h"


int main() {
        struct rlimit rlim;


        srand(time(NULL));


        /*
         * * Recuper la taille maximale du segment de données d'un processus
         */
        getrlimit(RLIMIT_DATA, &rlim);


        void *ptr = malloc(rand() % rlim.rlim_cur);

        void *ptr_reallocated = realloc(ptr, rand() % rlim.rlim_cur);

        free(ptr);

        if (ptr != ptr_reallocated) {
                free(ptr_reallocated);
        }

        show_alloc_mem();

        ft_putstr("freeptr done\n");

        return 0;
}
