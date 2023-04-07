project('threads', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

src = [
    'src/main.c',
    'src/thread.c',
]

includes = include_directories('include')
executable('threads',
           src,
           include_directories : includes,
           install : true)
