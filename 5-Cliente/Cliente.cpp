#include "Cliente.h"

Cliente::Cliente()
{
}

void Cliente::SetTelefone(string Telefone)
{
    this->Telefone = Telefone;
}

void Cliente::SetEndereco(string Endereco)
{
    this->Endereco = Endereco;
}

string Cliente::GetTelefone()
{
    return this->Telefone;
}

string Cliente::GetEndereco()
{
    return this->Endereco;
}
