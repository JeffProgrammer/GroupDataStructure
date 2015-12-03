//-----------------------------------------------------------------------------
// group.h
// Copyright(c) 2015 Jeff Hutchinson
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef _GROUP_H_
#define _GROUP_H_

#include <vector>

class Group;

class IGroupable {
public:
	IGroupable();
	
	~IGroupable();
	
	Group *mGroup;
};

class Group {
public:
	Group() {
	
	}
	
	~Group() {
		// delete every object.
		for (size_t i = 0; i < mGroupList.size(); i++) {
			IGroupable *obj = mGroupList[i];
			delete obj;
			obj = nullptr;
		}
	}
	
	void add(IGroupable *obj) {
		// if this group already contains this object, then don't re-add it
		if (contains(obj))
			return;
		
		// if the object is already in a group, remove it from
		// that group. an object can only belong to one group at a time.
		if (obj->mGroup != nullptr)
			obj->mGroup->remove(obj);
			
		mGroupList.push_back(obj);
		obj->mGroup = this;
	}
	
	bool remove(IGroupable *obj) {
		// make sure we have it in the group
		auto res = std::find(mGroupList.begin(), mGroupList.end(), obj);
		if (res == mGroupList.end())
			return false;
			
		// set the object's group to nullptr
		obj->mGroup = nullptr;
			
		mGroupList.erase(res);
		return true;
	}
	
	bool contains(IGroupable* obj) const {
		return std::find(mGroupList.begin(), mGroupList.end(), obj) != mGroupList.end();
	}
	
	size_t size() const {
		return mGroupList.size();
	}
	
	std::vector<IGroupable*>::iterator begin() {
		return mGroupList.begin();
	}
	
	std::vector<IGroupable*>::iterator end() {
		return mGroupList.end();
	}
	
	std::vector<IGroupable*>::const_iterator cbegin() const {
		return mGroupList.cbegin();
	}
	
	std::vector<IGroupable*>::const_iterator cend() const {
		return mGroupList.cend();
	}
	
	void print() {
		for (size_t i = 0; i < size(); i++)
			printf("%p\n", mGroupList[i]);
	}
	
private:
	std::vector<IGroupable*> mGroupList;
};

#endif // _GROUP_H_