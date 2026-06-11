#ifndef LEFTIST_PRIORITY_QUEUE
#define LEFTIST_PRIORITY_QUEUE

#include <iostream>
#include <stdexcept>
#include <cstring>
#include "mergeable_priority_queue.h"

class leftist_priority_queue :
    public mergeable_priority_queue
{
private:
    struct node
	{
		char *value;
		int priority;
		node *left;
		node *right;
		int rank;
	};

private: 
	node *_root;
	int (*_priorities_comparer)(int, int);
	size_t _values_count;

//help functions
private: 
	static node * create_node(
		char const * value, 
		int priority)
	{
		if(!value)
		{
			return nullptr;
		}
		node * result = new node;
		result->priority = priority;
		result->value = new char[strlen(value) + 1];
		strcpy(result->value, value);
		result->left = nullptr;
		result->right = nullptr;
		result->rank = 0;
		return result;
	}

	static void delete_node_value(
		node * node)
	{
		delete[] node->value;
		node->value = nullptr;
	}

	static node * copy_tree(
		node const * n)
	{
		if(n == nullptr)
		{
			return nullptr;
		}

		node * copy = create_node(n->value, n->priority);
		copy->rank = n->rank;
		copy->left = copy_tree(n->left);
		copy->right = copy_tree(n->right);
		return copy;
	}

	static void delete_tree(
		node * n)
	{
		if(!n)
		{
			return;
		}
		delete_tree(n->left);
		delete_tree(n->right);
		delete_node_value(n);
		delete n;
	}

	static int get_rank(
		node * n) 
	{
        return n ? n->rank : -1;
	}

	static node * merge_trees(
		node* x, 
		node* y) 
	{
    	if (!x)
		{
			return y;
		}
		if (!y)
		{
			return x;
		}	
    	if (x->priority < y->priority) 
		{
        	std::swap(x, y);
    	}

    	x->right = merge_trees(x->right, y);

    	if (get_rank(x->left) < get_rank(x->right)) 
		{
        	std::swap(x->left, x->right);
    	}

    	x->rank = get_rank(x->right) + 1;

    	return x;
	}


public:
	leftist_priority_queue(
		int (*priority_comparer)(int, int)):
		_priorities_comparer(priority_comparer),
		_root(nullptr),
		_values_count(0){}

	~leftist_priority_queue() noexcept override
	{
		delete_tree(_root);
	}

	leftist_priority_queue(
		leftist_priority_queue const &copy_from) :
		_priorities_comparer(copy_from._priorities_comparer),
		_root(copy_tree(copy_from._root)),
		_values_count(copy_from._values_count){}

	leftist_priority_queue &operator=(
		leftist_priority_queue const & other)
	{
		if(this == &other)
		{
			return *this;
		}
		delete_tree(_root);
		_root = copy_tree(other._root);
		_values_count = other._values_count;
		return *this;
	}

public: 

	// void debug_print() const
	// {
	// 	node* runner = _root;

	// 	std::cout << _values_count << ": ";
		
	// 	if (runner == nullptr)
	// 	{
	// 		std::cout << "<EMPTY>" << std::endl;
	// 		return;
	// 	}
		
	// 	do
	// 	{
	// 		std::cout << 'B' << get_rank(runner) << '<' << runner->priority << '>' << " -> ";
	// 		runner = runner->brother;
	// 	} while (runner != _root);
	// 	std::cout << std::endl;
	// }

	void merge(
		mergeable_priority_queue *to_merge_from) override
	{
		leftist_priority_queue * lpq_to_merge_from;

		if ((lpq_to_merge_from = dynamic_cast<leftist_priority_queue*>(to_merge_from)) == nullptr)
		{
			throw std::invalid_argument("Parameter must be of type leftist_priority_queue *");
		}

		if (this == to_merge_from)
		{
			return;
		}

		if (lpq_to_merge_from->_root == nullptr)
		{
			return;
		}

		_root = merge_trees(_root, lpq_to_merge_from->_root);
		_values_count += lpq_to_merge_from->_values_count;

		lpq_to_merge_from->_root = nullptr;
		lpq_to_merge_from->_values_count = 0;
		
	}
		
	mergeable_priority_queue *meld(
		mergeable_priority_queue const *to_meld_from) const override
	{
		leftist_priority_queue const * lpq_to_meld_from;

		if ((lpq_to_meld_from = dynamic_cast<leftist_priority_queue const *>(to_meld_from)) == nullptr)
		{
			throw std::invalid_argument("Parameter must be of type leftist_priority_queue const *");
		}

		leftist_priority_queue *to_meld_into = new leftist_priority_queue(*this);
		to_meld_into->_root = merge_trees(to_meld_into->_root, lpq_to_meld_from->_root);
		to_meld_into->_values_count += lpq_to_meld_from->_values_count;
		return to_meld_into;

	}

	void insert(
		int priority,
		char const *value) override
	{
		if(value == nullptr)
		{
			throw std::invalid_argument("insert value can not be NULL!");
		}
		if(priority < 0)
		{
			throw std::invalid_argument("insert priority must be more than 0");
		}
		leftist_priority_queue new_heap(_priorities_comparer);
		new_heap._root = create_node(value, priority);
		new_heap._values_count = 1;
		merge(&new_heap);	
	}

	char *remove_max() override
	{
		if (!_root) 
		{
        	throw std::runtime_error("remove_max: queue is empty!");
    	}
    	size_t len = strlen(_root->value);
    	char* max_value_copy = new char[len + 1];
    	strcpy(max_value_copy, _root->value);
    	node* old_root = _root;
    	_root = merge_trees(old_root->left, old_root->right);
    	delete_node_value(old_root);
    	delete old_root;
    	--_values_count;
    	return max_value_copy;
	}

	char const *get_max() override
	{
		if (!_root) 
		{
        	throw std::runtime_error("get_max: queue is empty!");
    	}
    	return _root->value;
	}
};
    

#endif