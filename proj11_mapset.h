//project 11
//mapset class using singly linked list of nodes
//Node<K,V>* find_key(K key) returns a pointer to a Node<K,V> 
//size()  returns size of the MapSet (number of Nodes)
//get(K) : returns a Node<K,V> that is either a copy of the Node that has the string as a key or a pair with default values
//update(K, V) : if the key is in the MapSet, update the key-value pair to the value and Return true. return false if not
//remove(string) : if the key is in the MapSet, remove the associated Node and return true. If the key is not in the MapSet do nothing and return false
//add(string,long) : if the is in the MapSet, do nothing and return false. Otherwise create a Node with the argument values and insert the new pair into the array, in sorted order, and return true
//compare(MapSet&) compares the two MapSets
//mapset_union(MapSet&). Return a new MapSet that is a union of the two MapSets being called
//mapset_intersection(MapSet&). Return a new MapSet that is the intersection of the two MapSets being called.


#ifndef MAP_SET
#define MAP_SET

#include<iostream>
using std::ostream; using std::endl; using std::cout;
#include<string>
using std::string;
#include<utility>
using std::pair;
#include<initializer_list>
using std::initializer_list;
#include<sstream>
using std::ostringstream;


//
// Node
//
template<typename K, typename V>
struct Node {
  K first;
  V second;
  Node *next = nullptr;
  
  Node() = default;
  Node(K,V);
  bool operator<(const Node&) const;
  bool operator==(const Node&) const;
  friend ostream& operator<<(ostream &out, const Node &n){
      out << n.first << ":" << n.second << endl; //write to o stream
      return out;
  }
};

template<typename K, typename V>
Node<K,V>::Node(K key, V value){
    first = key; //constructr key as first and value as second
    second = value;
}

template<typename K, typename V>
bool Node<K,V>::operator<(const Node &n) const{
    return n.first > first; //return true or false
}

template<typename K, typename V>
bool Node<K,V>::operator==(const Node &n) const{
    return first == n.first; //return true or false
}


//
// MapSet
// 
template<typename K, typename V>
class MapSet{
 private:
  Node<K,V>* head_ = nullptr;
  Node<K,V>* tail_ = nullptr;  
  size_t sz_ = 0;
   Node < K, V > *find_key(K);

 public:
  MapSet()=default;
  MapSet(initializer_list< Node<K,V> >);
  MapSet (const MapSet&);
  MapSet operator=(MapSet);
  ~MapSet();
  size_t size();
  bool remove (K);  
  bool add(Node<K,V>);
  Node<K,V> get(K);
  bool update(K,V);  
  int compare(MapSet&);
  MapSet mapset_union (MapSet&);
  MapSet mapset_intersection(MapSet&);

  friend ostream& operator<<(ostream &out, const MapSet &ms){
    // YOUR CODE HERE
    for(auto it = ms.head_; it != nullptr; it = it->next){
        out << (it == ms.head_ ? "" : ", ") << it->first << ":"<<it->second; //write to ostrem
    }
    return out;
  }  
};

template<typename K, typename V>
  MapSet<K,V>::MapSet(initializer_list< Node<K,V> > il){
  typename initializer_list <Node <K,V >>::iterator it;
  for (it = il.begin (); it != il.end (); ++it) {
      Node<K, V> pair = *it;
      add(pair); //add pairs from initializer_list in sorted order
    }
}

template<typename K, typename V>
MapSet<K,V>::MapSet(const MapSet &ms){
    if (ms.head_ == nullptr){ //empty mapset
        head_ = nullptr;
        tail_ = nullptr;
    }
    else{
        head_ = new Node<K,V>(*ms.head_); //add all of ms elements
        tail_ = head_;
        Node<K,V>* ms_ptr = ms.head_->next;
        Node<K,V>* new_node;
        while (ms_ptr != nullptr){
            new_node = new Node<K,V>(*ms_ptr);
            tail_->next = new_node;
            ms_ptr = ms_ptr->next;
            tail_ = new_node;
	    }
    }
}

template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::operator=(MapSet ms){
    swap(head_, ms.head_);
    swap(tail_, ms.tail_);
    return *this;
}	

// walk down the list, moving head_ but remember it in to_del
// delete each node in turn, the set head_ and tail_
template<typename K, typename V>
MapSet<K,V>::~MapSet(){
    Node<K,V>* to_del = head_;
    while (to_del != nullptr){
        head_ = head_->next;
        delete to_del;
        to_del = head_;
    }
    head_ = nullptr;
    tail_ = nullptr;
}

template<typename K, typename V>
size_t MapSet<K,V>::size(){
    return sz_;
}

