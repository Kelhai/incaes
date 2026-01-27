test_exe = executable(
  'aes_tests',
  'aes_kat_test.c',
  dependencies: aes_dep,
  include_directories: [
    inc,
    include_directories('../src')
  ]
)

test('AES test vectors', test_exe)

