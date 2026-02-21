#include <chrono>
#include "dockStorageClass.h"
#include "helperFunctions.h"
#include <cmath>

uint64_t getTimeMS(){
    using namespace std::chrono;
    uint64_t ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    return ms;
};
warpper::warpper(threadHandschakeClass* handschake,dockStorageClass* dockStorage){
    this->thread_handschake_object = handschake;
    this->thread_dockStorage_object = dockStorage;
};
uint64_t convertStringToUint(std::string input){
    uint64_t return_value=0;
    for(auto iterator : input){
        return_value *= 10;
        return_value += (iterator - '0');//abuse aski ^^
    }
    return return_value;
};
double convertStringToDouble(std::string input){
    double return_value;
    bool digit_area=false;
    int digit_number=0;
    //first the pre dot area
    for(auto iterator : input){
        if(! isdigit(iterator)){digit_area=true;}
        if(digit_area){
            digit_number--;//lowered the abs is the number of digits
        }
        return_value *= 10;
        return_value += (iterator - '0');
    }
    return_value *= std::pow(10,digit_number);
    return return_value;
};
bool convertStringToBool(std::string input){//defaults to false
    if(input == "true"){
        return true;
    }
    return false;
};