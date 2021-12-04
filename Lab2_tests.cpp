#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab2/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab2tests
{
	TEST_CLASS(Lab2tests)
	{
	public:
		
		TEST_METHOD(binary_search_method)
		{
			const int size = 10;
			int* array = new int[size];
			int index = 0;
			for (auto i : { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 })
			{
				array[index++] = i;
			}
			int key = 5;
			Assert::IsTrue(binary_search(array, size, key) == 4);
		}
		TEST_METHOD(quick_sort_method)
		{
			const int size = 10;
			int left = 0; int right = size - 1;
			int* array = new int[size];
			int index = 0;
			for (auto i : { 1, 4, 2, 8, 12, 3, 9, 3, 10, 5 })
			{
				array[index++] = i;
			}
			quick_sort(array, left, right);
			Assert::IsTrue(array[0] == 1 && array[1] == 2 && array[2] == 3 && array[3] == 3 && array[4] == 4 && array[5] == 5 && array[6] == 8 && array[7] == 9 && array[8] == 10 && array[9] == 12);
		}
		TEST_METHOD(bubble_sort_method)
		{
			const int size = 10;
			int* array = new int[size];
			int index = 0;
			for (auto i : { 1, 4, 2, 8, 12, 3, 9, 3, 10, 5 })
			{
				array[index++] = i;
			}
			bubble_sort(array, size);
			Assert::IsTrue(array[0] == 1 && array[1] == 2 && array[2] == 3 && array[3] == 3 && array[4] == 4 && array[5] == 5 && array[6] == 8 && array[7] == 9 && array[8] == 10 && array[9] == 12);
		}
		TEST_METHOD(bogo_sort_method)
		{
			const int size = 10;
			int* array = new int[size];
			int index = 0;
			for (auto i : { 1, 4, 2, 8, 12, 3, 9, 3, 10, 5 })
			{
				array[index++] = i;
			}
			bogo_sort(array, size);
			Assert::IsTrue(array[0] == 1 && array[1] == 2 && array[2] == 3 && array[3] == 3 && array[4] == 4 && array[5] == 5 && array[6] == 8 && array[7] == 9 && array[8] == 10 && array[9] == 12);
		}
		TEST_METHOD(counting_sort_method)
		{
			const int size = 5;
			char array[size] = { 'a', 'c', 'A', 'd', 'b' };
			counting_sort(array, size);
			Assert::IsTrue(array[0] == 'A' && array[1] == 'a' && array[2] == 'b' && array[3] == 'c' && array[4] == 'd');
		}
	};
}
