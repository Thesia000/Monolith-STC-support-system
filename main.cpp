#include <iostream>
#include <string>
#include <thread>
#include <cmath>
#include "config.h"
#include "playerInteractionLoop.h"
#include "internalLogicLoop.h"
int main(int, char**){
    
    bool active = true;
    Config config_data= Config();
    load_config(&config_data);
    threadHandschakeClass thread_handschake_object = threadHandschakeClass();
    dockStorageClass thread_dockStorage_object = dockStorageClass(&config_data);
    warpper warpper_object = warpper(&thread_handschake_object,&thread_dockStorage_object);
    std::thread internal_logic_thread = std::thread(internal_logic_loop,&warpper_object);
    std::thread player_interaction_thread = std::thread(player_interaction_loop,&warpper_object);
    
    while(active){
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
