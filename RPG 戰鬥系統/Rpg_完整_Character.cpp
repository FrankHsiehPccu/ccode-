#include <iostream>
#include "Character.h"
using namespace std;

Character::Character(string n, int health) : name(n), hp(health), maxHp(health), isDefending(false) {}

bool Character::isAlive() {
    return hp > 0; 
}
string Character::getName() {
    return name;
}
int Character::getHp() {
    return hp; 
}

void Character::takeDamage(int damage) {
    if (isDefending) {
        cout << name << " 防禦/閃避了這次攻擊，沒有受到傷害！" << endl;
        isDefending = false; 
    } else {
        hp -= damage;
        if (hp < 0) hp = 0;
        cout << name << " 受到了 " << damage << " 點傷害！" << endl;
    }
}

void Character::heal(int amount) {
    hp += amount;
    if (hp > maxHp) hp = maxHp;
    cout << name << " 恢復了 " << amount << " 點 HP！" << endl;
}

void Character::setDefending(bool state) { isDefending = state; }

string Character::getStatus() {
    return name + " HP: " + to_string(hp) + "/" + to_string(maxHp);
}