#ifndef LISTA_CPP
#define LISTA_CPP

#include "Lista.h"

template <typename Type>
Lista<Type>::Lista()
{
    inicio = new Node<Type>*;
    *inicio = NULL;
}

template <typename Type>
Lista<Type>::~Lista()
{
    Node<Type> *no;
    while(*inicio != NULL){
        no = *inicio;
        *inicio = (*inicio)->prox;
        delete no;
    }
    delete inicio;
}

template <typename Type>
int Lista<Type>::Size()
{
    int cont = 0;
    Node<Type> *no = *inicio;

    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

template <typename Type>
bool Lista<Type>::Empty()
{
    return (*inicio == NULL);
}

template <typename Type>
bool Lista<Type>::InsertBegin(Type i)
{
    Node<Type> *no;

    no = new Node<Type>;
    no->x = i;
    no->prox = (*inicio);
    *inicio = no;
    return true;
}

template <typename Type>
bool Lista<Type>::InsertEnd(Type i)
{
    Node<Type> *no;

    no = new Node<Type>;
    no->x = i;
    no->prox = NULL;

    if(Empty())
        *inicio = no;
    else{
        Node<Type> *aux = (*inicio);
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return true;
}

template <typename Type>
bool Lista<Type>::InsertOrdained(Type i)
{
    Node<Type> *no = new Node<Type>;
    no->x = i;

    if(Empty()){
        no->prox = (*inicio);
        *inicio = no;
        return true;
    }
    Node<Type> *aux = *inicio, *ant;
    //if(Type == Funcionari)
    while(aux != NULL && aux->x < no->x){
        ant = aux;
        aux = aux->prox;
    }
    if(aux == *inicio){
        no->prox = (*inicio);
        *inicio = no;
    }else{
        no->prox = ant->prox;
        ant->prox = no;
    }
    return true;
}

template <typename Type>
bool Lista<Type>::RemoveBegin(Type *valor){
    if(Empty())
        return false;
    Node<Type> *no = *inicio;
    no = no->prox;
    *inicio = no;
    delete no;
    return true;

}

template <typename Type>
bool Lista<Type>::RemoveEnd(Type *valor)
{
    if(Empty())
        return false;

    Node<Type> *no = *inicio, *ant;
    while(no->prox != NULL){
        ant = no;
        no = no->prox;
    }
    if(no == *inicio){
        *inicio = no->prox;
        return true;
    }
    else
        ant->prox = no->prox;
    delete no;
    return true;
}

template <typename Type>
bool Lista<Type>::Romove(int Index){
    if(Empty())
        return false;
    Node<Type> *no = *inicio, *ant;
    int i = 0;

    while(no != NULL && i < Index){
        ant = no;
        no = no->prox;
        i++;
    }
    if(no == NULL)
        return false;
    else if(no == *inicio){
        *inicio = no->prox;
        return true;
    }else{
        ant->prox = no->prox;
        delete no;
    }
    return true;
}

template <typename Type>
bool Lista<Type>::Search(int pos, Type &valor)
{
    if(pos < 0 || Empty() || pos > Size() - 1)
        return false;

    Node<Type> *no = *inicio;
    int i = 0;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }
    if(no == NULL)
        return false;
    else{
        valor = no->x;
        return true;
    }
}

template <typename Type>
bool Lista<Type>::Search(Type &valor)
{
    if(Empty())
        return false;
    Node<Type> *no = *inicio;
    while(no != NULL && no->x != valor){
        no = no->prox;
    }
    if(no == NULL)
        return false;
    else{
        valor = no->x;
        return true;
    }

}

template <typename Type>
void Lista<Type>::GetList(QTableWidget *tw)
{
    tw->clear();

    int qtdeLinas = tw->rowCount();
    for(int i = qtdeLinas; i >= 0; i--)
        tw->removeRow(i);

    int qtdeColunas = tw->columnCount();
    for(int i = qtdeColunas; i >= 0; i--)
        tw->removeColumn(i);

    tw->insertColumn(tw->columnCount());
    int i = 0;
    for(Node<Type> *no = *inicio; no != NULL; no = no->prox){
        tw->insertRow(tw->rowCount());
        tw->setItem(i, 0, new QTableWidgetItem(no->x));
        i++;
    }
}
#endif
