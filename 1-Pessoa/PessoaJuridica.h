#ifndef PESSOAJURIDICA_H
#define PESSOAJURIDICA_H

#include "Pessoa.h"

class PessoaJuridica : public Pessoa
{
public:
    PessoaJuridica();
    virtual ~PessoaJuridica();

    void SetCNPJ(string CNPJ);
    void SetRazaoSocial(string RazaoSocial);

    string GetCNPJ();
    string GetRazaoSocial();

private:
    string CNPJ, RazaoSocial;
};

#endif // PESSOAJURIDICA_H
