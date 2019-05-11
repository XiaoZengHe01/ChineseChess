#ifndef CHINESECHESS_H
#define CHINESECHESS_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "Stone.h"


class ChineseChess : public QWidget
{
    Q_OBJECT
public:
    explicit ChineseChess(QWidget *parent = nullptr);

private:
    //棋子的半径
    int _R;
    //保存32颗棋子
    Stone _Stones[32];
    //保存被选中的棋子的ID
    int _SelectID;
    //是否选中自己的棋子
    bool _IsMyStone;

public:
    void MoveByClick(QPoint p);
    void MoveByClick(int Row, int Col);

private:
    void paintEvent(QPaintEvent* Ev);
    void mouseReleaseEvent(QMouseEvent* Ev);
    //绘制棋盘
    void DrawBoard(QPainter& p);
    //绘制棋子
    void DrawStone(QPainter& p);
    //获取棋子的圆心
    QPoint GetStoneCenter(int Row,int Col);
    //根据其地的ID获取棋子的圆心
    QPoint GetStoneCenter(int StoneID);
    //鼠标点击的位置转换为棋盘中的行列坐标
    bool GetBoardPos(const QPoint Pos,int& Row,int &Col);
    int GetStoneID(int Row,int Col);
    /*
     * 功能：移动棋子;
     * 参数 int SelectID：选择的棋子;
     * 参数 int Row,int Col：起始位子;
     * 参数 int KillID：将被杀死的棋子;
     * 返回值：可行--返回true。
     */
    bool StoneMove(int SelectID,int Row,int Col,int KillID);
    //移动“车”。
    bool StoneMoveJU(int SelectID,int Row,int Col,int KillID);
    //移动“马”。
    bool StoneMoveMA(int SelectID,int Row,int Col,int KillID);
    //移动“象”
    bool StoneMoveXIANG(int SelectID,int Row,int Col,int KillID);
    //移动“士”
    bool StoneMoveSHI(int SelectID,int Row,int Col,int KillID);
    //移动“将”
    bool StoneMoveJIANG(int SelectID,int Row,int Col,int KillID);
    //移动“炮”
    bool StoneMovePAO(int SelectID,int Row,int Col,int KillID);
    //移动“兵”
    bool StoneMoveBING(int SelectID,int Row,int Col,int KillID);


signals:

public slots:
};

#endif // CHINESECHESS_H
