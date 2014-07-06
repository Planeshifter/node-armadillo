{
  "targets": [
    {
      "target_name": "armadillo",
      "sources": ['src/gg.cpp', 
                  'src/matrix.cpp',
                  'src/helper.cpp',
      ],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'libraries' : ['-llapack','-lblas','-larmadillo']
    }
  ],
   
}
