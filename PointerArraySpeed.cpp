#include <iostream>
//C++11 specific
//#include <chrono>
//#include <time.h>
#include <windows.h>
#include <sstream>
using namespace std;


/********************\
This program is a basic speedtest designed to test operations using array values vs reading the data directly.
It uses O(n^2) operations for array size n.
It then logs the clock time spent on the operations.
\********************/

void arrayTest (long len){
    long arr [len];
    for(long i = 0; i < len; i++){
        arr[i] = i;
        for(long j = 0; j < i; j++){
            arr[i] += arr[j];
        }
    }
}
void pointerTest(long len){
    long arr [len];
    long * poi;
    poi = arr;
    for(long i = 0; i < len; i++){
        *(poi + i ) = i;
        for(long j = 0; j < i; j++){
            *(poi + i) += *(poi + j);
        }
    }

}
//Prettying the results a bit...
string MatchUnit(double millis){
    string ret;
    ostringstream strm;
    if (millis < 0.001){
        strm << (millis*1000000.0);
        ret = strm.str() + " nanoseconds";
    }
    else if (millis < 1.0){
        strm << (millis*1000.0);
        ret = strm.str() + " microseconds";
    }
    else if (millis < 1000.0){
        strm << (millis);
        ret = strm.str() + " milliseconds";
    }
    else{
        strm << (millis/1000.0);
        ret = strm.str() + " seconds";
    }
    return ret;
}

int main(){
    LARGE_INTEGER PerSec;
    QueryPerformanceFrequency(&PerSec);
    cout << "Program init." << endl << "Ticks/sec: " << PerSec.QuadPart << endl;
    long arr [] = {1,10,100,1000, 5000,10000,30000,50000,70000};
    LARGE_INTEGER start, fin;
    double ticks, millis;
    for (long i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
        cout << endl << "Iterations: " << arr[i] << endl << endl;

        QueryPerformanceCounter(&start);
        arrayTest(arr[i]);
        QueryPerformanceCounter(&fin);

        ticks = (fin.QuadPart - start.QuadPart);
        millis = ticks * 1000.0 / PerSec.QuadPart;
        cout << "Array time: " << (ticks) << " ticks and " << MatchUnit(millis) << endl;

        QueryPerformanceCounter(&start);
        pointerTest(arr[i]);
        QueryPerformanceCounter(&fin);

        ticks = (fin.QuadPart - start.QuadPart);
        millis = ticks * 1000.0 / PerSec.QuadPart;
        cout << "Pointer time: " << (ticks) << " ticks and " << MatchUnit(millis) << endl;

    }
    return 0;
}
