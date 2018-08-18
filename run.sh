#!/bin/bash

LIB_PATH=$(pwd)

if [ $(uname -s) = "Linux" ]; then
  export LD_PRELOAD=$LIB_PATH/libft_malloc.so
  export LD_LIBRARY_PATH=$LIB_PATH
else
  export DYLD_LIBRARY_PATH=$LIB_PATH
  export DYLD_FORCE_FLAT_NAMESPACE=1
  export DYLD_INSERT_LIBRARIES="libft_malloc.so"
fi
$@
