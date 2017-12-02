#define USE_USBCON
#include <Encoder.h>
#include <Servo.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/UInt16.h>


Servo myservo;


void servo(const std_msgs::UInt16& data)
{
  myservo.write(data.data);
}

ros::NodeHandle nh;
geometry_msgs::Twist enc_value;
ros::Publisher chatter("encoders", &enc_value);
ros::Subscriber<std_msgs::UInt16> listener("pid", servo);

Encoder knobLeft(22,24);
Encoder knobRight(23,25);

double newLeft, newRight;
double tar_vel = 0;

void setup() {
  Serial.begin(9600);
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(listener);

  myservo.attach(9);
}

void loop() {

    newLeft = knobLeft.read();
    newRight = knobRight.read();

    //Serial.print("newLeft: ");
    //Serial.print(newLeft);
    //Serial.print("         newRight:");
    //Serial.println(newRight);

    enc_value.linear.x = newLeft;
    enc_value.linear.y = newRight;
    //tar_vel = tar_vel + 1;
    //enc_value.linear.z = tar_vel;
    chatter.publish( &enc_value);
    nh.spinOnce();
    delay(20);
    
}
