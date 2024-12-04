#include <vector>
#include <chrono>
#include <optional>

const int maxNumberOfLevel = 16;

class Node{
public:
    int data;
    std::chrono::system_clock::time_point timestamp;
    std::vector<Node*> forward;
    Node(int data, int level, std::chrono::system_clock::time_point timestamp) : data(data), forward(level +1, nullptr),timestamp(timestamp) {};
};

class skipList{
private:
    Node* head;
    int level;

public:
    skipList();

    void insert(int data);
    bool remove(int data);
    int search(int data);
    void display();
};