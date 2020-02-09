/*
 
 CS300 – Spring 2018-2019 - Sabancı University
 
 Homework #3 – Hashed Dictionary vs. AVL_Tree Dictionary
 
 Due March 23 Saturday at 22:00
 
 Brief Description:The dictionary will have hundreds of words and their corresponding meanings. In this case, you will keep a hash table of word entries to make translations faster than the other data structures.For each word in the dictionary file and its corresponding meanings will be inserted as a node into both of your data structures, i.e. Binary Search Tree (BST) and Hash Table.
 
 Data Structures:The dictionary that has been obtained from the txt file is kept inside both data structures AVL Tree and Hash Table.This process is done in order to show the difference of the speed due to the data structures.
 
 Program Flow:Program starts with reading the “dict.txt” file. Each line in the file provides an English word with its Turkish translation.The words in each line are separated by spaces. There is a possibility of having more than one space between each word, and also there may be some words without any translations, and also the program is not case sensitive. For each unique word appearing in the dictionary file, you need to insert a new node into the tree and the hash table. The initial size of hash table will be 53. Each rehash operation is performed in a way that the next table size of hash table will be the next prime number that comes right after the current table size is doubled. For example, if initial table size is 53, the next table size become 107 since 107 is the first prime number after 106=53x2.When rehashing occurs, i.e. program displays the previous capacity, the previous load, the current capacity, the current load, and the number of items in the HashTable.Once the preprocessing is finished, the program prints the final item count in the HashTable and the current load factor λ.After building the BST and the Hash Table, the program preprocesses the query file and stores all queries in a linear data structure (vector/array, etc.). The query file is composed of words on each line. This line might consist of extra whitespace other than the word itself. The program will query each word in the query file. Then, the program outputs the corresponding query results for that query file into an output file.Each line in the output file will be composed of the queried word itself and its corresponding translation in a tab separated format. Output file names for Hash Table and BST will be ht_results.txt and bst_results.txt respectively.Then, the program computes the time it takes to perform all queries in the file with each data structure implemented so far (BST, Hash Table) and displays them with elapsed time of all queries, the average query time, the speedup ratio of these timing values compared to each other and total elapsed time for k query where k = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096}.

 
 
 Line Number:904
 Line number from the previous code that was implemented for HW#2:386 for AVL_Tree class + 68 for dict.txt parser
 Line number for current HW's data structures and operations:170 for Hash Table Class and its necessary operations such as nextPrime,IsPrime.280 for query,outputting etc.
 
 
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <vector>

using namespace std;

//*******************************
//*****TREE FROM HW#2*****
//*******************************

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
AVL_Tree<Comparable>::AVL_Tree(const Comparable & notFound ) :ITEM_NOT_FOUND( notFound ), root( nullptr ){
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
//*******************************
//*****TREE FROM HW#2*****
//*******************************

bool IsPrime(int number){ //a function for checking if a number is prime or not
    if (number == 2 || number == 3)
        return true;
    
    if (number % 2 == 0 || number % 3 == 0)
        return false;
    
    int divisor = 6;
    while (divisor * divisor - 2 * divisor + 1 <= number)
    {
        
        if (number % (divisor - 1) == 0)
            return false;
        
        if (number % (divisor + 1) == 0)
            return false;
        
        divisor += 6;
        
    }
    
    return true;
    
}

int NextPrime(int a){ // a function that seeks for the first prime after itself
    while (!IsPrime(++a));
    return a;
}


template <class T>
class HashTable{
    
public:
    struct Hashed{ // hash node
        T word;
        T definition;
        Hashed * next;
        Hashed(T word, T definition) : word(word), definition(definition), next(nullptr){}
        Hashed() : next(nullptr) {};
    };
    
    int hash(T word){ //hash function
        int sum = 0;
        for (int k = 0; k < word.length(); k++)
            sum = sum + int(word[k])*k;
        return  sum % tableSize;
    }
    
    HashTable(int size){ // constructor
        
        head=new Hashed*[size];
        
        for (int i=0; i<size; i++){
            head[i]=nullptr;
        }
        
        tableSize=size;
        currLoad=0;
    }
    
    void rehash(){ //rehash function that extends the hash table when necessary
        
        int prevSize=tableSize;
        int newSize=NextPrime(prevSize*2);
        
        Hashed ** secondPoint= new Hashed*[newSize]();
        Hashed ** oldHead = head;
        
        head=secondPoint;
        tableSize=newSize;
       
        cout << "rehashed..." << endl; //necessary outputs for the program
        cout << "previous table size:"<<prevSize<<", new table size: "<<newSize<<", current unique word count "<<
        currLoad<<", current load factor: "<<1.0*currLoad/newSize<<endl;
        
        currLoad=0;
        
        for(int i=0; i<prevSize; i++){
        
            Hashed *toBeRelocated=oldHead[i];
            
            while(toBeRelocated!=nullptr){
                T wo=toBeRelocated->word;
                T de=toBeRelocated->definition;
                insert(wo, de);
                toBeRelocated=toBeRelocated->next;
            }
        }
        
        delete [] oldHead;
        
       
    }
    
    void insert(T w, T d){ //insert function where it also checks if there is a rehash needed or not
       
        currLoad+=1;
        int location=hash(w);
        Hashed *prev = nullptr;
        Hashed *curr = head[location];
        while(curr!=nullptr){
            prev=curr;
            curr=curr->next;
        }
        if(curr!=nullptr){
            T prevValue=curr->definition;
            curr->definition=prevValue+","+d;
        }
        else{
            
            curr=new Hashed(w, d);
            if(prev!=nullptr){
                prev->next=curr;
            
            }
            else{
                head[location]=curr;
                
            }
        }
       
        if((1.0*currLoad/tableSize)>0.5){
           
            rehash();
        
        }
    }
    
    T search(T w){ //search function
        int location=hash(w);
        Hashed *curr=head[location];
        while(curr!=nullptr){
            if(curr->word==w){
                return curr->definition;
            }
            curr=curr->next;
        }
        return "notFound";
    }
    
    int returnSize(){ //a function that returns the size of the table
        
        return tableSize;
        
    }
    
    int returnLoad(){ //a function that returns the load of the table
        
        return currLoad;
    
    }
    
    double returnLoad_Factor(){ //a function that returns the load factor
    
        return ((1.0*currLoad)/tableSize);
    
    }
    
    
private:
    
    Hashed **head;
    
    int currLoad;
    
    int tableSize;
    
};

long long averager(vector<long long>&average){
    long long average_output=0;
    for (int i = 0; i<average.size(); i++) {
        average_output=average_output + average[i];
    }
    return average_output;
}



int main(){
  
    string filename = "dict.txt" ;
    
    AVL_Tree<string>tree("");
    
    cout << "Building a binary tree for " << filename << endl ;
    
    HashTable<string>Hash(53);
    
    cout << "Building a hash table for " << filename << endl ;
    
    string line;
    
    string word;
    
    ifstream file;
    
    file.open("dict.txt");
    
    string translation;
    
    getline(file,line);
    
    string firstWord, secondWord;
    
    istringstream inn(line);
    
    inn>>firstWord>>secondWord;
    
    Hash.insert(firstWord, secondWord);
    
    int counter=0;
    
    while (getline(file, line)) {
        
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
        
        Hash.insert(word, translation);
        
        tree.insert(word, translation);
        
        word = "" ;
        
        translation = "";
        
        i=0;
        
        counter++;
        
    }

    file.close();
    
    cout << "After preprocessing, the unique word count is " << Hash.returnLoad()-1 << ". Current load ratio is "<< Hash.returnLoad_Factor() << endl;
    
    filename="queryNEW.txt";
    
    ifstream file_2;
    
    file_2.open(filename);
    
    vector<string>vec;//the vector that will hold the parsed query file data's
    
    while (getline(file_2,line)) {  //parsing the query file
    
        istringstream liner(line);
        
        liner>>firstWord;
        
        vec.push_back(firstWord);
    }
    
    file_2.close();
    
    cout << "Running queries in " << filename << "..." << endl ;
  
    cout << endl ;
    
    vector<int>holder;//the vector that will hold the coefficients(k) of the k*N times queries
    
    vector<long long>average_1;//the vector for calculating the average query time of the binary search tree
    
    vector<long long>average_2;//the vector for calculating the average query time of the hash table
    
    cout << "***********************************************" << endl;
    cout << "Benchmark results for Binary Search Tree (BST):" << endl;
    cout << "***********************************************" << endl;
   
    auto start = std::chrono::high_resolution_clock::now();
   
    for (int i = 0;i<vec.size();i++) {
        tree.find(vec[i]);
    }
    
    auto time = (std::chrono::high_resolution_clock::now() - start).count();
    
    cout << "+ Elapsed time: " << time  << " ns\n";
    long long int timer_1=time;
    vector<long long int>timer_bst; //the vector that will hold the time of the k*N query
    
    start = std::chrono::high_resolution_clock::now();
    
    
    for (int i = 1; i<4097; i=i*2) {
      
        for (int k = 0; k<i; k++) {
        
            for (int j = 0;j<vec.size();j++) {
                tree.find(vec[j]);
            }
        
        }
        
        time = (std::chrono::high_resolution_clock::now() - start).count();
        
        timer_bst.push_back(time);
        
        holder.push_back(i); //the k times of query num. is pushed to the vector
    
    }
    vector<long long int> timer_bst_average;
    for (int i=0; i<1; i++) {
        
        for (int j = 0;j<vec.size();j++) {
            start = std::chrono::high_resolution_clock::now();
            tree.find(vec[j]);
            time = (std::chrono::high_resolution_clock::now() - start).count();
            timer_bst_average.push_back(time);
        }
        
    }
    
    for (int i=0; i<timer_bst.size(); i++) {
        average_1.push_back(timer_bst_average[i]);
    }
    
   long long average_output_1=averager(average_1);
    
    cout << "+ Average query time: " << timer_1/timer_bst_average.size() << " ns\n";
    cout << endl;
    
    cout << "***********************************************" << endl;
    cout << "Benchmark results for Hash Table:" << endl;
    cout << "***********************************************" << endl;
    
    start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0;i<vec.size();i++) {
        Hash.search(vec[i]);
    }
    
    time = (std::chrono::high_resolution_clock::now() - start).count();
    
    cout << "+ Elapsed time: " << time  << " ns\n";
    
    vector<long long int>timer_hsh;
    
    start = std::chrono::high_resolution_clock::now();
    
    for (int i = 1; i<4097; i=i*2) {
        
        for (int k = 0; k<i; k++) {
        
            for (int j = 0;j<vec.size();j++) {
                Hash.search(vec[j]);
                
            }
            
        }
        
        time = (std::chrono::high_resolution_clock::now() - start).count();
        
        timer_hsh.push_back(time);
    }
    vector<long long int> timer_hsh_average;
    for (int i=0; i<1; i++) {
        
        for (int j = 0;j<vec.size();j++) {
            start = std::chrono::high_resolution_clock::now();
            Hash.search(vec[j]);
            time = (std::chrono::high_resolution_clock::now() - start).count();
            timer_hsh_average.push_back(time);
        }
        
    }
       
    
    
    for (int i=0; i<timer_hsh.size(); i++) {
        average_2.push_back(timer_hsh[i]/holder[i]);
    }
    
    long long average_output_2=averager(timer_hsh_average);
    
    cout << "+ Average query time: " << average_output_2/timer_hsh_average.size() << " ns\n";
    cout << "+ Speed up: " <<1.0*average_output_1/average_output_2 << "x" <<endl;
    cout << endl ;
    cout << "Time measurements in ns (N, 4096N):" << endl;
    cout << "*****************************" << endl;
    cout << "bst" << endl;
    cout << "N    time" << endl;
    
    for (int i = 0 ; i<timer_bst.size(); i++) { // a code fragment for proper form of outputs
        
        if (10>holder[i]) {
            cout << holder[i] << "    " << timer_bst[i] << endl;
        }
        
        if (100>holder[i]&&holder[i]>=10) {
            cout << holder[i] << "   " << timer_bst[i] << endl;
        }
        
        if (1000>holder[i]&&holder[i]>=100) {
            cout << holder[i] << "  " << timer_bst[i] << endl;
        }
        
        if (10000>holder[i]&&holder[i]>=1000) {
            cout << holder[i] << " " << timer_bst[i] << endl;
        }
        
    }
    
    cout << endl ;
    cout << "ht" << endl;
    cout << "N    time" << endl;
    
    for (int i = 0; i<timer_hsh.size(); i++) {
        
        if (10>holder[i]) {
            cout << holder[i] << "    " << timer_hsh[i] << endl;
        }
        
        if (100>holder[i]&&holder[i]>=10) {
            cout << holder[i] << "   " << timer_hsh[i] << endl;
        }
      
        if (1000>holder[i]&&holder[i]>=100) {
            cout << holder[i] << "  " << timer_hsh[i] << endl;
        }
        
        if (10000>holder[i]&&holder[i]>=1000) {
            cout << holder[i] << " " << timer_hsh[i] << endl;
        }
        
    }
    
    ofstream hash_file;
    
    hash_file.open("ht_results.txt");
    
    for (int i = 0;i<vec.size();i++) {
        
        hash_file << vec[i] << "\t" << Hash.search(vec[i]) << "\n" ;
        
    }
    
    hash_file.close();
    
    ofstream binaryT_file;
    
    binaryT_file.open("bst_results.txt");
    
    for (int i = 0;i<vec.size();i++) {
        
        binaryT_file << vec[i] << "\t" << tree.find_trans(vec[i]) << "\n" ;
        
    }
    
    binaryT_file.close();
    
    return 0 ;
}
