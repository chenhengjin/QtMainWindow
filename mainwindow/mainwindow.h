#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
    QAction *openaction;  //打开
    QAction *saveaction;  //保存
    QAction *helpaction;  //帮助
    QAction *colorselectaction; //颜色选择
    QAction *messageboxaction_information; //information对话框
    QAction *messageboxaction_critical; //critical对话框
    QAction *messageboxaction_warning; //warning对话框
    QAction *messageboxaction_question; //question对话框
    QAction *messageboxaction_about; //about对话框
    QAction *messageboxaction_message; //自定义信息对话框
    QAction *inputboxaction; //输入对话框
    QAction *eventaction; //事件对话框
    QAction *painteraction; //QPainter对话框
    QAction *serailportaction; //QPainter对话框
    QLabel *msgLabel;     //状态栏提示信息

//槽函数
private slots:
    void open(void);      //打开文件
    void save(void);      //保存文件
    void help(void);      //帮助信息
    void colorselect(void);  //颜色选择
    void messagebox_information(void);  //信息
    void messagebox_critical(void);     //禁止
    void messagebox_warning(void);      //警告
    void messagebox_question(void);     //询问
    void messagebox_about(void);        //关于
    void messagebox_message(void);      //自定义消息
    void inputdialog(void);             //标准输入对话框
    void event(void);                   //事件
    void closeEvent(QCloseEvent * event);  //关闭事件
    bool continueToClose();                //确认关闭
    void mypainter(void);                  //QPainter画图
    void myserailport(void);                  //串口调试

};
class EventLabel : public QLabel
{
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

class PaintedWidget : public QWidget
{
public:
    PaintedWidget();
protected:
    void paintEvent(QPaintEvent *event);
};


#endif // MAINWINDOW_H
