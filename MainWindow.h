#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QToolBar>
#include "6-Empresa/Empresa.h"

class QLineEdit;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Inicializa();
    void ExecutaAcaoFrm(int Index = -1);
    void Login();

private slots:
    void on_actionVer_Diagrama_de_Class_triggered();

    void on_actionGerente_triggered();

    void on_pushButtonSalvarFunc_clicked();

    void on_actionPadrao_triggered();

    void on_actionEstagiario_triggered();

    void on_actionLista_de_Funcionarios_triggered();

    void on_comboBoxTipoESt_activated(const QString &arg1);

    void on_pushButtonSalvarCliente_clicked();

    void on_actionCliente_triggered();

    void on_actionLista_de_Clientes_triggered();

    void on_actionFolha_de_Pagamento_triggered();

    void on_actionAlterar_Senha_triggered();

    void on_pushButtonEntrar_clicked();

    void on_pushButtonCadastrar_clicked();

    void on_actionSobre_triggered();

    void on_pushButtonRemoverCliente_clicked();

    void on_tableWidgetMostraCliente_clicked(const QModelIndex &index);

    void on_pushButtonRemoverFunc_clicked();

    void on_tableWidgetMostra_clicked(const QModelIndex &index);

    void on_actionSair_triggered();

private:
    Ui::MainWindow *ui;
    Empresa *Emp;
    QLineEdit **VetLine;
    QMainWindow  *Frm;
    QLabel *label;
    QIntValidator *intValidator;
    QDoubleValidator *doubleValidador;
    QString TipoEst;
    Gerente *GerAtual;
    int Controle;
    bool FlagLogado;
    int IndexExclusao;
};

#endif // MAINWINDOW_H
