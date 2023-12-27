#include <iostream>
using namespace std;

int main()
{
	int A, B, C, D, E;       //将题干中的条件记为五个命题
	//五重循环，穷举可能出现的32种取值情况
	for (A = 0; A <= 1; A++)
		for (B = 0; B <= 1; B++)
			for (C = 0; C <= 1; C++)
				for (D = 0; D <= 1; D++)
					for (E = 0; E <= 1; E++)
						if ((A || B) && (!A || C) && (!D || E) && (D || !C) && !E) {        //将题干符号化，使该命题公式成立的即为结果
							cout << "A = " << A << ", B = " << B << endl;
							if (A == 1)  cout << "A偷了手表" << endl;
							else if (B == 1)  cout << "B偷了手表" << endl;
							break;
						}
	return 0;
}