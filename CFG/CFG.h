//
//  CFG.hpp
//  CFG
//
//  Created by Krikor Bisdikian on 12/5/15.
//  Copyright © 2015 Krikor Bisdikian. All rights reserved.
//

#ifndef CFG_h
#define CFG_h

#include <stdio.h>
#include <map>
#include <string>
#include <vector>

class CFG
{
    std::map<std::string, std::vector<std::string>> productions;
    std::vector<std::string> var;
    std::vector<std::string> ter;
    
public:
    void addVar(std::string _var)
    {
        var.push_back(_var);
    }
    
    void addTer(std::string _ter)
    {
        ter.push_back(_ter);
    }
    void addProduction(std::string _var, std::string der)
    {
        std::map<std::string, std::vector<std::string>>::iterator it;
        it = productions.find(_var);
        
        if (it != productions.end())
        {
            it->second.push_back(der);
        }
        else
        {
            productions.insert(std::pair<std::string, std::vector<std::string>> (_var, std::vector<std::string> (1, der)));
        }
    }
    
    void removeNullProductions()
    {
        //Hay que hacer algo recursivo o si no algo por el estilo son 2 a la n producciones. N siendo el número de veces que aparezca la variable que puede ser nula.
    }
    
    void removeUnitProductions ()
    {
        
    }
    
    void printCFG()
    {
        
    }
    
};

#endif /* CFG_ha */
