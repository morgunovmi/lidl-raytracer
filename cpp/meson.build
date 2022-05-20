project('raytracer', 'cpp',
        default_options: ['default_library=static', 'cpp_std=c++2a']
        )

incdir = include_directories('src')

fmt_dep = dependency('fmt')

sources = files([
  './src/main.cpp',
  './src/math/math.cpp',
  ])

executable('app', sources,
           include_directories : incdir,
           dependencies: fmt_dep)
