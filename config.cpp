#ifndef CONFIG_CPP
#define CONFIG_CPP
#include <ostream>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>
#include "config.h"
#include "helperFunctions.h"
#include "debug.h"
enum pointer_type{
    PT_STRING,
    PT_INT,
    PT_BOOL,
    PT_DOUBLE,
    PT_DOUBLE_VECTOR,
    PT_UINT64
};

enum pointer_flags {
    PF_NONE  = 0,      // no flags
    PF_MULTI = 1 << 0, // multiple entries allowed
    PF_OPT   = 1 << 1, // is optional
    PF_SET   = 1 << 2, // has been set
};

struct pointer_entity
{
    enum pointer_type type;
    void* pointer;
    void* pointer_2;
    int flags;
};


void load_config(Config* config){
    std::string line;
    std::string line2;
    
    std::string filename = "config";
    if(std::filesystem::exists(filename)){
        no_config_detected();//emegency create the file
    }
    std::ifstream config_file(filename);
    assert_file_valid(config_file, filename);
    /*
    
    Declaration of all inputs, the string is what is needed to be writen in config first followed by the declaration of the pointer entity(a struct used to later asign the values)
    
    */
    std::unordered_map <std::string, pointer_entity> map_pointers {};
    map_pointers["fine_start_time"] =  pointer_entity {.type=PT_UINT64,.pointer = &config->fine_start_time, .flags = PF_NONE};
    map_pointers["fine_per_second"] =  pointer_entity {.type=PT_DOUBLE,.pointer = &config->fine_per_second, .flags = PF_NONE};
    map_pointers["base_fine"] =  pointer_entity {.type=PT_DOUBLE,.pointer = &config->base_fine, .flags = PF_NONE};
    map_pointers["auto_alert_time"] =  pointer_entity {.type=PT_UINT64,.pointer = &config->auto_alert_time, .flags = PF_NONE};
    map_pointers["auto_alert"] = pointer_entity {.type=PT_BOOL,.pointer = &config->auto_alert, .flags = PF_NONE};
    std::string* temp_string_pointer;
    int* temp_int8_t_pointer;
    double* temp_double_pointer;
    std::vector<double>* temp_double_vector_pointer;
    bool* temp_bool_pointer;
    uint64_t* temp_uint64_pointer;
    double start;
    double end;
    double increm;
    /*
    
    beginning of readin the config file

    */
    while(std::getline(config_file,line)){
        if(line == "<<END>>"){
            /*
            
            Ends the config

            */
            break;
        }
        if(!std::getline(config_file,line2)){
            panic("Unexpected EOF while parsing config");
            /*
            
            Error handeling

            */
        }
        if (line.back() != ':') {
            panic("Expect key '" << line << "' to end with ':'");
            /*
            
            Error handeling

            */
        }
        line.pop_back();
        std::cout << LOC << "parsing cfg key '" << line << "'" << std::endl;
        if (map_pointers.count(line) == 0) { // key doesnt exist
            panic("Invalid config key '" << line << "'");
            /*
            
            Error handeling

            */
        }
        if ((map_pointers[line].flags & PF_SET) != 0 && (map_pointers[line].flags & PF_MULTI) == 0) {
            panic("Config key '" << line << "' is set already");
            /*
            
            Error handeling

            */
        }
        map_pointers[line].flags |= PF_SET;
        switch (map_pointers[line].type)
        {
        case PT_STRING: //saves string at the coresponding position
            temp_string_pointer = (std::string*) map_pointers[line].pointer;
            *temp_string_pointer = line2;
            break;
        case PT_INT:  //converts a string to a int and saves it at the coresponding position
            temp_int8_t_pointer = (int*) map_pointers[line].pointer;
            try {
                *temp_int8_t_pointer = std::stoi(line2);
            } catch(...) {
                panic("Invalid argument for '" << line << "': '" << line2 << "'.\nExpected <int>");
            }
            break;
        case PT_BOOL://converts a string to a bool and saves it at the coresponding position
            temp_bool_pointer = (bool*) map_pointers[line].pointer;
            if (line2 != "true" && line2 != "false") panic("Invalid argument for '" << line << "': '" << line2 << "'.\nExpected [true|false]");
            *temp_bool_pointer = line2 == "true";
            break;
        case PT_DOUBLE://converts a string to a double and saves it at the coresponding position
            temp_double_pointer = (double*) map_pointers[line].pointer;
            try {
                *temp_double_pointer = std::stod(line2);
            } catch(...) {
                panic("Invalid argument for '" << line << "': '" << line2 << "'.\nExpected <double>");
            }
            break;
        case PT_DOUBLE_VECTOR://converts a string to a double and saves it at the coresponding vector
            temp_double_vector_pointer = (std::vector<double>*) map_pointers[line].pointer;
            temp_int8_t_pointer = (int*) map_pointers[line].pointer_2;
            try {
                start = std::stod(line2);
                std::getline(config_file, line);
                end = std::stod(line);
                std::getline(config_file, line);
                increm = std::stod(line);
            } catch(...) {
                panic("Invalid argument for '" << line << "': '" << line2 << "'.\nExpected double array");
            }
            temp_double_vector_pointer->push_back(start);
            temp_double_vector_pointer->push_back(end);
            temp_double_vector_pointer->push_back(increm);
            *temp_int8_t_pointer += 1;
            break;
        case PT_UINT64://converts a tring into a Uint64 saves it corespondidly
            temp_uint64_pointer = (uint64_t*) map_pointers[line].pointer;
            try {
                *temp_uint64_pointer = convertStringToUint(line2);
            } catch(...) {
                panic("Invalid argument for '" << line << "': '" << line2 << "'.\nExpected <int>");
            }
            break;

            break;
        default:
            panic("Unreachable");//something bad happened we should NOT reach this point
        }
    }
    for (const auto & [key, value] : map_pointers) {
        // value is mandarory but wasnt set?
        if ((value.flags & PF_SET) == 0 && (value.flags & PF_OPT) == 0) {
            panic("Config key '" << key << "' was never set");
        }
    }
    config_file.close();
};

/*

This is project specific the code generates the config file in a emergency

*/
void no_config_detected(){
    std::ofstream NewConfig("config");
    NewConfig <<"fine_start_time\n900000\n";
    NewConfig <<"fine_per_second\n16.6666\n";
    NewConfig <<"base_fine\n15000\n";
    NewConfig <<"auto_alert_time\n150000\n";
    NewConfig <<"auto_alert\ntrue\n";
    NewConfig <<"<<END>>";
    NewConfig.close();
    return;
}
#endif