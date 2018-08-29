//
// Created by Evan Kirkiles on 8/27/18.
//

#ifndef SHOPIFY_BOT_CHECKOUT_HPP
#define SHOPIFY_BOT_CHECKOUT_HPP

#ifndef string
#include <string>
#endif
#ifndef ifstream
#include <fstream>
#include <iostream>
#endif
#ifndef put_time
#include <iomanip>
#endif
#ifndef chrono
#include <chrono>
#endif
#include <random>

// cURL include
#ifndef curl
#include <curl/curl.h>
#endif

// Qt includes are already guarded
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QObject>
#include <QApplication>

// Include the global constants
#include <shopifybot/constants.hpp>

// Class containing all checkout related functions in the form of a "Checkout" class
// Will be able to run multiple times until success is had.
class Checkout : public QObject {
    Q_OBJECT
public:
    // Builds the checkout with the given URL for the given profile, proxy, etc.
    explicit Checkout(const std::string& URL, const std::string& cartLink, const std::string& logFileLocation,
                      const std::string& profile, const std::string& proxy, const std::string& identifier);

    // Runs the checkout
    void run();

signals:
    // Sets the status of the task widget
    void setStatus(QString status, QString color);

private:
    // Instances of parameters passed in
    const std::string url, cartLink, logFileLocation, identifier;
    std::string proxy, proxyunp;
    QJsonObject profile, ccard;

    // Must be true for run
    bool allInitialized = false;

//    // Sends the customer info, returning true if it was a success
//    bool sendCustomerInfo();
//    // Sends the payment info, returning true if it was a success
//    bool sendPaymentInfo();

    // Logs a line to the given log file
    void log(const std::string& message);
};

#endif //SHOPIFY_BOT_CHECKOUT_HPP