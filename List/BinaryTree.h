template <class Type>
class BinaryTree {
private:
    struct Node {
        Node *left, *right;
        char data;

        Node() : left(NULL), right(NULL) {}
        Node(char item, Node *L = NULL, Node *R = NULL) : data(item), left(L), right(R) {}

        ~Node() {}
    };

    Node *root;

public:
    BinaryTree() : root(NULL) {}

    BinaryTree(const Type &value) { root = new Node(value); }

    BinaryTree(const Node *p) { root = p; }

    ~BinaryTree() { clear(); }

    Type getRoot() const { return root->data; }

    Type getLeft() const { return root->left->data; }

    Type getRight() const { return root->right->data; }

    void makeTree(const Type &x, BinaryTree &lt, BinaryTree &rt) {
        root = new Node(x, lt.root, rt.root);
        lt.root = NULL;
        rt.root = NULL;
    }

    void delLeft() {
        BinaryTree tmp = root->left;
        root->left = NULL;
        tmp.clear();
    }

    void delRight() {
        BinaryTree tmp = root->right;
        root->right = NULL;
        tmp.clear();
    }

    bool isEmpty() const { return root == NULL; }

    void clear() {
        if (root != NULL)clear(root);
        root = NULL;
    }

    int size() const { return size(root); }

    int height() const { return height(root); }

    void preOrder()const{
        if(root!=NULL){
            cout<<"\n";
            preOrder(root);
        }
    }

    void postOrder()const{
        if(root!=NULL){
            cout<<"\npost:";
            postOrder(root);
        }
    }

    void midOrder()const{
        if(root!=NULL){
            cout<<"\n";
            midOrder(root);
        }
    }
    void levelB()const{
        cout<<"\nlevelB:";
        linkQueue<Node *> que;
        Node *P;
        P = root;
        cout<<P->data<<' ';
        if (P->leftChi) que.enQueue(P->leftChi);
        if (P->rightSib) que.enQueue(P->rightSib);

        while(!que.isEmpty()) {
            P = que.deQueue();
            cout<<P->data<<' ';
            if (P->leftChi) que.enQueue(P->leftChi);
            if (P->rightSib) que.enQueue(P->rightSib);
        }
    }

    void levelO()const{
        cout<<"\n";
        linkQueue<Node *> que;
        Node *P,*Q;
        P = root;
        cout<<P->data<<' ';
        if (P->leftChi) que.enQueue(P->leftChi);
        Q = P;
        while (Q->rightSib){
            Q = Q->rightSib;
            if(Q->leftChi)que.enQueue(Q->leftChi);
            cout<<Q->data<<' ';
        }

        while(!que.isEmpty()) {
            P = que.deQueue();
            cout<<P->data<<' ';
            if (P->leftChi) que.enQueue(P->leftChi);
            Q = P;
            while (Q->rightSib){
                Q = Q->rightSib;
                if(Q->leftChi)que.enQueue(Q->leftChi);
                cout<<Q->data<<' ';
            }

        }
    }

    void createTree() {
        int num;
        cin >> num;
        int len = getlen(num);
        list = new Node[num + 1];


        int check[num+1];
        for (int l = 0; l < num+1; ++l)
            check[l]=-1;
        int p, q, v;
        for (int i = 1; i <= num; ++i) {
            cin >> p >>q >> v;
            check[p]=p;check[q]=q;
            list[i].data = v;
            if (p == 0) {
                list[i].leftChi = NULL;
            } else {
                list[i].leftChi = &list[p];
            }
            if (q == 0) {
                list[i].rightSib = NULL;
            } else {
                list[i].rightSib = &list[q];
            }
        }

        for (int c = 0; c < num+1; ++c) {
            if(check[c]==-1){
                root = &list[c];
                break;
            }
        }

        preOrder();
        midOrder();
        levelO();

        root = NULL;
        delete [] list;

    }


private:
    int height(Node *t) const {
        if (t == NULL)return 0;
        else {
            int lt = height(t->left), rt = height(t->right);
            return 1 + ((lt > rt) ? lt : rt);
        }
    }

    void clear(Node *t) {
        if (t->left != NULL)clear(t->left);
        if (t->right != NULL)clear(t->right);
        delete t;
    }

    int size(Node *t) const {
        if (t == NULL)return 0;
        return 1 + size(t->left) + size(t->right);
    }
    void preOrder(Node*t)const{
        if(t!=NULL){
            cout<<t->data<<' ';
            preOrder(t->leftChi);
            preOrder(t->rightSib);
        }
    }

    void postOrder(Node*t)const{
        if(t!=NULL){
            postOrder(t->leftChi);
            postOrder(t->rightSib);
            cout<<t->data<<' ';
        }
    }

    void midOrder(Node*t)const{
        if(t!=NULL){
            midOrder(t->leftChi);
            cout<<t->data<<' ';
            midOrder(t->rightSib);
        }
    }


};