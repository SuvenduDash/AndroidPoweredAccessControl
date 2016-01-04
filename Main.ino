int buzzer = 13;            //Piezo buzzer connected to MCU pin
int gate_open = 10;        //AVR MCU pin goes high for 10 sec
char user_input[3];         //Characters to be entered by the user
char password[3] = {'5','5','5'};    //User-Defined Password
int password_ok = 0;          //If password matches, 0=false 1=true

void setup()
{
pinMode(gate_open, OUTPUT);
Serial.begin(9600);
digitalWrite(gate_open, LOW);  //By default gate is closed
pinMode(buzzer, OUTPUT); // Declare the buzzer as output
}

void loop()
{
Serial.println("Enter Password");
delay(3000);
while(Serial.available()) //Check the availability of data through serial input
{
  for(int i=0; i<3; i++)   
  {
   user_input[i] = Serial.read();  //Read the bytes into the array labled "user_input"
  }

  for(int i=0; i<3; i++)
  {
   if(user_input[i]==password[i]) //Compare each character received
   {
    password_ok = 1;   //If characters are matched, set the password_ok variable to true(1)
   }
   else
   {
password_ok = 0;  //If the input characters do NOT match, set pass_correct variable to false(0)
Serial.println("Wrong password. Try again"); 
    break;   
   }
  }
}

if(password_ok==1)  //If all characters matched, give audio alert 
{digitalWrite(buzzer, HIGH);
delay(1000);//buzzer sounds for about 1 second
digitalWrite(buzzer, LOW);
}
if(password_ok==1) //If all characters matched, open the gate or door
{  
  Serial.println("GateOpen");  
  digitalWrite(gate_open, HIGH);  
  delay(10000); //For 10 seconds gate is opened and closes automatically(becomes low)
  Serial.println("GateClosed");
  password_ok = 0;
}
else
{
digitalWrite(gate_open, LOW); 
//digitalWrite(buzzer, LOW);
}

delay(500);

}
