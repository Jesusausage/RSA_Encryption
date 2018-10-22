#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstring>

using namespace std;

void decrypt_file();
long long int power(long long int x, long long int mod, long long int n);
long long int multiply(long long int a, long long int b, long long int mod);


int main()
{
    long long int n, factor;
    char response;

    cout << "Would you like to decrypt a file? y/n ";
    cin >> response;
    while (response == 'y') {
	decrypt_file();
	cout << "Would you like to decrypt another file? y/n ";
	cin >> response;
    }
    
    return 0;
}


void decrypt_file() {
    ifstream input;
    ofstream output;
    char inputFile[80];
    char outputFile[80];
    long long int n, key;
    long long int encryptedChar;
    char decryptedChar;

    cout << "Please enter the name of the file you wish to decrypt: ";
    cin >> inputFile;
    cout << "Please enter a name for the newly created decrypted file: ";
    cin >> outputFile;   
    cout << "Please enter the key. n = ";
    cin >> n;
    cout << "Factor = ";
    cin >> key;

    input.open(inputFile);
    output.open(outputFile);

    while (!input.fail()) {
	input >> encryptedChar;
	decryptedChar = power(encryptedChar, n, key) - 1601;
	output.put(decryptedChar);
	cout << decryptedChar;
    }

    cout << "\nReached end of file. Decrypted data contained in " << outputFile << ".\n";

    input.close();
    output.close();
}


long long int power(long long int x, long long int mod, long long int n) {
    
    while (n != 1) {
	if (n%2 == 0) {
	    return ( power(multiply(x, x, mod), mod, n/2) ) % mod;
	} else {
	    return ( multiply( x, power(multiply(x, x, mod), mod, (n-1)/2), mod) ) % mod;
	}
    }

    return x;
}


long long int multiply(long long int a, long long int b, long long int mod) {
    long long int aLarge, aSmall, bLarge, bSmall;
    aLarge = a/100000000;
    aSmall = a%100000000;
    bLarge = b/100000000;
    bSmall = b%100000000;

    long long int answer1 = aLarge*bLarge;
    for (int index=0; index<16; index++)
	answer1 = (answer1*10) % mod;
    long long int answer2 = aSmall*bLarge + aLarge*bSmall;
    for (int index=0; index<8; index++)
	answer2 = (answer2*10) % mod;
    long long int answer3 = aSmall*bSmall;

    return (answer1 + answer2 + answer3) % mod;
}
