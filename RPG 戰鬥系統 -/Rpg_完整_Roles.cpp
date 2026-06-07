#include <iostream>
#include <cstdlib>
#include "Roles.h"
using namespace std;

// --- 法師實作 ---
// 初始化法師數值，設定初始 MP 為 10
Mage::Mage() : Character("法師", 50), mp(10), maxMp(10), explosionCD(0) {} 
void Mage::reduceCD() { if (explosionCD > 0) explosionCD--; }

// 覆寫狀態顯示，加上法師專屬的 MP 條
string Mage::getStatus() {
    return name + " HP: " + to_string(hp) + "/" + to_string(maxHp) + 
           " | MP: " + to_string(mp) + "/" + to_string(maxMp);
}
void Mage::restoreResources() {
    mp = maxMp; // 過關時補滿魔力
    cout << ">>> 冥想片刻後，" << name << " 的魔力 (MP) 完全恢復了！" << endl;
}

// 法師的戰鬥決策邏輯 (包含資源判斷與防呆)
void Mage::takeAction(Character& target) {
    int choice = 0;
    bool validChoice = false; // 用來控制是否成功執行動作的布林值
    
    while (!validChoice) { // 如果玩家輸入錯誤或資源不足，會一直留在迴圈內重新選擇
        cout << endl << "--- 你的回合 (" << name << ") ---" << endl;
        cout << "1. 輕攻擊 (傷害 7) [回復 1 MP]" << endl << "2. 重攻擊 (傷害 10~15) [消耗 2 MP]" << endl;
        cout << "3. 冥想回血 (恢復 15 HP) [回復 4 MP]" << endl << "4. 爆炸 (傷害 40) [消耗 5 MP, CD: " << explosionCD << "]" << endl;
        cout << "請選擇行動 (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << endl << "> " << name << " 使用了 輕攻擊！" << endl; 
                target.takeDamage(7); // 呼叫敵人的受傷函式
                mp = (mp + 1 > maxMp) ? maxMp : mp + 1; // 回復 MP，但不超過上限
                validChoice = true; // 動作成功，準備跳出 while 迴圈
                break;
            case 2:
                if (mp >= 2) { // 檢查資源是否足夠
                    cout << endl << "> " << name << " 使用了 重攻擊！" << endl;
                    target.takeDamage(rand() % 6 + 10); // 產生 10~15 的亂數傷害
                    mp -= 2; validChoice = true;
                } 
                else cout << "魔力不足！請重新選擇。" << endl; 
                break;
            // ... (case 3, case 4 邏輯雷同，處理對應的 MP 消耗與冷卻設定)
            case 3:
                cout << endl << "> " << name << " 施放了 冥想回血！" << endl; 
                heal(15);
                mp = (mp + 4 > maxMp) ? maxMp : mp + 4; validChoice = true; 
                break;
            case 4:
                if (explosionCD == 0 && mp >= 5) {
                    cout << endl << "> " << name << " 施放了 強力 爆炸！" << endl; 
                    target.takeDamage(40);
                    mp -= 5; explosionCD = 3; validChoice = true; // 施放後進入 3 回合 CD
                } 
                else if (explosionCD > 0) cout << "技能冷卻中！請重新選擇。" << endl;
                else cout << "魔力不足！請重新選擇。" << endl;
                break;
            default: cout << "無效的輸入，請重新選擇。" << endl; // 輸入非 1~4 的防呆
        }
    }
}

