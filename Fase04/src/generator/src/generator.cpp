#define _USE_MATH_DEFINES

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <string>

#include "../headers/plane.h"
#include "../headers/box.h"
#include "../headers/sphere.h"
#include "../headers/cone.h"
#include "../headers/patch.h"

using namespace std;


void help(){

        cout << "Por favor selecione um dos modelos disponiveis:\n";
        cout << "\t./generator plane <length> <divisions> <output_file>.3d\n";
        cout << "\t./generator box <units> <divisions> <output_file>.3d\n";
        cout << "\t./generator sphere <radius> <slices> <stacks> <output_file>.3d\n";
        cout << "\t./generator cone <bottom_radius> <height> <slices> <stacks> <output_file>.3d\n";
        cout << "\t./generator patch <patch name> <tesselation level> <output_file>.3d\n";
}


int input_valido(char* input, const std::vector<std::string>& inputs){
    for(auto & i : inputs){
        if(strcmp(input, i.c_str()) == 0)
            return 1;
    }
    return 0;
}


int main(int argc, char** argv){
    
    char* output_file = nullptr;

    std::vector<std::string> modelos = {"plane", "box", "sphere", "cone", "patch"};


    if (argc == 2 && !strcmp(argv[1], "help")){
        help();
        exit(0);
    }

    if(argc >= 5 && input_valido(argv[1], modelos)){

        if(!strcmp(argv[1], "plane") && argc == 5){
            
            Plane p = Plane(atof(argv[2]), atoi(argv[3]), true);
            output_file = strdup(argv[4]);
            p.toFile(output_file);
        }

        else if(!strcmp(argv[1], "box") && argc == 5){

            Box p = Box(atof(argv[2]), atoi(argv[3]));
            output_file = strdup(argv[4]);
            p.toFile(output_file);
        }

        else if(!strcmp(argv[1], "sphere") && argc == 6){
            
            Sphere p = Sphere(atof(argv[2]), atoi(argv[3]), atof(argv[4]));
            output_file = strdup(argv[5]);
            p.toFile(output_file);
        }
    
        else if(!strcmp(argv[1], "cone") && argc == 7){

            Cone p = Cone(atof(argv[2]), atof(argv[3]), atof(argv[4]), atoi(argv[5]));
            output_file = strdup(argv[6]);
            p.toFile(output_file);
        }

        else if (!strcmp(argv[1], "patch") && argc == 5){
            
            string input = string(argv[2]);
            string output = string(argv[4]);
            Patch patch = Patch(input, atoi(argv[3]), output);
            patch.toFile();
        }
        else{

            cout << "\nInput invalido\n";
            help();
            return(1);
        }

    } else {
        cout << "\nInput invalido.\n";
        help();
        return(1);
    }
}