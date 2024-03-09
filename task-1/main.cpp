#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class UserProgressCatalogue {
public:
    UserProgressCatalogue()
        : user_pages_(MAX_USER_COUNT_ + 1, -1)
        , page_users_(MAX_PAGES_, 0)
    {}

    void AddUser(int user, int pages) {
        for (size_t i = user_pages_[user] + 1; i <= pages; ++i) {
            ++page_users_[i];
        }
        user_pages_[user] = pages;
    }

    double CheerUser(int user) {
        if (user_pages_[user] == -1) {
            return 0.0;
        }
        if (page_users_[0] == 1) {
            return 1.0;
        }

        return (page_users_[0] - page_users_[user_pages_[user]]) * 1.0 / (page_users_[0] - 1);
    }

private:
    static const int MAX_USER_COUNT_ = 100000;
    static const int MAX_PAGES_ = 1000;
    
    std::vector<int> user_pages_;
    std::vector<int> page_users_;
};

void Parse(std::istream& input, UserProgressCatalogue& catalogue, const std::string& query, int user) {
    if (query == "READ") {
        int page;
        input >> page;
        catalogue.AddUser(user, page);
    }
    else if (query == "CHEER") {
        std::cout << std::setprecision(6) << catalogue.CheerUser(user) << "\n";
    }
}

int main() {
    UserProgressCatalogue catalogue;

    int query_count;
    std::cin >> query_count;

    for (int i = 0; i < query_count; ++i) {
        std::string query;
        int user;
        std::cin >> query >> user;
        Parse(std::cin, catalogue, query, user);
    }

    return 0;
}
