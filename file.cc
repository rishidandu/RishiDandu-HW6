#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class BinaryFileRecord
{
public:
  double  myVal;
  };

  int main()
  {
    BinaryFileRecord *myRecord = new BinaryFileRecord();
         ifstream binInfile ("cs3377.bin", ios::in | ios::binary);
         binInfile.read((char *) myRecord, sizeof(BinaryFileRecord));
	 cout << "Value was: " << setprecision(10) << myRecord->myVal << endl;
	 binInfile.close();
	 return 0;
   }
