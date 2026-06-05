#ifndef ROLES_H
#define ROLES_H
#include "Character.h"

// === 法師類別 ===
class Mage : public Character {
private:
    int mp;
    int maxMp;
    int explosionCD; 
public:
    Mage();
    void reduceCD() override;
    string getStatus() override;
    void restoreResources() override;
    void takeAction(Character& target) override;
};

// === 戰士類別 ===
class Warrior : public Character {
private:
    int sp; 
    int maxSp;
    int smashCD; 
public:
    Warrior();
    void reduceCD() override;
    string getStatus() override;
    void restoreResources() override;
    void takeAction(Character& target) override;
};

// === 怪物類別 ===
class Monster : public Character {
private:
    int dodgeCD;
public:
    Monster();
    void reduceCD() override;
    void takeAction(Character& target) override;
};

// === 魔王類別 ===
class Boss : public Character {
private:
    int ultimateCD;
public:
    Boss();
    void reduceCD() override;
    void takeAction(Character& target) override;
};
#endif