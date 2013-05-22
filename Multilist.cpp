/*! @file	Multilist.cpp
    @brief	Example of multilist.
    
    @version	0.1
    @date		22 may 2013 18:12
	@author		Friends :)
*/

#pragma once
#include <string>
#include <list>
#include <iostream>
#include <conio.h>
#include <iostream>
using namespace std;


/*! @class	Xnode
    @brief	Contains a record of the student's name, subject and their indices.
*/
class Xnode
{
public:
	Xnode()
		:pupil(-1)
		,subject(-1)
		,pPupil(-1)
		,pSubject(-1)	{}
	int pupil;
	int subject;
	int pPupil;
	int pSubject;
};


/*! @class	MultiList
*/
class MultiList
{
private:
	int pupilsCount;
	int subjectsCount;
	int Xcount;								/// num of entries
	char** pupils;							/// mass of pupils
	char** subjects;						/// mass of subjects
	int** linkTable;						/// mass of communication between the student and the subject
	Xnode* nodes;							/// mass of entries
public:
	//! Constructor
	MultiList():Xcount(0){
	}
	//! Desstructor
	~MultiList(){
	}
	PupilsCount();
	SubjectsCount();
	Pupils();
	Subjects();
	LinkTable();
	GetPupilsOnSubject(char* subject);
	GetSubjectsOnPupil(char* pupil);
	SetSubjects(char** arr, int count);
	SetPupils(char** arr, int count);
	SetLinks(int **lTable);
};



/*! @fn		int MultiList::PupilsCount()
    @brief	Return number of students.
    
	@return	int pupilsCount	Number of students.
*/
int MultiList::PupilsCount()
{
	return pupilsCount;
}


/*! @fn		int MultiList::SubjectsCount()
    @brief	Return number of subjects.
    
	@return	int subjectsCount	Number of subjects.
*/
int MultiList::SubjectsCount()
{
	return subjectsCount;
}


/*! @fn		char** MultiList::Pupils()
    @brief	Return of pupils'es names array.
    
	@return	char **pupils	Pointer to array.
*/
char** MultiList::Pupils()
{
	return pupils;
}


/*! @fn		char** MultiList::Subjects()
    @brief	Return of pupils'es subjects array.
    
	@return	char **subjects	Pointer to array.
*/
char** MultiList::Subjects()
{
	return subjects;
}


/*! @fn		char** MultiList::Subjects()
    @brief	Return link table.
    
	@return	int **linkTable	Pointer to linkTable.
*/
int** MultiList::LinkTable()
{
	return linkTable;
}


/*! @fn		list<char*> MultiList::GetPupilsOnSubject(char* subject)
    @brief	Make list of pupils sorted by subject.
     
	@param	char* subject		Pointer to subjects array
	@return	list<char*> result	Pointer to first element.
*/
list<char*> MultiList::GetPupilsOnSubject(char* subject)
{
	list<char*> result;
	int i;
	int k;
	for (i = 0; i < subjectsCount; ++i)	if (subjects[i] == subject)	break;
	for (k = 0; k < Xcount; ++k) if (nodes[k].subject == i) break;
	Xnode curNode = nodes[k];
	result.push_back(pupils[curNode.pupil]);
	while (curNode.pPupil !=-1)
	{
		curNode = nodes[curNode.pPupil];
		result.push_back(pupils[curNode.pupil]);
	}
	return result; 
}


/*! @fn		list<char*> MultiList::GetSubjectsOnPupil(char* pupil)
    @brief	Make list of subjects sorted by pupils.
     
	@param	char* pupil			Pointer to pupil array
	@return	list<char*> result	Pointer to first element.
*/
list<char*> MultiList::GetSubjectsOnPupil(char* pupil)
{
	list<char*> result;
	int i;
	int k;
	for (i = 0; i < pupilsCount; ++i)	if (pupils[i] == pupil)	break;
	for (k = 0; k < Xcount; ++k) if (nodes[k].pupil == i) break;
	Xnode curNode = nodes[k];
	result.push_back(subjects[curNode.subject]);
	while (curNode.pSubject !=-1)
	{
		curNode = nodes[curNode.pSubject];
		result.push_back(subjects[curNode.subject]);
	}
	return result; 
}