// --- 戰士實作 (邏輯與法師相似，資源改為 SP) ---
Warrior::Warrior() : Character("戰士", 70), sp(100), maxSp(100), smashCD(0) {} 
void Warrior::reduceCD() { if (smashCD > 0) smashCD--; }
string Warrior::getStatus() {
    return name + " HP: " + to_string(hp) + "/" + to_string(maxHp) + 
           " | 體力: " + to_string(sp) + "/" + to_string(maxSp);
}
void Warrior::restoreResources() {
    sp = maxSp;
    cout << ">>> 稍作喘息後，" << name << " 的體力 (SP) 完全恢復了！" << endl;
}
void Warrior::takeAction(Character& target) {
    int choice = 0;
    bool validChoice = false;
    while (!validChoice) {
        cout << endl << "--- 你的回合 (" << name << ") ---" << endl;
        cout << "1. 劈砍 (傷害 8) [消耗 15 體力]" << endl << "2. 旋風斬 (傷害 12~18) [消耗 30 體力]" << endl;
        cout << "3. 舉盾防禦 (擋下下次攻擊) [回復 50 體力]" << endl << "4. 致命碎擊 (傷害 35) [消耗 50 體力, CD: " << smashCD << "]" << endl;
        cout << "請選擇行動 (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (sp >= 15) {
                    cout << endl << "> " << name << " 使用了 劈砍！" << endl; 
                    target.takeDamage(8);
                    sp -= 15; validChoice = true;
                } 
                else cout << "體力不足！請重新選擇。" << endl;
                break;
            case 2:
                if (sp >= 30) {
                    cout << endl << "> " << name << " 使用了 旋風斬！" << endl; 
                    target.takeDamage(rand() % 7 + 12);
                    sp -= 30; validChoice = true;
                } 
                else cout << "體力不足！請重新選擇。" << endl; 
                break;
            case 3:
                cout << endl << "> " << name << " 舉起了盾牌！" << endl; 
                setDefending(true); // 啟動防禦狀態
                sp = (sp + 50 > maxSp) ? maxSp : sp + 50; validChoice = true; 
                break;
            case 4:
                if (smashCD == 0 && sp >= 50) {
                    cout << endl << "> " << name << " 使出了 致命碎擊！" << endl; 
                    target.takeDamage(35);
                    sp -= 50; smashCD = 3; validChoice = true;
                } 
                else if (smashCD > 0) cout << "技能冷卻中！請重新選擇。" << endl;
                else cout << "體力不足！請重新選擇。" << endl; 
                break;
            default: cout << "無效的輸入，請重新選擇。" << endl;
        }
    }
}

// --- 一般怪物實作 (簡易 AI) ---
Monster::Monster() : Character("哥布林", 60), dodgeCD(0) {}
void Monster::reduceCD() { if (dodgeCD > 0) dodgeCD--; }
void Monster::takeAction(Character& target) {
    cout << endl << "--- 敵人的回合 ---" << endl;
    int action = rand() % 4 + 1; // 產生 1~4 的亂數決定怪物動作
    if (action == 4 && dodgeCD > 0) action = 1; // 若抽到閃避但還在 CD，強制改為輕攻擊
    switch (action) {
        case 1: cout << "> " << name << " 使用了 輕攻擊！" << endl; 
            target.takeDamage(6); break;
        case 2: cout << "> " << name << " 使用了 重攻擊！" << endl; 
            target.takeDamage(10); break;
        case 3: cout << "> " << name << " 使用了 回血！" << endl; 
            heal(15); break;
        case 4: cout << "> " << name << " 準備 閃避！" << endl; 
            setDefending(true); dodgeCD = 4; break;
    }
}

// --- 魔王實作 (高智能 AI) ---
Boss::Boss() : Character("惡魔領主", 120), ultimateCD(2) {} 
void Boss::reduceCD() { if (ultimateCD > 0) ultimateCD--; }
void Boss::takeAction(Character& target) {
    cout << endl << "--- 魔王的回合 ---" << endl;
    
    // 魔王 AI 邏輯：只要大招 CD 好了，就絕對優先施放 (不隨機)
    if (ultimateCD == 0) {
        cout << "> " << name << " 釋放了 毀滅死光 ！！！" << endl;
        target.takeDamage(25); 
        ultimateCD = 4; 
    } else {
        int action = rand() % 3 + 1; // 大招還沒好，就隨機使用 1~3 的普通技能
        switch (action) {
            case 1: cout << "> " << name << " 揮舞巨爪！" << endl; 
                target.takeDamage(12); break;
            case 2: cout << "> " << name << " 吐出毒液！" << endl;
                target.takeDamage(18); break;
            case 3: cout << "> " << name << " 狂吼著恢復體力！" << endl; 
                heal(20); break;
        }
    }
}