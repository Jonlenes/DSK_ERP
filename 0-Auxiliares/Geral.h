#ifndef GERAL_H
#define GERAL_H

#include <iostream>
#include <QMessageBox>
using namespace std;

class Geral
{
public:
    Geral();
    void criptografia(string &frase, int k);
    void Alerta(QWidget *qw, QString msn);
    QString convertDataSQL(char data[], QString format);
    void separaConta(QString &str);
};

#endif // GERAL_H
