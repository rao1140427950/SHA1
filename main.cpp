#include <iostream>
#include "sha1.h"

using namespace std;

string info = "16711083";

int main()
{
	cout << getSHA1(info) << endl;
}

