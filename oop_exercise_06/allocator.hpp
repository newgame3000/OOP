#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP
#include <stack>

using namespace std;

template<class T, size_t BLOCK_SIZE>
class stack_allocator {
private:
	stack<T*> st;
	T* buffer = nullptr;
public: 
	using allocator_type = stack_allocator;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using const_reference = const T&;
	using size_type = size_t;

	T* allocate(const size_t & n) {
		if(buffer == nullptr) {
			buffer = new T[BLOCK_SIZE];
			for (int i = BLOCK_SIZE - 1; i >= 0; --i) {
				st.push(&buffer[i]);
			}
		}

		if (st.size() < n) {
			throw(bad_alloc());
		} else {
			T *p = st.top();
			for (int i = 0; i < n; ++i) {
				st.pop();
			}
			return p;
		}
	}	

	void deallocate(pointer, size_t n) {
		;
	}

	explicit stack_allocator(const stack_allocator<T, BLOCK_SIZE> & another_allocator) : stack_allocator() {
		buffer = new T[BLOCK_SIZE];
		for (std::size_t i = 0; i < BLOCK_SIZE; ++i) {
			buffer[i] = another_allocator.buffer[i];
			st.push(&buffer[i]);
		}
	}

	stack_allocator() : st(), buffer(nullptr) {
		static_assert(BLOCK_SIZE > 0);
	}

	template<class OTHER_T>
	class rebind {
	public:
		using other = stack_allocator<OTHER_T, BLOCK_SIZE>;
	};

	~stack_allocator() {
		delete[] buffer;
	}

};


#endif