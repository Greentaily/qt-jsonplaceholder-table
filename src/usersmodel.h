#ifndef USERSMODEL_H
#define USERSMODEL_H

#include <QAbstractTableModel>
#include <QPixmap>
#include <QPainter>
#include <QJsonArray>
#include <QJsonObject>

class UsersModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	explicit UsersModel(QObject* parent = nullptr);
	~UsersModel();

	enum column {NAME_COLUMN, LATITUDE_COLUMN, COLUMNS};

	void setDataSource(const QJsonArray& source);
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
	const QSize LATITUDE_ICON_SIZE = QSize(16, 16);

	QJsonArray users_;
	QPixmap* latitude_pixmap_green;
	QPixmap* latitude_pixmap_red;

	void drawLatitudePixmap(QPixmap* pixmap_ptr, QColor color);
};

#endif // USERSMODEL_H
