#ifndef __ARBRE_AVL__HPP__
#define __ARBRE_AVL__HPP__

// operators<>: the operators < and > should be overloaded for type D.
 
template<typename D>
class Avl;

template<typename D>
class Node {
	friend Avl<D>;
private:
	D data;
	Node<D>* l;
	Node<D>* r;
	int dif;
public:
	Node(const D &data);
	Node(const D &data, const int dif);
	Node(const Node<D> &n);
	Node<D> * left() const;
	Node<D> * right() const;
	int diff() const;
	D getData() const;
};

template<typename D>
class Avl {

private:
	Node<D> * root;
	Node<D> * search_rec(const Node<D> * const n,const D &d) const;
	void insert_rec(Node<D>* &n, const D& d);
	void insert_it(Node<D>* &n,const D&d);
	void print_infix_rec(const Node<D>* const n) const;
	void erase_rec(Node<D> * &n);	
	void right_rotation(Node<D> * &n);
	void left_rotation(Node<D> * &n);
	void print_ver_rec(const Node<D>* const n,const unsigned int nb_space) const;
	int height_rec(const Node<D>* const n) const;
	int Max(const int n, const int m) const;
	/*
		precondition: d init
		post-condition: insere d et equilibre.
		note: fonction pas optimiser
	*/
	bool insert_rec_nop(Node<D>* &n,const D& d);
	bool balance(Node<D>* &n);
	
public:
	Avl();
	Avl(const Avl<D> &a);
	~Avl();
	/*
		precondition: none
		post-condition: deletes all nodes and
	*/
	void erase();
	Avl<D>& operator=(const Avl<D> &a);
	bool isEmpty() const;
	/*
		precondition: operators<> 
		post-condition: data is inserted to the right place in the tree.
	*/
	void insert(const D &data);
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
	void remove(const D &data);
	/*
		precondition: none
		post-condition: the tree is printed vertically (l root r)
	*/
	void print() const;
	/*
		precondition: none
		post-condition: return the height of the root
	*/
	int height() const;

	/*
		the flowing 2 functions are only for testing purposes.
		these performes rotations around the root.
	*/
	void rotate_right();
	void rotate_left();


	

};


#endif


#include "avl.cpp"
