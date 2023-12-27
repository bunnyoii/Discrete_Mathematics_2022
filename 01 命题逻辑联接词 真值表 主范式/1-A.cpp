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
        bool p = GetInput("������P��ֵ��0��1��,�Իس�����: ");
        bool q = GetInput("������Q��ֵ��0��1��,�Իس�����: ");
        CalculateAndOutput(p, q);
    } while (AskContinue());
}

void Solution::Menu() const {
    std::cout << "***************************************\n"
        << "**                                   **\n"
        << "**        ��ӭ�����߼��������       **\n"
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
            std::cout << "����������������������\n";
        }
        else {
            return input;
        }
    }
}

bool Solution::AskContinue() const {
    char ch;
    std::cout << "�Ƿ�������㣿(Y/N) ";
    std::cin >> ch;

    return ch == 'Y' || ch == 'y';
}

void Solution::CalculateAndOutput(bool p, bool q) const {
    bool andResult = p && q;
    bool orResult = p || q;
    bool impliesResult = !p || q;
    bool iffResult = (p && q) || (!p && !q);

    std::cout << "\n\n  ��ȡ:\n       P��Q = " << andResult << std::endl
        << "  ��ȡ:\n       P��Q = " << orResult << std::endl
        << "  ����:\n       P->Q = " << impliesResult << std::endl
        << "  ˫����:\n       P<->Q = " << iffResult << std::endl;
}

int main() {
    Solution operationOfLogicalConnectives;
    operationOfLogicalConnectives.Run();
    return 0;
}
