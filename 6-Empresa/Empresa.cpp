#include "Empresa.h"
#include <typeinfo>
#include <QLabel>
#include <QDebug>

Empresa::Empresa(QWidget *Atual)
{
    ListFunc = new Lista<Funcionario*>;
    ListCliente = new Lista<Cliente*>;
    OperaBd = new Conexao_BD;
    OperaBd->SetConectBD(db, Atual);
    TransferenciaBD(1);
}

Empresa::~Empresa()
{
    TransferenciaBD(2);
    OperaBd->CloseBD(db);
}

void Empresa::AddPessoa(Funcionario *Func)
{
     ListFunc->InsertBegin(Func);
}

void Empresa::AddPessoa(Cliente *Client)
{
    ListCliente->InsertBegin(Client);
}

void Empresa::MostraFuncionarios(QTableWidget *Qtw)
{
    int qtdeLinas = Qtw->rowCount();
    for(int i = qtdeLinas - 1; i >= 0; i--)
        Qtw->removeRow(i);

        Funcionario *aux;
        int Tam = ListFunc->Size();
        for(int i = 0; i < Tam; i++){
            ListFunc->Search(i, aux);
            Qtw->insertRow(Qtw->rowCount());

            Qtw->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(aux->GetNome())));
            Qtw->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(aux->GetCPF())));
            Qtw->setItem(i, 3, new QTableWidgetItem(QString::number(aux->GetMatricula())));
            Qtw->setItem(i, 4, new QTableWidgetItem(QString::number(aux->GetSalarioBase())));
            Qtw->setItem(i, 5, new QTableWidgetItem(QString::number(aux->GetQtdeHsMensais())));
            Qtw->setItem(i, 6, new QTableWidgetItem(QString::number(aux->GetHorasTrab())));

            if(typeid(*aux) == typeid(Gerente))
            {
				Qtw->setItem(i, 0, new QTableWidgetItem("Gerente"));
                Qtw->setItem(i, 7, new QTableWidgetItem(QString::number(((Gerente*)aux)->GetQtdeFuncGereciados())));
			}else 
                if(typeid(*aux) == typeid(Estagiario))
				{
					Qtw->setItem(i, 0, new QTableWidgetItem("Estagiário"));
                    Qtw->setItem(i, 7, new QTableWidgetItem("-"));
                }else
				{
					Qtw->setItem(i, 0, new QTableWidgetItem("Padrao"));
					Qtw->setItem(i, 7, new QTableWidgetItem("-"));
				}
        }
}

void Empresa::MostraClientes(QTableWidget *Qtw)
{
    int qtdeLinas = Qtw->rowCount();
    for(int i = qtdeLinas - 1; i >= 0; i--)
        Qtw->removeRow(i);

    Cliente *aux;
    int Tam = ListCliente->Size();
    for(int i = 0; i  < Tam; i++)
    {
        ListCliente->Search(i, aux);
        Qtw->insertRow(Qtw->rowCount());
        Qtw->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(aux->GetNome())));
        Qtw->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(aux->GetCPF())));
        Qtw->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(aux->GetTelefone())));
        Qtw->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(aux->GetEndereco())));

    }
}

void Empresa::CalcularFolhaDePagamento(QTableWidget *Qtw, QLabel *Label)
{
    int qtdeLinas = Qtw->rowCount();
    for(int i = qtdeLinas - 1; i >= 0; i--)
        Qtw->removeRow(i);

    Funcionario *Func;
    int Tam = ListFunc->Size();
    double Salario, Soma = 0;
    for(int i = 0; i < Tam; i++){
        ListFunc->Search(i, Func);
        Salario = Func->CalculaSalarioBruto();
        Soma = Soma + Salario;

        Qtw->insertRow(Qtw->rowCount());
        Qtw->setItem(i, 0, new QTableWidgetItem(QString::number(Func->GetMatricula())));
        Qtw->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(Func->GetNome())));
        Qtw->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(Func->GetCPF())));
        Qtw->setItem(i, 3, new QTableWidgetItem(QString::number(Salario)));
    }
    Label->setText("Total a ser gasto com os funcionários = " + QString::number(Soma));
}


