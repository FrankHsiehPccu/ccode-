#include <iostream>
#include "Character.h"

using namespace std;

// ==========================================
// 進度二：基礎戰鬥迴圈與主程式
// ==========================================
int main() {
    Character player("勇者", 50);
    Character enemy("哥布林", 30);

    cout << "=================================" << endl;
    cout << " 戰鬥開始！野生 哥布林 出現了！" << endl;
    cout << "=================================" << endl;

    while (player.isAlive() && enemy.isAlive()) {
        
        cout << endl << "---------------------------------" << endl;
        cout << "[狀態] " << player.getName() << " HP: " << player.getHp() << " | "
             << enemy.getName() << " HP: " << enemy.getHp() << endl;

        int choice = 0;
        
        // 遇到的挑戰與解法 (二)：輸入防呆機制，避免輸入錯誤導致崩潰
        while (choice != 1 && choice != 2) {
            cout << "輪到你了！請選擇行動 (1. 攻擊  2. 休息): ";
            cin >> choice;
            
            if (choice != 1 && choice != 2) {
                cout << "無效的輸入，請重新輸入數字 1 或 2！" << endl;
            }
        }

        if (choice == 1) {
            cout << endl << "> 你揮劍攻擊！" << endl;
            enemy.takeDamage(10); 
        } else if (choice == 2) {
            cout << endl << "> 你稍微喘息，沒有採取行動。" << endl;
        }

        if (!enemy.isAlive()) {
            cout << endl << "=================================" << endl;
            cout << " 哥布林被擊敗了！你贏了！" << endl;
            cout << "=================================" << endl;
            break;
        }

        cout << endl << "> 哥布林反擊！" << endl;
        player.takeDamage(5); 

        if (!player.isAlive()) {
            cout << endl << "=================================" << endl;
            cout << " 你被打敗了... Game Over。" << endl;
            cout << "=================================" << endl;
            break;
        }
    }

    return 0;
}