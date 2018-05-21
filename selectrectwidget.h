#ifndef SELECTRECTWIDGET_H
#define SELECTRECTWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QPixmap>
#include <QSize>
#include <QPainter>
#include <QRect>

class SelectRectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SelectRectWidget(QWidget *parent = nullptr);
    ~SelectRectWidget();

signals:
    void completeSelect(QRect);
private:
    void initWindow();
    void loadBackGroundPixmap();

    QRect getRect(const QPoint& beginPoint,const QPoint& endPoint);

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void paintEvent(QPaintEvent* event);
private:
    bool m_isMouserPress;
    QPixmap m_loadPixmap,m_capturePixmap;
    int m_screenWidth;
    int m_screenHeight;
    QPoint m_beginPoint;
    QPoint m_endPoint;
    QPainter m_painter;
};

#endif // SELECTRECTWIDGET_H
