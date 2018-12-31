#include "grille.hpp"
#include "test.hpp"
#include <iostream>

using namespace std; 


void test::algo_dijkstra()
{
    Grille g("data/file.txt");
    g.print_grille_hauteur();
    g.ajouter_antenne(2,1);
    g.ajouter_antenne(0,0);
    g.ajouter_antenne(4,4);
    g.affiche_antenne();
    // std::priority_queue<Chemin> priorite = g.get_antenne(vect_chemin_antenne);
    g.display_colors();
    // g.display_vect(vect_chemin_antenne);
    g.load("data/file1.txt");
    int r,c;
    cout<<"ajouter 2 anetenne"<<endl<<"antenne 1:";
    cin>>r>>c;
    g.ajouter_antenne(r,c);
    cout<<"antenne 2:";
    cin>>r>>c;
    g.ajouter_antenne(r,c);    
    g.ajouter_antenne(9,9);
    g.ajouter_antenne(3,0);
    g.ajouter_antenne(8,8);
    g.ajouter_antenne(2,1);

    g.display_colors();

}
