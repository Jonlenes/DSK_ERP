#include "PessoaJuridica.h"
#include <iostream>
using namespace std;

PessoaJuridica::PessoaJuridica()
{
}

PessoaJuridica::~PessoaJuridica()
{

}

void PessoaJuridica::SetCNPJ(string CNPJ)
{
    this->CNPJ = CNPJ;
}

void PessoaJuridica::SetRazaoSocial(string RazaoSocial)
{
        this->RazaoSocial = RazaoSocial;
}

string PessoaJuridica::GetCNPJ()
{
    return this->CNPJ;
}

string PessoaJuridica::GetRazaoSocial()
{
    return this->RazaoSocial;
}
