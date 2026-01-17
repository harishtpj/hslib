/* Example usage of Dynamic Array DS */
#define HS_IMPL
#include "hs_dynarr.h"

int main() {
	HSIntArray *arr = hs_newArray(int);
	for (int i = 1; i < 10; i++) {
		hs_arrayPush(arr, i);
		hs_printArray(arr);
	}
	for (int i = 0; i < arr->length; i++)
		printf("%d ", arr->at[i]);
	hs_freeArray(arr);
	return 0;
}
