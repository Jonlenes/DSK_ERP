#include "conexao_bd.h"
#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <QFileDialog>
#include <QWidget>
using namespace std;


Conexao_BD::Conexao_BD()
{
}

bool Conexao_BD::SetConectBD(QSqlDatabase &db, QWidget *Atual){
    db = QSqlDatabase::addDatabase( "QSQLITE" );
    if(!db.isOpen()){
        string Direc = QFileDialog::getOpenFileName(Atual, "Selecione o Empresa.bd que está na pasta do projeto.", "Empresa.bd", "*.db").toStdString();
        qDebug() << QString::fromStdString(Direc);
        db.setDatabaseName(QString::fromStdString(Direc));
    }

    if( !db.open() ){
        qDebug() << db.lastError();
        QMessageBox::information(Atual, "Aviso", "Não foi possível conectar-se ao Banco de dados");
        return false;
    }
    qDebug( "Conectado." );
    return true;
}

bool Conexao_BD::Consulta(QString consulta, QSqlQuery &qry){
    qry.prepare(consulta);
    if( !qry.exec() ){
        qDebug() << qry.lastError();
        return false;
    }
    return true;
}

bool Conexao_BD::CloseBD(QSqlDatabase &db){
    db.close();
    //db.removeDatabase("qt_sql_default_connection");
    qDebug() << ("Desconectado.");
    return true;
}

/*void Conexao_BD::setUsuLogado(QString &UsuLogado){
    string str;

    QString QsQry;
    QSqlQuery qry;
    QsQry = "SELECT usuario FROM usuarios WHERE flag = 1";
    Consulta(QsQry, qry);
    for(int i = 0; qry.next(); i++)
        str = qry.value(0).toString().toStdString();
    geral.criptografia(str, 11);
    UsuLogado = QString::fromStdString(str);
}*/
