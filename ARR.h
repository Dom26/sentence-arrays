/*
  ARR.h
  Header file for the array of Linear linked lists
  Dominique Moore
*/

const int MAX = 3;

class Node{
  public:
    Node();
    Node(char*);
    Node(const Node&);
    ~Node();
    Node& operator=(const Node&);
    Node *&getNext();
    void setNext(Node*&,int);
    int set_word(char*);
    int change_word(char*);
    void display_word();
  private:
    Node *next;
    char *word;
};

class LLL{
  public:
    LLL();
    LLL(const LLL&);
    ~LLL();
    int check_list();
    int insert(char*);
    int destroy_list();
    int copy_list(const LLL&);
    void display_list();
  private:
    Node *head;
    Node *tail;
    int destroy_list(Node*&);
    int copy_list(Node*&,Node*);
    void display_list(Node*);
};
class ARR{
  public:
    ARR();
    ARR(int);
    ARR(const ARR&);
    ~ARR();
    int insert(char*);
    int remove_sentence(int);
    void display_array();
  private:
    LLL * list;
    int size;
    int read_sentence(char*,int);
    int insert_to_list(char*,int,int,int);
    int destroy_array();
};
