#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

const int num_launches = 10;
float arr_time[2][num_launches]; //array of time measurement results
const int data_dimension[5] = { 10, 100, 1000, 10000, 100000 };

char arr_char[256];

void initializing_array(int* arr, int size) { //function for filling an array with elements
	bool way;
	int element;

	if (size < 2) throw "Incorrect size";
	else {
		cout << "Choose the way to set the array\n0: manually\n1: random" << endl;
		cin >> way;

		if (way == 0) {
			for (int i = 0; i < size; i++)
			{
				cout << "Enter an array element" << endl;
				cin >> element;
				arr[i] = element;
			}
		}
		else {
			srand(static_cast<unsigned int>(time(0)));
			for (int i = 0; i < size; i++) {
				arr[i] = rand() % size;
				cout << arr[i] << " ";
			}
			cout << endl;
		}
	}
}

int binary_search(int* arr, int size, int key) //an algorithm for searching for an element in a sorted array 
                                               //using splitting the array in half
{
	int left = 0;
	int right = size - 1;
	int mid = 0;

	while (left < right) {
		mid = (left + right) / 2; //calculation of the middle, rounded to the smaller
		if (arr[mid] == key) 
			return mid;
		if (arr[mid] > key) //key is smaller, so it is to the left of the middle
			right = mid - 1;
		else if (arr[mid] < key) //to the right
			left = mid + 1;
	}
	if (arr[mid] != key)
		return -1;
	else return mid;
}

void quick_sort(int* arr, int left, int right) //quick sorting based on the principle of exchange
{
	int mid = (left + right) / 2; //support element
	int left_buf = left, right_buf = right;
	while (left_buf <= right_buf) {
		while (arr[left_buf] < arr[mid]) //searching for an element that is smaller than the element in the middle
			left_buf++;
		while (arr[right_buf] > arr[mid]) //searching for an element that is larger than the element in the middle
			right_buf--;
		if (left_buf <= right_buf) {
			swap(arr[left_buf], arr[right_buf]);
			left_buf++;
			right_buf--;
		}
		if (left < right_buf) 
			quick_sort(arr, left, right_buf);
		if (right > left_buf) 
			quick_sort(arr, left_buf, right);
	}
}

void bubble_sort(int* arr, int size) //bubble sorting method
{
	for (int i = 0; i < size; i++) {
		bool flag = true;
		for (int j = 0; j < size - (i + 1); j++) { //size - (i+1) in order not to re-pass 
												   //those that have already been passed
			if (arr[j] > arr[j + 1]) {
				flag = false;
				swap(arr[j], arr[j + 1]);
			}
		}
		if (flag) { //if the array is sorted
			break;
		}
	}
}

void bogo_sort(int* arr, int size) { //we check the pairs, if they are unordered, then we swap them and start again
	int i = 0;
	while (i < size - 1)
	{
		if (arr[i] <= arr[i+1])
			i++;
		else {
			swap(arr[i], arr[i + 1]);
			i--;
			if (i < 0)
				i = 0;
		}
	}
}

void counting_sort(char* arr_char, int size) { //sorting characters by counting
	int* cnt = new int[256];
	for (int i = 0; i < 256; i++) 
		cnt[i] = 0; 
	for (int i = 0; i < size; i++)
		cnt[arr_char[i]]++; 
	int j = 0;
	for (int i = 0; i < 256; i++) {
		while (cnt[i]) {
			arr_char[j] = i;
			j++;
			cnt[i]--;
		}
	}
}

