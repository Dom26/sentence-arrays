/*
  ARR.cpp
  Implementation file for array of linear linked lists
  Dominique Moore
*/

#include "ARR.h"
#include <cstdlib>
#include <iostream>
#include <cstring>

using namespace std;

const int NUM_OF_LETTERS = 512;

// Node Implementation:

// Node default constructor
Node::Node():next(NULL),word(NULL)
{}

// Node constructor w/arg.
Node::Node(char * w):next(NULL)
{
  word = new char[strlen(w) + 1];
  strcpy(word,w);
}

// Node copy constructor
Node::Node(const Node & to_copy):next(NULL)
{
  word = new char[strlen(to_copy.word) + 1];
  strcpy(word,to_copy.word);
}

// Node destructor
Node::~Node()
{
  if(word)
    delete[] word;
}

// overloaded assignment
Node& Node::operator=(const Node& to_copy)
{
  if(word != NULL)
    delete[] word;
  word = new char[strlen(to_copy.word)+1];
  strcpy(word,to_copy.word);
  return *this;
}
// Node getter
Node *&Node::getNext()
{
  return next;
}

// Node setter for next pointer
void Node::setNext(Node*& connector,int not_tail)
{
  // connector is the Node that next should equal.
  // If the int isn't zero then we want to set next
  // to the passed in Node, else we are the tail of
  // a list and tail's next should point to NULL.
  if(not_tail)
    next = connector;
  else
    next = NULL;
}
// word setter
int Node::set_word(char *w)
{
  if(w == NULL)
    return 0;
  if(word != NULL)
    delete[] word;
  word = new char[strlen(w)+1];
  strcpy(word,w);
  return 1;
}

// Node function to change the word
int Node::change_word(char * w)
{
  if(w == NULL)
    return 0;
  if(word != NULL)
    delete[] word;
  word = new char[strlen(w)+1];
  strcpy(word,w);
  return 1;
}
// print the word contained in node
void Node::display_word()
{
  if(!word)
    return;
  cout << word;
}
// Linear Linked List (LLL) Implementation:
// LLL default constructor
LLL::LLL():head(NULL),tail(NULL)
{}

// LLL copy constructor
LLL::LLL(const LLL& cpy_lst):head(NULL),tail(NULL)
{
  copy_list(head,cpy_lst.head);
}

// LLL destructor
LLL::~LLL()
{
  destroy_list(head);
}

int LLL::check_list()
{
  if(!head)
    return 0;
  return 1;
}

// LLL insertion by tail
int LLL::insert(char* w)
{
  if(!head)                 // check for empty list
  {
    head = new Node(w);
    head->setNext(tail,1);    // set the next pointer for head
  }
  else if(!tail)            // check for only one item in list
  {
    tail = new Node(w);
    head->setNext(tail,1);
  }
  else                      // insert at tail
  {
    Node * temp = new Node(w);
    tail->setNext(temp,1);  // connect new Node to end of list
    tail = temp;            // set tail to the end of the list
    tail->setNext(temp,0);  // set tail's next to NULL
  }
  return 1;
}

// function to deallocate the LLL
int LLL::destroy_list()
{
  if(!head)
    return 0;
  return destroy_list(head);
}

// recursively deallocate LLL
int LLL::destroy_list(Node*& cur)
{
  if(!cur)
    return 0;
  int destroyed = 0;
  destroyed += destroy_list(cur->getNext());
  delete cur;
  cur = NULL;
  return destroyed;
}

// copy list from passed in LLL
int LLL::copy_list(const LLL& copy)
{
  if(!copy.head) // No copying an empty list
    return 0;
  return copy_list(head,copy.head);
}

// recursively copy each node
int LLL::copy_list(Node*& cur,Node* to_copy)
{
  // Base case:
  // Check if everything has been copied
  if(!to_copy)
  {
    // Check if the cur list has more items
    if(cur->getNext() == NULL)
    {
      tail = cur;
      tail->setNext(cur,0);
    }
    return 0;
  }
  int copied = 0;
  if(!cur)
  {
    // Call Node copy constructor
    cur = new Node(*to_copy);
    copied += copy_list(cur->getNext(),to_copy->getNext());
  }
  else
  {
    // Call Node overloaded assignment operator
    cur = to_copy;
    copied += copy_list(cur->getNext(),to_copy->getNext());
  }
  return 1;
}

