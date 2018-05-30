#ifndef PROFILEVIEW_H
#define PROFILEVIEW_H

#include <QWidget>
#include <QAbstractTableModel>
#include <QHash>

class MRC;
class QTableView;
class QComboBox;
class QListWidget;
class QGridLayout;

class ProfileView:public QWidget
{
	Q_OBJECT
public:
	ProfileView(QWidget* parent = nullptr);
	void addModel(const QString & text, QAbstractTableModel * model);

signals:
	void itemSelected(const QString & text);
	void itemChanged(const QString & text);
private:
	QTableView * m_tableView;
	QListWidget * m_listWidget;
	QHash<QString,QAbstractTableModel *> m_hash;
};

class MRCInfoTableModel :public QAbstractTableModel
{
	Q_OBJECT
public:
	MRCInfoTableModel(int row,int column,QObject * parent = nullptr);
	int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
	int columnCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole)const Q_DECL_OVERRIDE;
	bool setData(const QModelIndex& index, const QVariant& value, int role) Q_DECL_OVERRIDE;



private:
	QVector<QVector<QVariant>> m_data;
	int m_rowCount;
	int m_columnCount;
};

#endif // PROFILEVIEW_H