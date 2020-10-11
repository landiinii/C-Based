#include "QS.h"
using namespace std;
void QS::quicksort(int left, int right){
    if((right-left)<1){
        return;
    }
    else{
        int pivot = medianOfThree(left, right);
        pivot = partition(left, right, pivot);
        if(pivot == -1){
            return;
        }
        else{
            quicksort(left, pivot-1);
            quicksort(pivot+1, right);
        }
    }
    return;
}
void QS::sortAll(){
    if(array == NULL){
        return;
    }
    else{
        quicksort(0, position-1);
    }
}
int QS::medianOfThree(int left, int right){
	    if(array == NULL){
	        cout << "error 2.1.1" << endl;
	        return -1;
	    }
	    if(left >= right){
	        cout << "error 2.1.2" << endl;
	        return -1;
	    }
	    if(position == 0){
	        cout << "error 2.1.3" << endl;
	        return -1;
	    }
	    if(left < 0){
	        cout << "error 2.1.4" << endl;
	        return -1;
	    }
	    if(right >= position){
	        cout << "error 2.1.5" << endl;
	        return -1;
	    }
	    int temp;
	    int mid = (left + right) / 2;
	    if(array[left] > array[mid]){
	        temp = array[left];
	        array[left] = array[mid];
	        array[mid] = temp;
	    }
	    if(array[mid] > array[right]){
	        temp = array[mid];
	        array[mid] = array[right];
	        array[right] = temp;
	    }
	    if(array[left] > array[mid]){
	        temp = array[left];
	        array[left] = array[mid];
	        array[mid] = temp;
	    }
	    return mid;
}
int QS::partition(int left, int right, int pivotIndex){
    if(array == NULL || left >= right || position == 0 || left < 0 || right >= position || pivotIndex < left || pivotIndex > right){
        cout << "error 2.2" << endl;
        return -1;
    }  
    int temp = array[left];
	array[left] = array[pivotIndex];
	array[pivotIndex] = temp;
	int up = left + 1;
	int down = right;
	int tmp;
	do{
	    while(up < right){
	        if(array[up] > array[left]){
	            break;
	        }
	        up++;
	    }
	    while(down > left){
	        if(array[down] <= array[left]){
	            break;
	        }
	        down--;
	    }
	    if(up<down){
	        tmp = array[up];
	        array[up] = array[down];
	        array[down] = tmp;
	    }
	}while(up < down);
	int piv = array[left];
	array[left] = array[down];
	array[down] = piv;
	
	return down;
}
string QS::getArray() const{
    string arreturn = "";
    stringstream rr;
    if(array == NULL){
        return arreturn;
    }
    else if(position > 0) {
        for (int i = 0; i < position -1; ++i){
                rr << array[i] << ",";
        }
        rr << array[position - 1];
        arreturn = rr.str();
    }
    else{
        arreturn = "";
    }
    return arreturn;
}
int QS::getSize() const{
    return position;
}
bool QS::addToArray(int value){
    if(position < maxposition){
        array[position] = value;
        position++;
        return true;
    }
    return false;
}
bool QS::createArray(int capacity){
    if(array != NULL){
        clear();
    }
    if(capacity >= 0){
        array = new int[capacity];
        position = 0;
        maxposition = capacity;
        return true;
    }
    else{
        return false;
    }
}
void QS::clear(){
    position = 0;
    maxposition = 0;
    delete [] array;
    array = NULL;
}
