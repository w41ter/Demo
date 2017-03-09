#include <thread>
#include <iostream>
#include <vector>

int main()
{
    std::vector<std::thread> threads;
    for(int i = 0; i < 5; ++i){
        threads.push_back(std::thread([](){
            std::cout << "Hello from lamda thread " << std::this_thread::get_id() << std::endl;
        }));
    }
		for(auto& thread : threads){
        thread.join();
    }
    std::cout<<"Main Thread"<<"\t"<<std::this_thread::get_id()<<std::endl;
    return 0;
}
