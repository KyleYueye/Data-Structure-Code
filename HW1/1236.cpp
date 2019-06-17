#include <iostream>
using namespace std;


template <class elemType>
class queue {
public:
    virtual bool isEmpty() = 0;

    virtual void enQueue(const elemType &x) = 0;

    virtual elemType deQueue() = 0;

    virtual elemType getHead() = 0;

    virtual ~queue() {}
};





template <class elemType>
class seqQueue:public queue<elemType> {
private:
    elemType *elem;
    int maxSize;
    int head,rear;

    void doubleSpace() {
        elemType *tmp = elem;
        elem = new elemType[2 * maxSize];
        for (int i = 1; i < maxSize; i++)
            elem[i] = tmp[(i + head) % maxSize];
        head = 0;
        rear = maxSize - 1;
        maxSize *= 2;
        delete[]tmp;
    }

public:
    seqQueue(int initSize = 10) {
        elem = new elemType[initSize];
        maxSize = initSize;
        head = rear = 0;
    }

    ~seqQueue() {
        delete[]elem;
    }

    bool isEmpty() {
        return rear == head;
    }

    void enQueue(const elemType &x) {
        if ((rear + 1) % maxSize == head)
            doubleSpace();
        rear = (rear + 1) % maxSize;
        elem[rear] = x;
    }

    elemType deQueue() {
        head = (head + 1) % maxSize;
        return elem[head];
    }

    elemType getHead() {
        return elem[(head + 1) % maxSize];
    }
};


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

    struct dis{
        int no;
        TypeOfEdge dist;
        bool operator<(const dis &rp) const { return dist < rp.dist; }
        bool operator>(const dis &rp) const { return dist > rp.dist; }
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
        for (int i = 0; i < Vers; ++i)
            verList[i].ver = i + 1;
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

    void printPath(int start, int end, int *prev) const {
        if (start == end) {
            cout << verList[start].ver;
            return;
        }
        printPath(start, prev[end], prev);
        cout << " " << verList[end].ver;
    }

    void weightedNegative(TypeOfVer start, TypeOfVer end, TypeOfEdge noEdge) const {
        seqQueue<TypeOfVer> q;
        dis *distance = new dis[Vers];
        int u, sNo;
        edgeNode *p;

        for (int i = 0; i < Vers; ++i) {
            distance[i].no = i;
            distance[i].dist = noEdge;
        }

        for (sNo = 0; sNo < Vers; ++sNo) {
            if (verList[sNo].ver == start)
                break;
        }

        distance[sNo].dist = 0;

        q.enQueue(sNo);
        while(!q.isEmpty()){
            u = q.deQueue();

            for (p = verList[u].head; p != NULL; p = p->next) {
                if (distance[p->endT].dist > distance[u].dist + p->weight) {
                    distance[p->endT].dist = distance[u].dist + p->weight;
                    q.enQueue(distance[p->endT].no);
                }
            }
        }

        cout << distance[end].dist << endl;
    }

    void input(int m) {
        int a, b, p, max = -1;
        for (int i = 0; i < m; ++i) {
            cin >> a >> b >> p;
            insertT(a, b, p);
            if (p > max)
                max = p;
        }
    }


};

int main(){
    int n,m,start,end,max;
    cin>>n>>m>>start>>end;
    adjListGraph<int,int> graph1(n);
    graph1.input(m);
    graph1.weightedNegative(start,end-1,1000);
}











