using namespace std;

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "seqreader.hpp"
#include "dnaduster.hpp"

using namespace std;
using namespace kraken;

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "Usage: dustmask <fasta file>" << endl
         << endl;
    return 0;
  }
 
  string fname(argv[1]);
  DNASequenceReader *reader = new FastaReader(fname);
  DNASequence dna;
  DNADuster d;

  while (reader->is_valid()) {
    dna = reader->next_sequence();
    size_t len = dna.seq.length() + 1;
    char *tmp = new char[len];
    strncpy(tmp, dna.seq.c_str(), len);
    d.dust(tmp);
    dna.seq.assign(tmp, len-1);

    cout << ">" << dna.header_line << endl;
    cout << dna.seq << endl;
  }

  return 0;
}
