#ifndef GERENTE_H
#define GERENTE_H

#include "2-Funcionario/Funcionario.h"
#include "0-Auxiliares/Geral.h"

class Gerente : public Funcionario
{
public:
    Gerente();

    void SetQtdeFuncGereciados(int QtdeFuncGereciados);
    void SetQtdeHsExcendente(float QtdeHsExcendente);

    int GetQtdeFuncGereciados();
    float GetQtdeHsExcendente();

    bool AlterarSenha( string NovaSenha, string SenhaAntiga = "");
    bool Autenticar(string Senha);

    double CalculaBonus();
    void SetQtdeHorasTrab(float qtdeHsTrab);

    //Método extra
    string GetSenhaCriptografada();
private:
    int QtdeFuncGereciados;
    float QtdeHsExcendente;
    string Senha;
};

#endif // GERENTE_H
