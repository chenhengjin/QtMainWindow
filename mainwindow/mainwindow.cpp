#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
/***********************打开菜单*********************************************/
    //第一个参数显示文本信息，第二个参数是parent，通常写this
    openaction = new QAction(QString::fromLocal8Bit("&打开"),this);
    //设置快捷键，默认为ctrl+o
    openaction->setShortcut(QKeySequence::Open);
    //状态栏的提示语句
    openaction->setStatusTip(tr("Open a file."));
    //添加图标
    openaction->setIcon(QIcon(":/open.png"));
    connect(openaction, SIGNAL(triggered()), this, SLOT(open()));
    //下面将QAction添加到菜单和工具条：
    //会返回菜单栏，直接新建菜单，参数为显示的菜单名字
    QMenu *file = menuBar()->addMenu(QString::fromLocal8Bit("&文件"));
    //使用这个QMenu指针添加这个QAction
    file->addAction(openaction);
    //使用addToolBar函数的返回值添加了一个工具条
    QToolBar *toolbar = addToolBar(tr("&file"));
    //把这个QAction添加到了上面。
    toolbar->addAction(openaction);

/***********************保存菜单*********************************************/
    //第一个参数显示文本信息，第二个参数是parent，通常写this
    saveaction = new QAction(QString::fromLocal8Bit("&保存"),this);
    //设置快捷键，默认为ctrl+s
    saveaction->setShortcut(QKeySequence::Save);
    //状态栏的提示语句
    saveaction->setStatusTip(tr("Save file."));
    //添加图标,相对路径显示不了，绝对路径能显示
    saveaction->setIcon(QIcon(":/save.png"));
    connect(saveaction, SIGNAL(triggered()), this, SLOT(save()));
    //下面将QAction添加到菜单和工具条：
    file->addAction(saveaction);
    toolbar->addAction(saveaction);

/***********************颜色选择工具条*********************************************/
    //第一个参数显示文本信息，第二个参数是parent，通常写this
    colorselectaction = new QAction(QString::fromLocal8Bit("&颜色选择"),this);
    //状态栏的提示语句
    colorselectaction->setStatusTip(tr("select color."));
    //添加图标,相对路径显示不了，绝对路径能显示
    colorselectaction->setIcon(QIcon(":/color.png"));
    connect(colorselectaction, SIGNAL(triggered()), this, SLOT(colorselect()));
    //下面将QAction添加到工具条：
    toolbar->addAction(colorselectaction);

/***********************帮助菜单*********************************************/
    //第一个参数显示文本信息，第二个参数是parent，通常写this
    helpaction = new QAction(QString::fromLocal8Bit("&帮助"),this);
    //设置快捷键，默认为ctrl+s
    helpaction->setShortcut(QKeySequence::HelpContents);
    //状态栏的提示语句
    helpaction->setStatusTip(tr("help."));
    connect(helpaction, SIGNAL(triggered()), this, SLOT(help()));
    //新建一个菜单
    QMenu *help = menuBar()->addMenu(QString::fromLocal8Bit("&帮助"));
    //使用这个QMenu指针添加这个QAction
    help->addAction(helpaction);
/*********************************标准对话框MessageBox_information*****************************/
    //第一个参数显示文本信息，第二个参数是parent，通常写this
    messageboxaction_information = new QAction(tr("&information"),this);
    //状态栏的提示语句
    messageboxaction_information->setStatusTip(tr("information."));
    connect(messageboxaction_information, SIGNAL(triggered()), this, SLOT(messagebox_information()));
    //新建一个菜单
    QMenu *messagebox = menuBar()->addMenu(QString::fromLocal8Bit("&对话框"));
    //使用这个QMenu指针添加这个QAction
    messagebox->addAction(messageboxaction_information);
