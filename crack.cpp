// 1198974049727

#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;

int main()
{
    long long int prime;
    
    cout << "Please enter the value of n: ";
    cin >> prime;
    
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    
    int lim = sqrt(prime)+1;
    int f = 3;
    
    while (prime%f!=0 && f<lim)
	f += 2;

    cout << prime << " = " << f << " x " << prime/f << endl;
    cout << "p = " << f << "\nq = " << prime/f << ".\n";

    cout << "Encryption cracked in " << chrono::duration_cast<chrono::milliseconds>
	(chrono::steady_clock::now() - start).count() << "ms.\n";

    return 0;
}
