#ifndef EMPRESA_H
#define EMPRESA_H

#include "1-Pessoa/PessoaJuridica.h"
#include "0-Auxiliares/Lista.h"
#include "0-Auxiliares/Conexao_BD.h"
#include "5-Cliente/Cliente.h"
#include "2-Funcionario/Funcionario.h"
#include "3-Gerente/Gerente.h"
#include "4-Estagiario/Estagiario.h"
#include <QTableWidget>
#include <QSql>

class Empresa : public PessoaJuridica
{
public:
    Empresa(QWidget *Atual);
    ~Empresa();

    void AddPessoa(Funcionario *Func);
    void AddPessoa(Cliente *Client);

    void MostraFuncionarios(QTableWidget *Qtw);
    void MostraClientes(QTableWidget *Qtw);

    void CalcularFolhaDePagamento(QTableWidget *Qtw, QLabel *Label);

    //Métodos que foram pedido pelo professor
    void TransferenciaBD(int Index);
    void ExcluiPessoa(int Tipo, int Index);
    bool AutenticaGerente(long Mat, string Senha, Gerente* &Ger);

private:
    Lista<Funcionario*> *ListFunc;
    Lista<Cliente*> *ListCliente;
    Conexao_BD *OperaBd;
    QSqlDatabase db;
};

#endif // EMPRESA_H
