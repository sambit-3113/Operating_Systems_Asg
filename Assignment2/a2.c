#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int partition(int arr[], int low, int high) {
    int pivot = arr[low];   
    int i = low + 1;
    int j = high;
    int temp;

    while (1) {
        
        while (i <= high && arr[i] <= pivot)
            i++;

        
        while (arr[j] > pivot)
            j--;

        if (i >= j)
            break;

        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    temp = arr[low];
    arr[low] = arr[j];
    arr[j] = temp;

    return j; 
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);

        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

void merge(int arr[], int low, int mid, int high) {
    int i = low;
    int j = mid + 1;
    int k = low;
    int temp[high + 1];

    while (i <= mid && j <= high) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= high)
        temp[k++] = arr[j++];

    for (int x = low; x <= high; x++)
        arr[x] = temp[x];
}

void mergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

int main() {
    int n;
    printf("Sambit Sahoo\t 22277\n");

    printf("Enter number of integers: ");
    scanf("%d", &n);

    int arr[n];
    int arr_copy[n];

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    	arr_copy[i] = arr[i];
    }

    pid_t v;
    v = fork();

    if (v == 0){
	printf("Hi! I am a child process.\n");
	printf("My PID is %d\n", getpid());
	printf("MY Parent PID is %d\n", getppid());
	printf("Quick Sort Result:");
	quickSort(arr_copy, 0, n - 1);
	for (int i = 0; i < n; i++)
            printf("%d ", arr_copy[i]);

	printf("\n");
    }

    else{
	wait(NULL);
	printf("Hi! I am a Parent process.\n");
	printf("My PID is %d\n", getpid());
	printf("Merge Sort Result:");
	mergeSort(arr, 0, n-1);
	for (int i = 0; i < n; i++)
            printf("%d ", arr[i]);
	printf("\n");
    }
 
    return 0;
}