template<typename K, typename V>
Node < K, V > *MapSet<K,V>::find_key(K key){
    
    if(head_ == nullptr or tail_ == nullptr){
        return nullptr;
    }
    Node<K,V>* ptr;
    for(auto it = head_; it!= nullptr; it = it->next){
        if(it->first == key or it->first < key){
            ptr = it;
        }
    }
    return ptr;
    
    
}

template<typename K, typename V>
bool MapSet<K,V>::add(Node<K,V> n){
    Node<K,V>* ptr = find_key(n.first);
    if(ptr == nullptr and sz_ == 0){ //if its the first element in an empty list
        Node<K,V>* new_node = new Node<K,V>(n) ;
        head_ = new_node;
        tail_ = new_node;
        sz_ ++;
        return true;
    }
    if(ptr == nullptr){ 
        Node<K,V>* new_node = new Node<K,V>(n) ;
        new_node->next = head_;
        head_ = new_node;
        sz_++;
        return true;
    }
    else{
        if(ptr->first == n.first){ //key already in list
            return false;
        }
        if(ptr->next == nullptr){ //if its the last element
            Node<K,V>* new_node = new Node<K,V>(n) ;
            ptr->next = new_node;
            new_node->next= nullptr;
            tail_ = new_node;
            sz_ ++;
            return true;
        }
        Node<K,V>* new_node = new Node<K,V>(n) ;
        Node<K,V>* node2 = ptr->next; //other case
        ptr->next = new_node;
        new_node->next = node2;
        sz_++;
        return true;
    }
    
    
    

}

template<typename K, typename V>
bool MapSet<K,V>::remove(K key){
    Node<K,V>* ptr = find_key(key);
    if(ptr == nullptr){ //doesnt exist
        return false;
    }
    for(auto it = head_; it!= nullptr; it = it->next){ //find position and delete it
        if(it->first == key){
            if(head_ == ptr){ //if it is first element
                head_ = head_->next;
                head_->next = ptr->next->next;
                delete ptr;
                sz_ --; //decrease size
                return true;
                
            }
            Node<K,V> *prev = head_;
            while(prev->next != nullptr && prev->next != ptr){ //find element based off of previuos element
                prev = prev->next;
            }
            prev->next = ptr->next; //update next
            delete ptr;
            sz_ --; //decrease size
            return true; 
        }
        
    }
    return false; //doesnt exist

}

template<typename K, typename V>
Node<K,V> MapSet<K,V>::get(K key){
    for(auto it = head_; it != nullptr; it = it->next){ //find key and return the pair
        if(it->first == key){
            return *it;
        }
    }
    return Node< K,V >(); //return default
}


template<typename K, typename V>
bool MapSet<K,V>::update(K key, V value){
    auto remove_result = remove(key);
    if(remove_result == false){ //doesnt exist already
        return false;
    }
    else{
        Node<K,V>* new_node = new Node<K,V>(key, value); //remove and then add value
        add(*new_node);
        return true;
    }
}

template<typename K, typename V>
int MapSet<K,V>::compare(MapSet &ms){
    size_t main_size = size(); //size of calling MapSet
    size_t ms_size = ms.size(); //size of parameter mapset
    auto i = head_;
    auto i2 = ms.head_;
    while(i != tail_ and i2 != ms.tail_ ){ //iterate through both mapsets
        i = i->next;
        i2 = i2->next; 
        if(i == i2){ //continue while the elements match
            continue;
        }
        else if(i->first > i2->first){ //return based off which element is bigger
            
            return 1;
        }
        else if(i2->first > i->first){
            
            return -1;
        }
    }
    if(main_size == ms_size){ //if both mapsets are exactly the same
        return 0;
    }
    if(main_size > ms_size){ //return based off of size
        return 1;
    }
    if(ms_size > main_size){
        return -1;
    }

    
}

template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_union(MapSet<K,V> &ms){
    MapSet < K, V > union_set(*this); //copy all elements from calling mapset
    for(auto it = ms.head_; it != nullptr; it = it->next){ 
        union_set.add(*it); //iterate through all elements in other mapset and add to new mapset
    }
    return union_set;
}

template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_intersection(MapSet<K,V> &ms){
    MapSet<K,V> intersection(*this); //add all elements of calling mapset
    for(auto i = head_ ; i != nullptr ; i= i->next){
        int check = 0;
        auto key = i->first;
        for(auto i2 = ms.head_ ; i2 != nullptr; i2 = i2->next){ 
            auto other_key = i2->first;
            if(key == other_key){
                check = 100;
            }
        }
        if(check == 0){
            intersection.remove(key); //remove the elements that arent in the other mapset
        }
    }
    return intersection;
}
#endif
