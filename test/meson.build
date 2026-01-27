inc = include_directories('../include')
internal_inc = include_directories('../src')
test_inc = include_directories('.')

tests = ['aes_kat_test', 'aes_cipher_test']

foreach t : tests
  exe = executable(
    t,
    t + '.c',
    dependencies: aes_dep,
    include_directories: [inc, internal_inc, test_inc],
    c_args: ['-DAES_INTERNAL', '-DAES_TESTING']
  )

  test(t, exe)
endforeach

