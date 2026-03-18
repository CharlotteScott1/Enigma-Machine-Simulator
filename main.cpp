#include <iostream>
#include <conio.h> 
using namespace std;



int rotorNotches[] = {16,4,21, 9, 25};
string rotors[] = {"EKMFLGDQVZNTOWYHXUSPAIBRCJ", "AJDKSIRUXBLHWTMCQGZNPYFVOE", "BDFHJLCPRTXVZNYEIWGAKMUSQO", "ESOVPZJAYQUIRHXLNFTGKDCMWB", "VZBRGITYUPSDNHLXAWMJQOFECK"};
int numOfRotors = size(rotors);

string reflectors[] = {"EJMZALYXVBWFCRQUONTSPIKHGD", "YRUHQSLDPXNGOKMIEBFZCWVJAT", "FVPJIAOYEDRZXWGCTKUQSBNMHL"};
string reflector;
char plugboard[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
/**
 * Given the current rotor offsets, rotate the relevant rotors
 * 
 * @param offsets array of offsets to be updated in place
 * @param positions rotors at each position of the machine (for stepover purposes)
*/
void tick(int offsets[3], int positions[3]){

  bool middleAtNotch = (offsets[1] == rotorNotches[positions[1]]);
  bool rightAtNotch = (offsets[2] == rotorNotches[positions[2]]);

  offsets[2] = (offsets[2] + 1) % 26;


  if(rightAtNotch){
    offsets[1]++;
  }    
  if(middleAtNotch){
    offsets[0]++;
    offsets[1]++;
  }
      
  offsets[0]  %= 26;
  offsets[1]  %= 26;

}

/**
 * Check cin for input errors e.i. wrong type.
 */
bool isValidInput(){
  if (cin.fail()) { 
        cin.clear();             
        cin.ignore(1000, '\n');  
        cout << "Invalid input\n";

        return false;
  }
  return true;
}
/** 
 * Configure rotor positions based on user input
 * Allows the user to select a rotor for each position and to enter its intial offset
 * 
 * @param positions array to populate with rotor positions
 * @param offsets array to populate with rotor offsets
 */
void configure(int positions[3], int offsets[3]){
  cout <<"Rotors:\n";
  for (int i = 0; i < numOfRotors; i++){
    cout <<  i +1 << ": " << rotors[i] << "\n";
  }
  cout <<"\nReflectors:\n";
    for (int i = 0; i < 3; i++){
    cout <<  i +1 << ": " << reflectors[i] << "\n";
  }
  cout <<"\n";
  int input;
  for (int i = 0; i < 3; i++){
    cout << "Select rotor [1 - "<< numOfRotors<< "] for position " << i << ": ";
    cin >> input;
    if(isValidInput && input >= 1 && input <= numOfRotors){
      positions[i] = input -1;
      
    }
    else{ i--;}
     
  }


  for (int i = 0; i < 3; i++){
    input = -1;
    cout << "Select offset [0 - 25] for position " << i << ": ";
    cin >> input;

    if (isValidInput() && input >= 0 && input < 26){
      offsets[i] = input;
    }
    else{ i--;}
  }
  input = -1;
  while ( input <= 0 || input > 2){
    cout << "Select reflector [1,2,3]: ";
    cin >> input;
    if(!isValidInput()){
      input = -1;
    }
  
  }
  reflector = reflectors[input-1];

  input = -1;
  while (input != 1 && input != 0){
    cout << "Use plugboard? [0/1]: ";
    cin >> input;
    if(!isValidInput()){
      input = -1;
    }
  }
  if(input == 1){
    char input1 = 'a';
    char input2 = 'a';

    cout << "Press 0 to stop adding plugs \n";
    //use up to 10 plugboard pairs
    for(int i = 0; i<10; i++){

      while( input1 <'A' || input1 > 'Z' || plugboard[input1 - 'A'] != input1){
        cout << "Input first letter of pair "<< i<< ": ";
        cin >> input1;
        if(isValidInput()){
          input1 = toupper(input1);
          if(input1 == '0'){
            return;
          }
          cin.ignore(1000, '\n');
        }
        else{
          input1 = '0';
        }
      }
      while(input2 <'A' || input2 > 'Z' || plugboard[input2 - 'A'] != input2){
        cout << "Input second letter of pair "<< i<< ": ";
        cin >> input2;
        if(isValidInput()){
          input2 = toupper(input2);
          if(input2 == '0'){
            return;
          }
          cin.ignore(1000, '\n');
        }
        else{
          input2 = '0';
        }
      }
      plugboard[input1-'A'] = input2;
      plugboard[input2-'A'] = input1;

    }
  }

}
int main()
{
  int rotorPos[] = {0,1,2};
  int offsets[] = {0,0,0};
  configure(rotorPos, offsets);
  cout << "Enigma machine configured, start typing to encode\n";
  char input;
  while(true){
    if (_kbhit()) {     
      input = _getch(); 
      input = toupper(input);
      if(input == ' '){
        cout << input;
      }
      else if ('A' <= input && input  <= 'Z'){
        tick(offsets, rotorPos);

        input = plugboard[input-'A'];
        // Pass letter through each rotor forwards
        input = ((rotors[rotorPos[2]][(input - 'A' + offsets[2]) % 26] - 'A' - offsets[2] + 26) % 26) + 'A'; 
        input = ((rotors[rotorPos[1]][(input - 'A' + offsets[1]) % 26] - 'A' - offsets[1] + 26) % 26) + 'A'; 
        input = ((rotors[rotorPos[0]][(input - 'A' + offsets[0]) % 26] - 'A' - offsets[0] + 26) % 26) + 'A'; 

        input = reflector[(input - 'A')];

        //Pass letter through rotors in reverse:
        input = char(((rotors[rotorPos[0]].find(char(((input - 'A' + offsets[0] + 26)%26) + 'A')) + 26 - offsets[0])%26)+'A');
        input = char(((rotors[rotorPos[1]].find(char(((input - 'A' + offsets[1] + 26)%26) + 'A')) + 26 - offsets[1])%26)+'A');
        input = char(((rotors[rotorPos[2]].find(char(((input - 'A' + offsets[2] + 26)%26) + 'A')) + 26 - offsets[2])%26)+'A');
        
        input = plugboard[input-'A'];
        cout << input;
        //cout << "\n" << offsets[1] << ", "<< offsets[2] << "\n";
      }
      else{
        break;
      }
    }
  }
} 


