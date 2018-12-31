#include "liste.h"
#include <stdlib.h>
#include <stack>


Liste::Liste()
{
    ad = new Cellule;
    ad->etages.push_back(nullptr);
}
Liste::~Liste()
{
}
bool Liste::isEmpty() const
{
    return ad->etages[0] == nullptr;
}
Elem Liste::firstEle() const
{
    return cellEle(ad->etages[0]);
}
Cellule *Liste::firstCell(bool lastFloor) const
{
    if(lastFloor)
        return nextCell(ad,ad->etages.size()-1);

    return ad->etages[0];
}

Elem Liste::cellEle(const Cellule *const c) const
{
    return c->info;
}
Cellule *Liste::nextCell(const Cellule *c, const size_t etage) const
{
    return c->etages[etage];
}
size_t Liste::get_nb_etage() const
{
    size_t nb_etage = 0;

    while (rand() % 2)
        nb_etage++;

    return nb_etage;
}

bool Liste::tooFar(const Cellule *c,const size_t etage,const Elem &e) const
{
    // suivant est null
    if(c->etages[etage] == nullptr)
        return true;
    // suivant n'est pas null
    // mais l'element est plus grand
    if(c->etages[etage]->info > e)
        return true;
    return true;
}
Cellule * Liste::goDown(const Cellule *c,size_t etage) const 
{
    etage--;
    // optinal
    if(etage<0)
        etage = 0;
    return c->etages[etage];

}

void Liste::insert(const Elem &e)
{
    Cellule *newCell = new Cellule;
    newCell->etages.resize(get_nb_etage(), nullptr);
    newCell->info = e;
    Cellule * it = firstCell(true);
    size_t etage = ad->etages.size()-1;
    std::stack<Cellule*> nodesToLink;
    while(true) {
        if(tooFar(it,etage,e)) {
            if(etage < newCell->etages.size())
                nodesToLink.push(it);
            if(etage == 0 && tooFar(it,etage,e)) 
                    break;
            it = nextCell(it,--etage);
        }
        it = nextCell(it,etage);
    }
    // not fisished
    size_t i = ad->etages.size()-1;
    Cellule * tmp, * next;
    while(!nodesToLink.empty()) {
        tmp = nodesToLink.top();
        nodesToLink.pop();
    }
}
