#include "C9.h"

int lowsearch(int A[], int key, int n) {
	int low = 0;
	int high = n - 1;
	int mid = (low + high) / 2;
	if (A[high] < key)
		return n;
	// high = n - 1, low = 0, mid = low + high / 2
	// loop invariant: low <= k <= high 
	// where k is the correct index to return
	while (low != high) {
		if (key > A[mid]) {
			// mid < k <= high, low <= k
			low = mid + 1;
			// low <= k <= high
		} else {
			// mid >= k, low <= k <= high
			high = mid;
			// low <= k <= high
		} 
		// low <= k <= high
		mid = (low + high) / 2;
		// low <= k <= high
	}
	// low <= k <= high = low
	return high;
}
