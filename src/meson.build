aes_sources = [
  'cipher.c'
]

aes_lib = library(
  'aes',
  aes_sources,
  include_directories: inc,
  install: false
)

aes_dep = declare_dependency(
  link_with: aes_lib,
  include_directories: inc
)

