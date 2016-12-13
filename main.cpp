/*
 * Copyright (c) 2010-2016 Stephane Poirier
 *
 * stephane.poirier@oifii.org
 *
 * Stephane Poirier
 * 3532 rue Ste-Famille, #3
 * Montreal, QC, H2X 2L1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <string>
#include <fstream>
#include <vector>

#include <iostream>
#include <sstream>
using namespace std;
//#include <stdlib.h>


#include <ctime>

int main(int argc, char *argv[])
{
	///////////////////
	//read in arguments
	///////////////////
	//char charBuffer[2048] = {"."}; //usage: spinavmidfiles "." 0
	char charBuffer[2048] = {"C:\\spoirier\\oifii-org\\httpdocs\\ns-org\\nsd\\ar\\cp\\audio_midi"}; 
	//char charBuffer[2048] = {"testmidfolder"}; 
	bool boolSplitIntoSeparateMidiTracks = 0; //0=don't split or 1=split in separate *.mid.txt file
	if(argc>1)
	{
		//first argument is the folder name where to find .mid files
		sprintf_s(charBuffer,2048-1,argv[1]);
	}
	if(argc>2)
	{
		//second argument is the flag specifying to split or not split the *.mid.txt file into *.mid.txt(track*).txt, 0=don't split or 1=split
		boolSplitIntoSeparateMidiTracks = atoi(argv[2]);
	}

	/////////////////////////////////////////////////////
	//execute cmd line to get all folder's .mid filenames
	/////////////////////////////////////////////////////
	string quote = "\"";
	string pathfilter;
	string path=charBuffer;
	pathfilter = path + "\\*.mid";
	string systemcommand;
	systemcommand = "DIR " + quote + pathfilter + quote + "/B /O:N > filenames.txt";
#ifdef _DEBUG
	cout << systemcommand << endl;
#endif //_DEBUG
	system(systemcommand.c_str());


	///////////////////////////////////////
	//load filenames.txt into string vector
	///////////////////////////////////////
	vector<string> filenames;
	ifstream ifs("filenames.txt");
	string temp;
	while(getline(ifs,temp))
		filenames.push_back(temp);


	//////////////////////////////////////////////
	//browse through filenames and call mf2txp.exe
	//////////////////////////////////////////////
	string inputfilename;
	string outputfilename;
	//stringstream ss1 (stringstream::in | stringstream::out);
	//stringstream ss2 (stringstream::in | stringstream::out);
	vector<string>::iterator it;
	cout << "filenames.txt contains:";

	
	it=filenames.begin();
	for ( it=filenames.begin() ; it < filenames.end(); it++ )
	{
		cout << *it << endl; //*it is a .mid filename

		//ss1 << fSecondsPerSegment;
		inputfilename = path + "\\" + *it;//ss1.str();
		//ss2 << numSecondsPlay;
		outputfilename = path + "\\" + *it + ".txt";//ss2.str();

		systemcommand = "mf2txp.exe " + quote + inputfilename + quote + " " + quote + outputfilename + quote;
		cout << systemcommand << endl;
		system(systemcommand.c_str()); 
	}
	cout << endl;	
	return 0;
}