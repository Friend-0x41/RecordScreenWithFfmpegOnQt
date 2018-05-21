#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QProcess>
#include <QDebug>
#include <QShortcut>
#include <QTimer>
#include <QTime>
#include <QFile>
#include <QMessageBox>
#include "selectrectwidget.h"
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <windowsx.h>
#include <QSpinBox>
#include <QFile>
#include <QDir>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_recordRect(0,0,1920,1080)
{
    QString path = "./Save";
    QDir dir(path);
    if(!dir.exists())
    {
        dir.mkpath(path);
    }
    ui->setupUi(this);
    recordProcess = new QProcess(this);
    passVideoEncodingProcess = new QProcess(this);
    connect(recordProcess,&QProcess::readyReadStandardError,this,&Widget::showRecordOutput);
    connect(passVideoEncodingProcess,&QProcess::readyReadStandardError,this,&Widget::showPassOutput);
    void (QProcess::*f)(int,QProcess::ExitStatus) = &QProcess::finished;
    connect(passVideoEncodingProcess,f,this,&Widget::onEncodingFinshed);
    ui->stopBtn->setEnabled(false);
    ui->passCheckBox->setEnabled(true);
    this->setFixedSize(this->size());

    srand(time(0));
    ui->pathLabel->setText(ui->pathLabel->text() + QString::number(rand()) + ".mp4");

    if(!RegisterHotKey((HWND)this->winId(),GlobalAddAtom(TEXT("2333")),MOD_CONTROL,'G'))
    {
        QMessageBox::critical(this,"错误","热键注册失败");
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_startBtn_clicked()
{
    QFile file(ui->pathLabel->text());
    if(file.exists())
    {
        if(QMessageBox::question(this,"提示信息","文件已存在，是否覆盖") == QMessageBox::Yes)
        {
            file.remove();
        }
        else
        {
            return;
        }
    }
    ui->textEdit->clear();
    QString logo;
    if(ui->useLogoCheckBox->isChecked())
    {
        logo = QString("-vf \"movie=logo.png[watermark];[in][watermark] overlay=main_w-overlay_w-%1 : main_h-overlay_h-%2[out]\"")
                .arg(ui->HOffsetSpinBox->value())
                .arg(ui->VOffsetSpinBox->value());
    }
    else
    {
        logo = "";
    }
    QString cmdLine = QString("ffmpeg -f gdigrab -framerate 60 -offset_x %1 -offset_y %2 -video_size %3x%4 -i desktop -c:v h264_nvenc -qp 0 %5 %6")
            .arg(m_recordRect.x())
            .arg(m_recordRect.y())
            .arg(m_recordRect.width())
            .arg(m_recordRect.height())
            .arg(logo)
            .arg(ui->pathLabel->text());
    recordProcess->start(cmdLine);
    qDebug() << ui->pathLabel->text();
    recordProcess->waitForStarted();
    if(recordProcess->state() == QProcess::ProcessState::Running)
    {
        ui->startBtn->setEnabled(false);
        ui->selectRectBtn->setEnabled(false);
        ui->stopBtn->setEnabled(true);
        ui->hideCheckBox->setEnabled(false);
        ui->pathBtn->setEnabled(false);
        if(ui->hideCheckBox->isChecked())
        {
            this->showMinimized();
        }
    }
}

void Widget::on_stopBtn_clicked()
{
    recordProcess->write("q\n");
    recordProcess->waitForFinished();
    recordProcess->close();
    if(recordProcess->state() == QProcess::ProcessState::NotRunning)
    {
        if(ui->passCheckBox->isChecked())
        {
            ui->startBtn->setEnabled(false);
            ui->stopBtn->setEnabled(false);
            ui->hideCheckBox->setEnabled(true);
            ui->pathBtn->setEnabled(false);
            ui->selectRectBtn->setEnabled(false);
            startPassVideoEncoding();
        }
        else
        {
            ui->startBtn->setEnabled(true);
            ui->stopBtn->setEnabled(false);
            ui->hideCheckBox->setEnabled(true);
            ui->pathBtn->setEnabled(true);
            ui->selectRectBtn->setEnabled(true);
            if(ui->infoCheckBox->isChecked())
            {
                QMessageBox::information(this,"录制完成","视频保存路径为：" + ui->pathLabel->text());
            }
            on_randBtn_clicked();
        }
    }
    m_recordRect.setX(0);
    m_recordRect.setY(0);
    m_recordRect.setWidth(1920);
    m_recordRect.setHeight(1080);
}

void Widget::on_pathBtn_clicked()
{
    QString path = QFileDialog::getSaveFileName(this,"选择保存路径","./Save","*.mp4");
    if(!path.isEmpty())
    {
        ui->pathLabel->setText(path);
    }
}

void Widget::showRecordOutput()
{
    QString msg = recordProcess->readAllStandardError().data();
    if(msg.contains("No such file or directory",Qt::CaseInsensitive))
    {
        ui->startBtn->setEnabled(true);
        ui->stopBtn->setEnabled(false);
        ui->pathBtn->setEnabled(true);
        ui->hideCheckBox->setEnabled(true);
        recordProcess->waitForFinished();
        recordProcess->close();
        if(this->isMinimized())
        {
            this->showNormal();
        }
        QMessageBox::critical(this,"Error","路径不存在，请重新选择");
    }
    ui->textEdit->insertPlainText(msg);
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Widget::showPassOutput()
{
    QString msg = passVideoEncodingProcess->readAllStandardError().data();
    if(msg.contains("No such file or directory",Qt::CaseInsensitive))
    {
        QMessageBox::critical(this,"Error","文件不存在，可能已被外部更改");
        ui->startBtn->setEnabled(true);
        ui->stopBtn->setEnabled(false);
        ui->pathBtn->setEnabled(true);
        ui->hideCheckBox->setEnabled(true);
        passVideoEncodingProcess->waitForFinished();
        passVideoEncodingProcess->close();
    }
    if(msg.contains("Overwrite ? [y/N]",Qt::CaseInsensitive))
    {
        passVideoEncodingProcess->write("y\n");
    }
    ui->textEdit->insertPlainText(msg);
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Widget::startPassVideoEncoding()
{
    passVideoEncodingProcess->start("PassVideoEncoding " + ui->pathLabel->text());
    passVideoEncodingProcess->waitForStarted();
    if(passVideoEncodingProcess->state() == QProcess::ProcessState::Running)
    {
        ui->startBtn->setEnabled(false);
        ui->stopBtn->setEnabled(false);
        ui->hideCheckBox->setEnabled(false);
        ui->pathBtn->setEnabled(false);
        ui->passCheckBox->setEnabled(false);
    }
}

void Widget::onEncodingFinshed()
{
    ui->startBtn->setEnabled(true);
    ui->stopBtn->setEnabled(false);
    ui->hideCheckBox->setEnabled(true);
    ui->pathBtn->setEnabled(true);
    ui->passCheckBox->setEnabled(true);
    ui->selectRectBtn->setEnabled(true);
    if(ui->infoCheckBox->isChecked())
    {
        QMessageBox::information(this,"压缩完成","压缩后的视频保存路径为：" + ui->pathLabel->text() + "_0.mp4");
    }
    on_randBtn_clicked();
}

void Widget::closeEvent(QCloseEvent* event)
{
    if(recordProcess->state() == recordProcess->ProcessState::Running)
    {
        recordProcess->write("q\n");
    }
    QWidget::closeEvent(event);
}

bool Widget::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = static_cast<MSG*>(message);
    if(msg->message == WM_HOTKEY)
    {
        if(recordProcess->state() == QProcess::ProcessState::Running)
        {
            this->on_stopBtn_clicked();
            this->showNormal();
            this->setWindowState(Qt::WindowActive);
            return true;
        }
        else if(recordProcess->state() == QProcess::ProcessState::NotRunning
                && passVideoEncodingProcess->state() == QProcess::ProcessState::NotRunning)
        {
            this->on_startBtn_clicked();
            return true;
        }
    }
    return false;
}

void Widget::on_finshed_selected(QRect rect)
{
    qDebug() << QString("%1, %2, %3, %4").arg(rect.x()).arg(rect.y()).arg(rect.width()).arg(rect.height());
    if(rect.width() != 1 && rect.height() != 1)
    {
        m_recordRect = rect;
    }
    selectRectWidget = nullptr;
}

void Widget::on_selectRectBtn_clicked()
{
    selectRectWidget = new SelectRectWidget;
    connect(selectRectWidget,&SelectRectWidget::completeSelect,this,&Widget::on_finshed_selected);
    selectRectWidget->setAttribute(Qt::WA_ShowModal,true);
    selectRectWidget->show();
}

void Widget::on_randBtn_clicked()
{
    ui->pathLabel->setText("./Save/" + QString::number(rand()) + ".mp4");
}

void Widget::on_useLogoCheckBox_stateChanged(int arg1)
{
    bool isChecked = ui->useLogoCheckBox->isChecked();
    ui->HOffsetSpinBox->setEnabled(isChecked);
    ui->VOffsetSpinBox->setEnabled(isChecked);
}
