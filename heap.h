#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> heap_store;
  int m_;
  PComparator pc_;
  void percolateUp(size_t index);
  void percolateDown(size_t index);
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c): heap_store(), m_(m), pc_(c){
}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap(){
}



template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item){
  heap_store.push_back(item);
  percolateUp(heap_store.size() - 1);//add element at the next available spot and percolateUp to correct position
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Top() on empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return heap_store[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Pop() on empty heap");
  }
  heap_store[0] = heap_store.back();
  heap_store.pop_back();
  percolateDown(0);
}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const{
  return heap_store.empty();
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const{
  return heap_store.size();
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::percolateUp(size_t index){
  if(index == 0){
    return;
  }
  size_t parent = (index - 1) / m_; //compare with the parent if it outranks then swap and recursive call to compare again with parent index
  if(pc_(heap_store[index], heap_store[parent])){
    std::swap(heap_store[index], heap_store[parent]);
    percolateUp(parent);
  }
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::percolateDown(size_t index){
  if(empty()){
    return;
  }
  size_t child = m_ * index + 1;
  if(child > size()){ //checking is there are children
    return;
  }
  size_t smallest_child = child; //initial child
  size_t last_child = smallest_child + (m_ - 1);
  if(last_child > size()){
    last_child = size() - 1;
  }
  for(size_t i = child + 1; i <= last_child; i++){ //finding smallest child
    if(pc_(heap_store[i], heap_store[smallest_child])){
      smallest_child = i;
    }
  }
  if(pc_(heap_store[smallest_child], heap_store[index])){ //swapping if higher priority otherwise in the correct position
    std::swap(heap_store[smallest_child], heap_store[index]);
    percolateDown(smallest_child);
  }
}


#endif

