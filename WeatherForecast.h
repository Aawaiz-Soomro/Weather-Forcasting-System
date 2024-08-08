#ifndef WEATHERFORECAST_H
#define WEATHERFORECAST_H

#include <iostream>
#include <list>
#include <queue>
#include <string>

using namespace std;

struct WeatherData {
    string timestamp;
    float temperature;
    float humidity;

    WeatherData(const string& ts, float temp, float hum) : timestamp(ts), temperature(temp), humidity(hum) {}
};

class AVLNode {
public:
    WeatherData data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const WeatherData& wd) : data(wd), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    AVLTree() : root(nullptr) {}
    void insert(const WeatherData& data);
    AVLNode* search(const string& timestamp);
    void inorder();

private:
    AVLNode* root;
    AVLNode* insert(AVLNode* node, const WeatherData& data);
    AVLNode* search(AVLNode* node, const string& timestamp);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    int getBalance(AVLNode* node);
    int height(AVLNode* node);
    void inorder(AVLNode* node);
};

class WeatherForecastingSystem {
private:
    list<WeatherData> dataCollection;
    AVLTree dataStorage;
    priority_queue<float> maxTempHeap;
    priority_queue<float, vector<float>, greater<float>> minTempHeap;
    priority_queue<float> maxHumidityHeap;
    priority_queue<float, vector<float>, greater<float>> minHumidityHeap;

public:
    void collectData(const string& timestamp, float temperature, float humidity);
    void storeData(const WeatherData& weatherData);
    void analyzeData();
    string generateForecast(const string& timestamp);
    void displayForecast(const string& timestamp);
    void showMenu();
    void handleMenuOption(int option);
};

#endif // WEATHERFORECAST_H
