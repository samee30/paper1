#include <iostream>
using namespace std;
#define MAX_HEAP_SIZE (128)
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
void swap(int &a, int &b){
   int temp = a;
   a = b;
   b = temp;
}
bool Greater(int a, int b){
   return a > b;
}
bool Smaller(int a, int b){
   return a < b;
}
int Signum(int a, int b){
   if( a == b )
      return 0;
   return a < b ? -1 : 1;
}
class Heap{
   public:
      Heap(int *b, bool (*c)(int, int)) : A(b), comp(c)
      { heapSize = -1; }
      virtual bool Insert(int e) = 0;
      virtual int GetTop() = 0;
      virtual int ExtractTop() = 0;
      virtual int GetCount() = 0;
      protected:
      int left(int i) {
         return 2 * i + 1;
      }
      int right(int i) {
         return 2 * (i + 1);
      }
      int parent(int i) {
         if( i <= 0 ){
            return -1;
         }
         return (i - 1)/2;
      }
      int *A;
      bool (*comp)(int, int);
      int heapSize;
      int top(void){
         int max = -1;
         if( heapSize >= 0 )
            max = A[0];
         return max;
      }
      int count() {
         return heapSize + 1;
      }
      void heapify(int i){
         int p = parent(i);
         if( p >= 0 && comp(A[i], A[p]) ) {
            swap(A[i], A[p]);
            heapify(p);
         }
      }
      int deleteTop(){
         int del = -1;
         if( heapSize > -1){
            del = A[0];
            swap(A[0], A[heapSize]);
            heapSize--;
            heapify(parent(heapSize+1));
         }
         return del;
      }
      bool insertHelper(int key){
         bool ret = false;
         if( heapSize < MAX_HEAP_SIZE ){
            ret = true;
            heapSize++;
            A[heapSize] = key;
            heapify(heapSize);
         }
         return ret;
      }
};
class MaxHeap : public Heap {
   private:
   public:
      MaxHeap() : Heap(new int[MAX_HEAP_SIZE], &Greater) { }
      int GetTop() {
         return top();
      }
      int ExtractTop() {
         return deleteTop();
      }
      int GetCount() {
         return count();
      }
      bool Insert(int key) {
         return insertHelper(key);
      }
};
class MinHeap : public Heap{
   private:
   public:
      MinHeap() : Heap(new int[MAX_HEAP_SIZE], &Smaller) { }
      int GetTop() {
         return top();
      }
      int ExtractTop() {
         return deleteTop();
      }
      int GetCount() {
         return count();
      }
      bool Insert(int key) {
         return insertHelper(key);
      }
};
int findMedian(int e, int &median, Heap &left, Heap &right){
   switch(Signum(left.GetCount(), right.GetCount())){
      case 0: if( e < median ) {
         left.Insert(e);
         median = left.GetTop();
      }
      else{
         right.Insert(e);
         median = right.GetTop();
      }
      break;
      case 1: if( e < median ){
         right.Insert(left.ExtractTop());
         left.Insert(e);
      }
      else
         right.Insert(e);
         median = ((left.GetTop()+right.GetTop())/2);
      break;
      case -1: if( e < median )
         left.Insert(e);
      else {
         left.Insert(right.ExtractTop());
         right.Insert(e);
      }
      median = ((left.GetTop()+right.GetTop())/2);
      break;
   }
   return median;
}
void printMedianStream(int A[], int size){
   int median = 0;
   Heap *left = new MaxHeap();
   Heap *right = new MinHeap();
   for(int i = 0; i < size; i++) {
      median = findMedian(A[i], median, *left, *right);
      cout<<"Median of elements : ";
      for(int j = 0; j<=i;j++) cout<<A[j]<<" ";
      cout<<"is "<<median<<endl;
   }
}
int main(){
   int A[] = {5, 15, 1, 3};
   int size = ARRAY_SIZE(A);
   printMedianStream(A, size);
   return 0;
}
