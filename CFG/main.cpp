//
//  main.cpp
//  CFG
//
//  Created by Krikor Bisdikian on 12/5/15.
//  Copyright © 2015 Krikor Bisdikian. All rights reserved.
//

#include <iostream>
#include "CFG.h"


int main(int argc, const char * argv[]) {
    
    CFG gramatica;
    
    //1. Sustituir por las variables incluidas en su gramática.
    gramatica.addVar("S");
    
    //2. Sustituir por los terminales que existen en su gramática.
    gramatica.addTer("a");
    gramatica.addTer("b");

    
    //3.Sustituit por las producciones que incluye su gramática.
    gramatica.addProduction("S", "aSb");
    gramatica.addProduction("S", "ab");
    
    
    
    gramatica.createChomsky();
    
    
    //4.Sustituir por el string que quiere comprobar
    if(gramatica.ultimaFuncionDelSemestre("aaaabbbb"))
    {
        std::cout<<"Sí es parte de la gramática."<<std::endl;
    }
    else
    {
        std::cout<<"No es parte de la gramática."<<std::endl;
    }
    
    return 0;
}
