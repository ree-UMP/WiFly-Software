#include "UserManager.h"

UserManager::UserManager() {
    authorizedUsers.insert("alice");
    authorizedUsers.insert("bob");
}

bool UserManager::isAuthorized(const std::string& username) {
    return authorizedUsers.find(username) != authorizedUsers.end();
}
