#include "Character.h"
#include <iostream>

using namespace std;

// ==========================================
// 進度一：核心物件建立 (實作)
// ==========================================

Character::Character(string n, int health) {
    name = n;
    hp = health;
    maxHp = health;
}

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
    hp -= damage;
    
    // 遇到的挑戰與解法 (一)：確保血量不會變成負數
    if (hp < 0) {
        hp = 0;
    }
    cout << name << " 受到了 " << damage << " 點傷害！剩餘 HP: " << hp << endl;
}
