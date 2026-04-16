#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <climits>
#include <fstream>
#include <cstdlib>
#include <functional>

using namespace std;

// ---------------- TICKET ----------------
struct Ticket {
    string source, destination;
    int fare, distance;
};

// ---------------- METRO ----------------
class Metro {
public:
    map<string, vector<pair<string,int>>> adj;
    map<string,string> line, color;

    void addEdge(string u,string v,int d){
        adj[u].push_back({v,d});
        adj[v].push_back({u,d});
    }

    void showStations(){
        cout<<"\n📍 Stations:\n";
        for(auto &p:adj) cout<<"- "<<p.first<<endl;
    }

    string findStation(string input){
        transform(input.begin(),input.end(),input.begin(),::tolower);
        for(auto &p:adj){
            string s=p.first,temp=s;
            transform(temp.begin(),temp.end(),temp.begin(),::tolower);
            if(temp.find(input)!=string::npos) return s;
        }
        return "";
    }

    void suggest(string input){
        transform(input.begin(),input.end(),input.begin(),::tolower);
        cout<<"\n🔎 Suggestions:\n";
        for(auto &p:adj){
            string s=p.first,temp=s;
            transform(temp.begin(),temp.end(),temp.begin(),::tolower);
            if(temp.rfind(input,0)==0) cout<<"- "<<s<<endl;
        }
    }

    // ---------- DIJKSTRA ----------
    vector<string> dijkstra(string start,string end,int &dist){
        map<string,int> d;
        map<string,string> parent;

        for(auto &p:adj) d[p.first]=INT_MAX;
        d[start]=0;

        priority_queue<pair<int,string>,vector<pair<int,string>>,greater<>> pq;
        pq.push({0,start});

        while(!pq.empty()){
            auto top=pq.top(); pq.pop();
            string node=top.second;

            for(auto &nbr:adj[node]){
                string next=nbr.first;
                int w=nbr.second;

                if(d[node]+w < d[next]){
                    d[next]=d[node]+w;
                    parent[next]=node;
                    pq.push({d[next],next});
                }
            }
        }

        vector<string> path;
        string cur=end;

        while(cur!=""){
            path.push_back(cur);
            cur=parent[cur];
        }

        reverse(path.begin(),path.end());
        dist=d[end];
        return path;
    }

    // ---------- BFS ----------
    vector<string> bfs(string start,string end){
        map<string,bool> vis;
        map<string,string> parent;
        queue<string> q;

        q.push(start);
        vis[start]=true;

        while(!q.empty()){
            string node=q.front(); q.pop();

            if(node==end) break;

            for(auto &nbr:adj[node]){
                string next=nbr.first;
                if(!vis[next]){
                    vis[next]=true;
                    parent[next]=node;
                    q.push(next);
                }
            }
        }

        vector<string> path;
        string cur=end;

        while(cur!=""){
            path.push_back(cur);
            cur=parent[cur];
        }

        reverse(path.begin(),path.end());
        return path;
    }

    // ---------- DFS ----------
    void dfsUtil(string node,string end,map<string,bool>&vis,
                 vector<string>&path,vector<string>&res){

        vis[node]=true;
        path.push_back(node);

        if(node==end){
            res=path;
            return;
        }

        for(auto &nbr:adj[node]){
            if(!vis[nbr.first]){
                dfsUtil(nbr.first,end,vis,path,res);
            }
        }

        path.pop_back();
    }

    vector<string> dfs(string start,string end){
        map<string,bool> vis;
        vector<string> path,res;
        dfsUtil(start,end,vis,path,res);
        return res;
    }

    // ---------- PRINT ROUTE ----------
    int printRoute(vector<string> path){
        int inter=0;

        cout<<"\n🚇 Route:\n";

        for(int i=0;i<path.size();i++){
            cout<<color[line[path[i]]] <<" "<<path[i]<<endl;

            if(i<path.size()-1 && line[path[i]]!=line[path[i+1]]){
                cout<<"⚠ Change "<<line[path[i]]
                    <<" → "<<line[path[i+1]]
                    <<" at "<<path[i]<<endl;
                inter++;
            }
        }

        return inter;
    }
};

// ---------------- QR ----------------
void generateQR(string data){
    string cmd="qrencode -o ticket.png -s 6 -m 2 \""+data+"\"";
    system(cmd.c_str());
}

// ---------------- SAVE ----------------
void saveTicket(Ticket t){
    ofstream f("ticket.txt");
    f<<"===== METRO TICKET =====\n";
    f<<"From: "<<t.source<<"\nTo: "<<t.destination<<endl;
    f<<"Distance: "<<t.distance<<" km\nFare: ₹"<<t.fare<<endl;
    f.close();
}

// ---------------- LOGIN ----------------
map<string,string> users;
hash<string> hasher;

