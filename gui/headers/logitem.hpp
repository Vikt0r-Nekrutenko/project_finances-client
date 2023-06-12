#ifndef LOGITEM_HPP
#define LOGITEM_HPP

#include <QDateTime>
#include <string>
#include <vector>

constexpr char lendl = '\n';

class LogItem : public std::vector<std::vector<std::string>>
{
public:

    LogItem &operator << (const std::string &str)
    {
        return pushToStream(str);
    }

    LogItem &operator << (int value)
    {
        return pushToStream(std::to_string(value));
    }

    LogItem &operator << (char value)
    {
        if(value == '\n') {
            push_back({QDateTime().currentDateTime().time().toString("hh:mm:ss").toStdString()});
            return *this;
        }
        return pushToStream(std::string().append(1, value));
    }

protected:

    LogItem &pushToStream(const std::string &str)
    {
        if(size() > 0) {
            back().push_back(str);
        } else {
            push_back({QDateTime().currentDateTime().time().toString("hh:mm:ss").toStdString(), str});
        }
        return *this;
    }
};

#endif // LOGITEM_HPP
