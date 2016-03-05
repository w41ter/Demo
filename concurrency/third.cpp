#include <thread>
#include <iostream>
#include <mutex>
using namespace std;

int main()
{
    std::mutex m;
    thread t1([&m]()
    {
        std::this_thread::sleep_for (chrono::milliseconds(10)); 
        for(int i=0;i<10;i++) 
         {     
            m.lock(); 
            cout <<  "In t1 ThreadID : " << std::this_thread::get_id() << ":" << i << endl;         
            m.unlock (); 
        }
    } );
    thread t2([&m]() 
    {         
				std::this_thread::sleep_for (chrono::milliseconds(10)); 
        for(int i=0;i<10;i++) 
        {         
            m.lock ();
            cout <<  "In t2 ThreadID : " << std::this_thread::get_id() << ":" << i << endl;      
            m.unlock(); 
        } 
    } );
		cout << "Begin thread" << endl; 
    t1.join();     
    t2.join();    
    cout<<"Main Thread"<<endl;
    return 0;
}
