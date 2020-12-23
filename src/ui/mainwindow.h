#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTcpSocket>
#include <QJsonDocument>

#include "usersmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

public slots:
	void connectSocket();

private:
	QTcpSocket* tcp_socket_;
	UsersModel* users_model_;
	Ui::MainWindow* ui_;

private slots:
	void writeToSocket();
	void readAndProcessReadyData();
	void enableReloadButton();
	void socketErrorOccured(QAbstractSocket::SocketError socketError);
};
#endif // MAINWINDOW_H