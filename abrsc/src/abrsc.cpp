#ifndef __ARBRE_BIN_REC_CPP__
#define __ARBRE_BIN_REC_CPP__

#include "abrsc.hpp"
#include <iostream>

template<typename D>
Node<D>::Node(const D &data)
{
	this->data = data;
	l = NULL;
	r = NULL;
	this->has_right = false;
}


template<typename D>
Node<D>::Node(const Node<D> &n)
{
	data = n.getData();
	l = n.left();
	r = n.right();
}


template<typename D>
Node<D>::Node(const D &data,const Node<D>* const l,const Node<D>* const r)
{
	this->data = data;
	this->l = l;
	this->r = r;
}


template<typename D>
Tree<D>::Tree()
{
	root = NULL;
}

template<typename D>
Tree<D>::~Tree()
{
	erase();
}

template<typename D>
void Tree<D>::erase()
{
	erase_rec(root);
}

template<typename D>
void Tree<D>::erase_rec(Node<D> * &n)
{
	if(n == NULL)
		return;
	erase_rec(n->l);
	if(n->has_right)
		erase_rec(n->r);
	delete n;
	n = NULL;
}


template<typename D>
bool Tree<D>::isEmpty() const
{
	return root == NULL;
}

template<typename D>
Node<D>* Tree<D>::search_rec(const Node<D> * const n, const D&d) const
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
void Tree<D>::insert_rec(Node<D>*& n,Node<D> * infix_ptr, const D& d)
{
	if(n == NULL )
	{
		n = new Node<D>(d);
		n->r = infix_ptr;
	}
	else if(d > n->data)
	{
		if(!n->has_right)
			n->r = NULL;
		insert_rec(n->r,infix_ptr,d);
		n->has_right = true;
	}
	else if(d <= n->data)
		insert_rec(n->l,n,d);

}

template<typename D>
Node<D> * Tree<D>::plus_a_gauche(const Node<D> * const n) const
{
	if(n == NULL)
		return NULL;

	Node<D> * it = n;
	
	while(it->l != NULL)
		it = it->l;
	return it;
}


template<typename D>
void Tree<D>::infix(const Node<D> * const n, infix_func_type infix_func) const
{
	Node<D> * it = n;
	while(it != NULL)
	{
		infix_func(it);
		if(!it->has_right)
			it = it->r;
		else it = plus_a_gauche(it->r);

	}
}

template<typename D>
void Tree<D>::insert(const D& d)
{
	insert_rec(root,NULL,d);
}

template<typename D>
void Tree<D>::print_infix_rec(const Node<D>* n) const
{
	if(n == NULL)
		return;

	std::cout<<"( ";
	if(n->l != NULL)
		print_infix_rec(n->l);

	std::cout<<n->data;

	if(n->r != NULL)
		print_infix_rec(n->r);
	std::cout<<" )";
}

template<typename D>
void Tree<D>::print_infix() const
{
	print_infix_rec(root);
	std::cout<<std::endl;
}


template<typename D>
void Tree<D>::remove(const D& d,const bool it)
{
	
}

#endif


