#include "PessoaFisica.h"

PessoaFisica::PessoaFisica()
{
}

PessoaFisica::~PessoaFisica()
{

}

void PessoaFisica::SetCPF(string CPF)
{
    this->CPF = CPF;
}

string PessoaFisica::GetCPF()
{
    return this->CPF;
}
