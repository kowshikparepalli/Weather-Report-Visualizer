#include <iostream>
#include <string>
using namespace std;

// ABSTRACT BASE CLASS
class Weather {
private:
    string day;
    float temperature;
    float humidity;
    float windSpeed;

public:
    Weather(string d, float t, float h, float w) {
        day = d;
        temperature = t;
        humidity = h;
        windSpeed = w;
    }

    // ENCAPSULATION
    string getDay() {
        return day;
    }

    float getTemperature() {
        return temperature;
    }

    float getHumidity() {
        return humidity;
    }

    float getWindSpeed() {
        return windSpeed;
    }

    // ABSTRACTION
    virtual string getWeatherType() = 0;
    virtual string getCondition() = 0;

    virtual ~Weather() {}
};

// INHERITANCE - SUNNY
class Sunny : public Weather {
public:
    Sunny(string d, float t, float h, float w)
        : Weather(d, t, h, w) {}

    string getWeatherType() override {
        return "Sunny";
    }

    string getCondition() override {
        return "Clear sky and bright sunshine";
    }
};

// INHERITANCE - RAINY
class Rainy : public Weather {
public:
    Rainy(string d, float t, float h, float w)
        : Weather(d, t, h, w) {}

    string getWeatherType() override {
        return "Rainy";
    }

    string getCondition() override {
        return "Rainy conditions";
    }
};

// INHERITANCE - CLOUDY
class Cloudy : public Weather {
public:
    Cloudy(string d, float t, float h, float w)
        : Weather(d, t, h, w) {}

    string getWeatherType() override {
        return "Cloudy";
    }

    string getCondition() override {
        return "Cloud-covered sky";
    }
};

// WEATHER VISUALIZER
class WeatherVisualizer {
private:
    Weather* records[100];
    int count;

public:
    WeatherVisualizer() {
        count = 0;
    }

    // VALIDATE DAY NAME
    bool isValidDay(string day) {
        string days[7] = {
            "Monday", "Tuesday", "Wednesday",
            "Thursday", "Friday", "Saturday",
            "Sunday"
        };

        for (int i = 0; i < 7; i++) {
            if (day == days[i]) {
                return true;
            }
        }

        return false;
    }

    // ADD WEATHER DATA
    void addWeather(string day, float temp,
                    float humidity, float wind) {

        if (count >= 100) {
            cout << "Maximum records reached!\n";
            return;
        }

        Weather* w;

        // AUTOMATIC WEATHER DETECTION
        if (humidity >= 80) {
            w = new Rainy(day, temp, humidity, wind);
        }
        else if (temp >= 30 && humidity < 60) {
            w = new Sunny(day, temp, humidity, wind);
        }
        else {
            w = new Cloudy(day, temp, humidity, wind);
        }

        records[count] = w;
        count++;

        cout << "\nWeather data added successfully!\n";
        cout << "Detected Weather: "
             << w->getWeatherType() << endl;
    }

    // DISPLAY WEATHER REPORT
    void displayData() {
        if (count == 0) {
            cout << "\nNo weather data available!\n";
            return;
        }

        cout << "\n========== WEATHER REPORT ==========\n";

        for (int i = 0; i < count; i++) {
            cout << "\nDay: "
                 << records[i]->getDay();

            cout << "\nTemperature: "
                 << records[i]->getTemperature() << " C";

            cout << "\nHumidity: "
                 << records[i]->getHumidity() << "%";

            cout << "\nWind Speed: "
                 << records[i]->getWindSpeed() << " km/h";

            cout << "\nWeather Type: "
                 << records[i]->getWeatherType();

            cout << "\nCondition: "
                 << records[i]->getCondition();

            cout << "\n-----------------------------\n";
        }
    }

    // TEMPERATURE GRAPH
    void temperatureGraph() {
        if (count == 0) {
            cout << "\nNo data available!\n";
            return;
        }

        cout << "\n====== TEMPERATURE GRAPH ======\n";

        for (int i = 0; i < count; i++) {
            cout << records[i]->getDay() << " | ";

            int bars = (int)records[i]->getTemperature();

            if (bars < 0)
                bars = 0;

            if (bars > 50)
                bars = 50;

            for (int j = 0; j < bars; j++) {
                cout << "#";
            }

            cout << " " << records[i]->getTemperature()
                 << " C\n";
        }
    }

    // HUMIDITY GRAPH
    void humidityGraph() {
        if (count == 0) {
            cout << "\nNo data available!\n";
            return;
        }

        cout << "\n====== HUMIDITY GRAPH ======\n";

        for (int i = 0; i < count; i++) {
            cout << records[i]->getDay() << " | ";

            int bars = (int)records[i]->getHumidity() / 2;

            for (int j = 0; j < bars; j++) {
                cout << "*";
            }

            cout << " " << records[i]->getHumidity()
                 << "%\n";
        }
    }

    // WEATHER STATISTICS
    void statistics() {
        if (count == 0) {
            cout << "\nNo data available!\n";
            return;
        }

        float sum = 0;
        float maxTemp = records[0]->getTemperature();
        float minTemp = records[0]->getTemperature();

        for (int i = 0; i < count; i++) {
            float temp = records[i]->getTemperature();

            sum += temp;

            if (temp > maxTemp)
                maxTemp = temp;

            if (temp < minTemp)
                minTemp = temp;
        }

        cout << "\n====== WEATHER STATISTICS ======\n";

        cout << "Average Temperature: "
             << sum / count << " C\n";

        cout << "Maximum Temperature: "
             << maxTemp << " C\n";

        cout << "Minimum Temperature: "
             << minTemp << " C\n";
    }

    // DESTRUCTOR
    ~WeatherVisualizer() {
        for (int i = 0; i < count; i++) {
            delete records[i];
        }
    }
};

// MAIN FUNCTION
int main() {
    WeatherVisualizer visualizer;
    int choice;

    do {
        cout << "\n================================\n";
        cout << "     WEATHER DATA VISUALIZER\n";
        cout << "================================\n";

        cout << "1. Enter Weather Data\n";
        cout << "2. Display Weather Report\n";
        cout << "3. Temperature Graph\n";
        cout << "4. Humidity Graph\n";
        cout << "5. Weather Statistics\n";
        cout << "6. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1: {
            string day;
            float temp, humidity, wind;

            // VALID DAY INPUT
            do {
                cout << "\nEnter Day "
                     << "(Monday to Sunday): ";
                cin >> day;

                if (!visualizer.isValidDay(day)) {
                    cout << "Invalid day! "
                         << "Please enter a correct day.\n";
                }

            } while (!visualizer.isValidDay(day));

            // WEATHER INPUT
            cout << "Enter Temperature (C): ";
            cin >> temp;

            cout << "Enter Humidity (%): ";
            cin >> humidity;

            cout << "Enter Wind Speed (km/h): ";
            cin >> wind;

            if (!cin || temp < -100 || temp > 100 ||
                humidity < 0 || humidity > 100 ||
                wind < 0) {

                cout << "Invalid weather data!\n";
                cin.clear();
                cin.ignore(1000, '\n');
                break;
            }

            visualizer.addWeather(
                day, temp, humidity, wind
            );

            break;
        }

        case 2:
            visualizer.displayData();
            break;

        case 3:
            visualizer.temperatureGraph();
            break;

        case 4:
            visualizer.humidityGraph();
            break;

        case 5:
            visualizer.statistics();
            break;

        case 6:
            cout << "\nThank you for using "
                 << "Weather Data Visualizer!\n";
            break;

        default:
            cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
