#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>

template <typename Cmp>
class lessThan{
public:
	bool operator() (const Cmp &a, const Cmp &b) const
	{
		return a < b;
	}
};

template <typename Comparable, typename Comparator>
class BinarySearchTree
{
public:
	BinarySearchTree() { root = nullptr; }
	BinarySearchTree(const BinarySearchTree& rhs) { operator= (rhs); }
	const BinarySearchTree& operator= (const BinarySearchTree& rhs);
	BinarySearchTree& operator<< (const Comparable& ele);
	~BinarySearchTree() { makeEmpty(); }

	const Comparable& findMax() const
	{
		BinaryNode tmp = findMax(root);
		return tmp->ele;
	}
	const Comparable& findMin() const
	{
		BinaryNode tmp = findMin(root);
		return tmp->ele;
	}
	bool contains(const Comparable& x) const
	{ return contains(x, root); }
	bool isEmpty() const { return root == nullptr; }
	void printTree(std::ostream& out = std::cout) const
	{
		if (isEmpty())
			out << "Empty tree!" << std::endl;
		else
			printTree(out, root);
	}

	void makeEmpty() { makeEmpty(root); }
	void insert(const Comparable& x) { insert(x, root); }
	void remove(const Comparable& x) { remove(x, root); }

private:
	struct BinaryNode
	{
		Comparable ele;
		BinaryNode* left;
		BinaryNode* right;
		BinaryNode(const Comparable& e, BinaryNode* l, BinaryNode* r)
			: ele(e), left(l), right(r) { }
	};

	BinaryNode *root;
	Comparator isLessThan;

	void insert(const Comparable& x, BinaryNode* & t);
	void remove(const Comparable& x, BinaryNode* & t);
	BinaryNode* removeMin(BinaryNode* & t);

	BinaryNode* findMax(BinaryNode* t) const;
	BinaryNode* findMin(BinaryNode* t) const;

	bool contains(const Comparable& x, BinaryNode* t) const;
	void makeEmpty(BinaryNode * & t);
	void printTree(std::ostream& cout, BinaryNode *t, int depth = 1) const;

	BinaryNode* clone(BinaryNode* t) const;
};


#define Tree BinarySearchTree<Comparable, Comparator>

template <typename Comparable, typename Comparator>
Tree& Tree::operator<< (const Comparable& ele)
{
	this->insert(ele);

	return *this;
}

template <typename Comparable, typename Comparator>
typename Tree::BinaryNode* Tree::findMin(
	typename Tree::BinaryNode* t) const
{
	if (t == nullptr)
		return nullptr;
	if (t->left == nullptr)
		return t;
	return findMin(t->left);

	/*The iterative implement of Binary Search Tree function "findMin".
	if (t != nullptr)
	{
		while (t->left != nullptr)
			t = t->left;
	}

	return t;*/
}

template <typename Comparable, typename Comparator>
typename Tree::BinaryNode* Tree::findMax(
	typename Tree::BinaryNode* t) const
{
	if (t == nullptr)
		return nullptr;
	if (t->right == nullptr)
		return t;
	return findMax(t->right);

	/*The iterative implement of Binary Search Tree function "findMax".
	if (t != nullptr)
	{
		while (t->right != nullptr)
			t = t->right;
	}

	return t;*/
}

template <typename Comparable, typename Comparator>
bool Tree::contains(const Comparable& x, typename Tree::BinaryNode* t) const
{
	if (t == nullptr)
		return false;
	else if (isLessThan(x, t->ele))
		return contains(x, t->left);
	else if (isLessThan(t->ele, x))
		return constains(x, t->right);
	else
		return true;

	/*The iterative implement of BST function "contains".
	while (t £¡ = nullptr)
	{
		if (isLessThan(x, t->ele))
			t = t->left;
		else if (isLessThan(t->ele, x))
			t = t->right;
		else
			return true;
	}
	
	return false;*/
}

template <typename Comparable, typename Comparator>
void Tree::insert(const Comparable& x, typename Tree::BinaryNode* & t)
{
	if (t == nullptr)
		t = new BinaryNode(x, nullptr, nullptr);
	else if (isLessThan(x, t->ele))
		return insert(x, t->left);
	else if (isLessThan(t->ele, x))
		return insert(x, t->right);
	else
		; // Duplicated, do nothing.

	/*The iterative implement of Binary Search Tree member function "insert".
	while (t != nullptr)
	{
		if (isLessThan(x, t->ele))
			t = t->left;
		else if (isLessThan(t->ele, x))
			t = t->right;
		else
			return; // Duplicated, do not need to insert a second time.
	}

	t = new BinaryNode(x, nullptr, nullptr);*/
}

template <typename Comparable, typename Comparator>
void Tree::remove(const Comparable& x, typename Tree::BinaryNode* & t)
{
	if (t == nullptr)
		return;
	else if (isLessThan(x, t->ele))
		return remove(x, t->left);
	else if (isLessThan(t->ele, x))
		return remove(x, t->right);
	else if (t->left != nullptr && t->right != nullptr)
	{
		//More efficient version.
		BinaryNode* tmp = removeMin(t->right);
		t->ele = tmp->ele;
		if (tmp == t->right)
			t->right = tmp->right;
		delete tmp;

		//The original version
		/*t->ele = findMin(t->right)->ele;
		remove(t->ele, t->right);
		*/
	}
	else
	{
		BinaryNode* oldNode = t;
		t = t->left ? t->left : t->right;
		delete oldNode;
	}
}

template <typename Comparable, typename Comparator>
typename Tree::BinaryNode* Tree::removeMin(typename Tree::BinaryNode* & t)
{
	if (t == nullptr) //Null tree.
		return nullptr;

	if (t->left != nullptr) //Normal condition.
	{
		BinaryNode* tmp = t->left;
		if (tmp->left == nullptr)
		{
			t->left = tmp->right;
			return tmp;
		}
	}
	else//The condition that the right son tree does not have a left son tree.
	{
		return t;
	}

	return removeMin(t->left);
}

template <typename Comparable, typename Comparator>
void Tree::makeEmpty(typename Tree::BinaryNode* & t)
{
	if (t != nullptr)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}

	t = nullptr;
}

template <typename Comparable, typename Comparator>
typename Tree::BinaryNode* Tree::clone(typename Tree::BinaryNode* t) const
{
	if (t == nullptr)
	{
		return nullptr;
	}

	return new BinaryNode(t->ele, clone(t->left), clone(t->right) ); //A marvelous implement!
}

template <typename Comparable, typename Comparator>
const Tree& Tree::operator= (const Tree& rhs)
{
	if (*this != rhs)
	{
		makeEmpty();
		root = clone(rhs.root);
	}

	return *this;
}

template <typename Comparable, typename Comparator>
void Tree::printTree(std::ostream& out, typename Tree::BinaryNode* t, int depth) const
{
	if (t != nullptr)
	{
		//Pre-order traversal
		for (int i = 0; i < depth; i++)
		{
			out << "  ";
		}
		out << t->ele << std::endl;

		++depth;
		printTree(out, t->left, depth);
		printTree(out, t->right, depth);
	}
}

#endif