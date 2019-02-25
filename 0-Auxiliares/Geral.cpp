#include "geral.h"

Geral::Geral()
{
}

void Geral::criptografia(string &frase, int k)
{
    k = k % 26;

    int controlador = 0;
    for(int i = 0; i < 6; i++)
    {
        if(frase[i] >= 65 && frase[i] <= 90)
        {
            if(frase[i] + k <= 90)
                frase[i] = frase[i] + k;
            else
            {
                controlador = k - (90 -frase[i] + 1);
                frase[i] = 65 + controlador;
            }
        }
        if(frase[i] >= 97 && frase[i] <= 122)
        {
            if(frase[i] + k <= 122)
                frase[i] = frase[i] + k;
            else
            {
                controlador = k - (122 -frase[i] + 1);
                frase[i] = 97 + controlador;
            }
        }
    }
}

void Geral::Alerta(QWidget *qw, QString msn){
    QMessageBox::information(qw, "Alerta", msn);
}

QString Geral::convertDataSQL(char data[], QString format){
    QString dt[3];
    int k = 0;
    if(format == "sis-sql"){
        for(int i = 0; data[i] != '\0'; i++){
            if(data[i] == '/'){
                i++;
                k++;
            }
            dt[k] = dt[k] + data[i];
        }
        return ("20" + dt[2] + "-" + dt[0] + "-" + dt[1]);
    }
    return "";
}

void Geral::separaConta(QString &str){
    string aux1 = str.toStdString(), aux2 = "";
    str = "";
    for(int i = 0; aux1[i] != 32; i++)
        aux2 = aux2 + aux1[i];
    str = QString::fromStdString(aux2);
}
