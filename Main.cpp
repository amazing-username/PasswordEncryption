#include<QApplication>

#include"MainWindow.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	MainWindow stuff{};

	stuff.show();

	return app.exec();
}
