#include<iostream>
using namespace std;


int main(){
	int size,temp;
	cout<<"Enter array size"<<endl;
	cin>>size;
	
	int arr[size];
	for(int i=0;i<size;i++){
		cout<<"Enter array element: ";
		cin>>arr[i];
	}
	
	for(int i=0;i<size;i++){
		for(int j=0;j<=i;j++){
			if(arr[i] < arr[j]){
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	
	cout<<"The smallest element is "<<arr[0]<<endl;
	cout<<"And second smallest element is "<<arr[1]<<endl;
}
