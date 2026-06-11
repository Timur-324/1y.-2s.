#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

class priority_queue
{
public:
  virtual void insert(
    int priority,
    char const * value) = 0;
    
  virtual char const * findMax() const = 0;

	virtual char * removeMax() = 0;
  
  virtual ~priority_queue() noexcept = default;
};

#endif