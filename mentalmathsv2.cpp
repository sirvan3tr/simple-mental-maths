/*
 * Random mental maths script, tbf
 */
#include <iostream>
#include <cstdio>
#include <ctime>
#include <string>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>

using namespace std;

class randomise {
public:
  int size, digits;

  vector<int> getRandom(int size, int digits) {
    vector<int> r;
    srand( (unsigned)time( NULL ) );
    for (int i = 0; i < size; ++i)
    {
      r.push_back(rand() % digits);
    }
    return r;
  }

  void dispRand() {
    vector<int> r = getRandom(size, digits);
    for(int i=0; i < size; i++) {
      cout << "Random number: " << r[i] << endl;
    }
  }

  randomise();
};

randomise::randomise() {
  size = 2;
  digits = 10;
  vector<int> r = getRandom(size, digits);
}

/*
  1 = addition,
  2 = subtraction,
  3 = multiplication,
  4 = division,
*/
class processing: public randomise {
public:
  long mtime, seconds, useconds;
  struct timeval start, end;
  bool nomore = false;
  string reply, sign;
  int ans;
  processing();
  bool theprocess(int operation) {
    cout << "#######################################################" << endl;
    cout << "Are you ready? press enter to start and to finish..." << endl;
    cout << "After each question, type y to end, enter for next question" << endl;
    cout << "#######################################################" << endl;
    while(!nomore)
    {
      cin.ignore();
      gettimeofday(&start, NULL);
      vector<int> r = getRandom(size, digits);
      if(operation == 1) {
        ans = r[0]+r[1];
        sign = " + ";
      } else if (operation == 2) {
        ans = r[0]-r[1];
        sign = " - ";
      } else if(operation == 3) {
        ans = r[0]*r[1];
        sign = " * ";
      } else if(operation == 4) {
        ans = r[0]/r[1];
        sign = " / ";
      } else {
        cout << "unknown operation" << endl;
        nomore = true;
      }
      cout << "---------------" << endl;
      cout << "    " << r[0] << sign << r[1] << endl;
      cout << "---------------" << endl;
      getline(cin, reply);
      cout << "Answer: [" << ans << "] ";

      gettimeofday(&end, NULL);
      seconds  = end.tv_sec  - start.tv_sec;
      useconds = end.tv_usec - start.tv_usec;
      mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
      printf("Elapsed time: %ld milliseconds\n", mtime);

      if (reply=="y") nomore = true;
    }
  }

};

processing::processing() {
  //theprocess(1);
}

int main ()
{
  string programme, digits;
  processing addition;
  cout << "one digit or two digit numbers?" << endl;
    getline(cin, digits);
    if(digits == "1" || digits == "one") {
      addition.digits = 10;
    } else if(digits == "2" || digits == "two") {
      addition.digits = 100;
    } else {
      cout << "unknown operation, default one digit is set" << endl;
      addition.digits = 10;
    }

  cout << "Welcome, choose an option from below" << endl;
  cout << "## type 1 for addition problems" << endl;
  cout << "## type 2 for subtraction problems" << endl;
  cout << "## type 3 for multiplication problems" << endl;
  cout << "## type 4 for division problems" << endl;

  getline(cin, programme);
  if(programme == "1") {
     addition.theprocess(1);
  } else if (programme == "2") {
     addition.theprocess(2);
  } else if(programme == "3") {
     addition.theprocess(3);
  } else if(programme == "4") {
     addition.theprocess(4);
  } else {
    cout << "unknown operation" << endl;
  }

   return 0;
}
