project('locus', 'cpp',
    version: '0.1.0',
    license: 'AGPL-3.0-or-later',
    default_options : [
        'cpp_std=c++23',
        'warning_level=3',
    ]
)

inc = include_directories('include')

executable( 'locus',
'src/main.cpp',
'src/geometry.cpp',
'src/input.cpp',
'src/colors.cpp',
'src/display.cpp',
'src/solver.cpp',
include_directories : inc,
)