#include <cstdlib>
#include <vector>
using namespace std;

class Node {
public:
    int key;
    char value;
    Node *leftChild = nullptr;
    Node *rightChild = nullptr;

    Node() = default;

    Node(int _key, char _value, Node *_leftChild, Node *_rightChild) :
            key(_key), value(_value), leftChild(_leftChild), rightChild(_rightChild) {}

    Node *BST_SearchNode(Node *current, int target) {
        if (current == nullptr) {// 원하는 Node가 없을 시 예외처리
            cout << "Does not exist" << endl;
            return nullptr;
        }

        if (current->key == target)
            return current;
        else if (current->key > target)
            return BST_SearchNode(current->leftChild, target);
        else if (current->key < target)
            return BST_SearchNode(current->rightChild, target);

    }

    void BST_InOrder(Node *current, vector<char> &values) {
        if (current == nullptr)
            return;

        //중위순회
        BST_InOrder(current->leftChild, values);
        values.push_back(current->value);
        BST_InOrder(current->rightChild, values);
    }

    void BST_InsertNode(Node *current, Node *new_node) {
        if (new_node->key <= current->key) {
            if (current->leftChild == nullptr) {
                current->leftChild = new_node;
                return;
            } else
                BST_InsertNode(current->leftChild, new_node);
        } else if (new_node->key > current->key) {
            if (current->rightChild == nullptr) {
                current->rightChild = new_node;
                return;
            } else
                BST_InsertNode(current->rightChild, new_node);
        }
    }

    Node *BST_SearchMinNode(Node *current) {
        if (current == nullptr)
            return nullptr;

        if (current->leftChild == nullptr)
            return current;
        else
            return BST_SearchMinNode(current->leftChild);
    }

    Node *BST_RemoveNode(Node *current, Node *parent, int target) {

        if (current == nullptr) //Tree가 비었거나 찾는 노드가 없는 경우.
            return nullptr;

        Node *removedNode = nullptr;

        /* 삭제할 노드 탐색하기*/
        if (current->key > target) {
            removedNode = BST_RemoveNode(current->leftChild, current, target);
        } else if (current->key < target) {
            removedNode = BST_RemoveNode(current->rightChild, current, target);
        } else if (current->key == target) { // 삭제할 노드 찾음
            removedNode = current; // 삭제된 노드 리턴할거라 삭제 작업 전 캐싱

            // 1. 삭제하려는 노드의 자식 서브트리가 0 개 일때 (=단말노드)
            if (current->leftChild == nullptr && current->rightChild == nullptr) {
                if (parent->leftChild == current)
                    parent->leftChild = nullptr;
                if (parent->rightChild == current)
                    parent->rightChild = nullptr;
            }
                // 2. 삭제하려는 노드의 자식 서브트리가 1 개 일때
            else if (current->leftChild == nullptr || current->rightChild == nullptr) {
                Node *temp = nullptr;
                if (current->leftChild != nullptr)
                    temp = current->leftChild;
                else
                    temp = current->rightChild;

                if (parent->leftChild == current)
                    parent->leftChild = temp;
                else
                    parent->rightChild = temp;
            }
                // 3. 삭제하려는 노드의 자식 서브트리가 2 개 일 때
            else if (current->leftChild != nullptr && current->rightChild != nullptr) {
                Node *minNode_Of_BiggerNodes = BST_SearchMinNode(current->rightChild);
                minNode_Of_BiggerNodes = BST_RemoveNode(current, nullptr,
                                                        minNode_Of_BiggerNodes->key);
                current->key = minNode_Of_BiggerNodes->key;
                current->value = minNode_Of_BiggerNodes->value;
            }
        }

        return removedNode;
    }
};

    void initializeBST() {
        int select = 0;
        bool firstInput = true;
        int tmpKey;
        char tmpValue;
        Node *tree = nullptr;
        vector<char> treeValues;

            while (true) {
                cout << "1.입력 2.탐색 3.삭제 4.보기 5.종료" << endl;
                cin >> select;

                if (select == 1) {//입력
                    cin >> tmpKey >> tmpValue;
                    if (firstInput) {
                        tree = new Node(tmpKey, tmpValue, nullptr, nullptr);
                        firstInput = false;
                    } else {
                        tree->BST_InsertNode(tree, new Node(tmpKey, tmpValue, nullptr, nullptr));
                    }

                } else if (select == 2) {//탐색
                    cin >> tmpKey;
                    Node *tmp = tree->BST_SearchNode(tree, tmpKey);
                    cout << tmp->value << endl;
                } else if (select == 3) {//삭제
                    cin >> tmpKey;
                    tree->BST_RemoveNode(tree, nullptr, tmpKey);
                } else if (select == 4) {//보기
                    tree->BST_InOrder(tree, treeValues);
                    cout << "Value : ";
                    for (auto loop: treeValues) {
                        cout << loop << " ";
                    }
                    cout << endl;

                    treeValues.clear();
                } else if (select == 5) {// 종료
                    cout << "종료되었습니다." << endl;
                    exit(0);
                }
            }
        };
