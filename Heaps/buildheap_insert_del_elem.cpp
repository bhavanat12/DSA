#include<bits/stdc++.h>
using namespace std;
void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}
void insert_maxHeap(vector <int> &nodes, int index)
{
	int parent = index/2;
	if(parent>0 && nodes[parent]<nodes[index])
	{
		swap(nodes[parent], nodes[index]);
		insert_maxHeap(nodes, parent);
	}
}
void heapify(vector <int> &nodes, int index, int n)
{
	int left = 2*index;
	int right = 2*index +1;
	int largest = index;

	// Finding the largest elem among parent, left and right child
	if(left<=n && nodes[left]>nodes[largest])
		largest = left;
	if(right<=n && nodes[right]>nodes[largest])
		largest = right;

	if(largest != index)
	{
		swap(nodes[largest], nodes[index]);
		// since swap occured, checking the heap property of elements
		// below the current index
		heapify(nodes, largest, n);
	}
}
void buildMaxHeap(vector <int> &nodes, int n)
{
	// collecting nodes by reference, so that updates here are
	// reflected in the main function

	// Upon assigning order in level order traversal of tree, we can 
	// observe that the leave elements start from
	// [ (n/2)+1, (n/2)+2, ...... n ]

	// While building heap, we can assume that all the leaf nodes
	// satisfy the heap property, as every single element is a heap
	// Therefore we start from n/2th node (considering each as 
	// parent)

	for(int i=n/2; i>=1; i--)
		heapify(nodes, i, n);
}
int main()
{
	int n;
	// number of elem in array
	scanf("%d", &n);
	vector <int> nodes;
	// Dummy element to start indexing from 1 in the array
	nodes.push_back(-1);
	for(int i=1; i<=n; i++)
	{
		int elem;
		scanf("%d", &elem);
		nodes.push_back(elem);
	}
	// Similar approach can be followed for building min Heap
	buildMaxHeap(nodes, n);

	// number of insert queries
	int q;
	scanf("%d", &q);
	while(q--)
	{
		int insert_elem;
		scanf("%d", &insert_elem);

		nodes.push_back(insert_elem);
		n = n+1;

		insert_maxHeap(nodes, n);
	}

	// Deleting is demonstrating by using the above built heap 
	// to perform heap sort

	// In heap sort, every max element is removed from max heap,
	// from the front and added at the last. the length of the
	// array is now reduced by one.

	// for(int i=1; i<=n; i++)
	// 	printf("%d ", nodes[i]);
	// printf("\n");

	// Heap sort
	int length = n;
	for(int i=1; i<n; i++)
	{
		swap(nodes[1], nodes[length]);
		length--;
		// Now to make the heap valid after this swap, heapify
		heapify(nodes, 1, length);
	}

	// Printing the final sorted array 
	for(int i=1; i<=n; i++)
		printf("%d ", nodes[i]);
	printf("\n");

	return 0;
}
