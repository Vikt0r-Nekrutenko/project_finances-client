#ifndef LOGITEM_HPP
#define LOGITEM_HPP

#include <QDateTime>
#include <string>
#include <vector>

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
