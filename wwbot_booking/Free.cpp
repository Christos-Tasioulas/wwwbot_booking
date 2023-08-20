// C++ file to destroy complicated data structures
#include "Interface.h"

using namespace std;

// destroying everything the given countries list list includes
void list_destroy_countries(List* countries)
{
    ListNode* node;
    node = countries->get_first();
    while(node != NULL)
    {
        string* country;
        country = (string*) node->get_value();
        delete country;
        node = node->get_next();
    }
    delete countries;
}

// destroying everything the given percentages list list includes
void list_destroy_percentages(List* percentages)
{
    ListNode* node;
    node = percentages->get_first();
    while(node != NULL)
    {
        float* percentage;
        percentage = (float*) node->get_value();
        delete percentage;
        node = node->get_next();
    }
    delete percentages;   
}