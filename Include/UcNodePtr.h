//#ifndef _UC_NODEPTR_H_
//#define _UC_NODEPTR_H_
////
//#include "UcSmartPtr.h"
//#include "UcNode.h"
//#include <list>
//
//namespace Unicorn
//{
//
//	class NodePtr: public SmartPtr<Node>
//	{
//	public:
//		typedef std::list<NodePtr> ChildrenList;
//
//	public:
//		//
//		NodePtr();
//		virtual ~NodePtr();
//		//
//		void attachChild(const NodePtr node);
//		NodePtr detachChild(const NodePtr node);
//		//
//		NodePtr getParent();
//		void setParent(NodePtr parent);
//		//
//		int getChildCount();
//
//	protected:
//				
//	private:
//		int _childCount;
//		//a ptr to refer to the parent of current node as 2nd class 
//		NodePtr* _parent;
//		ChildrenList _children;
//
//	};
//
//}
//
//
//#endif