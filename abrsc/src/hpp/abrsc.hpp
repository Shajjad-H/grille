#ifndef __ARBRE_BIN_REC_HPP__
#define __ARBRE_BIN_REC_HPP__

// operators<>: the operators < and > should be overloaded for type D.
 

 

template<typename D>
class Tree;

template<typename D>
class Node {
	friend Tree<D>;
private:
	D data;
	Node<D>* l;
	Node<D>* r;
	bool has_right;
public:
	Node(const D &data);
	Node(const Node<D> &n);
	Node(const D &data,const Node<D>* const l,const Node<D>* const r);
	Node<D> * left() const;
	Node<D> * right() const;
	D getData() const;
};

template<typename D>
class Tree {

private:
	Node<D> * root;
	Node<D> * last_l;
	Node<D> * search_rec(const Node<D> * const n,const D &d) const;
	void insert_rec(Node<D>* &n, const D& d);
	void insert_it(Node<D>* &n,const D&d);
	void print_infix_rec(const Node<D>* const n) const;
	void erase_rec(Node<D> * &n);
	Node<D> * plus_a_gauche(const Node<D> * const) const;
	void insert_rec(Node<D>*& n, Node<D> * infix_ptr, const D& d);

public:
	Tree();
	Tree(const Tree<D> &a);
	~Tree();
	/*
		precondition: none
		post-condition: deletes all nodes and
	*/
	void erase();
	Tree<D>& operator=(const Tree<D> &a);
	bool isEmpty() const;
	/*
		precondition: operators<> 
		post-condition: data is inserted to the right place in the tree.
	*/
	void insert(const D &data);
	/*
		precondition: operators<>
		post-condition: only the data is inserted of the node.

	*/

	Node<D> * search(const D &data) const;
	/*
		precondition: none
		post-condition: print (l node right)
	*/
	void print_infix() const;
	/*	
		precondition: none
		post-condition: print (l node right)
	*/
	void print_prefix() const;
	
	/*	
		precondition: none
		post-condition: print (l node right)
	*/
	void print_postfix() const;
	/*
		precondition: none
		post-condition: deletes the node where the data is.
	*/
	void remove(const D &data,const bool iteratif=true);
	
	typedef void (*infix_func_type)(const Node<D> * const);
	void infix(const Node<D> * const n,infix_func_type infix_func) const;
	

};


#endif


#include "abrsc.cpp"










