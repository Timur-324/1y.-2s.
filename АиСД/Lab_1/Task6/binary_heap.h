#ifndef HEAP 
#define HEAP
#include "mergeable_priority_queue.h"
#include <cstring>
#include <iostream>
#include <stdexcept>

class binary_heap final: 
    public mergeable_priority_queue
{
private: 
    class Node
    {
    public:
        int pkey;
        char * value;

        Node() :
            pkey(0), value(nullptr){}

        Node(
            int key, 
            char const * val);

        //вспомогательные функци
        void copy(
            Node const & other);
        
        void copy(
            char const * val);

        void destruct();

		//правило трёх
        ~Node();

		Node(
			Node const & other);
		
		Node & operator=(
			Node const & other);
    };

private:
    Node * root; // указатель на начало массива
    size_t capacity;
    size_t size; // заполненные элементы массива
    int (*_priorities_comparer)(int, int); // компаратор

    //вспомогательные функции
    static size_t parent(size_t i){ return (i - 1) / 2; }
    static size_t left(size_t i)  { return 2 * i + 1; }
    static size_t right(size_t i) { return 2 * i + 2; }
    void destruct();
    void copy(
        binary_heap const & other);

    // Операции просеивания
    static int default_comparator(int a, int b);
    void sift_up(
        size_t i); //поддерживаем свойство кучи при вставке
    void sift_down(
        size_t i); // восстановление структуры после удаления элемента


public:
    binary_heap();

    binary_heap(int (*cmp)(int, int));

    //правило трёх для кучи
    ~binary_heap() override;

    binary_heap(
        binary_heap const & other);

    binary_heap & operator=(
        binary_heap const & other);

    //основные методы
    void insert(
        int priority, 
        char const * value) override;

    char const * findMax() const override;

    char * removeMax() override;

    //долгое слияние(за O(N))
    mergeable_priority_queue & merge(
        mergeable_priority_queue * to_merge_from) override;
};

#endif