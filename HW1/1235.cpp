#include <iostream>
using namespace std;

template <class Type>
class priorityQueue {
private:
    int currentSize;
    Type *array;
    int maxSize;

    void doubleSpace() {
        Type *tmp = array;
        maxSize *= 2;
        array = new Type[maxSize];
        for (int i = 0; i <= currentSize; ++i)
            array[i] = tmp[i];
        delete[]tmp;
    }

    void buildHeap() {
        for (int i = currentSize / 2; i > 0; i--)
            percolateDown(i);
    }

    void percolateDown(int hole) {
        int child;
        Type tmp = array[hole];

        for (; hole * 2 <= currentSize; hole = child) {
            child = hole * 2;
            if (child != currentSize && array[child + 1] < array[child])
                child++;
            if (array[child] < tmp)array[hole] = array[child];
            else break;
        }
        array[hole] = tmp;
    }

public:
    priorityQueue(int capacity = 1000) {
        array = new Type[capacity];
        maxSize = capacity;
        currentSize = 0;
    }

    priorityQueue(const Type data[], int size) : maxSize(size + 10), currentSize(size) {
        array = new Type[maxSize];
        for (int i = 0; i < size; ++i) array[i + 1] = data[i];
        buildHeap();

    }

    ~priorityQueue() { delete[]array; }

    bool isEmpty() const { return currentSize == 0; }

    void enQueue(const Type &x) {
        if (currentSize == maxSize - 1)doubleSpace();

        int hole = ++currentSize;
        for (; hole > 1 && x < array[hole / 2]; hole /= 2)
            array[hole] = array[hole / 2];
        array[hole] = x;

    }

    Type deQueue() {
        Type minItem;
        minItem = array[1];
        array[1] = array[currentSize--];
        percolateDown(1);
        return minItem;
    }

    Type getHead() const { return array[1]; }


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

    struct dis {
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
        int u = x - 1, v = y - 1;
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

    void printPath(int start, int end, int prev[]) const {
        if (start == end) {
            cout << verList[start].ver;
            return;
        }
        printPath(start, prev[end], prev);
        cout << " " << verList[end].ver;
    }

    void dijkstra(TypeOfVer start, TypeOfVer end, TypeOfEdge noEdge) const {
        dis *distance = new dis[Vers];

        int *d;
        d = new int[Vers];

        int *prev = new int[Vers];
        bool *known = new bool[Vers];

        int u = 0, sNo, i, j;
        edgeNode *p;
        TypeOfEdge min;
        for (i = 0; i < Vers; ++i) {
            known[i] = false;
            distance[i].no = i;
            distance[i].dist = noEdge;
            d[i] = 0;
        }

        for (sNo = 0; sNo < Vers; ++sNo) {
            if (verList[sNo].ver == start)
                break;
        }

        if (sNo == Vers) {
            cout << "No start" << endl;
            return;
        }

        distance[sNo].dist = 0;
        prev[sNo] = sNo;

        priorityQueue<dis> kueue;
        for (j = 0; j < Vers; ++j) {
            kueue.enQueue(distance[j]);
        }

        dis de;

        while (!kueue.isEmpty()) {
            de = kueue.deQueue();
            if (known[de.no])
                continue;

            min = de.dist;
            u = de.no;

//            cout<<countVer(prev,u)<<endl;

            known[u] = true;
            for (p = verList[u].head; p != NULL; p = p->next) {
                if (!known[p->endT] && (distance[p->endT].dist > min + p->weight
                                        || (distance[p->endT].dist == min + p->weight && d[p->endT] > d[u] + 1))) {
                    distance[p->endT].dist = min + p->weight;
                    prev[p->endT] = u;
                    d[p->endT] = d[u] + 1;
                    kueue.enQueue(distance[p->endT]);
                }
            }
        }
//        cout << start << " to " << verList[end].ver << ':' << endl;
        cout << distance[end].dist << endl;
        printPath(sNo, end, prev);
    }

    int input(int m) {
        int a, b, p, max = -1;
        for (int i = 0; i < m; ++i) {
            cin >> a >> b >> p;
            insertT(a, b, p);
            if (p > max)
                max = p;
        }
        return max + 10;
    }


};

int main(){
    int n,m,start,end,max;
    cin>>n>>m>>start>>end;
    adjListGraph<int,int> graph1(n);
    max = graph1.input(m);
    graph1.dijkstra(start,end-1,100000);
}










