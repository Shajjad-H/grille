#include "grille.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <limits>

using namespace std;

Chemin::Chemin()
{
	distance = numeric_limits<float>::infinity();
}

Chemin::Chemin(const size_g p, const size_g s_a, const float d)
{
	index_antenne = p;
	sommet_actuelle = s_a;
	distance = d;
}

bool Chemin::operator<(const Chemin &c) const
{
	return distance > c.distance;
}

void Grille::init_grilles(const size_g l, const size_g c)
{
	L = l;
	C = c;
	
	if(array_sommet) delete[] array_sommet;
	array_sommet = new Sommet[L * C];

}

void Grille::init_colors()
{
	for (size_g row = 0; row < L; row++)
		for (size_g col = 0; col < C; col++)
		{
			array_sommet[index(row,col)].color = blanc;
		}
}



Grille::Grille(const int l, const int c)
{
	array_sommet = NULL;
	init_grilles(l,c);
}

Grille::Grille(const char *file)
{
	array_sommet = NULL;
	load(file);
}

void Grille::load(const char *file_name)
{
	ifstream myfile(file_name);
	if (!myfile.is_open())
	{
		cout << "ficher n'est pas ouvert " << file_name << endl;
		return;
	}
	size_g size = 0;
	myfile >> size;
	L = size;
	myfile >> size;
	C = size;
	size_g ind = 0;
	grille_data d;

	init_grilles(L,C);
	for (size_g row = 0; row < L; row++)
		for (size_g col = 0; col < C; col++)
		{
			ind = index(row, col);
			myfile >> d;

			array_sommet[ind].data = d;
		}
}

void Grille::ajouter_antenne(const size_g row, const size_g col)
{
	int ind = index(row, col);

	if(row >= L)
	{
		cout<<"index invilide dans ajouter_antenne ("<<row<<","<<col<<")"<<endl;
		return;		
	}
	if(col >= C)
	{
		cout<<"index invilide dans ajouter_antenne ("<<row<<","<<col<<")"<<endl;
		return;		
	}

	array_sommet[ind].antenne = true;

}

/*
void Grille::alg_dijkstra(int ind_req)
{

}
*/

void Grille::print_grille_hauteur() const
{
	size_g ind = 0;
	for (size_g row = 0; row < L; row++)
	{
		for (size_g col = 0; col < C; col++)
		{
			ind = index(row, col);
			cout <<"("<<row<<","<<col<<") "<<array_sommet[ind].data << " | ";
		}

		cout << endl;
	}
}

void Grille::affiche_antenne() const
{
	size_g ind = 0;
	for (size_g row = 0; row < L; row++)
	{
		for (size_g col = 0; col < C; col++)
		{
			ind = index(row, col);
			if (array_sommet[ind].antenne)
				cout << "🔥"
					 << " | ";
			else
				cout << "🏠"
					 << " | ";
		}

		cout << endl;
	}
}

size_g Grille::index(const size_g row, const size_g col) const
{
	return row * C + col;
}

size_g Grille::voisin_nord(const size_g row, const size_g col) const
{
	if (row < 1)
		return -1;
	return index(row - 1, col);
}

size_g Grille::voisin_sud(const size_g row, const size_g col, const size_g row_size) const
{
	if (row < row_size - 1)
		return index(row + 1, col);
	return -1;
}

size_g Grille::voisin_west(const size_g row, const size_g col) const
{
	if (col < 1)
		return -1;
	return index(row, col - 1);
}

size_g Grille::voisin_est(const size_g row, const size_g col, const size_g col_size) const
{
	if (col < col_size - 1)
		return index(row, col + 1);
	return -1;
}

size_g Grille::voisin(const size_g row, const size_g col, const Voisin direction) const
{

	switch (direction)
	{
	case nord:
		return voisin_nord(row, col);

	case sud:
		return voisin_sud(row, col, L);

	case est:
		return voisin_est(row, col, C);

	case west:
		return voisin_west(row, col);

	default : return -1;
	}
}

size_g Grille::voisin(const size_g index, const Voisin direction) const
{
	return voisin((int)index/C,(int)index%C,direction);
}

Grille::~Grille()
{
	if(array_sommet){
		delete[] array_sommet;
		array_sommet = NULL;
	}

}


