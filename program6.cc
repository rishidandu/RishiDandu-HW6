/*
 * Usage of CDK Matrix
 *
 * File:   cdkexample.cc
 * Author: Rishi Dandu
 * Email:  rishi.dandu@utdallas.edu
 */

#include "cdk.h"
#include <stdint.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Binary File"

using namespace std;

const int maxRecordStringLength = 25;

class BinaryFileHeader
{
public: 
	uint32_t magicNumber;
	uint32_t versionNumber;
	uint64_t numRecords;

};

class BinaryFileRecord
{

public:
	uint8_t strLength;
	char stringBuffer[maxRecordStringLength];
};

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

BinaryFileHeader *test1 = new BinaryFileHeader ();

  ifstream input_file("cs3377.bin",ios::in|ios::binary ); 

if(!input_file.is_open() ) {

	cout << "Error \n";
	exit(-1);
}


//input_file.read ((char *) temp, sizeof (BinaryFileHeader));
  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char 		*columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */
  //  setCDKMatrixCell(myMatrix, 2, 2, "Test Message hi ");
// BinaryFileHeader *test1 = new BinaryFileHeader ();
 input_file.read ((char *) test1, sizeof (BinaryFileHeader));	
	string str1 = "Magic: 0x";
	stringstream ss1;
	ss1 << hex << uppercase << test1->magicNumber;
	str1 = str1 +  ss1.str();

	string str2 = "Version: ";
	stringstream ss2;
	ss2 << test1->versionNumber;
	str2 = str2 +  ss1.str();

	string str3 = "NumRecords: ";
	stringstream ss3;
	ss3 << test1->numRecords;
	str3 = str3 +  ss3.str();

	setCDKMatrixCell (myMatrix, 1, 1, str1.c_str () );
	setCDKMatrixCell (myMatrix, 1, 2, str2.c_str () );
	setCDKMatrixCell (myMatrix, 1, 3, str3.c_str () );
 
 	int row = 2;
 	BinaryFileRecord *test2  = new BinaryFileRecord ();
	while (input_file.read (( char *) test2, sizeof (BinaryFileRecord )) && row <= 5)
 	{
		string str1;
		string str2;

		stringstream ss1;
		stringstream ss2;

		ss2 << test2->stringBuffer;
		str2 += ss2.str();
		ss1 << "strlen: " << static_cast<uint16_t> (test2->strLength);
		str1 += ss1.str();

		setCDKMatrixCell (myMatrix, row, 1, str1.c_str () );
		setCDKMatrixCell (myMatrix, row, 2, str2.c_str () );
		row++;
	}
 
 drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;
input_file.close ();
  // Cleanup screen
  endCDK();
}
