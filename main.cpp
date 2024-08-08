#include "WeatherForecast.h"
#include "WeatherFcast.cpp"


int main() {
    WeatherForecastingSystem wfs;
    int option;

    while (true) {
        wfs.showMenu();
        cout << "Enter your choice: ";
        cin >> option;
        wfs.handleMenuOption(option);
    }

    return 0;
}

