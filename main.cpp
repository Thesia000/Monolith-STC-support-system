#include <iostream>
#include <string>
#include <thread>
#include <cmath>

#include "playerInteractionLoop.h"
#include "internalLogicLoop.h"
int main(int, char**){
    std::cout << "Hello, from small_hobby_project!\n";
    bool active = true;
    int flavour_wait=25;
    int flavour_wait_text_type=25;
    int flavour_wait_break = 1250;
    threadHandschakeClass thread_handschake_object = threadHandschakeClass();
    dockStorageClass thread_dockStorage_object = dockStorageClass();
    warpper warpper_object = warpper(&thread_handschake_object,&thread_dockStorage_object);
    std::thread internal_logic_thread = std::thread(internal_logic_loop,&warpper_object);
    std::thread player_interaction_thread = std::thread(player_interaction_loop,&warpper_object);
    
    while(active){
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
