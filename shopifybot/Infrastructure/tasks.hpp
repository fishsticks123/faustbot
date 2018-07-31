//
// Created by Evan Kirkiles on 7/18/18.
//

#ifndef SHOPIFY_BOT_TASKS_HPP
#define SHOPIFY_BOT_TASKS_HPP

#ifndef ShopifyWebsiteHandler
#include <WebAccess/product_scraper.hpp>
#endif
#ifndef put_time
#include <iomanip>
#endif
#ifndef thread
#include <thread>
#endif
#ifndef chrono
#include <chrono>
#endif
#ifndef QObject
#include <QObject>
#endif
#ifndef QCoreApplication
#include <QCoreApplication>
#endif
#ifndef QDateTime
#include <QDateTime>
#endif

// Class containing task-related functions
// Main functionality is a while loop that continuously checks the website for the product
// This is a QObject to allow for QThread functinoality
class Task : public QObject {
        Q_OBJECT
public:

    // Constructor that creates an instance of the task for the specified website, title keywords, color keywords,
    // size, results to check, and frequency (default is to check every 30 seconds to preserve performance).
    explicit Task(const std::string& title, const URLAndMethod& url, const std::string& identifier,
                  const std::string& collection, const std::vector<std::string>& keywords,
                  const std::vector<std::string>& colorKeywords, const std::string& size, const QDateTime& startat,
                  const std::string& profile, const std::string& proxy,
                  unsigned int resultsToCheck=constants::BASE_NUMRESULTS, unsigned int frequency=constants::BASE_FREQ);

    // Boolean which can be disabled to stop the running of the task
    bool shouldcontinue = false;

    // Changed to public so I can copy all of them over into a new Task easily (no copy constructor bc QObject)
    // Title of the task
    const std::string title;

    // Shopify Website Handler
    ShopifyWebsiteHandler swh;
    // Collection in which to search for
    std::string collection;
    // Keywords to check for in the title of the product
    std::vector<std::string> keywords;
    // Keywords to check for in the color of the product
    std::vector<std::string> colorKeywords;
    // Size to check for
    std::string size;
    // Quantity of products to try for
    QDateTime startat;
    // Profile identifier to be given to the Python script to use
    std::string profile;
    // Proxy identifier to be given to the Python script to use
    std::string proxy;
    // How many results to check on the front of each page (in order of most recent)
    unsigned int resultsToCheck;
    // How frequently the check should be run (in seconds)
    unsigned int frequency;

public slots:
    // Runs the task, essentially creating a while loop that runs every [frequency] seconds and continuously checks
    // if there exists a product for the given size.
    void run();
signals:
    // Emitted when the task has finished running
    void finished();
    // Emitted to update the status text
    void status(QString text, QString hexColor);

private:
    // Called to log a message to the tasks log file
    void log(const std::string& message);

    // Orders the product from the given URL using PayPal to ensure consistency
    void order(const std::string& url);
};

// Function which interprets the string form of a vector back into the vector
// Ex. "A,B A,C D W" will produce a vector of size 3 with elements "A", "B A", "C D W"
std::vector<std::string> vectorFromString(const std::string& interpret);

#endif //SHOPIFY_BOT_TASKS_HPP
