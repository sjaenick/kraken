
#ifndef DNADUSTER_HPP
#define DNADUSTER_HPP

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <new>

class DNADuster {
  public:
    DNADuster();
    ~DNADuster();
    void dust(char* seq);

  private:
    int wo(const int len, const char* s, int* beg, int* end); 
    void wo1(const int len, const char* s, int ivv);
    void uppercase(char *sPtr);
    int mv, iv, jv;
    int counts[32*32*32];
    int iis[32*32*32];

    char* mask;
    size_t mask_size;

    static const int dustword=3;
    static const int dustwindow=32;
    static const int dustwindow2 = (32>>1);
    static const int dustcutoff=16;

};

#endif
