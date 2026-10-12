#include "iter.hpp"



template< typename T >
void print( T& x )
{
    // if (std::is_same<T, const int>() )
    //     std::cout << x << std::endl;
    // else
        std::cout << x * 2 << std::endl;
//   return;
}

int main() {
    const int tab[] = { 0, 1, 2, 3, 4 };
    int tab2[] = { 50, 51, 52, 53, 54 };

  iter( tab, 5, print<const int> );
  iter( tab2, 5, print<int> );

  return 0;
}