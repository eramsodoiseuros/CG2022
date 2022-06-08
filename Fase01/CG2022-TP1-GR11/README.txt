COMO COMPILAR COM VISUAL STUDIO:  

GENERATOR
Criar uma pasta build ou USAR pasta "buildGenerator" existente.
Usar CMake para compilar.
Correr com argumentos do generator.
Exemplo: (plane 1 3 plane.3d | box 1 5 box.3d | cone 1 2 4 3 cone.3d | sphere 1 20 20 sphere.3d)


ENGINE
Criar uma pasta build ou USAR pasta "buildEngine" existente.
Usar Cmake para compilar.
Correr com o argumento path relativo - "../models/{xmlfile}"