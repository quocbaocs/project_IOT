// define các biến chân
int denKhach = 8;

int denBep = 9;

int denNgu1 = 10;

int denNgu2 = 11;

int denToilet = 12;

String readString;

void setup() {

Serial.begin(9600);

pinMode(denKhach, OUTPUT);

pinMode(denBep, OUTPUT);

pinMode(denNgu1, OUTPUT);

pinMode(denNgu2, OUTPUT);

pinMode(denToilet, OUTPUT);

}

void loop() {

while (Serial.available()) {

delay(3);

char c = Serial.read();

readString += c;

}

if (readString.length() >0) {

Serial.println(readString);

if(readString == "bật đèn phòng khách" ||readString == "Bật đèn phòng khách"||readString == "bật 1")
{digitalWrite(denKhach, HIGH);}
else if(readString == "tắt đèn phòng khách"||readString == "Tắt đèn phòng khách"||readString == "tắt 1") 
{digitalWrite(denKhach, LOW);}
                                       //denKhach
if(readString == "bật đèn phòng bếp" ||readString == "Bật đèn phòng bếp"||readString == "bật 2")
{digitalWrite(denBep, HIGH);}
else if(readString == "tắt đèn phòng bếp"||readString == "Tắt đèn phòng bếp"||readString == "tắt 2") 
{digitalWrite(denBep, LOW);}
                                           //denNgu1
if(readString == "bật đèn phòng ngủ 1" ||readString == "Bật đèn phòng ngủ 1" ||readString == "bật đèn phòng ngủ một"||readString == "bật 3")
{digitalWrite(denNgu1, HIGH);}
else if(readString == "tắt đèn phòng ngủ 1"||readString == "Tắt đèn phòng ngủ 1"||readString == "tắt đèn phòng ngủ một"||readString == "tắt 3") 
{digitalWrite(denNgu1, LOW);} 

if(readString == "bật đèn phòng ngủ 2" ||readString == "Bật đèn phòng ngủ 2"|| readString == "bật đèn phòng ngủ hai" || readString == "bật 4")
{digitalWrite(denNgu2, HIGH);}
else if(readString == "tắt đèn phòng ngủ 2"||readString == "Tắt đèn phòng ngủ 2"||readString == "tắt đèn phòng ngủ hai"||readString == "tắt 4") 
{digitalWrite(denNgu2, LOW);} 

if(readString == "bật đèn nhà vệ sinh" ||readString == "Bật đèn nhà vệ sinh"||readString == "bật 5")
{digitalWrite(denToilet, HIGH);}
else if(readString == "tắt đèn nhà vệ sinh"||readString == "Tắt đèn nhà vệ sinh"||readString == "tắt 5") 
{digitalWrite(denToilet, LOW);} 

if (readString == "bat den khach")

{

digitalWrite(denKhach, HIGH);

}

if (readString == "tat den khach")

{

digitalWrite(denKhach, LOW);

}

if (readString == "bat den bep")
 
{

digitalWrite(denBep, HIGH);

}

if (readString == "tat den bep")

{

digitalWrite(denBep, LOW);

}

if (readString == "bat den ngu 1")

{

digitalWrite(denNgu1, HIGH);

}

if (readString == "tat den ngu 1")

{

digitalWrite(denNgu1, LOW);

}

if (readString == "bat den ngu 2")

{

digitalWrite(denNgu2, HIGH);

}

if (readString == "tat den ngu 2")

{

digitalWrite(denNgu2, LOW);

}

if (readString == "bat den toilet")

{

digitalWrite(denToilet, HIGH);

}

if (readString == "tat den toilet")

{

digitalWrite(denToilet, LOW);

}

readString="";

}

}
