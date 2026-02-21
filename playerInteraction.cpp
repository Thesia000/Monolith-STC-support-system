#include <string>
#include <iostream>
#include <cmath>
#include "playerInteraction.h"
#include "playerInteractionLoop.h"
#include "helperFunctions.h"
std::string nextWord(std::string input,int taken_words){
    int a=0;
    int b=0;
    std::string return_value="";
    input+='.';
    while(true){
        if(input[a]=='.'){
            if(b>=taken_words){
                return return_value;
            }
            return_value="";
            b++;
        }
        else{
            return_value+=input[a];
        }
        a++;  
    }
};

player_order get_player_interaction(){

    player_order return_player_order = player_order{.action=AT_DEFAULT};

    std::string player_input;
    std::cin>>player_input;
    std::string word = nextWord(player_input,0);
    if(word=="print"){
        return_player_order.action = AT_PRINT;
    }
    else if (word == "exit"){
        return_player_order.action = AT_EXIT;
    }
    else if (word=="help"){
        return_player_order.action = AT_HELP;
    }
    else if(word=="cls"){
        return_player_order.action = AT_CLS;
    }
    else if(word=="assign"){
        return_player_order.action = AT_ASSIGN;
        word = nextWord(player_input,1);
        return_player_order.arguments[0] = word;
        word = nextWord(player_input,2);
        return_player_order.arguments[1] = word;
    }
    else if(word=="unassign"){
        return_player_order.action = AT_UNASSIGN;
        word = nextWord(player_input,1);
        return_player_order.arguments[0] = word;
    }
    else if(word=="unassign_name"){
        return_player_order.action = AT_UNASSIGN_NAME;
        word = nextWord(player_input,1);
        return_player_order.arguments[0] = word;
    }
    else if(word=="config"){
        return_player_order.action = AT_CONFIG;
        word = nextWord(player_input,1);
        return_player_order.arguments[0] = word;
        word = nextWord(player_input,2);
        return_player_order.arguments[1] = word;
    }

    return return_player_order;
};
void print_help(){
    //help
    std::cout<<seperator<<"help: showes this text"<<std::endl;
    //print
    std::cout<<std::endl;
    std::cout<<"print: displays all times and fines a ship has acrude"<<std::endl;
    //cls
    std::cout<<std::endl;
    std::cout<<"cls: clears the console"<<std::endl;
    //assign
    std::cout<<std::endl;
    std::cout<<"assign.<arg1>.<arg2>: Assigns the ship <arg2> to the dock <arg1>"<<std::endl;
    //unassign
    std::cout<<std::endl;
    std::cout<<"unassign.<arg>: Unassigns the ship at dock <arg>"<<std::endl;
    //unassign_name
    std::cout<<std::endl;
    std::cout<<"unassign_name.<arg>: Unassigns the ship with the name <arg>"<<std::endl;
    //config
    std::cout<<std::endl;
    std::cout<<"config.<arg1>.<arg2>: Changes the variable <arg1> to the value <arg2>. Valid variables and types: \n-[fine_start_time,uint64,in ms],\n-[fine_per_second,double],\n-[base_fine,double],\n-[auto_alert_time,unit64,in ms],\n-[auto_alert,bool]"<<std::endl;
    return;
};
void print_dock_status(warpper* warpper_object){
    warpper_object->thread_dockStorage_object->printAllShips(getTimeMS());
    return;
}
void player_interaction_loop(warpper* warpper_object){
    std::cout <<seperator<< "Welcome to the Station Traffic Controll managment System Controller\n\n";
    while(true){
        player_order order=player_order{.action=AT_DEFAULT};
        std::cout<<seperator<<"Enter next order: ";
        order = get_player_interaction();
        if(order.action == AT_PRINT){
            print_dock_status(warpper_object);
        }
        else if (order.action == AT_EXIT){
            warpper_object->thread_handschake_object->shutdown_order = true;
        }
        else if(order.action == AT_HELP){
            print_help();
        }
        else if(order.action == AT_CLS){
            system("cls");
        }
        else if(order.action == AT_ASSIGN){
            warpper_object->thread_dockStorage_object->addShip(order.arguments[1],order.arguments[0]);
        }
        else if(order.action == AT_UNASSIGN){
            warpper_object->thread_dockStorage_object->removeShipByDock(order.arguments[0]);
        }
        else if(order.action == AT_UNASSIGN_NAME){
            warpper_object->thread_dockStorage_object->removeShip(order.arguments[0]);
        }
        else if(order.action == AT_CONFIG){
            warpper_object->thread_dockStorage_object->ajustValue(order.arguments[0],order.arguments[1]);
        }
    }
};