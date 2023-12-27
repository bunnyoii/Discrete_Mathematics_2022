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
	// 构造函数 接受一个关系矩阵作为参数并初始化关系对象
	Relation(const vector<vector<int>>&matrix):graph(matrix){}
	void reflexiveClosure();						// 自反闭包
	void symmetricClosure();						// 对称闭包
	void transitiveClosure();						// 传递闭包
	void print();
	bool option();
};

bool Relation::option()
{
	cout << "\n请输入对应序号选择算法\n";
	cout << "1.自反闭包   2.传递闭包   3.对称闭包   4.退出\n";
	cout << "请选择：";
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
	// 遍历关系矩阵的对角线元素，并将其设置为1，以实现自反性
	for (int i = 0; i < graph.size(); i++) { graph[i][i] = 1; }
}

void Relation::symmetricClosure()
{
	// 遍历关系矩阵的所有元素，如果(i, j)为1，则设置(j, i)也为1，以实现对称性
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
				// 如果存在路径从 i 到 j 或者通过 k，则将(i, j)设置为1
				if (graph[i][k] && graph[k][j]) {
					graph[i][j] = 1;
				}
			}
		}
	}
}

// 打印关系矩阵
void Relation::print()
{
	for (const auto& row : graph) {
		for (int val : row) {
			cout << setw(5) << left << val << " ";
		}
		cout << endl;
	}
}

// 输入数字
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
			std::cout << "输入数据有误，请重新输入\n";
		}
		else {
			if (std::cin.get() == '\n')
				break;
			else {
				std::cin.clear();
				std::cin.ignore(65536, '\n');
				std::cout << "输入数据有误，请重新输入\n";
			}
		}
	}
	return inputNum;
}

// 生成矩阵
vector<vector<int>> generateMatrix()
{
	int matRow = 0, matCol = 0;
	cout << "请输入矩阵的行数：";
	matRow = inputNum(1);
	cout << "请输入矩阵的列数：";
	matCol = inputNum(1);
	vector<vector<int>> graph(matRow, vector<int>(matRow, 0));
	cout << "请输入关系矩阵:";
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
	cout << "····································\n";
	cout << "·                      关系的对称、自反、传递                        ·\n";
	cout << "·      Symmetric Relation/Reflexive Relation/Transitive Relation     ·\n";
	cout << "····································\n";
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