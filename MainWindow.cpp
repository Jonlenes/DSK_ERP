#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "3-Gerente/Gerente.h"
#include "4-Estagiario/Estagiario.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QDockWidget>
#include <typeinfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Inicializa();
    ui->menuBar->setEnabled(0);
    ui->mainToolBar->setEnabled(0);
    Login();
}

MainWindow::~MainWindow()
{
    ui->dockWidget->close();
    delete ui;
    delete Emp;
    delete [] VetLine;
    delete Frm;
    delete label;
    delete intValidator;
    delete doubleValidador;
}

void MainWindow::on_actionVer_Diagrama_de_Class_triggered()
{
    ui->dockWidget->close();
    ui->labelFotoDiagrama->setPixmap(QPixmap::fromImage(QImage(":/Imagens/CDH.png")));
    ui->dockWidget->setWidget(ui->widgetMostraDiagrama);
    ui->dockWidget->show();
}

void MainWindow::on_actionGerente_triggered()
{
    ui->dockWidget->close();
    ui->widgetFuncionario->setVisible(1);
    Controle = 1;
    ExecutaAcaoFrm(1);

    ui->dockWidget->setWidget(ui->widgetFuncionario);
    ui->dockWidget->show();
}

void MainWindow::on_actionPadrao_triggered()
{
    ui->dockWidget->close();
    ui->widgetFuncionario->setVisible(1);
    Controle = 2;
    ExecutaAcaoFrm(2);

    ui->dockWidget->setWidget(ui->widgetFuncionario);
    ui->dockWidget->show();
}

void MainWindow::on_actionEstagiario_triggered()
{
    ui->dockWidget->close();
    TipoEst = "Jovem Aprendiz";
    ui->widgetFuncionario->setVisible(1);
    Controle = 3;
    ExecutaAcaoFrm(3);

    ui->dockWidget->setWidget(ui->widgetFuncionario);
    ui->dockWidget->show();
}

void MainWindow::on_actionCliente_triggered()
{
    ui->dockWidget->close();
    ui->dockWidget->setWindowTitle("Cadastro de Clientes");
    ui->widgetCadastroCliente->setVisible(1);
    ui->dockWidget->setWidget(ui->widgetCadastroCliente);
    ui->dockWidget->show();
}

void MainWindow::on_actionLista_de_Funcionarios_triggered()
{
    ui->dockWidget->close();
    ui->dockWidget->setWindowTitle("Lista de Funcionarios");
    Emp->MostraFuncionarios(ui->tableWidgetMostra);
    ui->dockWidget->setWidget(ui->widgetMostraFuncCliente);
    ui->dockWidget->show();
    IndexExclusao = -1;
}

void MainWindow::on_actionLista_de_Clientes_triggered()
{
    ui->dockWidget->close();
    ui->dockWidget->setWindowTitle("Lista de Cliente");
    Emp->MostraClientes(ui->tableWidgetMostraCliente);
    ui->dockWidget->setWidget(ui->widgetMostraCliente);
    ui->dockWidget->show();
    IndexExclusao = -1;
}

void MainWindow::on_pushButtonSalvarFunc_clicked()
{
    bool Flag = true;
    switch (Controle) {
    case 1: //Gerente
        for(int i = 0; i < 8; i++)
            if(VetLine[i]->text() == "")
                Flag = 0;
        if(!Flag)
            QMessageBox::information(this, "Aviso", "Campos em branco.");
        else{
            Gerente *Ger = new Gerente;
            try{
                Ger->SetNome(VetLine[0]->text().toStdString());
                Ger->SetCPF(VetLine[1]->text().toStdString());
                Ger->SetMatricula(VetLine[2]->text().toLong());
                Ger->SetSalarioBase(VetLine[3]->text().toDouble());
                Ger->SetQtdeHsMensais(VetLine[4]->text().toInt());
                Ger->SetQtdeHorasTrab(VetLine[5]->text().toInt());
                Ger->SetQtdeFuncGereciados(VetLine[6]->text().toInt());
                Ger->AlterarSenha(VetLine[7]->text().toStdString());
            }
            catch (QString e){
                QMessageBox::information(this, "Aviso", e);
                delete Ger;
                Ger = NULL;
            }
            Emp->AddPessoa(Ger);
            ExecutaAcaoFrm();

            if(!FlagLogado)
                Login();
        }
        break;
    case 2: //Pradrão
        for(int i = 0; i < 5; i++)
            if(VetLine[i]->text() == "")
                Flag = 0;
        if(!Flag)
            QMessageBox::information(this, "Aviso", "Campos em branco.");
        else{
            Funcionario *Func = new Funcionario;
            try{
                Func->SetNome(VetLine[0]->text().toStdString());
                Func->SetCPF(VetLine[1]->text().toStdString());
                Func->SetMatricula(VetLine[2]->text().toLong());
                Func->SetSalarioBase(VetLine[3]->text().toDouble());
                Func->SetQtdeHsMensais(VetLine[4]->text().toInt());
                Func->SetQtdeHorasTrab(VetLine[5]->text().toInt());
            }
            catch (QString e){
                QMessageBox::information(this, "Aviso", e);
                delete Func;
                Func = NULL;
            }
            if(Func != NULL){
                Emp->AddPessoa(Func);
                ExecutaAcaoFrm();
            }
        }
        break;
    case 3: //Estagiario
        for(int i = 0; i <= 6; i++)
            if(VetLine[i]->text() == "")
                Flag = 0;
        if(!Flag)
            QMessageBox::information(this, "Aviso", "Campos em preto e branco.");
        else{
            Estagiario *Est = new Estagiario;
            try{
                Est->SetNome(VetLine[0]->text().toStdString());
                Est->SetCPF(VetLine[1]->text().toStdString());
                Est->SetMatricula(VetLine[2]->text().toLong());
                Est->SetSalarioBase(VetLine[3]->text().toDouble());
                Est->SetQtdeHsMensais(VetLine[4]->text().toInt());
                Est->SetQtdeHorasTrab(VetLine[5]->text().toInt());
                Est->SetTempoContratoRestante(VetLine[6]->text().toFloat());
                if(TipoEst == "Jovem Aprendiz")
                    Est->SetTipo(1);
                else
                    Est->SetTipo(2);
            }
            catch (QString e){
                QMessageBox::information(this, "Aviso", e);
                delete Est;
                Est = NULL;
            }
            if(Est != NULL){
                Emp->AddPessoa(Est);
                ExecutaAcaoFrm();
            }
        }
        break;
    }
}

