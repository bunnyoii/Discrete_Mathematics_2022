#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

const int MAX_VERTICES = 5005;  // 定义最大顶点数
const int MAX_EDGES = 200005;   // 定义最大边数

struct Edge {
    int src, dest, weight;       // 边结构，包括源点、目标点和权重
};

// 并查集类用于辅助Kruskal算法
class UnionFind {
public:
    UnionFind(int size) : parent(size + 1) {
        for (int i = 1; i <= size; ++i) parent[i] = i; // 初始化父节点
    }

    int find(int vertex) {
        // 查找根节点，同时进行路径压缩
        return parent[vertex] == vertex ? vertex : (parent[vertex] = find(parent[vertex]));
    }

    void unite(int x, int y) {
        // 合并两个集合
        parent[find(x)] = find(y);
    }

private:
    std::vector<int> parent; // 存储父节点信息
};

// Kruskal最小生成树算法类
class KruskalMST {
public:
    KruskalMST(int vertices) : numVertices(vertices), uf(vertices) {}

    void addEdge(int src, int dest, int weight) {
        // 添加边
        edgeList.push_back({ src, dest, weight });
    }

    void constructMST() {
        // 构建最小生成树
        sortEdges(); // 首先对边进行排序
        int totalWeight = 0; // 记录总权重

        for (const auto& edge : edgeList) {
            // 遍历每条边，检查是否形成环
            if (uf.find(edge.src) != uf.find(edge.dest)) {
                // 如果不形成环，则添加这条边
                std::cout << edge.src << " -- " << edge.dest << " (权重: " << edge.weight << ")\n";
                totalWeight += edge.weight;
                uf.unite(edge.src, edge.dest);
            }
        }

        std::cout << "最小生成树的总权重: " << totalWeight << std::endl;
    }

private:
    int numVertices;
    std::vector<Edge> edgeList;
    UnionFind uf; // 并查集实例

    void sortEdges() {
        // 边按权重排序的函数
        std::sort(edgeList.begin(), edgeList.end(), [](const Edge& a, const Edge& b) {
            return a.weight < b.weight;
            });
    }
};

class InputHandler {
public:
    static int inputNumber(bool isVertices, int numVertices = 0) {
        // 输入处理函数，确保输入有效
        int maxSize = isVertices ? 30 : numVertices * (numVertices - 1) / 2;
        int inputNum;
        while (true) {
            std::cin >> inputNum;
            if (std::cin.fail() || inputNum < 0 || inputNum > maxSize) {
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

    static void validateVertices(int vertex, const std::set<int>& validVertices) {
        // 验证顶点是否有效
        if (validVertices.find(vertex) == validVertices.end()) {
            throw std::invalid_argument("输入的顶点不存在");
        }
    }
};

void menu() {
    // 程序菜单
    std::cout << "··················\n";
    std::cout << "·          最小生成树            ·\n";
    std::cout << "·      Minimum Spanning Tree     ·\n";
    std::cout << "··················\n";
}

int main() {
    menu();
    // 主函数，程序入口
    std::cout << "输入顶点数量[不超过30个]: ";
    int numVertices = InputHandler::inputNumber(true);

    std::set<int> validVertices;
    std::cout << "输入顶点编号[超过顶点数量的会被忽略]:\n";
    for (int i = 0; i < numVertices; ++i) {
        int vertex;
        std::cin >> vertex;
        validVertices.insert(vertex);
    }
    std::cin.ignore(65536, '\n');

    std::cout << "输入边的数量：";
    int numEdges = InputHandler::inputNumber(false, numVertices);

    KruskalMST mst(numVertices);
    std::cout << "输入边（源点 目标点 权重）:\n";
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
            --i; // 如果输入无效，重新输入这条边
        }
    }

    mst.constructMST(); // 构建最小生成树
    return 0;
}