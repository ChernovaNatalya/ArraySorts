#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
 
double t = 0;
int nsr = 0, nob = 0;

int hello() {
	int a;
	printf("\nSelect the command:\n");
	printf("1. Create array\n");
	printf("2. Print array\n");
	printf("3. Bubble sort\n");
	printf("4. Choice sort\n");
	printf("5. Insertion sort\n");
	printf("6. Counting sort\n");
	printf("7. Quicksort\n");
	printf("8. Merge sort\n");
	printf("9. Linear search\n");
	printf("10. Binary search\n");
	printf("0. Exit\n\n");
	scanf_s("%i", &a);
	printf("\n");
	return a;
}

int* createarr(int n) {
	int i = 0;
	int* res;
	res = (int*)malloc(n * sizeof(int));
	if (n < 10) {
		for (i = 0; i < n; i++) {
			printf("Enter %i element: ", i);
			scanf_s("%d", &res[i]);
		}
	}
	else {
		for (i = 0; i < n; i++) {
			res[i] = rand();
		}
	}
	return res;
}

void printarr(int arr[], int n) {
	int i = 0;
	for (i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void printresults(int arr0[], int arr[], int n) {
	if (n <= 100) {
		printf("Old array: ");
		printarr(arr0, n);
		printf("New array: ");
		printarr(arr, n);
	}
	printf("Comparisons: %i\n", nsr);
	printf("Swaps: %i\n", nob);
	printf("Time=%f \n", t);
	nsr = 0; nob = 0; t = 0;
}

void printresultsofsearch(int m) {
	printf("Position: %i\n", m);
	printf("Comparisons: %i\n", nsr);
	printf("Time=%f \n", t);
	nsr = 0; t = 0;
}

void swap(int* a, int* b) {
	int c = *a;
	*a = *b;
	*b = c;
}

int* copyarr(int arr[], int n) {
	int* res;
	res = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		res[i] = arr[i];
	}
	return res;
}
// Searches

int linear_search(int el, int arr[], int n) {
	clock_t begin, end;
	begin = clock();
	int i = 0;
	for (i = 0; i < n; i++) {
		nsr++;
		if (arr[i] == el) {
			return i;
			break;
		}
	}
	return -1;
	end = clock();
	t = (end - begin) * 1.0;
}

int binary_search(int el, int arr[], int n) {
	clock_t begin, end;
	begin = clock();
	int low = 0, high = n - 1, middle = (low + high) / 2;
	while (low <= high) {
		nsr++;
		middle = (low + high) / 2;
		if (el < arr[middle]) {
			high = middle - 1;
			nsr++;
		}
		else if (el > arr[middle]) {
			low = middle + 1;
			nsr++;
		}
		else {
			nsr++;
			return middle;
		}
	}
	return -1;
	end = clock();
	t = (end - begin) * 1.0;
}

// Sorts

void bubble_sort(int arr[], int n) {
	clock_t begin, end;
	begin = clock();
	int i = 0, j = 0, flag = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
				nob++;
				flag = 1;
			}
			nsr++;
		}
		if (flag == 0) {
			break;
		}
		else
			flag = 0;
	}
	end = clock();
	t = (end - begin)*1.0;
}

void choise_sort(int arr[], int n) {
	clock_t begin, end;
	begin = clock();
	int i = 0, j = 0, min, ind;
	for (i = 0; i < n; i++) {
		min = arr[i];
		ind = i;
		for (j = i; j < n; j++) {
			if (arr[j] < min) {
				ind = j;
				min = arr[j];
			}
			nsr++;
		}
		if (i != ind) {
			swap(&arr[i], &arr[ind]);
			nob++;
		}
	}
	end = clock();
	t = (end - begin) * 1.0;
}

int binsearch(int el, int arr[], int left, int right) { // for insertion_sort
	clock_t begin, end;
	begin = clock();
	nsr++;
	if (right <= left) {
		nsr++;
		if (el > arr[left])
			return left + 1;
		else
			return left;
	}

	int mid = (left + right) / 2;
	nsr++;
	if (el == arr[mid])
		return mid + 1;
	nsr++;
	if (el > arr[mid])
		return binsearch(el, arr, mid + 1, right);
	return binsearch(el, arr, left, mid - 1);
	end = clock();
	t += (end - begin) * 1.0;
}

void insertion_sort(int arr[], int n) {
	clock_t begin, end;
	begin = clock();
	int i, j, tmp, position;
	for (i = 1; i < n; i++)	{
		j = i - 1;
		tmp = arr[i];
		position = binsearch(tmp, arr, 0, j);
		while (j >= position) {
			arr[j + 1] = arr[j];
			j--;
			nob++;
		}
		arr[j + 1] = tmp;
		nob++;
	}
	end = clock();
	t += (end - begin) * 1.0;
}

