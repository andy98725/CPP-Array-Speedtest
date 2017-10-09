#include <iostream>
#include <windows.h>
#include <sstream>
using namespace std;


/********************\
This program is a basic speedtest designed to test operations using array indicies vs reading the data directly.
It performs O(n^2) operations for array size n using each method of accessing the data.
It then logs the clock time spent on the operations.
\********************/


//Performs operations using array index
void arrayTest (long len){
    long arr [len];
    for(long i = 0; i < len; i++){
        arr[i] = i;
        for(long j = 0; j < i; j++){
            arr[i] += arr[j];
        }
    }
}
//Performs operations using pointer
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

//Main loop
int main(){
    //Get ticks/sec
    LARGE_INTEGER PerSec;
    QueryPerformanceFrequency(&PerSec);
    //Log ticks/sec
    cout << "Program init." << endl << "Ticks/sec: " << PerSec.QuadPart << endl;
    
    //Each array size to check and log:
    long arr [] = {1,10,100,1000, 5000,10000,30000,50000,70000};
    
    //Measures clock time
    LARGE_INTEGER start, fin;
    //Stores clock time
    double ticks, millis;
    //Main loop for array sizes
    for (long i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
        //Log array size
        cout << endl << "Iterations: " << arr[i] << endl << endl;

        //Perform array operations; Log start and end time
        QueryPerformanceCounter(&start);
        arrayTest(arr[i]);
        QueryPerformanceCounter(&fin);

        //Find time taken
        ticks = (fin.QuadPart - start.QuadPart);
        //Convert to milliseconds
        millis = ticks * 1000.0 / PerSec.QuadPart;
        //Log ticks and time with matching unit
        cout << "Array time: " << (ticks) << " ticks and " << MatchUnit(millis) << endl;

        //Repeat with pointer operations
        QueryPerformanceCounter(&start);
        pointerTest(arr[i]);
        QueryPerformanceCounter(&fin);

        ticks = (fin.QuadPart - start.QuadPart);
        millis = ticks * 1000.0 / PerSec.QuadPart;
        cout << "Pointer time: " << (ticks) << " ticks and " << MatchUnit(millis) << endl;

    }
    //fin
    return 0;
}
