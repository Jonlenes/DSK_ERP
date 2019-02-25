#ifndef CONEXAO_BD_H
#define CONEXAO_BD_H

#include <QtSql>
#include <QMessageBox>
//#include "geral.h"

class Conexao_BD
{
public:
    Conexao_BD();
    bool SetConectBD(QSqlDatabase &db, QWidget *Atual);
    bool Consulta(QString consulta, QSqlQuery &qry);
    bool CloseBD(QSqlDatabase &db);
    void setUsuLogado(QString &UsuLogado);
    //Geral geral;
};

#endif // CONEXAO_BD_H