void registerUser(){
    string u,p;
    cout<<"Username: "; cin>>u;
    cout<<"Password: "; cin>>p;
    users[u]=to_string(hasher(p));
}

bool login(){
    string u,p;
    cout<<"Username: "; cin>>u;
    cout<<"Password: "; cin>>p;

    return users[u]==to_string(hasher(p));
}

// ---------------- MAIN ----------------
int main(){
    Metro m;

    // COLORS
    m.color["Blue"]="🔵";
    m.color["Yellow"]="🟡";
    m.color["Red"]="🔴";

    // 🔵 BLUE LINE
    m.addEdge("Rajiv Chowk","Barakhamba Road",1);
    m.addEdge("Barakhamba Road","Mandi House",1);
    m.addEdge("Mandi House","Pragati Maidan",1);
    m.addEdge("Pragati Maidan","Indraprastha",1);
    m.addEdge("Indraprastha","Yamuna Bank",1);
    m.addEdge("Yamuna Bank","Akshardham",1);
    m.addEdge("Akshardham","Mayur Vihar Phase 1",1);

    // 🟡 YELLOW LINE
    m.addEdge("Rajiv Chowk","Patel Chowk",1);
    m.addEdge("Patel Chowk","Central Secretariat",1);
    m.addEdge("Central Secretariat","Udyog Bhawan",1);
    m.addEdge("Udyog Bhawan","AIIMS",2);
    m.addEdge("AIIMS","Green Park",1);
    m.addEdge("Green Park","Hauz Khas",1);

    // 🔴 RED LINE
    m.addEdge("Kashmere Gate","Tis Hazari",1);
    m.addEdge("Tis Hazari","Pul Bangash",1);
    m.addEdge("Pul Bangash","Pratap Nagar",1);
    m.addEdge("Kashmere Gate","Chandni Chowk",1);
    m.addEdge("Chandni Chowk","Red Fort",1);

    // 🔁 INTERCHANGES
    m.addEdge("Rajiv Chowk","Kashmere Gate",3);
    m.addEdge("Mandi House","Central Secretariat",2);

    // LINE MAP
    m.line["Rajiv Chowk"]="Blue";
    m.line["Barakhamba Road"]="Blue";
    m.line["Mandi House"]="Blue";
    m.line["Pragati Maidan"]="Blue";
    m.line["Indraprastha"]="Blue";
    m.line["Yamuna Bank"]="Blue";
    m.line["Akshardham"]="Blue";
    m.line["Mayur Vihar Phase 1"]="Blue";

    m.line["Patel Chowk"]="Yellow";
    m.line["Central Secretariat"]="Yellow";
    m.line["Udyog Bhawan"]="Yellow";
    m.line["AIIMS"]="Yellow";
    m.line["Green Park"]="Yellow";
    m.line["Hauz Khas"]="Yellow";

    m.line["Kashmere Gate"]="Red";
    m.line["Tis Hazari"]="Red";
    m.line["Pul Bangash"]="Red";
    m.line["Pratap Nagar"]="Red";
    m.line["Chandni Chowk"]="Red";
    m.line["Red Fort"]="Red";

    int ch;

    while(true){
        cout<<"\n1.Register\n2.Login\n3.Exit\n";
        cin>>ch;

        if(ch==1) registerUser();

        else if(ch==2 && login()){
            while(true){
                int op;
                cout<<"\n===== USER MENU =====\n";
                cout<<"1.Show Stations\n2.Find Route\n3.Book Ticket\n4.Exit\n";
                cin>>op; cin.ignore();

                if(op==1){
                    m.showStations();
                    continue;
                }

                string s1,s2;
                cout<<"From: "; getline(cin,s1);
                cout<<"To: "; getline(cin,s2);

                string start=m.findStation(s1);
                string end=m.findStation(s2);

                if(start==""||end==""){
                    cout<<"Invalid!\n";
                    m.suggest(s1);
                    continue;
                }

                int alg;
                cout<<"1.Dijkstra\n2.BFS\n3.DFS\n";
                cin>>alg;

                vector<string> path;
                int dist;

                if(alg==1) path=m.dijkstra(start,end,dist);
                else if(alg==2){ path=m.bfs(start,end); dist=path.size()-1; }
                else { path=m.dfs(start,end); dist=path.size()-1; }

                int inter=m.printRoute(path);

                int fare=(dist<=5)?10:20;

                cout<<"\n📏 "<<dist<<" km\n💰 ₹"<<fare<<endl;
                cout<<"🔁 Interchanges: "<<inter<<endl;

                if(op==3){
                    Ticket t{start,end,fare,dist};
                    saveTicket(t);

                    string qrData =
                        "FROM:"+start+
                        "\nTO:"+end+
                        "\nDIST:"+to_string(dist)+
                        "\nFARE:"+to_string(fare);

                    generateQR(qrData);

                    cout<<"🎟 Ticket Booked!\n";
                }

                if(op==4) break;
            }
        }
    }
}