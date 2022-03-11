#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

#include <string>
#include <vector>

using namespace std;

class NetTime {
public:
    NetTime() 
    {
        hour = 3;
        minute = 0;
    }

    NetTime(const string& time_str) 
    {
        hour = int(time_str[0] + time_str[1]);
        minute = int(time_str[3] + time_str[4]);
    }

    int hour;
    int minute;
};

class Device {
public:
    Device() 
    {
        dev_name = "Default_company";
        dev_batch = "404,";
        port = "port1";
    }

    Device(string dev, string batch, string inp_port) 
    {
        dev_name = dev;
        dev_batch = batch;
        port = inp_port;
    }

    string GetPort() { return port; }

private:
    string dev_name;
    string dev_batch;
    string port;
};

class NetLoad {
public:
    NetLoad() 
    {
        date = "30.12.1950";
        time = NetTime();
        device = Device();
        traffic = 0.0;
    }
    double GetTraffic()      { return traffic; }
    NetTime GetTime()        { return time; }

    void SetDate(const string& data) { date = data; }
    void SetTime(const string& data) { time = NetTime(data); }
    void SetDevice(const string& dev, const string& batch, const string& inp_port) 
    { 
        device = Device(dev, batch, inp_port); 
    }
    void SetTraffic(const double& val) { traffic = val; }

    string GetPort() { return device.GetPort(); }

    string IsNormal(NetLoad& normal)
    {
        double low_border = normal.CalcLowBorder();
        double high_border = normal.CalcHighBorder();

        if (low_border > traffic) {
            return "Traffic is below normal";
        }
        else if (high_border >= traffic) {
            return "Traffic within normal limits";
        }
        else
            return "Traffic is above normal";
    }

private:
    double CalcLowBorder() { return traffic * 0.9; }
    double CalcHighBorder() { return traffic * 1.3; }

    string date;
    NetTime time;
    Device device;
    double traffic;
};

istream& operator>>(istream& stream, NetLoad& net_load) 
{
    string data1;

    stream >> data1;
    net_load.SetDate(data1);

    stream >> data1;
    net_load.SetTime(data1);

    string data2, data3;
    stream >> data1 >> data2 >> data3 ;
    net_load.SetDevice(data1, data2, data3);

    double val;
    net_load.SetTraffic(val);
    
    return stream;
    //In: 10.01.2021 18:15 Cisco 5300, port1  708.117
}

int main()
{
    vector<NetLoad> net_load_vec; 
    NetLoad net_load;

    //import file
    cout << "Enter file name: ";
    string file_name;
    cin >> file_name;

    fstream finput(file_name);
    while (finput) {
        finput >> net_load;
        net_load_vec.push_back(net_load);
    }
    cout << "File is readed!" << endl;
    //read info from port
    //Handle
    cout << "Commands: end, next" << endl;
    cout << "Enter command: ";

    string command = "next";
    while (command != "end") 
    {
        cout << "Enter command: ";
        cin >> command;

        if (command == "next") {
            cout << "Enter data: ";
            cin >> net_load;

            string port = net_load.GetPort();
            NetTime time = net_load.GetTime();

            NetLoad normal1, normal2;
            for (auto& el : net_load_vec) {
                if (el.GetPort() == port) {
                    int new_hour = el.GetTime().hour;
                    if (new_hour == time.hour) { normal1 = el; }
                    if (new_hour == time.hour + 1) { normal2 = el; }
                }  
            }

            double traf1 = normal1.GetTraffic(), traf2 = normal2.GetTraffic(), res_traf;
            if (time.minute == 0) {
                res_traf = traf1;
            }
            if (time.minute == 15) {
                res_traf = (traf1 + (traf1 + traf2) / 2) / 2;
            }
            else if (time.minute == 30) {
                res_traf = (traf1 + traf2) / 2;
            }
            else if (time.minute == 45) {
                res_traf = (traf2 - (traf1 + traf2) / 2) / 2;
            }
            
            normal1.SetTraffic(res_traf);
            cout << net_load.IsNormal(normal1) << endl;
        }
        else { cout << "unknown command" << endl; }
    }
    cout << "See you in da final!";
    return 1;
}


//In: 10.01.2021 18 : 15 Cisco 5300, port1  708.117

//Out : Трафик ниже нормы