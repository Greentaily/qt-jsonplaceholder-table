#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, tcp_socket_(new QTcpSocket(this))
	, users_model_(new UsersModel(this))
	, ui_(new Ui::MainWindow)
{
	ui_->setupUi(this);

	connect(this->ui_->pushButton_reload, &QAbstractButton::clicked,
			this, &MainWindow::connectSocket);
	connect(tcp_socket_, &QAbstractSocket::connected,
			this, &MainWindow::writeToSocket);
	connect(tcp_socket_, &QAbstractSocket::disconnected,
			this, &MainWindow::enableReloadButton);
	connect(tcp_socket_, &QAbstractSocket::errorOccurred,
			this, &MainWindow::socketErrorOccured);

	ui_->tableView->setModel(users_model_);
	ui_->tableView->horizontalHeader()->setSectionResizeMode(UsersModel::NAME_COLUMN,
															 QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
	if (tcp_socket_->isOpen()) tcp_socket_->abort();
	delete ui_;
}

void MainWindow::connectSocket()
{
	ui_->pushButton_reload->setEnabled(false);
	ui_->pushButton_reload->setText("Подключение...");
	tcp_socket_->connectToHost("jsonplaceholder.typicode.com", 80);
}

void MainWindow::writeToSocket()
{
	ui_->pushButton_reload->setText("Отправка данных...");
	tcp_socket_->write("GET /users HTTP/1.0\nHOST: jsonplaceholder.typicode.com\n\n");
}

void MainWindow::readAndProcessReadyData()
{
	ui_->pushButton_reload->setText("Получение данных...");

	QByteArray data;
	data = tcp_socket_->readAll();
	data = data.right(data.length() - (data.indexOf("\r\n\r\n") + 4));

	QJsonParseError json_error;
	QJsonDocument json_data = QJsonDocument::fromJson(data, &json_error);
	if (json_error.error != QJsonParseError::NoError)
	{
		QString error_message = "При чтении полученных данных произошла ошибка:\n"
								+ json_error.errorString()
								+ "\n offset: "
								+ json_error.offset;
		QMessageBox::critical(this, "Ошибка!", error_message);
		this->ui_->statusbar->showMessage("Ошибка чтения.", 3000);
	}
	users_model_->setDataSource(json_data.array());
	this->ui_->statusbar->showMessage("Данные успешно загружены.", 3000);
}

void MainWindow::enableReloadButton()
{
	ui_->pushButton_reload->setText("Загрузить данные");
	ui_->pushButton_reload->setEnabled(true);
}

void MainWindow::socketErrorOccured(QAbstractSocket::SocketError socketError)
{
	QString error_string;
	switch (socketError)
	{
	case QAbstractSocket::RemoteHostClosedError:
		readAndProcessReadyData();
		return;
	default:
		error_string = tcp_socket_->errorString();
	}
	QMessageBox::critical(this, "Ошибка!", "При загрузке данных произошла ошибка:\n" + error_string);
	this->ui_->statusbar->showMessage("Ошибка соединения.", 3000);
}
