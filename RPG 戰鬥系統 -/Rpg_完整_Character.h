#ifndef CHARACTER_H // 標頭檔保護：避免這個檔案被重複載入編譯
#define CHARACTER_H
#include <string>

using namespace std;

// === 角色基底類別 ===
class Character {
protected: // 【封裝】使用 protected 讓這些變數只能被自己和繼承的子類別使用，外部不能亂改
    string name;
    int hp;
    int maxHp;
    bool isDefending; // 記錄角色是否處於防禦狀態

public:
    Character(string n, int health); // 建構子：用來設定角色的初始數值
    virtual ~Character() {} // 虛擬解構子：確保未來使用 delete 釋放記憶體時，子類別的空間也能被正確清除
    
    // 基本狀態取得與操作方法
    bool isAlive(); // 判斷是否存活 (血量 > 0)
    string getName();
    int getHp();
    
    void takeDamage(int damage); // 處理受傷與扣血的共用邏輯
    void heal(int amount); // 處理補血的共用邏輯
    void setDefending(bool state); // 開關防禦狀態
    
    // 【多型】使用 virtual 關鍵字，允許子類別覆寫 (Override) 這些方法
    virtual string getStatus(); 
    virtual void restoreResources() {} // 預設為空函式，讓有 MP/SP 的職業自己去覆寫補滿資源的邏輯
    
    // 【純虛擬函式】加上 "= 0" 代表這是一個「介面」，強制所有繼承的子類別都必須實作這兩個方法
    virtual void reduceCD() = 0; // 減少技能冷卻時間
    virtual void takeAction(Character& target) = 0; // 執行行動 (玩家選單或怪物 AI)
};

#endif