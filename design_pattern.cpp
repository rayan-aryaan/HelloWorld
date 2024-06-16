#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef unsigned int uint_32;

class PlatformOsInterface {
    public:
        PlatformOsInterface() {}
        virtual void* plat_malloc(uint_32 size) = 0;
        virtual void plat_free(void* ptr) = 0;
};



class PlatformOsWindows : public PlatformOsInterface {
public:
    PlatformOsWindows() {

    }
    virtual void* plat_malloc(uint_32 size) {
        void* ptr = malloc(size);
        memset(ptr, '\0', size);
        return ptr;
    }
    virtual void plat_free(void* ptr) {
        if(ptr != NULL) {
            free(ptr);
        }
    }

};

class PlatformOsLinux: PlatformOsInterface {
public:
    PlatformOsLinux() {

    }
    virtual void* plat_malloc(uint_32 size) {
        void* ptr = malloc(size);
        memset(ptr, '\0', size);
        return ptr;
    }
    virtual void plat_free(void* ptr) {
        if(ptr != NULL) {
            free(ptr);
        }
    }

};


// factory & singleton design pattern
class PlatformOsFactory {
private:
    static PlatformOsInterface* instance;
    static int i;
public:
    static PlatformOsInterface* createPlatObject(){
        if(PlatformOsFactory::instance == NULL) {
#ifdef _WIN32
            instance = new PlatformOsWindows();
#elif __linux__
            instance = new PlatformOsLinux();
            // linux 
#else
        printf("Platform not suppport.");
        assert(false)
#endif
        }
        return instance;
    }
private:
    static void * operator new(size_t size) {
        return NULL;
    }
    PlatformOsFactory() {
        
    }
};

// .data section if initialized .bss if not initilaized
// dumpbin xyz.exe shows the different sections of executable
PlatformOsInterface* PlatformOsFactory::instance = NULL;
int PlatformOsFactory::i;
int j;

int main() {
    PlatformOsInterface* p = PlatformOsFactory::createPlatObject();
    p->plat_malloc(sizeof(p));
    PlatformOsInterface* x = PlatformOsFactory::createPlatObject();
    printf("%d", j);
    
}


