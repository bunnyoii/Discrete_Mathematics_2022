#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <vector>
#include <cctype>
#include <cmath>
#include <set>
using namespace std;

// ��������������׺���ʽת��Ϊ��׺���ʽ
vector<char> toPostfix(const string& infix, const map<char, int>& priority) {
	vector<char> postfix;
	stack<char> opStack;

	for (char token : infix) {
		if (isalpha(token)) {
			postfix.push_back(token);
		}
		else if (token == '(') {
			opStack.push(token);
		}
		else if (token == ')') {
			while (!opStack.empty() && opStack.top() != '(') {
				postfix.push_back(opStack.top());
				opStack.pop();
			}
			opStack.pop();  // Pop '('
		}
		else {
			while (!opStack.empty() && priority.at(token) <= priority.at(opStack.top())) {
				postfix.push_back(opStack.top());
				opStack.pop();
			}
			opStack.push(token);
		}
	}

	while (!opStack.empty()) {
		postfix.push_back(opStack.top());
		opStack.pop();
	}

	return postfix;
}

/* ��������㹫ʽ */
typedef class PropositionalFormula {
	string formula;
	map<char, int> priority;		// �洢����������ȼ�
	map<char, bool> variables; // �洢�������丳ֵ
	bool isOperator(char ch) { return priority.find(ch) != priority.end(); }
	bool isVariable(char ch) { return isalpha(ch); }
public:
	// ������������ȼ�
	PropositionalFormula(const string& f) : formula(f) {
		priority['('] = 6;
		priority[')'] = 6;
		priority['!'] = 5;
		priority['&'] = 4;
		priority['|'] = 3;
		priority['^'] = 2;
		priority['~'] = 1;
		priority['#'] = 0;
	}
	// ��ȡ��ʽ�е����б���
	set<char> getVariables() const {
		set<char> vars;
		for (char ch : formula) {
			if (isalpha(ch)) {  // ֱ�Ӽ���ַ��Ƿ�Ϊ��ĸ
				vars.insert(ch);
			}
		}
		return vars;
	}
	// ���ñ�����ֵ
	void setVariableValue(char var, bool value) {
		if (isVariable(var)) {
			variables[var] = value;
		}
	}
	// ��鹫ʽ�Ƿ���Ч
	bool isValid();
	// ������ֵ
	int calculate();
}PF;

// ��鹫ʽ�Ƿ���Ч
bool PropositionalFormula::isValid()
{
	if (formula.empty()) return false;
	int balance = 0;
	bool lastWasOperator = true;  // ���蹫ʽ���������ʼ
	for (char ch : formula) {
		if (ch == '(') {
			balance++;
			lastWasOperator = true;  // ���ź�Ӧ��������������
		}
		else if (ch == ')') {
			balance--;
			if (balance < 0 || lastWasOperator) return false; // ��ƥ��Ļ�յ�����
			lastWasOperator = false;
		}
		else if (isVariable(ch)) {
			if (!lastWasOperator) return false; // ����֮��ȱ�������
			lastWasOperator = false;
		}
		else if (isOperator(ch)) {
			if (lastWasOperator && ch != '!' && ch != '(') return false; // ����������������˷��������
			lastWasOperator = true;
		}
		else {
			return false; // �Ƿ��ַ�
		}
	}

	return balance == 0 && !lastWasOperator; // ȷ���������Ŷ��պ��Ҳ������������
}

// ������ֵ
int PropositionalFormula::calculate()
{
	auto postfix = toPostfix(formula, priority);  // ����׺���ʽת��Ϊ��׺���ʽ
	stack<bool> valStack;  // ���ڴ洢����ֵ��ջ

	// ������׺���ʽ
	for (char token : postfix) {
		if (isalpha(token)) {  // ����Ǳ�������ѹ����ֵ
			valStack.push(variables.at(token));
		}
		else {  // ����Ӧ���߼������
			bool right = valStack.top();
			valStack.pop();
			if (token == '!') {  // �������
				valStack.push(!right);
			}
			else {  // �����������Ҫ����������
				bool left = valStack.top();
				valStack.pop();
				switch (token) {
				case '&':
					valStack.push(left && right);
					break;
				case '|':
					valStack.push(left || right);
					break;
				case '^':  // �޸Ĵ˴���������Ϊ�̺�����
					valStack.push(!left || right); // A �� B �ǵ� A Ϊ�ٻ� B Ϊ��ʱΪ��
					break;
				case '~':
					valStack.push(left == right);
					break;
				}
			}
		}
	}

	return valStack.top();  // ջ��Ԫ�ؾ����������ʽ�Ľ��
}

