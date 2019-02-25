#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include "1-Pessoa/PessoaFisica.h"

class Funcionario : public PessoaFisica
{
public:
    Funcionario();
    virtual ~Funcionario();

    double CalculaSalarioBruto();

    void SetMatricula(long Matricula);
    void SetSalarioBase(double Salario);
    void SetQtdeHsMensais(float QtdeHsMensais);
    virtual void SetQtdeHorasTrab(float QtdeHsTrab);

    long GetMatricula();
    double GetSalarioBase();
    float GetQtdeHsMensais();
    float GetHorasTrab();

protected:
    virtual double CalculaBonus(){ return 0.0;}
private:
    long Matricula;
    double SalarioBase;
    float QtdeHsMensais;
    float QtdeHsTrab;
};

#endif // FUNCIONARIO_H
