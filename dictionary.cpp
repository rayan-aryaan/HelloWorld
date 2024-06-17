#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"

Dictionary* createDictionary() {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->capacity = 8;
    dict->size = 0;
    //dict->entry = (Entry*)malloc(sizeof(Entry) * dict->capacity);
    dict->entry = (Entry*)calloc(dict->capacity, sizeof(Entry));
    return dict;
}

Dictionary* resize(Dictionary* dict) {
    dict->capacity *= 2;
    dict->entry = (Entry*)realloc(dict->entry, sizeof(Entry) * dict->capacity);
    return dict;
}

void addToDictionary(Dictionary* dict, char key, int value) {
    if(dict->size == dict->capacity) {
        dict = resize(dict);
    }
    dict->entry[dict->size].key = key;
    dict->entry[dict->size].value = value;
    dict->size++;
}

void printEntry(Entry entry) {
    printf("Key: %C, Value: %d\n", entry.key, entry.value);
}

int giveKeyreturnValue(Dictionary* dict, char key) {
    for(int i = 0; i < dict->size; i++) {
        if(dict->entry[i].key == key) {
            return dict->entry[i].value;
        }
        if(i == dict->size - 1 && dict->entry[i].key != key) {
            printf ("Key does not exists in this dictionary\n");
            return -1;
        }
    }
    return 0;
}

void printDictionary(Dictionary* dict) {
    for(int i = 0; i < dict->size; i++) {
        printEntry(dict->entry[i]);
    }
}

void freeDictionary(Dictionary* dict) {
    free(dict->entry);
    free(dict);
}

