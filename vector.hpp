#ifndef VECTOR_HPP
#define VECTOR_HPP
#include<iostream>
#include<memory>
#include"allocator.hpp"

using namespace std;



template <class T, class ALLOCATOR>
class TVector {
    public:

      struct deleter;
      deleter del;

	    int Max = 0;
	    shared_ptr<T[]> Data =  shared_ptr<T[]>(nullptr,del);

      using allocator_type = typename ALLOCATOR::template rebind<T>::other;

      static allocator_type& get_allocator() {
          static allocator_type allocator;
          return allocator;
      }

      struct deleter {

        void operator() (void* ptr) {
          get_allocator().deallocate((T*)ptr, 1);
        }
     };


      class Iterator {
      public:

        typedef Iterator self;
        typedef T value_type;
        typedef T &reference;
        typedef T *pointer;
        typedef std::random_access_iterator_tag iterator_category;
        typedef ptrdiff_t difference_type;

        shared_ptr<T[]> ptr;
        int size;
        int index = 0;
      public:
        Iterator(shared_ptr<T[]> ptr, size_t const index, int size) : ptr(ptr), index(index), size(size) {};

        Iterator(){
        
        }

        T operator*(){
          return ptr[index];
        }

          self &operator++() {
            if (index >= size)
              throw std::out_of_range("Итератор вышел за пределы вектора\n");
            index+=1;
            return *this;
          }

         bool operator<(const Iterator &b) {
            return index < b.index;
          }
          bool operator!=(const Iterator &b) {
            return index != b.index;
          }
      };


      Iterator begin(){
        return Iterator(Data, 0, Max);
      }

      Iterator end(){
        return Iterator(Data, Max, Max);
      }

    void insert(T z, Iterator it) {
      if(Max == 0) {
        T * u = get_allocator().allocate(1);

        shared_ptr<T[]> Data2{new(u) T[1],(del)};
        Data = Data2;

        Data[0] = z;

        Max = 1;
        it.ptr = Data;
        it.size = 1;

      } else {
        T * u = get_allocator().allocate(Max + 1);
        shared_ptr<T[]> Data2{new(u) T[Max + 1],(del)};

        for (int i = 0; i < it.index; ++i){
          Data2[i] = Data[i];
        }

        Data2[it.index] = z;

        for (int i = it.index + 1; i < Max + 1; ++i) {
          Data2[i] = Data[i-1];
        }

        it.ptr = Data2;
        it.size+=1;
        Data = Data2;

        Max+=1;
      }

    }

    void erase(Iterator it) {

      if (Max == 1) {
        Data = nullptr;
        Max = 0;
        it.ptr = nullptr;
        it.size = 0;
        it.index = 0;

      } else {

      T * u = get_allocator().allocate(Max + 1);
      shared_ptr<T[]> Data2{new(u) T[Max - 1],(del)};

      for (int i = 0; i < it.index; ++i) {
         Data2[i] = Data[i];
      }

      for (int i = it.index + 1; i < Max; ++i) {
         Data2[i-1] = Data[i];
      }

      Data = Data2;
      Max-=1;
      it.ptr = Data;
      it.size-=1;

    }
  }

      int size() {
        return Max;
      }


      T& operator[](int i){
        return Data[i];
      }

};



#endif 