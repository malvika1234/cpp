// rainer
#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

using std::vector;

class BigArray
{

public:
  BigArray(size_t len)
  : len_{len}
  , data_{new int[len]}
  {
  }

  BigArray(const BigArray& other)
  : len_{other.len_}
  , data_{new int[other.len_]}
  {
    cout << "Copy construction of " << other.len_
         << " elements " << endl;
    std::copy(other.data_, other.data_ + len_, data_);
  }

  BigArray& operator=(const BigArray& other)
  {
    cout << "Copy assignment of " << other.len_
         << " elements " << endl;
    if(this != &other) {
      delete[] data_;

      len_  = other.len_;
      data_ = new int[len_];
      std::copy(
        other.data_, other.data_ + len_, data_);
    }
    return *this;
  }

  ~BigArray() { delete[] data_; }

private:
  size_t len_;
  int*   data_;
};

int main()
{
  vector<BigArray> myVec{};

  myVec.push_back(BigArray{1'000'000'000});
}
