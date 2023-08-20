#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <time.h>
#include "Interface.h"

using namespace std;

// returns the current date
string get_current_time(void)
{
    // getting the current time
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // we should add 1900 to the year and 1 to the month for the correct results
    int yyyy = 1900 + ltm->tm_year;
    int mm = 1 + ltm->tm_mon;
    int dd = ltm->tm_mday;
    int h = ltm->tm_hour;
    int min = ltm->tm_min;

    // we should make a string out of the current day
    string day = to_string(dd);
    // making the string valid if it is less than 1 digit
    if(dd < 10)
    {
        string new_day = "0";
        new_day.append(day);
        day = new_day;
    }  

    // we should make a string out of the current month
    string month = to_string(mm);
    // making the string valid if it is less than 1 digit
    if(mm < 10)
    {
        string new_month = "0";
        new_month.append(month);
        month = new_month;
    }

    // we should make a string out of the current year
    string year = to_string(yyyy);
    
    string hour = to_string(h);

    string minute = to_string(min);

    // appending the three strings and some '-' in between to form the date string
    string date;
    date.append(day);
    date.append("-");
    date.append(month);
    date.append("-");
    date.append(year);
    
    string time;
    time.append(date);
    time.append(" ");
    time.append(hour);
    time.append(":");
    time.append(minute);

    return time;
}

float* create_float(float value)
{
    float* pointer = new float();
    *pointer = value;
    return pointer;
}

float* float_array_to_list(List* percentages)
{
    float* float_array = new float[percentages->get_size()];

    ListNode* node = percentages->get_first();
    int i = 0;
    while(node != NULL)
    {
        float_array[i] = *((float *) node->get_value());
        node = node->get_next();
        i++;
    }

    return float_array;
}

float* get_results(float starter, List* percentages)
{
    float* percentages_array = float_array_to_list(percentages);
    int size = percentages->get_size();
    
    float** divisions_array = new float*[size];

    for(int i=0; i<percentages->get_size(); i++)
    {
        size--;
        divisions_array[i] = new float[size];
        for(int j=i+1; j<percentages->get_size(); j++)
        {
            divisions_array[i][j-(i+1)] = percentages_array[i]/percentages_array[j];
        }
    }

    float* results = new float[percentages->get_size()];

    results[0] = starter/10.0;
    for(int i=1; i<percentages->get_size(); i++)
    {
        int count = 0;
        results[i] = 0;
        for(int j=i-1; j>=0; j--)
        {
            count++;
            results[i] = results[i] + results[j] * divisions_array[j][i-j-1];

        }
        results[i] = results[i] / ((float) count);

    } 

    delete[] percentages_array;
    for(int i=0; i<percentages->get_size(); i++)
    {
        delete[] divisions_array[i];
    }
    delete[] divisions_array;

    return results;
}

int main(void)
{
    List* countries = new List();
    List* percentages = new List();

    string country;
    float percentage;

    while(1)
    {
        cout << "Give me country" << endl;
        cin >> country;

        if(country == "No") break;

        string* new_country = new string(country);
        countries->ListInsertLast(new_country);

        cout << "Give me percentage" << endl;
        cin >> percentage;

        percentages->ListInsertLast(create_float(percentage));
    }

    float territories;
    cout << "Give leader's territories" << endl;
    cin >> territories;

    float all_territories;
    cout << "Give all territories" << endl;
    cin >> all_territories; 

    float starter = all_territories/territories;

    float* results = get_results(starter, percentages);

    ListNode* node = countries->get_first();
    int i = 0;

    fstream file;
    file.open("wwbot_booking_updates.txt", std::ios_base::app);
    string time = get_current_time();
    file.write(time.data(), time.size());
    file.write("\n", strlen("\n"));

    while(node != NULL)
    {
        string country = *((string*) node->get_value());
        string line = country.append(": ");
        line = line.append(to_string(results[i]));
        file.write(line.data(), line.size());
        file.write("\n", strlen("\n"));
        i++;
        node=node->get_next();
    }

    file.write("\n", strlen("\n"));
    list_destroy_countries(countries);
    list_destroy_percentages(percentages);
    delete[] results;

}