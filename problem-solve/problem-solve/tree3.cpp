#include <fstream>
#include <vector>
using namespace std;

ifstream finp("tree3.inp");
ofstream fout("tree3.out");

typedef struct node {
    int parent;
    int weight;
    int max_weight;
};

vector<node> Node;
vector<vector<int>> graph;

void dfs(int root, int sum) {

    for (int i = 0; i < graph[root].size(); i++) {
        sum += Node[graph[root][i]].weight;
        dfs(graph[root][i], sum);

        if (graph[graph[root][i]].size() == 0) {
            Node[graph[root][i]].max_weight = sum;
        }
        if (Node[graph[root][i]].max_weight > Node[root].max_weight) {
            Node[root].max_weight = Node[graph[root][i]].max_weight;
        }
        sum -= Node[graph[root][i]].weight;
    }

}

void solve(int nodeNum) {

    Node.push_back({ 0,0,0 });
    int parent, weight;

    for (int i = 1; i < nodeNum; i++) {
        finp >> parent >> weight;
        Node.push_back({ parent, weight });
        graph[parent].push_back(i);
    }

}

int main() {

    int testcase, nodeNum;
    finp >> testcase;

   while(testcase--) {

        int result = 0;

        finp >> nodeNum;
        graph.resize(nodeNum);
        solve(nodeNum);
        
        dfs(0, 0);

        for (int i = 1; i < nodeNum; i++) {
            result += Node[Node[i].parent].max_weight - Node[i].max_weight;
        }

        fout << result << "\n";

        Node.clear();
        graph.clear();
    }

    finp.close();
    fout.close();
    return 0;
}