void MainWindow::on_pushButtonSalvarCliente_clicked()
{
    bool Flag = true;
    for(int i = 8; i <= 11; i++)
        if(VetLine[i]->text() == "")
            Flag = 0;
    if(!Flag)
        QMessageBox::information(this, "Aviso", "Campos em preto e branco.");
    else{
        Cliente *Client = new Cliente;
        Client->SetNome(VetLine[8]->text().toStdString());
        Client->SetCPF(VetLine[9]->text().toStdString());
        Client->SetTelefone(VetLine[10]->text().toStdString());
        Client->SetEndereco(VetLine[11]->text().toStdString());
        Emp->AddPessoa(Client);

        for(int i = 8; i <= 11; i++)
            VetLine[i]->setText("");
    }
}

void MainWindow::Inicializa()
{
    ui->widgetFuncionario->setVisible(0);
    ui->widgetMostraFuncCliente->setVisible(0);
    ui->widgetCadastroCliente->setVisible(0);
    ui->widgetMostraCliente->setVisible(0);
    ui->widgetFolhaPagamento->setVisible(0);
    ui->widgetLogin->setVisible(0);
    ui->widgetMostraDiagrama->setVisible(0);
    ui->dockWidget->setVisible(0);
    Controle = -1;
    IndexExclusao = -1;
    FlagLogado = false;

    Emp = new Empresa(this);
    Frm = new QMainWindow(this);
    VetLine = new QLineEdit*[12];
    label = new QLabel(Frm->centralWidget());
    intValidator = new QIntValidator(this);
    doubleValidador = new QDoubleValidator(this);

    ui->lineEditMat->setValidator(intValidator);
    ui->lineEditQtdeFuncGere->setValidator(intValidator);
    ui->lineEditQtdeHsMensais->setValidator(intValidator);
    ui->lineEditQtdeHsTrab->setValidator(intValidator);
    ui->lineEditSalarioBase->setValidator(doubleValidador);
    ui->lineEditTelefoneCliente->setValidator(doubleValidador);

    VetLine[0] = ui->lineEditNome;
    VetLine[1] = ui->lineEditCPF;
    VetLine[2] = ui->lineEditMat;
    VetLine[3] = ui->lineEditSalarioBase;
    VetLine[4] = ui->lineEditQtdeHsMensais;
    VetLine[5] = ui->lineEditQtdeHsTrab;
    VetLine[6] = ui->lineEditQtdeFuncGere;
    VetLine[7] = ui->lineEditSenha;
    VetLine[8] = ui->lineEditNomeCliente;
    VetLine[9] = ui->lineEditCPFCliente;
    VetLine[10] = ui->lineEditTelefoneCliente;
    VetLine[11] = ui->lineEditEndCliente;


    ui->lineEditCPF->setInputMask("###.###.###-##");
    ui->lineEditCPFCliente->setInputMask("###.###.###-##");
}

