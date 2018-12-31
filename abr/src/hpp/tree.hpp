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
	Node<D> * search_rec(const Node<D> * const n,const D &d) const;
	void insert_rec(Node<D>* &n, const D& d);
	void print_infix_rec(const Node<D>* const n) const;
	void erase_rec(Node<D> * &n);	
	void insert_it(Node<D>* &n,const D&d);

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
	void insert(const D &data,const bool itratif=true);
	/*
		precondition: operators<>
		post-condition: only the data is inserted of the node.
		param: Node<D> n is the data, bool iteratif choise of insertion mode
			   either recursive or iterative.
	*/
	void insert(const Node<D> &n,const bool iteratif=true);
	/*
		precondition: operators<>
		post-condition: -> NULL if data ! in tree
						-> pointer to the node if data in tree.
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

	void insert_it(const D & data);
	

};


#endif


#include "tree.cpp"
