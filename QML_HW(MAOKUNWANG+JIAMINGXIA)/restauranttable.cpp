#include "restaurantmodel.h"
#include "restauranttable.h"

RestaurantTableModel::RestaurantTableModel(QObject *parent) : QAbstractListModel(parent)
  ,mList(nullptr)
{

}
int RestaurantTableModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid() || !mList)
        return 0;

    return mList->items().size();

}
QVariant RestaurantTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || !mList)
        return QVariant();
    const RestaurantItem item =mList->items().at(index.row());
    switch(role)
    {
        case DoneRole:
            return QVariant(false);
        case DescritptionRole:
            return QVariant(QStringLiteral("Set the time of arrival; number of guest; name who book"));
    }
    return QVariant();
}
bool RestaurantTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!mList)
        return false;
    RestaurantItem item = mList->items().at(index.row());
    switch (role) {
    case DoneRole:
            item.done = value.toBool();
            break;
    case DescritptionRole:
            item.description = value.toString();
            break;
    }

    if (mList->setItemAt(index.row(),item))
    {
        emit dataChanged(index, index, QVector<int>() << role);//check if the data has changed
        return true;
    }
    return false;
}
Qt:: ItemFlags RestaurantTableModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}
QHash<int, QByteArray> RestaurantTableModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[DoneRole] = "done";
    names[DescritptionRole]="description";
    return names;
}


RestaurantModel *RestaurantTableModel::list() const
{
    return mList;
}

void RestaurantTableModel::setList(RestaurantModel *list)
{
    beginResetModel();
    if(mList)
    {
        mList->disconnect(this);
    }
    mList = list;

    if(mList)
    {
        connect(mList, &RestaurantModel::preItemAppended, this, [=](){
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &RestaurantModel::postItemAppended, this, [=](){
            endInsertRows();
        });

        connect(mList, &RestaurantModel::preItemRemoved, this, [=](int index){
            beginRemoveRows(QModelIndex(), index, index);
        });

        connect(mList, &RestaurantModel::postItemRemoved, this, [=](){
            endRemoveRows();
        });

    }

    endResetModel();
}
