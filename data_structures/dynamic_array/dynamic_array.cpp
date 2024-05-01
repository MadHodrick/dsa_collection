#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "dynamic_array.h"
#include <iostream>

DynamicArray::DynamicArray(){
  size=0;
  capacity=2;
  arr=new int[capacity];
}

int DynamicArray::getSize(){
  return size;
}
int DynamicArray::getCapacity(){
  return capacity;
}

bool DynamicArray::isEmpty(){
  return size==0;
}

int DynamicArray::at(int index){
  if (index<size&&index>=0){
    return arr[index];
  }else {
    throw "Index out of bounds";
  }
}


void DynamicArray::push(int item){
  // If we need to resize
  if (size+1>capacity){
    resize(capacity*2);
  }

  arr[size]=item;
  size++;
}

void DynamicArray::insert(int index,int item){
  // Check index is within bounds
  if(index<0||index>size){
    throw "Index out of bounds";
  }

  // Check for space
  if (size+1>capacity){
    resize(capacity*2);
  }

  // Shift all elements to the right by one
  for (int i=size+1;i>index;i--){
    arr[i]=arr[i-1];
  }

  arr[index]=item;
  size++;
}

void DynamicArray::prepend(int item){
  // Ensure space
  if (size+1>capacity){
    resize(capacity*2);
  }

  // Reverse for loop to shift all the arr elms right
  for (int i = size; i >= 1; i--) {
    arr[i]=arr[i-1];
  }
  arr[0]=item;
  size++;
}

int DynamicArray::pop(){
  size--;
  // Check id we need to downsize
  if(size<(capacity/4)){
    resize(capacity/2);
  }

  return arr[size];
}

void DynamicArray::resize(int newCapacity){
  if (newCapacity>capacity){
    int* oldArr=arr;
    arr=new int[newCapacity];
    for(int i=0;i<capacity;i++){
      arr[i]=oldArr[i];
    }
    capacity=newCapacity;
    delete oldArr;
  }else if (newCapacity<capacity){
    int* oldArr=arr;
    arr=new int[newCapacity];
    for(int i=0;i<newCapacity;i++){
      arr[i]=oldArr[i];
    }
    capacity=newCapacity;
    delete oldArr;
  }
}


void check_array(DynamicArray& vector,const int (&values)[],int len){
  for (int i=0;i<len;i++){
    CHECK(vector.at(i)==values[i]);
  }
}

// Test cases
TEST_CASE("Check push"){
  DynamicArray arr;
  CHECK(arr.getSize()==0);
  arr.push(5);
  CHECK(arr.getSize()==1);
  CHECK(arr.at(0)==5);
  arr.push(6);
  arr.push(8);
  CHECK(arr.getSize()==3);
  CHECK(arr.at(2)==8);
}

TEST_CASE("Test insert"){
  DynamicArray arr;
  arr.push(5);
  arr.push(6);
  arr.push(8);
  CHECK(arr.getSize()==3);
  CHECK(arr.at(2)==8);
  arr.insert(0,4);
  CHECK(arr.getSize()==4);
  check_array(arr,{4,5,6,8},4);
  arr.insert(3,7);
  check_array(arr,{4,5,6,7,8},5);
}

TEST_CASE("Test prepend"){
  DynamicArray arr;
  arr.prepend(5);
  CHECK(arr.getSize()==1);
  CHECK(arr.at(0)==5);
  
  arr.prepend(8);
  CHECK(arr.getSize()==2);
  CHECK(arr.at(0)==8);
  CHECK(arr.at(1)==5);
  arr.prepend(6);

  CHECK(arr.getSize()==3);
  check_array(arr,{6,8,5},3);
}


TEST_CASE("Test resize"){
  DynamicArray arr;
  // Check for proper start capacity
  CHECK(arr.getCapacity()==2);

  // Check for uneccesary resize
  arr.push(5);
  CHECK(arr.getCapacity()==2);
  CHECK(arr.at(0)==5);

  // Check upsize
  arr.push(6);
  arr.push(6);
  CHECK(arr.getCapacity()==4);
  arr.push(6);
  arr.push(8);
  CHECK(arr.getCapacity()==8);
  CHECK(arr.getSize()==5);
  CHECK(arr.at(0)==5);
  CHECK(arr.at(1)==6);
  CHECK(arr.at(2)==6);
  CHECK(arr.at(3)==6);
  CHECK(arr.at(4)==8);
  
  // Check downsize
  arr.pop();
  arr.pop();
  arr.pop();
  arr.pop();
  CHECK(arr.at(0)==5);
  CHECK(arr.getCapacity()==4);
  CHECK(arr.getSize()==1);
}
