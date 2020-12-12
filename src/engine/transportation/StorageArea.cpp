/*
 * The <unnamed> factory builder project.
 *
 * \file /factory0/src/engine/transportation/StorageArea.cpp/StorageArea.cpp.h
 *
 * \brief
 */

/*
 * CHANGELOG:
 * 30 déc. 2019: File creation (niels)
 */

#include <StorageArea.h>

StorageArea::StorageArea()
: INode()
, IFacilityTile()
, m_ActiveContainers(nullptr)
, m_EmptyContainers(nullptr)
{
	m_ActiveContainers = new ObjList<ItemContainer>();
	m_EmptyContainers = new ObjList<ItemContainer>();
}

StorageArea::~StorageArea()
{

}

void StorageArea::deliverContainer(ItemContainer *_container)
{
	// TODO asser m_Containers is not null
	m_ActiveContainers->addObject(_container);
}

ItemContainer *StorageArea::loadEmptyContainer()
{
	ItemContainer *l_ret = m_EmptyContainers->removeFirst();
	return l_ret;
}

Item *StorageArea::pickRawMaterial(s_ItemTypeUUID _itemType)
{
	ObjListIterator<ItemContainer> *l_it = new ObjListIterator<ItemContainer>(m_ActiveContainers);

	Item *l_ret = nullptr;

	// TODO assert l_it is not null
	while((nullptr != l_it->getCurrent()) && (nullptr==l_ret))
	{
		if(_itemType == l_it->getCurrent()->getCarriedItemType())
		{
			l_ret = l_it->getCurrent()->pickItem();

			if(true == l_it->getCurrent()->isEmpty())
			{
				ItemContainer *l_container = l_it->getCurrent();
				m_ActiveContainers->removeObject(l_container);
				m_EmptyContainers->addObject(l_container);
			}
		}
		else
		{
			l_it->iterate();
		}
	}

	delete l_it;
	return l_ret;
}

bool StorageArea::checkAvailability(s_ItemTypeUUID _itemType)
{
	ObjListIterator<ItemContainer> *l_it = new ObjListIterator<ItemContainer>(m_ActiveContainers);

	bool l_ret = false;

	// TODO assert l_it is not null
	while((nullptr != l_it->getCurrent()) && (false==l_ret))
	{
		if(_itemType == l_it->getCurrent()->getCarriedItemType())
		{
			l_ret = true;
		}
		else
		{
			l_it->iterate();
		}
	}

	delete l_it;
	return l_ret;
}

bool StorageArea::checkAndPickItem(s_ItemTypeUUID _itemType, Item *_pickedItem)
{
	ObjListIterator<ItemContainer> *l_it = new ObjListIterator<ItemContainer>(m_ActiveContainers);

	bool l_ret = false;

	// TODO assert l_it is not null
	while((nullptr != l_it->getCurrent()) && (false==l_ret))
	{
		if(_itemType == l_it->getCurrent()->getCarriedItemType())
		{
			l_ret = true;
			_pickedItem = l_it->getCurrent()->pickItem();
		}
		else
		{
			l_it->iterate();
		}
	}

	delete l_it;
	return l_ret;
}

void StorageArea::lockAccess()
{
	// TODO add mutex lock
}

void StorageArea::unlockAccess()
{
	// TODO add mutex unlock
}