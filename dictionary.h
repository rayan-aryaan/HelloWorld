#ifndef DICTIONARY_H
#define DICTIONARY_H
typedef struct Entry {
    char key;
    int value;
} Entry;

typedef struct Dictionary {
    Entry* entry;
    int size;
    int capacity;
} Dictionary;


Dictionary* createDictionary();
Dictionary* resize(Dictionary* dict);
void addToDictionary(Dictionary* dict, char key, int value);
void printEntry(Entry entry);
int giveKeyreturnValue(Dictionary* dict, char key);
bool searchKey(Dictionary* dict, char key);
void printDictionary(Dictionary* dict);
void freeDictionary(Dictionary* dict);
#endif 