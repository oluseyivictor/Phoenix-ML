#include <iostream>
#include <boost/thread/thread.hpp>

void thread_func() {
  std::cout << "Hello from thread!" << std::endl;
}

int main() {
  std::cout << "Hello from main thread!" << std::endl;

  boost::thread thread(&thread_func);
  thread.join();

  return 0;
}