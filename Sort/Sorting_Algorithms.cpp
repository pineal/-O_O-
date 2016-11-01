//Bubble Sort
void bubble_sort(int arr[], int n) {
	int i, j;
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

//Insertion Sort
void insertion_sort(int* arr, int n) {
	int i, j;
	for (i = 1; i < n; i++) {
		int temp = arr[i];
		for (j = i; j > 0 && arr[j - 1] > temp; j--) {
			arr[j] = arr[j - 1];
		}
		arr[j] = temp;
	}
}
//Selection Sort
void selection_sort(int arr[], int n) {
	for (int i = 0; i < n - 1; i++){
		int min_index = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j]<arr[min_index]) {
				min_index = j;
			}
		}
		swap(arr[i], arr[min_index]);
	}
}

//Merge Sort
void merge(int* arr, int left, int mid, int right) {
	int len1 = mid - left + 1;
	int len2 = right - mid;

	int l[mid - left + 1];
	int r[right - mid];

	int i, j, k;
	for (i = 0; i < len1; i++) {
		l[i] = arr[left + i];
	}
	for (j = 0; j < len2; j++) {
		r[j] = arr[mid + 1 + j];
	}
	i = 0, j = 0, k = left;
	while (i < len1 && j < len2) {
		if (l[i] < r[j]) {
			arr[k++] = l[i++];
		} else {
			arr[k++] = r[j++];
		}
	}
	while (i < len1) {
		arr[k++] = l[i++];
	}
	while (j < len2) {
		arr[k++] = r[j++];
	}
}

void merge_sort(int arr[], int left, int right) {
	if (left >= right) {
		return;
	}
	int mid = left + (right - left) / 2;
	merge_sort(arr, left, mid);
	merge_sort(arr, mid + 1, right);
	merge(arr, left, mid, right);
}

void merge_sort(int arr[], int n) {
	merge_sort(arr, 0, n - 1);
}

//Quick Sort
void quick_sort(int arr[], int left, int right) {
	if (left >= right) {
		return;
	}
	int pivot_index = (left + right) / 2;
	int pivot = arr[pivot_index];
	int l = left;
	int r = right - 1;
	swap(arr[right], arr[pivot_index]);
	while (l <= r) {
		if (arr[l] < pivot) {
			l++;
		} else if (arr[r] > pivot){
			r--;
		} else {
			swap(arr[r--], arr[l++]);
		}
	}
	swap(arr[l], arr[right]);
	quick_sort(arr, left, l - 1);
	quick_sort(arr, l + 1, right);
}

void quick_sort(int arr[], int n) {
	return quick_sort(arr, 0, n - 1);
}

