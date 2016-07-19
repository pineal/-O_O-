//第二题：Log Parser
//有事游戏中有Log用于记录各种状态，想知道究竟用户连接的时间是多少。状态除了START, CONNECTED, DISCONNECTED, SHUTDONW外还有ERROR啥的，但是只需要关注前四个。
//输入形式： vector<string> lines
//(11/01/2015-04:00:00) :: START
//(11/01/2015-04:00:00) :: CONNECTED
//(11/01/2015-04:30:00) :: DISCONNECTED
//(11/01/2015-04:45:00) :: CONNECTED
//(11/01/2015-05:00:00) :: SHUTDOWN
//输出形式：75%%(注意两个百分号)

#include <set>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class LogEvent {
public:
    string status;
    tm timestamp;
    LogEvent(string input) {
        timestamp.tm_mon = atoi(input.substr(1, 2).c_str()) - 1;
        timestamp.tm_mday = atoi(input.substr(4, 2).c_str());
        timestamp.tm_year = atoi(input.substr(7, 4).c_str()) - 1900;
        timestamp.tm_hour = atoi(input.substr(12, 2).c_str());
        timestamp.tm_min = atoi(input.substr(15, 2).c_str());
        timestamp.tm_sec = atoi(input.substr(18, 2).c_str());
        status = input.substr(25, input.size() - 25);
    }
};


class LogEventManager {
public:
    //vector<LogEvent*> queue;
    int active_seconds;
    int connected_seconds;
    bool is_active;
    bool is_connected;
    LogEvent* e_start;
    LogEvent* e_connected;
    LogEvent* e_disconnected;
    LogEvent* e_shutdown;
    LogEventManager() {
        active_seconds = connected_seconds = 0;
        is_active = is_connected = false;
        e_start = nullptr;
        e_connected = nullptr;
        e_disconnected = nullptr;
        e_shutdown = nullptr;
    }
    LogEventManager(const vector<string> & input){
        active_seconds = connected_seconds = 0;
        is_active = is_connected = false;
        e_start = nullptr;
        e_connected = nullptr;
        e_disconnected = nullptr;
        e_shutdown = nullptr;
        builder(input);
    }
    
    void builder(const vector<string> & input) {
        for (int i = 0; i < input.size(); i++) {
            LogEvent* temp = new LogEvent(input[i]);
            if (temp->status == "START") {
                is_active = true;
                e_start = temp;
            } else if (temp->status == "CONNECTED") {
                if (is_active){
                    is_connected = true;
                    e_connected = temp;
                }
            } else if (temp->status == "DISCONNECTED") {
                if (is_connected) {
                    is_connected = false;
                    e_disconnected = temp;
                    connected_seconds += difftime(mktime(&e_disconnected->timestamp), mktime(&e_connected->timestamp));
                }
            } else if (temp->status == "SHUTDOWN") {
                e_shutdown = temp;
                cout<<mktime(&e_shutdown->timestamp)<<endl;
                cout<<mktime(&e_start->timestamp)<<endl;
                cout << difftime(mktime(&e_shutdown->timestamp), mktime(&e_start->timestamp)) << endl;
                active_seconds = difftime(mktime(&e_shutdown->timestamp), mktime(&e_start->timestamp));
                if (is_connected) {
                    connected_seconds += difftime(mktime(&temp->timestamp), mktime(&e_connected->timestamp));
                }
            }
        }
    
    
    }
    string get_percent_connected() {
        string rst = (active_seconds == 0)? 0 : to_string(static_cast<int>(connected_seconds * 100.0 / active_seconds));
        return rst + "%%";
    }
};


//1446380100
//1446377400


//1446376500
//1446377400
//-900
//-200%%
int main(int argc, const char * argv[]) {
    vector<string> input;
    input.emplace_back("(11/01/2015-03:30:00) :: START");
    input.emplace_back("(11/01/2015-03:30:00) :: CONNECTED");
    input.emplace_back("(11/01/2015-04:00:00) :: DISCONNECTED");
    input.emplace_back("(11/01/2015-04:15:00) :: SHUTDOWN");
    LogEventManager* manager = new LogEventManager(input);
    cout << manager->get_percent_connected() << endl;
    return 0;
}
