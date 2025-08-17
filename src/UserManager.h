#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <unordered_set>

class UserManager {
private:
    std::unordered_set<std::string> authorizedUsers;
public:
    UserManager();
    bool isAuthorized(const std::string& username);
};

#endif
