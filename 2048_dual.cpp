#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include <time.h>
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif
using namespace std;
class Base2048{
    private:
        int *matrix[2];
        int boardSize;
        int totalCell;
        int totalSteps;
        int nRand;
        int nGrid;
        time_t t;
        void initGrid(int*);
        int randomBinary();
        int randomCell();
        void displayBoard(int*);
        void displayBoard();
        int moveGrid(char,int*);
        int moveGrid(char);
        int processInput(char);
        int addVal(int,int*);
        int addVal();
        int finalScore(int*);
        int finalScore();
        int canMove(int*);
        int canMove();
        int isCellEmpty(int*,int,int);
        void addCell(int*,int,int,int,int,int*);
        void moveCell(int*,int,int,int,int,int,int,int*);
    public:
        Base2048(int,int=1,int=1);
        int start();
};
Base2048::Base2048(int gSize,int nG,int nR){
    boardSize = gSize;
    nGrid = nG;
    nRand = nR;
    totalSteps = 0;
    srand((unsigned) time(&t));
    totalCell = boardSize*boardSize;
    initGrid(matrix[0] = (int*)malloc(sizeof(int)*totalCell));
    if(nGrid == 2) initGrid(matrix[1] = (int*)malloc(sizeof(int)*totalCell));
}
void Base2048::initGrid(int *matrix){
    for(int i=0;i<totalCell;*(matrix+i++)=0);
}
int Base2048::randomBinary(){
    return (rand()%2)? 2 : 4;
}
int Base2048::randomCell(){
    return rand()%totalCell;
}
void Base2048::displayBoard(int *matrix){
    cout<<"\n\n\n\n\n";
    for(int i=0;i<boardSize;++i){
        for(int j=0;j<boardSize;++j)
            cout<<*(matrix+i*boardSize+j)<<"\t";
        cout<<endl<<endl;
    }
}
int Base2048::addVal(int val,int *matrix){
    int index=randomCell();
    int tmp = index;
    while(matrix[tmp]!=0 && tmp!=(index-1)%totalCell)
        tmp = (tmp+1)%totalCell;
    return (matrix[tmp])? 0: (matrix[tmp]=val);
}
int Base2048::canMove(int *matrix){
    int t = boardSize-1;
    for(int i=0;i<t;++i)
        for(int j=0;j<t;++j)
            if(*(matrix+i*boardSize+j)==*(matrix+i*boardSize+j+1) || *(matrix+i*boardSize+j)==*(matrix+i+1*boardSize+j) || *(matrix+i*boardSize+j)==0)
                return 1;
    for(int i=0;i<t;++i)
        if(*(matrix+t*boardSize+i)==*(matrix+t*boardSize+i+1) || *(matrix+i*boardSize+t)==*(matrix+i+1*boardSize+t) || *(matrix+i*boardSize+t)==0 || *(matrix+t*boardSize+i) ==0 )
            return 1;
    if(*(matrix+t*boardSize+t)==0) return 1;
    return 0;
}
int Base2048::isCellEmpty(int *matrix,int i,int j){
    return (*(matrix+i*boardSize+j))? 0 : 1;
}
void Base2048::addCell(int *matrix,int i,int j,int k,int l,int *lastChange){
    *(matrix+i*boardSize+j) += *(matrix+k*boardSize+l);
    *(matrix+k*boardSize+l)=0;
    ++*lastChange;
}
void Base2048::moveCell(int *matrix,int i,int j,int k,int l,int m,int n,int *lastChange){
    if(m==n) return;
    *(matrix+i*boardSize+j) = *(matrix+k*boardSize+l);
    *(matrix+k*boardSize+l)=0;
    ++*lastChange;
}
int Base2048::moveGrid(char ch,int *matrix){
    int t1;
    int lastChange = 0;
    if(ch=='K'){//Left
        for(int i=0;i<boardSize;++i){
            t1=0;
            for(int j=1;j<boardSize;++j){
                if(isCellEmpty(matrix,i,j)) continue;
                else if(*(matrix+i*boardSize+t1)==*(matrix+i*boardSize+j))
                    addCell(matrix,i,t1++,i,j,&lastChange);
                else if(*(matrix+i*boardSize+t1)==0)
                    moveCell(matrix,i,t1,i,j,t1,j,&lastChange);
                else moveCell(matrix,i,++t1,i,j,t1,j,&lastChange);
            }
        }
    }else if(ch=='H'){//Up
            for(int i=0;i<boardSize;++i){
                t1=0;
                for(int j=1;j<boardSize;++j){
                    if(isCellEmpty(matrix,j,i)) continue;
                    else if(*(matrix+t1*boardSize+i)==*(matrix+j*boardSize+i))
                        addCell(matrix,t1++,i,j,i,&lastChange);
                    else if(*(matrix+t1*boardSize+i)==0)
                        moveCell(matrix,t1,i,j,i,t1,j,&lastChange);
                    else moveCell(matrix,++t1,i,j,i,t1,j,&lastChange);
                }
            }
    }else if(ch=='P'){//Down
        for(int i=boardSize-1;i>=0;--i){
                t1=boardSize-1;
                for(int j=boardSize-2;j>=0;--j){
                    if(isCellEmpty(matrix,j,i)) continue;
                    else if(*(matrix+t1*boardSize+i)==*(matrix+j*boardSize+i))
                        addCell(matrix,t1--,i,j,i,&lastChange);
                    else if(*(matrix+t1*boardSize+i)==0)
                        moveCell(matrix,t1,i,j,i,t1,j,&lastChange);
                    else moveCell(matrix,--t1,i,j,i,t1,j,&lastChange);
                }
        }
    }else if(ch=='M'){//Right
        for(int i=boardSize-1;i>=0;--i){
            t1=boardSize-1;
            for(int j=boardSize-2;j>=0;--j){
                if(isCellEmpty(matrix,i,j)) continue;
                else if(*(matrix+i*boardSize+t1)==*(matrix+i*boardSize+j))
                    addCell(matrix,i,t1--,i,j,&lastChange);
                else if(*(matrix+i*boardSize+t1)==0)
                    moveCell(matrix,i,t1,i,j,t1,j,&lastChange);
                else moveCell(matrix,i,--t1,i,j,t1,j,&lastChange);
            }
        }
    }
    return lastChange;
}
int Base2048::moveGrid(char ch){
    return (moveGrid(ch,matrix[0]) && moveGrid(ch,matrix[1]));
}
int Base2048::processInput(char ch){
    return ((ch == 'H' || ch == 'K' || ch == 'P' || ch == 'M'))? moveGrid(ch)? 1 : processInput(getch()) : processInput(getch());
}
int Base2048::finalScore(int *matrix){
    int score = 0;
    for(int i=0;i<totalCell;score+=*(matrix+i++));
    return score;
}
int Base2048::finalScore(){
    int score = finalScore(matrix[0]) + finalScore(matrix[1]);
    cout<<"Steps : "<<totalSteps<<endl<<"Score : "<<score<<endl;
    return score;
}
int Base2048::addVal(){
    for(int i=0;i<nRand;++i){
        addVal(randomBinary(),matrix[0]);
        addVal(randomBinary(),matrix[1]);
    }
    return 1;
}
void Base2048::displayBoard(){
    system(CLEAR);
    displayBoard(matrix[0]);
    displayBoard(matrix[1]);
}
int Base2048::canMove(){
    return (!canMove(matrix[0]) || !canMove(matrix[1]));
}
int Base2048::start(){
    do{
        addVal();
        displayBoard();
        if(canMove()) return finalScore();
        processInput(getch());
        ++totalSteps;
    }while(1);
}
int main(){
    Base2048 Grid(4,2,1); //Grid Size, Number of Grid, number of Random Numbers
    Grid.start();
    getch();
    return 0;
}