void time_characteristics(int size) //comparison of the operating time of two sorts
{
	int* arr_quick_sort = new int[size];
	int*  arr_bubble_sort = new int[size];
	srand(static_cast<unsigned int>(time(0)));

	for (int i = 0; i < num_launches; i++) {

		for (int j = 0; j < size; j++)
			arr_quick_sort[j] = arr_bubble_sort[j] = rand() % 1000;

		//for quick_sort
		auto start1 = chrono::high_resolution_clock::now();
		quick_sort(arr_quick_sort, 0, size - 1);
		auto end1 = chrono::high_resolution_clock::now();
		chrono::duration<float> time_quick_sort = end1 - start1;
		arr_time[0][i] = time_quick_sort.count();

		//for bubble_sort
		auto start2 = chrono::high_resolution_clock::now();
		bubble_sort(arr_bubble_sort, size);
		auto end2 = chrono::high_resolution_clock::now();
		chrono::duration<float> time_bubble_sort = end2 - start2;
		arr_time[1][i] = time_bubble_sort.count();

	}
	delete[] arr_quick_sort;
	delete [] arr_bubble_sort;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	float sum_time_quick_sort = 0;
	float sum_time_bubble_sort = 0;
	int choice;
	int size;
	int key;
	int left = 0;
	int right;
	int* arr = new int;

	do {

		cout << "Choose\n1: binary search\n2: quick sort\n3: bubble sort\n4: bogo sort\n5: counting sort\n6: time of quick sort and bogo sort\n7: exit" << endl;
		cin >> choice;

		if (choice < 1 || choice > 7) {
			cout << "Error" << endl;
			break;
		}

		switch (choice) {
		case 1:
			cout << "Enter the size of the array" << endl;
			cin >> size;
			initializing_array(arr, size);
			cout << "Enter the desired character" << endl;
			cin >> key;
			cout << binary_search(arr, size, key) << endl;
			delete[] arr;
			break;
		case 2:
			cout << "Enter the size of the array" << endl;
			cin >> size;
			initializing_array(arr, size);
			right = size - 1;
			quick_sort(arr, left, right);
			for (int i = 0; i < size; i++)
			{
				cout << arr[i] << " ";
			}
			cout << endl;
			delete[] arr;
			break;
		case 3:
			cout << "Enter the size of the array" << endl;
			cin >> size;
			initializing_array(arr, size);
			bubble_sort(arr, size);
			for (int i = 0; i < size; i++)
			{
				cout << arr[i] << " ";
			}
			cout << endl;
			delete[] arr;
			break;
		case 4:
			cout << "Enter the size of the array" << endl;
			cin >> size;
			initializing_array(arr, size);
			bogo_sort(arr, size);
			for (int i = 0; i < size; i++)
			{
				cout << arr[i] << " ";
			}
			cout << endl;
			delete[] arr;
			break;
		case 5:
			cout << "Enter the size of the array" << endl;
			cin >> size;
			char element;
			for (int i = 0; i < size; i++)
			{
				cout << "Enter an char_array element" << endl;
				cin >> element;
				arr_char[i] = element;
			}
			counting_sort(arr_char, size);
			for (int i = 0; i < size; i++)
			{
				cout << arr_char[i] << " ";
			}
			cout << endl;
			break;
		case 6:
			for (int i = 0; i < 5; i++) {
				time_characteristics(data_dimension[i]);
				cout << "Time measurements for dimension " << data_dimension[i] << ":" << endl;
				cout << "      quick_sort: ";
				for (int j = 0; j < num_launches; j++) {
					if (j != num_launches - 1) cout << arr_time[0][j] << "; ";
					else cout << arr_time[0][j] << endl;
					sum_time_quick_sort += arr_time[0][j];
				}
				cout << "      bubble_sort: ";
				for (int j = 0; j < num_launches; j++) {
					if (j != num_launches - 1) cout << arr_time[1][j] << "; ";
					else cout << arr_time[1][j] << endl;
					sum_time_bubble_sort += arr_time[1][j];
				}
			}

			cout << "Average values for all dimensions and launches:" << endl;
			cout << "      quick_sort: " << sum_time_quick_sort / (num_launches * 5) << endl;
			cout << "      bubble_sort: " << sum_time_bubble_sort / (num_launches * 5) << endl;
			exit;
		}

	}while (choice != 7);
	return 0;
}