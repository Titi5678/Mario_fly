/*
 * Author: equati0n
 * Date: December 2016
*/

#include "redturtle.h"
#include <QPainter>
#include "myscene.h"
#include "coincounter.h"

RedTurtle::RedTurtle(QRectF platformRect, int direction,QGraphicsItem *parent)
    : QGraphicsItem(parent)
      ,mCurrentFrame(),mPlatform(platformRect), mDirection(direction)

{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/redt.png");
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextFrame()));
    timer->start(100);
}

void RedTurtle::nextFrame(){

    mCurrentFrame += 179;
    if (mCurrentFrame >= 3521 ) {
        mCurrentFrame = 0;
    }
    if(this->pos().x() < mPlatform.x() || this->pos().x() > mPlatform.x()+ mPlatform.width()) {
        mDirection = -mDirection;
        setTransform(QTransform(-mDirection, 0, 0, 1, boundingRect().width(), 0));
    }
    setPos(this->pos().x() + (mDirection*7), this->pos().y());

    //Collision Detection
        QList<QGraphicsItem *> colliding_items = collidingItems();

        //If one of the colliding items is an Enemy, destroy both the bullet and the enemy
        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(Player)){
                g_nFlag = 0;
                emit marioSizeStatus(0);
                delete colliding_items[i];
                qDebug()<<"Mario deleted small mario added";
                delete this;
                return;
            }
        }
        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(SmallMario)){

               // emit marioSizeStatus(1);
              //  delete colliding_items[i];
               // qDebug()<<"small mario dead";
                g_life_count->decrease();
                delete this;
                return;
            }
        }
        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(FireMario)){

               // emit marioSizeStatus(6);
                //delete colliding_items[i];
               // qDebug()<<"Fire mario deleted small mario added";
                delete this;
                return;
            }
        }
}

QRectF RedTurtle::boundingRect() const {
    return QRectF(0,0,130,146);

}

void RedTurtle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,130, 146);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}

int RedTurtle::type() const {
    return Type;
}

