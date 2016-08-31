#include<iostream>
using namespace std;

class MinHeap {
	private:	
		int *harr;	//pointer to array of elements in heap
		int capacity; //max possible size of min heap
		int heap_size;	//current number of elements in min heap
	public:
		MinHeap(int capacity);
		void MinHeapify(int);
		inline int parent(int i) {return (i - 1)/2;}
		inline int left(int i) {return (2 * i) + 1;}
		inline int right(int i) {return (2 * i) + 2;}
		int extractMin();
		void decreaseKey(int i, int new_val);
		int getMin() {return harr[0]};
		void deleteKey(int i);
		void insertKey(int k);
}

MinHeap:: MinHeap(int cap) {
	heap_size = 0;
	capacity = cap;
	harr[i] = k;
}
//			0	
//		1		2		
// 3		45		6

void
MinHeap::insertKey(int k) {
	if (heap_size == capacity) {
		cout << "overflow" <<endl;
		return;
	}

	//First insert the new key at the end
	heap_size++;
	int i = heap_size - 1;
	harr[i] = k;

	//Maintain min heap property
	while (i != 0 && harr[parent(i)] > harr[i]) {
		swap(&harr[i], &harr[parent(i)]);	
		i = parent[i];
	}
} 

void
MinHeap::decreaseKey(int i, int new_val) {
	harr[i] = new_val;
	while ()
}
