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
    gramatica.addVar("S");
//    gramatica.addVar("A");
//    gramatica.addVar("B");
    
    gramatica.addTer("a");
    gramatica.addTer("b");
    
    //  gramatica.addProduction("S", "bA");
    //  gramatica.addProduction("S", "aB");
    //  gramatica.addProduction("A", "bAA");
    //  gramatica.addProduction("A", "aS");
    //  gramatica.addProduction("A", "a");
    //  gramatica.addProduction("B", "aBB");
    //  gramatica.addProduction("B", "bS");
    //  gramatica.addProduction("B", "b");
    
    
      gramatica.addProduction("S", "aSa");
      gramatica.addProduction("S", "bSb");
      gramatica.addProduction("S", "aa");
      gramatica.addProduction("S", "bb");
      gramatica.addProduction("S", "a");
      gramatica.addProduction("S", "b");
    
//    gramatica.addProduction("S", "aB");
//    gramatica.addProduction("S", "bA");
//    gramatica.addProduction("A", "a");
//    gramatica.addProduction("A", "bS");
//    gramatica.addProduction("A", "bAA");
//    gramatica.addProduction("B", "b");
//    gramatica.addProduction("B", "bS");
//    gramatica.addProduction("B", "aBB");
    
    gramatica.createChomsky();
    
    
    gramatica.printCFG();
    
    if(gramatica.ultimaFuncionDelSemestre("abba"))
    {
        std::cout<<"pene"<<std::endl;
    }
    
    return 0;
}
