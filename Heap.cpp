
/*
 CS300 – Spring 2018-2019 - Sabanci University
 Homework #4 – Job Scheduling
 Due Date: May 15 Wednesday 22:00
 
 For testing there are 5 inputs where 4 of them are taken from the HW document and 1 is taken from the Drive folder of the lecture
 
 Outputs are named as input_filename.out(.out extension comes after the filename that is asked from the user)
 
 
 
 Name:Onur Arda
 Surname:Bodur
 ID:23617
 Username:onurarda
 E-Mail:onurarda@sabanciuniv.edu
 
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <climits>

using namespace std;

struct Job //Structure of a job that contains info. about the specific jobID,the days_to_do and overloaded '>','<' operators
{
    int jobID;
    
    int days_to_do;
    
    Job():jobID(0),days_to_do(0){}
    
    bool operator<(const Job & j)const  {
        
        if(this->days_to_do<j.days_to_do){
            
            return true;
            
        }
        
        return false;
    }
    
    bool operator>(const Job & j)const  {
        
        if(this->days_to_do>j.days_to_do){
            
            return true;
            
        }
        
        return false;
        
    }
    
    
};

struct Worker //Structure for a worker that contains specific workerID ,operated(Job) that the worker does and overloaded '>','<','-' operators
{
    int workerID;
    
    Job operated;
    
    Worker(){
        
        workerID=0;
        
        operated.jobID=0;
        
        operated.days_to_do=0;
        
    }
    
    bool operator<(const Worker & w)const{
        
        if(this->operated<w.operated==true){
            
            return true;
            
        }
        
        else if(this->operated.days_to_do==w.operated.days_to_do){
            
            if(this->workerID<w.workerID){
                
                return true;
                
            }
            
        }
        
        return false;
        
    }
    
    bool operator>(const Worker & w)const{
        
        if(this->operated>w.operated==true){
            
            return true;
            
        }
        
        else if (this->operated.days_to_do==w.operated.days_to_do){
            
            if(this->workerID>w.workerID){
                
                return true;
                
            }
            
        }
        
        return false;
        
    }
    
    void operator-(const int & d){
        
        this->operated.days_to_do=this->operated.days_to_do - d;
    }
    
};
// Prototype of a utility function to swap two integers
void swap(int *x, int *y);

// A class for Min Heap
template<class Comparable>
class MinHeap{
    
private:
    
    Comparable *harr; // pointer to array of elements in heap
    
    int capacity; // maximum possible size of min heap
    
    int heap_size; // Current number of elements in min heap
    
public:
    
    // Constructor
    MinHeap(int capacity);
    
    // to heapify a subtree with the root at given index
    void MinHeapify(int );
    
    int parent(int i) { return (i-1)/2; }
    
    // to get index of left child of node at index i
    int left(int i) { return (2*i + 1); }
    
    // to get index of right child of node at index i
    int right(int i) { return (2*i + 2); }
    
    // to extract the root which is the minimum element
    Comparable extractMin();
    
    void decreaseElements(int t);
    
    // Returns the minimum key (key at root) from min heap
    Comparable getMin() { return harr[0]; }
    
    // Inserts a new key 'k'
    void insertKey(Comparable & item);
    
    int size();
};

// Constructor: Builds a heap from a given array a[] of given size
template<class Comparable>
MinHeap<Comparable>::MinHeap(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = new Comparable[cap];
}

// Inserts a new key 'k'
template<class Comparable>
void MinHeap<Comparable>::insertKey(Comparable & item)
{
    if (heap_size == capacity)
    {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }
    
    // First insert the new key at the end
    heap_size++;
    int i = heap_size - 1;
    harr[i] = item;
    
    // Fix the min heap property if it is violated
    while (i != 0 && harr[parent(i)] > harr[i])
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

// Method to remove minimum element (or root) from min heap
template<class Comparable>
Comparable MinHeap<Comparable>::extractMin()
{
    
    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }
    
    // Store the minimum value, and remove it from heap
    Comparable root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    MinHeapify(0);
    
    return root;
}

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
template<class Comparable>
void MinHeap<Comparable>::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l] < harr[i])
        smallest = l;
    if (r < heap_size && harr[r] < harr[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}
// decreaseElements func. for using to calculate the minimized scheduling / decreaseKey method with O(N) time complexity
template<class Comparable>
void MinHeap<Comparable>::decreaseElements(int t)
{
    for(unsigned int i=0;i<heap_size;i++)
    {
        harr[i]-t;
    }
    
}

template<class Comparable>
int MinHeap<Comparable>::size()
{
    return heap_size;
}

// A utility function to swap two elements
template<class Comparable>
void swap(Comparable *x, Comparable *y)
{
    Comparable temp = *x;
    *x = *y;
    *y = temp;
}


int main() {
    
    int painter_num,job_num;
    
    string filename;
    
    cout << "Please enter a file name: ";
    
    cin >> filename;
    
    cout << endl;
    
    // For taking the necessary information from the input file
    
    ifstream file;
    
    file.open(filename.c_str());
    
    string line;
    
    getline(file,line);
    istringstream N(line);
    N>>painter_num;
    
    getline(file,line);
    istringstream W(line);
    W>>job_num;
    
    queue<Job>job_holder;
    
    int jobID,days;
    int i=0;
    
    for (; i<job_num; i++) { // a loop for putting the necessary input info. inside a queue
        
        getline(file, line);
        
        istringstream Liner(line);
        
        Liner>>jobID>>days;
        
        Job jobby; // a job structure to put inside the queue
        
        jobby.jobID=jobID;
        
        jobby.days_to_do=days;
        
        job_holder.push(jobby);
        
    }
    
    file.close();
    
    //Necessary info's. taken from the file,file is closed
    
    ofstream myfile; //output file
    
    string out=filename+".out"; //output file extension covered(input_file_name.out)
    
    myfile.open(out); //output file opened
    
    MinHeap<Worker> heap(painter_num); // heap for workers capacity of painter_num(the heaps capacity wont be needed to go larger than this)
    
    int day_delete=0; //if the painter_num>job_num than this means that the jobs will be done till the largest deadline
    
    int day_count=0; //for counting days
    
    if (painter_num >= job_num) { //reassignment of a worker and decrease the days are not necessary actions in this state
        
        for (int i = 0; i<job_num; i++) {
            
            Worker work;
            
            work.operated=job_holder.front();
            
            work.workerID=i+1;
            
            heap.insertKey(work);
            
            myfile << "Job->" << work.operated.jobID << " Worker->" << work.workerID << " (Day: " << day_count << ")" << endl;
            
            myfile << endl;
            
            job_holder.pop();
            
        }
        
        for (int j = 0; j<job_num; j++) {
            
            day_delete=heap.getMin().operated.days_to_do;
            
            heap.extractMin();
            
            // heap.decreaseElements(day_delete);
            
            // day_count= day_count + day_delete;
            
        }
        
        myfile << "All jobs are completed in " << day_delete << " days." << endl ;
        
        myfile << endl;
        
    }
    
    else { //re-assignment needed and decrease days are necessary
        
        for (int i = 0; i<painter_num; i++) {
            
            Worker work;
            
            work.operated=job_holder.front();
            
            job_holder.pop();
            
            work.workerID=i+1;
            
            myfile << "Job->" << work.operated.jobID << " Worker->" << work.workerID << " (Day: " << day_count << ")" << endl;
            
            myfile << endl;
            
            heap.insertKey(work);
            
        }
        
        
        while(heap.size()!=0) {
            
            int workerID_deleted=heap.getMin().workerID;
            
            day_count=day_count+heap.getMin().operated.days_to_do;
            
            heap.decreaseElements(heap.getMin().operated.days_to_do);
            
            heap.extractMin();
            
            if (!job_holder.empty()) {
                
                Worker work;
                
                work.operated=job_holder.front();
                
                work.workerID = workerID_deleted;
                
                myfile << "Job->" << work.operated.jobID << " Worker->" << work.workerID << " (Day: " << day_count << ")" << endl;
                
                myfile << endl;
                
                heap.insertKey(work);
                
                job_holder.pop();
            }
            
        }
        
        myfile << "All jobs are completed in " << day_count << " days." << endl ;
        
        myfile << endl;
    }
    
    myfile.close(); //output file closed
    
    return 0 ;
}
