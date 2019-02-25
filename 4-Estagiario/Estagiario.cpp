#include "Estagiario.h"

#include <QDebug>
#include <QString>

Estagiario::Estagiario()
{
}

double Estagiario::CalculaBonus()
{
    if(Tipo == 1)
        return ((0.05 * GetSalarioBase()) / TempoContratoRestante);
    else
        return ((0.1 * GetSalarioBase()) / TempoContratoRestante);
}

void Estagiario::SetTempoContratoRestante(float Trc)
{
    this->TempoContratoRestante = Trc;
}

void Estagiario::SetTipo(int Tipo)
{
    this->Tipo = Tipo;
}

float Estagiario::GetTempoContratoRestante()
{
    return TempoContratoRestante;
}

int Estagiario::GetTipo()
{
    return this->Tipo;
}
