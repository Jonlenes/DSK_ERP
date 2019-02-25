#ifndef LISTA_H
#define LISTA_H

#include <QTableWidget>
#include "Node.h"

template <typename Type>
class Lista
{
public:
    Lista();
    ~Lista();
    int Size();
    bool Empty();

    bool InsertBegin(Type i);
    bool InsertEnd(Type i);
    bool InsertOrdained(Type i);

    bool RemoveBegin(Type *valor = NULL);
    bool RemoveEnd(Type *valor = NULL);
    bool Romove(int Index);

    bool Search(int pos, Type &valor);
    bool Search(Type &valor);

    void GetList(QTableWidget *tw);

protected:
    Node<Type> **inicio;
};

#include "Lista.cpp"
#endif // LISTA_H
