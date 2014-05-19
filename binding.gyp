{
  "targets": [
    {
      "target_name": "GrumpyGolem",
      "sources": ['src/gg.cpp',
                  'src/matrix.cpp'
                 
      ],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'libraries' : ['-llapack','-lblas','-larmadillo']
    }
  ],
   
}
