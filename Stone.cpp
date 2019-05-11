#include "Stone.h"


Stone::Stone()
{




}


//初始化棋子
void Stone::Initialize(int StoneID)
{
    this->_StoneID=StoneID;

    struct
    {
        int Row;
        int Col;
        Stone::STONE_TYPE StType;
    }StInfo[16]={
    {0,0,Stone::JU},
    {0,1,Stone::MA},
    {0,2,Stone::XINAG},
    {0,3,Stone::SHI},
    {0,4,Stone::JIANG},
    {0,5,Stone::SHI},
    {0,6,Stone::XINAG},
    {0,7,Stone::MA},
    {0,8,Stone::JU},

    {2,1,Stone::PAO},
    {2,7,Stone::PAO},

    {3,0,Stone::BING},
    {3,2,Stone::BING},
    {3,4,Stone::BING},
    {3,6,Stone::BING},
    {3,8,Stone::BING},
};

    this->_IsLive=true;
    //棋子编号小于16的就是自己的
    this->_Owner=StoneID<16;
    if(this->_Owner)
    {
        this->_Row=StInfo[StoneID].Row;
        this->_Col=StInfo[StoneID].Col;
        this->_StType=StInfo[StoneID].StType;

    }
    else
    {
        this->_Row=9-StInfo[StoneID-16].Row;
        this->_Col=8-StInfo[StoneID-16].Col;
        this->_StType=StInfo[StoneID-16].StType;
    }
}

//获取棋子的名字
QString Stone::GetStoneName()
{
    switch (this->_StType)
    {
    case Stone::JU:
        return "车";
    case Stone::MA:
        return "马";
    case Stone::XINAG:
        return "象";
    case Stone::SHI:
        return "士";
    case Stone::JIANG:
        return "将";
    case Stone::PAO:
        return "炮";
    case Stone::BING:
        return "兵";
    }
    return "ERROR";
}

void Stone::Rotate()
{
    this->_Col= 8-this->_Col;
    this->_Row = 9-this->_Row;
}