void MainWindow::ExecutaAcaoFrm(int Index)
{
    for(int i = 0; i < 8; i++){
        VetLine[i]->clear();
        if(Index != -1)
            VetLine[i]->setVisible(1);
    }

    if(Index == 1){
        ui->label_6->setVisible(1);
        ui->label_7->setVisible(1);
        ui->label_8->setVisible(1);
        ui->label_9->setVisible(0);
        ui->comboBoxTipoESt->setVisible(0);
        ui->label_7->setText("Qtde de funcionarios Gerenciados:");
        ui->dockWidget->setWindowTitle("Cadastro de Gerente");
    }
    if(Index == 2 || Index == 3){
        ui->label_6->setVisible(0);
        VetLine[6]->setVisible(0);
        VetLine[7]->setVisible(0);
        ui->label_6->setVisible(1);
        ui->label_7->setVisible(0);
        ui->label_8->setVisible(0);

        if(Index == 2){
            ui->label_5->setVisible(1);
            ui->label_9->setVisible(0);
            VetLine[7]->setVisible(0);
            ui->comboBoxTipoESt->setVisible(0);
            ui->dockWidget->setWindowTitle("Cadastro de Funcionário");
        }else{
            ui->label_7->setVisible(1);
            ui->label_7->setText("Tempo restante de contrato");
            VetLine[5]->setVisible(1);
            VetLine[6]->setVisible(1);
            ui->label_9->setVisible(1);
            ui->comboBoxTipoESt->setVisible(1);
            ui->dockWidget->setWindowTitle("Cadastro de Estagiario");
        }
    }
}

void MainWindow::on_comboBoxTipoESt_activated(const QString &arg1)
{
    TipoEst = arg1;
}

void MainWindow::on_actionFolha_de_Pagamento_triggered()
{
    ui->dockWidget->close();
    ui->dockWidget->setWindowTitle("Folha de Pagamento");
    Emp->CalcularFolhaDePagamento(ui->tableWidgetFolaPagamento, ui->labelFolhaPagamento);
    ui->dockWidget->setWidget(ui->widgetFolhaPagamento);
    ui->dockWidget->show();
}

void MainWindow::on_actionAlterar_Senha_triggered()
{
    QMessageBox::information(this, "Aviso", "Você só poderá alterar sua propria senha de Gerente. (A que foi utilizada para logar)");
    QString SenhaVelha = QInputDialog::getText(this, "Senha Atual", "Digite a senha antiga: ");
    QString SenhaNova = QInputDialog::getText(this, "Nova Senha", "Digite a nova Senha: ");
    if(GerAtual->AlterarSenha(SenhaNova.toStdString(), SenhaVelha.toStdString())){
        QMessageBox::information(this, "Aviso", "Senha Alterada com Sucesso.");
        ui->dockWidget->close();
    }else
        QMessageBox::information(this, "Aviso", "Senha antiga incorreta.");
}

void MainWindow::on_pushButtonEntrar_clicked()
{
    if(Emp->AutenticaGerente(ui->lineEditLoginMat->text().toLong(),
                             ui->lineEditLoginSenha->text().toStdString(), GerAtual)){
        ui->menuBar->setEnabled(1);
        ui->mainToolBar->setEnabled(1);
        ui->dockWidget->close();
        FlagLogado = 1;
    }else
        QMessageBox::information(this, "Aviso", "Falha de autenticação.");
}

void MainWindow::on_pushButtonCadastrar_clicked()
{
    on_actionGerente_triggered();
}

void MainWindow::Login()
{
    ui->dockWidget->close();
    ui->dockWidget->setWindowTitle("Login para Gerente já cadastrados");
    ui->dockWidget->setWidget(ui->widgetLogin);
    ui->dockWidget->show();
}

void MainWindow::on_actionSobre_triggered()
{
    QString Str = " Essa prova foi desenvolvido";
    Str = Str + " pelo aluno Jonlenes Silva de Castro";
    Str = Str + " para a disciplina de técnica de programação II";
    Str = Str + " a pedido do professor Max.\n\n ";
    QMessageBox::information(this, "Aviso", Str);
}

void MainWindow::on_pushButtonRemoverCliente_clicked()
{
    if(IndexExclusao != -1){
        Emp->ExcluiPessoa(2, IndexExclusao);
        on_actionLista_de_Clientes_triggered();
        IndexExclusao = -1;
    }else
        QMessageBox::information(this, "Aviso", "Selecione uma celula do registro que deseja exclui.");
}

void MainWindow::on_tableWidgetMostraCliente_clicked(const QModelIndex &index)
{
    IndexExclusao = index.row();
}

void MainWindow::on_pushButtonRemoverFunc_clicked()
{
    if(IndexExclusao != -1){
        Emp->ExcluiPessoa(1, IndexExclusao);
        on_actionLista_de_Funcionarios_triggered();
        IndexExclusao = -1;
    }else
        QMessageBox::information(this, "Aviso", "Selecione uma celula do registro que deseja exclui.");
}

void MainWindow::on_tableWidgetMostra_clicked(const QModelIndex &index)
{
    IndexExclusao = index.row();
}

void MainWindow::on_actionSair_triggered()
{
    this->close();
}
