// { Driver Code Starts
// C++ program for implementation of Heap Sort
#include <bits/stdc++.h>
using namespace std;
// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(int arr[], int n, int i);

void buildHeap(int arr[], int n);

// main function to do heap sort
void heapSort(int arr[], int n)
{
  buildHeap(arr, n);
  for (int i = n - 1; i >= 0; i--)
  {
    swap(arr[0], arr[i]);
    heapify(arr, i, 0);
  }
}

/* Function to print an array */
void printArray(int arr[], int size)
{
  int i;
  for (i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

// Driver program to test above functions
int main()
{
  int arr[1000000], n, T, i;
  scanf("%d", &T);
  while (T--)
  {
    scanf("%d", &n);
    for (i = 0; i < n; i++)
      scanf("%d", &arr[i]);
    heapSort(arr, n);
    printArray(arr, n);
  }
  return 0;
}
// } Driver Code Ends

/* Main function to do heap sort. This function uses buildHeap()
   and heapify()
void heapSort(int arr[], int n)  {
    buildHeap(arr, n);
    for (int i=n-1; i>=0; i--)  {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
} */
// The functions should be written in a way that array become sorted
// in increasing order when above heapSort() is called.
// To heapify a subtree rooted with node i which is  an index in arr[].
// n is size of heap. This function  is used in above heapSor()
// 半堆顶下沉
void heapify(int arr[], int n, int i)
{
  // Your Code Here
  int val = arr[i];
  while (i < n)
  {
    int left = i * 2 + 1, right = left + 1;
    int larger = left;
    if (right < n && arr[left] < arr[right])
      larger = right;
    if (larger < n && val < arr[larger])
    {
      arr[i] = arr[larger];
      i = larger;
    }
    else
      break;
  }
  arr[i] = val;
}

// Rearranges input array so that it becomes a max heap
void buildHeap(int arr[], int n)
{
  // Your Code Here
  for (int i = (n - 2) / 2; i >= 0; i--)
  {
    heapify(arr, n, i);
  }
}
