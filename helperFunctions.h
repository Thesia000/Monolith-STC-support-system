#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H



#include <cstdint>
#include "dockStorageClass.h"
#include "threadHandschakeClass.h"
class warpper{
    public:
    threadHandschakeClass* thread_handschake_object;
    dockStorageClass* thread_dockStorage_object;
    warpper(threadHandschakeClass* handschake,dockStorageClass* dockStorage);
};
uint64_t getTimeMS();
void printStatics();
const std::string seperator = "\n#########################################################################\n\n";
uint64_t convertStringToUint(std::string input);
double convertStringToDouble(std::string input);
bool convertStringToBool(std::string input);
#endif