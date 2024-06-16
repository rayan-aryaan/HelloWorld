#include <corecrt_malloc.h>
#include <conio.h>
#include <vcruntime_string.h>
class sumn{
public:
    int size;
    int* arr;
};

struct MemPool {
    int owner;
    int allocated_flag;
    int page_size;
    char buffer[128];
    MemPool(){
        this->owner = 0;
        this->allocated_flag = 1;
        this->page_size = 128;
        memset(this->buffer,0, 128);
    }

};

void* operator new (size_t size, void* buffer){
    MemPool* ptr = reinterpret_cast<MemPool*>(buffer);
    if(ptr->page_size >= size){
        return ptr->buffer;
    }
    return malloc(size);

}

void* operator new (size_t size){
    return malloc(size);

}
int main(){
    sumn* s1 = new sumn;
    MemPool page;
    MemPool* buffer = new  MemPool[10];
   // MemPool* buffer = (MemPool*)malloc(10 * sizeof(MemPool));
    sumn* s2 = new (buffer + 1) sumn();
    sumn* s3 = reinterpret_cast<sumn*>(&page);
    // sumn* s3 = (sumn*)(arr);
    s2->size = 5;
    s3->size = 10;
    getch();
    
}