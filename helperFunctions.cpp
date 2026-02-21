#include <chrono>
#include "dockStorageClass.h"
#include "helperFunctions.h"

uint64_t getTimeMS(){
    using namespace std::chrono;
    uint64_t ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    return ms;
};
warpper::warpper(threadHandschakeClass* handschake,dockStorageClass* dockStorage){
    this->thread_handschake_object = handschake;
    this->thread_dockStorage_object = dockStorage;
};