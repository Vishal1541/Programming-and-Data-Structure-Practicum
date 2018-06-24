#ifndef _SM_h
#define _SM_h

typedef struct sparseMat{
int col;
int row;
float value;
}SMatrix;



void print(SMatrix *);
void sort(SMatrix* );
SMatrix* Create(int ,int ,int );
void insertSM(SMatrix *,int ,int ,float );
void deleteSM(SMatrix *,int,int);
SMatrix* transpose (SMatrix *);
float getvalue(SMatrix *,int ,int );
#endif
