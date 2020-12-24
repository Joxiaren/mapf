#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<queue>
#include<map>

#include "auxilary.hpp"
#include "walker.hpp"
#include "bfs.hpp"


using namespace std;

short** mazeInput(string mazeName, short* mazeN, short* mazeM);
void mazeDisplay(short mazeN, short mazeM, short** maze);
bool findStartEnd(struct coordinates* sC, struct coordinates* eC, short n, short m, short** maze);

int main(int argn, char* argv[])
{ 
    short mazeN, mazeM;
    string mazeName = "maze0.txt";

    short** maze = mazeInput(mazeName, &mazeN, &mazeM);

    struct coordinates startCoord, endCoord;

    if(!findStartEnd(&startCoord, &endCoord, mazeN, mazeM, maze)) return 0;

    mazeDisplay(mazeN, mazeM, maze);

    Walker Mirko("Mirko", startCoord);

    Mirko.setPath(BFS(Mirko.getPosition(), endCoord, mazeN, mazeM, maze));
    Mirko.readOutPath();


    return 0;    
}

short** mazeInput(string mazeName, short* n, short* m)
{
    ifstream fin;
    fin.open(mazeName);
    
    fin>>*n>>*m;

    short** maze;
    maze = new short*[*n];
    for(int j = 0; j < *n; j++) maze[j] = new short[*m];

    for(int j = 0; j < *n; j++) for(int jj = 0; jj < *m; jj++) fin>>maze[j][jj];

   fin.close();

   return maze;
}

void mazeDisplay(short mazeN, short mazeM, short** maze)
{
    map<short, unsigned char> mazeToDisplay;
    mazeToDisplay.insert(pair<short, unsigned char>(0, (unsigned char)(176)));
    mazeToDisplay.insert(pair<short, unsigned char>(1, (unsigned char)(219)));
    mazeToDisplay.insert(pair<short, unsigned char>(2, 'S'));
    mazeToDisplay.insert(pair<short, unsigned char>(3, 'E'));
    mazeToDisplay.insert(pair<short, unsigned char>(11, 'w'));
    mazeToDisplay.insert(pair<short, unsigned char>(12, 'x'));
    mazeToDisplay.insert(pair<short, unsigned char>(14, 'a'));
    mazeToDisplay.insert(pair<short, unsigned char>(15, 'q'));
    mazeToDisplay.insert(pair<short, unsigned char>(16, 'z'));
    mazeToDisplay.insert(pair<short, unsigned char>(18, 'd'));
    mazeToDisplay.insert(pair<short, unsigned char>(19, 'e'));
    mazeToDisplay.insert(pair<short, unsigned char>(20, 'c'));
    
    for(int j = 0; j < mazeN; j++)
    {
        for(int jj = 0; jj < mazeM; jj++) cout<<mazeToDisplay[maze[j][jj]];
        cout<<endl;
    }
    cout<<endl;
}

bool findStartEnd(struct coordinates* sC, struct coordinates* eC, short n, short m, short** maze)
{
    sC -> x = -1;
    sC -> y = -1;
    eC -> x = -1;
    eC -> y = -1;
    // im typing something
    for(int j = 0; j < n; j++)
    {
        for(int jj = 0; jj < m; jj++)
        {
            if(maze[j][jj] == 2)
            {
                if(sC -> x == -1)
                {
                    sC -> x = jj;
                    sC -> y = j;
                }
                else 
                {
                    cout<<"Multiple start position error"<<endl;
                    return false;
                }
            }
            else if(maze[j][jj] == 3)
            {
                if(eC -> x == -1)
                {
                    eC -> x = jj;
                    eC -> y = j;
                }
                else
                {
                    cout<<"Multiple end position error"<<endl;
                    return false;
                }
            }
        }
    }
    if(sC->x != -1 && eC->x != -1) return true;
    else
    {
        cout<<"Couldnt find start or end"<<endl;
        return false;
    }
}



