//#include "UcNodePtr.h"
//#include "UcLogger.h"
//NS_UNICORN;
//
//NodePtr::NodePtr() :
//_childCount(0),
//_parent(NULL)
//{
//}
//
//NodePtr::~NodePtr()
//{
//
//}
//
//void NodePtr::attachChild(const NodePtr node)
//{
//	if (node.isNull())
//	{
//		Logger::log("Node can not be nil.\n");
//		return;
//	}
//	_children.push_back(node);
//}
//
//NodePtr NodePtr::detachChild(const NodePtr node)
//{
//	if (node.isNull())
//	{
//		Logger::log("Node can not be nil.\n");
//		return node;
//	}
//	
//	NodePtr detached;
//	ChildrenList::iterator iter = _children.begin();
//	for (; iter != _children.end(); ++iter)
//	{
//		if (*iter == node)
//		{
//			detached = *(_children.erase(iter));
//			break;
//		}
//	}
//	return detached;
//}
//
//NodePtr NodePtr::getParent()
//{
//	return *_parent;
//}
//
//void NodePtr::setParent(NodePtr parent)
//{
//	if (parent.isNull())
//	{
//		Logger::log("Node can not be nil.\n");
//		return;
//	}
//	this->_parent = &parent;
//}
//
//int NodePtr::getChildCount()
//{
//	return _childCount;
//}