// Display LLL contents
void LLL::display_list()
{
  if(!head)
    return;
  display_list(head);
}

// Recursively display LLL
void LLL::display_list(Node *cur)
{
  if(!cur)
    return;
  if(cur == tail)
  {
    if(!cur)
      cout << endl;
    else
    {
      cur->display_word();
      cout << endl;
    }
  }
  else
  {
    cur->display_word();
    cout << " ";
    display_list(cur->getNext());
  }
}
// Array (ARR) Implementation:
// array default constructor
ARR::ARR():size(MAX)
{
  list = new LLL[size];
}

// initialize array size
ARR::ARR(int sz):size(sz)
{
  list = new LLL[size];
}

// array copy constructor
ARR::ARR(const ARR& to_copy):size(to_copy.size)
{
  list = new LLL[size];
}

// array destructor
ARR::~ARR()
{
  destroy_array();
}

// inserting into the array
// the passed in char* is a sentence
// that was typed by the user
int ARR::insert(char* sentence)
{
  if(!sentence)
    return 0;
  int inserted = 0;
  // only insert into empty array index
  // i.e. where list is NULL
  for(int i=0;(i<size) && (!inserted);++i)
  {
    if(list[i].check_list() == 0)
    {
      read_sentence(sentence,i);
      inserted = 1;
    }
  }
  return inserted;
}

// breaks sentence into individual words and calls
// an insertion function for the LLL.
int ARR::read_sentence(char* sentence,int list_num)
{
  int place_holder = 0;
  int first_letter = 0;
  int adds = 0;
  int length = strlen(sentence);
  char word[NUM_OF_LETTERS];

  for(int j=0;j<NUM_OF_LETTERS;++j)
    word[j] = ' ';

  for(int i=0;i < length;++i)
  {
    if(sentence[i] == ' ')
    {
      // Call a function that takes the word out of the
      // sentence
      adds += insert_to_list(word,list_num,first_letter,place_holder);
      // clear the "word" for reuse
      // No need to set word[0] to ' ' because
      // it will get overwritten
      for(;place_holder>0;--place_holder)
        word[place_holder] = ' ';
      //first_letter = place_holder;
    }
    else if(i == (length-1))
    {
      word[place_holder] = sentence[i];
      ++place_holder;
      adds += insert_to_list(word,list_num,first_letter,place_holder);
    }
    else
    {
      word[place_holder] = sentence[i];
      ++place_holder;
    }
  }
  return 1;
}

// take a word out of a sentence and insert in list
// start is where the word begins and end is where
// the word ends.
int ARR::insert_to_list(char* sentence,int list_num,int start,int end)
{
  int length = (end - start) + 1;
  // end - start = difference between first and last letter
  // + 2 = the last letter and the null terminating character
  int j = 0;
  char word[length];

  for(int k=0;k<length;++k)
    word[k] = ' ';

  for(int i=start;i<end;++i)
  {
    word[j] = sentence[i];
    ++j;
  }
  // Give word the null terminating character
  word[length-1] = '\0'; 
  return list[list_num].insert(word);
}

// search for a list and call a list function
// to delete that list
int ARR::remove_sentence(int to_remove)
{
  // Checking that the passed in number is within range
  if(to_remove < 0 || to_remove >= size)
    return 0;
  int removed = 0;
  for(int i=0;(i<size) && (!removed);++i)
  {
    if(i == to_remove)
    {
      list[i].destroy_list();
      removed = 1;
    }
  }
  return removed;
}

// Deallocate array function
int ARR::destroy_array()
{
  int destroyed = 0;
  for(int i=0;i<size;++i)
  {
    if(list[i].check_list() != 0)
      destroyed += list[i].destroy_list();
  }
  delete[] list;
  return destroyed;
}

// Display the sentences
void ARR::display_array()
{
  for(int i=0;i<size;++i)
  {
    if(list[i].check_list() != 0)
      list[i].display_list();
  }
}
