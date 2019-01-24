#include "spef_parse.h"



void spef_parse(ifstream &is, string &delimiter, Spef &design)
{
  string line;
  size_t start, end;
  while(!is.eof()) {
    getline(is, line);
    line.push_back(' ');
    start = line.find_first_not_of(delimiter);
    if(start != string::npos) {
      end = line.find_first_of(delimiter, start);
      string attribute = line.substr(start, end - start);
      if(attribute.compare("*T_UNIT") == 0) {
        start = line.find_first_not_of(delimiter, end);
        end = line.find_first_of(delimiter, start);
        start = line.find_first_not_of(delimiter, end);
        end = line.find_first_of(delimiter, start);
        design.t_unit = line.substr(start, end - start);
      }
      else if(attribute.compare("*C_UNIT") == 0) {
        start = line.find_first_not_of(delimiter, end);
        end = line.find_first_of(delimiter, start);
        start = line.find_first_not_of(delimiter, end);
        end = line.find_first_of(delimiter, start);
        design.c_unit = line.substr(start, end - start);
      }
      else if(attribute.compare("*R_UNIT") == 0) {
      
        start = line.find_first_not_of(delimiter, end);
        end = line.find_first_of(delimiter, start);
        start = line.find_first_not_of(delimiter, end);
        end = line.find_first_of(delimiter, start);
        design.r_unit = line.substr(start, end - start);
      }
      else if(attribute.compare("*L_UNIT") == 0) {
        start = line.find_first_not_of(delimiter, end);
        end = line.find_first_of(delimiter, start);
        start = line.find_first_not_of(delimiter, end);
        end = line.find_first_of(delimiter, start);
        design.l_unit = line.substr(start, end - start);
      }
      else if(attribute.compare("*D_NET") == 0) {
        start = line.find_first_not_of(delimiter, end);
        end = line.find_first_of(delimiter, start);
        Net* net = new Net(line.substr(start, end - start));
        start = line.find_first_not_of(delimiter, end);
        end = line.find_first_of(delimiter, start);
        net -> total_cap = atof(line.substr(start, end - start).c_str());
        add_net(is, delimiter, net);
        design.addNet(net);
      }
    }
  }
}

void add_net(ifstream &is, string &delimiter, Net* net)
{
  string line;
  size_t start, end;
  CurrentState state;
  while(state != CurrentState::END) {
    getline(is, line);
    line.push_back(' ');
    start = line.find_first_not_of(delimiter);
    if(start != string::npos) {
      end = line.find_first_of(delimiter, start);
      string attribute = line.substr(start, end - start);
      if(attribute.compare("*END") == 0) {
        state = CurrentState::END;
      }
      else if(attribute.compare("*CONN") == 0) {
        state = CurrentState::CONN;
      }
      else if(attribute.compare("*CAP") == 0) {
        state = CurrentState::CAP;
      }
      else if(attribute.compare("*RES") == 0) {
        state = CurrentState::RES;
      }
      else {
        switch (state) {
          case CurrentState::END:
            break;
          case CurrentState::CONN: add_conn(is, delimiter, net, state, line);
            break;
          case CurrentState::CAP: add_cap(is, delimiter, net, state, line);
            break;
          case CurrentState::RES: add_res(is, delimiter, net, state, line);
            break;
        }
      }        
    }
  }
}

void add_conn(ifstream &is, string &delimiter, Net* net, CurrentState &state, string &line)
{
  size_t start, end;
  start = line.find_first_not_of(delimiter);
  end = line.find_first_of(delimiter, start);
  string attribute = line.substr(start, end - start);
  start = line.find_first_not_of(delimiter, end);
  end = line.find_first_of(delimiter, start);
  string name = line.substr(start, end - start);
  V* node = new V(name);
  if(attribute.compare("*I") == 0) {
    node -> type = ConnectionType::INTERNAL;
  }
  else {
    node -> type = ConnectionType::EXTERNAL;
  }
  start = line.find_first_not_of(delimiter, end);
  end = line.find_first_of(delimiter, start);
  string direction = line.substr(start, end - start);
  if(direction.compare("I") == 0) {
    node -> direction = ConnectionDirection::INPUT;
  }
  else if(direction.compare("O") == 0) {
    node -> direction = ConnectionDirection::OUTPUT;
  }
  else {
    node -> direction = ConnectionDirection::INOUT;
  }
  node -> isconn = true;
  net -> conn.insert(make_pair(name, node));     
}

void add_cap(ifstream &is, string &delimiter, Net* net, CurrentState &state, string &line)
{
  size_t start, end;
  start = line.find_first_not_of(delimiter);
  end = line.find_first_of(delimiter, start);
  string attribute = line.substr(start, end - start);
  start = line.find_first_not_of(delimiter, end);
  end = line.find_first_of(delimiter, start);
  string name = line.substr(start, end - start);
  V* node;
  if(net -> conn.find(name) == net -> conn.end()) {
    node = new V(name);
  }
  else {
    node = net -> conn[name];
  }
  net -> all_nodes.insert(make_pair(name, node));
  start = line.find_first_not_of(delimiter, end);
  end = line.find_first_of(delimiter, start);
  node -> cap = atof(line.substr(start, end - start).c_str());
}

void add_res(ifstream &is, string &delimiter, Net* net, CurrentState &state, string &line)
{
  size_t start, end;
  start = line.find_first_not_of(delimiter);
  end = line.find_first_of(delimiter, start);
  string attribute = line.substr(start, end - start);
  start = line.find_first_not_of(delimiter, end);
  end = line.find_first_of(delimiter, start);
  string u = line.substr(start, end - start);
  start = line.find_first_not_of(delimiter, end);
  end = line.find_first_of(delimiter, start);
  string v = line.substr(start, end - start);
  start = line.find_first_not_of(delimiter, end);
  end = line.find_first_of(delimiter, start);
  double r = atof(line.substr(start, end - start).c_str());
  net -> all_nodes[u] -> succ.insert(make_pair(net -> all_nodes[v], r));
  net -> all_nodes[v] -> pred.insert(make_pair(net -> all_nodes[u], r));
}

