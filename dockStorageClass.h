#ifndef OBJECT_H
#define OBJECT_H
#include <map>
#include <cstdint>
#include <string>
struct dockedShip{
    std::string ship_name = "Urist McShip";
    uint64_t inicial_dock_time = 0;
    uint64_t fine = 0;
    bool overstaying;
};
class dockStorageClass{
    public:
    uint64_t fine_start_time = 1000 * 60 * 15;//fine starts at 15min
    uint64_t last_auto_alert_time = 0;
    uint64_t auto_alert_time = 1000 * 60 * 2.5;//every 2.5 min
    bool auto_alert = true;
    double fine_per_second = 16.666;//results in 1k fine per min
    double base_fine = 15000;//applied for overstaying
    dockStorageClass();
    std::map<std::string, dockedShip> docked_ships_map;
    void addShip(std::string ship_name,std::string dock);
    void removeShip(std::string ship_name);
    void removeShipByDock(std::string dock);
    void updateShipFines();
    void raiseOverstayAlert();//triggers ever 2.5 min can be configured
    uint64_t nextOserstayAlertTime();
    void printAllShips(uint64_t time);
    void ajustValue(std::string change_var,std::string value);
};
#endif