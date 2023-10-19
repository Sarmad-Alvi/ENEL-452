/**
   Project: Implementation of a Queue in C++.
   Programmer: Karim Naqvi
   Course: enel452
   Description: test code
*/

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>

#include "queue.h"

/**
   Compare the given queue to the given array of data elements.  Return
   true if they are all equal.
 */
bool testQueueEquality( Queue & q, std::vector<Data> const & array)
{
    if (q.size() != array.size())
	return false;

    for (unsigned i = 0; i < q.size(); ++i)
    {
        Data d(0,0);
	q.remove(&d);
	if ( !d.equals(array[i]) )
	    return false;
	q.insert(d);
    }
    return true;
}

/**
   Empty queue and insert values using old and new insert function.  Return
   true if order of values as they are removed from the queue matches
   expected order.
 */
bool testInsert( Queue & q)
{
    using namespace std;
    cout << "Testing overloaded insert function.\n";
    if (q.size() > 0)
    {
        for (unsigned i = 0; i < q.size() + 2; i++)
        {
            Data d(0, 0);
            q.remove(&d);
        }
    }
    vector<Data> dataVec;
    dataVec.push_back(Data(0,-1));
    dataVec.push_back(Data(1,2));
    dataVec.push_back(Data(-2,-3));
    dataVec.push_back(Data(3,4));
    dataVec.push_back(Data(-4,-5));
    dataVec.push_back(Data(5,6));
    dataVec.push_back(Data(-6,-7));

    q.insert(Data(1,2));
    q.insert(Data(3,4));
    q.insert(Data(5,6));
    q.print();
    q.insert(Data(-2,-3), 1);
    q.insert(Data(-4,-5), 3);
    q.insert(Data(0,-1), 0);
    q.insert(Data(-6,-7), 6);

    q.print();

    assert(q.size() == dataVec.size());
    for (unsigned i = 0; i < dataVec.size(); i++)
    {
        Data buffer(0,0);
        q.remove(&buffer);
        if (!buffer.equals(dataVec[i]))
        {
            return false;
        }
    }
    return true;

}


int main()
{
    using namespace std;

    cout << "Testing queue.\n";
    Queue q1;

    q1.insert(Data(1,1));
    q1.insert(Data(3,3));
    q1.insert(Data(5,5));

    q1.print();

    vector<Data> dataVec;
    dataVec.push_back(Data(1,1));
    dataVec.push_back(Data(3,3));
    dataVec.push_back(Data(5,5));

    assert(testQueueEquality(q1, dataVec));

    Data d44(4, 4);
    bool found = q1.search(d44);
    assert(found == false);


    q1.insert(d44);  // now is (1,1),(3,3),(5,5),(4,4)
    found = q1.search(d44);
    assert(found == true);

    // now queue is(1,1),(3,3),(5,5),(4,4) and 
    // dataVec has (1,1),(3,3),(5,5).  Not equal
    assert(testQueueEquality(q1, dataVec) == false);

    Data temp;
    q1.remove(&temp);  // now q1 is (3,3),(5,5),(4,4)

    Data temp2(1,1);
    assert(temp.equals(temp2));  // (1,1) == (1,1)

    Data temp3(6,6);
    found = q1.search(temp3);
    assert(found == false);

    assert(testInsert(q1));
}
