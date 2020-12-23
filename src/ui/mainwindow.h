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
	/**
	 * @brief Connect socket to host, as per assignment.
	 * @note host: "jsonplaceholder.typicode.com" port: 80
	 */
	void connectSocket();

private:
	QTcpSocket* tcp_socket_;
	UsersModel* users_model_;
	Ui::MainWindow* ui_;

	enum ReadError {FORMAT_ERROR, JSON_ERROR};
	const int statusbar_message_duration = 3000;

private slots:
	void writeToSocket();
	void readAndProcessReadyData();
	void enableReloadButton();
	void socketErrorOccured(QAbstractSocket::SocketError socket_error);
	void readErrorOccured(ReadError read_error);
};
#endif // MAINWINDOW_H
