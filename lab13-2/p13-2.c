#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int array[], int startIndex, int endIndex) {
    for (int i = startIndex; i < endIndex; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void printPartition(int array[], int startIndex, int pivotIndex, int endIndex) {
    printf("<");
    for (int i = startIndex; i < pivotIndex; i++) {
        if (i != startIndex) {
            printf(" ");
        }
        printf("%d", array[i]);
    }
    
    printf("> <");
    
    printf("%d", array[pivotIndex]);
    
    printf("> <");
    
    for (int i = pivotIndex + 1; i <= endIndex; i++) {
        if (i != pivotIndex + 1) {
            printf(" ");
        }
        printf("%d", array[i]);
    }
    
    printf(">\n");
}

int leftmostPartition(int array[], int lowIndex, int highIndex){
    int pivotValue = array[lowIndex]; // 좌측 기준 파티션
    int lowCursor = lowIndex + 1;
    int highCursor = highIndex;
    
    while (lowCursor <= highCursor) {
        while (lowCursor <= highIndex && array[lowCursor] < pivotValue) {
            lowCursor++;
        }
        
        while (highCursor >= lowIndex && array[highCursor] > pivotValue) {
            highCursor--;
        }
        
        if (lowCursor <= highCursor){
            swap(&array[lowCursor], &array[highCursor]);
        }
    }
    
    swap(&array[lowIndex], &array[highCursor]);
    
    int pivotIndex = highCursor;
    
    return pivotIndex;
}

void quickSort(int array[], int lowIndex, int highIndex) {
    if (lowIndex < highIndex) {
        int pivotIndex = leftmostPartition(array, lowIndex, highIndex);
        
        printPartition(array, lowIndex, pivotIndex, highIndex);
        
        quickSort(array, lowIndex, pivotIndex - 1);
        quickSort(array, pivotIndex + 1, highIndex);
    }
}

void runTestCase() {
    int array[] = {73, 21, 19, 109, 410, 57, 51, 1, 3216, 7000, 15, 9, 24};
    int arraySize = sizeof(array) / sizeof(array[0]);
    quickSort(array, 0, arraySize - 1);
    printArray(array, 0, arraySize - 1);
}

int main() {
    FILE* fpInput = fopen("input.txt", "r");
    FILE* fpOutput;
    
    int elementsCount = 0;
    fscanf(fpInput, "%d", &elementsCount);
    
    int* array = (int*) calloc(elementsCount, sizeof(int));
    
    for (int i = 0; i < elementsCount; i++) {
        fscanf(fpInput, "%d", &array[i]);
    }
    
    printf("leftmost:\n");
    quickSort(array, 0, elementsCount - 1);
    printf("\n");
    
    printf("result:\n");
    printArray(array, 0, elementsCount);
    
    fpOutput = freopen("output.txt", "w", stdout); // stdout 스트림 출력을 파일 스트림으로 리다이렉트한다.
    printArray(array, 0, elementsCount);
    
    fclose(fpInput);
    fclose(fpOutput);
    
    return 0;
}
