#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

class node {
public:
    int data;
    node *left, *right;
};

node* insert(node* root, int data) {
    if (!root) {
        root = new node{data, NULL, NULL};
        return root;
    }

    vector<node*> q;
    q.push_back(root);

    while (!q.empty()) {
        node* temp = q.front();
        q.erase(q.begin());

        if (!temp->left) {
            temp->left = new node{data, NULL, NULL};
            return root;
        } else q.push_back(temp->left);

        if (!temp->right) {
            temp->right = new node{data, NULL, NULL};
            return root;
        } else q.push_back(temp->right);
    }
    return root;
}

void parallelBFS(node* root) {
    if (!root) return;

    vector<node*> currentLevel;
    currentLevel.push_back(root);

    while (!currentLevel.empty()) {
        vector<node*> nextLevel;

        #pragma omp parallel for
        for (int i = 0; i < currentLevel.size(); i++) {
            node* curr = currentLevel[i];

            #pragma omp critical
            cout << curr->data << " ";

            if (curr->left) {
                #pragma omp critical
                nextLevel.push_back(curr->left);
            }
            if (curr->right) {
                #pragma omp critical
                nextLevel.push_back(curr->right);
            }
        }

        currentLevel = nextLevel;
    }
}

int main() {
    node* root = NULL;
    int data;
    char ans;

    do {
        cout << "\nEnter data: ";
        cin >> data;
        root = insert(root, data);

        cout << "Add more? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    cout << "\nParallel BFS Traversal:\n";
    parallelBFS(root);

    return 0;
}