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
        int *matrix;
        int boardSize;
        int totalCell;
        int totalSteps;
        int lastChange;
        time_t t;
    public:
        Base2048(int);
        int randomBinary();
        int randomCell();
        void displayBoard();
        int start();
        void moveGrid(char);
        void processInput(char);
        int addVal(int);
        int finalScore();
        int isCellEmpty(int*,int,int);
        void addCell(int*,int,int,int,int);
        void moveCell(int*,int,int,int,int,int,int);
};
Base2048::Base2048(int n){
    lastChange = boardSize = n;
    totalSteps = 0;
    srand((unsigned) time(&t));
    totalCell = boardSize*boardSize;
    matrix = (int*)malloc(sizeof(int)*totalCell);
    for(int i=0;i<totalCell;*(matrix+i++)=0);
}
int Base2048::randomBinary(){
    return (rand()%2)? 2 : 4;
}
int Base2048::randomCell(){
    return rand()%totalCell;
}
void Base2048::displayBoard(){
    for(int i=0;i<boardSize;++i){
        for(int j=0;j<boardSize;++j)
            cout<<*(matrix+i*boardSize+j)<<"\t";
        cout<<endl<<endl;
    }
}
int Base2048::addVal(int val){
    if(lastChange==0) return 1;
    int index=randomCell();
    int tmp = index;
    while(matrix[tmp]!=0 && tmp!=(index-1)%totalCell)
        tmp = (tmp+1)%totalCell;
    return (matrix[tmp])? 0: (matrix[tmp]=val);
}
int Base2048::isCellEmpty(int *matrix,int i,int j){
    return (*(matrix+i*boardSize+j))? 0 : 1;
}
void Base2048::addCell(int *matrix,int i,int j,int k,int l){
    *(matrix+i*boardSize+j) += *(matrix+k*boardSize+l);
    *(matrix+k*boardSize+l)=0;
    ++lastChange;
}
void Base2048::moveCell(int *matrix,int i,int j,int k,int l,int m,int n){
    if(m==n) return;
    *(matrix+i*boardSize+j) = *(matrix+k*boardSize+l);
    *(matrix+k*boardSize+l)=0;
    ++lastChange;
}
void Base2048::moveGrid(char ch){
    int t1;
    ++totalSteps;
    lastChange = 0;
    if(ch=='K'){//Left
        for(int i=0;i<boardSize;++i){
            t1=0;
            for(int j=1;j<boardSize;++j){
                if(isCellEmpty(matrix,i,j)) continue;
                else if(*(matrix+i*boardSize+t1)==*(matrix+i*boardSize+j))
                    addCell(matrix,i,t1++,i,j);
                else if(*(matrix+i*boardSize+t1)==0)
                    moveCell(matrix,i,t1,i,j,t1,j);
                else moveCell(matrix,i,++t1,i,j,t1,j);
            }
        }
    }else if(ch=='H'){//Up
            for(int i=0;i<boardSize;++i){
                t1=0;
                for(int j=1;j<boardSize;++j){
                    if(isCellEmpty(matrix,j,i)) continue;
                    else if(*(matrix+t1*boardSize+i)==*(matrix+j*boardSize+i))
                        addCell(matrix,t1++,i,j,i);
                    else if(*(matrix+t1*boardSize+i)==0)
                        moveCell(matrix,t1,i,j,i,t1,j);
                    else moveCell(matrix,++t1,i,j,i,t1,j);
                }
            }
    }else if(ch=='P'){//Down
        for(int i=boardSize-1;i>=0;--i){
                t1=boardSize-1;
                for(int j=boardSize-2;j>=0;--j){
                    if(isCellEmpty(matrix,j,i)) continue;
                    else if(*(matrix+t1*boardSize+i)==*(matrix+j*boardSize+i))
                        addCell(matrix,t1--,i,j,i);
                    else if(*(matrix+t1*boardSize+i)==0)
                        moveCell(matrix,t1,i,j,i,t1,j);
                    else moveCell(matrix,--t1,i,j,i,t1,j);
                }
        }
    }else if(ch=='M'){//Right
        for(int i=boardSize-1;i>=0;--i){
            t1=boardSize-1;
            for(int j=boardSize-2;j>=0;--j){
                if(isCellEmpty(matrix,i,j)) continue;
                else if(*(matrix+i*boardSize+t1)==*(matrix+i*boardSize+j))
                    addCell(matrix,i,t1--,i,j);
                else if(*(matrix+i*boardSize+t1)==0)
                    moveCell(matrix,i,t1,i,j,t1,j);
                else moveCell(matrix,i,--t1,i,j,t1,j);
            }
        }
    }
}
void Base2048::processInput(char ch){
    if((ch == 'H' || ch == 'K' || ch == 'P' || ch == 'M'))
        moveGrid(ch);
    else processInput(getch());
}
int Base2048::finalScore(){
    int score = 0;
    for(int i=0;i<totalCell;score+=*(matrix+i++));
    cout<<"Steps : "<<totalSteps<<endl<<"Score : "<<score<<endl;
    return score;
}
int Base2048::start(){
    int t;
    do{
        t = 0;
        if(!addVal(randomBinary())&&!addVal(randomBinary()))
            return 0;
        system(CLEAR);
        displayBoard();
        processInput(getch());
    }while(1);
}
int main(){
    Base2048 table(4);
    table.start();
    table.finalScore();
    getch();
    return 0;
}
