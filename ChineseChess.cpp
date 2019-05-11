#include "ChineseChess.h"

ChineseChess::ChineseChess(QWidget *parent) : QWidget(parent)
{
    this->resize(500,550);
    this->_R=0;
    this->_SelectID=-1;
    this->_IsMyStone=false;

    //初始化32颗棋子
    for(int i(0);i<32;i++)
    {
        this->_Stones[i].Initialize(i);
    }
}

void ChineseChess::paintEvent(QPaintEvent* Ev)
{
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    this->DrawBoard(p);
    this->DrawStone(p);
}

void ChineseChess::mouseReleaseEvent(QMouseEvent* Ev)
{
    int Row(0);
    int Col(0);
    if(this->GetBoardPos(Ev->pos(),Row,Col))
    {

            int ClickID(-1);
            for(int i(0);i<32;i++)
            {
                if(this->_Stones[i]._Col==Col&&
                        this->_Stones[i]._Row==Row&&
                        this->_Stones[i]._IsLive)
                {
                    ClickID=i;
                    break;
                }

            }

            if(-1==this->_SelectID)
            {
                if(ClickID!=-1)
                {
                    if(this->_IsMyStone==this->_Stones[ClickID]._Owner)
                    {
                        this->_SelectID=ClickID;
                        this->update();
                    }
                }
            }
            else
            {

                if(StoneMove(this->_SelectID,Row,Col,ClickID))
                {

                    //移动棋子
                    this->_Stones[this->_SelectID]._Row=Row;
                    this->_Stones[this->_SelectID]._Col=Col;

                    if(ClickID!=-1)
                    {
                        //棋子被吃
                        this->_Stones[ClickID]._IsLive=false;
                    }

                    this->_SelectID=-1;
                    this->_IsMyStone=!this->_IsMyStone;
                    this->update();
                }
            }
        }
}

//绘制棋盘
void ChineseChess::DrawBoard(QPainter& p)
{
    //保存棋盘所有的线条
    QVector<QLine> Lines;
    //线间距
    int Interval(50);
    //棋子的半径
    this->_R=Interval/2;

    for(int i(1);i<=10;i++)
    {
        //保存10条横线
        Lines.append(QLine(Interval,i*Interval,9*Interval,i*Interval));
        if(i<=9)
        {
            //保存9条竖线
            //留出“楚河、汉界”的区域
            if(1==i||9==i)
            {
                Lines.append(QLine(i*Interval,Interval,i*Interval,10*Interval));
            }
            else
            {
                Lines.append(QLine(i*Interval,Interval,i*Interval,5*Interval));
                Lines.append(QLine(i*Interval,6*Interval,i*Interval,10*Interval));
            }
        }

    }

    //绘制“将、士”区域
    Lines.append(QLine(4*Interval,Interval,6*Interval,3*Interval));
    Lines.append(QLine(6*Interval,Interval,4*Interval,3*Interval));

    Lines.append(QLine(4*Interval,8*Interval,6*Interval,10*Interval));
    Lines.append(QLine(6*Interval,8*Interval,4*Interval,10*Interval));

    p.drawLines(Lines);
}

//绘制棋子
void ChineseChess::DrawStone(QPainter& p)
{

    p.setFont(QFont("楷体",this->_R));

    QPoint C;
    for(int i(0);i<32;i++)
    {

        if(!this->_Stones[i]._IsLive)
        {
            continue;
        }

        if(this->_Stones[i]._Owner)
        {
            p.setPen(Qt::white);

        }
        else
        {
            p.setPen(Qt::red);

        }

        if(this->_SelectID==i)
        {
            p.setBrush(Qt::gray);

        }
        else
        {
            p.setBrush(Qt::black);
        }

        p.drawEllipse(C=GetStoneCenter(i),this->_R,this->_R);
        p.drawText(QRect(C.x()-this->_R,C.y()-this->_R,this->_R*2,this->_R*2),
                   this->_Stones[i].GetStoneName(),
                   QTextOption(Qt::AlignCenter));
    }

}


