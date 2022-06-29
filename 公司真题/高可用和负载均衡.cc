#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

// Node load in cluster
struct NodeLoad {
  int mode;  // mode, 0-data node, 1-virtual node
  string ip;
  int port;
  double load;  // load value, range is [0,1)
};
// Server class
class Server {
 public:
  bool connect(string &ip, int port);  // connect ip:port
  void close();
  void getClusterLoads(
      vector<NodeLoad> &loads);  // get each node load in this cluster.
};
Server g_Server;
// HA site list
vector<string> g_haIps;  // ip
vector<int> g_haPorts;   // port
// Connect server with specified HA site list.
bool Connect(string &ip, int port, vector<string> &haIps,
             vector<int> &haPorts) {
  // connect.
  while (true) {
    if (g_Server.connect(ip, port)) break;
    std::cerr << "Connect Failed, retry in one second." << std::endl;
    // Sleep(1000);
    sleep(1000);
  }
  // get each node load.
  vector<NodeLoad> nodeLoads;
  vector<int> nodeIds;
  g_Server.getClusterLoads(nodeLoads);
  // add node to ha site list.
  if (haIps.empty()) {
    int index = 0;
    for (auto one : nodeLoads) {
      if (one.mode == 1) continue;
      g_haIps.push_back(one.ip);
      g_haPorts.push_back(one.port);
      nodeIds.push_back(index++);
    }
  } else {
    g_haIps = haIps;
    g_haPorts = haPorts;
    for (int i = 0; i < haIps.size(); i++) {
      int index = 0;
      for (auto one : nodeLoads) {
        if (one.mode == 1) continue;

        if (haIps[i] == one.ip && haPorts[i] == one.port)

          nodeIds.push_back(index);

        index++;
      }
    }
  }
  // get min load node
  string hostTmp = ip;
  int portTmp = port;
  double avg = 1.0;
  for (int i = 0; i < (int)g_haIps.size(); i++) {
    double avgTmp = nodeLoads[nodeIds[i]].load;
    if (avgTmp < avg) {
      hostTmp = g_haIps[i];
      portTmp = g_haPorts[i];
      avg = avgTmp;
    }
    // connect again
    printf("Now connect node: host:%s port:%d\n", hostTmp.c_str(), portTmp);
    g_Server.close();
    g_Server.connect(hostTmp, portTmp);
    return true;
  }
}