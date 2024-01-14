project('main', 'cpp')

my_add_lib = shared_library(
  'myadd', 
  ['math/add.cpp', 'math/add.h']
)

executable('main', 'main.cpp', link_with: my_add_lib)

