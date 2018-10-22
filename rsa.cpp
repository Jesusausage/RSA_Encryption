#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstring>

using namespace std;

long long int getPrime(int magnitude);
bool testPrime(long long int n);
long long int euclidean_alg(int a, long long int b);
void encrypt_file(long long int n, int publicKey);
void decrypt_file(long long int n, long long int privateKey);
long long int power(long long int x, long long int mod, long long int n);
long long int multiply(long long int a, long long int b, long long int mod);


int main()
{
    srand(time(NULL));
    
    long long int p = getPrime(1000000);
    long long int q = getPrime(1000000);
    long long int m = (p-1)*(q-1);
    long long int n = p*q;
    char response;
    
    cout << "p = " << p << endl;
    cout << "q = " << q << endl;
    cout << "m = " << m << endl;
    cout << "n = " << n << endl;
    
    int publicKey = getPrime(1000000);
    cout << "Public key = " << publicKey << endl;

    long long int privateKey = euclidean_alg(publicKey, m) % n;
    if (privateKey < 0) privateKey = m+privateKey;
    cout << "Private key = ";
    cout << privateKey << ".\n";

    cout << "Would you like to encrypt a file? y/n ";
    cin >> response;
    while (response == 'y') {
	encrypt_file(n, publicKey);
	cout << "Would you like to encrypt another file? y/n ";
	cin >> response;
    }

    cout << "Would you like to decrypt a file? y/n ";
    cin >> response;
    while (response == 'y') {
	decrypt_file(n, privateKey);
	cout << "Would you like to decrypt another file? y/n ";
	cin >> response;
    }
    
    return 0;
}


long long int getPrime(int magnitude) {
    long long int n = ( (rand()%(9*magnitude) + magnitude) )*10 + 1;
    while (!testPrime(n)) {
	n+=2;
    }
    return n;
}


bool testPrime(long long int n) {
    double ceil = sqrt(n);
    int divisor = 3;
    while (divisor <= ceil) {
	if (n % divisor == 0) return 0;
	divisor += 2;
    }
    return 1;
}


long long int euclidean_alg(int a, long long int b) {
    int remainder = a;
    long long int quotient, dividend = b;
    long long int x=1, y=0, xp=0, yp=1;
    
    while (remainder != 0) {
	quotient = dividend / remainder;
	int temp = remainder;
	remainder = dividend % remainder;
	dividend = temp;

	long long int tempx=xp, tempy=yp;
	xp = x - quotient*xp;
	yp = y - quotient*yp;
	x = tempx;
	y = tempy;
    }
    return y;
}


void encrypt_file(long long int n, int publicKey) {
    ifstream input;
    ofstream output;
    char inputFile[80];
    char outputFile[80];
    char ch;
    long long int encryptedChar;

    cout << "Please enter the name of the file you wish to encrypt: ";
    cin >> inputFile;
    cout << "Please enter a name for the newly created encrypted file: ";
    cin >> outputFile;

    input.open(inputFile);
    output.open(outputFile);

    while (!input.fail()) {
	input.get(ch);
	encryptedChar = power(ch+1601, n, publicKey);
	output << encryptedChar;
	output.put(32);
	cout << encryptedChar << " ";
    }

    cout << "\nReached end of file. Encrypted data contained in " << outputFile << ".\n";
    
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


void decrypt_file(long long int n, long long int privateKey) {
    ifstream input;
    ofstream output;
    char inputFile[80];
    char outputFile[80];
    long long int encryptedChar;
    char decryptedChar;

    cout << "Please enter the name of the file you wish to decrypt: ";
    cin >> inputFile;
    cout << "Please enter a name for the newly created decrypted file: ";
    cin >> outputFile;

    input.open(inputFile);
    output.open(outputFile);

    while (!input.fail()) {
	input >> encryptedChar;
	decryptedChar = power(encryptedChar, n, privateKey) - 1601;
	output.put(decryptedChar);
	cout << decryptedChar;
    }

    cout << "\nReached end of file. Decrypted data contained in " << outputFile << ".\n";

    input.close();
    output.close();
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
    
    
/* 
   135 = 10 * 13 + 5;
   13  = 2  * 5  + 3;
   5   = 1  * 3  + 2;
   3   = 1  * 2  + 1;
   2   = 2  * 1  + 0;
   
   1;
   = 3 - 1*2;
   = 13 - 2*5 - 1*(5 - 1*3);
   = 13 - 2*(135 - 10*13) - 1*(135 - 10*13 - 1*(13 - 2*5));
   = 13 - 2*(135 - 10*13) - 1*(135 - 10*13 - 1*(13 - 2*(135 - 10*13)));
   = 13 + 20*13 + 10*13 + 1*13 + 20*13;
   = 52 * 13;

   1 = 3 - 1*(5 - 1*(13 - 2*(135 - 10*13)))
*/