/*********************************标准对话框MessageBox_critical*****************************/
    //第一个参数显示文本信息，第二个参数是parent，通常写this
    messageboxaction_critical = new QAction(tr("&critical"),this);
    //状态栏的提示语句
    messageboxaction_critical->setStatusTip(tr("critical."));
    connect(messageboxaction_critical, SIGNAL(triggered()), this, SLOT(messagebox_critical()));
    //添加到菜单栏
    messagebox->addAction(messageboxaction_critical);
/*********************************标准对话框MessageBox_warning*****************************/
    //第一个参数显示文本信息，第二个参数是parent，通常写this
    messageboxaction_warning = new QAction(tr("&warning"),this);
    //状态栏的提示语句
    messageboxaction_warning->setStatusTip(tr("warning."));
    connect(messageboxaction_warning, SIGNAL(triggered()), this, SLOT(messagebox_warning()));
    //添加到菜单栏
    messagebox->addAction(messageboxaction_warning);
/*********************************标准对话框MessageBox_question*****************************/
    //第一个参数显示文本信息，第二个参数是parent，通常写this
    messageboxaction_question = new QAction(tr("&question"),this);
    //状态栏的提示语句
    messageboxaction_question->setStatusTip(tr("question."));
    connect(messageboxaction_question, SIGNAL(triggered()), this, SLOT(messagebox_question()));
    //添加到菜单栏
    messagebox->addAction(messageboxaction_question);
/*********************************标准对话框MessageBox_about*****************************/
    //第一个参数显示文本信息，第二个参数是parent，通常写this
    messageboxaction_about = new QAction(tr("&about"),this);
    //状态栏的提示语句
    messageboxaction_about->setStatusTip(tr("about."));
    connect(messageboxaction_about, SIGNAL(triggered()), this, SLOT(messagebox_about()));
    //添加到菜单栏
    messagebox->addAction(messageboxaction_about);

    /*********************************标准对话框MessageBox_about*****************************/
    //第一个参数显示文本信息，第二个参数是parent，通常写this
    messageboxaction_message = new QAction(tr("&message"),this);
    //状态栏的提示语句
    messageboxaction_message->setStatusTip(tr("message."));
    connect(messageboxaction_message, SIGNAL(triggered()), this, SLOT(messagebox_message()));
    //添加到菜单栏
    messagebox->addAction(messageboxaction_message);
/*********************************添加状态栏*******************************************/
    msgLabel = new QLabel;
    msgLabel->setMinimumSize(msgLabel->sizeHint());
    msgLabel->setAlignment(Qt::AlignHCenter);
    statusBar()->addWidget(msgLabel);
    //解决没有提示信息的时候，有边框的情况
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
}

void MainWindow::open(void)
{
    //弹出一个标准对话框，标题为Open，提示语为Open a file，并且有一个OK按键
    //QMessageBox::information(NULL, tr("Open"), tr("Open a file"));

    //标准文件打开对话框
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg *.png)"));
    if(path.length() == 0)
    {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    }
    else
    {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path);
    }


}

void MainWindow::save(void)
{
    //弹出一个标准对话框，标题为Open，提示语为Open a file，并且有一个OK按键
    //QMessageBox::information(NULL, tr("Save"), tr("Save a file"));

    //标准文件打开对话框
    QString path = QFileDialog::getSaveFileName(this, tr("Save Image"), ".", tr("Image Files(*.jpg *.png)"));
    if(path.length() == 0)
    {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't Save any files."));
    }
    else
    {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path);
    }

}

void MainWindow::help(void)
{
    //弹出一个标准对话框，标题为help，提示语为暂时没有信息，并且有一个OK按键
    QMessageBox::information(NULL, tr("help"), tr("暂时没有信息"));

}
void MainWindow::colorselect(void)
{
    //弹出一个标准对话框，标题为help，提示语为暂时没有信息，并且有一个OK按键
    //QMessageBox::information(NULL, tr("help"), QString::fromLocal8Bit("暂时没有信息"));
    QColor color = QColorDialog::getColor(Qt::black, this,QString::fromLocal8Bit("选择颜色"));
    //占位符的替换需要使用QString的arg()函数
    QString msg = QString("r: %1, g: %2, b: %3").arg(QString::number(color.red()), QString::number(color.green()), QString::number(color.blue()));
    QMessageBox::information(NULL, "Selected color", msg);
}

