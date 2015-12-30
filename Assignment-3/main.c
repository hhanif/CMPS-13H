// Haris Hanif
// Assignment 3
// ID: 1357292

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define SWAP(a,b) int temp = a; a = b; b = temp; moves += 3;

int minIndex(int [], int, int);
void minSort(int [], int);
void bubbleSort(int [], int);
void insertionSort(int [], int);
void shellSort(int [], int);
void quickSort(int [], int, int);
void mergeSort(int [], int, int);
void merge(int [], int, int, int);
int partition(int [], int, int);
void checkSort(int [], int);
void heapSort(int [], unsigned int);


int main(int argc, const char * argv[]) {
    int count;
    printf("How many numbers would you like sorted?\n");
    scanf("%d", &count);
    int* array = malloc(sizeof(int) * count);

    for (int i = 1; i < count; i++) {
        array[i] = rand();
    }
    for (int i = 1; i < count; i++) {
        printf("%i\n", &array[i]);
    }
    
    minSort(array, count);
    printf("Min Sort: \n");
    for(int i = 0; i < count; i++) {
        printf(" %d\n",array[i]);
    }
    checkSort(array, count);
    free(array);
    
    bubbleSort(array, count);
    printf("Bubble Sort: \n");
    for(int i = 0; i < count; i++) {
        printf(" %d\n",array[i]);
    }
    checkSort(array, count);
    free(array);
    
    insertionSort(array, count);
    printf("Insertion Sort: \n");
    for(int i = 0; i < count; i++) {
        printf(" %d\n",array[i]);
    }
    checkSort(array, count);
    free(array);

    shellSort(array, count);
    printf("Shell Sort: \n");
    for(int i = 0; i < count; i++) {
        printf(" %d\n",array[i]);
    }
    checkSort(array, count);
    free(array);

    quickSort(array, 0, count);
    printf("Quick Sort: \n");
    for(int i = 0; i < count; i++) {
        printf(" %d\n",array[i]);
    }
    checkSort(array, count);
    free(array);

    heapSort(array, count);
    printf("Merge Sort: \n");
    for(int i = 0; i < count; i++) {
        printf(" %d\n",array[i]);
    }
    checkSort(array, count);
    free(array);

    mergeSort(array, 0, count);
    printf("Merge Sort: \n");
    for(int i = 0; i < count; i++) {
        printf(" %d\n",array[i]);
    }
    checkSort(array, count);
    free(array);

    
    return 0;
}

// minIndex: find the index of the least element.
int minIndex(int a[], int first, int last) //Taken from Professor Long
{
    int compares;
    int min = first;
    for (int i = first; i < last; i += 1) {
        min = a[i] < a[min] ? i : min; compares += 1; // He used it!
    }
    //printf("Total number of comparions: %i\n", &compares);
    //printf("Total number of moves: %i\n", &moves);
    return min;
}
// minSort: sort by repeatedly finding the least element.
void minSort(int a[], int length) //Taken from Professor Long
{
    int moves;
    for (int i = 0; i < length - 1; i += 1) {
        int min = minIndex(a, i, length);
        if (min != i) { SWAP(a[min], a[i]); moves += 3; }
    }
    //printf("Total number of comparions: %i\n", &compares);
    printf("Total number of moves: %i\n", moves);
    return;
}

void bubbleSort(int a[], int length)
{
    int moves;
    int compares;

    for (int i = 0; i < length - 1; i ++) {
        for(int j = 0; j < length - i - 1; j++) {
            if(a[j] > a[j + 1]) {
                compares +=1;
                int k = a[j];
                a[j] = a[j + 1];
                a[j + 1] = k;
                moves += 3;

            }
        }
    }
    printf("Total number of comparions: %i\n", compares);
    printf("Total number of moves: %i\n", moves);

    return;
}

void insertionSort(int a[], int length)
{
    int moves;
    int compares;
    for(int i = 0; i < length; i++)
    {
        for(int j = i - 1; 0 <= j; j--)
        {
            if(a[j] > a[j+1])
            {
                compares += 1;
                
                int k = a[j];
                a[j] = a[j+1];
                a[j+1] = k;
                
                moves += 3;
            }
            else
                break;
        }
    }
    printf("Total number of comparions: %i\n", compares);
    printf("Total number of moves: %i\n", moves);
    return;
}

void shellSort(int a[], int length) {
    int moves;
    int compares = 0;
    for (int i = length / 2; i > 0; i /= 2) {
        for (int j = i; length > j; j++) {
            for (int k = j - i; k >= 0 && a[k] > a[k + i]; k -= i) {
                int l = a[k];
                a[k] = a[k + i];
                a[k + i] = l;
                moves += 3;
            }
        }
    }
    printf("Total number of comparions: %i\n", compares);
    printf("Total number of moves: %i\n", moves);
    return;
}

