#include "Base/assert.h"
#include "Base/memory.h"
#include "Base/smart_ptr.h"
#include "Base/ref_ptr.h"
#include "Base/timer.h"
#include "Base/random.h"
#include "Base/filesystem.h"

#include <iostream>
#include <assert.h>
#include <chrono>
#include <thread>
#include <random>

using sysclock = std::chrono::system_clock;

int main()
{
	//assert(3 == 5);
	//ASSERT_MSG(3 == 5, "Message boi");
	//static_assert(sizeof(int) == 5, "invalid int size");


	/*int* p = new int;
	delete p;*/

	//ref_ptr<int> r1(new int(25));
	//{
	//	ref_ptr<int> r2 = r1;
	//}

	//int* p = new int[32];
	//delete p;


	//ns_timer t;

	//std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	//std::cout << t.elapsed_time() << std::endl;
	//std::cout << t.seconds() << std::endl;

	//sysclock::time_point start = sysclock::now();
	//std::cout << start.time_since_epoch().count() << std::endl;
	//std::cout << std::chrono::duration_cast<std::chrono::hours>(start.time_since_epoch()).count() << std::endl;

	//std::chrono::milliseconds ms = std::chrono::milliseconds(1000);
	//std::chrono::microseconds mi = ms;
	//std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);

	//std::cout << ms.count() << std::endl;
	//std::cout << mi.count() << std::endl;
	//std::cout << s.count() << std::endl;

	//random_real_t random;
	//for (int i = 0; i < 5; i++) {
	//	std::cout << random(1.0f, 100.0f) << std::endl;
	//}

	//std::cout << filesystem::file_exists("test.txt") << std::endl;

	char pathname[255];
	filesystem::get_current_path(pathname, 255);
	std::cout << pathname << std::endl;
	filesystem::create_directory("textures/a/b");
	filesystem::set_current_path("textures/a");

	std::vector<int> numbers{ 1, 2, 3, 4, 5 };
	filesystem::write_file("test.txt", numbers.data(), numbers.size() * sizeof(int));

	int* buffer = nullptr;
	size_t size;
	filesystem::read_file("test.txt", (void**)(&buffer), size);

	std::vector<int> numbers2;
	for (int i = 0; i < 5; i++) {
		numbers2.push_back(*(buffer + i));
	}

	filesystem::free_file(buffer);

	return 0;
}
