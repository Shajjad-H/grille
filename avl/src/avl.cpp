#ifndef __ARBRE_AVL__CPP__
#define __ARBRE_AVL__CPP__


#include "avl.hpp"
#include <cstddef>
#include <iostream>

template<typename D>
Node<D>::Node(const D &d)
{
	this->data = d;
	this->l = NULL;
	this->r = NULL;
	this->dif = 0;
}

template<typename D>
Node<D>::Node(const D &d,const int diff)
{
	this->data = d;
	this->l = NULL;
	this->r = NULL;
	this->dif = diff;
}

template<typename D>
Avl<D>::Avl()
{
	root = NULL;
}
template<typename D>
Avl<D>::~Avl()
{
	erase();
}

template<typename D>
bool Avl<D>::isEmpty() const
{
	return root == NULL;
}

template<typename D>
Node<D>* Avl<D>::search_rec(const Node<D> * const n, const D&d) const
{
	if(n == NULL)
		return NULL;
	if(d < n->data)
		return search_rec(n->l,d);
	if(d > n->data)
		return search_rec(n->r,d);
	return n;
}

template<typename D>
void Avl<D>::erase_rec(Node<D> * &n)
{
	if(n == NULL)
		return;
	erase_rec(n->l);
	erase_rec(n->r);
	delete n;
	n = NULL;
}

template<typename D>
void Avl<D>::erase()
{
	erase_rec(root);
}

template<typename D>
void Avl<D>::right_rotation(Node<D> * &n)
{
	Node<D> * tmp = n->l;
	n->l = tmp->r;
	tmp->r = n;
	n = tmp;
}


template<typename D>
void Avl<D>::left_rotation(Node<D> * &n)
{
	Node<D> * tmp = n->r;
	n->r = tmp->l;
	tmp->l = n;
	n = tmp;
}


template<typename D>
void Avl<D>::print_ver_rec(const Node<D>* const n,const unsigned int nb_space) const
{
	if(n == NULL)
		return;

	print_ver_rec(n->r,nb_space+1);

	std::cout<<std::endl;
	for (unsigned int i = 0; i < nb_space; ++i)
		std::cout<<"  ";
	std::cout<<"|-";
	
	std::cout<<n->data;

	print_ver_rec(n->l,nb_space+1);

}

template<typename D>
void Avl<D>::print() const
{
	std::cout<<"r";
	print_ver_rec(root,0);
	std::cout<<std::endl<<"l"<<std::endl;
}



template<typename D>
void Avl<D>::insert_rec(Node<D>*& n, const D& d)
{
	if(n == NULL)
		n = new Node<D>(d);

	else if(d < n->data)
		insert_rec(n->l,d);
	else if(d > n->data)
		insert_rec(n->r,d);	
}


template<typename D>
void Avl<D>::insert(const D &data)
{
	//insert_rec(root,data);
	insert_rec_nop(root,data);
}


template<typename D>
int Avl<D>::height_rec(const Node<D>* const n) const
{
	if(n == NULL)
		return -1;
	int h_r = height_rec(n->r);
	int h_l = height_rec(n->l);
	return 1 + Max(h_r,h_l);
}

template<typename D>
int Avl<D>::height() const
{
	return height_rec(root);
}


template<typename D>
int Avl<D>::Max(const int n, const int m) const
{
	if(n<m)
		return m;
	return n;
}

template<typename D>
void Avl<D>::rotate_right()
{
	right_rotation(root);
}


template<typename D>
void Avl<D>::rotate_left()
{
	left_rotation(root);
}

template<typename D>
bool Avl<D>::insert_rec_nop(Node<D>* &n,const D& d)
{
	bool l_un_blance = 0;
	bool r_un_blance = 0;
	if(n == NULL)
	{
		n = new Node<D>(d);
		return true;
	}
	else if(d < n->data)
		l_un_blance = insert_rec_nop(n->l,d);
	else if(d > n->data)
		r_un_blance = insert_rec_nop(n->r,d);
	else return false;

	// balance
	n->dif += (int)l_un_blance - (int)r_un_blance;
	n->dif = height_rec(n->l) - height_rec(n->r);

	return balance(n);

}

template<typename D>
bool Avl<D>::balance(Node<D>* &n)
{

	if(n->dif > 1)
	{
		if(n->l->dif == 1)
			right_rotation(n);
		else {
			left_rotation(n->l);
			right_rotation(n);
		}
		return false;
	}
	else if(n->dif < -1)
	{
		if(n->r->dif == - 1)
			left_rotation(n);
		else {
			right_rotation(n->r);
			left_rotation(n);
		}
		return false;
	}
	return true;
}







#endif



