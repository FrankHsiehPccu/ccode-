#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>

using namespace std;

// === 角色基底類別 ===
class Character {
protected:
    string name;
    int hp;
    int maxHp;
    bool isDefending; 

public:
    Character(string n, int health);
    virtual ~Character() {}
    bool isAlive();
    string getName();
    int getHp();
    void takeDamage(int damage);
    void heal(int amount);
    void setDefending(bool state);
    virtual string getStatus();
    virtual void restoreResources() {} 
    // 純虛擬函式
    virtual void reduceCD() = 0;
    virtual void takeAction(Character& target) = 0; 
};

#endif