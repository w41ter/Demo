#include <iostream>
#include <thread>

using namespace std;

int main() {
	thread t1([]{
		cout << "hello world" << endl;
	});
	t1.join();
	cout << "main thread" << endl;
	return 0;
}

