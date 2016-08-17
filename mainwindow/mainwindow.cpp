#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QColorDialog>
#include <QInputDialog>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>

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
    //添加图标
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

/*********************************标准对话框MessageBox*****************************/
    //第一个参数显示文本信息，第二个参数是parent，通常写this
    messageboxaction_information = new QAction(tr("&information"),this);
    //状态栏的提示语句
    messageboxaction_information->setStatusTip(tr("information."));
    connect(messageboxaction_information, SIGNAL(triggered()), this, SLOT(messagebox_information()));
    //新建一个菜单
    QMenu *messagebox = menuBar()->addMenu(tr("&MessageBox"));
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

    /*********************************标准输入对话框QInoutDialog*****************************/
    //第一个参数显示文本信息，第二个参数是parent，通常写this
    inputboxaction = new QAction(QString::fromLocal8Bit("&输入对话框"),this);
    //状态栏的提示语句
    inputboxaction->setStatusTip(QString::fromLocal8Bit("输入对话框"));
    connect(inputboxaction, SIGNAL(triggered()), this, SLOT(inutdialog()));
    //新建一个菜单
    QMenu *input = menuBar()->addMenu(QString::fromLocal8Bit("&输入对话框"));
    //使用这个QMenu指针添加这个QAction
    input->addAction(inputboxaction);

    /*********************************事件event*****************************/
    //第一个参数显示文本信息，第二个参数是parent，通常写this
    eventaction = new QAction(QString::fromLocal8Bit("&事件"),this);
    //状态栏的提示语句
    eventaction->setStatusTip(QString::fromLocal8Bit("事件"));
    connect(eventaction, SIGNAL(triggered()), this, SLOT(event()));
    //新建一个菜单
    QMenu *event = menuBar()->addMenu(QString::fromLocal8Bit("&事件(event)"));
    //使用这个QMenu指针添加这个QAction
    event->addAction(eventaction);

    /*********************************QPainter*****************************/
    //第一个参数显示文本信息，第二个参数是parent，通常写this
    painteraction = new QAction(QString::fromLocal8Bit("&QPainter"),this);
    //状态栏的提示语句
    painteraction->setStatusTip(QString::fromLocal8Bit("QPainter"));
    connect(painteraction, SIGNAL(triggered()), this, SLOT(mypainter()));
    //新建一个菜单
    QMenu *painter = menuBar()->addMenu(tr("&QPainter"));
    //使用这个QMenu指针添加这个QAction
    painter->addAction(painteraction);

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



void MainWindow::inutdialog(void)
{
    bool isOK;

    /**
     * @brief 获取输入对话框的字符串 ，类似的还有QInputDialog::getInt\QInputDialog::getDouble\QInputDialog::getItem
     * @param 第一个参数是parant
     *        第二个参数为对话框的标题
     *        第三个对话框是在输入框上面的提示语句
     *        第四个蚕食是用于指明这个QLineEdit的输入模式，
     *        取值范围是QLineEdit::EchoMode，默认是Normal，也就是正常显示，
     *        你也可以声明为password，这样就是密码的输入显示了
     *        第五个参数text是QLineEdit的默认字符串
     *        第六个参数ok是可选的，如果非NLL，则当用户按下对话框的OK按钮时，
     *        这个bool变量会被置为true，可以由这个去判断用户是按下的OK还是Cancel，
     *        从而获知这个text是不是有意义
     *
     */
    QString text = QInputDialog::getText(NULL,
                                         "Input Dialog",
                                         "Please input your comment",
                                         QLineEdit::Normal,
                                         "your comment",
                                         &isOK);
    if(isOK)
    {
        QMessageBox::information(NULL,
                                "Information",
                                "Your comment is: <b>" + text + "</b>",
                                QMessageBox::Yes | QMessageBox::No,
                                QMessageBox::Yes);
    }
}

void MainWindow::event(void)
{
    EventLabel *label = new EventLabel;

    //设置事件lebel的标题
    label->setWindowTitle("MouseEvent Demo");
    //设置Label的大小
    label->resize(300, 200);
    //显示label
    label->show();
}

void EventLabel::mouseMoveEvent(QMouseEvent *event)
{
    this->setText(QString("<center><h1>Move: (%1, %2)</h1></center>").arg(QString::number(event->x()),
                                                                          QString::number(event->y())));
}

void EventLabel::mousePressEvent(QMouseEvent *event)
{
    #if 0
        this->setText(QString("<center><h1>Press: (%1, %2)</h1></center>")
                                                        .arg(QString::number(event->x()), 
                                                           QString::number(event->y())));
    #endif

    //鼠标按下的事件中检测，如果按下的是左键，做我们的处理工作，如果不是左键，则调用父类的函数。
    if(event->button() == Qt::LeftButton)
    {
        this->setText(QString("<center><h1>Press: (%1, %2)</h1></center>")
                                                        .arg(QString::number(event->x()),
                                                           QString::number(event->y())));
    }
    else
    {
        QLabel::mousePressEvent(event);
    }
}

void EventLabel::mouseReleaseEvent(QMouseEvent *event)
{
    QString msg;

    //鼠标按下的事件中检测，如果释放的是左键，做我们的处理工作，如果不是左键，则调用父类的函数。
    if(event->button() == Qt::LeftButton)
    {
        msg.sprintf("<center><h1>Release: (%d, %d)</h1></center>",
                                            event->x(), event->y());
        this->setText(msg);
    }
    else
    {
        QLabel::mouseReleaseEvent(event);
    }
}

void MainWindow::closeEvent(QCloseEvent * event)
{
        if(continueToClose()) {
                event->accept();
        } else {
                event->ignore();
        }
}

bool MainWindow::continueToClose()
{
        if(QMessageBox::question(this,
                                            tr("Quit"),
                                            tr("Are you sure to quit this application?"),
                                            QMessageBox::Yes | QMessageBox::No,
                                            QMessageBox::No)
                == QMessageBox::Yes) {
                return true;
        } else {
                return false;
        }
}

void MainWindow::mypainter(void)
{


}

PaintedWidget::PaintedWidget()
{
    resize(800, 600);
    setWindowTitle(tr("Paint Demo"));
}

void PaintedWidget::paintEvent(QPaintEvent *event)
{
        QPainter painter(this);
        painter.drawLine(80, 100, 650, 500);
        painter.setPen(Qt::red);
        painter.drawRect(10, 10, 100, 400);
        painter.setPen(QPen(Qt::green, 5));
        painter.setBrush(Qt::blue);
        painter.drawEllipse(50, 150, 400, 200);
}

MainWindow::~MainWindow()
{
    //delete ui;
}