int partition( int a[], int lo, int hi ) { //TA Dustin helped me write this function
    int moves;
    int compares;
    int i = a[lo];
    int j = lo + 1;
    int k = hi;
    int temp;
    
    while (k >= j)
    {
        compares += 1;
        while (i > a[j]) {
            j++;
            compares += 1;
        }
        
        while (i < a[k]) {
            k--;
            compares += 1;
        }
        
        if (k > j)
        {
            compares += 1;
            temp = a[j];
            a[j] = a[k];
            a[k] = temp;
            moves += 3;
        }
    }
    
    temp = a[lo]; //SWAP
    a[lo] = a[k];
    a[k] = temp;
    moves += 3;
    return k;
}

void quickSort(int a[], int lo, int hi) { //TA Dustin helped me write this function
    int moves;
    int compares;
    int pivot = 0;
    int i;
    int j;
    int temp;
    if(hi > lo) { //TA Dustin helped me with this
        compares += 1;
        pivot = partition( a, lo, hi );
        quickSort( a, lo, pivot - 1 );
        quickSort( a, pivot + 1, hi );
    }
    
    if(lo < hi) {
        compares += 1;
        pivot = lo;
        i = lo;
        j = hi;
        moves += 3;
    }
    while(i < j) {
        compares += 1;
        while(a[i] <= a[pivot] && i < hi) {
            compares += 2;
            i++;
        }
        while(a[pivot] < a[j]) {
            compares += 1;
            j--;
        }
        if(i < j){
            compares += 1;
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            moves += 3;
        }
        
        temp = a[pivot];
        a[pivot] = a[j];
        a[j] = temp;
        moves += 3;
        quickSort(a,lo,j - 1); //TA Dustin helped me with this
        quickSort(a,j + 1,hi);
        
    }
    printf("Total number of comparions: %i\n", compares);
    printf("Total number of moves: %i\n", moves);
    return ;
}

void merge(int a[], int lo, int middle, int hi) { //TA Dustin helped me write this function
    int moves;
    int compares;
    int i = lo;
    int j = middle + 1;
    int k = 0;
    int temp[1000];
    
    while (hi >= j && middle >= i) {
        compares += 2;
        if (a[j] >= a[i]) {
            compares += 1;
            temp[k++] = a[i++];
            moves += 1;
        }
        else {
            temp[k++] = a[j++];
            moves += 1;
        }
    }
    while (middle >= i) {
        compares += 1;
        temp[k++] = a[i++];
        moves += 1;
    }
    while (hi >= j) {
        compares += 1;
        temp[k++] = a[j++];
        moves += 1;
        k--;
    }
    while (0 < k) {
        temp[k] = a[lo + k];
        moves += 1;
        k--;
    }
}

void mergeSort(int a[], int lo, int hi) //TA Dustin helped me write this function
{
    int moves;
    int compares;
    if (hi > lo) {
        compares += 1;
        int mid = (hi + lo)/2;
        mergeSort(a, lo, mid);
        mergeSort(a, mid + 1, hi);
        merge(a, lo, mid, hi);
    }
    printf("Total number of comparions: %i\n", compares);
    printf("Total number of moves: %i\n", moves);
    return;
}
void heapSort(int a[], unsigned int n) { //Different than how TA Dustin told us to write heap sort
    //I had no idea how to use insert
    int temp;
    unsigned int i = n;
    unsigned int j = n / 2;
    unsigned int left;
    unsigned int right;
    int moves;
    int compares;
    
    while (1) {
        if (0 < j) {
            compares += 1;
            j--;
            temp = a[j];
            moves += 1;
        }
        else {
            i--;
            if (i == 0) {
                return ;
            }
            temp = a[i];
            a[i] = a[0];
            moves += 2;
        }
}
    right = j;
    left = j * 2 + 1;
    
    while (n > left) {
        compares += 1;
        if (a[left] < a[left + 1] && n > left + 1) {
            compares += 2;
            left++;
        }
        if (temp < a[left]) {
            compares += 1;
            a[right] = a[left];
            right = left;
            left = right * 2 + 1;
            moves += 3;
        } else {
            break;
        }
    }
    a[right] = temp;
    moves += 1;
    
    printf("Total number of comparions: %i\n", compares);
    printf("Total number of moves: %i\n", moves);
}

void checkSort(int a[], int length) {
for ( int i = 0 ;i < length; i++ )
{
    int count;
    if ( a[ i ] < a[ i+1 ] )
    {
        count++;
    }
    if( count == i) {
        printf("The array is sorted\n");
    }

    }
}
