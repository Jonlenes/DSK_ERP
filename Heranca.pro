#-------------------------------------------------
#
# Project created by QtCreator 2014-10-01T09:58:09
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Heranca
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    1-Pessoa/Pessoa.cpp \
    1-Pessoa/PessoaFisica.cpp \
    1-Pessoa/PessoaJuridica.cpp \
    2-Funcionario/Funcionario.cpp \
    3-Gerente/Gerente.cpp \
    4-Estagiario/Estagiario.cpp \
    5-Cliente/Cliente.cpp \
    6-Empresa/Empresa.cpp\
    0-Auxiliares/Lista.cpp\
    0-Auxiliares/Node.cpp\
    0-Auxiliares/Conexao_BD.cpp \
    0-Auxiliares/Geral.cpp

HEADERS  += MainWindow.h \
    1-Pessoa/Pessoa.h \
    1-Pessoa/PessoaFisica.h \
    1-Pessoa/PessoaJuridica.h \
    2-Funcionario/Funcionario.h \
    3-Gerente/Gerente.h \
    4-Estagiario/Estagiario.h \
    5-Cliente/Cliente.h \
    6-Empresa/Empresa.h\
    0-Auxiliares/Lista.h\
    0-Auxiliares/Node.h\
    0-Auxiliares/Conexao_BD.h \
    0-Auxiliares/Geral.h

FORMS    += MainWindow.ui

RESOURCES += \
    Resource.qrc

OTHER_FILES +=
