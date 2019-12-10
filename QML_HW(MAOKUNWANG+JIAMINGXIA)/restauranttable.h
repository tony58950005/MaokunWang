//todomodel.h
//ToDoItem==RestaurantItem
//ToDoList==RestaurantModel
//ToDoList==RestaurantModel
//ToDoModel==RestaurantTableModel
#ifndef RESTAURANTTABLE_H
#define RESTAURANTTABLE_H

#include <QObject>
#include<QAbstractListModel>


class RestaurantModel;

class RestaurantTableModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(RestaurantModel *list READ list WRITE setList)
public:
    explicit RestaurantTableModel(QObject *parent = nullptr);

    enum
    {
        DoneRole= Qt::UserRole,
        DescritptionRole
    };


    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    virtual QHash<int, QByteArray> roleNames() const override;





    RestaurantModel *list() const;
    void setList(RestaurantModel *list);

private:
    RestaurantModel *mList;
};

#endif // RESTAURANTTABLE_H
