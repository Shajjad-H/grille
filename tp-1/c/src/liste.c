#include "liste.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


void initialiseListeDefaut(Liste *l) {
    l->ad = NULL; 
    l->nb_elem = 0;   
}
int testListeVide(Liste l) {
    if(l.ad == NULL)
        return 1;
    return 0;
}

void initialiseListeCopie(Liste *l1, Liste l2) {
    videListe(l1);
    Cellule * it = premiereCelluleListe(l2);
    while(it) {
        ajoutEnQueueListe(elementCelluleListe(it),l1);
        it = celluleSuivanteListe(it,l2);
    }
}
void affectationListe(Liste *l1, Liste l2) {
    initialiseListeCopie(l1,l2);
}

Cellule * premiereCelluleListe(Liste l) {
    return l.ad; 
}
Elem elementCelluleListe(const Cellule * c) {
    return c->info;
}

void ajoutEnTeteListe(Elem e,Liste *l) {
    Cellule * newCellule = malloc(sizeof(Cellule));
    newCellule->info = e;
    newCellule->suivant = l->ad;
    l->ad = newCellule;
    l->nb_elem++;
}
void testamentListe(Liste *l) {
    videListe(l);
}
void videListe(Liste *l) {
    Cellule * it = premiereCelluleListe(*l);
    Cellule * tmp;
    while(it != NULL) {
        tmp = it;
        it = it->suivant;
        free(tmp);
    }
    l->nb_elem = 0;
    l->ad = NULL;
}
Cellule * celluleSuivanteListe(const Cellule *c, Liste l) {
    return c->suivant;
}
void affichageListe(Liste l) {
    Cellule * it = premiereCelluleListe(l);
    while(it != NULL) {
        afficheElement(elementCelluleListe(it));
        it = it->suivant;
    }
    printf("\n");
}
void suppressionEnTeteListe(Liste *l) {
    Cellule * tmp = premiereCelluleListe(*l);
    l->ad = l->ad->suivant;
    free(tmp);
}
static void ajouterApartirDeCellule(const Elem * const e,Cellule *c) {
    if(c->suivant == NULL) {
        Cellule * tmp = malloc(sizeof(Cellule));
        tmp->suivant = NULL;
        tmp->info = *e;
        c->suivant = tmp;
    } else {
        ajouterApartirDeCellule(e,c->suivant);
    }
}
void ajoutEnQueueListe(Elem e,Liste *l) {
    if(testListeVide(*l)) {
        ajoutEnTeteListe(e,l);
    } 
    else {
        ajouterApartirDeCellule(&e,premiereCelluleListe(*l));
    }
    
}