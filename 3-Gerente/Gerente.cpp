#include "Gerente.h"
#include <QString>

Gerente::Gerente()
{
}

void Gerente::SetQtdeFuncGereciados(int QtdeFuncGereciados)
{
    if(QtdeFuncGereciados < 0)
        throw QString("Quantidade de funcionarios gerenciados inválido.");
    this->QtdeFuncGereciados = QtdeFuncGereciados;
}

void Gerente::SetQtdeHsExcendente(float QtdeHsExcendente)
{
    this->QtdeHsExcendente = QtdeHsExcendente;
}

int Gerente::GetQtdeFuncGereciados()
{
    return this->QtdeFuncGereciados;
}

float Gerente::GetQtdeHsExcendente()
{
    return this->QtdeHsExcendente;
}

bool Gerente::AlterarSenha(string NovaSenha, string SenhaAntiga)
{
    if(SenhaAntiga != Senha)
        return 0;
    Senha = NovaSenha;
    return 1;
}

bool Gerente::Autenticar(string Senha)
{
    return (this->Senha == Senha);
}

double Gerente::CalculaBonus()
{
    float PercntBonus = 0.05 * QtdeFuncGereciados;
    if(PercntBonus > 0.3){
        return (GetSalarioBase() * 0.3 + (QtdeHsExcendente * ((1.5 * GetSalarioBase())/ GetQtdeHsMensais())));
    }
    return(GetSalarioBase() * PercntBonus + (QtdeHsExcendente * ((1.5 * GetSalarioBase())/ GetQtdeHsMensais())));
}

void Gerente::SetQtdeHorasTrab(float qtdeHsTrab)
{
    if(qtdeHsTrab < 0)
        throw QString("Quantidade de horas trabalhadas inválida.");
    if(qtdeHsTrab > GetQtdeHsMensais()){
        Funcionario::SetQtdeHorasTrab(GetQtdeHsMensais());
        this->QtdeHsExcendente = qtdeHsTrab - GetQtdeHsMensais();
    }else{
        Funcionario::SetQtdeHorasTrab(qtdeHsTrab);
        this->QtdeHsExcendente = 0;
    }
}

string Gerente::GetSenhaCriptografada()
{
    Geral *geral = new Geral;
    string senh = this->Senha;
    geral->criptografia(senh, 15);
    delete geral;
    return senh;
}
