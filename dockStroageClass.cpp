#include <string>
#include <iostream>
#include <cmath>
#include "dockStorageClass.h"
#include "helperFunctions.h"
dockStorageClass::dockStorageClass(Config* config){
    this->fine_start_time = config->fine_start_time;
    this->fine_per_second = config->fine_per_second;
    this->base_fine = config->base_fine;
    this->auto_alert_time = config->auto_alert_time;
    this->auto_alert = config->auto_alert;
    return;
}
void dockStorageClass::addShip(std::string ship_name,std::string dock){
    this->docked_ships_map.insert({dock,dockedShip{.ship_name=ship_name,.inicial_dock_time=getTimeMS(),.fine=0}});
    std::cout << "The ship:" << this->docked_ships_map[dock].ship_name << " has docked at dock: " << dock;
    return;
}
void dockStorageClass::removeShip(std::string ship_name){
    std::string removal_key;
    for(auto iterator : this->docked_ships_map){
        if(ship_name==iterator.second.ship_name){
            removal_key = iterator.first;
        }
    }
    this->docked_ships_map.erase(removal_key);
    return;
}
void dockStorageClass::removeShipByDock(std::string dock){
    this->docked_ships_map.erase(dock);
    return;
}
void dockStorageClass::updateShipFines(){
    for(auto iterator: this->docked_ships_map){
        if((this->fine_start_time + iterator.second.inicial_dock_time) <= getTimeMS()){
            this->docked_ships_map[iterator.first].fine = (getTimeMS() - iterator.second.inicial_dock_time - this->fine_start_time)/1000 * fine_per_second + base_fine;
            this->docked_ships_map[iterator.first].overstaying = true;
        }
    }
    return;
}
void dockStorageClass::raiseOverstayAlert(){
    if(!this->auto_alert)return;
    std::cout << seperator << "Overstay and fine alert\n\n";
    bool alert_raised = false;
    for(auto iterator: this->docked_ships_map){
        if(iterator.second.overstaying){
            std::cout << "The ship:"<<iterator.second.ship_name<<" at dock:"<<iterator.first<<" is overstaying and owes a fine of:"<<iterator.second.fine<<" spesos\n";
            alert_raised = true;
        }
    }
    if(!alert_raised)std::cout<<"No ships need to be fine";
    std::cout << seperator;
    this->last_auto_alert_time = getTimeMS();
    return;
}
uint64_t dockStorageClass::nextOserstayAlertTime(){
    return this->last_auto_alert_time + this->auto_alert_time;
}
void dockStorageClass::printAllShips(uint64_t time){
    for(auto iterator: this->docked_ships_map){
        std::cout << "The ship:"<<iterator.second.ship_name<<" at dock:"<<iterator.first<<". It owes a fine of:"<<iterator.second.fine<<" spesos. Total docking time:"<<(time - iterator.second.inicial_dock_time)/1000/60.0<<" min.\n";
    }
    return;
}
void dockStorageClass::ajustValue(std::string change_var,std::string value){
    if(change_var == "fine_start_time"){
        this->fine_start_time = convertStringToUint(value);
        std::cout << "fine_start_time is now set to: " << this->fine_start_time/1000/60.0<<"min\n";
    }
    else if(change_var=="fine_per_second"){
        this->fine_per_second = convertStringToDouble(value);
        std::cout << "fine_per_second is now set to: " << this->fine_per_second<<"spesos per second\n";
    }
    else if(change_var=="base_fine"){
        this->base_fine = convertStringToDouble(value);
        std::cout << "base_fine is now set to: " << this->base_fine<<"spesos\n";
    }
    else if(change_var=="auto_alert_time"){
        this->auto_alert_time = convertStringToUint(value);
        std::cout << "auto_alert_time is now set to: " << this->auto_alert_time/1000/60.0<<"min\n";
    }
    else if(change_var=="auto_alert"){
        this->auto_alert = convertStringToBool(value);
        std::cout << "auto_alert is now set to: " << this->auto_alert<<"\n";
    }else{
        std::cout<<"The variable: "<<change_var<<" was not recognised";
    }

    return;
}