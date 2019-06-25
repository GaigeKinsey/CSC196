#include "memory.h"
#include <iostream>

void* operator new (size_t size) {
	std::cout << "new: " << size << std::endl;
	return malloc(size);
}

void operator delete (void* ptr, size_t size) {
	std::cout << "delete: " << size << std::endl;
	free(ptr);
}