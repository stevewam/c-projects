/* Calendar Enumerated Types
Steven Williams
May 16, 2021 */

#include <stdio.h>

typedef enum {
	jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
} month;

typedef struct date {
	month m;
	int d;
} date;

/* days_in_month returns the total number of days in each month. 
Only works for non-leap years. */
int days_in_month( month m){
	switch( m){
	case jan: return 31; break;
	case feb: return 28; break;
	case mar: return 31; break;
	case apr: return 30; break;
	case may: return 31; break;
	case jun: return 30; break;
	case jul: return 31; break;
	case aug: return 31; break;
	case sep: return 30; break;
	case oct: return 31; break;
	case nov: return 30; break;
	case dec: return 31; break;
	default: return 0;
	}
};

/* get_month_name returns the full month name. */
char *get_month_name ( month m){
	switch( m){
	case jan: return "January"; break;
	case feb: return "February"; break;
	case mar: return "March"; break;
	case apr: return "April"; break;
	case may: return "May"; break;
	case jun: return "June"; break;
	case jul: return "July"; break;
	case aug: return "August"; break;
	case sep: return "September"; break;
	case oct: return "October"; break;
	case nov: return "November"; break;
	case dec: return "December"; break;
	default: return "Month not recognized.";
	}
}

/* next_date evaluates the next calendar date and return a date enum. */
date next_date( date dt) {
	int this_day = dt.d;
	int this_month = dt.m;

	// modulo operation to evaluate if next day is in the next month
	int next_day = (this_day + 1) % days_in_month( this_month);

	// modulo operation to account for next date after December
	month next_month = (this_month + 1) % 12;
	
	if ( next_day >  this_day) {
		dt.m = this_month; // if next day does not cross over, use the current month
	}
	else {
		dt.m = next_month; // if next day crosses over, use next month
	}
	dt.d = this_day;
	return dt;
}
		
void print_date( date dt) {
	int this_day = dt.d;
	int this_month = dt.m;
	char *this_month_name = get_month_name( this_month);
	printf("%d %s", this_day, this_month_name);
}

int main( void) {
	int day;
	int month;
	date dt;
	date next_dt;
	printf("Enter date (D M): ");
	scanf("%d %d", &day, &month);

	dt.d = day;
	dt.m = month - 1; // - 1 to convert typicall month number to index number
	printf("Date entered:\n");
	print_date( dt);
	printf("\n\n");

	next_dt = next_date( dt);
	printf("Next calendar date\n");
	print_date( next_dt);
	printf("\n\n");

	return 0;
}



