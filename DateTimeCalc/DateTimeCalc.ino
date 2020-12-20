#define MONTH_SIZE 12
#define HOURTIME 60
#define DAY_HOURS 24
#define OFFSET 1

// January 1, Feburary 2, March 3, April 4, May 5, June 6, July 7
// August 8, September 9, October 10, Novemeber 11, Decemebe 12

// Struct to hold input values
struct DateTime
{
  int month;
  int day;
  int hours;
  int minutes;
  // Always in minutes
};

char buff[15];

struct DateTime current;

void setup() {
  // put your setup code here, to run once:
  
  current.month = 12;
  current.day = 19;
  current.hours = 4;
  current.minutes = 30;

  Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
  // If the offset plus minutes is bigger than an hour, begin the program
  //Serial.println(current.minutes + " Hello");
  delay(1000);
  struct DateTime next = GetNewAlarm(current);
  current = next;
  sprintf(buff,"%d:%d",current.hours,current.minutes);
  Serial.println(buff);

}

struct DateTime GetNewAlarm(struct DateTime curr) {

  int newMinutes;
  int newHours;
  int newDay;
  int newMonth;
  int hoursInOffset;

  if (curr.minutes >= HOURTIME) {
    // If the
    newMinutes == (curr.minutes + OFFSET) % HOURTIME;
    hoursInOffset == (curr.minutes + OFFSET) / HOURTIME;
    newHours == hoursInOffset + curr.hours;
    if (hoursInOffset >= 24) {
      switch (curr.month){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
        if (curr.day != 31) {
          newDay = curr.day + (newHours / DAY_HOURS);
          newMonth = curr.month;
        } else {
          newDay = 1 + (newHours / DAY_HOURS);
          newMonth = curr.month + 1;
        }
        break;
        case 4:
        case 6:
        case 9:
        case 11:
        if (curr.day != 30) {
          newDay = curr.day + (newHours / DAY_HOURS);
          newMonth = curr.month;
        } else {
          newDay = 1 + (newHours / DAY_HOURS);
          newMonth = curr.month + 1;
        }
        break;
        case 2:
        if (curr.day != 29) {
          newDay = curr.day + (newHours / DAY_HOURS);
          newMonth = curr.month;
        } else {
          newDay = 1 + (newHours / DAY_HOURS);
          newMonth = curr.month + 1;
        }
        default:
        break;
      }
    }
  } else {
    newMinutes = curr.minutes + OFFSET;
    newHours = curr.hours;
    newDay = curr.day;
    newMonth = curr.month;
  }
  struct DateTime newtime;
  newtime.minutes=newMinutes;
  newtime.hours=newHours;
  newtime.day=newDay;
  newtime.month=newMonth;
  return(newtime);
}
