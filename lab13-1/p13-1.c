#include <stdlib.h>
#include <stdio.h>

void merge(int array[], int leftIndex, int midIndex, int rightIndex);
void recursiveMergeSort(int array[], int leftIndex, int rightIndex);
void printArray(int array[], int startIndex, int endIndex);

void printArray(int array[], int startIndex, int endIndex) {
    for (int i = startIndex; i < endIndex; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void merge(int array[], int leftIndex, int midIndex, int rightIndex) {
    int leftArraySize = midIndex - leftIndex + 1;
    int rightArraySize =  rightIndex - midIndex;
    
    // 정렬된 두 배열의 복사본 배열
    int leftArray[leftArraySize];
    int rightArray[rightArraySize];
    
    // 정렬된 두 배열을 복사본 배열로 복사한다.
    for (int i = 0; i < leftArraySize; i++) {
        leftArray[i] = array[leftIndex + i];
    }
    for (int i = 0; i < rightArraySize; i++) {
        rightArray[i] = array[midIndex + 1 + i];
    }
    
    int arrayCursor = leftIndex;
    int leftCursor = 0;
    int rightCursor = 0;
    
    // 정렬된 두 복사본 배열의 요소들 중 작은 값을 array에 차례대로 대치시킨다.
    while (leftCursor < leftArraySize && rightCursor < rightArraySize) {
        if (leftArray[leftCursor] <= rightArray[rightCursor]) {
            array[arrayCursor] = leftArray[leftCursor];
            leftCursor++;
        } else {
            array[arrayCursor] = rightArray[rightCursor];
            rightCursor++;
        }
        arrayCursor++;
    }
    
    // leftArray에 남은 요소가 있다면 이를 array로 복사한다.
    while (leftCursor < leftArraySize) {
        array[arrayCursor] = leftArray[leftCursor];
        leftCursor++;
        arrayCursor++;
    }
    
    // rightArray에 남은 요소가 있다면 이를 array로 복사한다.
    while (rightCursor < rightArraySize) {
        array[arrayCursor] = rightArray[rightCursor];
        rightCursor++;
        arrayCursor++;
    }
}

void recursiveMergeSort(int array[], int leftIndex, int rightIndex) {
    if (leftIndex < rightIndex) {
        int midIndex = leftIndex + (rightIndex - leftIndex) / 2;
        
        recursiveMergeSort(array, leftIndex, midIndex);
        recursiveMergeSort(array, midIndex + 1, rightIndex);
        
        merge(array, leftIndex, midIndex, rightIndex);
        
        printArray(array, leftIndex, rightIndex + 1);
    }
}

void runTestCase() {
    int array[] = {26, 5, 77, 1, 61, 11, 59, 15, 48, 19};
    int arraySize = sizeof(array) / sizeof(array[0]);
    
    printf("input: \n");
    printArray(array, 0, arraySize - 1);
    printf("\n");
    
    printf("recursive: \n");
    recursiveMergeSort(array, 0, arraySize - 1);
}

int main(int argc, const char * argv[]) {
    FILE* fpInput = fopen("input.txt", "r");
    FILE* fpOutput = freopen("output.txt", "w", stdout); // stdout 스트림 출력을 파일 스트림으로 리다이렉트한다.
    
    int elementsCount = 0;
    fscanf(fpInput, "%d", &elementsCount);
    
    int* array = (int*) calloc(elementsCount, sizeof(int));
    
    for (int i = 0; i < elementsCount; i++) {
        fscanf(fpInput, "%d", &array[i]);
    }
    
    printf("input: \n");
    printArray(array, 0, elementsCount);
    printf("\n");
    
    printf("recursive: \n");
    recursiveMergeSort(array, 0, elementsCount - 1);
    
    fclose(fpInput);
    fclose(fpOutput);
    
    return 0;
}
