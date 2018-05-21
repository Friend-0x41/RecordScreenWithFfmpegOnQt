#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QRect>
#include "selectrectwidget.h"

class QProcess;

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:

    void on_finshed_selected(QRect rect);

private slots:
    void on_startBtn_clicked();

    void on_stopBtn_clicked();

    void on_pathBtn_clicked();

    void showRecordOutput();

    void showPassOutput();

    void startPassVideoEncoding();

    void onEncodingFinshed();

    void on_selectRectBtn_clicked();

    void on_randBtn_clicked();

    void on_useLogoCheckBox_stateChanged(int arg1);

protected:

    virtual void closeEvent(QCloseEvent* event);

    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private:
    Ui::Widget *ui;

    QProcess* recordProcess;
    QProcess* passVideoEncodingProcess;

    QRect m_recordRect;

    SelectRectWidget* selectRectWidget;
};

#endif // WIDGET_H
