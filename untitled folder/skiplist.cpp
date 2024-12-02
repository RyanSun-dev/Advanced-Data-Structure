#include <random>
#include "skiplist.hpp"
#include <iostream>

skipList::skipList(){
    head = new Node(0, maxNumberOfLevel);
    level = 0;
}

void skipList::insert(int data){
    int newLevel = 0;

    // random coin toss
    while(newLevel < maxNumberOfLevel and rand()%2 ==1){
        newLevel++;
    }

    // increase the level of skiplist if more than previous highest level
    if(newLevel > level){
        head->next.resize(newLevel + 1, nullptr);
        level = newLevel;
    }

    // get the insertion point for the new data
    Node* current = head;
    std::vector<Node*> update(level+1,nullptr);
    for(int i = level; i >= 0;i--){
        while(current->next[i] and current->next[i]->data < data){
            current = current->next[i];
        }
        update[i] = current;
    }

    // insert the new data
    current = current->next[0];
    if(current == nullptr or current->data != data){
        Node* newNode = new Node(data,newLevel);
        for(int i =0;i <= newLevel;i++){
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }

        std::cout<<"Element "<<data<<" added successfully!"<<std::endl;
    } else{
        std::cout<<"Element "<<data<<" already exists!"<<std::endl;
    }

}

bool skipList::search(int data){

    Node* current = head;

    // start at the highest level
    for(int i = level; i >= 0; i--){
        while(current->next[i]){
            if(current->data == data) return true;
            if(current->next[i]->data > data) break;
            current = current->next[i];
        }
    }

    return false;

}

void skipList::display(){
    std::cout<<"SkipList: "<<std::endl;

    for(int i = level;i >= 0; i--){
        Node* current = head->next[i];

        std::cout<<"Level "<<i<<":   ";
        std::cout<<"Head->";
        while(current != nullptr){
            if(current->next[i] != nullptr){
                std::cout<<current->data<<"->";
            } else{
                std::cout<<current->data<<"->tail";
            }
            current = current->next[i];
        }
        std::cout<<std::endl;
    }
}

void skipList::remove(int data){
    Node* current = head;

    std::vector<Node*> update(level+1,nullptr);
    for(int i = level; i >= 0; i--){
        while(current->next[i] and current->next[i]->data < data){
            current = current->next[i];
        }
        update[i] = current;
    }

    current = current->next[0];
    if(current->data == data){
        for(int i = 0;i <= level; i++){
            if(update[i]->next[i] != current) break;
            update[i]->next[i] = current->next[i];
        }
        delete current;
        std::cout<<"Element "<<data<<" deleted successfully!!"<<std::endl;

        while(level > 0 and head->next[level] == nullptr){
            level--;
        }
    }  
}
