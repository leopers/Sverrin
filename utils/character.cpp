#include "character.hpp"

std::string Character::get_name() { return name; };
std::string Character::get_character_class() { return character_class; };
Status Character::get_status() { return status; };

void Character::heal() {
    if (status.spell > 0) {
        int initial_life = status.life;

        status.life += 10;
        if (status.life_base < status.life)
            status.life = status.life_base;
    }
}

void Character::attack(Character &attacker) {
    std::mt19937 gen(dev());

    if (character_class == "Ladino" && status.spell_active) 
        return;

    std::uniform_int_distribution<int> d20(1, 20);

    int attacker_d20 = d20(gen);
    int target_d20 = d20(gen);

    bool success;
    if (attacker.status.dexterity + attacker_d20 > status.dexterity + target_d20)
        success = true;
    else
        success = false;

    if (success) {

        bool critic = false;
        attacker_d20 = d20(gen);
        if (attacker_d20 + attacker.status.intelligence >= 20)
            critic = true;

        std::uniform_int_distribution<int> damage_base(5, 10);

        int damage = damage_base(gen) + attacker.status.strength - status.constitution;

        if (critic)
            damage *= 2;

        status.life -= damage;
    }
}

void Character::create_heroe(Character &heroe) {
    heroe.name = "Verri";
    heroe.character_class = "Guerreiro";
    heroe.status.strength = 16;
    heroe.status.constitution = 11;
    heroe.status.dexterity = 11;
    heroe.status.intelligence = 5;
    heroe.status.life = heroe.status.life_base = 70;
}

void Character::create_enemy(Character &enemy) {
    enemy.name = "Ogro";
    enemy.character_class = "Guerreiro";
    enemy.status.strength = 4;
    enemy.status.constitution = 3;
    enemy.status.dexterity = 3;
    enemy.status.intelligence = 2;
    enemy.status.life = enemy.status.life_base = 40;
}

void Character::backup_heroe(std::string backup_name, std::string backup_class, Status backup_status) {
    name = backup_name;
    character_class = backup_class;
    status = backup_status;
}
