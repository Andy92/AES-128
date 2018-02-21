// reading an entire binary file
#include <iostream>
#include <fstream>
#include  <iomanip>
#include  <vector>
using namespace std;

int main () {
  streampos size;
  unsigned int * memblock;
  bool reading_key = true;
  char * aes_key = new char[16];
  char * block = new char[16];
  ifstream file ("aes_sample.in", ios::in|ios::binary|ios::ate);
  if (file.is_open())
  {
    size = file.tellg();
    memblock = new unsigned int [size];
    file.seekg (0, ios::beg);
    file.read (memblock, size);
    file.close();

    cout << "size: " << size << " bytes" << endl;
    cout << "output: ";
    for(int i=0;i<size;++i) {
		printf("%X", memblock[i]);
		if(reading_key) {
			aes_key[i] = memblock[i]; // Read key.
		} else {
			block[i % 16] = memblock[i]; // Read last block.
		}

		if((i % 16) == 15 ) {	// New line every 16 bytes
			cout << endl << "       ";
			reading_key = false;
		}

		cout << " ";
	}
	cout << endl;

	//char * encryptedBlock = encrypt(aes_key, block);

    delete[] memblock;
  }
  else cout << "Unable to open file";
  delete[] aes_key;
  return 0;
}