#include <ncurses.h>
#include "AutoComplete.h"

using namespace std ;

class TextEditor{
    
    int cur_x,cur_y ;
    Trie obj ;

    void UpdateCursorPosition(){
        cur_x = getcurx(stdscr) ;
        cur_y = getcury(stdscr);
    }

    void PrintString(string word){
        for(int i=0;i<word.length();i++){
            addch(word[i]);
        }
    }
    public :

    TextEditor(){
        initscr();   // initialize ncurses screen
        cbreak();    // get a character without pressing enter
        noecho();    // disabling print of character while reading 
        cur_x =0 ;
        cur_y =0 ;
    }

    ~TextEditor(){
        endwin();
    }

    
    void Read(){
        
        printw("$") ;
        char ch ;
        string word;

        while(ch=wgetch(stdscr)){
             
            UpdateCursorPosition();

            // Delete a character
            if((ch=='\b')||(ch==127)||(ch==KEY_BACKSPACE)){
                if(cur_x!=1)
                {
                    move(cur_y,cur_x-1);
                    delch();
                    word = word.substr(0,word.length()-1);
                }
            }
            // for executing command 
            else if(ch=='\n'){
                move(cur_y+1,0);
                Read();
            }
            // tab for auto completion 
            else if(ch=='\t'){
                if(word!=""){
                    vector <string> Suggestions(100,"");
                    int len =0;
                    obj.suggest(word,Suggestions,len);
                    if(len==1){
                        move(cur_y,cur_x-word.length());
                        PrintString(word+Suggestions[0]);
                    }
                    else if(len>1){
                        move(cur_y+1,0);
                        int iter =1;
                        for(int i=0;i<len;i++){
                            PrintString(word+Suggestions[i]);
                            move(cur_y+ (++iter),0);
                        }
                        move(cur_y+iter,0);
                        Read();
                    }
                    
                }
            }
            // add character to terminal
            else {
                addch(ch);
                if(ch!=' '){
                    word+=ch ;
                }
                else word="";
            }
            
        }
    }
};