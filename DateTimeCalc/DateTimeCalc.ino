#define MONTH_SIZE 12
#define HOURTIME 60
#define DAY_HOURS 24
#define OFFSET 1

// January 1, Feburary 2, March 3, April 4, May 5, June 6, July 7
// August 8, September 9, October 10, Novemeber 11, Decemebe 12

// Struct to hold input values
typedef struct DateTime
{
  int month;
  int day;
  int hours;
  int minutes;
  // Always in minutes
} DateTime;

char buff[15];

DateTime current;

void setup() {
  // put your setup code here, to run once:
  
  current.month = 12;
  current.day = 19;
  current.hours = 22;
  current.minutes = 30;

  Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
  // If the offset plus minutes is bigger than an hour, begin the program
  //Serial.println(current.minutes + " Hello");
  delay(1000);
  DateTime next = GetNewAlarm(current);
  current = next;
  sprintf(buff,"%d:%d %d %d",current.hours,current.minutes,current.day,current.month);
  Serial.println(buff);

}



DateTime GetNewAlarm(struct DateTime curr) {

  int newMinutes;
  int newHours;
  int newDay;
  int newMonth;
  int hoursInOffset;

  if (curr.minutes <= HOURTIME) {
    // If the
    newMinutes = (curr.minutes + OFFSET) % HOURTIME;
    hoursInOffset = (curr.minutes + OFFSET) / HOURTIME;
    newHours = hoursInOffset + curr.hours;
    if (newHours <= 24) {
      newHours %= 24;
      switch (curr.month){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
        newDay = curr.day + (newHours / DAY_HOURS);
        newMonth = curr.month+(newDay/31);
        newDay %= 31;
        break;
        case 4:
        case 6:
        case 9:
        case 11:
        newDay = curr.day + (newHours / DAY_HOURS);
        newMonth = curr.month+(newDay/30);
        newDay %= 30;
        break;
        case 2:
        newDay = curr.day + (newHours / DAY_HOURS);
        newMonth = curr.month+(newDay/28);
        newDay %= 28;
        default:
        break;
      }
    }
  }// else {
//    newMinutes = curr.minutes + OFFSET;
//    newHours = curr.hours;
//    newDay = curr.day;
//    newMonth = curr.month;
  DateTime newtime;
  newtime.minutes=newMinutes;
  newtime.hours=newHours;
  newtime.day=newDay;
  newtime.month=newMonth;
  return(newtime);
}
