#pragma once

class DynamicArray
{

public:
  DynamicArray();

  int getSize();
  int getCapacity();
  bool isEmpty();
  int at(int index);
  void push(int item);
  void insert(int index,int item); 
  void prepend(int item);
  int pop();
  
  void remove(int item);
  void find(int item);


private:
  int* arr;
  int size;
  int capacity;

  void resize(int newCapacity);

};
