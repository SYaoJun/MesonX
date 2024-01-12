project('your_project', 'cpp')

# Google Test dependency
gtest_dep = dependency('gtest')

# Executable for tests
test_exe = executable(
  'test_executable',
  sources: ['tests/test_main.cpp', 'tests/add_test.cpp'],
  dependencies: gtest_dep
)

