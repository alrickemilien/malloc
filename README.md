# Malloc - Realloc - Free - Calloc

## Installation
  1. Compile the library malloc.so with `make`
  2. Run `sh` to use a shell that dont use its own malloc
  3. Change your environnements variables with `source run.sh`
  4. Or run `sh run.sh [args]` with [args] the binarys you want to exec with malloc's funcs
  5. Be careful, some programs use other functions than malloc or realloc to allocate memory
  For example, /bin/ls of the library used on MacOS use reallocf, zsh use its own allocation functions, sh and bash use mmap in addition to malloc
