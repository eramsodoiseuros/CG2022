#include <string>
#include <vector>
#include <iostream>
#include "../../headers/figures.h"

/**
 * @brief adiciona uma nova primitiva
 * 
 * @param p 
 * @return int 
 */
int Figures::addPrimitive(Primitive prim){

    for (Primitive p : primitives)
        if (!prim.getFilename().compare(p.getFilename())) {
            cout << "\n#> esta primitiva já se encontra guardada" << endl;
            return 1;
        }
    
    primitives.push_back(prim.clone());
    return 0;
}

/**
 * @brief adiciona uma nova primitiva
 * 
 * @param file3d 
 */
int Figures::addPrimitive(string file3d){

    Primitive primitive = Primitive(file3d);
    
    for (Primitive p : primitives)
        if (!primitive.getFilename().compare(p.getFilename())) {
            //cout << "\n#> esta primitiva já se encontra guardada" << endl;
            return 1;
        }
    
    primitives.push_back(primitive.clone());
    return 0;
}



/**
 * @brief remove uma primitiva
 * 
 * @param prim 
 * @return int 
 */
int Figures::removePrimitive(Primitive prim){

    int i = 0;
    for (Primitive p : primitives){
        if (!(p.getFilename().compare(prim.getFilename()))) {

            primitives.erase(primitives.begin() + i);
            return 0;
        }
        i++;
    }

    cout << "\n#> esta primitiva não se encontra guardada" << endl;
    return 1;
}

/**
 * @brief remove uma primitiva
 * 
 * @param file3d 
 * @return int 
 */
int Figures::removePrimitive(string file3d){
       
    int i = 0;
    for (Primitive p : primitives){
        if (!file3d.compare(p.getFilename())) {

            primitives.erase(primitives.begin() + i);
            return 0;
        }
        i++;
    }

    cout << "\n#> esta primitiva não se encontra guardada" << endl;
    return 1;    
}


Primitive Figures::getPrimitive(string file3d){

    for (Primitive p : primitives){

        if (!p.getFilename().compare(file3d)){

            return p.clone();
        }
    }
    return nullptr;
}


/**
 * @brief devolve o primeiro plano presente na lista das primitivas
 * 
 */
Primitive Figures::getPlane(){

    for (Primitive p : primitives){

        if (!p.getPrimitiveName().compare("plane")){

            return p.clone();
        }
    }
    return nullptr;
}

/**
 * @brief devolve a primeira box presente na lista das primitivas
 * 
 */
Primitive Figures::getBox(){

    for (Primitive p : primitives){

        if (!p.getPrimitiveName().compare("box")){

            return p.clone();
        }
    }
    return nullptr;
}

/**
 * @brief devolve o primeiro cone presente na lista das primitivas
 * 
 */
Primitive Figures::getCone(){

    for (Primitive p : primitives){

        if (!p.getPrimitiveName().compare("cone")){

            return p.clone();
        }
    }
    return nullptr;
}

/**
 * @brief devolve a primeira sphere presente na lista das primitivas
 * 
 */
Primitive Figures::getSphere(){

    for (Primitive p : primitives){

        if (!p.getPrimitiveName().compare("sphere")){

            return p.clone();
        }
    }
    return nullptr;
}

int Figures::getSize() {

    return primitives.size();
}