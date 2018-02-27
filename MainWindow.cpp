#include<iostream>
#include<QString>
#include"MainWindow.h"
#include"Encryption.h"
#include"Decryption.h"
#include"KeyRetrieval.h"
#include"FileNameRetrieval.h"
#include"FolderStructure.h"
#include"Key.h"
#include"Password.h"

MainWindow::MainWindow()
{
	MainWindow* mw = this;
	QWidget* w = 0;
	ph = unique_ptr<PasswordManagementWindow>{new PasswordManagementWindow};
	kh = unique_ptr<KeyManagementWindow>{new KeyManagementWindow{w, mw, ph.get()}};
	setupMainWindow();
}


void MainWindow::setupMainWindow()
{
	windowHeight = 450;
	windowWidth = 450;
	textForCryption = unique_ptr<QTextEdit>{new QTextEdit{}};
	actionButton = unique_ptr<QPushButton>{new QPushButton(tr("encrypt"))};
	selectionBox = unique_ptr<QComboBox>{new QComboBox{}};

	buttonLayout = unique_ptr<QVBoxLayout>{new QVBoxLayout};
	buttonWidget = unique_ptr<QWidget>{new QWidget};
	buttonDockWidget = unique_ptr<QDockWidget>{new QDockWidget};
	buttonDockWidget.get()->setWindowTitle(tr("Cryption Controls"));
	buttonLayout.get()->addWidget(selectionBox.get());
	buttonLayout.get()->addWidget(actionButton.get());
	buttonWidget.get()->setLayout(buttonLayout.get());
	buttonDockWidget.get()->setWidget(buttonWidget.get());
	buttonDockWidget.get()->setFeatures(QDockWidget::NoDockWidgetFeatures);
	setCentralWidget(buttonDockWidget.get());

	cryptionArea = unique_ptr<QDockWidget>{new QDockWidget(tr("Cryption"))};
	cryptionArea.get()->setWidget(textForCryption.get());
	cryptionArea.get()->setFeatures(QDockWidget::NoDockWidgetFeatures);
	addDockWidget(Qt::LeftDockWidgetArea, cryptionArea.get());

	createMenus();
	setupContentOfComboBox();

	setWindowTitle("Encryption Decryption Messaging");
	setFixedHeight(windowHeight);
	setFixedWidth(windowWidth);
	actionButton.get()->setEnabled(false);
	connections();
}
void MainWindow::setupContentOfComboBox()
{
	selectionBox.get()->clear();
	FileNameRetrieval fnr;
	fnr.retrieveFileNames();
	vector<string> fn{fnr.fileNameContainer()};

	for (auto fle: fn)
	{
		QString bl{QString::fromStdString(fle)};
		selectionBox.get()->addItem(bl);
	}
}
void MainWindow::refreshComboBox() { setupContentOfComboBox(); }
void MainWindow::createMenus()
{
	fileMenu = unique_ptr<QMenu>{menuBar()->addMenu(tr("File"))};
	editMenu = unique_ptr<QMenu>{menuBar()->addMenu(tr("Edit"))};

	closeApplication = unique_ptr<QAction>{new QAction(new QObject(nullptr))};
	closeApplication.get()->setText("Exit Application");

	keyEdit = unique_ptr<QAction>{new QAction(new QObject(nullptr))};
	keyEdit.get()->setText("Key Management");
	passwordManage = unique_ptr<QAction>{new QAction{new QObject{nullptr}}};
	passwordManage.get()->setText("PasswordManagement");

	fileMenu.get()->addAction(closeApplication.get());
	editMenu.get()->addAction(keyEdit.get());
	editMenu.get()->addAction(passwordManage.get());
}
void MainWindow::connections()
{
	QObject::connect(closeApplication.get(), SIGNAL(triggered()), this, SLOT(exitApplication()));
	QObject::connect(keyEdit.get(), SIGNAL(triggered()), this, SLOT(keyManagementWindow()));
	QObject::connect(passwordManage.get(), SIGNAL(triggered()), this, SLOT(passwordManageWindow()));
	QObject::connect(actionButton.get(), SIGNAL(clicked()), this, SLOT(encryptPassword()));
	QObject::connect(textForCryption.get(), SIGNAL(textChanged()), this, SLOT(activateButton()));
}


void MainWindow::encryptPassword()
{
	QString passwordToEncrypt{textForCryption.get()->toPlainText()}, keyForEncryption{selectionBox.get()->currentText()};
	auto passwordToEncryptString = passwordToEncrypt.toStdString(), keyForEncryptionString = FolderStructure::keyDirectory+keyForEncryption.toStdString();
	auto strKeyFilename = keyForEncryption.toStdString();
	Password<> pass{};
	Key<> k;
	pass.setupDecryptedMessage(passwordToEncryptString);
	k.setupFilename(strKeyFilename);

	Encryption ec2{pass, k};
	std::cout<<"Encrypted"<<std::endl;
	ph.get()->populatePass();
}
void MainWindow::keyManagementWindow() { kh.get()->show(); }
void MainWindow::passwordManageWindow() { ph.get()->show(); }
void MainWindow::exitApplication() { exit(0); }


string MainWindow::grabCryptionText()
{
	auto placeHolder = textForCryption.get()->toPlainText();
	
	return placeHolder.toStdString();
}	
void MainWindow::activateButton() 
{ 
	QString content{textForCryption.get()->toPlainText()};
	if (content.size()>0 && selectionBox.get()->count()>0) actionButton.get()->setEnabled(true);
	else actionButton.get()->setEnabled(false);
}
