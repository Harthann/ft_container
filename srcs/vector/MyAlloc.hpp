#ifndef MYALLOC_HPP
#define MYALLOC_HPP

namespace ftc {

template <class T>
class MyAlloc {

	public:
		MyAlloc() {} ;
		~MyAlloc() {} ;
		T *allocate(size_t size) {
			return (new T[size]);
		}
		void deallocate(T *ptr, size_t size) {
			(void)size;
			delete ptr;
		}
};


} //namespace declaration end


#endif
