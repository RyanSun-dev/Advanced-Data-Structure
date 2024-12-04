#include <random>
#include "skiplist.hpp"
#include <iostream>

bool coin_toss(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0,1);
    return dis(gen) == 1?true:false;
}

skipList::skipList(){
    head = new Node(0, maxNumberOfLevel,std::chrono::system_clock::now());
    level = 0;
}

void skipList::insert(int data){
    int newLevel = 0;

    // random coin toss
    while(newLevel < maxNumberOfLevel and coin_toss()){
        newLevel++;
    }

    // increase the level of skiplist if more than previous highest level
    if(newLevel > level){
        head->forward.resize(newLevel + 1, nullptr);
        level = newLevel;
    }

    // get the insertion point for the new data
    Node* current = head;
    std::vector<Node*> update(level+1,nullptr);
    for(int i = level; i >= 0;i--){
        while(current->forward[i] and current->forward[i]->data < data){
            current = current->forward[i];
        }
        update[i] = current;
    }

    // insert the new data
    current = current->forward[0];
    if(current == nullptr or current->data != data){
        std::chrono::system_clock::time_point timestamp = std::chrono::system_clock::now();
        Node* newNode = new Node(data,newLevel,timestamp);
        for(int i =0;i <= newLevel;i++){
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }

        //std::cout<<"Element "<<data<<" added successfully!"<<std::endl;
    } else{
        //std::cout<<"Element "<<data<<" already exists!"<<std::endl;
    }

}

int skipList::search(int data){

    Node* current = head;

    // start at the highest level
    for(int i = level; i >= 0; i--){
        while(current->forward[i]){
            if(current->data == data) return data;
            if(current->forward[i]->data > data) break;
            current = current->forward[i];
        }
    }

    return -1;

}

void skipList::display(){
    std::cout<<"SkipList: "<<std::endl;

    for(int i = level;i >= 0; i--){
        Node* current = head->forward[i];

        std::cout<<"Level "<<i<<":   ";
        std::cout<<"Head->";
        while(current != nullptr){
            if(current->forward[i] != nullptr){
                std::cout<<current->data<<"->";
            } else{
                std::cout<<current->data<<"->tail";
            }
            current = current->forward[i];
        }
        std::cout<<std::endl;
    }
}

bool skipList::remove(int data){
    Node* current = head;

    std::vector<Node*> update(level+1,nullptr);
    for(int i = level; i >= 0; i--){
        while(current->forward[i] and current->forward[i]->data < data){
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];
    if(current->data == data){
        for(int i = 0;i <= level; i++){
            if(update[i]->forward[i] != current) break;
            update[i]->forward[i] = current->forward[i];
        }
        delete current;
        //std::cout<<"Element "<<data<<" deleted successfully!!"<<std::endl;

        while(level > 0 and head->forward[level] == nullptr){
            level--;
        }
        return true;
    }

    return false;
}
