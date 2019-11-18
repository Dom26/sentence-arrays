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
Node::Node(Node & to_copy):next(NULL)
{
  word = new char[strlen(to_copy.word) + 1];
  strcpy(word,to_copy.word);
}

// Node destructor
Node::~Node()
{
  if(word != NULL)
    delete[] word;
}

// Node getter
Node *&Node::getNext()
{
  return next;
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

// print the word contained in node
void Node::display_word()
{
  cout << word;
}
// Linear Linked List (LLL) Implementation:

// Array (ARR) Implementation:
