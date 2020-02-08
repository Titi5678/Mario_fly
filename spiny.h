/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef SPINY_H
#define SPINY_H

#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"
#include <QObject>

class MyScene;
class CoinCounter;

class Spiny : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    enum { Type = UserType + spinyType };
    Spiny (QRectF platformRect, int direction,QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

public slots:
    void nextFrame();
signals:
    void marioSizeStatus(int);
private:

    int mCurrentFrame;
    QPixmap mPixmap;
    QRectF mPlatform;
    int mDirection;
};
#endif // SPINY_H
