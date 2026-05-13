#include <iostream>
#include <queue>
using namespace std;

class node {
public:
    int data;
    node *left, *right;

    node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Insert nodes in level order (like your earlier code)
node* insert(node* root, int data) {
    if (!root) return new node(data);

    queue<node*> q;
    q.push(root);

    while (!q.empty()) {
        node* temp = q.front();
        q.pop();

        if (temp->left == NULL) {
            temp->left = new node(data);
            return root;
        } else {
            q.push(temp->left);
        }

        if (temp->right == NULL) {
            temp->right = new node(data);
            return root;
        } else {
            q.push(temp->right);
        }
    }

    return root;
}

// BFS traversal
void bfs(node* root) {
    if (!root) return;

    queue<node*> q;
    q.push(root);

    while (!q.empty()) {
        node* curr = q.front();
        q.pop();

        cout << curr->data << " ";

        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

int main() {
    node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);

    cout << "BFS Traversal: ";
    bfs(root);

    cout << endl;
    return 0;
}