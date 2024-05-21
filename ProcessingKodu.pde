import processing.serial.*;

Serial myPort;

void setup(){
  size(300, 300);
  myPort = new Serial(this, "COM6", 9600);
}

void draw(){
  background(0,0,0);
  if(mousePressed && (mouseButton == LEFT)){
    myPort.write('1');
  }
  if (mousePressed && (mouseButton == RIGHT)){
    myPort.write('0');
  }
}