void counting_sort(int arr[], int n) {
	clock_t begin, end;
	begin = clock();
	int i = 0, k = 0, j = 0, min = INT_MAX, max = INT_MIN, size = 0;
	for (i = 0; i < n; i++) {
		if (arr[i] < min) {
			min = arr[i];
		}
		nsr++;
		if (arr[i] > max) {
			max = arr[i];
		}
		nsr++;
	}
	size = max - min + 1;
	int* p;
	p = (int*)malloc(size * sizeof(int));
	for (i = 0; i < size; i++)
		p[i] = 0;
	for (i = 0; i < n; i++) {
		p[arr[i] - min]++;
		nob++;
	}
	for (i = 0; i < size; i++) {
		for (j = 0; j < p[i]; j++) {
			arr[k] = i+min;
			k++;
			nob++;
		}
	}
	end = clock();
	t = (end - begin) * 1.0;
}

void quicksort(int arr[], int left, int right) {
	clock_t begin, end;
	begin = clock();
	int l = left, r = right, key = arr[(l + r) / 2];
	while (l <= r) {
		while (arr[l] < key) {
			l++;
			nsr++;
		}
		while (arr[r] > key) {
			r--;
			nsr++;
		}

		if (l <= r) {
			swap(&arr[l++], &arr[r--]);
			nob++;
		}
	}

	if (left < r) {
		nsr++;
		quicksort(arr, left, r);
	}
	if (right > l) {
		nsr++;
		quicksort(arr, l, right);
	}
	end = clock();
	t = (end - begin) * 1.0;
}

void merge(int arr[], int res[], int left, int mid, int right) {
	clock_t begin, end;
	begin = clock();
	int i = left, j = mid + 1, k = left;
	while ((i <= mid) && (j <= right)) {
		if (arr[i] < arr[j]) {
			res[k] = arr[i];
			i++;
		}
		else {
			res[k] = arr[j];
			j++;
		}
		k++;
	}
	if (i > mid) {
		while (j <= right) {
			res[k] = arr[j];
			k++;
			j++;
		}
	}
	else {
		while (i <= mid) {
			res[k] = arr[i];
			k++;
			i++;
		}
	}
	for (i = left; i <= right; i++) {
		arr[i] = res[i];
	}
	end = clock();
	t += (end - begin) * 1.0;
}

void merge_sort(int arr[], int res[], int left, int right) {
	clock_t begin, end;
	begin = clock();
	if (left == right)
		return;
	int mid = (left + right) / 2;
	merge_sort(arr, res, left, mid);
	merge_sort(arr, res, mid + 1, right);
	merge(arr, res, left, mid, right);
	end = clock();
	t += (end - begin) * 1.0;
}



int main() {
	int f = 0, n = 0;
	int* arr0;
	arr0 = (int*)malloc(1 * sizeof(int));
	int* arr;
	arr = (int*)malloc(1 * sizeof(int));
	int m = 0, key=0;

	do {
		f = hello();
		switch (f)
		{
		case 1:
			printf("Enter the length of the array\n");
			scanf_s("%i", &n);
			arr0 = createarr(n);
			printf("Done!\n");
			break;

		case 2:
			printarr(arr0, n);
			break;

		case 3:
			arr=copyarr(arr0,n);
			bubble_sort(arr, n);
			printresults(arr0, arr, n);
			break;

		case 4:
			arr = copyarr(arr0, n);
			choise_sort(arr, n);
			printresults(arr0, arr, n);
			break;
			
		case 5:
			t = 0;
			arr = copyarr(arr0, n);
			insertion_sort(arr, n);
			printresults(arr0, arr, n);
			break;

		case 6:
			arr = copyarr(arr0, n);
			counting_sort(arr, n);
			printresults(arr0, arr, n);
			break;

		case 7:
			arr = copyarr(arr0, n);
			quicksort(arr, 0, n-1);
			printresults(arr0, arr, n);
			break;
			
		case 8:
			t = 0;
			arr = copyarr(arr0, n);
			int* arrm;
			arrm = (int*)malloc(n * sizeof(int));
			merge_sort(arr, arrm, 0, n-1);
			printresults(arr0, arr, n);
			break;
			
		case 9:
			arr = copyarr(arr0, n);
			quicksort(arr, 0, n - 1);
			nsr = 0; nob = 0; t = 0;
			if (n <= 100) {
				printf("Array: ");
				printarr(arr, n);
			}
			printf("Enter the desired value\n");
			scanf_s("%i", &key);
			m = linear_search(key, arr, n);
			printresultsofsearch(m);
			break;
			
		case 10:
			arr = copyarr(arr0, n);
			quicksort(arr, 0, n - 1);
			nsr = 0; nob = 0; t = 0;
			if (n <= 100) {
				printf("Array: ");
				printarr(arr, n);
			}
			printf("Enter the desired value\n");
			scanf_s("%i", &key);
			m = binary_search(key, arr, n);
			printresultsofsearch(m);
			break;
			
		case 0:
			printf("Goodbye!\n");
			break;
		default:
			printf("Error: Enter a value from 0 to 10\n");
			break;
		}
	} while (f != 0);
}