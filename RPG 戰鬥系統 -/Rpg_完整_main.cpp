#include <iostream>
#include <cstdlib>
#include <ctime>
#include "RPG_Roles.h" 

using namespace std;

// 戰鬥流程函式
bool playBattleStage(Character* player, Character* enemy, int stageNum) {
    int turnCount = 1;
    cout << endl << "=========================================" << endl;
    cout << " 進入第 " << stageNum << " 關！野生 " << enemy->getName() << " 出現了！" << endl;
    cout << "=========================================" << endl;

    while (player->isAlive() && enemy->isAlive()) {
        cout << endl << "[第 " << turnCount << " 回合]" << endl;
        // 將原本的 \n 改為 endl
        cout << "[狀態] " << player->getStatus() << endl << enemy->getStatus() << endl;

        player->reduceCD();
        enemy->reduceCD();

        player->takeAction(*enemy);

        if (!enemy->isAlive()) {
            cout << endl << "=========================================" << endl;
            cout << " 擊敗了 " << enemy->getName() << "！你贏得了第 " << stageNum << " 關！" << endl;
            cout << "=========================================" << endl;
            return true; 
        }

        enemy->takeAction(*player);

        if (!player->isAlive()) {
            cout << endl << "=========================================" << endl;
            cout << " " << player->getName() << " 倒下了... Game Over。" << endl;
            cout << "=========================================" << endl;
            return false; 
        }
        turnCount++;
    }
    return false;
}

int main() {
    srand(time(0)); 

    cout << "=========================================" << endl;
    cout << " 歡迎來到簡易 RPG 戰鬥系統！" << endl;
    cout << "=========================================" << endl;
    cout << "請選擇你的職業：" << endl << "1. 法師 (使用魔力 MP)" << endl << "2. 戰士 (使用體力 SP)" << endl;
    cout << "請輸入數字 (1 或 2): ";
    
    int classChoice;
    cin >> classChoice;

    Character* player = nullptr; 
    if (classChoice == 2) player = new Warrior();
    else player = new Mage(); 

    Monster stage1Enemy;
    if (playBattleStage(player, &stage1Enemy, 1)) {
        cout << endl << ">>> 戰鬥結束，稍作休息..." << endl << ">>> " << player->getName() << " 喝下了地上的生命藥水！" << endl;
        player->heal(30); 
        player->restoreResources(); // 恢復滿狀態

        Boss stage2Enemy;
        if (playBattleStage(player, &stage2Enemy, 2)) {
            cout << endl << "★★★ 恭喜你！通關了所有的關卡，拯救了世界！ ★★★" << endl << endl;
        }
    }

    delete player; // 釋放記憶體
    return 0;
}