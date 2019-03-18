# include <stdio.h>
# include <stdlib.h>

typedef struct {
	char *name;
	int studentID;
	char *major;
} studentT;

int main() {
	FILE *fp;
	int size;
	studentT *arr;
	
	char inputFilename[64];
	char outputFilename[64];
	
	
	// Get filenames from user
	printf("Enter input filename: ");
	scanf("%s", inputFilename);
	
	printf("Enter output filename: ");
	scanf("%s", outputFilename);
	
	
	// Read input file
	fp = fopen(inputFilename, "r");
	
	fscanf(fp, "%d", &size);
	
	arr = (studentT*)malloc(sizeof(studentT) * size);
	
	
	for (int i = 0; i < size; i++) {
		arr[i].name = (char*)malloc(sizeof(char) * 30);
		arr[i].major = (char*)malloc(sizeof(char) * 30);
		
		fscanf(fp, "%s %d %s", arr[i].name, &(arr[i].studentID), arr[i].major);
	}
	
	fclose(fp);
	
	
	// Write output file
	fp = fopen(outputFilename, "w");
	
	for (int i = 0; i < size; i++) {
		printf("%s %d %s\n", arr[i].name, arr[i].studentID, arr[i].major);
		fprintf(fp, "%s %d %s\n", arr[i].name, arr[i].studentID, arr[i].major);
		
		free(arr[i].name);
		free(arr[i].major);
	}
	
	fclose(fp);
	
	
	// Deallocate
	free(arr);
	
	return 0;
}