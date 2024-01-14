project('your_project', 'cpp')

gtest_dep = dependency('gtest')

test_exe = executable(
  'test_executable',
  sources: ['tests/test_main.cpp', 'tests/add_test.cpp'],
  dependencies: gtest_dep
)

