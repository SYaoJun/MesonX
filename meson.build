project('demo', 'cpp')


my_add_lib = shared_library(
  'myadd', 
  ['math/add.cpp', 'math/add.h']
)

# Google Test dependency
gtest_dep = dependency('gtest')

# Executable for tests
test_exe = executable(
  'test_executable',
  sources: ['tests/test_main.cpp', 'tests/add_test.cpp'],
  dependencies: gtest_dep,
  link_with: my_add_lib
)

