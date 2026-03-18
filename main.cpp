#include <iostream>
#include <conio.h> 
using namespace std;

char rotor0TickOver = 'R';
char rotor1TickOver = 'F';
char rotor2TickOver = 'W';

string rotors[] = {"EKMFLGDQVZNTOWYHXUSPAIBRCJ", "AJDKSIRUXBLHWTMCQGZNPYFVOE", "BDFHJLCPRTXVZNYEIWGAKMUSQO"};
string reflector = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
bool doubleStep = false;
//Take offsets and update rotor positions
void tick(int offsets[3]){
  offsets[2] ++;

  if(char(offsets[1]%26 + 'A') == rotor1TickOver){
    offsets[0]++;
    offsets[1]++;
  }
  if(char(offsets[2]%26 + 'A') == rotor2TickOver){
    offsets[1] ++;
    
  }

  
}

// Configure rotor positions based on user input
void configure(int positions[3], int offsets[3]){
  int input;
  for (int i = 0; i < 3; i++){
    cout << "Select rotor [0, 1 or 2] for position " << i << ": ";
    cin >> input;

    if (input >= 0 && input <= 2){
      positions[i] = input;
    }
    else{ i--;}
  }



  for (int i = 0; i < 3; i++){
    int input;
    cout << "Select offset [0 - 25] for position " << i << ": ";
    cin >> input;

    if (input >= 0 && (int)input < 26){
      offsets[i] = input;
    }
    else{ i--;}
  }

}
int main()
{
  int rotorPos[] = {0,1,2};
  int offsets[] = {0,0,0};
  configure(rotorPos, offsets);
  char input;
  while(true){
    if (_kbhit()) {     
      input = _getch(); 
      input = toupper(input);
      if(input == ' '){
        cout << input;
      }
      else if ('A' <= input && input  <= 'Z'){
        tick(offsets);
        input = ((rotors[rotorPos[2]][(input - 'A' + offsets[2]) % 26] - 'A' - offsets[2] + 26) % 26) + 'A'; 
        input = ((rotors[rotorPos[1]][(input - 'A' + offsets[1]) % 26] - 'A' - offsets[1] + 26) % 26) + 'A'; 
        input = ((rotors[rotorPos[0]][(input - 'A' + offsets[0]) % 26] - 'A' - offsets[0] + 26) % 26) + 'A'; 

        input = reflector[(input - 'A')];

        //reverse order:
        input = char(((rotors[rotorPos[0]].find(char(((input - 'A' + offsets[0])%26) + 'A')) + 26 - offsets[0])%26)+'A');
        input = char(((rotors[rotorPos[1]].find(char(((input - 'A' + offsets[1])%26) + 'A')) + 26 - offsets[1])%26)+'A');
        input = char(((rotors[rotorPos[2]].find(char(((input - 'A' + offsets[2])%26) + 'A')) + 26 - offsets[2])%26)+'A');

        cout << input;
      }
      else{
        break;
      }
    }
  }
} 


