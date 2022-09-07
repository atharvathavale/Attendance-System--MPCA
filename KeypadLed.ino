// Include Keypad library 
#include <Keypad.h> 
#include <IRremote.h> 
 
// Length of password + 1 for null character 
#define Password_Length 7 
// Character to hold password input 
char Data[Password_Length]; 
// Password 
char Master[Password_Length] = "123456"; 
// Counter for character entries 
byte data_count = 0; 
 
// Character to hold key input 
char customKey; 
 
// Constants for row and column sizes 
const byte ROWS = 4; 
const byte COLS = 3; 
 
// Array to represent keys on keypad 
char hexaKeys[ROWS][COLS] = { 
 {'1', '2', '3'}, 
 {'4', '5', '6'}, 
 {'7', '8', '9'}, 
 {'*', '0', '#'} 
}; 
 
// Connections to Arduino 
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad 
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad 
#define led 9 
int data, flag = 2; 
int flagIR = 0; 
int IR_RECEIVE_PIN = 10; 
//IRrecv irrecv(IR_RECEIVE_PIN); 
//decode_results results; 
// Create keypad object 
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
float temp; 
 
void setup(){ 
 pinMode(led, OUTPUT); 
 //pinMode(LED_BUILTIN, OUTPUT); 
 Serial.begin(9600); 
 IrReceiver.begin(IR_RECEIVE_PIN); 
 //irrecv.enableIRIn(); 
 digitalWrite(led, LOW); 
 //digitalWrite(LED_BUILTIN, LOW); 
 
} 
 
void loop() { 
 
 // Initialize LCD and print 
 //Serial.println("Enter Password:"); 
 
 // Look for keypress 
 customKey = customKeypad.getKey(); 
 if (customKey) { 
 // Enter keypress into array and increment counter 
 Data[data_count] = customKey; 
 Serial.println(Data[data_count]); 
 data_count++; 
 } 
 while( Serial.available() ) 
 { 
 data = Serial.read(); 
 if (data == '1') 
 { 
 flag = 1; 
 } 
 else if(data == '0') 
 { 
 flag = 0; 
 } 
 } 
 if(flag == 1) 
 { 
 Serial.print(" Welcome Boss!! "); 
 digitalWrite(led, HIGH); 
 delay(1000); 
 digitalWrite(led, LOW); 
 //digitalWrite(LED_BUILTIN, HIGH); 
 } 
 else if (flag == 0) 
 { 
 Serial.print("Face Unidentified "); 
 digitalWrite(led, LOW); 
 //digitalWrite(LED_BUILTIN, LOW); 
 } 
 if (IrReceiver.decode()) 
 { 
 if(flagIR == 0) 
 { 
 flagIR = 1; 
 Serial.print("The System is now live"); 
 Serial.print(" "); 
 delay(1000); 
 } 
 else if(flagIR == 1) 
 { 
 flagIR = 0; 
 Serial.print("The System is not accepting anymore personnel."); 
 Serial.print(" "); 
 } 
 IrReceiver.resume(); 
 } 
/* 
 if(irrecv.decode(&results)) 
 { 
 if(flagIR == 0) 
 { 
 serial.print("The System is now live"); 
 flagIR = 1; 
 } 
 else if(flagIR == 0) 
 { 
 serial.print("The System is not accepting anymore personnel."); 
 flagIR = 0; 
 } 
 irrecv.resume(); 
 } 
 */ 
 // See if we have reached the password length 
 if (data_count == Password_Length - 1) { 
 
 if (!strcmp(Data, Master)) { 
 // Password is correct 
 Serial.println("Correct Key"); 
 } 
 else { 
 // Password is incorrect 
 Serial.println("Incorrect Key"); 
 } 
 temp=analogRead(A0); 
 temp=temp*0.40020125; 
 Serial.println("The Current Room Temperature is: "); 
 Serial.print(temp); 
 Serial.print("*C"); 
 Serial.print(" "); 
 // Clear data and LCD display 
 clearData(); 
 } 
} 
 
void clearData() { 
 // Go through array and clear data 
 while (data_count != 0) { 
 Data[data_count--] = 0; 
 } 
 return; 
} 
