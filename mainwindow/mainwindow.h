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

    QLabel *msgLabel;     //状态栏提示信息
private slots:
    void open(void);
    void save(void);
    void help(void);
    void colorselect(void);
    void messagebox_information(void);
    void messagebox_critical(void);
    void messagebox_warning(void);
    void messagebox_question(void);
    void messagebox_about(void);
    void messagebox_message(void);
    void inutdialog(void);
    void event(void);
    void closeEvent(QCloseEvent * event);
    bool continueToClose();
    void mypainter(void);
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
