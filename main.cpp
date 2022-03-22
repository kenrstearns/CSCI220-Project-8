//Kenneth Stearns
//Project 8
//Due 11/8/21
//This program will compare 4 separate sorting methods.
#include <iostream>

using namespace std;

//Swap Function
//Pre: two integers to be swapped.
//Post: The two integers that are swapped.
void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

//inSort Function.
//Pre: an array to be sorted, an integer for the length of the array, and an integer to keep track of count.
//Post: an array that is sorted using an insertion sort.
void inSort(int a[], int n, int &count)
{
    int j, k;

    for(int i = 1; i < n; i++)
    {
        k = a[i];
        j = i - 1;

        while(j >= 0 && a[j] > k)
        {
            a[j+1] = a[j];
            j = j - 1;

            ++count;
        }

        a[j+1] = k;
    }

    return;
}

//merge function
//pre: 4 separate integers. One that will be used as an array to be merged, the left edge of the array, the middle of the array, and the right of the array. A 5th integer is used for the count.
//post: merges two integers together.
void merge(int *a, int l, int m, int r, int &count)
{
    int i, j, k, nl, nr;

    nl = m - l + 1;

    nr = r - m;

    int larr[nl], rarr[nr];

    for(i = 0; i<nl; i++)
        larr[i] = a[l+i];

    for(j = 0; j<nr; j++)
        rarr[j] = a[m+1+j];

    i = 0;
    j = 0;
    k = l;

    while(i < nl && j < nr)
    {
        if(larr[i] <= rarr[j])
        {
            a[k] = larr[i];
            i++;
        }
        else
        {
            a[k] = rarr[j];
            j++;
        }
      k++;
      count++;
   }

    while(i<nl)
    {
        a[k] = larr[i];
        i++;
        k++;
        count++;
    }

    while(j < nr)
    {
        a[k] = rarr[j];
        j++;
        k++;
        count++;
    }
}

//mergeSort function
//Pre: three integers, one used for an array, and two others for the left and right ends of the array. A 4th integer used to track the count.
//Post: Sorts the array by use of a merge sort.
void mergeSort(int *a, int l, int r, int &count)
{
    if(l < r)
   {
        ++count;
        int m = l+(r-l)/2;

        mergeSort(a, l, m, count);
        mergeSort(a, m+1, r, count);
        merge(a, l, m, r, count);
   }
}

//partition function
//pre: an integer array, two integers for the low and high values, and a integer to track the count.
//post: performs the majority of the work in the quick sort, and sorts part of the array.
int partition(int a[], int low, int high, int &count)
{
    int pivot = a[high];

    int i = (low - 1);

    for(int j = low; j <= high; j++)
    {
        if(a[j] < pivot)
        {
            i++;
            swap(&a[i], &a[j]);
            count++;
        }
    }
    swap(&a[i + 1], &a[high]);
    count++;
    return(i + 1);
}

//quiSort function
//pre: an integer array, two integers for low and high, and a fourth integer to track the count.
//post: sorts the array by using a quick sort method.
void quiSort(int a[], int low, int high, int &count)
{
    if (low < high)
    {
        int pi = partition(a, low, high, count);
        count++;
        quiSort(a, low, pi - 1, count);
        quiSort(a, pi + 1, high, count);
    }
}

//heapify function
//pre: an integer array, an integer for the length, and a integer for the root of the heap.
//post: re-organizes the heap to follow the correct hierarchy.
void heapify(int a[], int n, int root, int &count)
{
    int largest = root;
    int l = 2 * root + 1;
    int r = 2 * root + 2;

    if(l < n && a[l] > a[largest])
    {
        largest = l;
    }

    if(r < n && a[r] > a[largest])
    {
        largest = r;
    }

    if(largest != root)
    {
        swap(&a[root], &a[largest]);
        count++;
        heapify(a, n, largest, count);
    }
}

//heaSort function
//Pre: an integer array, a integer for the length, and a integer to keep track of the count.
//Post: sorts the array by utilizing a heap sort.
void heaSort(int a[], int n, int &count)
{
    for(int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(a, n, i, count);
        count++;
    }

    for(int i = n-1; i >=0; i--)
    {
        swap(&a[0], &a[i]);
        count++;
        heapify(a, i, 0, count);
    }
}

//printArray function
//Pre: an array and a integer for the length.
//Post: outputs the contents of an array to the terminal.
void printArray(int a[], int n)
{
    for(int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

int main()
{
    int seed;
    int length;
    char print;

    cout << "Enter the number of values to generate and sort, between 1 and 5000: ";
    cin >> length;

    cout << "Enter an integer seed value: ";
    cin >> seed;

    cout << "Print the values? y/n: ";
    cin >> print;

    srand(seed);

    int ins[length], mer[length], qui[length], hea[length];

    int insCount = 0, merCount = 0, quiCount = 0, heaCount = 0;

    for(int i = 0; i < length; i++)
    {
        ins[i] = rand();
        mer[i] = ins[i];
        qui[i] = ins[i];
        hea[i] = ins[i];
    }


    inSort(ins, length, insCount);
    mergeSort(mer, 0, length - 1, merCount);
    quiSort(qui, 0, length - 1, quiCount);
    heaSort(hea, length, heaCount);

    if(print == 'y')
    {
        cout << "Insert Sort: ";
        printArray(ins, length);

        cout << "Merge Sort:  ";
        printArray(mer, length);

        cout << "Quick Sort:  ";
        printArray(qui, length);

        cout << "Heap Sort:   ";
        printArray(hea, length);
    }

    cout << "Insertion Sort Count = " << insCount;
    cout << endl << "Merge Sort Count = " << merCount;
    cout << endl << "Quick Sort Count = " << quiCount;
    cout << endl << "Heap Sort Count = " << heaCount;

    return 0;
}
