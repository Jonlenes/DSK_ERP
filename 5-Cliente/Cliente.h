#ifndef CLIENTE_H
#define CLIENTE_H

#include "1-Pessoa/PessoaFisica.h"

class Cliente : public PessoaFisica
{
public:
    Cliente();

    void SetTelefone(string Telefone);
    void SetEndereco(string Endereco);

    string GetTelefone();
    string GetEndereco();

private:
    string Telefone;
    string Endereco;
};

#endif // CLIENTE_H
