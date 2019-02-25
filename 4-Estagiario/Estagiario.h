#ifndef ESTAGIARIO_H
#define ESTAGIARIO_H

#include "2-Funcionario/Funcionario.h"

class Estagiario : public Funcionario
{
public:
    Estagiario();
    double CalculaBonus();

    void SetTempoContratoRestante(float Trc);
    float GetTempoContratoRestante();

    void SetTipo(int Tipo);
    int GetTipo();

private:
    float TempoContratoRestante;
    int Tipo;
};

#endif // ESTAGIARIO_H
