#!/bin/sh
LIB_PATH=/home/alricko/Projects/malloc

if [ $(uname -s) = "Linux" ]; then
  export LD_PRELOAD=$LIB_PATH/libft_malloc.so
else
  export DYLD_LIBRARY_PATH=$LIB_PATH
  export DYLD_FORCE_FLAT_NAMESPACE=1
  export DYLD_INSERT_LIBRARIES="libft_malloc.so"
fi
$@
