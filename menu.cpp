#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int choice;

    do
    {
        //display menu
        cout << "\n Overtale Menu \n\n";
        cout << "1. Back to game \n";
        cout << "2. User settings \n";
        cout << "3. Game credits \n";
        cout << "4. Quit game  \n";
        cout << "\nEnter your selection: ";

        //get selection
        cin >> choice;

        //evaluate option
        switch (choice)
        {
        case 1:
            cout << "Going back to game \n";
            break;
        case 2:
            cout << "Show user settings\n";
            break;
        case 3:
            cout << "Show credits\n";
            break;
        default:
            cout << "Invalid selection. Please enter a menu option\n";
        }

    } while (choice != 4);
    return 0;
}
