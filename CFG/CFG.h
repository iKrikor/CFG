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
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

class CFG
{
    std::map<std::string, std::vector<std::string>> productions;
    std::map<std::string, std::string> newProductions;
    
    std::vector<std::string> var;
    std::vector<std::string> ter;
    
public:
    void addVar(std::string _var) {
        var.push_back(_var);
    }
    
    void addTer(std::string _ter) {
        ter.push_back(_ter);
    }
    void addProduction(std::string _var, std::string der) {
        std::map<std::string, std::vector<std::string>>::iterator it;
        it = productions.find(_var);
        
        if (it != productions.end()) {
            it->second.push_back(der);
        }
        else {
            productions.insert(std::pair<std::string, std::vector<std::string>> (_var, std::vector<std::string> (1, der)));
        }
    }
    
    void addNewProduction(std::string _var, std::string der) {
        std::map<std::string, std::string>::iterator it;
        it = newProductions.find(der);
        
        if (it != newProductions.end()) {
            it->second= _var;
        }
        else {
            newProductions.insert(std::pair<std::string, std::string> (der, _var));
        }
    }
    
    void createChomsky() {
        
        int cont = 0;
        int cont2 = 0;
        int cont3 = 0;
        std::string nuevaVar = "Z";
        std::string nuevaVar2 = "Y";
        
        
        
        int numProd = productions.size();
        
        
        std::map<std::string, std::vector<std::string>>::iterator it;
        it = productions.begin();
        
        
        
        for (int i = 0; i < numProd; i++)
        {
            for (auto j: it->second)
            {
                if (j.length() == 1)
                {
                    
                    std::ostringstream oss;
                    oss << nuevaVar << cont;
                    addVar(oss.str());
                    addProduction(oss.str(), j);
                    addNewProduction(oss.str(), j);
                    cont++;
                    
                }
            }
            it++;
        }
        
        
        for (auto &variable:productions)
        {
            for (auto &terminal: variable.second)
            {
                if (terminal.length() > 1)
                {
                    for (int k = 0; k<terminal.length(); k++)
                    {
                        if (islower(terminal[k]))
                        {
                            bool found=false;
                            for (auto l:newProductions)
                            {
                                if (terminal[k]==l.first[0])
                                {
                                    found = true;
                                    size_t pos = terminal.find(l.first[0]);
                                    if(pos != std::string::npos)
                                    {
                                        
                                        terminal.erase(terminal.begin() + pos);
                                        terminal.insert(pos, l.second);
                                    }
                                }
                            }
                            if(!found)
                            {
                                std::ostringstream oss;
                                oss << nuevaVar << cont++;
                                addVar(oss.str());
                                addProduction(oss.str(), terminal.substr(k,1));
                                addNewProduction(oss.str(), terminal.substr(k,1));
                                terminal.erase(terminal.begin()+k);
                                terminal.insert(k, oss.str());

                            }
                            
                        }
                    }
                }
            }
        }
        
        for (auto &i : productions) {
            for (auto &j : i.second) {
                cont3 = 0;
                for (int k = 0; k<j.length(); k++) {
                    if (j[k] == 'Z') {
                        cont3++;
                        k++;
                    }
                    else
                    {
                        cont3++;
                    }
                }
                std::string clave = "";
                if (cont3>2){
                    if (j[0] == 'Z') {
                        
                        std::map<std::string, std::string>::iterator it;
                        it = newProductions.find(j.substr(2));
                        
                        
                        if(it == newProductions.end()){
                            std::ostringstream oss2;
                            oss2 << nuevaVar2 << cont2;
                            addVar(oss2.str());
                            addProduction(oss2.str(), j.substr(2));
                            addNewProduction(oss2.str(), j.substr(2));
                            j=j.substr(0,2)+ oss2.str();
                            cont2++;
                        }
                        else
                        {
                            j = j.substr(0,2)+ it->second;
                        }
                    }
                    else {
                        std::map<std::string, std::string>::iterator it;
                        it = newProductions.find(j.substr(1));
                        
                        
                        if(it == newProductions.end()){
                            std::ostringstream oss2;
                            oss2 << nuevaVar2 << cont2;
                            addVar(oss2.str());
                            addProduction(oss2.str(), j.substr(1));
                            addNewProduction(oss2.str(), j.substr(1));
                            j=j.substr(0,1)+ oss2.str();
                            cont2++;
                        }
                        else
                        {
                            j = j.substr(0,1)+ it->second;
                        }
                    }
                }
            }
        }
        
        
    }
    
    bool ultimaFuncionDelSemestre(std::string input)
    {
        
        std::sort(var.begin(), var.end());
        
        int n = input.length();
        int r = var.size();
        
        std::vector<std::vector<std::vector<bool>>> P(n, std::vector<std::vector<bool>>(n, std::vector<bool>(r, false)));
        
        
        
        for (int i = 0; i<n ; i++)
        {
            for(std::map<std::string, std::vector<std::string>>::iterator j = productions.begin(); j != productions.end(); j++)
            {
                for (auto b : j->second)
                {
                    if(islower(b[0]))
                    {
                        if(input[i] == b[0])
                        {
                            int f;
                            for (f =0; f<var.size(); f++) {
                                if (var[f] == j->first) {
                                    break;
                                }
                            }
                            P[0][i][f] = true;
                        }
                    }
                }
            }
        }
        
        for (int i =1; i < n; i++)
        {
            for (int j =0; j<n-i; j++)
            {
                for (int k=0; k<i; k++)
                {
                    for(std::map<std::string, std::vector<std::string>>::iterator a = productions.begin(); a != productions.end(); a++)
                    {
                            for (auto str : a->second)
                            {
                                std::string auxStr="";
                                std::string auxStr2="";
                                if (str[0] == 'Y' || str[0] == 'Z'){
                                    auxStr = str.substr(0,2);
                                    if (str[2] == 'Y' || str[2] == 'Z') {
                                        auxStr2 = str.substr(2,2);
                                    }
                                    else
                                    {
                                        auxStr2 = str[2];
                                    }
                                }
                                else
                                {
                                    auxStr = str.substr(0,1);
                                    if (str[1] == 'Y' || str[1] == 'Z') {
                                        auxStr2 = str.substr(1,2);
                                    }
                                    else
                                    {
                                        auxStr2 = str[1];
                                    }
                                }
                                
                                int B;
                                int C;
                                for (int z =0; z< var.size(); z++)
                                {
                                    if(var[z] == auxStr){
                                        B=z;
                                    }
                                    if (var[z] == auxStr2) {
                                        C=z;
                                    }
                                }
                                
                                
                                if(P[k][j][B] && P[i-k-1][j+k+1][C])
                                {
                                    P[i][j][std::distance(productions.begin(), a)] = true;
                                }
                            }
                    }
                }
            }
        }
        
        
        int i;
        for (i=0; i<var.size();i++)
        {
            if (var[i] == "S")
            {
                break;
            }
        }
        return (P[n-1][0][i]);
        
    }
    
    void printCFG()
    {
        for ( auto i : productions ){
            
            std::cout << i.first << "->";
            
            for (auto j : i.second)
            {
                std::cout << j << "|";
            }
            std::cout << std::endl;
        }
    }
    
    
};

#endif /* CFG_ha */
