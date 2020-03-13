#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "lab2_drones_manager.hpp"

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;
#include <vector>
#include <stdlib.h>
#include <time.h>

class DronesManagerTest {
public:
	// PURPOSE: New empty list is valid
	bool test1() {
		DronesManager manager;
		ASSERT_TRUE(manager.get_size() == 0)
		ASSERT_TRUE(manager.empty() == true)
		ASSERT_TRUE(manager.first == NULL)
		ASSERT_TRUE(manager.last == NULL)
	    return true;
	}
	
	// PURPOSE: insert_front() and insert_back() on zero-element list
	bool test2() {
		DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_back(DronesManager::DroneRecord(100));
	    
		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1)
		ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last)
		ASSERT_TRUE(manager2.first != NULL && manager2.first == manager2.last)
		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)
		ASSERT_TRUE(manager2.first->prev == NULL && manager2.last->next == NULL)
		ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))		
	    return true;
	}
	
	// TODO: Implement all of the test cases below
	
	// PURPOSE: select() and search() work properly
	bool test3() {
        
        //Init.
        DronesManager manager1, manager2;
        manager1.insert_back(10);
        manager1.insert_back(20);
        manager1.insert_back(30);
        manager1.insert_back(40);
        manager1.insert_back(50);
        vector<int> values = {10,20,30,40,50};
        
        //Select and search base case testing
        for(int i = 0; i < manager1.size; i++){
            ASSERT_TRUE(manager1.select(i) == values[i])
        }
        
        for(int i = 0; i < values.size(); i++){
            ASSERT_TRUE(manager1.search(values[i]) == i);
        }
        
        //Edge Cases
        ASSERT_TRUE(manager1.select(6) == 50)
        ASSERT_TRUE(manager2.select(4) == DronesManager::DroneRecord(0))
        return true;
    }
	
	// PURPOSE: remove_front() and remove_back() on one-element list
	bool test4() {
        
        //Init.
        DronesManager manager1, manager2;
        manager1.insert_back(10);
        manager1.insert_back(20);
        manager1.insert_back(30);
        manager1.insert_back(40);
        manager1.insert_back(50);
        manager2.insert_back(30);
        
        //Multiple element remove_front and remove_back testing
        ASSERT_TRUE(manager1.remove_front())
        ASSERT_TRUE(*manager1.first == 20);
        ASSERT_TRUE(manager1.remove_back())
        ASSERT_TRUE(*manager1.last == 40)
        ASSERT_TRUE(manager1.size == 3)
        
        //One element list removal
        ASSERT_TRUE(manager2.remove_front())
        ASSERT_TRUE(manager2.size == 0)
        ASSERT_TRUE(!manager2.remove_back())
        
        return true;
	}
	
	// PURPOSE: replace() and reverse_list() work properly
	bool test5() {
        
        //Init.
        DronesManager manager1;
        manager1.insert_back(10);
        manager1.insert_back(20);
        manager1.insert_back(30);
        manager1.insert_back(40);
        manager1.insert_back(50);
        manager1.insert_back(30);
        manager1.insert_back(40);
        manager1.insert_back(50);
        manager1.insert_back(30);

        //Base case and corner case testing for replace method
        ASSERT_TRUE(manager1.replace(2, 10))
        ASSERT_TRUE(manager1.select(2) == 10)
        ASSERT_TRUE(manager1.replace(8, 10))
        ASSERT_TRUE(*manager1.last == 10)
        ASSERT_TRUE(manager1.replace(0, 50))
        ASSERT_TRUE(*manager1.first == 50)
        ASSERT_TRUE(manager1.replace(5, 120))
        ASSERT_TRUE(manager1.select(5) == 120)
        
        ASSERT_TRUE(manager1.reverse_list())
        ASSERT_TRUE(!manager1.empty())
        
        return true;
	}
	
	// PURPOSE: insert_front() keeps moving elements forward
    bool test6() {
        
        //Init.
        DronesManager manager1;
        manager1.insert_front(10);
        manager1.insert_front(20);
        manager1.insert_front(30);
        manager1.insert_front(40);
        manager1.insert_front(50);
        manager1.insert_front(30);
        manager1.insert_front(40);
        manager1.insert_front(50);
        manager1.insert_front(30);
        vector<int> values = {30,50,40,30,50,40,30,20,10};
        
        //Testing that each value inserted at the front is pushed back
        ASSERT_TRUE(manager1.size == 9)
        for(int i = 0; i < manager1.size; i++){
            ASSERT_TRUE(manager1.select(i) == values[i])
        }
        ASSERT_TRUE(*manager1.last == 10)
        ASSERT_TRUE(*manager1.first == 30)
	    return true;
	}
	
	// PURPOSE: inserting at different positions in the list
	bool test7() {
        
        //Init.
        DronesManager manager1;
        manager1.insert_back(10);
        manager1.insert_back(20);
        manager1.insert_back(30);
        manager1.insert_back(40);
        manager1.insert_back(50);
        manager1.insert_back(30);
        manager1.insert_back(40);
        manager1.insert_back(50);
        manager1.insert_back(30);
        
        //Testing the insertion at different positions within the list and then checking if the node has changed
        ASSERT_TRUE(manager1.insert(120, 2))
        ASSERT_TRUE(manager1.insert(120, 4))
        ASSERT_TRUE(manager1.insert(120, 6))
        ASSERT_TRUE(manager1.select(2) == 120)
        ASSERT_TRUE(manager1.select(4) == 120)
        ASSERT_TRUE(manager1.select(6) == 120)

        return true;
	}
	
	// PURPOSE: try to remove too many elements, then add a few elements
	bool test8() {
        
        //Init.
        DronesManager manager1;
	    manager1.insert_back(10);
        manager1.insert_back(20);
        manager1.insert_back(30);
        manager1.insert_back(40);
        manager1.insert_back(50);
        manager1.insert_back(30);
        manager1.insert_back(40);
        manager1.insert_back(50);
        manager1.insert_back(30);
        
        //Testing removes all elements and tries to remove too many
        for(int i = 0; i < 9; i++){
            ASSERT_TRUE(manager1.remove_front())
        }
        ASSERT_TRUE(manager1.empty())
        ASSERT_TRUE(!manager1.remove_front())
        
        //Adding a few elements
        manager1.insert_back(10);
        manager1.insert_back(20);
        manager1.insert_back(30);
        manager1.insert_back(40);
        ASSERT_TRUE(!manager1.empty())
        ASSERT_TRUE(manager1.size == 4)
        ASSERT_TRUE(*manager1.last == 40)
        ASSERT_TRUE(*manager1.first == 10)
        
        return true;
	}
	
	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9() {
        
        //Random seed and DroneManager Init.
        srand(time(0));
        
        int size = rand() % 100 + 1;
        
        DronesManager manager1;
        
        for(int i = 0; i < size; i++){
            manager1.insert_back(rand() % 100 + 1);
        }
        
        return true;
	}    
	    	
	// PURPOSE: lots of inserts, reverse the list, and then lots of removes until empty
	bool test10() {
        
        //Init the DroneManager and make lots of random inserts
        srand(time(0));
        int size = rand() % 100 + 1;
        DronesManager manager1;
        for(int i = 0; i < size; i++){
            ASSERT_TRUE(manager1.insert_back(rand() % 100 + 1));
        }
        
        //Reverse the list and then remove lots of nodes until it is empty
        ASSERT_TRUE(manager1.reverse_list());
        for(int i = 0; i < size; i++){
            manager1.remove_back();
        }
        ASSERT_TRUE(manager1.empty())
        return true;
	} 
};

#endif
