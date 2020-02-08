/*
 * Author: equati0n
 * Date: December 2016
*/

#include "spiny.h"
#include <QPainter>
#include "myscene.h"
#include "coincounter.h"

Spiny::Spiny(QRectF platformRect, int direction,QGraphicsItem *parent)
    : QGraphicsItem(parent)
      ,mCurrentFrame(),mPlatform(platformRect), mDirection(direction)

{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/spiny.png");
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextFrame()));
    timer->start(100);
}

void Spiny::nextFrame(){

    mCurrentFrame += 238;
    if (mCurrentFrame >= 3569 ) {
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
                g_life_count->decrease();
               // this->removeFromIndex();
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

QRectF Spiny::boundingRect() const {
    return QRectF(0,0,120,93);

}

void Spiny::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,120, 93);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}

int Spiny::type() const {
    return Type;
}

