#ifndef PESSOA_H
#define PESSOA_H

#include <iostream>
using namespace std;

class Pessoa
{
public:
    Pessoa();

    void SetNome(string Nome);
    string GetNome();

protected:
    string Nome;
};

#endif // PESSOA_H
