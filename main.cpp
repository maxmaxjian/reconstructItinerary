#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>

using std::vector;
using std::string;
using std::pair;

class solution {
  public:
    vector<string> findItinerary(const vector<pair<string,string>> & tickets) {
        std::unordered_map<string, std::set<string>> from_to;
        for (size_t i = 0; i < tickets.size(); i++) {
            if (from_to.find(tickets[i].first) == from_to.end())
                from_to.insert(std::make_pair(tickets[i].first, std::set<string>()));
            from_to[tickets[i].first].insert(tickets[i].second);
        }

        for(auto it = from_to.begin(); it != from_to.end(); ++it) {
            std::cout << it->first << ": ";
            std::for_each(it->second.begin(), it->second.end(), [](auto && s){std::cout << s << " ";});
            std::cout << std::endl;
        }

        vector<string> itin;
        itin.push_back("JFK");
        auto it = from_to.find(itin.back());
        while (it != from_to.end()) {
            // std::cout << "found " << it->first << std::endl;
            auto jt = it->second.begin();
            itin.push_back(*jt);
            if (it->second.size() > 1)
                it->second.erase(it->second.begin());
            else
                from_to.erase(it);
            it = from_to.find(itin.back());
        }

        return itin;
    }
};

int main() {
    // vector<pair<string,string>> tickets{
    //     std::make_pair("MUC","LHR"),
    //     std::make_pair("JFK","MUC"),
    //     std::make_pair("SFO","SJC"),
    //     std::make_pair("LHR","SFO")
    // };

    vector<pair<string,string>> tickets{
        std::make_pair("JFK","SFO"),
        std::make_pair("JFK","ATL"),
        std::make_pair("SFO","ATL"),
        std::make_pair("ATL","JFK"),
        std::make_pair("ATL","SFO")    
    };

    solution soln;
    auto itinerary = soln.findItinerary(tickets);
    std::cout << "The itinerary is:" << std::endl;
    std::for_each(itinerary.begin(), itinerary.end(), [](string & s){ std::cout << s << " "; });
    std::cout << std::endl;
}
