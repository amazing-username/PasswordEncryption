#ifndef COMMONWINDOW_H_
#define COMMONWINDOW_H_

#include<QDialog>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QComboBox>
#include<QPushButton>
#include<memory>

using std::unique_ptr;

class CommonWindow
{
public:
	CommonWindow() = default;
	~CommonWindow() = default;
protected:
	virtual void connections()=0;
	unique_ptr<QComboBox> selectionBox;
	unique_ptr<QPushButton> actionButton;
	unique_ptr<QHBoxLayout> mainLayout;
	unique_ptr<QVBoxLayout> subLayoutOne;
	unique_ptr<QVBoxLayout> subLayoutTwo;
	int windowHeight, windowWidth;
};
#endif
