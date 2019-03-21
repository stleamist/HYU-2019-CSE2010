# include <stdio.h>
# include <stdlib.h>
# define SWAP(x, y, temp) ( (temp)=(x), (x)=(y), (y)=(temp) )

void selection_sort(int list[], int n) {
	int i, j, min, temp;
	
	for (i = 0; i < n-1; i++) {
		min = i;
		
		for (j = i+1; j < n; j++) {
			if (list[j] < list[min]) {
				min = j;
			}
		}
		
		SWAP(list[i], list[min], temp);
	}
}

int main() {
	FILE* fp;
	int size;
	int* arr;
	
	char inputFilename[32];
	char outputFilename[32];
	
	
	// Get filenames from user
	printf("Enter input filename: ");
	scanf("%s", inputFilename);
	
	printf("Enter output filename: ");
	scanf("%s", outputFilename);
	
	
	// Read input file
	fp = fopen(inputFilename, "r");
	
	fscanf(fp, "%d", &size);
	
	arr = (int*)malloc(sizeof(*arr) * size);
	
	for (int i = 0; i < size; i++) {
		fscanf(fp, "%d", &arr[i]);
	}
	
	fclose(fp);
	
	
	// Sort
	selection_sort(arr, size);
	
	
	// Write output file
	fp = fopen(outputFilename, "w");
	
	for (int i = 0; i < size; i++) {
		fprintf(fp, "%d ", arr[i]);
	}
	
	fclose(fp);
	
	
	// Deallocate
	free(arr);
	
	return 0;
}