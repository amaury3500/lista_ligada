#include <iostream>
#include<locale.h>
#include "SocioClub.h"

template<class T>
class LSLSE;

template<class T>
class node{
private:
    T data;
    node<T>* sig;
public:
    node():sig(nullptr){};
    T getData(){
        return data;
    }
    friend class LSLSE<T>;
};

template<class T>
class LSLSE{
private:
    node<T>* lista;
public:
    LSLSE():lista(nullptr){};
    bool vacia()const;
    node<T>* ultimo()const;
    node<T>* primero()const;
    node<T>* anterior(node<T>* pos)const;
    void insertar(node<T>* pos, T elem);
    bool eliminar(node<T>* pos);
    void imprimir()const;
    int cont()const;
    node<T>* buscar(T elem)const;
    void quicksort();
    void Quicksort(node<T>* primero, node<T>* ultimo);
    bool Repeat(SocioClub X)const;

};

template<class T>
void LSLSE<T>::imprimir()const{
    node<T>* aux=lista;
    while(aux!=nullptr){
        std::cout<<aux->data<<"-> "<<std::endl<<std::endl;
        aux=aux->sig;
    }
}

template<class T>
bool LSLSE<T>::eliminar(node<T>* pos){
    if(vacia() || pos==nullptr){
        return false;
    }
    if(pos==lista){
        lista=lista->sig;
    }
    else{
        anterior(pos)->sig=pos->sig;
    }
    delete pos;
    return true;
}

template<class T>
void LSLSE<T>::insertar(node<T>* pos, T elem){
    node<T>* aux= new node<T>;
    aux->data=elem;
    if(pos==nullptr){
        aux->sig=lista;
        lista=aux;
    }
    else{
        aux->sig=pos->sig;
        pos->sig=aux;
    }
}

template<class T>
node<T>* LSLSE<T>::anterior(node<T>* pos)const{
    if(vacia() || pos==nullptr){
        return nullptr;
    }
    node<T>* aux=lista;
    while(aux!=nullptr && aux->sig!=pos){
        aux=aux->sig;
    }
    return aux;
}

template<class T>
node<T>* LSLSE<T>::primero()const{
    if(vacia()){
        return nullptr;
    }
    return lista;
}

template<class T>
node<T>* LSLSE<T>::ultimo()const{
    if(vacia()){
        return nullptr;
    }
    node<T>* aux=lista;
    while(aux->sig!=nullptr){
        aux=aux->sig;
    }
    return aux;
}

template<class T>
bool LSLSE<T>::vacia()const{
    if(lista==nullptr)
        return true;
    return false;
}

template<class T>
int LSLSE<T>::cont()const{
    int cont=1;
    if(vacia()){
        return 0;
    }
    node<T>* aux=lista;
    while(aux->sig!=nullptr){
        cont++;
        aux=aux->sig;
    }
    return cont;
}

template<class T>
node<T>* LSLSE<T>::buscar(T elem)const{
    node<T>* aux=lista;
    while(aux!=nullptr && aux->data!=elem){
        aux = aux->sig;
    }
    return aux;
}

template<class T>
void LSLSE<T>::quicksort() {
    quicksortAux(primero(), ultimo());
}

template<class T>
void LSLSE<T>::Quicksort(node<T>* primero, node<T>* ultimo) {
    if (primero != nullptr && ultimo != nullptr && primero != ultimo && primero != ultimo->sig) {
        node<T>* pivote = ultimo;
        node<T>* anteriorPivote = anterior(pivote);
        node<T>* i = primero;
        node<T>* j = anteriorPivote;

        while (i != j) {
            if (i->data > pivote->data) {
                i = i->sig;
            } else {
                T temp = i->data;
                i->data = j->data;
                j->data = temp;
                j = anterior(j);
            }
        }

        if (i->data < pivote->data) {
            T temp = i->data;
            i->data = pivote->data;
            pivote->data = temp;
        }

        Quicksort(primero, anterior(i));
        Quicksort(i->sig, ultimo);
    }
}

int main()
{
    setlocale(LC_ALL, "spanish");
    int opc;
    LSLSE<SocioClub> milista;
    SocioClub elem,X;
    std::string temp;
    do{
        system("cls");
        std::cout<<"\n\tMenu de opciones"<<std::endl<<std::endl;
        std::cout<<" 1. Registrar a un nuevo socio."<<std::endl;
        std::cout<<" 2. Dar de baja a un socio."<<std::endl;
        std::cout<<" 3. reporte de todos los socios del club."<<std::endl;
        std::cout<<" 4. Buscar a un socio del club."<<std::endl;
        std::cout<<" 5. Numer total de socios."<<std::endl;
        std::cout<<" 6. Salir."<<std::endl;
        std::cout<<"Ingresa la opcion: ";
        std::cin>>opc;

        switch(opc){
            case 1: system("cls");
                    std::cout<<"\n\tRegistrar a un nuevo socio: "<<std::endl;
                    std::cin>>X;
                     if(milista.buscar(X)){
                            std::cout<<"Numero de socio ya existente, asignar otro numero!"<<std::endl<<std::endl;
                    }else{
                        milista.insertar(milista.ultimo(),SocioClub(X));
                        milista.Quicksort(milista.primero(),milista.ultimo());
                        std::cout<<"Socio agregado con exito!"<<std::endl<<std::endl;
                    }
                    system("pause");
                    break;

            case 2: system("cls");
                    if(!milista.vacia()){
                        std::cout<<"Ingresa los datos del socio a dar de baja: "<<std::endl;
                        std::cin>>elem;
                        if(milista.eliminar(milista.buscar(elem))){
                            std::cout<<"Socio eliminado con exito!"<<std::endl;
                        }else{
                            std::cout<<"El Socio no existe!"<<std::endl;
                        }
                    }else{
                        std::cout<<"La lista esta vacia!"<<std::endl;
                    }
                    system("pause");
                    break;

            case 3: system("cls");
                    if(!milista.vacia()){
                        milista.imprimir();
                    }else{
                        std::cout<<"La lista esta vacia!"<<std::endl;
                    }
                    system("pause");
                    break;

            case 4: system("cls");
                    if(!milista.vacia()){
                        std::cout<<"\n\tIngresa los datos a buscar"<<std::endl;
                        std::cout<<"Nombre: ";
                        std::cin>>temp;
                        elem.setNombre(temp);
                        std::cout<<"Domicilio: ";
                        std::cin>>temp;
                        elem.setDomicilio(temp);
                        if(milista.buscar(elem)){
                            elem=milista.buscar(elem)->getData();
                            std::cout<<"\n\tSocio encontrado"<<elem<<std::endl;
                        }
                        else{
                            std::cout<<"Socio no encontrado!"<<std::endl;
                        }
                    }else{
                        std::cout<<"La lista esta vacia!"<<std::endl;
                    }
                    system("pause");
                    break;

            case 5: system("cls");
                    if(!milista.vacia()){
                        std::cout<<milista.cont()<<std::endl;
                    }else{
                        std::cout<<"La lista esta vacia!"<<std::endl;
                    }
                    system("pause");
                    break;
        }

    }while(opc!=6);
    return 0;
}
