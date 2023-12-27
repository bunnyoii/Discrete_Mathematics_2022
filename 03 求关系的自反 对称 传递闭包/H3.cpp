#include <iostream>
#include <vector>
#include <conio.h>
#include <iomanip>
using namespace std;

int inputNum(bool opt);
vector<vector<int>> generateMatrix();

class Relation {
private:
	vector<vector<int>> graph;
public:
	// ���캯�� ����һ����ϵ������Ϊ��������ʼ����ϵ����
	Relation(const vector<vector<int>>&matrix):graph(matrix){}
	void reflexiveClosure();						// �Է��հ�
	void symmetricClosure();						// �ԳƱհ�
	void transitiveClosure();						// ���ݱհ�
	void print();
	bool option();
};

bool Relation::option()
{
	cout << "\n�������Ӧ���ѡ���㷨\n";
	cout << "1.�Է��հ�   2.���ݱհ�   3.�ԳƱհ�   4.�˳�\n";
	cout << "��ѡ��";
	int opt = inputNum(0);
	switch (opt) {
	case 1:
		reflexiveClosure();
		cout << "\nReflexive Closure:\n";
		print();
		break;
	case 2:
		symmetricClosure();
		cout << "\nSymmetric Closure:\n";
		print();
		break;
	case 3:
		transitiveClosure();
		cout << "\nTransitive Closure:\n";
		print();
		break;
	case 4:
		cout << "Thanks for using. Hope to see you again!\n";
		return 0;
	}
	return 1;
}

void Relation::reflexiveClosure()
{
	// ������ϵ����ĶԽ���Ԫ�أ�����������Ϊ1����ʵ���Է���
	for (int i = 0; i < graph.size(); i++) { graph[i][i] = 1; }
}

void Relation::symmetricClosure()
{
	// ������ϵ���������Ԫ�أ����(i, j)Ϊ1��������(j, i)ҲΪ1����ʵ�ֶԳ���
	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph.size(); j++) {
			if (graph[i][j] == 1) {
				graph[j][i] = 1;
			}
		}
	}
}

void Relation::transitiveClosure()
{
	for (int k = 0; k < graph.size(); k++) {
		for (int i = 0; i < graph.size(); i++) {
			for (int j = 0; j < graph.size(); j++) {
				// �������·���� i �� j ����ͨ�� k����(i, j)����Ϊ1
				if (graph[i][k] && graph[k][j]) {
					graph[i][j] = 1;
				}
			}
		}
	}
}

// ��ӡ��ϵ����
void Relation::print()
{
	for (const auto& row : graph) {
		for (int val : row) {
			cout << setw(5) << left << val << " ";
		}
		cout << endl;
	}
}

// ��������
int inputNum(bool opt)
{
	int maxSize;
	if (opt)
		maxSize = 9;
	else
		maxSize = 4;
	int inputNum;
	while (true) {
		std::cin >> inputNum;
		if (std::cin.fail() || inputNum < 0 || inputNum > maxSize) {
			std::cin.clear();
			std::cin.ignore(65536, '\n');
			std::cout << "����������������������\n";
		}
		else {
			if (std::cin.get() == '\n')
				break;
			else {
				std::cin.clear();
				std::cin.ignore(65536, '\n');
				std::cout << "����������������������\n";
			}
		}
	}
	return inputNum;
}

// ���ɾ���
vector<vector<int>> generateMatrix()
{
	int matRow = 0, matCol = 0;
	cout << "����������������";
	matRow = inputNum(1);
	cout << "����������������";
	matCol = inputNum(1);
	vector<vector<int>> graph(matRow, vector<int>(matRow, 0));
	cout << "�������ϵ����:";
	for (int i = 0; i < matRow; i++) {
		for (int j = 0; j < matCol; j++) {
			while ((graph[i][j] = _getch() - '0') != 1 && graph[i][j] != 0);
			cout << setw(5) << graph[i][j];
		}
		cout << endl << "               ";
	}
	return graph;
}

void menu() 
{
	cout << "������������������������������������������������������������������������\n";
	cout << "��                      ��ϵ�ĶԳơ��Է�������                        ��\n";
	cout << "��      Symmetric Relation/Reflexive Relation/Transitive Relation     ��\n";
	cout << "������������������������������������������������������������������������\n";
}

int main()
{
	bool loop = 1;
	vector<vector<int>> matrix;
	menu();
	matrix = generateMatrix();
	Relation relation(matrix);
	cout << "\nOriginal Matrix:\n";
	relation.print();
	while (loop) {
		loop = relation.option();
	}
	return 0;
}