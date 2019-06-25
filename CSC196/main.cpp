#include <iostream>
#include <assert.h>
#include "Base/assert.h"
#include "Base/memory.h"
#include "Base/smart_ptr.h"

int main()
{
	//assert(3 == 5);
	//ASSERT_MSG(3 == 5, "Message boi");
	//static_assert(sizeof(int) == 5, "invalid int size");

	int* p = new int;
	delete p;

    std::cout << "Hello World!\n";
}
