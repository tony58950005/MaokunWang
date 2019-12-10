//todolist.h
//ToDoItem==RestaurantItem
//ToDoList==RestaurantModel
//ToDoItem==RestaurantItem
//ToDoList==RestaurantModel
//ToDoList==RestaurantModel
//ToDoModel==RestaurantTableModel
#ifndef RESTAURANTMODEL_H
#define RESTAURANTMODEL_H

#include <QObject>
#include <QVector>

struct RestaurantItem
{
    bool done;
    QString description;

};

class RestaurantModel : public QObject
{
    Q_OBJECT
public:
    explicit RestaurantModel(QObject *parent = nullptr);
    QVector<RestaurantItem> items() const;

    bool setItemAt(int index, const RestaurantItem &item);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void appendItem();
    void removeCompletedItems();

private:
       QVector<RestaurantItem> mItems;
};

#endif // RESTAURANTMODEL_H
