#include <iostream>
#include <vector>
#include <fstream>
#include <map>


class LogMessage {
private:
    std::string lFatalError = "FatalError";
    std::string lError = "Error";
    std::string lWarning = "Warning";
    std::string lUnknown = "Unknown";

    int count = 0;
    std::vector<std::map<std::string, std::string>> logmes;
    std::vector<LogMessage*> logs_;

    void realization2(const std::string& type, const std::string& message) {
        for (int i = 0; i < logs_.size(); i++) {
            if (type == lFatalError) {
                logs_[i]->logFatalError(message);
            }
            else if (type == lError) {
                logs_[i]->logError(message);
            }
            else if (type == lWarning) {
                logs_[i]->logWarning(message);
            }
            else {
                logs_[i]->logUnknown(message);
            }
        }
     }

protected:
    virtual void logFatalError(const std::string& message) {}
    virtual void logError(const std::string& message) {}
    virtual void logWarning(const std::string& message) {}
    virtual void logUnknown(const std::string& message) {}

public:
    void addError(LogMessage* log) {
        logs_.push_back(log);
    }

    void addLogMessage(const std::string& type, const std::string& message) {
        std::map<std::string, std::string> time;
        time[type] = message;
        logmes.push_back(time);
        count++;
    }

    void realization() {
        for (int i = 0; i < count; i++) {
            if (logmes[i].count(lFatalError)) {
                realization2(lFatalError, logmes[i][lFatalError]);
                logmes[i].clear();
            }
        }
        for (int i = 0; i < count; i++) {
            if (logmes[i].count(lError)) {
                realization2(lError, logmes[i][lError]);
                logmes[i].clear();
            }
        }
        for (int i = 0; i < count; i++) {
            if (logmes[i].count(lWarning)) {
                realization2(lWarning, logmes[i][lWarning]);
                logmes[i].clear();
            }
        }
        for (int i = 0; i < count; i++) {
            if (logmes[i].count(lUnknown)) {
                realization2(lUnknown, logmes[i][lUnknown]);
                logmes[i].clear();
            }
        }
    }

    void RemoveObserver(LogMessage* log) {
        auto it = std::remove(logs_.begin(), logs_.end(), log);
        logs_.erase(it, logs_.end());
    }
};

class myFatalError : public LogMessage {
    void logFatalError(const std::string& message) override {
        try {
            throw message;
        }
        catch (std::string fatal) {
            std::cout << "FatalError: " << fatal << std::endl;
        }
    }
};

class myError : public LogMessage {
    void logError(const std::string& message) override {
        std::ofstream out("Error.txt", std::ios::app);
        if (out.is_open()) {
            out << "Error: " << message << std::endl;
        }
        out.close();
    }
};

class myWarning : public LogMessage {
    void logWarning(const std::string& message) override {
        std::cout << "Warning: " << message << std::endl;
    }
};

class myUnknown : public LogMessage {
    void logUnknown(const std::string& message) override {
        try {
            throw message;
        }
        catch (std::string fatal) {
            std::cout << "Unknown: " << fatal << std::endl;
        }
    }
};

int main() {
    auto logm = new LogMessage();
    auto fat = new myFatalError(); logm->addError(fat);
    auto err = new myError(); logm->addError(err);
    auto war = new myWarning(); logm->addError(war);
    auto unk = new myUnknown(); logm->addError(unk);

    logm->addLogMessage("FatalError", "check 1");
    logm->addLogMessage("Error", "check 2");
    logm->addLogMessage("Warning", "check 3");
    logm->addLogMessage("Unknown", "check 4");

    logm->addLogMessage("FatalError", "check 5");
    logm->addLogMessage("Error", "check 6");
    logm->addLogMessage("Warning", "check 7");
    logm->addLogMessage("Unknown", "check 8");

    logm->addLogMessage("FatalError", "check 9");
    logm->addLogMessage("Error", "check 10");
    logm->addLogMessage("Warning", "check 11");
    logm->addLogMessage("Unknown", "check 12");

    logm->realization();
}