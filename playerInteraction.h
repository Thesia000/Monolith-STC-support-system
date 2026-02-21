#ifndef PLAYERINTERACTION_H
#define PLAYERINTERACTION_H
#include <string>

enum action_types{
    AT_DEFAULT,
    AT_PRINT,
    AT_EXIT,
    AT_HELP,
    AT_CLS,
    AT_ASSIGN,
    AT_UNASSIGN,
    AT_UNASSIGN_NAME,
    AT_CONFIG,
    AT_FINE
};
struct player_order{
    enum action_types action;
    std::string arguments[20];
};
player_order get_player_interaction();
void print_help();
void print_start();
#endif