#include <iostream>
#include "Character.h"
using namespace std;

// 建構子實作：使用「初始化列表」將傳入的參數設定給內部變數
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

// 受傷邏輯：集中處理防禦與扣血，這就是【封裝】的好處，主程式不用自己寫扣血邏輯
void Character::takeDamage(int damage) {
    if (isDefending) { // 如果處於防禦狀態，則免疫本次傷害
        cout << name << " 防禦/閃避了這次攻擊，沒有受到傷害！" << endl;
        isDefending = false; // 消耗掉防禦狀態
    } else {
        hp -= damage;
        if (hp < 0) hp = 0; // 【防呆機制】確保血量不會扣到變成負數
        cout << name << " 受到了 " << damage << " 點傷害！" << endl;
    }
}

// 治療邏輯
void Character::heal(int amount) {
    hp += amount;
    if (hp > maxHp) hp = maxHp; // 【防呆機制】確保補血不會超過最大血量上限
    cout << name << " 恢復了 " << amount << " 點 HP！" << endl;
}

void Character::setDefending(bool state) { 
    isDefending = state; 
}

// 回傳基礎的狀態字串 (只有 HP)
string Character::getStatus() {
    return name + " HP: " + to_string(hp) + "/" + to_string(maxHp);
}