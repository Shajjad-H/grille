#ifndef __GRILLE__H__SH__
#define __GRILLE__H__SH__

# define BLACK    "\033[0;30m"
# define RED      "\033[0;31m"
# define GREEN    "\033[0;32m"
# define YELLOW   "\033[0;33m"


#include <vector>
#include <queue>

class Grille;

typedef int grille_data;
typedef int size_g;

enum Couleur
{
	blanc,
	gris,
	noir
};

enum Voisin
{
	nord,
	sud,
	est,
	west
};

class Sommet
{
	friend Grille;

  private:
	grille_data data;
	Couleur color;
	bool antenne;
	size_g color_term;
  public:
	Sommet()
	{
		color = blanc;
		antenne = false;
		color_term = 0;
	}
	~Sommet(){};
	bool operator<(const Sommet &) const;
};

struct touple
{
	size_g t1, t2;
};


class Chemin
{
	friend Grille;

  private:
	//touple sommet_actuelle;
	//touple parent;
	size_g sommet_actuelle;
	size_g index_antenne;
	float distance;
	
  public:
	Chemin();
	Chemin(const size_g index_antenne, const size_g sommet_actuelle, const float d);
	bool operator<(const Chemin &) const;
};

class Grille
{

  private:
	Sommet * array_sommet;
	size_g L, C;

	size_g voisin_nord(const size_g row, const size_g col) const;
	size_g voisin_sud(const size_g row, const size_g col, const size_g row_size) const;
	size_g voisin_est(const size_g row, const size_g col, const size_g col_size) const;
	size_g voisin_west(const size_g row, const size_g col) const;

	/**
	 * emplier tous les voisins possible et mettre à jours sa couleur. si aucune n'est empilée retourn faux.
	*/
	void empiler_tous_les_voisins(std::priority_queue<Chemin> & priorite, Chemin &);
	void empiler_un_voisin(std::priority_queue<Chemin> & priorite, Chemin &, const Voisin);
	void print_chemin(Chemin &c) const;
	void print_PQ(std::priority_queue<Chemin> &priorite) const;
	bool grid_changed() const;
	void init_grilles(const size_g l, const size_g c);
	void put_chemin_in_tab(const Chemin &c);
	void init_colors();

  public:
	Grille(const size_g l, const size_g c);
	Grille(const char *file);
	~Grille();
	size_g index(const size_g row, const size_g col) const;
	size_g voisin(const size_g row, const size_g col, const Voisin direction) const;
	size_g voisin(const size_g index, const Voisin direction) const;
	void load(const char *file_name);
	void alg_dijkstra(int ind_req);
	void print_grille_hauteur() const;
	void  display_vect(std::vector<std::vector<Chemin>>& vect);

	/*
		ajoute un antenne aux indices (i,j)
	*/
	void ajouter_antenne(const size_g row, const size_g col);
	/*
		affiche tous les antenne dans la grille
	*/
	void affiche_antenne() const;

	/*
		precondition: grille initialiser correctement
		post-condition: retourne le chemin le plus court vers une antenne.
						le tableau retourné stocke les indices des sommets à travers où 
						le chemin est tracer. le dernier dans le tableau est l'indice de 
						l'antenne.
	*/
	std::vector<size_g> antenne_la_plus_proche(const size_g row, const size_g col);
	//bool estAntenne(const size_g row, const size_g col) const;
	bool estAntenne(const Chemin &) const;
	bool estAntenne(const size_g row, const size_g col) const;
	Couleur getColor(const size_g index) const;
	/**
	 * precondition: grille intialiser
	 * post-condition: retourne le parcour de dijkstra
	 * 				   
	*/
	void dijkstra();
	std::priority_queue<Chemin> get_antenne();
	void display_colors();
	
};

#endif
