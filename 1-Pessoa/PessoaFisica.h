#ifndef PESSOAFISICA_H
#define PESSOAFISICA_H

#include "Pessoa.h"

class PessoaFisica : public Pessoa
{
public:
    PessoaFisica();
    virtual ~PessoaFisica();

    void SetCPF(string CPF);
    string GetCPF();

private:
    string CPF;
};

#endif // PESSOAFISICA_H
