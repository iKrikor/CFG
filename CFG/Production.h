//
//  Production.h
//  CFG
//
//  Created by Krikor Bisdikian on 12/5/15.
//  Copyright © 2015 Krikor Bisdikian. All rights reserved.
//

#ifndef Production_h
#define Production_h

#include <vector>
#include <string>

class Production
{
    public:
    std::string NT;
    std::vector<std::string> derivations;
    

    
    Production(std::string _NT){ NT = _NT; }
    
    //Función para agregar nuevas derivaciones a un No-Terminal
    void addDerivation(std::string newDerivation)
    {
        derivations.push_back(newDerivation);
    }
    
    //Función que generará una nueva derivación sin el no terminal que derivaría a nulo.
    void deleteNulls(std::string terminalToRemove)
    {
        size_t derSize = derivations.size();
        for (int i=0; i<derSize; i++)
        {
            if(derivations[i].find(terminalToRemove) < derivations[i].length())
            {
                derivations.push_back(derivations[i]);
                size_t startPos=0;
                while(std::string::npos != derivations[i].find(terminalToRemove, startPos))
                {
                    derivations[i].replace(derivations[i].find(terminalToRemove, startPos), 1, "");
                    startPos++;
                }
            }
        }
    }
};


#endif /* Production_h */
