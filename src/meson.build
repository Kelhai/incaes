aes_sources = [
  'rijndael.c',
  'cipher.c',
  'key_expansion.c',
  'helper.c',
]

aes_lib = library(
  'aes',
  aes_sources,
  include_directories: [
    inc,
    include_directories('internal')
  ],
  c_args: ['-DAES_INTERNAL'],
  install: false
)

aes_dep = declare_dependency(
  link_with: aes_lib,
  include_directories: inc
)

