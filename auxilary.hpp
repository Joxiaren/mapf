#ifndef DEFINE_AUXILARY
#define DEFINE_AUXILARY

struct coordinates
{
    int x;
    int y;
    coordinates(){};
    coordinates(int X, int Y) : x(X), y(Y){};
};

bool operator==(const coordinates& lhs, const coordinates& rhs)
{
    bool ret = true;
    if(lhs.x != rhs.x) ret = false;
    else if(lhs.y != rhs.y) ret = false;
    return ret;
};

bool operator!=(const coordinates& lhs, const coordinates& rhs)
{
    return !(lhs == rhs);
}


enum DIRECTIONS
{ 
    DIRECTION_UP = 0x01,
    DIRECTION_DOWN = 0x02,
    DIRECTION_LEFT = 0x04,
    DIRECTION_RIGHT = 0x08
};

unsigned short invDirections(unsigned short directions)
{
    if(directions & DIRECTION_UP) directions += (-DIRECTION_UP + DIRECTION_DOWN);
    else if(directions & DIRECTION_DOWN) directions += (-DIRECTION_DOWN + DIRECTION_UP);
    if(directions & DIRECTION_LEFT) directions += (-DIRECTION_LEFT + DIRECTION_RIGHT);
    else if(directions & DIRECTION_RIGHT) directions += (-DIRECTION_RIGHT + DIRECTION_LEFT);

    return directions;
}

#endif //DEFINE_AUXILARY