//获取棋子的圆心
QPoint ChineseChess::GetStoneCenter(int Row,int Col)
{

    return QPoint((Col+1)*this->_R*2,
                  (Row+1)*this->_R*2);
}

//根据其地的ID获取棋子的圆心
QPoint ChineseChess::GetStoneCenter(int StoneID)
{
    return GetStoneCenter(this->_Stones[StoneID]._Row,
                          this->_Stones[StoneID]._Col);
}

//鼠标点击的位置转换为棋盘中的行列坐标
bool ChineseChess::GetBoardPos(const QPoint Pos,int& Row,int &Col)
{
    QPoint C;
    int a(0);
    int b(0);
    for(Row=0;Row<=9;Row++)
    {
        for(Col=0;Col<=8;Col++)
        {
            C=this->GetStoneCenter(Row,Col);

            a=C.x()-Pos.x();
            b=C.y()-Pos.y();

            if(a*a+b*b<this->_R*this->_R)
            {
                return true;
            }
        }
    }
    return false;
}



/*
 ******************************************
 * 功能：移动棋子;
 * 参数 int SelectID：选择的棋子;
 * 参数 int Row,int Col：起始位子;
 * 参数 int KillID：将被杀死的棋子;
 * 返回值：可行--返回true。
 ******************************************
 */
bool ChineseChess::StoneMove(int SelectID,int Row,int Col,int KillID)
{

    //如果颜色相同，表示切换选择
    if(this->_Stones[SelectID]._Owner==this->_Stones[KillID]._Owner&&
            KillID!=-1)
    {
        this->_SelectID=KillID;
        this->update();
        return false;
    }

    switch (this->_Stones[SelectID]._StType)
    {
    case Stone::JU:
        return StoneMoveJU(SelectID, Row, Col, KillID);
    case Stone::MA:
        return StoneMoveMA(SelectID,Row,Col,KillID);
    case Stone::XINAG:
        return StoneMoveXIANG(SelectID,Row,Col,KillID);
    case Stone::SHI:
        return StoneMoveSHI(SelectID,Row,Col,KillID);
    case Stone::JIANG:
        return StoneMoveJIANG(SelectID,Row,Col,KillID);
    case Stone::PAO:
        return StoneMovePAO(SelectID,Row,Col,KillID);
    case Stone::BING:
        return StoneMoveBING(SelectID,Row,Col,KillID);
    }

    return true;
}

void ChineseChess::MoveByClick(QPoint p)
{
    int Row(0);
    int Col(0);
    if(this->GetBoardPos(p,Row,Col))
    {
        this->MoveByClick(Row,Col);
    }
}


void ChineseChess::MoveByClick( int Row, int Col)
{


}

int ChineseChess::GetStoneID(int Row,int Col)
{
    for(int i(0);i<32;i++)
    {
        if(this->_Stones[i]._Row==Row&&
                this->_Stones->_Col==Col)
        {
            return i;
        }
    }
    return -1;
}
//移动“车”。
bool ChineseChess::StoneMoveJU(int SelectID,int Row,int Col,int KillID)
{

    return true;
}

//移动“马”。
bool ChineseChess::StoneMoveMA(int SelectID,int Row,int Col,int KillID)
{
    return true;
}

//移动“象”
bool ChineseChess::StoneMoveXIANG(int SelectID,int Row,int Col,int KillID)
{
    return true;
}

//移动“士”
bool ChineseChess::StoneMoveSHI(int SelectID,int Row,int Col,int KillID)
{
    return true;
}

//移动“将”
bool ChineseChess::StoneMoveJIANG(int SelectID,int Row,int Col,int KillID)
{

    return true;
}

//移动“炮”
bool ChineseChess::StoneMovePAO(int SelectID,int Row,int Col,int KillID)
{
    return true;
}

//移动“兵”
bool ChineseChess::StoneMoveBING(int SelectID,int Row,int Col,int KillID)
{
    return true;
}
