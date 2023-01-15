#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <set>
using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses,
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator>>(istream& is, Query& q) {
    string type;
    is >> type;
    if  (type== "NEW_BUS"s) {
        q.type= QueryType::NewBus;
        int stop_count=0; 
        string bus_name;
        is >> bus_name >> stop_count;
        q.bus= bus_name;
         q.stops.clear();
        for (int i=0; i< stop_count; i++) {
            string stop;
            is>>stop;
            q.stops.push_back (stop);
        }
    }
    else if  (type=="BUSES_FOR_STOP"s) {
 string stop1;
        is>> stop1;
        q.type=QueryType::BusesForStop;
        q.stop=stop1;
    } 
    else if (type== "STOPS_FOR_BUS"s) {
 string bus;
        is>> bus; 
         q.type=QueryType::StopsForBus;
         q.bus=bus;
    } 
   else if  (type=="ALL_BUSES"s) {
q.type=QueryType::AllBuses;
   } 
        
       
// Реализуйте эту функцию
    return is;
}
//проверяем чтение запроса NEW_BUS
void TestReadingQuery (){
istringstream is;
is.str ("NEW_BUS bus 2 stop1 stop2"s );
Query q;
is>> q;
assert(q.type ==QueryType::NewBus);
assert(q.bus =="bus"s);
assert(q.stops[0] =="stop1"s );
assert(q.stops[1] =="stop2"s );
assert(q.stops.size()==2);
}

struct BusesForStopResponse {
   vector <string> buses;
    // Наполните полями эту структуру
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
    if (!r.buses.empty()){
   bool x=1;
    for (const auto& bus: r.buses) {
        
       if (x) {
            os<< bus;
            x=0;
           
    
        } 
        else {
           os <<' '<< bus ;   
        }
       
    }
    os<< endl;
    }
    else os<<"No stop"s<<endl;// Реализуйте эту функцию
    return os;
}

// проверяем вывод списка автобусов данной остановки
void TestBusesForStop(){
    ostringstream os;
    BusesForStopResponse r;
     os <<r;
    assert (os.str()=="No stop\n"s);
    r.buses={"69"s,  "1231sd"s, "asd"s};
    
    os << r;
    assert (os.str()=="No stop\n69 1231sd asd\n"s);
    r.buses.clear();
    os <<r;
    assert (os.str()=="No stop\n69 1231sd asd\nNo stop\n"s);
}


struct StopsForBusResponse {
    vector<string> stops;
    map<string, vector<string>> interchanges;
      // Наполните полями эту структуру
};

ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
    if (!r.stops.empty()) {
    for (const auto& stop: r.stops){
        os<< "Stop "s<< stop<< ": "s;
        if (r.interchanges.count(stop)==0) {os<<"no interchange"s;}
        else { bool x=1;
        
            for (const auto& bus:r.interchanges.at(stop)) {
            if (x)   {
               os<<bus;
               x=0;
            } 
            else {
                os<<' '<<bus;
            }
            }
             
        }
      os<<endl;  
    } // Реализуйте эту функцию
    }
    else os<<"No bus"<<endl; ;
    return os;
}

//проверяем вывод остановок и пересадок данного автобуса
 void TestStopsForBuses() {
    StopsForBusResponse r;
    ostringstream os;
    r.stops={"Vnukovo"s, "Pulkovo"s, "Domodedovo"s};
    r.interchanges["Vnukovo"]={"32"s, "33"s};
    r.interchanges["Domodedovo"]={"64"s, "69"s, "39"s}; 
    os<< r;
    assert (os.str()== "Stop Vnukovo: 32 33\nStop Pulkovo: no interchange\nStop Domodedovo: 64 69 39\n"s);
}
 
struct AllBusesResponse {
  vector<string> buses;
  map <string, vector<string>> stops_for_buses;   // Наполните полями эту структуру
};

ostream& operator<<(ostream& os, const AllBusesResponse& r) {
    if (!r.buses.empty()) {
        
    for (const auto& bus: r.buses) {
        os<<"Bus "<< bus<<": ";
        bool x=1;
        for ( const auto& stop: r.stops_for_buses.at(bus)) {
            
            if (x) {
                os<<stop;
                x=0;
            }
            else {
                os<<' '<<stop;
            }
            
        }
     os<< endl;    
    }
    }
    else os<<"No buses"<<endl;// Реализуйте эту функцию
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_.insert( bus);
        for ( const auto& stop: stops) {
        stops_.insert(stop);
        stops_for_bus_[bus].push_back(stop);
        buses_for_stop_[stop].push_back(bus);      
        }
       // Реализуйте этот метод
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        BusesForStopResponse result;
        if (count(stops_.begin(), stops_.end(), stop)) {
        for ( const auto& bus:buses_for_stop_.at(stop) ) {
        result.buses.push_back(bus);
        }
        }
       return result; // Реализуйте этот метод
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        StopsForBusResponse result;
        if (count(buses_.begin(), buses_.end(), bus)) {
      for (const auto stop: stops_for_bus_.at(bus) ) {
        result.stops.push_back(stop);
        
        for  (const auto& bus1:buses_for_stop_.at(stop) ) {
           if (bus1!=bus) {result.interchanges[stop].push_back(bus1);}
             
        }
      
      }
      } // Реализуйте этот метод
      return result;
    }

    AllBusesResponse GetAllBuses() const {
       AllBusesResponse result;
       if (!buses_.empty()) {
       for (const auto&bus: buses_){
        result.buses.push_back( bus);
        for (const auto& stop: stops_for_bus_.at(bus)){
            result.stops_for_buses[bus].push_back(stop);
        }
       }
       }
      return result;  // Реализуйте этот метод
    }
private:
   set<string>buses_;
   set<string> stops_;
   map <string, vector<string>> stops_for_bus_;
   map <string, vector<string>> buses_for_stop_;
};
// тестируем методы AddBus и GetBusesForStop
    void TestAddbus(){
        BusManager bm;
        bm.AddBus ( "66"s, {"a"s, "b"s, "c"s, "d"s});
        bm.AddBus ( "69"s, {"e"s, "f"s, "g"s, "d"s});
        BusesForStopResponse result= bm.GetBusesForStop("d"s);
        assert (result.buses[0]=="66"s );
        assert (result.buses[1]=="69"s );
        assert (result.buses.size()==2);
    }

//тестируем AllBuses
void TestAllBuses (){
    BusManager bm;
    ostringstream os;
    os<<bm.GetAllBuses();
    assert (os.str()=="No buses\n"s);
    bm.AddBus ( "66"s, {"a"s, "b"s, "c"s, "d"s});
    bm.AddBus ( "69"s, {"e"s, "f"s, "g"s, "d"s});
    
    os<<bm.GetAllBuses();
    assert (os.str()=="No buses\nBus 66: a b c d\nBus 69: e f g d\n"s);
}
// Реализуйте функции и классы, объявленные выше, чтобы эта функция main
// решала задачу "Автобусные остановки"

int main() {
    TestReadingQuery();
    TestBusesForStop();
    TestAddbus();
    TestStopsForBuses(); 
    TestAllBuses ();
   int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }
}