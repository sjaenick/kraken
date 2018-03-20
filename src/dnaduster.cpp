#include "dnaduster.hpp"

DNADuster::DNADuster() {
  mv=0;
  iv=0;
  jv=0;
  mask_size = 0;
  mask = (char*)malloc(500);
  if (mask != NULL) {
    mask_size = 500;
  } else {
    throw std::bad_alloc();
  }
}

DNADuster::~DNADuster() {
  if (mask != NULL && mask_size > 0) {
    free(mask);
  }
}

void DNADuster::wo1(const int len, const char* s, int ivv) {
  int i, ii, j, v, t, n, n1, sum;
  int js, nis;
  n = 32 * 32 * 32;
  n1 = n - 1;
  nis = 0;
  i = 0;
  ii = 0;
  sum = 0;
  v = 0;
  for (j=0; j < len; j++, s++) {
    ii <<= 5;
    if (*s<=32) {
      i=0;
      continue;
    }
    ii |= *s - 'A'; //assume uppercase!
    ii &= n1;
    i++;
    if (i >= dustword) {
      for (js=0; js < nis && iis[js] != ii; js++) ;
        if (js == nis) {
          iis[nis] = ii;
          counts[ii] = 0;
          nis++;
        }
        if ((t = counts[ii]) > 0) {
          sum += t;
          v = 10 * sum / j;
          if (mv < v) {
            mv = v;
            iv = ivv;
            jv = j;
          }
        }
      counts[ii]++;
    }
  }
}

int DNADuster::wo(const int len, const char* s, int* beg, int* end) {
      int i, l1;
      l1 = len - dustword + 1;
      if (l1 < 0) {
            *beg = 0;
            *end = len - 1;
            return 0;
            }
      mv = 0;
      iv = 0;
      jv = 0;
      for (i=0; i < l1; i++) {
        wo1(len-i, s+i, i);
      }
      *beg = iv;
      *end = iv + jv;
      return mv;
}

void DNADuster::dust(char* seq) {
  size_t offset;
  int j, l, a, b, v;
  a=0;b=0;

  size_t seqlen = strlen(seq);

  if (seqlen > mask_size) {
    mask = (char*)realloc(mask, seqlen);
    if (mask == NULL) { throw std::bad_alloc(); }
    mask_size = seqlen;
  }

  uppercase(seq);
  strncpy(mask, seq, seqlen);

  for (offset=0; offset < seqlen; offset += dustwindow2) {
    l = (seqlen > offset+dustwindow) ? dustwindow : seqlen-offset;
    v = wo(l, seq+offset, &a, &b);
    if (v > dustcutoff) {
      for (j = a; j <= b; j++) {
        mask[offset+j]='N';
      }
    }
  }

  strncpy(seq, mask, seqlen);
}

void DNADuster::uppercase(char *sPtr) {  
  while(*sPtr != '\0') {
    *sPtr = toupper(*sPtr);
    ++sPtr;
  }
}