void MainWindow::messagebox_information(void)
{
    //弹出一个标准对话框，标题为hello，提示语为暂时没有信息,有OK和NO两个按键，默认为OK按键

    //如果选择了OK
    if(QMessageBox::information(NULL, tr("hello"), QString::fromLocal8Bit("暂时没有信息"),QMessageBox::Ok|QMessageBox::No,QMessageBox::Ok) == QMessageBox::Ok)
    {
        QMessageBox::information(NULL, tr("Selected OK"),QString::fromLocal8Bit("选择了OK"));
    }
    else
    {
        QMessageBox::information(NULL, tr("Selected NO"),QString::fromLocal8Bit("选择了NO"));
    }
}

void MainWindow::messagebox_critical(void)
{
    //弹出一个标准对话框，标题为critical，提示语为暂时没有信息,有OK和NO两个按键，默认为OK按键

    //如果选择了OK
    if(QMessageBox::critical(NULL, tr("critical"), QString::fromLocal8Bit("暂时没有信息"),QMessageBox::Ok|QMessageBox::No,QMessageBox::Ok) == QMessageBox::Ok)
    {
        QMessageBox::critical(NULL, tr("Selected OK"),QString::fromLocal8Bit("选择了OK"));
    }
    else
    {
        QMessageBox::critical(NULL, tr("Selected NO"),QString::fromLocal8Bit("选择了NO"));
    }
}
void MainWindow::messagebox_warning(void)
{
    //弹出一个标准对话框，标题为warning，提示语为暂时没有信息,有OK和NO两个按键，默认为OK按键

    //如果选择了OK
    if(QMessageBox::warning(NULL, tr("warning"), QString::fromLocal8Bit("暂时没有信息"),QMessageBox::Ok|QMessageBox::No,QMessageBox::Ok) == QMessageBox::Ok)
    {
        QMessageBox::warning(NULL, tr("Selected OK"),QString::fromLocal8Bit("选择了OK"));
    }
    else
    {
        QMessageBox::warning(NULL, tr("Selected NO"),QString::fromLocal8Bit("选择了NO"));
    }
}

void MainWindow::messagebox_question(void)
{
    //弹出一个标准对话框，标题为question，提示语为暂时没有信息,有OK和NO两个按键，默认为OK按键

    //如果选择了OK
    if(QMessageBox::question(NULL, tr("question"), QString::fromLocal8Bit("暂时没有信息"),QMessageBox::Ok|QMessageBox::No,QMessageBox::Ok) == QMessageBox::Ok)
    {
        QMessageBox::question(NULL, tr("Selected OK"),QString::fromLocal8Bit("选择了OK"));
    }
    else
    {
        QMessageBox::question(NULL, tr("Selected NO"),QString::fromLocal8Bit("选择了NO"));
    }
}

void MainWindow::messagebox_about(void)
{
    //弹出一个标准对话框，标题为about，提示语为暂时没有信息,有OK和NO两个按键，默认为OK按键

    //如果选择了OK
    QMessageBox::about(NULL, tr("about"), QString::fromLocal8Bit("暂时没有信息"));

}

void MainWindow::messagebox_message(void)
{
    QMessageBox message(QMessageBox::NoIcon, "Show Qt", "Do you want to show Qt dialog?", QMessageBox::Yes | QMessageBox::No, NULL);

    message.setIconPixmap(QPixmap(":/save.png"));
    if(message.exec() == QMessageBox::Yes)
    {
        QMessageBox::aboutQt(NULL, "About Qt");
    }
}
MainWindow::~MainWindow()
{
    //delete ui;
}


