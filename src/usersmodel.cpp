#include "usersmodel.h"

UsersModel::UsersModel(QObject *parent)
	: QAbstractTableModel(parent)
	, latitude_pixmap_green(createLatitudePixmap(Qt::green))
	, latitude_pixmap_red(createLatitudePixmap(Qt::red))
{
}

UsersModel::~UsersModel()
{
	delete latitude_pixmap_green;
	delete latitude_pixmap_red;
}

void UsersModel::setDataSource(const QJsonArray& source)
{
	if (users_ == source) return;

	beginResetModel();
	users_ = source;
	endResetModel();
}

int UsersModel::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return users_.count();
}

int UsersModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return COLUMNS;
}

QVariant UsersModel::data(const QModelIndex& index, int role) const
{
	if (index.column() == NAME_COLUMN && role == Qt::DisplayRole)
	{
		QString name = users_.at(index.row()).toObject().value("name").toString();
		return name.isEmpty() ? "?" : name;
	}
	else if (index.column() == LATITUDE_COLUMN)
	{
		if (role == Qt::DecorationRole)
		{
			QString latitude = (users_.at(index.row())
								.toObject().value("address")
								.toObject().value("geo")
								.toObject().value("lat")
								.toString());
			if (latitude.isEmpty()) return QVariant();
			return latitude.toDouble() >= 0 ? *latitude_pixmap_green : *latitude_pixmap_red;
		}
		else if (role == Qt::SizeHintRole) return LATITUDE_ICON_SIZE;
	}
	return QVariant();
}

QVariant UsersModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case NAME_COLUMN:
				return "Name";
			case LATITUDE_COLUMN:
				return "Latitude";
			default:
				break;
			}
		}
		else return section + 1;
	}
	return QVariant();
}

QPixmap* UsersModel::createLatitudePixmap(QColor color)
{
	QPixmap* pixmap_ptr = new QPixmap(LATITUDE_ICON_SIZE);
	pixmap_ptr->fill(Qt::transparent);
	QPainter painter(pixmap_ptr);
	painter.setBrush(color);
	painter.drawEllipse(0, 0, LATITUDE_ICON_SIZE.width()-1, LATITUDE_ICON_SIZE.height()-1);
	return pixmap_ptr;
}
