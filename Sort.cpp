#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

int main(int argc, char* args[]){

  char c;
  cin >> c;
  while(c!='\0'){
    cin >> c;
    cout << c;
    &c++;
  }
  
  return 0;
}
