
#include <Tape.hpp>

#include <iostream>

using namespace MutableCode;
using namespace std;

int main()
{
	Tape tape;
	tape.write('2');
	tape.moveRight();
	cin>>tape;
	tape.moveLeft();
	//read out '2'
	char c = tape.read();
	cout<<c<<endl;
	
	//print '2', '?'
	cout<<tape;
	
	return 0;
}
