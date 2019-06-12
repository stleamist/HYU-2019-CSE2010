#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// MARK: HashTable의 버킷 상태를 나타내는 컴파일 상수
#define EMPTY 0
#define DELETED 0


// MARK: 해시테이블 관련 구조체들의 정의

// 해시테이블 구조체
typedef struct HashTable {
    int capacity;
    int* array;
} HashTable;

// _find() 함수의 반환값의 상태를 나타내는 데에 사용하는 자료형
typedef enum Existence {
    NonExistent = 0,
    Existent = 1
} Existence;

// _find() 함수의 반환값으로 사용하는 구조체. 탐색을 마친 인덱스의 값과 탐색 결과를 함께 반환하기 위해 구조체를 사용했다.
typedef struct FindResult {
    Existence existence;
    int index;
} FindResult;

// Probing 솔루션을 나타내는 열거형
typedef enum Probing {
    Linear = 0,
    Quadratic,
    Double
} Probing;

// Probing 열거형을 문자열로 변환하는 데에 사용하는 배열
static const char* PROBING_STRING[] = {
    "Linear", "Quadratic", "Double"
};


// MARK: HashTable 함수 프로로타입 선언
HashTable* createHashTable(int capacity);
int hash(int value, int size, int i, Probing probing);
void insert(HashTable* table, int value, Probing probing);
FindResult _find(HashTable* table, int value, Probing probing); // insert(), find(), delete()에서 공통적으로 사용되는 탐색 로직을 분리했다.
void find(HashTable* table, int value, Probing probing);
void delete(HashTable* table, int value, Probing probing);
void print(HashTable* table);


// MARK: HashTable 함수 정의

HashTable* createHashTable(int capacity) {
    HashTable* table;
    table = malloc(sizeof(HashTable));
    
    table->capacity = capacity;
    table->array = calloc(capacity, sizeof(int));
    
    return table;
}

int hash(int value, int size, int i, Probing probing) {
    int hashValue = value % size;
    
    switch (probing) {
        case Linear: {
            return hashValue + i;
            break;
        }
        case Quadratic: {
            return hashValue + i * i;
            break;
        }
        case Double: {
            int divisor = 7;
            int secondaryHashValue = (divisor - (value % divisor));
            return (hashValue + secondaryHashValue * i) % size;
            break;
        }
    }
}

void insert(HashTable* table, int value, Probing probing) {
    FindResult result = _find(table, value, probing);
    
    switch (result.existence) {
        case Existent:
            printf("Already exists\n");
            break;
        case NonExistent:
            table->array[result.index] = value;
            printf("Inserted %d\n", value);
            break;
    }
}

FindResult _find(HashTable* table, int value, Probing probing) {
    for (int i = 0; i < table->capacity; i++) {
        int hashValue = hash(value, table->capacity, i, probing);
        int existingValue = table->array[hashValue];
        
        if (existingValue == value) {
            FindResult result = {.existence = Existent, .index = hashValue};
            return result;
        } else if (existingValue == EMPTY) {
            FindResult result = {.existence = NonExistent, .index = hashValue};
            return result;
        } else {
            continue;
        }
    }
    
    FindResult result = {.existence = NonExistent, .index = table->capacity};
    return result;
}

void find(HashTable* table, int value, Probing probing) {
    FindResult result = _find(table, value, probing);
    
    switch (result.existence) {
        case Existent:
            printf("%d\n", result.index);
            break;
        case NonExistent:
            printf("Not found\n");
            break;
    }
}

void delete(HashTable* table, int value, Probing probing) {
    FindResult result = _find(table, value, probing);
    
    switch (result.existence) {
        case Existent:
            table->array[result.index] = DELETED;
            printf("Deleted %d\n", value);
            break;
        case NonExistent:
            printf("%d not exists\n", value);
            break;
    }
}

void print(HashTable* table) {
    for (int i = 0; i < table->capacity; i++) {
        printf("%d ", table->array[i]);
    }
    printf("\n\n");
}

// MARK: 테스트 케이스를 실행하는 함수
void runTestCase() {
    HashTable* table = createHashTable(11);
    Probing probing = Linear;
    printf("%s\n", PROBING_STRING[probing]);
    
    insert(table, 1, probing);
    insert(table, 11, probing);
    insert(table, 4, probing);
    insert(table, 15, probing);
    insert(table, 22, probing);
    find(table, 64, probing);
    insert(table, 22, probing);
    insert(table, 23, probing);
    insert(table, 24, probing);
    insert(table, 9, probing);
    insert(table, 18, probing);
    insert(table, 77, probing);
    insert(table, 16, probing);
    delete(table, 4, probing);
    delete(table, 18, probing);
    delete(table, 85, probing);
    print(table);
    
    
    table = createHashTable(11);
    probing = Quadratic;
    printf("%s\n", PROBING_STRING[probing]);
    
    insert(table, 1, probing);
    insert(table, 11, probing);
    insert(table, 4, probing);
    insert(table, 15, probing);
    insert(table, 22, probing);
    find(table, 64, probing);
    insert(table, 22, probing);
    insert(table, 23, probing);
    insert(table, 24, probing);
    insert(table, 9, probing);
    insert(table, 18, probing);
    delete(table, 4, probing);
    delete(table, 18, probing);
    delete(table, 86, probing);
    print(table);
    
    
    table = createHashTable(11);
    probing = Double;
    printf("%s\n", PROBING_STRING[probing]);
    
    insert(table, 1, probing);
    insert(table, 11, probing);
    insert(table, 4, probing);
    insert(table, 15, probing);
    insert(table, 22, probing);
    find(table, 64, probing);
    insert(table, 22, probing);
    insert(table, 23, probing);
    insert(table, 24, probing);
    insert(table, 9, probing);
    insert(table, 18, probing);
    insert(table, 77, probing);
    delete(table, 4, probing);
    delete(table, 18, probing);
    delete(table, 87, probing);
    print(table);
}

// MARK: main
int main(int argc, const char * argv[]) {
    FILE* fpInput = fopen("input.txt", "r");
    FILE* fpOutput = freopen("output.txt", "w", stdout); // stdout 스트림 출력을 파일 스트림으로 리다이렉트한다.
    
    int testCasesCount = 0;
    fscanf(fpInput, "%d", &testCasesCount);
    
    for (int i = 0; i < testCasesCount; i++) {
        char probingString[10];
        int tableCapacity = 0;
        Probing probing = Linear;
        
        fscanf(fpInput, "%s", probingString);
        fscanf(fpInput, "%d", &tableCapacity);
        
        HashTable* table = createHashTable(tableCapacity);
        
        if (!strcmp(probingString, PROBING_STRING[Linear])) {
            probing = Linear;
        } else if (!strcmp(probingString, PROBING_STRING[Quadratic])) {
            probing = Quadratic;
        } else if (!strcmp(probingString, PROBING_STRING[Double])) {
            probing = Double;
        }
        printf("%s\n", PROBING_STRING[probing]);
        
        char command;
        int number;
        
        do {
            fscanf(fpInput, "%c %d", &command, &number);
            
            switch (command) {
                case 'i': insert(table, number, probing); break;
                case 'd': delete(table, number, probing); break;
                case 'f': find(table, number, probing); break;
                case 'p': print(table); break;
            }
        } while (command != 'q');
    }
    
    fclose(fpInput);
    fclose(fpOutput);
    
    return 0;
}
