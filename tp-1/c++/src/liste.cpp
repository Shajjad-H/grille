#include "liste.h"
#include <iostream>

using namespace std;

Liste::Liste() {
    ad = nullptr;
}

Liste::Liste(const Liste &l) {
    Cellule * iterator = l.premiereCellule();
    while(iterator != nullptr) {
        ajoutEnQueue(elementCellule(iterator));
        iterator = celluleSuivante(iterator);
    }
    iterator = nullptr;
}
Liste::~Liste() {
    vide();
}
bool Liste::testVide() const {
    return this->ad == nullptr;
}

Liste &Liste::operator=(const Liste &l) {
    Cellule * iterator = l.premiereCellule();
    while(iterator != nullptr) {
        ajoutEnQueue(elementCellule(iterator));
        iterator = celluleSuivante(iterator);
    }
    iterator = nullptr;
    return *this;
}

Elem Liste::premierElement() const {
    return ad->info;
}
Cellule *Liste::premiereCellule() const {
    if(testVide()) 
        return nullptr;
    return ad;
}
Cellule *Liste::celluleSuivante(const Cellule *c) const {
    return c->suivant;
}
Elem Liste::elementCellule(const Cellule *c) const {
    return c->info;
}
void Liste::affichage() const {
    Cellule * iterator = ad;
    while(iterator != nullptr) {
        affichageElement(elementCellule(iterator));
        iterator = celluleSuivante(iterator);
    }
    cout<<endl;
}
void Liste::ajoutEnTete(const Elem &e) {

    Cellule * newCellule = new Cellule;
    modifieInfoCellule(e,newCellule);
    newCellule->suivant = ad;
    ad = newCellule;
}
void Liste::vide() {
    Cellule * iterator;
    while(ad != nullptr) {
        iterator = ad;
        ad = celluleSuivante(ad);
        delete iterator;
    }
    ad = nullptr;
}

void Liste::ajoutEnQueueConnaissantUneCellule(const Elem &e, Cellule *c) {
    if(celluleSuivante(c) == nullptr) {
        c->suivant = new Cellule;
        modifieInfoCellule(e,c->suivant);
        c->suivant->suivant = nullptr;
    }
    else {
        ajoutEnQueueConnaissantUneCellule(e,celluleSuivante(c));
    }
}

void Liste::ajoutEnQueue(const Elem &e) {
    if(testVide())
        ajoutEnTete(e);
    else 
        ajoutEnQueueConnaissantUneCellule(e,ad);
}
Cellule *Liste::rechercheElement(const Elem &e) const {
    Cellule * iterator = premiereCellule();
    while(iterator != nullptr) {
        if( elementCellule(iterator) == e )
            return iterator;
        iterator = celluleSuivante(iterator);
    }
    return nullptr;
}
void Liste::insereElementApresCellule(const Elem &e, Cellule *c) {
    Cellule * tmp = new Cellule;
    modifieInfoCellule(e,tmp);
    tmp->suivant = celluleSuivante(c);
    c->suivant = tmp;
}
void Liste::modifieInfoCellule(const Elem &e, Cellule *c) {
    c->info = e;
}
