#include "lab2_drones_manager.hpp"
#include <iostream>

using namespace std;

DronesManager::DronesManager() {
    first=last=NULL;
    size = 0;
}

DronesManager::~DronesManager() {
    DroneRecord* cur = first;
    while(cur){
        cur = cur->next;
        first = cur;
    }
    delete first;
    first = last = NULL;
    size = 0;
}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
    bool is_equal = lhs.droneID == rhs.droneID;
    return is_equal;
}

unsigned int DronesManager::get_size() const {
    return size;
}

bool DronesManager::empty() const {
    if(size == 0){
        return true;
    }else return false;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
    if(size == 0)return DroneRecord(0);
    else if(index == 0)return *first;
    else if(index == size - 1)return *last;
    else{
        DroneRecord* cur = first;
        for(int i = 0; i < size; i++){
            if(i == index){
                return *cur;
            }
            cur = cur->next;
        }
    }
    return *last;
}

unsigned int DronesManager::search(DroneRecord value) const {
    if(size == 0)return 0;
    else{
        DroneRecord* cur = first;
        for(int i = 0; i < size; i++){
            if(*cur == value)return i;
            cur = cur->next;
        }
    }
    return size;
}

void DronesManager::print() const {
    if(size == 0) cout<<"This list is empty"<<endl;
    else{
        cout<<"Commencing printing of DroneRecords:"<<endl;
        cout<<"First-->";
        DroneRecord* cur = first;
        while(cur->next){
            cout<<"["<<"DroneID:"<<cur->droneID<<"]-->";
            cur = cur->next;
        }
        cout<<"["<<"DroneID:"<<cur->droneID<<"]";
        cout<<"-->Last"<<endl;
    }
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
    if(index > size-1 || index < 0)return false;
    else if(index == 0){
        first->prev = &value;
        value.prev = NULL;
        value.next = first;
        first = &value;
        size++;
        return true;
    }
    else if(index == size - 1){
        last->next = &value;
        value.prev = last;
        value.next = NULL;
        last = &value;
        size++;
        return true;
    }
    else{
        DroneRecord* cur = first;
        for(int i = 0; i < index + 1; i++){
            if(i == index){
                cur->prev->next = &value;
                value.prev = cur->prev;
                value.next = cur;
                size++;
            }
            cur = cur->next;
        }
        return true;
    }
}

bool DronesManager::insert_front(DroneRecord value) {
    if(value == NULL)return false;
    else if(size == 0){
        first = &value;
        last = &value;
        size++;
        return true;
    }
    else{
        first->prev = &value;
        value.prev = NULL;
        value.next = first;
        first = &value;
        size++;
        return true;
    }
}

bool DronesManager::insert_back(DroneRecord value) {
    if(value == NULL) return false;
    else if(size == 0){
        first = &value;
        last = &value;
        size++;
        return true;
    }
    else{
        last->next = &value;
        value.prev = last;
        value.next = NULL;
        last = &value;
        size++;
        return true;
    }
}

bool DronesManager::remove(unsigned int index) {
    if(size == 0)return false;
    else if(index == 0){
        last = last->next;
        last->prev = NULL;
        size--;
        return true;
    }
    else if (index == size-1){
        last = last->prev;
        last->next = NULL;
        size--;
        return true;
    }
    else{
        DroneRecord* cur = first;
        DroneRecord* prev = NULL;
        DroneRecord* next = NULL;
        for(int i = 0; i < index + 1; i++){
            if(i == index){
                prev = cur->prev;
                next = cur->next;
                prev->next = next;
                next->prev = prev;
                delete cur;
                size--;
                
            }else cur = cur->next;
        }
        return true;
    }
}

bool DronesManager::remove_front() {
    if(size == 0) return false;
    else{
        first = first->next;
        size--;
        return true;
    }
}

bool DronesManager::remove_back() {
    if(size == 0)return false;
    else{
        last = last->prev;
        last->next = NULL;
        size--;
        return true;
    }
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
    if(size == 0 || value == NULL)return false;
    if(index == 0){
        first = first->next;
        first->prev = &value;
        value.prev = NULL;
        value.next = first->next;
        first = &value;
        return true;
    }
    else if(index == size - 1){
        last = last->prev;
        last->next = &value;
        value.prev = last;
        value.next = NULL;
        last = &value;
        return true;
    }
    else{
        DroneRecord* cur = first;
        for(int i = 0; i < index + 1; i++){
            if(i == index){
                DroneRecord* temp = NULL;
                temp = cur->prev;
                temp->next = &value;
                value.next = cur->next;
                value.prev = temp;
                cur->next->prev = &value;
                return true;
            }
            cur = cur->next;
        }
        return true;
    }
}

bool DronesManager::reverse_list() {
    if(empty()) return false;
    if(size == 1) return true;
    
    DroneRecord* temp = first;
    first = last;
    last = temp;
    DroneRecord* cur = first;
    
    while(cur){
        temp = cur->next;
        cur->next = cur->prev;
        cur->prev = temp;
        cur = cur->next;
    }
    return true;
}

