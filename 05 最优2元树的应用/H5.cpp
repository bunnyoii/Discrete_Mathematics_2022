#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;
// 树节点的结构
template <class D,class F>
struct Node {
    D data; // 存储字符
    F freq; // 存储频率
    Node* left, * right; // 左右子节点

    Node(D data, F freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

// 用于优先队列的比较函数
template <class D, class F>
struct compare {
    // 重载括号运算符
    bool operator()(Node<D,F>* l, Node<D,F>* r) {
        // 高频率的节点应该排在队列的后面
        return (l->freq > r->freq);
    }
};

// 哈夫曼树类，包含构建和打印树的方法
template <class D, class F>
class HuffmanTree {
private:
    Node<D, F>* root; // 哈夫曼树的根

    // 递归函数，用于打印从根到每个叶子节点的路径（哈夫曼编码）
    void printCodes(Node<D, F>* root, string str) {
        if (!root) return;

        // 如果是叶子节点，打印字符和对应的编码
        if (root->data != '$')
            cout << root->data << ": " << str << "\n";

        // 递归遍历左右子树
        printCodes(root->left, str + "0");
        printCodes(root->right, str + "1");
    }

public:
    // 构造函数
    HuffmanTree() : root(nullptr) {}

    // 构建哈夫曼树
    void buildTree(const vector<char>& data, const vector<int>& freq, int size) {
        // 创建一个优先队列（最小堆）
        priority_queue<Node<D, F>*, vector<Node<D, F>*>, compare<D,F>> minHeap;

        // 将所有字符及其频率添加到最小堆中
        for (int i = 0; i < size; ++i) {
            minHeap.push(new Node<D,F>(data[i], freq[i]));
        }


        // 循环，直到堆中只剩一个节点（树的根）
        while (minHeap.size() != 1) {
            Node<D, F>* left = minHeap.top(); minHeap.pop();
            Node<D, F>* right = minHeap.top(); minHeap.pop();

            // 创建一个新节点，其频率是两个最小节点的总和
            Node<D, F>* top = new Node<D, F>('$', left->freq + right->freq);
            top->left = left;
            top->right = right;

            minHeap.push(top);
        }

        root = minHeap.top(); // 根节点
    }

    // 打印哈夫曼树的编码
    void printHuffmanCodes() {
        cout << "哈夫曼编码如下：\n";
        printCodes(root, "");
    }
};

// 输入处理函数
static int inputNumber() {
    int inputNum = 0;
    while (true) {
        std::cin >> inputNum;
        if (std::cin.fail() || inputNum < 0 || inputNum > 65536) {
            // 输入验证
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

void menu()
{
    std::cout << "·················\n";
    std::cout << "·          最优二元树          ·\n";
    std::cout << "·      Optimal Binary Tree     ·\n";
    std::cout << "·················\n";
}

int main()
{
    HuffmanTree<char, int> huffmanTree;
    int nodeNum = 0;
    char inputName;
    int inputFreq;
    vector<char> nodeName;
    vector<int> nodeFreq;
    menu();
    std::cout << "请输入节点的个数：";
    nodeNum = inputNumber();
    std::cout << "请依次输入节点名称(用字母表示)及其频率(用数字表示)：\n";
    for (int i = 0; i < nodeNum; i++) {
        while (true) {
            std::cin >> inputName >> inputFreq;
            if ((inputName >= 'a' && inputName <= 'z') || (inputName >= 'A' && inputName <= 'Z')) {
                if (inputFreq >= 0)
                    break;
                else
                    std::cout << "节点频率不可以为负数，请重新输入：";
            }
            else
                std::cout << "节点名称输入错误，请重新输入：";

        }
        nodeName.push_back(inputName);
        nodeFreq.push_back(inputFreq);
    }
    huffmanTree.buildTree(nodeName, nodeFreq, nodeName.size());
    huffmanTree.printHuffmanCodes();
    return 0;
}