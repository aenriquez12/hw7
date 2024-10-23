#include "lfgqueue.h"
#include "player.h"



LFGQueue::LFGQueue(){
    for (int i = 0; i < 3; ++i){
    heads[i];
    tails[i];
    counts[i]=0;
    }
}

int LFGQueue::size(){
    return counts[0] + counts[1] + counts[2];
}

void LFGQueue::push_player(Player* plyr){
     int role = plyr->role();
    
    Node* newNode = new Node();
    newNode->p = plyr;
    newNode->next = nullptr;
    
    if (tails[role] == nullptr) {  
        heads[role] = newNode;
    } else {
        tails[role]->next = newNode;
    }
    tails[role] = newNode;
    ++counts[role];  
}

Player* LFGQueue::front_player(Player::Role r) {
    if (heads[r] != nullptr) {
        return heads[r]->p;
    }
    return nullptr;
}


void LFGQueue::pop_player(Player::Role r){
    if (heads[r] == nullptr) {
        return;  
    }
    
    Node* temp = heads[r];
    heads[r] = heads[r]->next;
    
    if (heads[r] == nullptr) {
        tails[r] = nullptr; 
    }
    
    delete temp;
    --counts[r]; 
}

bool LFGQueue::front_group(Player** group){
     if (heads[Player::Defender] != nullptr && 
        heads[Player::Hunter] != nullptr &&
        heads[Player::Bard] != nullptr) {
        
        group[0] = heads[Player::Defender]->p;
        group[1] = heads[Player::Hunter]->p;
        group[2] = heads[Player::Bard]->p;
        
        return true;
    }
    return false;
}

void LFGQueue::pop_group(){
    if (heads[Player::Defender] == nullptr || 
        heads[Player::Hunter] == nullptr || 
        heads[Player::Bard] == nullptr) {
        return;  
    }
    
    pop_player(Player::Defender);
    pop_player(Player::Hunter);
    pop_player(Player::Bard);

}

