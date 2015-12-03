//-----------------------------------------------------------------------------
// main.cpp
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

#include <stdlib.h>
#include "group.h"

class Obj : public IGroupable
{
public:
	Obj(int val) : mValue(val) {}
	
	~Obj() {
		printf("Obj was deleted with value %d\n", mValue);
	}
	
	inline int getValue() const {
		return mValue;
	}
	
private:
	// value that is stored in the object
	int mValue;
};

int main() {
	// create some objects
	Obj *obj0 = new Obj(5);
	Obj *obj1 = new Obj(100);
	Obj *obj2 = new Obj(200);
	Obj *obj3 = new Obj(300);

	// create a group
	Group g;
	
	// add the objects to the group
	g.add(obj0);
	g.add(obj1);
	g.add(obj2);
	g.add(obj3);
	
	// test a foreach loop to see if iterators work
	printf("Testing iterators...\n");
	for (auto obj : g) {
		printf("Value is %d\n", static_cast<Obj*>(obj)->getValue());
	}
	
	// test const iterator
	printf("Testing const iterators...\n");
	for (const auto obj : g) {
		printf("Value is %d\n", static_cast<Obj*>(obj)->getValue());
	}

	// test operator overloading
	printf("Testing operator overloading...\n");
	for (unsigned int i = 0; i < g.size(); i++) {
		Obj *obj = static_cast<Obj*>(g[i]);
		printf("Value is %d\n", static_cast<Obj*>(obj)->getValue());
	}
	
	// print out the group
	printf("G:\n");
	g.print();
	
	{
		// create another group to test mutual exclusion
		Group x;
		
		// add obj0 to x.
		x.add(obj0);
		
		// print x and then g to show that it moved
		printf("X:\n");
		x.print();
		printf("G:\n");
		g.print();
	}
	
	// print G
	printf("\n\nPrinting G again...\n");
	g.print();
	
	// !!!!! WARNING: OBJ0 IS NULLPTR HERE SINCE THE GROUP DELETED IT!!!!!!

	return 0;
}