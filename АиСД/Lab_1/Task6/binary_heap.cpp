#include "binary_heap.h"

// Функционал нода
void binary_heap::Node::copy(
    Node const & other)
{
    pkey = other.pkey;
    copy(other.value);
}


void binary_heap::Node::copy(
    char const * val)
{
    if (val == nullptr)
    {
        value = nullptr;
    }
    else
    {
        value = new char[strlen(val) + 1];
        strcpy(value, val);
    }
}

void binary_heap::Node::destruct() 
{
    delete[] value;
    value = nullptr;
}

binary_heap::Node::Node(
    int key, 
    char const * val) : 
    pkey(key), value(nullptr)
{
    if(pkey == 0)
    {
        throw std::invalid_argument("pkey can not be 0!");
    }

    if(val == nullptr)
    {
        throw std::runtime_error("Value can not be nullptr!");
    }

    copy(val);
}

binary_heap::Node::~Node() 
{
    destruct();
}

binary_heap::Node::Node(
    Node const & other) :
    pkey(other.pkey), value(nullptr)
{
    copy(other);    
}
		
binary_heap::Node & binary_heap::Node::operator=(
    Node const & other)
{
    if (this == &other)
    {
        return *this;
    }

    destruct();

    copy(other);
	
    return *this;
}

//Функционал кучи
void binary_heap::destruct()
{
    /*автоматические вызовет деструктор 
    для всех элементов в массиве*/
    delete[] root; // <---
    root = nullptr;
    size = 0;
    capacity = 0;
}

void binary_heap::copy(
    binary_heap const & other)
{
    root = new Node[other.capacity];
    for (int i = 0; i < other.size; ++i) 
    {
        root[i] = other.root[i];
    }
    _priorities_comparer = other._priorities_comparer;
}

void binary_heap::sift_up(
    size_t i) 
{
    while (i > 0) 
    {
        size_t parent_idx = parent(i);
        if (_priorities_comparer(root[parent_idx].pkey, root[i].pkey) >= 0) 
        {
            break;
        }
        std::swap(root[parent_idx], root[i]);
        i = parent_idx;
    }
}

void binary_heap::sift_down(
    size_t i) 
{
    while (left(i) < size) 
    {
        size_t left_child = left(i);
        size_t right_child = right(i);
        size_t max_child = left_child;

        if (right_child < size && (_priorities_comparer(root[right_child].pkey, root[left_child].pkey) > 0)) 
        {
            max_child = right_child;
        }

        if (_priorities_comparer(root[i].pkey, root[max_child].pkey) >= 0) 
        {
            break;
        }

        std::swap(root[i], root[max_child]);
        i = max_child;
    }
}


binary_heap::binary_heap() :
    root(nullptr), capacity(16), size(0), _priorities_comparer(default_comparator)
{
    root = new Node[capacity];
}

binary_heap::binary_heap(int (*cmp)(int, int)) :
    root(nullptr), capacity(16), size(0)
{
    if(cmp == nullptr)
    {
        throw std::runtime_error("Comporator can not be nullptr!");
    }
    else
    {
        _priorities_comparer = cmp;
    }
    root = new Node[capacity];
}

int binary_heap::default_comparator(int a, int b)
{
    return a - b;
}

binary_heap::~binary_heap()
{
    destruct();
}

binary_heap::binary_heap(
    binary_heap const & other) :
    root(nullptr), capacity(other.capacity), size(other.size)
{
    copy(other);
}

binary_heap & binary_heap::operator=(
    binary_heap const & other)
{
    if(this == &other)
    {
        return *this;
    }

    destruct();

    copy(other);

    return *this;
}

void binary_heap::insert(
    int priority, 
    char const * value)
{
    if(priority == 0)
    {
        throw std::invalid_argument("pkey can not be 0!");
    }
    if(value == nullptr)
    {
        throw std::runtime_error("Value can not be nullptr!");
    }
    if (size == capacity) 
    {
        capacity *= 2;
        Node * new_root = new Node[capacity];

        for (int i = 0; i < size; ++i) 
        {
            new_root[i] = root[i];
        }

        delete[] root;
        root = new_root;
    }

    root[size] = Node(priority, value); 
    sift_up(size);
    ++size;

    for (int i = 0; i < size; ++i) { std::cout << root[i].pkey << ' '; } std::cout << std::endl;
}

char const * binary_heap::findMax() const
{
  return root[0].value;
}

char * binary_heap::removeMax()
{
    if (size == 0) {return nullptr;}

    char * result = root[0].value;
    root[0].value = nullptr;

    if (size == 1) 
    {
        --size;
    } 
    else 
    {
        std::swap(root[0], root[size - 1]);
        --size;
        sift_down(0);
    }

    return result;
}

mergeable_priority_queue & binary_heap::merge(
    mergeable_priority_queue * to_merge_from)
{
    if (!to_merge_from) 
    {
        throw std::invalid_argument("Can not merge with null!");
    }

    binary_heap* other = dynamic_cast<binary_heap*>(to_merge_from);
    if (!other) 
    {
        throw std::invalid_argument("Incompatible heap type");
    }

    /*проходимся по кажому элементу второй кучи и добавляем во вторную через insert*/
    for (int i = 0; i < other->size; ++i) 
    {
        insert(other->root[i].pkey, other->root[i].value);
    }

    return *this;
}

