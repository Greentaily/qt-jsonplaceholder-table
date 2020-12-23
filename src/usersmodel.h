#ifndef USERSMODEL_H
#define USERSMODEL_H

#include <QAbstractTableModel>
#include <QPixmap>
#include <QPainter>
#include <QJsonArray>
#include <QJsonObject>

/**
 * @brief The UsersModel class.
 * @details This class represents personal data of users
 * as QJsonArray, wrapped in a table model.
 */
class UsersModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	explicit UsersModel(QObject* parent = nullptr);
	~UsersModel();

	/**
	 * @brief The enumeration of all columns.
	 * @details This enumeration represents all columns in the model.
	 * @note The final value COLUMNS contains total number of columns.
	 */
	enum column {NAME_COLUMN, LATITUDE_COLUMN, COLUMNS};

	/**
	 * @brief Set the data source for the model.
	 * @param source Source of data for the model.
	 * @note This method will copy the specified source.
	 */
	void setDataSource(const QJsonArray& source);
	/**
	 * @brief Get the current number of rows in the model.
	 * @param parent (unused)
	 * @return The number of rows.
	 */
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	/**
	 * @brief Get the number of columns in the model.
	 * @param parent (unused)
	 * @return The number of columns.
	 * @note The number of columns is supposed to be invariant.
	 */
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	/**
	 * @brief Define the displayed data.
	 * @param index Index of the cell.
	 * @param role Role.
	 * @return Representation of the data.
	 * @note As per assignment, only two pieces of data are displayed,
	 * those being name and geographical latitude of personal address,
	 * the latter represented as an icon.
	 */
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	/**
	 * @brief Define the displayed headers.
	 * @param section The row / column the header corresponds to.
	 * @param orientation Orientation of the header.
	 * @param role Role.
	 * @return Representation of the header.
	 */
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
	/* Note: this defines the width and the height
	 * of the bounding box for the icons. */
	const QSize LATITUDE_ICON_SIZE = QSize(16, 16);

	QJsonArray users_;
	/* Icons are invariant and therefore cached to improve performance. */
	/* They are created and drawn in the constructor of the class. */
	QPixmap* latitude_pixmap_green;
	QPixmap* latitude_pixmap_red;

	/* Creates and draws pixmap then fills it with specified color. */
	/* Modify this method to change the shape of the icons. */
	QPixmap* createLatitudePixmap(QColor color);
};

#endif // USERSMODEL_H
