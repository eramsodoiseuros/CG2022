#define _USE_MATH_DEFINES

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "plane.h"
#include "box.h"
#include "sphere.h"
#include "cone.h"
#include <string>
#include <iostream>

int input_valido(char* input, const std::vector<std::string>& inputs){
    for(auto & i : inputs){
        if(strcmp(input, i.c_str()) == 0)
            return 1;
    }

    return 0;
}

int main(int argc, char** argv){
    char* output_file = nullptr;

    std::vector<std::string> modelos = {"plane", "box", "sphere", "cone"};

    if(argc > 1 && input_valido(argv[1], modelos)){

        if(strcmp(argv[1], "plane") == 0){
            Plane p = Plane();
            output_file = strdup(argv[2]);
            p.toFile(output_file);
        }

        if(strcmp(argv[1], "box") == 0){
            Box p = Box(atof(argv[2]), atof(argv[3]), atof(argv[4]), atoi(argv[5]));
            output_file = strdup(argv[6]);
            p.toFile(output_file);
        }

        if(strcmp(argv[1], "sphere") == 0){
            Sphere p = Sphere(atof(argv[2]), atoi(argv[3]), atof(argv[4]));
            output_file = strdup(argv[5]);
            p.toFile(output_file);
        }

        if(strcmp(argv[1], "cone") == 0){
            Cone p = Cone(atof(argv[2]), atof(argv[3]), atof(argv[4]), atoi(argv[5]));
            output_file = strdup(argv[6]);
            p.toFile(output_file);
        }

    } else {
        std::cout << "Input invalido.\n";
        std::cout << "Por favor selecione um dos modelos disponiveis:";
        std::cout << "\t./generator plane <output_file>.3d\n";
        std::cout << "\t./generator box <x> <y> <z> <divisions> <output_file>.3d\n";
        std::cout << "\t./generator sphere <radius> <stacks> <slices> <output_file>.3d\n";
        std::cout << "\t./generator cone <bottom_radius> <height> <stacks> <slices> <output_file>.3d\n";
    }
}