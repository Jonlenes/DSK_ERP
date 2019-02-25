#include "Funcionario.h"
#include <QString>

Funcionario::Funcionario()
{
}
Funcionario::~Funcionario()
{

}

double Funcionario::CalculaSalarioBruto()
{
    return (((SalarioBase * QtdeHsTrab) / QtdeHsMensais) + CalculaBonus());
}

void Funcionario::SetMatricula(long Matricula)
{
    this->Matricula = Matricula;
}

void Funcionario::SetSalarioBase(double Salario)
{
    if(Salario < 0)
        throw QString("Salario Base inválidas.");
    this->SalarioBase = Salario;

}

void Funcionario::SetQtdeHsMensais(float QtdeHsMensais)
{
    if(QtdeHsMensais < 0)
        throw QString("Quantidade de horas mensal inválidas.");
    this->QtdeHsMensais = QtdeHsMensais;
}

void Funcionario::SetQtdeHorasTrab(float QtdeHsTrab)
{
    if(QtdeHsTrab < 0 || QtdeHsTrab > QtdeHsMensais)
        throw QString("Para funcionarios padrão e estágiarios a quantidade de horas trabalhas não pode ser menor e nem maior do que as horas mensais.");
    this->QtdeHsTrab = QtdeHsTrab;
}

long Funcionario::GetMatricula()
{
    return this->Matricula;
}

double Funcionario::GetSalarioBase()
{
    return this->SalarioBase;
}

float Funcionario::GetQtdeHsMensais()
{
    return this->QtdeHsMensais;
}

float Funcionario::GetHorasTrab()
{
    return this->QtdeHsTrab;
}
