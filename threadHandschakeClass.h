#ifndef HANDSCHAKE_H
#define HANDSCHAKE_H

#include "playerInteraction.h"
#include <string>
class threadHandschakeClass{
    public:
    bool active;
    bool new_order;
    bool order_processed;
    player_order order;
    bool new_event;
    std::string event_key;
    threadHandschakeClass();
    bool shutdown_order;
};

#endif