/* ��������ʾ��ֵ�� */
class TruthTable {
	PF& formula;
	vector<map<char, bool>> truthTable; // �洢ÿ�еı�����ֵ�ͽ��
	vector<bool> results; // �洢ÿ�еĽ��

public:
	TruthTable(PF& f) : formula(f) {}
	// ������ֵ��
	void generateTruthTable();
	// ��ʾ��ֵ��
	void display();
	string getDNF();
	string getCNF();
};

// ������ֵ��
void TruthTable::generateTruthTable()
{
	// ��ȡ���б���
	set<char> vars = formula.getVariables();
	int numVars = vars.size();
	int numRows = pow(2, numVars);

	// ���ɲ�����ÿ����ֵָ��
	for (int i = 0; i < numRows; ++i) {
		map<char, bool> row;
		int mask = 1;
		for (char var : vars) {
			bool value = (i & mask) > 0;
			formula.setVariableValue(var, value);
			row[var] = value;
			mask <<= 1;
		}
		truthTable.push_back(row);
		results.push_back(formula.calculate());
	}
}

// ��ʾ��ֵ��
void TruthTable::display()
{
	cout << "The truth table is as follows : \n";
	for (const auto& var : truthTable[0]) {
		cout << var.first << "\t";
	}
	cout << "Result\n";
	// ��ӡÿ�е���ֵָ�ɺͽ��
	for (size_t i = 0; i < truthTable.size(); ++i) {
		for (const auto& var : truthTable[i]) {
			cout << var.second << "\t";  // ֱ�Ӵ�ӡ 1 �� 0
		}
		cout << results[i] << "\n"; // ͬ��ֱ�Ӵ�ӡ 1 �� 0 ��ʾ���
	}
}

// ����ȡ��ʽ
string TruthTable::getDNF() {
	string dnf;
	int index = 0; // ͨ������������m(n)��M(n)
	for (size_t i = 0; i < truthTable.size(); ++i) {
		if (results[i]) { // ������Ϊ��
			if (!dnf.empty()) dnf += " �� ";
			dnf += "m(" + to_string(index) + ")";
		}
		index++; // ���۽����Σ�����������
	}
	return dnf.empty() ? "FALSE" : dnf;
}

// ����ȡ��ʽ
string TruthTable::getCNF() {
	string cnf;
	int index = 0; // ͨ������������m(n)��M(n)
	for (size_t i = 0; i < truthTable.size(); ++i) {
		if (!results[i]) { // ������Ϊ��
			if (!cnf.empty()) cnf += " �� ";
			cnf += "M(" + to_string(index) + ")";
		}
		index++; // ���۽����Σ�����������
	}
	return cnf.empty() ? "TRUE" : cnf;
}

// �˵�
void menu()
{
	cout << "***************************************\n";
	cout << "**                                   **\n";
	cout << "**         ��ӭ�����߼��������      **\n";
	cout << "**   (��������ֵ��,����ʽ,֧������)  **\n";
	cout << "**                                   **\n";
	cout << "**              ��!��ʾ��            **\n";
	cout << "**              ��&��ʾ��            **\n";
	cout << "**              ��|��ʾ��            **\n";
	cout << "**             ��^��ʾ�̺�           **\n";
	cout << "**             ��~��ʾ��ֵ           **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n";
	cout << "Please enter a legitimate proposition formula: \n";
}

// ����������
int countUniqueVariables(const string& expression) {
	set<char> variables;
	for (char ch : expression) {
		if (isalpha(ch)) { // ����ַ��Ƿ�����ĸ
			variables.insert(ch); // ����ĸ����������ӵ�������
		}
	}
	return variables.size(); // ���ϵĴ�С��Ψһ�����ĸ���
}

int main()
{
	string inputFormula;
	menu();
	getline(cin, inputFormula);
	int count = countUniqueVariables(inputFormula);
	cout << "Number of unique variables: " << count << endl << endl;
	PF pf(inputFormula);
	if (pf.isValid()) {
		TruthTable tt(pf);
		tt.generateTruthTable();
		tt.display();
		cout << "����ȡ��ʽ(DNF): \n" << tt.getDNF() << endl;
		cout << "����ȡ��ʽ(CNF): \n" << tt.getCNF() << endl;
	}
	else {
		cout << "Invalid formula!\n";
	}
	return 0;
}