#ifndef DEFINE_WALKER
#define DEFINE_WALKER

#include<vector>
#include<string>

#include "auxilary.hpp"

using namespace std;


class Walker
{
    private:
        string name;
        struct coordinates currentPosition;
        vector<unsigned short> path;

    public:
    //Constructors
        Walker() 
        {
            name = "Generic_Walker";
            currentPosition.x = 0; 
            currentPosition.y = 0;
            path = vector<unsigned short>();
        }
        Walker(string n)
        {
            name = n;
            currentPosition.x = 0;
            currentPosition.y = 0;
            path = vector<unsigned short>();
        }
        Walker(string n, struct coordinates coord)
        {
            name = n;
            currentPosition.x = coord.x;
            currentPosition.y = coord.y;
            path = vector<unsigned short>();
        }
        Walker(string n, struct coordinates coord, vector<unsigned short> p)
        {
            name = n;
            currentPosition.x = coord.x;
            currentPosition.y = coord.y;
            path = p;
        }
    //Destructor
        ~Walker()
        {
            vector<unsigned short>().swap(path);            
        }
        struct coordinates getPosition() { return currentPosition; }
        void displayPosition()
        {
            cout<<"Current Position of Walker " << name << " is: X: " << currentPosition.x << " Y: " << currentPosition.y <<endl;  
        }
        void setPath(vector<unsigned short> newPath)
        {
            path = newPath;
        }
        void followPath()
        {
            while(!path.empty())
            {
                short nextStep = path.back();
                path.pop_back();

                if(nextStep & DIRECTION_UP) currentPosition.y -= 1;
                if(nextStep & DIRECTION_DOWN) currentPosition.y += 1;
                if(nextStep & DIRECTION_LEFT) currentPosition.x -= 1;
                if(nextStep & DIRECTION_RIGHT) currentPosition.x += 1;
            }
        }
        void readOutPath()
        {
            cout<<"Walker "<<name<<" Taking Route: "<<endl;

            for(auto jt : path)
            {
                if(jt & DIRECTION_UP)
                {
                    if(jt & DIRECTION_LEFT) cout << "NORTH-WEST, ";
                    else if(jt & DIRECTION_RIGHT) cout << "NORTH-EAST, ";
                    else cout << "NORTH, ";
                }
                else if(jt & DIRECTION_DOWN)
                {
                    if(jt & DIRECTION_LEFT) cout << "SOUTH-WEST, ";
                    else if(jt & DIRECTION_RIGHT) cout << "SOUTH-EAST, ";
                    else cout << "SOUTH, ";
                }
                else if(jt & DIRECTION_LEFT) cout << "WEST, ";
                else if(jt & DIRECTION_RIGHT) cout << "EAST, ";
            }
            cout<<endl<<"END PATH"<<endl;
        }
};

#endif // DEFINE_WALKER