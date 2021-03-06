// =====================================================================================
// 
//       Filename:  MainWindow.cpp
//
//    Description:  主窗口的类实现文件
//
//        Version:  1.0
//        Created:  2013年03月05日 21时11分08秒
//       Revision:  none
//       Compiler:  cl
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <QtGui>

#include "MainWindow.h"
#include "LinkListWidget.h"
#include "MainTabWidget.h"
#include "CamareDialog.h"
#include "ScreenShotDialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)	
{
	// 设置窗口大小
	this->resize(1000, 650);
	createMainWeiget();
	createActions();
	createMenus();
	createToolBars();
	createStatusBar();

	setWindowIcon(QIcon(":/res/ico/main.ico"));
	setWindowTitle(tr("Shadow -- Alpha 1"));
}

MainWindow::~MainWindow()	
{

}

void MainWindow::screenshot()
{
	ScreenShotDialog screenShotDialog;

	screenShotDialog.exec();
}

void MainWindow::camare()
{
	CamareDialog camareDialog;

	camareDialog.exec();
}

void MainWindow::about()
{
	QMessageBox::about(this, tr("关于 Shadow"),
			tr("<h2>Shadow 远程控制</h2>"
				"<p>Copyright (C) 2013 hurley liuhuan1992@gmail.com"
				"<p><h3>一个基于 Windows NT 平台的远程控制软件，GUI By Qt 4.X 。</h3>"
				"<p>严正声明：本程序仅用于技术研究，任何集体和个人使用该"
				"程序造成的任何违法后果由使用者个人承担！"));
}

void MainWindow::createMainWeiget()
{
	currLinkLabel = new QLabel(tr("正向连接主机"));
	currPortLabel = new QLabel(tr("  连接端口"));
	passwordLabel = new QLabel(tr("  连接密码"));
	
	currLinkIPEdit = new QLineEdit();

	QRegExp regExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
	currLinkIPEdit->setValidator(new QRegExpValidator(regExp, this));
	currLinkIPEdit->setText("127.0.0.1");
	currLinkIPEdit->setMaxLength(15);

	currPortSpin = new QSpinBox();
	currPortSpin->setRange(1, 65535);
	currPortSpin->setValue(5921);

	passwordEdit = new QLineEdit();
	passwordEdit->setEchoMode(QLineEdit::Password);

	linkButton = new QPushButton(tr("正向连接"));

	topLayout = new QHBoxLayout();
	topLayout->addWidget(currLinkLabel);
	topLayout->addWidget(currLinkIPEdit);
	topLayout->addWidget(currPortLabel);
	topLayout->addWidget(currPortSpin);
	topLayout->addWidget(passwordLabel);
	topLayout->addWidget(passwordEdit);
	topLayout->addStretch();
	topLayout->addWidget(linkButton);
	topLayout->addStretch();

	linkListWidget = new LinkListWidget();
	mainTabWidget = new MainTabWidget();

	bottomSplitter = new QSplitter(Qt::Horizontal);
	bottomSplitter->addWidget(linkListWidget);
	bottomSplitter->addWidget(mainTabWidget);
	bottomSplitter->setStretchFactor(1, 1); 

	mainLayout = new QVBoxLayout();
	mainLayout->addLayout(topLayout);
	mainLayout->addWidget(bottomSplitter);

	mainWigget = new QWidget();
	mainWigget->setLayout(mainLayout);

	this->setCentralWidget(mainWigget);
}

void MainWindow::createActions()
{
	auto_connAction = new QAction(tr("自动上线"), this);
	auto_connAction->setIcon(QIcon(":/res/images/auto_conn.png"));
	auto_connAction->setStatusTip(tr("自动上线设置"));

	screenShotAction = new QAction(tr("屏幕捕获"), this);
	screenShotAction->setIcon(QIcon(":/res/images/screenshot.png"));
	screenShotAction->setStatusTip(tr("捕获被控端的屏幕"));
	connect(screenShotAction, SIGNAL(triggered()), this, SLOT(screenshot()));

	camareAction = new QAction(tr("开启摄像头"), this);
	camareAction->setIcon(QIcon(":/res/images/camare.png"));
	camareAction->setStatusTip(tr("开启被控端的摄像头"));
	connect(camareAction, SIGNAL(triggered()), this, SLOT(camare()));

	configAction = new QAction(tr("服务端配置"), this);
	configAction->setIcon(QIcon(":/res/images/config.png"));
	configAction->setStatusTip(tr("服务端配置"));

	settingAction = new QAction(tr("程序设置"), this);
	settingAction->setIcon(QIcon(":/res/images/setting.png"));
	settingAction->setStatusTip(tr("程序设置"));

	minAction = new QAction(tr("最小化窗口"), this);
	minAction->setIcon(QIcon(":/res/images/min.png"));
	minAction->setStatusTip(tr("最小化程序窗口"));
	connect(minAction, SIGNAL(triggered()), this, SLOT(showMinimized()));

	exitAction = new QAction(tr("退出程序"), this);
	exitAction->setIcon(QIcon(":/res/images/exit.png"));
	exitAction->setStatusTip(tr("退出程序"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	aboutAction = new QAction(tr("关本于程序"), this);
	aboutAction->setIcon(QIcon(":/res/images/about.png"));
	aboutAction->setStatusTip(tr("关于本程序"));
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()
{
	fileMenu = this->menuBar()->addMenu(tr("文件"));
	fileMenu->addAction(auto_connAction);
	fileMenu->addAction(screenShotAction);
	fileMenu->addAction(camareAction);

	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

	setsMenu = this->menuBar()->addMenu(tr("设置"));
	setsMenu->addAction(configAction);
	setsMenu->addSeparator();
	setsMenu->addAction(settingAction);

	toolsMenu = this->menuBar()->addMenu(tr("工具"));

	helpMenu = this->menuBar()->addMenu(tr("帮助"));
	helpMenu->addAction(aboutAction);
}

void MainWindow::createToolBars()
{
	fileToolBar = addToolBar(tr("文件"));
	fileToolBar->setIconSize(QSize(60, 70));
	fileToolBar->addAction(auto_connAction);
	fileToolBar->addSeparator();
	fileToolBar->addAction(screenShotAction);
	fileToolBar->addSeparator();
	fileToolBar->addAction(camareAction);

	workToolBar = addToolBar(tr("设置"));
	workToolBar->setIconSize(QSize(60, 70));
	workToolBar->addAction(configAction);
	workToolBar->addSeparator();
	workToolBar->addAction(settingAction);

	infoToolBar = addToolBar(tr("其它"));
	infoToolBar->setIconSize(QSize(60, 70));
	infoToolBar->addAction(minAction);
	infoToolBar->addSeparator();
	infoToolBar->addAction(exitAction);

	aboutToolBar = addToolBar(tr("关于"));
	aboutToolBar->setIconSize(QSize(60, 70));
	aboutToolBar->addAction(aboutAction);
}

void MainWindow::createStatusBar()
{
	statusLabel = new QLabel(tr("  Shadow -- Alpha 1"));
	statusLabel->setAlignment(Qt::AlignHCenter);
	statusLabel->setMinimumSize(statusLabel->sizeHint());

	this->statusBar()->addWidget(statusLabel);
}

void MainWindow::sleep(unsigned int msec)
{
	QTime dieTime = QTime::currentTime().addMSecs(msec);

	while( QTime::currentTime() < dieTime ) {
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
	}
}