//Métodos extras que não forma pedidos pelo professor;
void Empresa::TransferenciaBD(int Index)
{
    QSqlQuery Qry;
    QString StrQry;

    if(Index == 1){ //Carrega os Funcionarios e clientes salvos no BD para as listas

        StrQry = "SELECT * FROM Funcionarios ORDER BY(Nome)";
        OperaBd->Consulta(StrQry, Qry);
        while(Qry.next()){
            if(Qry.value(1).toInt() == 1){ //Gerente

                Gerente *Ger = new Gerente;
                Geral *geral = new Geral;
                string senha;

                Ger->SetCPF(Qry.value(4).toString().toStdString());
                Ger->SetNome(Qry.value(3).toString().toStdString());
                Ger->SetMatricula(Qry.value(2).toString().toLong());
                Ger->SetSalarioBase(Qry.value(5).toDouble());
                Ger->SetQtdeHsMensais(Qry.value(6).toInt());
                Ger->SetQtdeHorasTrab(Qry.value(7).toInt());
                Ger->SetQtdeFuncGereciados(Qry.value(8).toInt());
                senha = Qry.value(10).toString().toStdString();
                geral->criptografia(senha, 11);
                Ger->AlterarSenha(senha);

                ListFunc->InsertBegin(Ger);
                delete geral;

            }else
                if(Qry.value(1).toInt() == 2) //Padrão
                {
                    Funcionario *Func = new Funcionario;
                    Func->SetCPF(Qry.value(4).toString().toStdString());
                    Func->SetNome(Qry.value(3).toString().toStdString());
                    Func->SetMatricula(Qry.value(2).toString().toLong());
                    Func->SetSalarioBase(Qry.value(5).toDouble());
                    Func->SetQtdeHsMensais(Qry.value(6).toInt());
                    Func->SetQtdeHorasTrab(Qry.value(7).toInt());

                    ListFunc->InsertBegin(Func);

                }else{ // Estagiario

                    Estagiario *Est = new Estagiario;
                    Est->SetCPF(Qry.value(4).toString().toStdString());
                    Est->SetNome(Qry.value(3).toString().toStdString());
                    Est->SetMatricula(Qry.value(2).toString().toLong());
                    Est->SetSalarioBase(Qry.value(5).toDouble());
                    Est->SetQtdeHsMensais(Qry.value(6).toInt());
                    Est->SetQtdeHorasTrab(Qry.value(7).toInt());
                    Est->SetTipo(Qry.value(0).toInt());
                    Est->SetTempoContratoRestante(Qry.value(11).toFloat());

                    ListFunc->InsertBegin(Est);
                }
        }
        StrQry = "DELETE FROM Funcionarios";
        OperaBd->Consulta(StrQry, Qry);

        StrQry = "SELECT * FROM Clientes ORDER BY(Nome)";
        OperaBd->Consulta(StrQry, Qry);
        while(Qry.next()){
            Cliente * Cli = new Cliente;

            Cli->SetNome(Qry.value(1).toString().toStdString());
            Cli->SetCPF(Qry.value(2).toString().toStdString());
            Cli->SetTelefone(Qry.value(3).toString().toStdString());
            Cli->SetEndereco(Qry.value(4).toString().toStdString());

            ListCliente->InsertBegin(Cli);

        }
        StrQry = "DELETE FROM Clientes";
        OperaBd->Consulta(StrQry, Qry);

    }else{ //Carrega os dados da lista para o BD
        Funcionario *aux;
        int Tam = ListFunc->Size();
        QString aux2;

        for(int i = 0; i < Tam; i++){
            ListFunc->Search(i, aux);

            StrQry = "INSERT INTO Funcionarios";
            StrQry = StrQry + " VALUES (" + QString::number(i) +  ",";
            aux2 =  ", '" + QString::number(aux->GetMatricula());
            aux2 = aux2 + "', '" + QString::fromStdString(aux->GetNome());
            aux2 = aux2 + "', '" + QString::fromStdString(aux->GetCPF());
            aux2 = aux2 + "', " + QString::number(aux->GetSalarioBase());
            aux2 = aux2 + ", " + QString::number(aux->GetQtdeHsMensais());
            aux2 = aux2 + ", " + QString::number(aux->GetHorasTrab());

            if(typeid(*aux) == typeid(Gerente))
            {
                StrQry = StrQry + " 1 ";
                aux2 = aux2 + ", " + QString::number(((Gerente*) aux)->GetQtdeFuncGereciados());
                aux2 = aux2 + ", NULL, '" + QString::fromStdString(((Gerente*) aux)->GetSenhaCriptografada()) + "', NULL)";

            }else
                if(typeid(*aux) == typeid(Estagiario))
                {
                    StrQry = StrQry + " 3 ";
                    aux2 = aux2 + ", NULL," + QString::number(((Estagiario*)aux)->GetTipo()) + ", NULL, ";
                    aux2 = aux2 + QString::number(((Estagiario*) aux)->GetTempoContratoRestante()) + ")";

                }else
                {
                    StrQry = StrQry + " 2 ";
                    aux2 = aux2 + ", NULL, NULL, NULL, NULL)";
                }
            StrQry = StrQry + aux2;
            OperaBd->Consulta(StrQry, Qry);
        }



        Cliente *Cli;
        int Tam1 = ListCliente->Size();

        for(int i = 0; i < Tam1; i++){
            ListCliente->Search(i, Cli);

            StrQry = "INSERT INTO Clientes ";
            StrQry = StrQry + " VALUES (";
            StrQry = StrQry + QString::number(i) + ", '";
            StrQry = StrQry + QString::fromStdString(Cli->GetNome()) + "', '";
            StrQry = StrQry + QString::fromStdString(Cli->GetCPF()) + "', '";
            StrQry = StrQry + QString::fromStdString(Cli->GetTelefone()) + "', '";
            StrQry = StrQry + QString::fromStdString(Cli->GetEndereco()) + "')";

            OperaBd->Consulta(StrQry, Qry);
        }
    }
}

void Empresa::ExcluiPessoa(int Tipo, int Index)
{
    if(Tipo == 1) //Exclui Funcionario de Index Index
        ListFunc->Romove(Index);
    else  //Exclui Cliente de Index Index
        ListCliente->Romove(Index);
}

bool Empresa::AutenticaGerente(long Mat, string Senha, Gerente* &Ger)
{
    int Tam = ListFunc->Size();
    Funcionario *Func;

    for(int i = 0; i < Tam; i++){
        ListFunc->Search(i, Func);
        if(typeid(*Func) == typeid(Gerente)){
            if(Func->GetMatricula() == Mat && ((Gerente*)Func)->Autenticar(Senha)){
                Ger = (Gerente*)Func;
                return true;
            }
        }
    }
    return false;
}
