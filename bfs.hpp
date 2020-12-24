#ifndef DEFINE_BFS
#define DEFINE_BFS

#include<queue>

#include "walker.hpp"
#include "auxilary.hpp"

bool validJump(struct coordinates check, short n, short m, bool diagonal, int j, int jj)
{
    if(j || jj)
        if(check.y >= 0 && check.y <= n-1 && check.x >= 0 && check.x <= m-1)
            if(diagonal ||(!j || !jj)) return true;
    return false;
}

void tempMazeDisplay(short mazeN, short mazeM, unsigned short** maze)
{
    map<short, unsigned char> mazeToDisplay;
    mazeToDisplay.insert(pair<short, unsigned char>(0, (unsigned char)(176)));
    mazeToDisplay.insert(pair<short, unsigned char>(1, (unsigned char)(219)));
    mazeToDisplay.insert(pair<short, unsigned char>(2, 'S'));
    mazeToDisplay.insert(pair<short, unsigned char>(3, 'E'));
    mazeToDisplay.insert(pair<short, unsigned char>(10, '0'));
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

vector<unsigned short> BFS(struct coordinates sC, struct coordinates eC, short n, short m, short** maze, bool diagonal = true)
{
    vector<unsigned short> ret;
    bool found = false;
    queue<struct coordinates> nextVisit; 
    
    unsigned short** visited;
    visited = new unsigned short*[n];
    for(int j = 0; j < n; j++) visited[j] = new unsigned short[m];
    
    for(int j = 0; j < n; j++) for(int jj = 0; jj < m; jj++) visited[j][jj] = 0;

    unsigned short** tempMap;
    tempMap = new unsigned short*[n];
    for(int j = 0; j < n; j++) tempMap[j] = new unsigned short[m];
    
    for(int j = 0; j < n; j++) for(int jj = 0; jj < m; jj++) tempMap[j][jj] = 0;

    nextVisit.push(sC);
    visited[sC.y][sC.x] = 10;
    tempMap[sC.y][sC.x] = 10;

    while(!nextVisit.empty())
    {
        struct coordinates checkCoordinates = nextVisit.front();
        nextVisit.pop();

        for(int j = -1; j <= 1; j++)
        {
            for(int jj = -1; jj <= 1; jj++)
            {
                int newCoordY = checkCoordinates.y + j;
                int newCoordX = checkCoordinates.x + jj;
                struct coordinates pushCoord(newCoordX, newCoordY); 

                if(validJump(pushCoord, n, m, diagonal, j, jj) && maze[pushCoord.y][pushCoord.x] != 1 && !visited[newCoordY][newCoordX])
                {
                    //cout<<"checkCoordinates -> pushCoord"<<endl;
                    //cout<<checkCoordinates.x<<" "<<checkCoordinates.y<<" -> "<<pushCoord.x<<" "<<pushCoord.y<<endl;
                    //cout<<endl;
                    if (pushCoord == eC) found = true;

                    nextVisit.push(pushCoord);

                    if(j > 0) visited[newCoordY][newCoordX] += DIRECTION_DOWN;
                    else if(j < 0) visited[newCoordY][newCoordX] += DIRECTION_UP;
                    if(jj > 0) visited[newCoordY][newCoordX] += DIRECTION_RIGHT;
                    else if(jj < 0) visited[newCoordY][newCoordX] += DIRECTION_LEFT;
                    
                    tempMap[newCoordY][newCoordX] = visited[newCoordY][newCoordX] + 10;

                }
                if(found) break;
            }
            if(found) break;
        }
        if(found) break;
    }
    queue<struct coordinates>().swap(nextVisit);


    //tempMazeDisplay(n,m,tempMap);

    if(found)
    {
        struct coordinates mazePointer(eC.x, eC.y);

        while(mazePointer != sC)
        {
            short currentDirection = visited[mazePointer.y][mazePointer.x];
            short invertedDirection = invDirections(visited[mazePointer.y][mazePointer.x]);

            if(currentDirection == 0)
            {
                cout<<"You lost your way"<<endl;
                break;
            }

            ret.push_back(currentDirection);

            if(invertedDirection & DIRECTION_UP) mazePointer.y -= 1;
            if(invertedDirection & DIRECTION_DOWN) mazePointer.y += 1;
            if(invertedDirection & DIRECTION_RIGHT) mazePointer.x += 1;
            if(invertedDirection & DIRECTION_LEFT) mazePointer.x -= 1;
        }
        reverse(ret.begin(), ret.end());
    }
    else
    {
        cout<<"Could Not Reach Exit";
    }
    return ret;
}


#endif //DEFINE_BFS