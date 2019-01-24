#include <fstream>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <unordered_map>
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <unordered_set>
#include <set>
#include <utility>
#include <functional>
#include <queue>

using namespace std;

enum class ConnectionType {
  INTERNAL,
  EXTERNAL
};

enum class ConnectionDirection {
  INPUT,
  OUTPUT,
  INOUT
};

enum class CurrentState {
  END,
  CONN,
  CAP,
  RES
};

class V
{
  public: 
    V(const string &vertex) {
      name = vertex;
      cap = 0;
      isconn = false;
    };
    string name;
    unordered_map <V*, double> succ;
    unordered_map <V*, double> pred;
    bool isconn;
    ConnectionType type;
    ConnectionDirection direction;
    double cap;
};

class Net {
  public:
    Net(const string &net_name) {
      name = net_name;
      total_cap = 0;
    };
    string name;
    double total_cap;
    unordered_map<string, V*> conn;
    unordered_map<string, V*> all_nodes;
    ~Net() {
      for(unordered_map<string, V*>::iterator it = all_nodes.begin(); it != all_nodes.end(); ++it) {
        delete it -> second;
      }
    };
};

class Spef {
  public:
    unordered_map<string, Net*> Nets;
    void addNet(Net* net) {
      Nets.insert(make_pair(net -> name, net));
    }
    string standard;
    string design_name;
    string date;
    string vendor;
    string program;
    string version;
    string design_flow;
    string divider;
    string delimiter;
    string bus_delimiter;
    string t_unit;
    string c_unit;
    string r_unit;
    string l_unit;
};

void spef_parse(ifstream &is, string &delimiter, Net* net);

void add_net(ifstream &is, string &delimiter, Net* net);

void add_conn(ifstream &is, string &delimiter, Net* net, CurrentState &state, string &line);

void add_cap(ifstream &is, string &delimiter, Net* net, CurrentState &state, string &line);

void add_res(ifstream &is, string &delimiter, Net* net, CurrentState &state, string &line);

