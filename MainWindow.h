#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include<QDialog>
#include<QTextEdit>
#include<QLabel>
#include<QMenuBar>
#include<QMainWindow>
#include<QMenu>
#include<QAction>
#include<QDockWidget>
#include<QWidget>
#include"KeyManagementWindow.h"
#include"PasswordManagementWindow.h"
#include"CommonWindow.h"

class KeyManagementWindow;


class MainWindow : public QMainWindow, public CommonWindow
{
	Q_OBJECT
public:
	MainWindow();
	~MainWindow() = default;

	void refreshComboBox();
signals:
private slots:
	void encryptPassword();
	void keyManagementWindow();
	void passwordManageWindow();
	void exitApplication();
	void activateButton();
private:	
	void setupMainWindow();
	void setupContentOfComboBox();
	void createMenus();
	void connections();

	unique_ptr<QVBoxLayout> buttonLayout;

	unique_ptr<QWidget> buttonWidget;

	unique_ptr<QDockWidget> buttonDockWidget;
	unique_ptr<QDockWidget> cryptionArea;

	unique_ptr<QTextEdit> textForCryption;

	unique_ptr<QMenu> fileMenu;
	unique_ptr<QMenu> editMenu;
	unique_ptr<QAction> closeApplication;
	unique_ptr<QAction> keyEdit;	
	unique_ptr<QAction> passwordManage;

	unique_ptr<KeyManagementWindow> kh;
	unique_ptr<PasswordManagementWindow> ph;

	string grabCryptionText();
};
#endif
