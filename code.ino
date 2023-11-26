// IMPLEMENTASI FSM DENGAN UNTUK ROBOT LENGAN 3DOF KENDALI LQR
#include <cppQueue.h>
#include <ErriezLCDKeypadShield.h>
#include <StateMachine.h>
// state machine
StateMachine machine = StateMachine();
State* S0 = machine.addState(&state0); 
State* S1 = machine.addState(&state1);
State* S2 = machine.addState(&state2);
State* S3 = machine.addState(&state3);
State* S4 = machine.addState(&state4);
// Keypad Shield
LCDKeypadShield shield;
// QUEUE
#define	IMPLEMENTATION	LIFO // last in first out
typedef struct struktur {
	int	posisi;
} Record;
cppQueue	q(sizeof(Record), 3, IMPLEMENTATION);

// mulai setup
void setup() {
  Serial.begin(115200);
  // State awal mula 
  S0->addTransition(&transitionS0S1, S1);
  S0->addTransition(&transitionS0S2, S2);
  S0->addTransition(&transitionS0S3, S3);
  // state 1 ke semua state
  S1->addTransition(&transitionS1S2, S2);
  S1->addTransition(&transitionS1S3, S3);
  S1->addTransition(&transitionS1S4, S4);
  // state 2 ke semua state
  S2->addTransition(&transitionS2S1, S1);
  S2->addTransition(&transitionS2S3, S3);
  S2->addTransition(&transitionS2S4, S4);
  // state 3 ke semua state
  S3->addTransition(&transitionS3S1, S1);
  S3->addTransition(&transitionS3S2, S2);
  S3->addTransition(&transitionS3S4, S4);
}

void loop() {
  machine.run();
  delay(200);
}
void state0() {
  if(machine.executeOnce){
    shield.clear();
    shield.setCursor(0, 1);
    shield.print(F("STATE 0"));
  }
}
// declare semua state
void state1() {
  if(machine.executeOnce){
    Record urutan = {10};
    q.push(&urutan);
    shield.setCursor(0, 1);
    shield.print(F("STATE 1"));
  }
}

void state2() {
  if(machine.executeOnce){
    Record urutan = {20};
    q.push(&urutan);
    shield.setCursor(0, 1);
    shield.print(F("STATE 2"));
  }
} 

void state3() {
  if(machine.executeOnce){
    Record urutan = {30};
    q.push(&urutan);
    shield.setCursor(0, 1);
    shield.print(F("STATE 3"));
  }
} 

void state4() {
  unsigned int i;
  unsigned int count = q.getCount();
  delay(3000);
  for(i = 0; i < count + 1; i++){
    shield.clear();
    shield.setCursor(0, 1);
    Record urutan;
    q.pop(&urutan);
    shield.print(urutan.posisi);
    delay(3000);
  }
  delay(2000);
  machine.transitionTo(S0);
}



// transisi tiap state
// dari S0 ke semua state kecuali s4
// s0 > s1
bool transitionS0S1() {
  switch (shield.getButtons()) {
    case ButtonLeft:
        return true;
    default:
        break;
  }
  return false;
}
// s0 > s2
bool transitionS0S2() {
  switch (shield.getButtons()) {
    case ButtonUp:
        return true;
    default:
        break;
  }
  return false;
}
// s0 > s3
bool transitionS0S3() {
  switch (shield.getButtons()) {
    case ButtonRight:
        return true;
    default:
        break;
  }
  return false;
}
// dari S1 ke semua state kecuali initial state (s0)
// s1 > s2
bool transitionS1S2() {
  switch (shield.getButtons()) {
    case ButtonUp:
        return true;
    default:
        break;
  }
  return false;
}
// s1 > s3
bool transitionS1S3() {
  switch (shield.getButtons()) {
    case ButtonRight:
        return true;
    default:
        break;
  }
  return false;
}
// s1 > s4
bool transitionS1S4() {
  switch (shield.getButtons()) {
    case ButtonDown:
        return true;
    default:
        break;
  }
  return false;
}

// dari S2 ke semua state kecuali initial state (s0)
// s2 > s1
bool transitionS2S1() {
  switch (shield.getButtons()) {
    case ButtonLeft:
        return true;
    default:
        break;
  }
  return false;
}
// s2 > s3
bool transitionS2S3() {
  switch (shield.getButtons()) {
    case ButtonRight:
        return true;
    default:
        break;
  }
  return false;
}
// s2 > s4
bool transitionS2S4() {
  switch (shield.getButtons()) {
    case ButtonDown:
        return true;
    default:
        break;
  }
  return false;
}

// dari S3 ke semua state kecuali initial state (s0)
// s3 > s1
bool transitionS3S1() {
  switch (shield.getButtons()) {
    case ButtonLeft:
        return true;
    default:
        break;
  }
  return false;
}
// s3 > s2
bool transitionS3S2() {
  switch (shield.getButtons()) {
    case ButtonUp:
        return true;
    default:
        break;
  }
  return false;
}
// s3 > s4
bool transitionS3S4() {
  switch (shield.getButtons()) {
    case ButtonDown:
        return true;
    default:
        break;
  }
  return false;
}