/*! @fn		void MultiList::SetSubjects(char** arr, int count)
    @brief	Set name of subject
     
	@param	char** arr	Pointer to pointer to array of subjects
*/
void MultiList::SetSubjects(char** arr, int count)
{
	subjects = arr;
	subjectsCount = count;
}


/*! @fn		void MultiList::SetPupils(char** arr, int count)
    @brief	Set name of pupil
     
	@param	char** arr	Pointer to pointer to array of pupils
*/
void MultiList::SetPupils(char** arr, int count)
{
	pupils = arr;
	pupilsCount = count;
}


/*! @fn		void MultiList::SetLinks(int **lTable)
    @brief	Set link table
     
	@param	int **lTable	Pointer to pointer to array of link table
*/
void MultiList::SetLinks(int **lTable)
{
	linkTable = lTable;		
	nodes = new Xnode[Xcount];	
	int k = 0;
	for (int i = 0; i < subjectsCount; ++i)
	{
		for (int j = 0; j < pupilsCount; ++j)
		{
			if (linkTable[i][j])
			{
				nodes[k].pupil = j;
				nodes[k].subject = i;
				++k;
				++Xcount;			
			}
		}		
	}
	for(int k = 0; k < Xcount; ++k)
	{
		nodes[k].pPupil = -1;
		nodes[k].pSubject = -1;		
	}
	for(int k = 0; k < Xcount; ++k)
	{
		for (int i = k + 1; i < Xcount; ++i) 
		{
			if (nodes[i].subject == nodes[k].subject) 
			{
				nodes[k].pPupil = i;
				break;
			}
		}
		for (int i = k + 1; i < Xcount; ++i)
		{
			if (nodes[i].pupil == nodes[k].pupil)
			{
				nodes[k].pSubject = i;
				break;
			}
		}
	}		
}


void main()
{	
	
	MultiList ml;						/// new element of class MultyList
	//! Create arrays
	const int subjectsCount = 3;
	const int pupilsCount = 6;
	char* subjectsArr[subjectsCount] =	{"Fizika", "Fizkultura", "Matematika"};
	char* pupilsArr[pupilsCount] =		{"Sergey", "Valeriy", "Sveta", "Katya", "Alexander", "Kristina"};	
	//! Link table
	bool _lTable[subjectsCount][pupilsCount] =
    {
        {1,0,1,1,0,0},
        {1,0,0,1,0,1},
        {1,1,0,0,1,0}
    };
	int** lTable = new int*[subjectsCount];
	for (int i = 0; i < subjectsCount; ++i)
	{
		lTable[i] = new int[pupilsCount];
		for (int j = 0; j < pupilsCount; ++j)
		{
			lTable[i][j] = _lTable[i][j];
		}
	}

	//! Set pupils, subjects, link table
	ml.SetSubjects(subjectsArr, subjectsCount);
	ml.SetPupils(pupilsArr, pupilsCount);
	ml.SetLinks(lTable);

	cout<<"Subjects: "<<endl;
	for (int i = 0; i < subjectsCount; ++i) 
		cout<<i<<". "<<subjectsArr[i]<<endl;

	cout<<endl<<"Pupils: "<<endl;
	for (int i = 0; i < pupilsCount; ++i) 
		cout<<i<<". "<<pupilsArr[i]<<endl;

	cout<<endl<<"Link Table: "<<endl;
	for (int i = 0; i < subjectsCount; ++i)
	{
		for (int j = 0; j < pupilsCount; ++j)
			cout<<ml.LinkTable()[i][j]<<"\t"
		cout<<endl<<endl;
	}

	
	list<char*> res = ml.GetPupilsOnSubject("Fizika");
	cout<<endl<<"Pupils on Fizika: "<<"\t";
	for (auto it = res.begin(); it != res.end(); it++)
		cout<<*it<<", ";

	cout<<endl<<endl<<"Subject on Sergey: "<<"\t";
	res = ml.GetSubjectsOnPupil("Sergey");
	for (auto it = res.begin(); it != res.end(); it++)
		cout<<*it<<", ";

	cout<<endl<<endl;
	system("PAUSE");
}