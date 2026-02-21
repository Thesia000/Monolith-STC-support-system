#include <chrono>
#include <thread>
#include <iostream>
#include <cmath>

#include "internalLogicLoop.h"
#include "threadHandschakeClass.h"
#include "helperFunctions.h"
#include "playerInteraction.h"

void internal_logic_loop(warpper* warpper_object){
    threadHandschakeClass* handschake;
    uint64_t start;
    uint64_t end;
    uint64_t overtime=0;
    while(handschake->active){
        start = getTimeMS();
        warpper_object->thread_dockStorage_object->updateShipFines();
        if(warpper_object->thread_dockStorage_object->nextOserstayAlertTime() <= start){
            warpper_object->thread_dockStorage_object->raiseOverstayAlert();
        }
        

        end = getTimeMS();
        if(end-start<100){
            std::this_thread::sleep_for(std::chrono::milliseconds(100-(end-start)));//thread sleeps for 100ms
        }
        else{
            overtime=end-start;
        }
        
    }
    std::cout<<"I DID A FUCK UP SOMEHOW";
}