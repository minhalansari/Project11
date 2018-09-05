#include<iostream>
using std::cout; using std::endl; using std::boolalpha;
#include<vector>
using std::vector;
#include<string>
using std::string;
#include<utility>
using std::pair;
#include<sstream>
using std::ostringstream;
#include "proj11_mapset.h"

int main(){
    
  MapSet<string,long> ms1({ {"bill",1},{"alan",2},{"abby",3} });
  MapSet<string,long> ms2({ {"alan",4},{"abby", 5},{"john",7} });
  MapSet<string,long> ms3({ {"abby",5}, {"alan",17} });
  
  MapSet<string,long> ms_intersect = ms1.mapset_intersection(ms2);
  ostringstream oss;
  oss << ms_intersect;
  string result1 = oss.str();
  cout<<result1<<endl;
  string ans1 = "abby:3, alan:2";
  oss.str("");
  ms_intersect = ms2.mapset_intersection(ms1);
  oss << ms_intersect;
  string result2 = oss.str();
  cout<<result2<<endl;
  string ans2 = "abby:5, alan:4";
  //ASSERT_EQ(result2, ans2); 


}

