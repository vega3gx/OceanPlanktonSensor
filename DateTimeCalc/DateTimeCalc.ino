#define month_size 12
#define HOURTIME 60
#define DAY_HOURS 24

int newMinutes;
int newHours;
int newDay;
int newMonth;
int hoursInOffset;

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
  int offset;
};


void setup() {
  // put your setup code here, to run once:


}

void loop() {
  // put your main code here, to run repeatedly:
  // If the offset plus minutes is bigger than an hour, begin the program
  if (DateTime.offset + DateTime.minutes) >= HOURTIME {
    // If the
    newMinutes == (DateTime.minutes + DateTime.offset) % HOURTIME;
    hoursInOffset == (DateTime.minutes + DateTime.offset) / HOURTIME;
    newHours == hoursInOffset + DateTime.hours;
    if hoursInOffset >= 24 {
    if DateTime.month == 1, 3, 5, 7, 8, 10, 12 {
      if DateTime.day != 31 {
        newDay = DateTime.day + (newhours / DAY_HOURS);
          newMonth = DateTime.month;
        } else {
          newDay = 1 + (newhours / DAY_HOURS);
          newMonth = DateTime.month + 1;
        }
      } else if DateTime.month == 4, 6, 9, 11 {
      if DateTime.day != 30 {
        newDay = DateTime.day + (newhours / DAY_HOURS);
          newMonth = DateTime.month;
        } else {
          newDay = 1 + (newhours / DAY_HOURS);
          newMonth = DateTime.month + 1;
        }
      } else {
        if DateTime.day != 29 {
        newDay = DateTime.day + (newhours / DAY_HOURS);
          newMonth = DateTime.month;
        } else {
          newDay = 1 + (newhours / DAY_HOURS);
          newMonth = DateTime.month + 1;
        }
      }
    }
  } else {
    newMinutes = DateTime.minutes + DateTime.offset;
    newHours = DateTime.hours;
    newDay = DateTime.day;
    newMonth = DateTime.month;
  }


}
