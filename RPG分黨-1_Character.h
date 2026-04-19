#ifndef CHARACTER_H
#define CHARACTER_H
using namespace std;
#include <string>

// ==========================================
// 進度一：核心物件建立 (宣告)
// ==========================================
class Character {
private:
    string name;
    int hp;
    int maxHp;

public:
    Character(string n, int health);
    bool isAlive();
    string getName();
    int getHp();
    void takeDamage(int damage);
};

#endif // CHARACTER_H
