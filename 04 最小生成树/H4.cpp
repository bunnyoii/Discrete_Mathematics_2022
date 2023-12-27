#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

const int MAX_VERTICES = 5005;  // ������󶥵���
const int MAX_EDGES = 200005;   // ����������

struct Edge {
    int src, dest, weight;       // �߽ṹ������Դ�㡢Ŀ����Ȩ��
};

// ���鼯�����ڸ���Kruskal�㷨
class UnionFind {
public:
    UnionFind(int size) : parent(size + 1) {
        for (int i = 1; i <= size; ++i) parent[i] = i; // ��ʼ�����ڵ�
    }

    int find(int vertex) {
        // ���Ҹ��ڵ㣬ͬʱ����·��ѹ��
        return parent[vertex] == vertex ? vertex : (parent[vertex] = find(parent[vertex]));
    }

    void unite(int x, int y) {
        // �ϲ���������
        parent[find(x)] = find(y);
    }

private:
    std::vector<int> parent; // �洢���ڵ���Ϣ
};

// Kruskal��С�������㷨��
class KruskalMST {
public:
    KruskalMST(int vertices) : numVertices(vertices), uf(vertices) {}

    void addEdge(int src, int dest, int weight) {
        // ��ӱ�
        edgeList.push_back({ src, dest, weight });
    }

    void constructMST() {
        // ������С������
        sortEdges(); // ���ȶԱ߽�������
        int totalWeight = 0; // ��¼��Ȩ��

        for (const auto& edge : edgeList) {
            // ����ÿ���ߣ�����Ƿ��γɻ�
            if (uf.find(edge.src) != uf.find(edge.dest)) {
                // ������γɻ��������������
                std::cout << edge.src << " -- " << edge.dest << " (Ȩ��: " << edge.weight << ")\n";
                totalWeight += edge.weight;
                uf.unite(edge.src, edge.dest);
            }
        }

        std::cout << "��С����������Ȩ��: " << totalWeight << std::endl;
    }

private:
    int numVertices;
    std::vector<Edge> edgeList;
    UnionFind uf; // ���鼯ʵ��

    void sortEdges() {
        // �߰�Ȩ������ĺ���
        std::sort(edgeList.begin(), edgeList.end(), [](const Edge& a, const Edge& b) {
            return a.weight < b.weight;
            });
    }
};

class InputHandler {
public:
    static int inputNumber(bool isVertices, int numVertices = 0) {
        // ���봦������ȷ��������Ч
        int maxSize = isVertices ? 30 : numVertices * (numVertices - 1) / 2;
        int inputNum;
        while (true) {
            std::cin >> inputNum;
            if (std::cin.fail() || inputNum < 0 || inputNum > maxSize) {
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

    static void validateVertices(int vertex, const std::set<int>& validVertices) {
        // ��֤�����Ƿ���Ч
        if (validVertices.find(vertex) == validVertices.end()) {
            throw std::invalid_argument("����Ķ��㲻����");
        }
    }
};

void menu() {
    // ����˵�
    std::cout << "������������������������������������\n";
    std::cout << "��          ��С������            ��\n";
    std::cout << "��      Minimum Spanning Tree     ��\n";
    std::cout << "������������������������������������\n";
}

int main() {
    menu();
    // ���������������
    std::cout << "���붥������[������30��]: ";
    int numVertices = InputHandler::inputNumber(true);

    std::set<int> validVertices;
    std::cout << "���붥����[�������������Ļᱻ����]:\n";
    for (int i = 0; i < numVertices; ++i) {
        int vertex;
        std::cin >> vertex;
        validVertices.insert(vertex);
    }
    std::cin.ignore(65536, '\n');

    std::cout << "����ߵ�������";
    int numEdges = InputHandler::inputNumber(false, numVertices);

    KruskalMST mst(numVertices);
    std::cout << "����ߣ�Դ�� Ŀ��� Ȩ�أ�:\n";
    for (int i = 0; i < numEdges; ++i) {
        int src, dest, weight;
        std::cin >> src >> dest >> weight;
        try {
            InputHandler::validateVertices(src, validVertices);
            InputHandler::validateVertices(dest, validVertices);
            mst.addEdge(src, dest, weight);
        }
        catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
            --i; // ���������Ч����������������
        }
    }

    mst.constructMST(); // ������С������
    return 0;
}