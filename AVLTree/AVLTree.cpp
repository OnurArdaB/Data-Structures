/*

 CS300 – Spring 2018-2019 - Sabancı University Homework #2 – Dictionary
 Due March 23 Saturday at 22:00
 
 Problems and Solutions:
 In order to make the dictionary and run a fast search algorithm a Binary Search Tree must be implemented.If the
 given input file is not sorted a regular BST would work.But if the given input file is sorted
 then the a normal BST would work as a linear list which would not change the efficiency.In order to solve this
 problem the BST should be implemented as Balanced (as an AVL Tree).One other major problem is to collect the data
 from the given .txt file correctly.There can be \n chars and etc.In order to solve this problem the lines must be
 searched char by char.After collecting the data correctly there needs some extra functions such as Insert_Trans
 which would insert the translation of the word to the AVL tree.
 
 Details:
 The implemented AVL Tree is taken from the CS-300/Lecture Slides(Spring 2018-2019) and contains some extra
 functions in order to run the code correctly.The Tree does not contain a remove method due to the fact that there
 is no need for one.
 
 Bonus:
 Due to the problem for collecting the data correct(Turkish char collecting) is also solved.
 There is a print function that prints the tree in alphabetic order,in order to check.
 
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <class Comparable>
class AVL_Tree;

template <class Comparable>
class AVL_Node{
    
    Comparable element ; // word to be covered inside the node
    
    Comparable trans ; // translation to be covered inside the node
    
    AVL_Node * left ; // left address of the next node
    
    AVL_Node * right ; // right address of the next node
    
    int height ; //in order to make the tree as an AVL(Balanced) tree we must check the height for the operations and etc.
    
    AVL_Node(const Comparable & theElement, const Comparable & theTrans, AVL_Node * lt ,AVL_Node * rt , int h = 0 ) : element (theElement),trans (theTrans), left(lt) , right(rt) , height (h) {} //node init.
    
    friend class AVL_Tree<Comparable>;
    
};

template <class Comparable>
class AVL_Tree{
    
private:
    
    AVL_Node<Comparable> * root ;
    
    const Comparable ITEM_NOT_FOUND;
    
    const Comparable & elementAt (AVL_Node <Comparable> * t) const {
        
        if (t==nullptr) {
            
            return ITEM_NOT_FOUND;
            
        }
        
        else
            return t->element;
        
    }
    
    const Comparable & elementAt_Trans (AVL_Node <Comparable> * t) const{
        
        if (t==nullptr) {
            
            return ITEM_NOT_FOUND;
            
        }
        
        else
            return t->trans;
        
    }
    
    void insert_trans (const Comparable & x ,const Comparable & y , AVL_Node <Comparable> * & t) const{
        
        find(x, t)->trans = find(x, t)->trans + ", " + y ;
        
    }
    void insert (const Comparable & x ,const Comparable & y , AVL_Node <Comparable> * & t) const{
        
        if ( t == nullptr )
            t = new AVL_Node<Comparable>(x , y , nullptr , nullptr );
        
        else if( x < t-> element ){
            
            insert( x,y,t->left );
            
            if (height( t->left )-height( t->right ) == 2) {
                
                if ( x < t->left->element ) {
                    
                    rotateWithLeftChild ( t ) ;
                    
                } else {
                    
                    doubleWithLeftChild ( t ) ;
                    
                }
                
            }
            
        }
        
        else if(x > t->element ){
            
            insert( x ,y, t->right );
            
            if (height( t->right)-height( t->left ) == 2) {
                
                if (x > t->right->element ) {
                    
                    rotateWithRightChild ( t ) ;
                    
                } else {
                    
                    doubleWithRightChild ( t ) ;
                    
                }
                
            }
            
        }
        
        else
            ;
        
        t->height = max( height( t->left ), height( t->right ) ) + 1;
        
    }
    
    AVL_Node <Comparable> * findMin (AVL_Node<Comparable> *t ) const{
        
        if( t == nullptr )
            return nullptr;
        
        if( t->left == nullptr )
            return t;
        
        return findMin( t->left );
    }
    
    AVL_Node <Comparable> * findMax (AVL_Node<Comparable> *t ) const{
        
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        
        return t;
    }
    
    AVL_Node <Comparable> * find (const Comparable & x , AVL_Node<Comparable> *t) const{
        
        if ( t == nullptr )
            return nullptr ;
        
        else if( x < t->element )
            return find( x, t->left ) ;
        
        else if( t->element < x )
            return find( x, t->right ) ;
        
        else
            return t;    // Match
    }
    
    void makeEmpty ( AVL_Node<Comparable> * & t ) const{
        
        if( t != nullptr ){
            
            makeEmpty( t->left );
            
            makeEmpty( t->right );
            
            delete t;
            
        }
        
        t = nullptr;
        
    }
    
    int height( AVL_Node<Comparable> *t ) const{
        
        if (t == nullptr)
            return -1 ;
        
        return t->height ;
        
    }
    
    
    int max( int lhs, int rhs ) const{
        
        if (lhs > rhs)
            return lhs ;
        
        return rhs ;
    }
    
    
    void rotateWithLeftChild( AVL_Node <Comparable> * & k2 ) const{
        
        AVL_Node <Comparable> * k1 = k2->left;
        
        k2->left = k1->right;
        
        k1->right = k2;
        
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        
        k1->height = max( height( k1->left ), k2->height ) + 1;
        
        k2 = k1;
        
    }
    
    void rotateWithRightChild( AVL_Node <Comparable> * & k1 ) const{
        
        AVL_Node<Comparable> *k2 = k1->right;
        
        k1->right = k2->left;
        
        k2->left = k1;
        
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        
        k2->height = max( height( k2->right ), k1->height ) + 1;
        
        k1 = k2;
        
    }
    
    
    void doubleWithLeftChild( AVL_Node <Comparable> * & k3 ) const{
        
        rotateWithRightChild( k3->left );
        
        rotateWithLeftChild( k3 );
        
    }
    
    void doubleWithRightChild( AVL_Node <Comparable> * & k1 ) const{
        
        rotateWithLeftChild( k1->right );
        
        rotateWithRightChild( k1 );
        
    }
    
    void printTree( AVL_Node<Comparable> *t ) const{
        
        if ( t != nullptr ){
            
            printTree( t->left );
            
            cout << t->element << " ---> " << t->trans <<endl;
            
            printTree( t->right );
            
        }
        
    }
    
public:
    
    //const. funcs.
    
    explicit AVL_Tree (const Comparable & notFound);
    
    AVL_Tree (const AVL_Tree & rhs);
    
    ~AVL_Tree ( );
    
    //finder funcs.
    
    const Comparable & findMin () const ;
    
    const Comparable & findMax () const ;
    
    const Comparable & find (const Comparable & x) const;
    
    const Comparable & find_trans (const Comparable & x) const;
    
    //containment funcs.
    
    bool isEmpty () const ;
    
    void printTree () const ;
    
    void makeEmpty ();
    
    //insert or remove funcs. that calls the private insert or remove
    
    void insert (const Comparable & x,const Comparable & y) ;
    
    void insert_trans (const Comparable & x,const Comparable & y) ;
    
};

//********** CONSTRUCTORS & DESTRUCTOR **************

template <class Comparable>
AVL_Tree<Comparable>::AVL_Tree(const Comparable & notFound) :ITEM_NOT_FOUND( notFound ), root( nullptr ){
}

template <class Comparable>
AVL_Tree<Comparable>::~AVL_Tree( ){
    
    makeEmpty();
    
}

template <class Comparable>
AVL_Tree<Comparable>::AVL_Tree( const AVL_Tree<Comparable> & rhs ) :root( nullptr ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ){
    
    *this = rhs;
    
}


//************* FINDER FUNCS.*******************

template <class Comparable>
const Comparable & AVL_Tree<Comparable>::find( const Comparable & x ) const{
    
    return elementAt( find( x, root ) );
    
}

template <class Comparable>
const Comparable & AVL_Tree<Comparable>::find_trans( const Comparable & x ) const{
    
    return elementAt_Trans( find( x, root ) );
    
}

template <class Comparable>
const Comparable & AVL_Tree<Comparable>::findMin( ) const{
    
    return elementAt( findMin( root ) );
    
}

template <class Comparable>
const Comparable & AVL_Tree<Comparable>::findMax( ) const{
    
    return elementAt( findMax( root ) );
    
}

//************ EMPTY FUNCS *****************

template <class Comparable>
void AVL_Tree<Comparable>::makeEmpty(){
    
    makeEmpty(root);
    
}
template <class Comparable>
bool AVL_Tree<Comparable>::isEmpty() const {
    
    if (root==nullptr) {
        
        return true;
        
    }
    
    else
        return false;
}

//*********** INSERTION & DELETION ****************

template<class Comparable>
void AVL_Tree<Comparable>::insert(const Comparable & x,const Comparable & y){
    
    insert(x,y,root);
    
}

template<class Comparable>
void AVL_Tree<Comparable>::insert_trans(const Comparable & x,const Comparable & y){
    
    insert_trans(x,y,root);
    
}

template <class Comparable>
void AVL_Tree<Comparable>::printTree( ) const{
    
    if( isEmpty( ) )
        cout << "Empty tree" << endl;
    
    else
        printTree( root );
}

int main(){
    
    const string ITEM_NOT_FOUND = ""; // definition for item not found
    
    AVL_Tree<string> tree(ITEM_NOT_FOUND); // tree constructed
    
    string filename = "dict.txt" ; // filenam
    
    string line,word,translation,line_2;
    
    tree.insert("a", "bir");
    tree.insert("I", "ben");
    
  /*  ifstream file(filename.c_str());
    
    //parsing the lines and pushing the data inside tree
    
    while (!file.eof()) {
        
        getline(file, line);
        
        if (line == "\r" || line.empty() || line == "\n") { //lines that does not contain any info are ignored
            
            continue;
            
        }
        
        char one ;
        
        for (int i = 0 ; i<line.size(); i++) { //the words are covered in here
            
            if ((line.at(0)>32||line.at(0)<127)&& (i ==0 )&&(line.at(1)<33||line.at(1)>126)) { //checks if there are any non-necessary chars
                
                one=line.at(0);
                
                line=line.substr(2,line.size()-i-2);
                
                break;
                
            }
            
            if (line.at(i)<33||line.at(i)>126) { //checks if there are any non-necessary chars
                
                word=line.substr(0,i);
                
                line=line.substr(i+1,line.size()-i-1);
                
                break;
                
            }
            
        }
        
        int i = 0 ;
        
        for ( i = 0; i<line.size(); i++) {
            
            if (line.at(i)==92) {
                
                if (line.at(i+1) == 'n' || line.at(i+1) == 'r'|| line.at(i+1) == 't') {
                    
                    line=line.substr(0,i-1) + " " + line.substr(i+2,line.size()-i-1) ;
                    
                    i=0;
                    
                }
                
            }
            
        }
        
        line=line.substr(0,line.size()-1);
        
        translation = line ;
        
        tree.insert(word, translation);
        
        word = "" ;
        
        translation = "";
        
        i=0;
        
        
        
    }
    
    //tree.printTree(); // checking part
    
    bool flag = true ;  // a flag method for running the while loop
    
    cout << "***Help***\nQuery: 1\nAdd new translation: 2\nAdd new word: 3\nExit: 0\n" ;
    
    while(flag == true){ // runs while flag = true , first gives the info of the commands
        
        string command ;
        
        cout << "Enter Command: " ;
        
        cin >> command ;
        
        if (command == "1") { // if 1 is entried as command asks the querried word to be search
            
            cout << "Enter queried word: ";
            
            cin >> command ;
            
            
            if(tree.find_trans(command) != ITEM_NOT_FOUND){ // if the querried word exists shows the translation
                
                cout << command << " ---> ";
                
                cout << tree.find_trans(command) << endl;
                
                //  flag = false ;
            }
            /*
             else{ //if the entered word does not exists the necessary output is given
             cout << " The entered word does not exist \n ";
             }
   
        }
        
        else if(command=="2"){ // if the command is entered as 2 asks for the querried word
            
            cout << "Which word do you want to edit: ";
            
            string querried_word;
            
            cin >> querried_word;
            
            if (tree.find(querried_word) == ITEM_NOT_FOUND) { // if the querried word does not exists
                
                cout << "Word does not exists , if you want to add a new word please use command 3.\n" ;
                
            }
            
            else{ // if the querried word exists the new translation is asked from the user
                
                cout << "Enter the new translation: ";
                
                string new_trans_querried;
                
                cin >> new_trans_querried;
                
                tree.insert_trans(querried_word, new_trans_querried); // new trans. is added
                
                cout << "\n***UPDATED***\n" ;
                
            }
            
        }
        
        else if (command=="3"){ //First takes the new word if the command is entered as 3
            
            cout << "Enter New Word: " ;
            
            string new_word ;
            
            cin >> new_word ;
            
            if (tree.find(new_word) == ITEM_NOT_FOUND) { // checks whether the word exist or not
                
                cout << "Enter Translations: " ; //if not exists takes the translation for the word
                
                string new_trans ;
                
                cin >> new_trans ;
                
                cout << "\n";
                
                tree.insert(new_word, new_trans) ; //inserts the the word with translation
                
                // flag = false; //breaks the while loop
            }
            
            else{ // if exists gives an appropiate output
                
                cout << "Word already exists, if you want to add new translation please use command 2.\n";
                
            }
            
        }
        
        else if (command == "0"){
            
            cout << "Bye...\n";
            
            flag = false ; //If 0 in entered as a command the loop is broken with this line of code
            
        }
    }
    */
    cout << find
    return 0 ;
    
}
