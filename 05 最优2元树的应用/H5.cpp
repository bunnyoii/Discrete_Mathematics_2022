#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;
// ���ڵ�Ľṹ
template <class D,class F>
struct Node {
    D data; // �洢�ַ�
    F freq; // �洢Ƶ��
    Node* left, * right; // �����ӽڵ�

    Node(D data, F freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

// �������ȶ��еıȽϺ���
template <class D, class F>
struct compare {
    // �������������
    bool operator()(Node<D,F>* l, Node<D,F>* r) {
        // ��Ƶ�ʵĽڵ�Ӧ�����ڶ��еĺ���
        return (l->freq > r->freq);
    }
};

// ���������࣬���������ʹ�ӡ���ķ���
template <class D, class F>
class HuffmanTree {
private:
    Node<D, F>* root; // ���������ĸ�

    // �ݹ麯�������ڴ�ӡ�Ӹ���ÿ��Ҷ�ӽڵ��·�������������룩
    void printCodes(Node<D, F>* root, string str) {
        if (!root) return;

        // �����Ҷ�ӽڵ㣬��ӡ�ַ��Ͷ�Ӧ�ı���
        if (root->data != '$')
            cout << root->data << ": " << str << "\n";

        // �ݹ������������
        printCodes(root->left, str + "0");
        printCodes(root->right, str + "1");
    }

public:
    // ���캯��
    HuffmanTree() : root(nullptr) {}

    // ������������
    void buildTree(const vector<char>& data, const vector<int>& freq, int size) {
        // ����һ�����ȶ��У���С�ѣ�
        priority_queue<Node<D, F>*, vector<Node<D, F>*>, compare<D,F>> minHeap;

        // �������ַ�����Ƶ����ӵ���С����
        for (int i = 0; i < size; ++i) {
            minHeap.push(new Node<D,F>(data[i], freq[i]));
        }


        // ѭ����ֱ������ֻʣһ���ڵ㣨���ĸ���
        while (minHeap.size() != 1) {
            Node<D, F>* left = minHeap.top(); minHeap.pop();
            Node<D, F>* right = minHeap.top(); minHeap.pop();

            // ����һ���½ڵ㣬��Ƶ����������С�ڵ���ܺ�
            Node<D, F>* top = new Node<D, F>('$', left->freq + right->freq);
            top->left = left;
            top->right = right;

            minHeap.push(top);
        }

        root = minHeap.top(); // ���ڵ�
    }

    // ��ӡ���������ı���
    void printHuffmanCodes() {
        cout << "�������������£�\n";
        printCodes(root, "");
    }
};

// ���봦����
static int inputNumber() {
    int inputNum = 0;
    while (true) {
        std::cin >> inputNum;
        if (std::cin.fail() || inputNum < 0 || inputNum > 65536) {
            // ������֤
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

void menu()
{
    std::cout << "����������������������������������\n";
    std::cout << "��          ���Ŷ�Ԫ��          ��\n";
    std::cout << "��      Optimal Binary Tree     ��\n";
    std::cout << "����������������������������������\n";
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
    std::cout << "������ڵ�ĸ�����";
    nodeNum = inputNumber();
    std::cout << "����������ڵ�����(����ĸ��ʾ)����Ƶ��(�����ֱ�ʾ)��\n";
    for (int i = 0; i < nodeNum; i++) {
        while (true) {
            std::cin >> inputName >> inputFreq;
            if ((inputName >= 'a' && inputName <= 'z') || (inputName >= 'A' && inputName <= 'Z')) {
                if (inputFreq >= 0)
                    break;
                else
                    std::cout << "�ڵ�Ƶ�ʲ�����Ϊ���������������룺";
            }
            else
                std::cout << "�ڵ���������������������룺";

        }
        nodeName.push_back(inputName);
        nodeFreq.push_back(inputFreq);
    }
    huffmanTree.buildTree(nodeName, nodeFreq, nodeName.size());
    huffmanTree.printHuffmanCodes();
    return 0;
}