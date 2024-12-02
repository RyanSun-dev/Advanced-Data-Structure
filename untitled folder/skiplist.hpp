#include <vector>

const int maxNumberOfLevel = 16;

class Node{
public:
    int data;
    std::vector<Node*> next;
    Node(int data, int level) : data(data), next(level +1, nullptr) {};
};

class skipList{
private:
    Node* head;
    int level;

public:
    skipList();

    void insert(int data);
    void remove(int data);
    bool search(int data);
    void display();
};