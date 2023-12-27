#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <vector>
#include <cctype>
#include <cmath>
#include <set>
using namespace std;

// 辅助函数：将中缀表达式转换为后缀表达式
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

/* 解析与计算公式 */
typedef class PropositionalFormula {
	string formula;
	map<char, int> priority;		// 存储运算符的优先级
	map<char, bool> variables; // 存储变量及其赋值
	bool isOperator(char ch) { return priority.find(ch) != priority.end(); }
	bool isVariable(char ch) { return isalpha(ch); }
public:
	// 定义运算符优先级
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
	// 获取公式中的所有变量
	set<char> getVariables() const {
		set<char> vars;
		for (char ch : formula) {
			if (isalpha(ch)) {  // 直接检查字符是否为字母
				vars.insert(ch);
			}
		}
		return vars;
	}
	// 设置变量的值
	void setVariableValue(char var, bool value) {
		if (isVariable(var)) {
			variables[var] = value;
		}
	}
	// 检查公式是否有效
	bool isValid();
	// 计算真值
	int calculate();
}PF;

// 检查公式是否有效
bool PropositionalFormula::isValid()
{
	if (formula.empty()) return false;
	int balance = 0;
	bool lastWasOperator = true;  // 假设公式以运算符开始
	for (char ch : formula) {
		if (ch == '(') {
			balance++;
			lastWasOperator = true;  // 括号后应该是运算符或变量
		}
		else if (ch == ')') {
			balance--;
			if (balance < 0 || lastWasOperator) return false; // 不匹配的或空的括号
			lastWasOperator = false;
		}
		else if (isVariable(ch)) {
			if (!lastWasOperator) return false; // 变量之间缺少运算符
			lastWasOperator = false;
		}
		else if (isOperator(ch)) {
			if (lastWasOperator && ch != '!' && ch != '(') return false; // 连续的运算符（除了非运算符）
			lastWasOperator = true;
		}
		else {
			return false; // 非法字符
		}
	}

	return balance == 0 && !lastWasOperator; // 确保所有括号都闭合且不以运算符结束
}

// 计算真值
int PropositionalFormula::calculate()
{
	auto postfix = toPostfix(formula, priority);  // 将中缀表达式转换为后缀表达式
	stack<bool> valStack;  // 用于存储布尔值的栈

	// 遍历后缀表达式
	for (char token : postfix) {
		if (isalpha(token)) {  // 如果是变量，则压入其值
			valStack.push(variables.at(token));
		}
		else {  // 否则，应用逻辑运算符
			bool right = valStack.top();
			valStack.pop();
			if (token == '!') {  // 非运算符
				valStack.push(!right);
			}
			else {  // 其他运算符需要两个操作数
				bool left = valStack.top();
				valStack.pop();
				switch (token) {
				case '&':
					valStack.push(left && right);
					break;
				case '|':
					valStack.push(left || right);
					break;
				case '^':  // 修改此处，将其作为蕴含运算
					valStack.push(!left || right); // A → B 是当 A 为假或 B 为真时为真
					break;
				case '~':
					valStack.push(left == right);
					break;
				}
			}
		}
	}

	return valStack.top();  // 栈顶元素就是整个表达式的结果
}

/* 生成与显示真值表 */
class TruthTable {
	PF& formula;
	vector<map<char, bool>> truthTable; // 存储每行的变量赋值和结果
	vector<bool> results; // 存储每行的结果

public:
	TruthTable(PF& f) : formula(f) {}
	// 生成真值表
	void generateTruthTable();
	// 显示真值表
	void display();
	string getDNF();
	string getCNF();
};

// 生成真值表
void TruthTable::generateTruthTable()
{
	// 提取所有变量
	set<char> vars = formula.getVariables();
	int numVars = vars.size();
	int numRows = pow(2, numVars);

	// 生成并计算每个真值指派
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

// 显示真值表
void TruthTable::display()
{
	cout << "The truth table is as follows : \n";
	for (const auto& var : truthTable[0]) {
		cout << var.first << "\t";
	}
	cout << "Result\n";
	// 打印每行的真值指派和结果
	for (size_t i = 0; i < truthTable.size(); ++i) {
		for (const auto& var : truthTable[i]) {
			cout << var.second << "\t";  // 直接打印 1 或 0
		}
		cout << results[i] << "\n"; // 同样直接打印 1 或 0 表示结果
	}
}

// 主析取范式
string TruthTable::getDNF() {
	string dnf;
	int index = 0; // 通用索引，用于m(n)和M(n)
	for (size_t i = 0; i < truthTable.size(); ++i) {
		if (results[i]) { // 如果结果为真
			if (!dnf.empty()) dnf += " ∨ ";
			dnf += "m(" + to_string(index) + ")";
		}
		index++; // 无论结果如何，索引都递增
	}
	return dnf.empty() ? "FALSE" : dnf;
}

// 主合取范式
string TruthTable::getCNF() {
	string cnf;
	int index = 0; // 通用索引，用于m(n)和M(n)
	for (size_t i = 0; i < truthTable.size(); ++i) {
		if (!results[i]) { // 如果结果为假
			if (!cnf.empty()) cnf += " ∧ ";
			cnf += "M(" + to_string(index) + ")";
		}
		index++; // 无论结果如何，索引都递增
	}
	return cnf.empty() ? "TRUE" : cnf;
}

// 菜单
void menu()
{
	cout << "***************************************\n";
	cout << "**                                   **\n";
	cout << "**         欢迎进入逻辑运算软件      **\n";
	cout << "**   (可运算真值表,主范式,支持括号)  **\n";
	cout << "**                                   **\n";
	cout << "**              用!表示非            **\n";
	cout << "**              用&表示与            **\n";
	cout << "**              用|表示或            **\n";
	cout << "**             用^表示蕴含           **\n";
	cout << "**             用~表示等值           **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n";
	cout << "Please enter a legitimate proposition formula: \n";
}

// 检查变量个数
int countUniqueVariables(const string& expression) {
	set<char> variables;
	for (char ch : expression) {
		if (isalpha(ch)) { // 检查字符是否是字母
			variables.insert(ch); // 将字母（变量）添加到集合中
		}
	}
	return variables.size(); // 集合的大小即唯一变量的个数
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
		cout << "主析取范式(DNF): \n" << tt.getDNF() << endl;
		cout << "主合取范式(CNF): \n" << tt.getCNF() << endl;
	}
	else {
		cout << "Invalid formula!\n";
	}
	return 0;
}