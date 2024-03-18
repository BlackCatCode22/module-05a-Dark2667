#include <iostream>
#include <iomanip> // Include for std::put_time
#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;

// Function to add months manually (simple version)
tm addMonths(tm date, int monthsToAdd) {
    int yearsToAdd = monthsToAdd / 12;
    monthsToAdd %= 12;
    date.tm_year += yearsToAdd;
    date.tm_mon += monthsToAdd;
    if (date.tm_mon > 11) { // tm_mon is 0-11 for Jan-Dec
        date.tm_year++;
        date.tm_mon -= 12;
    }
    // Note: This does not handle days in month overflow (e.g., adding 1 month to Jan 31)
    return date;
}

int main() {
    // Get current time as time_point
    auto now = system_clock::now();
    time_t now_c = system_clock::to_time_t(now);
    tm now_tm = *localtime(&now_c);

    // User input for adding time
    int months, weeks, days, seconds;
    cout << "Enter months to add: ";
    cin >> months;
    cout << "Enter weeks to add: ";
    cin >> weeks;
    cout << "Enter days to add: ";
    cin >> days;
    cout << "Enter seconds to add: ";
    cin >> seconds;

    // Add months manually
    now_tm = addMonths(now_tm, months);

    // Add weeks, days, and seconds using chrono
    auto final_time = system_clock::from_time_t(mktime(&now_tm))
                    + weeks * duration<int, ratio<604800>>() // weeks to seconds
                    + days * duration<int, ratio<86400>>()   // days to seconds
                    + seconds * duration<int>(); // seconds directly

    // Convert back to tm struct for printing
    time_t final_time_t = system_clock::to_time_t(final_time);
    tm final_tm = *localtime(&final_time_t);

    // Print the final calculated date
    cout << "Calculated date: " << put_time(&final_tm, "%Y-%m-%d %H:%M:%S") << endl;

    return 0;
}
