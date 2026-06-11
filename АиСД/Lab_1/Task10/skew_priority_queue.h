#ifndef SKEW_HE
#define SKEW_H

#include <iostream>
#include <stdexcept>
#include "leftist_priority_queue.h"

class skew_priority_queue final: 
    public leftist_priority_queue    
{
public:
    skew_priority_queue(
        int (*priorities_comparer)(int, int)):
            leftist_priority_queue(priorities_comparer){}

private:
    void keep_leftist(
		node * n) override
	{}
public: 

    mergeable_priority_queue *meld(
		mergeable_priority_queue const *to_meld_from) const override
	{
		skew_priority_queue const * spq_to_meld_from;

		if ((spq_to_meld_from = dynamic_cast<skew_priority_queue const *>(to_meld_from)) == nullptr)
		{
			throw std::invalid_argument("Parameter must be of type skew_priority_queue const *");
		}

		skew_priority_queue *to_meld_into = new skew_priority_queue(*this);
		to_meld_into->_root = to_meld_into->merge_trees(const_cast<node *>(to_meld_into->_root), spq_to_meld_from->_root);
		to_meld_into->_values_count += spq_to_meld_from->_values_count;
		return to_meld_into;
	}  
};


#endif