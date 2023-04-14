#pragma once

#include <string>
#include <random>
#include <array>
#include <iostream>
#include <fstream>

struct Status {
    int strength;
    int constitution;
    int dexterity;
    int intelligence;
    int life;
    int life_base;
    int spell = 3;
    int spell_active = 0;
}; 

class Character {
public:
    static void create_heroe(Character &);
    static void create_enemy(Character &);
    void backup_heroe(std::string, std::string, Status);

    void stun();
    void heal();
    void attack(Character &);

    std::string get_name();
    std::string get_character_class();
    Status get_status();

    std::random_device dev;
    
private:
    std::string name;
    std::string character_class;
    Status status;

};
