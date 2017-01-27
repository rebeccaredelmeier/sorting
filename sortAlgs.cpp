//sortAlgs.cpp
//By Rebecca Redelmeier
//Date: November 2016
//Purpose: implementation of different sort functions.

#include"sortAlgs.h"
#include<vector>
#include<iostream>

using namespace std;

//function declarations
vector<int>& mergeHelper(vector<int>&, int);

///////////////////////////////////////////////
////////////FUNCTION IMPLEMENTATIONS///////////
///////////////////////////////////////////////

//Purpose: sorts list by maintaining a sorted sublist in the lower
//         part of the list. Goes through vector and adds next 
//	   unsorted int to the sorted portion, then shifts sorted
//	   portion down to keep the invariant.
//Arguments: address of a vector of unsorted ints
//Returns: none
//Source: http://codereview.stackexchange.com/questions/
//        110793/insertion-sort-in-c
void insertionSort(vector<int>& unsorted)
{
	int size = (int)unsorted.size(); 
	int i, j;

	for (i = 0; i < size; i++) { //iterate through all ints in unsorted list
		int temp = unsorted[i]; //get next unsorted int

		//iterate through sorted portion and restore invariant 
                //where necessary
		for (j = i; j > 0 and unsorted[j-1] > temp; j--) { 
			unsorted[j] = unsorted[j - 1];
		}
		unsorted[j] = temp;
	}
}

//Purpose: sorts list using bucket sort algorithm. Sorts all numbers in list
//	   into buckets (one bucket per integer) and then concatenates the 
//	   number of each integer together.
//Arguments: address of a vector of unsorted ints
//Returns: none
void bucketSort(vector<int>& unsorted)
{
	int size = (int)unsorted.size();
	int max = unsorted[0];

	//get the maximum int in the unsorted list
	for (int i = 0; i < size; i++) {
		if (unsorted[i] > max)
			max = unsorted[i];
	}

	//make an array of the size of the max int in unsorted list
	int array[max + 1];

	//initialize all ints in the array to 0
	for (int i = 0; i < (max + 1); i++) {
		array[i] = 0;
	}

	//increment array indice of number in unsorted list when the number
	//appears
	for (int i = 0;  i < size; i++) {
		array[unsorted[i]]++;
	}

	//concatenate list back into unsorted variable
	unsorted.clear();
	for (int i = 0; i < max + 1; i++) { 
		for (int j = array[i]; j > 0; j--) {
			unsorted.push_back(i);
		}
	}
}

//Purpose: sorts a list of ints through breaking list into left and right
//	   recursively until each sublist has only 1 element in it. Then,
//	   compare left and right and put lower one back into list. Do until
//	   all elements arrive back in list.
//Arguements: address of a vector of unsorted ints
//Returns: none 
void mergeSort(vector<int>& unsorted)
{
	int size = (int)unsorted.size();

	//calls recursive function
	unsorted = mergeHelper(unsorted, size);
}

vector<int>& mergeHelper(vector<int>& sorting, int size)
{
	//base case: sublist has 1 or no elements
	if (size <= 1) {
		return sorting;
	}

	//make left and right vector to hold all elements left and right
	//of the passed in vector's mid (right vector holds mid)
	int mid = size/2;
	vector<int> left;
	vector<int> right;

	for (int i = 0; i < mid; i++)
		left.push_back(sorting[i]);

	for (int i = mid; i < size; i++)
		right.push_back(sorting[i]);

	//call merge function recursively on left and right sublists
	left = mergeHelper(left, (int)left.size());
	right = mergeHelper(right, (int)right.size());

	//compare sublist so that elements get put back in list in order.
	//left and right count iterate through all elements in both sublists
	int left_count = 0;
	int right_count = 0;
	sorting.clear();

	//if left is smaller, push it on and move left count up. Else, push
	//right on because it must be smaller and move right count up
	while ((left_count < (int)left.size() and right_count < 
            (int)right.size())) {
		if (left[left_count] < right[right_count]) {
			sorting.push_back(left[left_count]);
			left_count++;
		}
		else {
			sorting.push_back(right[right_count]);
			right_count++;
		}
	}

	//check if there are still any elements remaining in either list 
        //and push them on
	if (left_count != (int)left.size()) {
		for (int i = left_count; i < (int)left.size(); i++)
			sorting.push_back(left[i]);
	}
	if (right_count != (int)right.size()){
		for (int i = right_count; i < (int)right.size(); i++)
			sorting.push_back(right[i]);
	}

	//return list that is now sorted
	return sorting;
}

//Purpose: sort list through radix method, sorting list by
//         integer space, i.e 0s  first, then 10s, then 100s, etc. Perform until
//	   list is completely sorted.
//Arguments: address to a vector of unsorted ints
//Returs: none
//sources used: https://www.youtube.com/watch?v=xhr26ia4k38
void radixSort(vector<int>& unsorted)
{
	//create 10 buckets to place ints in, representative of integers 0-9 that
	//could hold a single spot in an integer
	vector< vector<int> > buckets(10);
	int max = unsorted[0];
	int max_digits = 0;
	int size = (int)unsorted.size();

	//get the maximum int in the unsorted list, then find the number of digits
	//of this max number. This is the max number of digits in the set.
	for (int i = 1; i < size; i++) {
		if (unsorted[i] > max)
			max = unsorted[i];
	}
	while (max > 1) {
		max = max/10;
		max_digits++;
	}

	//define variables used to find specific digit of an integer
	//These variables are incremented at * 10 after each loop
	int mod = 10;
	int divide = 1;

	//loop through list by the number of digits that there are in the
	//largest int. Sort by current digit place, the concatenate. 
	//Increment mod and divide by factors after each loop.
	for (int i = 0; i < max_digits; i++) {
		for (int j = 0; j < size; j++) {
			int temp_digit = ((unsorted[j] % mod) / divide); //get curr digit
									 //place of int
			buckets[temp_digit].push_back(unsorted[j]);
		}
		unsorted.clear();
		int bucket_num = 0;
		while (bucket_num < 10) {
			for (int j = 0; j < (int)buckets[bucket_num].size(); j++) {
				unsorted.push_back(buckets[bucket_num][j]);
			}
			bucket_num++;
		}
		for (int i = 0; i < 10; i++) 
			buckets[i].clear();
		mod = mod * 10; 
		divide = divide * 10;
	}
}





