#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iostream>
#include <string>
#include <set>

using namespace std;





class Hiker
{
public:

  string name;
  float speed; // units per minute  whatever units the bridges are in 
  int bridge;//the bridge we 1st encounted this hiker at

};

void operator >> (const YAML::Node& node, Hiker& hiker)
{
  hiker.name = node["name"].as<string>();
  hiker.speed = node["speed"].as<float>();
  hiker.bridge = node["bridge"].as<int>();
}

ostream& operator << (ostream& out, const Hiker& h)
{
  out<<h.name<<"  "
      <<h.speed<<" "
      <<h.bridge<<"\n";
  return out;
}



auto cmpSpeed = [](const Hiker& a, const Hiker& b){ return a.speed > b.speed; };
auto cmpBridge = [](const Hiker& a, const Hiker& b){ return a.bridge < b.bridge; };
using BridgeSet = multiset<Hiker,decltype(cmpBridge)>;
using SpeedSet = multiset<Hiker,decltype(cmpSpeed)>;


float calcTime(const SpeedSet& s,float len)
{
  if(0 == s.size())
  {
    cout<<"Broken input. You must have hikers at the 1st bridge"<<endl;
    exit(1);
  }
  
  auto fast = s.begin();
  float fastTime = len/fast->speed;
  if(s.size() == 1) //special case of 1 hiker. 
  {
    return fastTime;
  }
  
 

  //so it really doesn't matter (according to the explanation I got)
  //if the fastest hiker goes 1st or last. In reality... it would be best
  //to send the slowest 1st, but I guess they can't hike until everyone is across
  float runningTime=0.0f;
  auto cur = ++fast;
  for( ;cur!=s.end();++cur)
  {
    runningTime += len/cur->speed;
    runningTime += fastTime;
  }
  runningTime -= fastTime;//you don't need to go back across the bridge after escorting the last hiker, so remove that. Its faster than tryting to figure out if you are at the end of the set each time through the loop.

  return runningTime;
  
}

void usage()
{
  cout<<"hikerTest <inputfile>"<<endl;
  cout<<"\t inputfile must be legal yaml"<<endl;
}

int main(int argc, char* argv[])
{


  if(argc != 2)
  {
    usage();
  }
  
  YAML::Node doc = YAML::LoadFile(argv[1]);
 

  
  BridgeSet fullHikerSet(cmpBridge);
  const YAML::Node& hikers = doc["hikers"];
  for(unsigned int i=0;i<hikers.size();++i)
  {
    Hiker hiker;
    hikers[i]>>hiker;
    fullHikerSet.insert(hiker);
  }

  vector<float> bridgeVec;
  const YAML::Node& bridges = doc["bridges"];
  for(unsigned int i=0;i<bridges.size();++i)
  {
    float len;
    const YAML::Node& bridge = bridges[i];
    bridgeVec.push_back(bridge["length"].as<float>());
  }

  
  for(auto h: fullHikerSet)
  {
    cout<<h;
  }

  for( auto b: bridgeVec)
  {
    cout<<b<<"\n";
  }

  float totalTime=0.0f;
  SpeedSet currentHikerSet(cmpSpeed);
  for(unsigned int i=0; i< bridgeVec.size();++i)
  {
    auto setItr = fullHikerSet.begin();
    auto setItr2 = setItr;
    while( setItr2->bridge == i )
    {
      setItr2++;
    }
    currentHikerSet.insert(setItr,setItr2);
    fullHikerSet.erase(setItr,setItr2);
    cout<<"current"<<endl;
    for(auto h: currentHikerSet)
    {
      cout<<h;
    }
    totalTime+=calcTime(currentHikerSet, bridgeVec[i] );
    cout<<"time="<<totalTime<<endl;
    
    cout<<"full"<<endl;
    for(auto h: fullHikerSet)
    {
      cout<<h;
    }

    
    
    
  }
  

  
  return 0;
}
