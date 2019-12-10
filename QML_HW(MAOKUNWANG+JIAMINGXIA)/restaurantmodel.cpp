#include "restaurantmodel.h"

RestaurantModel::RestaurantModel(QObject *parent) : QObject(parent)
{
    mItems.append({true, QStringLiteral("") });
  //  mItems.append({true, QStringLiteral("") });

    mItems.append({false, QStringLiteral("") });

}

QVector<RestaurantItem> RestaurantModel::items() const
{
    return  mItems;
}

bool RestaurantModel::setItemAt(int index, const RestaurantItem &item)
{
    if(index < 0 || index >= mItems.size())//make sure the data is successful to modify)
        return false;
    const RestaurantItem &oldItem = mItems.at(index);
    if(item.done == oldItem.done && item.description == oldItem.description)//store the current or old item in a local
    //return false if there is nothing changed
        return false;

    mItems[index]=item;
    return true;
}

void RestaurantModel::appendItem()
{
    emit preItemAppended();

    RestaurantItem item;
    item.done = false;
    mItems.append(item);

    emit postItemAppended();

}

void RestaurantModel::removeCompletedItems()
{
    for (int i=0; i < mItems.size();)
    {
        if(mItems.at(i).done)
        {
            emit preItemRemoved(i);

            mItems.removeAt(i);

            emit postItemRemoved();
        }
        else
        {
            ++i;
        }
    }
}
