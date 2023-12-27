#include <iostream>

class Solution {
public:
    void Run();
private:
    void Menu() const;
    bool GetInput(const char* prompt) const;
    bool AskContinue() const;
    void CalculateAndOutput(bool p, bool q) const;
};

void Solution::Run() {
    Menu();
    do {
        bool p = GetInput("请输入P的值（0或1）,以回车结束: ");
        bool q = GetInput("请输入Q的值（0或1）,以回车结束: ");
        CalculateAndOutput(p, q);
    } while (AskContinue());
}

void Solution::Menu() const {
    std::cout << "***************************************\n"
        << "**                                   **\n"
        << "**        欢迎进入逻辑运算程序       **\n"
        << "**                                   **\n"
        << "***************************************\n\n";
}

bool Solution::GetInput(const char* prompt) const {
    bool input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail() || (input != 0 && input != 1)) {
            std::cin.clear();
            std::cin.ignore(65536, '\n');
            std::cout << "输入数据有误，请重新输入\n";
        }
        else {
            return input;
        }
    }
}

bool Solution::AskContinue() const {
    char ch;
    std::cout << "是否继续运算？(Y/N) ";
    std::cin >> ch;

    return ch == 'Y' || ch == 'y';
}

void Solution::CalculateAndOutput(bool p, bool q) const {
    bool andResult = p && q;
    bool orResult = p || q;
    bool impliesResult = !p || q;
    bool iffResult = (p && q) || (!p && !q);

    std::cout << "\n\n  合取:\n       P∧Q = " << andResult << std::endl
        << "  析取:\n       P∨Q = " << orResult << std::endl
        << "  条件:\n       P->Q = " << impliesResult << std::endl
        << "  双条件:\n       P<->Q = " << iffResult << std::endl;
}

int main() {
    Solution operationOfLogicalConnectives;
    operationOfLogicalConnectives.Run();
    return 0;
}
