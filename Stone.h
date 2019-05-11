#ifndef STONE_H
#define STONE_H

#include <QString>
#include <QDebug>

class Stone
{
public:
    Stone();
    //枚举所有的棋子类型
    enum STONE_TYPE
    {
        JU,
        MA,
        XINAG,
        SHI,
        JIANG,
        PAO,
        BING
    };

    //棋子所在行
    int _Row;
    //棋子所在列
    int _Col;
    //棋子的存亡状态,_IsLive==true 表示活着的
    bool _IsLive;
    //棋子的所有者,_OWner==true 表示自己的,这也决定了棋子的颜色。
    bool _Owner;
    //棋子的ID
    int _StoneID;
    //棋子的类型
    STONE_TYPE _StType;

    //初始化棋子
    void Initialize(int StoneID);
    //获取棋子的名字
    QString GetStoneName();
    //旋转棋盘
    void Rotate();


};

#endif // STONE_H
