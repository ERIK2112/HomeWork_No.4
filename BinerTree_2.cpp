/*! @file	BinarTree_2.cpp
    @brief	Example of BinarTree.
    
			Example of BinarTree.
			In this programm you can add new element, delete it.
	@author		Niklaus Wirth
    @date		1985
*/


#include<iostream>
using namespace std;
#define TRUE 1
#define FALSE 0


/*! @struct	node
	@brief	Struct for elements of tree.
    @param Count	Value of leaf.
	@param Key		Key&
	@param *Left	Pointer to left son.
	@param *Right	Pointer to right son.
*/
struct  node
{
  int Key;
  int Count;
  node *Left;
  node *Right;
};


class TREE
{
  private:
    node *Tree;							/// root of tree
    node  *Res;							/// pointer to the found vertex
    int B;								/// sign of finding the top of the tree
    void Search (int, node**);			//! search in the top of the tree (recursive algorithm)
    void Delete_1 (node**,node**);
  public:
    TREE() { Tree = NULL;}
    node** GetTree() {return &Tree;}
    void  BuildTree ();					/// create tree
    void Vyvod (node**,int);			/// print tree
    int Poisk (int);					/// find virtex (unrecursive algorithm)
    node *Poisk_1 (int,node **);		/// search in the top of the tree (recursive algorithm)
    void Addition (int);				/// add the vertices in the tree (non-recursive algorithm)
	void Delete (node**, int);			/// delete virtex
};

void main ()
{
  TREE A;
  int el;

  A.BuildTree ();  
  A.Vyvod (A.GetTree(),0);

  cout<<"Enter the key top, you want to find in the tree:";		cin>>el;
  if  (A.Poisk (el)) 
	  cout<<"vertex exists\n";
  else
	  cout<<"vertex non-exists\n";

  cout<<"Enter the key top, you want to find in the tree:";     cin>>el;
  if  (A.Poisk_1 (el,A.GetTree())!=NULL) 
	  cout<<"vertex exists\n";
  else
	  cout<<"vertex non-exists\n";

  cout<<"Enter the key tops added:";	cin>>el;
	  A.Addition (el);  
	  A.Vyvod (A.GetTree(),0);

  cout<<"Enter the key removed the top:";	cin>>el;
	  A.Delete (A.GetTree(),el);  
	  A.Vyvod (A.GetTree(),0);
}

void TREE::BuildTree ()
{
  int el;
  cout<<"Enter the key nodes of the tree:\n";
  cin>>el;
  while  (el!=0)
    { Search (el,&Tree);cin>>el; }
}


/*! @fn		void TREE::Vyvod (node **w,int l)
    @brief	Print tree
			
	@param	node **w	A pointer to the root
	@param	int l
*/
void TREE::Vyvod (node **w,int l)
{
  int i;

  if  (*w!=NULL)
  {
    Vyvod (&((**w).Right),l+1);
    for  (i=1; i<=l; i++) cout<<"   ";
    cout<<(**w).Key<<endl;
    Vyvod (&((**w).Left),l+1);
  }
}


/*! @fn		void TREE::Search (int x,node **p)
    @brief	Search link x in a binary tree with inset
			
	@param	node **p	A pointer to the root
	@param	int x
*/
void TREE::Search (int x,node **p)
{
  if  (*p==NULL)						/// The top of the tree there, turn it on
  { 
    *p = new(node);
    (**p).Key = x;     (**p).Count = 1;
    (**p).Left = (**p).Right = NULL;
  }
  else
	  if  (x<(**p).Key) Search (x,&((**p).Left));
  else
	  if  (x>(**p).Key) Search (x,&((**p).Right));
	  else  (**p).Count += 1;
}


/*! @fn		void TREE::Addition (int k)
    @brief	Search link k in a binary tree with inset
			
	@param	int k
*/
void TREE::Addition (int k)
{
  node *s;

  Poisk (k);
  if  (!B)
  {
    s = new(node);
    (*s).Key  = k;    (*s).Count = 1;
    (*s).Left = (*s).Right = NULL;
    if  (Tree==NULL) Tree = s;
    else
      if  (k<(*Res).Key) (*Res).Left = s;
      else  (*Res).Right = s;
  }
  else  (*Res).Count += 1;
}


/*! @fn		void TREE::Addition (int k)
    @brief	Search virtex with link k

	@param	int k		
	@return	int B
*/
int TREE::Poisk (int k)
{
  node *p;
  node *q;

  B = FALSE; 
  p = Tree;								/// pointer to tree
  if  (Tree!=NULL)
  do
  {
    q = p;
    if  ((*p).Key==k) B = TRUE;
    else
      {
       q = p;
       if  (k<(*p).Key) p = (*p).Left;
       else  p = (*p).Right;
      }
  } while  (!B && p!=NULL);
  Res = q;								/// virtex
  return B;
}


/*! @fn		node *TREE::Poisk_1 (int k,node **p)
    @brief	Search virtex with link k
			
	@param	node **p	Pointer to root
	@param	int k
*/
node *TREE::Poisk_1 (int k,node **p)
{
  if  (*p==NULL) return (NULL);
  else
	 if  ((**p).Key==k) return (*p);
	 else
           if  (k<(**p).Key) return Poisk_1 (k,&((**p).Left));
           else return Poisk_1 (k,&((**p).Right));
}


/*! @fn		node *TREE::Poisk_1 (int k,node **p)
    @brief	Search virtex with link k
			
	@param	node **p	Pointer to root
	@param	int k
*/
void TREE::Delete (node **p,int k)
{
  node *q;

  if  (*p==NULL) cout<<"top with the specified key is not found\n";
  else
	 if  (k<(**p).Key) Delete (&((**p).Left),k);
	 else
		if  (k>(**p).Key) Delete (&((**p).Right),k);
		else
		  {
                    q = *p;
                    if  ((*q).Right==NULL) {*p = (*q).Left; delete q;}
                    else
                     if  ((*q).Left==NULL) { *p = (*q).Right; delete q; }
                     else  Delete_1 (&((*q).Left),&q);
		  }
}


/*! @fn		void TREE::Delete_1 (node **r,node **q)
    @brief	Delete leaf
			
	@param	node **r	Pointer to ...
	@param	node **q	Pointer to ...
*/
void TREE::Delete_1 (node **r,node **q)
{
  node *s;

  if  ((**r).Right==NULL)
  {
    (**q).Key = (**r).Key; (**q).Count = (**r).Count;
    *q = *r;
    s = *r; *r = (**r).Left; delete s;
  }
  else  Delete_1 (&((**r).Right), q);
}
