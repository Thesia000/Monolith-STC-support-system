#ifndef CONFIG_H
#define CONFIG_H
#include <string>
#include <vector>

struct Config {
    uint64_t fine_start_time;
    uint64_t auto_alert_time;
    bool auto_alert;
    double fine_per_second;
    double base_fine;
    /*
    
    class used as a wrapper class(a thing that just saves a lot of data) for all config options

    */
};

void load_config(Config* config);
void no_config_detected();
#endif