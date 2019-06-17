#ifndef LIST_GRAPH_H
#define LIST_GRAPH_H
#include <iostream>

using namespace std;

template<class TypeOfVer,class TypeOfEdge>
class graph {
public:
    virtual void insertT(TypeOfVer x, TypeOfVer y, TypeOfEdge w) = 0;

    virtual void removeT(TypeOfVer x, TypeOfVer y) = 0;

    virtual bool exist(TypeOfVer x, TypeOfVer y) const = 0;
};

template<class TypeOfVer,class TypeOfEdge>
class adjListGraph:public graph<TypeOfVer,TypeOfEdge> {
private:
    int Vers, Edges;

    struct edgeNode {
        int endT;
        TypeOfEdge weight;
        edgeNode *next;

        edgeNode(int e, TypeOfEdge w, edgeNode *n = NULL) {
            endT = e;
            weight = w;
            next = n;
        }
    };

    struct verNode {
        TypeOfVer ver;
        edgeNode *head;

        verNode(edgeNode *h = NULL) { head = h; }
    };

    verNode *verList;

    int findT(TypeOfVer v) const {
        for (int i = 0; i < Vers; ++i)
            if (verList[i].ver == v)
                return i;
    }

public:
    int numOfVer() const { return Vers; }

    int numOfEdge() const { return Edges; }

    adjListGraph(int vSize) {
        //有向
        Vers = vSize;
        Edges = 0;

        verList = new verNode[vSize];
        for (int i = 0; i < Vers; ++i) verList[i].ver = i + 1;
    }

    void insertT(TypeOfVer x, TypeOfVer y, TypeOfEdge w) {
        int u = findT(x), v = findT(y);
        verList[u].head = new edgeNode(v, w, verList[u].head);
        ++Edges;
    }

    void removeT(TypeOfVer x, TypeOfVer y) {
        int u = findT(x), v = findT(y);
        edgeNode *p = verList[u].head, *q;

        if (p == NULL) {
            verList[u].head = p->next;
            delete p;
            --Edges;
            return;
        }

        while (p->next != NULL && p->next->endT != v) p = p->next;
        if (p->next != NULL) {
            q = p->next;
            p->next = q->next;
            delete q;
            --Edges;
        }
    }

    bool exist(TypeOfVer x, TypeOfVer y) const {
        int u = findT(x), v = findT(y);
        edgeNode *p = verList[u].head;

        while (p != NULL && p->endT != v) p = p->next;
        if (p == NULL) return false;
        else return true;
    }

    ~adjListGraph() {
        int i;
        edgeNode *p;

        for (i = 0; i < Vers; ++i)
            while ((p = verList[i].head) != NULL) {
                verList[i].head = p->next;
                delete p;
            }

        delete[]verList;
    }

    void dfs(int sta, int len) const {
        bool *visited = new bool[Vers];

        for (int i = 0; i < Vers; ++i)
            visited[i] = false;
        int total[1] = {0};
        dfs(sta - 1, visited, -1, len, total);
        cout << total[0] << endl;
    }

    void dfs(int start, bool visited[], int now, int len, int total[]) const {
        edgeNode *p = verList[start].head;
        visited[start] = true;
        now++;
        if (now >= len) {
            total[0]++;
            return;
        }

        while (p != NULL) {
            bool *vvsit = new bool[Vers];
            for (int j = 0; j < Vers; ++j)
                vvsit[j] = visited[j];
            if (!visited[p->endT])
                dfs(p->endT, vvsit, now, len, total);
            p = p->next;
        }
    }
};



#endif //LIST_GRAPH_H
