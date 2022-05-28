#include <bits/stdc++.h>
#include <ncurses.h>
using namespace std ;

class Trie ;

class Node {
    Node** links;
    char data ;
    bool IsEnd ;
    vector <int> flag ;
    friend class Trie ;
    
    public :
    Node(char data){
        this->data = data ;
        links = new Node*[26];
        for(int i=0;i<26;i++){
            links[i] = NULL ;
        }
        IsEnd = false;
    }
};


class Trie {
    Node* root ;
    
    void Insert(string data){
        
        Node* temp  = root ;
    
            for(int i=0;i<data.length();i++){
                int key = data[i]- 'a' ;
                if(temp->links[key]==NULL){
                    temp->links[key] = new Node(data[i]);
                    temp->flag.push_back(key);
                }
                 temp = temp->links[key];
                
            }
            temp->IsEnd = true ;
    
        
    }
  
    void DisplayAll(Node* temp,int& cur,vector<string>& a){
       
        
        for(auto i:temp->flag){
                a[cur]=(a[cur]+temp->links[i]->data);
                if(!temp->links[i]->IsEnd) DisplayAll(temp->links[i],cur,a);
                else cur++ ;
        }
       
    }

   
    public :
    Trie(){
        root =  new Node(-1);
        vector <string> words ={
            "mkdir","rename","mkfile","rm","index.cpp","index.html"
        }  ;
        for(auto i:words){
            Insert(i);
        }
    }   
     
    

    
    void suggest(string data,vector <string>& hi,int& cur){
        string result ="";
        Node* temp = root ;
        bool flag =false ;
        int iter =0;
        for(int i=0;i<data.length();i++){
            if((flag==false)&&(i>0)) break;
            int key = data[i]-'a' ;
            if(temp->links[key]!=NULL){
                temp = temp->links[key];
                flag =true ;
              
            }
        }
        if(flag) 
            DisplayAll(temp,cur,hi);
       
    }
};

