#include <Bluepad32.h>
const int PWMA = 14;
const int PWMB = 12;
const int STBY = 33;
const int motor_a_1 = 23;
const int motor_a_2 = 25;
const int motor_b_1 = 26;
const int motor_b_2 = 27;

GamepadPtr myGamepad = nullptr;
const uint8_t targetMAC[6] = {0xAC,0x8E,0xBD,0x40,0x01,0xC6};

void onConnectedGamepad(GamepadPtr gp) {
  GamepadProperties p = gp->getProperties();
  uint8_t* mac = p.btaddr;

  bool match = true;
  for (int i=0; i<6; i++) {
    if (mac[i] != targetMAC[i]) match = false;
  }

  if (match) {
    Serial.println(" Control autorizado conectado");
    myGamepad = gp;
  } else {
    Serial.println(" Control rechazado");
    
  }
}

void setup() {
  Serial.begin(115200);
  BP32.forgetBluetoothKeys();
  BP32.setup(&onConnectedGamepad, nullptr);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY,HIGH);
  pinMode(PWMA,OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(motor_a_1, OUTPUT);
  pinMode(motor_a_2, OUTPUT);
  pinMode(motor_b_1, OUTPUT);
  pinMode(motor_b_2, OUTPUT);
  ledcAttach(PWMA,1000,8);
  ledcAttach(PWMB,1000,8);
}

void loop() {
  BP32.update();

  if (myGamepad && myGamepad->isConnected()) {

    if (myGamepad->l2()) 
    {
      Serial.println("lt");
      digitalWrite(motor_a_1, HIGH);
      digitalWrite(motor_a_2, LOW);
      ledcWrite(PWMA, 255);
    }
    else if (myGamepad->l1()) {
      Serial.println("lb");
      digitalWrite(motor_a_1, LOW);
      digitalWrite(motor_a_2, HIGH);
      ledcWrite(PWMA, 255);
    }
    else{
      digitalWrite(motor_a_1, LOW);
      digitalWrite(motor_a_2, LOW);
      ledcWrite(PWMA, 0);

  }
    if (myGamepad->r2()) 
    {
      Serial.println("rt");      
      digitalWrite(motor_b_1, HIGH);
      digitalWrite(motor_b_2, LOW);
      ledcWrite(PWMB, 255);
    }
    else if (myGamepad->r1()) 
    {
      Serial.println("rb");
      digitalWrite(motor_b_1, LOW);
      digitalWrite(motor_b_2, HIGH);
      ledcWrite(PWMB, 255);
    }
    else{
      digitalWrite(motor_b_1, LOW);
      digitalWrite(motor_b_2, LOW);
      ledcWrite(PWMB, 0);

    }
  }
}