Couleur Grille::getColor(const size_g index) const
{
	return array_sommet[index].color;
}


void Grille::empiler_un_voisin(std::priority_queue<Chemin> &priorite, Chemin &c, const Voisin dir)
{
	size_g v = voisin(c.sommet_actuelle, dir);
	if (v == -1)
		return;
	if (getColor(v) == noir)
		return;
	float dist = sqrt(1 + pow((array_sommet[c.sommet_actuelle].data - array_sommet[v].data),2));
	priorite.push(Chemin(c.index_antenne,v, c.distance + dist));
	array_sommet[v].color = gris;
	
}

void Grille::empiler_tous_les_voisins(std::priority_queue<Chemin> &priorite, Chemin &c)
{

	empiler_un_voisin(priorite, c, nord);
	empiler_un_voisin(priorite, c, sud);
	empiler_un_voisin(priorite, c, est);
	empiler_un_voisin(priorite, c, west);
	
}

bool Grille::estAntenne(const Chemin &c) const
{
	return array_sommet[c.sommet_actuelle].antenne;
}

std::priority_queue<Chemin> Grille::get_antenne()
{
	priority_queue<Chemin> res;
	//size_g ind = 0;
	//int count_antenne = 0;
	int i = 1;
	for (size_g row = 0; row < L; row++)
		for (size_g col = 0; col < C; col++)
		{
			if(estAntenne(row,col))
			{

				array_sommet[index(row,col)].color_term = i;
				i++;
				res.push(Chemin(index(row, col), index(row, col), 0.0f));
			}

		}
	return res;
}

bool Grille::estAntenne(const size_g row, const size_g col) const
{
	return array_sommet[index(row,col)].antenne;
}

void Grille::put_chemin_in_tab(const Chemin &c)
{
	array_sommet[c.sommet_actuelle].color_term = array_sommet[c.index_antenne].color_term;
}

void  Grille::display_vect(vector<vector<Chemin>>& vect)
{
	for (int i = 0; i < vect.size(); i++) {
        for (int j = 0; j < vect[i].size(); j++) 
			print_chemin(vect[i][j]);
            cout  << " "; 
        cout << endl; 
    } 

}

void Grille::dijkstra()
{
	init_colors();
	priority_queue<Chemin> priorites = get_antenne();

	while (!priorites.empty())
	{
		Chemin premier = priorites.top();

		// cette site existe déjà dans le resulat avec un chemin plus court
		if(getColor(premier.sommet_actuelle) == noir){
			priorites.pop();
			continue;
		}

		empiler_tous_les_voisins(priorites, premier);

		array_sommet[premier.sommet_actuelle].color = noir;

		put_chemin_in_tab(premier);


		priorites.pop();

	}

}

void Grille::print_chemin(Chemin &c) const
{
    cout << "index_sommet_actuel: " << c.sommet_actuelle << endl;
    cout << "index_antenne: "<<  c.index_antenne << endl;
    cout << "distance: " << c.distance << endl;
	cout << "----------------------------------------------------\n";
}
void Grille::print_PQ(std::priority_queue<Chemin> &priorite) const
{
	Chemin c;
    while (!priorite.empty())
	{
		c = priorite.top();
		print_chemin(c);
		priorite.pop();
	}
}

void Grille::display_colors()
{
	
	dijkstra();
	size_g ind = 0;
	for (size_g row = 0; row < L; row++)
	{
		for (size_g col = 0; col < C; col++)
		{
			//if(array_sommet[index(row, col)].antenne)
			//{
			//	cout<<"🔥|";

			//}else{
				//cout<<array_sommet[index(row, col)].color_term<<" |";
			//}

			ind = index(row, col);
			if (array_sommet[ind].antenne)
			{

				cout <<"\x1b["<< 40 +  array_sommet[ind].color_term % 47 <<";"
				<< array_sommet[ind].color_term << "m🔥|\x1b[0m";
			}
			else
			{

				cout <<"\x1b["<< 40 +  array_sommet[ind].color_term % 47 <<";"
				<< array_sommet[ind].color_term << "m "<<array_sommet[ind].color_term<<"|\x1b[0m";
			}
		}

		cout << endl;
	}
}


/*
std::vector<size_g> antenne_la_plus_proche(const size_g row, const size_g col)
{

}*/