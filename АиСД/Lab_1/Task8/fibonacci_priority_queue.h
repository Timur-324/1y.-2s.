#ifndef FIBONACCI_H
#define FIBONACCI_H

#include <cstring>
#include <stdexcept>
#include <iostream>
#include "binomial_priority_queue.h"

class fibonacci_priority_queue final:
    public binomial_priority_queue
{
public:
    fibonacci_priority_queue(
	    int (*priorities_comparer)(int, int)):
            binomial_priority_queue(priorities_comparer){}
public:

    void insert(
		int priority,
		char const *value) override
	{
		fibonacci_priority_queue new_heap(_priorities_comparer);
		new_heap._root = create_node(priority, value);
		new_heap._root->brother = new_heap._root;
		new_heap._values_count = 1;
		merge(&new_heap);
	}

    void merge(
        mergeable_priority_queue *to_merge_from) override
    {
        fibonacci_priority_queue *fpq_to_merge_from;
        fpq_to_merge_from = dynamic_cast<fibonacci_priority_queue *>(to_merge_from);
        if(fpq_to_merge_from == nullptr)
        {
            throw std::invalid_argument("Parameter must be of type fibonacci_priority_queue *");
        }
        
        if(this == to_merge_from)
        {
            return;
        }
        if(fpq_to_merge_from->_root == nullptr)
        {
            return;
        }
        if(this->_root == nullptr && fpq_to_merge_from->_root != nullptr)
        {
            //передвигаем всё с одной кучи в другую
            this->_root = fpq_to_merge_from->_root;
            this->_values_count = fpq_to_merge_from->_values_count;
            fpq_to_merge_from->_root = nullptr;
            fpq_to_merge_from->_values_count = 0;
            return;
        }

        this->_values_count = this->_values_count + fpq_to_merge_from->_values_count;
        fpq_to_merge_from->_values_count = 0;

        node *temp = this->_root->brother;
        _root->brother = fpq_to_merge_from->_root;
        node *temp2 = fpq_to_merge_from->_root;
        while (temp2->brother != fpq_to_merge_from->_root)
        {
            temp2 = temp2->brother;
        }

        temp2->brother = temp;

        this->_root = _priorities_comparer(this->_root->priority, fpq_to_merge_from->_root->priority) >= 0
            ? this->_root
            : fpq_to_merge_from->_root;

        fpq_to_merge_from->_root = nullptr;
    }

    void consolidate()
    {
        if(_root == nullptr)
        {
            return;
        }

        fibonacci_priority_queue temp(*this);
        _values_count = 0;

        binomial_priority_queue *base_temp = static_cast<binomial_priority_queue*>(&temp);
        binomial_priority_queue::merge(base_temp);
    }

    char * remove_max() override
    {
        // first step: remove max + to get new heap and merge with this
        if(_root == nullptr)
        {
            throw empty_priority_queue_exception();
        }

        node *tree_to_split = _root;
        if(tree_to_split->brother == tree_to_split)
        {
            _root = nullptr; 
        }
        else
        {
            node *new_max_tree = tree_to_split->brother;
            node *runner = tree_to_split->brother;
            while(runner->brother != _root)
            {
                if(_priorities_comparer(runner->priority, new_max_tree->priority) > 0)
                {
                    new_max_tree = runner;
                }
                runner = runner->brother;
            }
            runner->brother = runner->brother->brother;
            _root = new_max_tree;
        }

        _values_count -= (1 << get_rank(tree_to_split));

        fibonacci_priority_queue new_heap(_priorities_comparer);
        new_heap._root = tree_to_split->children;
        new_heap._values_count = (1 << get_rank(tree_to_split)) - 1;

        char *to_return = tree_to_split->value;
        delete tree_to_split;

        merge(&new_heap);

        //second step: we need to make our fpq into bpq
        consolidate();

        return to_return;
    }
};


#endif