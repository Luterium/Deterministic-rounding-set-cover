#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "subconjunto.h"
#include <queue>
#define EPS 0.0001

using namespace std;

bool comparaFloats(float i, float j){
    if(i > j-EPS && i < j+EPS)
        return true;
    return false;
}

void trataInput(char inputName[], char LPPath[]){
    cout << inputName << endl << endl << LPPath << endl;
    int n, m, auxWeight, auxQtdSubsets, auxSubset;
    int totalWeight = 0;
    float deterministicFrequency = 0;
    double LPWeight, auxLP;

    ifstream inputSCP;
    inputSCP.open(inputName);
    inputSCP >> n >> m;

    //fstream costLog;
    //costLog.open("costLogDeterministicRounding.txt", std::fstream::in | std::fstream::out | std::fstream::app);

    vector <Subset> Subsets(m);
    vector < vector <int> > elementos(n);
    
    //vector <int> subconjuntosEscolhidos;



    for(int i = 0; i < m; i++){
        inputSCP >> auxWeight;
        Subsets[i].setWeight(auxWeight);
    }

    for (int i = 0; i < n; i++){
        inputSCP >> auxQtdSubsets;

        if(deterministicFrequency < auxQtdSubsets)
            deterministicFrequency = auxQtdSubsets;

        for(int j = 0; j < auxQtdSubsets; j++){
            inputSCP >> auxSubset;
            elementos[i].push_back(auxSubset-1);
            Subsets[auxSubset-1].incrementSize();
            Subsets[auxSubset-1].adicionaElemento(i);
        }
    }
    inputSCP.close();
    ifstream LPFile;
    LPFile.open(LPPath);

    LPFile >> LPWeight;
    cout << LPWeight << endl;
    int freq = deterministicFrequency;
    deterministicFrequency = 1/deterministicFrequency;
    for(int i = 0; i < m; i++){
        LPFile >> auxLP;

        if(auxLP > deterministicFrequency){
            totalWeight += Subsets[i].getWeight();
            //subconjuntosEscolhidos.push_back(i)
        }
        
    }

    cout << "Total cover cost: " << totalWeight << endl;
    //costLog << freq << endl;
    inputSCP.close();
    LPFile.close();
    //costLog.close();
    /*for(unsigned int i = 0; i < subconjuntosEscolhidos.size(); i++){
        cout << subconjuntosEscolhidos[i]+1 << " ";
    }*/
}
