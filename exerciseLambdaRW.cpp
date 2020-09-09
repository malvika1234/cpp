#include <cstdint>
#include <cstdio>

#ifndef _MSC_VER
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#else
#define SEEK_SET 1
#define O_RDWR 1

int lseek(int, int, int)
{
  return 0;
}

void close(int) {}
int  read(int, char*, size_t)
{
  return -1;
}
int write(int, const char*, size_t)
{
  return -1;
}
#endif

void Close(int& fd)
{
  if(-1 != fd) {
    close(fd);
    fd = -1;
  }
}
//---------------------------------------------------------------------------

class AutoFreeFD
{
public:
  AutoFreeFD(int fd)
  : mFD{fd}
  {
  }

  AutoFreeFD& operator=(const int& fd)
  {
    mFD = fd;
    return *this;
  }

  ~AutoFreeFD() { Close(mFD); }

  operator int() const { return mFD; }

private:
  int mFD;
};
//---------------------------------------------------------------------------

struct FileHeader
{
  uint32_t checksum;
};
//---------------------------------------------------------------------------

bool SkipBytesFromBeginning(int fd, size_t len)
{
  return len == lseek(fd, len, SEEK_SET);
}
//---------------------------------------------------------------------------

bool ReadExact(int fd, char* data, size_t dataLen)
{
  const auto ret = read(fd, data, dataLen);

  if(-1 == ret) {
    return false;
  }

  return dataLen == static_cast<size_t>(ret);
}
//---------------------------------------------------------------------------

bool WriteExact(int fd, const char* data, size_t dataLen)
{
  const auto ret = write(fd, data, dataLen);

  if(-1 == ret) {
    return false;
  }

  return dataLen == static_cast<size_t>(ret);
}
//---------------------------------------------------------------------------

bool ReadBlock(char* data, size_t dataLen, const int fileId)
{
  char fileName[1'024]{};
  snprintf(fileName, sizeof(fileName), "file-%d.bin", fileId);

  AutoFreeFD fd = open(fileName, O_RDWR, 0);

  if(-1 == fd) {
    printf("file open failed %s\n", fileName);
    return false;
  }

  if(!SkipBytesFromBeginning(fd, sizeof(FileHeader))) {
    return false;
  }

  if(ReadExact(fd, data, dataLen)) {
    return true;
  }

  return false;
}
//---------------------------------------------------------------------------

bool WriteBlock(const char* data, size_t dataLen, const int fileId)
{
  char fileName[1'024]{};
  snprintf(fileName, sizeof(fileName), "file-%d.bin", fileId);

  AutoFreeFD fd = open(fileName, O_RDWR, 0);

  if(-1 == fd) {
    printf("file open failed %s\n", fileName);
    return false;
  }

  if(!SkipBytesFromBeginning(fd, sizeof(FileHeader))) {
    return false;
  }

  if(WriteExact(fd, data, dataLen)) {
    return true;
  }

  return false;
}
//---------------------------------------------------------------------------

int main()
{
  WriteBlock("hello", 4, 2);
  char buffer[5];
  ReadBlock(buffer, 4, 2);
}
//---------------------------------------------------------------------------
