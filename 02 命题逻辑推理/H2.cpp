#include <iostream>
using namespace std;

int main()
{
	int A, B, C, D, E;       //������е�������Ϊ�������
	//����ѭ������ٿ��ܳ��ֵ�32��ȡֵ���
	for (A = 0; A <= 1; A++)
		for (B = 0; B <= 1; B++)
			for (C = 0; C <= 1; C++)
				for (D = 0; D <= 1; D++)
					for (E = 0; E <= 1; E++)
						if ((A || B) && (!A || C) && (!D || E) && (D || !C) && !E) {        //����ɷ��Ż���ʹ�����⹫ʽ�����ļ�Ϊ���
							cout << "A = " << A << ", B = " << B << endl;
							if (A == 1)  cout << "A͵���ֱ�" << endl;
							else if (B == 1)  cout << "B͵���ֱ�" << endl;
							break;
						}
	return 0;
}