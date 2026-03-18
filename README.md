# Enigma Machine Simulator

Encodes and decodes text using a simulation of an enigma machine.

Allows user to select rotor ordering, starting position and reflector as well as optional plugboard configurations.

- Rotor choices 1 to 3 are based on the standard enigma machine from 1930s and rotors 4 and 5 from 1938 army version of the enigma machine.  
- The machine takes 3 rotors at a time in any order (allowing duplicates even though this is not entirely traditional).  
- The three rotors can be initialised in any one of their 26 positions.  
- The plugboard allows up to 10 "steckered pairs".


## Rotors
| Rotor | Wiring (A→Z) | Version | Notch |
|-------|---------------|---------|-------|
| 1     | `EKMFLGDQVZNTOWYHXUSPAIBRCJ` | Enigma I, 1930 | R | 
| 2     | `AJDKSIRUXBLHWTMCQGZNPYFVOE` | Enigma I, 1930 | F |
| 3     | `BDFHJLCPRTXVZNYEIWGAKMUSQO` | Enigma I, 1930 | W |
| 4     | `ESOVPZJAYQUIRHXLNFTGKDCMWB` | M3 Army, 1938 | K |
| 5     | `VZBRGITYUPSDNHLXAWMJQOFECK` | M3 Army, 1938 | A |

The notch represents when the rotor will turn the rotor to its left
## Reflectors
| Reflector | Wiring (A→Z) | Version |
|-----------|---------------|-------|
| 1  | `EJMZALYXVBWFCRQUONTSPIKHGD` | UKW-A -Original reflector |
| 2  | `YRUHQSLDPXNGOKMIEBFZCWVJAT` | UKW-B - Introduced 1937 |
| 3  | `FVPJIAOYEDRZXWGCTKUQSBNMHL` | UKW-C - Introduced 1940 |

---

**Note:** Uses conio.h and _kbhit() for input, making the program Windows only.
