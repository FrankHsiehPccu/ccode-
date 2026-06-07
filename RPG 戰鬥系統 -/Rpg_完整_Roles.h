#ifndef ROLES_H
#define ROLES_H
#include "Character.h"

// === 法師類別 ===
// 【繼承】Mage 繼承了 Character 的所有基礎屬性與方法
class Mage : public Character {
private:
    int mp; // 法師專屬資源：魔力
    int maxMp;
    int explosionCD; // 大招冷卻時間
public:
    Mage();
    // 使用 override 關鍵字，明確表示我們要覆寫父類別的虛擬函式
    void reduceCD() override;
    string getStatus() override;
    void restoreResources() override;
    void takeAction(Character& target) override;
};

// === 戰士類別 ===
class Warrior : public Character {
private:
    int sp; // 戰士專屬資源：體力
    int maxSp;
    int smashCD; 
public:
    Warrior();
    void reduceCD() override;
    string getStatus() override;
    void restoreResources() override;
    void takeAction(Character& target) override;
};

// === 怪物類別 (第一關) ===
class Monster : public Character {
private:
    int dodgeCD;
public:
    Monster();
    void reduceCD() override;
    void takeAction(Character& target) override; // 怪物的行動是由 AI (亂數) 決定的
};

// === 魔王類別 (第二關) ===
class Boss : public Character {
private:
    int ultimateCD; // 魔王專屬的大招冷卻
public:
    Boss();
    void reduceCD() override;
    void takeAction(Character& target) override;
};
#endif