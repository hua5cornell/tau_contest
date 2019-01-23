#include "spef_parse.cpp"



int main(int argc, char *argv[]) {
  string t = "test";
  Net* net = new Net(t);
  ifstream is(argv[1]);
  string delimiter = " ";
  Spef design;
  spef_parse(is, delimiter, design);
  cout << "t_unit = " << design.t_unit << endl;
  cout << "c_unit = " << design.c_unit << endl;
  cout << "r_unit = " << design.r_unit << endl;
  cout << "l_unit = " << design.l_unit << endl;
  cout << "The design has " << design.Nets.size() << " nets" << endl;
  cout << "They are " << endl;
  for(unordered_map <string, Net*>::iterator it = design.Nets.begin(); it != design.Nets.end(); ++it) {
    cout << it -> first << endl;
    Net* net = it -> second;
    cout << "The net has " << net -> conn.size() << " connections" << endl;
    cout << "They are " << endl;
    for(unordered_map <string, V*>::iterator it_2 = net -> conn.begin(); it_2 != net -> conn.end(); ++it_2) {
      cout << it_2 -> first << endl;
      if(it_2 -> second -> type == ConnectionType::INTERNAL) {
        cout << "It is an internal node which is ";
        if(it_2 -> second -> direction == ConnectionDirection::INPUT) {
          cout << "an input" << endl;
        }
        else if(it_2 -> second -> direction == ConnectionDirection::OUTPUT) {
          cout << "an output" << endl;
        }
        else {
          cout << "an inout" << endl;
        }
      }
      else {
        cout << "It is an external node which is ";
        if(it_2 -> second -> direction == ConnectionDirection::INPUT) {
          cout << "an input" << endl;
        }
        else if(it_2 -> second -> direction == ConnectionDirection::OUTPUT) {
          cout << "an output" << endl;
        }
        else {
          cout << "an inout" << endl;
        }
      }
    }
    cout << "The net has " << net -> all_nodes.size() << " capacitances and the total capacitance is " << net -> total_cap << endl;
    cout << "They are " << endl;
    for(unordered_map <string, V*>::iterator it_2 = net -> all_nodes.begin(); it_2 != net -> all_nodes.end(); ++it_2) {
      cout << it_2 -> first << " = " << it_2 -> second -> cap << endl;
      V* node = it_2 -> second;
      for(unordered_map<V*, double>::iterator it_3 = node -> succ.begin(); it_3 != node -> succ.end(); ++it_3) {
        cout << "there is resistance between " << it_2 -> first << " and " << it_3 -> first -> name << " which is " << it_3 -> second << endl;
      }
    }
  }
  delete net;
  return 0;
}

