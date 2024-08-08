#include "WeatherForecast.h"

// AVL Tree functions

int AVLTree::height(AVLNode* node) {
    return node ? node->height : 0;
}

int AVLTree::getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

AVLNode* AVLTree::insert(AVLNode* node, const WeatherData& data) {
    if (!node)
        return new AVLNode(data);

    if (data.timestamp < node->data.timestamp)
        node->left = insert(node->left, data);
    else if (data.timestamp > node->data.timestamp)
        node->right = insert(node->right, data);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && data.timestamp < node->left->data.timestamp)
        return rightRotate(node);

    if (balance < -1 && data.timestamp > node->right->data.timestamp)
        return leftRotate(node);

    if (balance > 1 && data.timestamp > node->left->data.timestamp) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && data.timestamp < node->right->data.timestamp) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::insert(const WeatherData& data) {
    root = insert(root, data);
}

AVLNode* AVLTree::search(AVLNode* node, const string& timestamp) {
    if (!node || node->data.timestamp == timestamp)
        return node;

    if (timestamp < node->data.timestamp)
        return search(node->left, timestamp);
    
    return search(node->right, timestamp);
}

AVLNode* AVLTree::search(const string& timestamp) {
    return search(root, timestamp);
}

void AVLTree::inorder(AVLNode* node) {
    if (node) {
        inorder(node->left);
        cout << node->data.timestamp << " ";
        inorder(node->right);
    }
}

void AVLTree::inorder() {
    inorder(root);
    cout << endl;
}

// Weather Forecasting System functions

void WeatherForecastingSystem::collectData(const string& timestamp, float temperature, float humidity) {
    WeatherData newData(timestamp, temperature, humidity);
    dataCollection.push_back(newData);
    storeData(newData);
}

void WeatherForecastingSystem::storeData(const WeatherData& weatherData) {
    dataStorage.insert(weatherData);
    maxTempHeap.push(weatherData.temperature);
    minTempHeap.push(weatherData.temperature);
    maxHumidityHeap.push(weatherData.humidity);
    minHumidityHeap.push(weatherData.humidity);
}

void WeatherForecastingSystem::analyzeData() {
    cout << "Highest Temperature: " << maxTempHeap.top() << endl;
    cout << "Lowest Temperature: " << minTempHeap.top() << endl;
    cout << "Highest Humidity: " << maxHumidityHeap.top() << endl;
    cout << "Lowest Humidity: " << minHumidityHeap.top() << endl;
    dataStorage.inorder();
}

string WeatherForecastingSystem::generateForecast(const string& timestamp) {
    string forecast = "Weather forecast: ";
    AVLNode* node = dataStorage.search(timestamp);
    if (node) {
        forecast += "Temperature: " + to_string(node->data.temperature) + " degrees, ";
        forecast += "Humidity: " + to_string(node->data.humidity) + "%.";
    } else {
        forecast += "No data available for " + timestamp;
    }
    return forecast;
}

void WeatherForecastingSystem::displayForecast(const string& timestamp) {
    string forecast = generateForecast(timestamp);
    cout << forecast << endl;
}

void WeatherForecastingSystem::showMenu() {
    cout << "Weather Forecasting System Menu" << endl;
    cout << "1. Log weather data" << endl;
    cout << "2. View forecasts" << endl;
    cout << "3. Analyze data" << endl;
    cout << "4. Exit" << endl;
}

void WeatherForecastingSystem::handleMenuOption(int option) {
    string timestamp;
    float temperature, humidity;

    switch (option) {
        case 1:
            cout << "Enter timestamp (YYYY-MM-DD HH:MM:SS): ";
            cin >> timestamp;
            cout << "Enter temperature: ";
            cin >> temperature;
            cout << "Enter humidity: ";
            cin >> humidity;
            collectData(timestamp, temperature, humidity);
            break;
        case 2:
            cout << "Enter timestamp to view forecast (YYYY-MM-DD HH:MM:SS): ";
            cin >> timestamp;
            displayForecast(timestamp);
            break;
        case 3:
            analyzeData();
            break;
        case 4:
            exit(0);
        default:
            cout << "Invalid option. Please try again." << endl;
    }
}
