#ifndef __ARBRE_BIN_REC_CPP__
#define __ARBRE_BIN_REC_CPP__

#include "tree.hpp"
#include <iostream>

template<typename D>
Node<D>::Node(const D &data)
{
	this->data = data;
	l = NULL;
	r = NULL;
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
void Tree<D>::insert_rec(Node<D>*& n, const D& d)
{
	if(n == NULL)
		n = new Node<D>(d);

	else if(d < n->data)
		insert_rec(n->l,d);
	else if(d > n->data)
		insert_rec(n->r,d);	
}


template<typename D>
void Tree<D>::insert_it(Node<D>*& n, const D& d)
{
	Node<D> ** it = &n;
	while(*it != NULL)
	{
		if(d < (*it)->data)
		{
			Node<D> **tmp = &((*it)->l);
			it = tmp;
		}
		else if(d > (*it)->data)
		{
			Node<D> **tmp = &((*it)->r);
			it = tmp;
		}
		// the data already existes
		else return;
	}
	
	*it = new Node<D>(d);
}

template<typename D>
void Tree<D>::insert_it(const D& d)
{
	insert_it(root,d);
}


template<typename D>
void Tree<D>::insert(const D& d,const bool it)
{
	if(it) insert_it(root,d);
	else insert_rec(root,d);
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


