#include <iostream>
#include <sys/mman.h>

int main() {
  void* ptr = mmap((void*)0x600000000000, 1000, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  std::cout << "ptr addres: " << ptr << std::endl;
  getchar();

  //void* ptr_remapped = mremap(ptr, 1000, 9999, MREMAP_MAYMOVE);
  //std::cout << "remapped to addres: " << ptr_remapped << std::endl;
  getchar();

  //int res = munmap(ptr_remapped, 9999);
}