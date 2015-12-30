// Assignment 5

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

#include <cstdlib>

struct Vertex
{
    string name;
    bool isVisited;
    list<int> Adj_Vertices;
    
    list<pair<int, double> > adjacentVertices;
    int prev;
    double cost;
};

struct Container
{
    int vertex;
    int prev;
    double cost;
    
    bool operator<(const Container& v) const
    {
        return cost > v.cost;
    }
};

/*
 queue<int> BFS(int Origin, vector<Vertex>& database)
 {
 
 
 queue<int> Search;
 queue<int>Q;
 for(int i=0;i<database.size();i++)
 database[i].isVisited=false;
 database[Origin].isVisited=true;
 Search.push(Origin);
 Q.push(Origin);
 list<int>::const_iterator it;
 
 while(!Q.empty())
 {
 int a = Q.front();
 Q.pop();
 for(it=database[a].Adj_Vertices.begin();it!=database[a].Adj_Vertices.end();it++)
 {
 if(database[*it].isVisited==false)
 {
 database[*it].isVisited=true;
 Search.push(*it);
 Q.push(*it);
 }
 }
 }
 return Search;
 }
*/

queue<int> DFS(int Origin, vector<Vertex>& database)
{
    
    queue<int> Search;
    stack<int>Q;
    for(int i=0;i<database.size();i++)
        database[i].isVisited=false;
    Q.push(Origin);
    while(!Q.empty())
    {
        int a = Q.top();
        Q.pop();
        if(!database[a].isVisited)
        {
            database[a].isVisited=true;
            Search.push(a);
            list<int>::const_reverse_iterator it;
            for(it=database[a].Adj_Vertices.rbegin();it!=database[a].Adj_Vertices.rend();it++)
            {
                if(!database[*it].isVisited)
                {
                    Q.push(*it);
                }
            }
        }
    }
    return Search;
}

pair<stack<int>, double> getShortestRoute(int iStart, int iEnd, vector<Vertex>& database)
{
    pair<stack<int>, double> result;
    list<pair<int, double> >::iterator it;
    
    for(int i=0;i<database.size();i++)
    {
        database[i].cost=0;
        database[i].prev= -1;
        database[i].isVisited=false;
    }
    queue<int>Q;
    database[iStart].isVisited=true;
    Q.push(iStart);
    while(!Q.empty())
    {
        int a = Q.front();
        Q.pop();
        for(it=database[a].adjacentVertices.begin();it!=database[a].adjacentVertices.end();it++)
        {
            if(!database[it->first].isVisited)
            {
                database[it->first].isVisited =true;
                database[it->first].cost= database[a].cost+1;
                database[it->first].prev=a;
                Q.push(it->first);
            }
            if(it->first==iEnd)
            {
                while(!Q.empty())
                    Q.pop();
                break;
            }
        }
    }
    result.second = database[iEnd].cost;
    for(int svertex=iEnd;svertex >=0;svertex=database[svertex].prev)
        result.first.push(svertex);
    return result;
}

pair<stack<int>, double> getCheapestRoute(int iStart, int iEnd, vector<Vertex>& database)
{
    pair<stack<int>, double> result;
    list<pair<int, double> >::iterator it;
    
    for(int i=0;i<database.size();i++)
    {
        database[i].cost=0;
        database[i].prev= -1;
        database[i].isVisited=false;
    }
    
    priority_queue<Container>Q;
    
    Container Start;
    Start.cost=0;
    Start.vertex=iStart;
    Start.prev= -1;
    
    Q.push(Start);
    
    while(!Q.empty())
    {
        
        Container a = Q.top();
        Q.pop();
        
        if(database[a.vertex].isVisited) continue;
        
        database[a.vertex].isVisited = true;
        
        database[a.vertex].cost = a.cost;
        
        database[a.vertex].prev=a.prev;
        
        if(a.vertex ==iEnd)break;
        
        for(it=database[a.vertex].adjacentVertices.begin();it!=database[a.vertex].adjacentVertices.end();it++)
        {
            
            Container neighbor;
            neighbor.vertex= it->first;
            
            neighbor.cost=a.cost + it->second;
            
            neighbor.prev = a.vertex;
            
            Q.push(neighbor);
        }
    }
    
    result.second = database[iEnd].cost;
    
    for(int svertex=iEnd;svertex >=0;svertex=database[svertex].prev)
        result.first.push(svertex);
    return result;
}

int main() {
    ifstream fin;
    fin.open("map.txt");
    if (!fin.good())
        throw "I/O error";
    
    vector<Vertex> database;
    while (fin.good()) // EOF loop
    {
        string fromCity, toCity, cost;
        
        getline(fin, fromCity);
        getline(fin, toCity);
        getline(fin, cost);
        fin.ignore(1000, 10); // skip the separator
        
        fromCity.erase(remove_if(fromCity.begin(), fromCity.end(), ::isspace), fromCity.end());
        toCity.erase(remove_if(toCity.begin(), toCity.end(), ::isspace), toCity.end());
        
        
        int iToVertex = -1, iFromVertex = -1, i;
        for (i = 0; i < database.size(); i++) // seek "to" city
            if (database[i].name == fromCity)
                break;
        if (i == database.size()) // not in database yet
        {
            Vertex fromVertex;
            fromVertex.name = fromCity;
            database.push_back(fromVertex);
        }
        iFromVertex = i;
        
        for (i = 0; i < database.size(); i++) // seek "from" city
            if (database[i].name == toCity)
                break;
        if (i == database.size()) // not in vector yet
        {
            Vertex toVertex;
            toVertex.name = toCity;
            database.push_back(toVertex);
        }
        iToVertex = i;
        //For Graph Search
        database[iFromVertex].Adj_Vertices.push_back(iToVertex);
        database[iToVertex].Adj_Vertices.push_back(iFromVertex);
        //For Shortest & Cheapest Route
        double edgeCost = atof(cost.c_str());
        database[iFromVertex].adjacentVertices.push_back(pair<int, double>(iToVertex, edgeCost));
        database[iToVertex].adjacentVertices.push_back(pair<int, double>(iFromVertex, edgeCost));
    }
    fin.close();
    cout << "The Input file was processed" << endl;
    
    int input;
    cout << "Welcome to my graphing program! To begin, please select from the menu: " << endl;
    cout<<"1. Graph Search (Uses DFS-based calculated routes from start city)" << endl;
    cout<<"2. Graph Shortest Route (Uses edges on map to create shortest route using the least amount of edges)" << endl;
    cout<<"3. Graph Cheapest Route (Uses miles on map to create cheapest route using the least number of miles)" << endl;
    cout<<"4. Exit" << endl;
    cout<<"Input: ";
    cin >> input;
    switch (input) {
        case 1: {
                string Start_City;
                cout << "Enter the city you would like to start with: ";
                cin >> Start_City;
                if (Start_City.length() == 0)
                    break;
                
                int i;
                bool found = false;
                
                for (i = 0; i < database.size(); i++)
                    if (database[i].name == Start_City)
                    {
                        found=true;
                        break;
                    }
                if(found)
                {
                    /*
                     cout << "BFS";
                     queue<int> a = BFS(i, database);
                     while(!a.empty())
                     {
                     cout  << '-'<< database[a.front()].name;
                     a.pop();
                     }
                     cout << endl;
                    */
                    cout << "DFS";
                    queue<int> a = DFS(i, database);
                    while(!a.empty())
                    {
                        cout  << '-'<< database[a.front()].name;
                        a.pop();
                    }
                    cout << endl;
                }
                else
                    cout<< endl << "No city was found in the database"<<endl;
    
        } break;
        case 2: {

                string fromCity, toCity;
                cout << "\nEnter the source city: ";
                cin >> fromCity;
                if (fromCity.length() == 0) break;
                
                int iFrom;
                bool from=false;
                for (iFrom = 0; iFrom < database.size(); iFrom++)
                    if (database[iFrom].name == fromCity)
                    {
                        from=true;
                        break;
                    }
                cout << "Enter the destination city: ";
                cin >> toCity;
                if (toCity.length() == 0)
                    break;
                
                int iTo;
                bool to = false;
                for (iTo = 0; iTo < database.size(); iTo++)
                    if (database[iTo].name == toCity)
                    {
                        to =true;
                        break;
                    }
                if(from && to)
                {
                    pair<stack<int>, double> result = getShortestRoute(iFrom, iTo, database);
                    cout << "\nTotal edges: " << result.second;
                    while (!result.first.empty()){cout << '-' << database[result.first.top()].name; result.first.pop();}
                    cout<<endl;
                }
                else
                {
                    if(!from && !to)
                        cout<<"\nNo start city and end city was found in the database"<<endl;
                    else if(!from && to)
                        cout<<"\nNo start city was found in the database"<<endl;
                    else
                        cout<<"\nNo end city was found in the database"<<endl;
                }
            
        } break;
        case 3: {
                string fromCity, toCity;
                cout << "\nEnter the source city: ";
                cin >> fromCity;
                //getline(cin, fromCity);
                if (fromCity.length() == 0) break;
                
                
                
                int iFrom;
                bool from=false;
                for (iFrom = 0; iFrom < database.size(); iFrom++)
                    if (database[iFrom].name == fromCity)
                    {
                        from=true;
                        break;
                    }
                
                cout << "Enter the destination city: ";
                cin >> toCity;
                //getline(cin, toCity);
                if (toCity.length() == 0) break;
                
                
                bool to=false;
                int iTo;
                for (iTo = 0; iTo < database.size(); iTo++)
                    if (database[iTo].name == toCity)
                    {
                        to=true;
                        break;
                    }
                
                
                if(from && to)
                {
                    pair<stack<int>, double> result = getCheapestRoute(iFrom, iTo, database);
                    cout << "\nTotal miles: " << result.second;
                    while (!result.first.empty()){cout << '-' << database[result.first.top()].name; result.first.pop();}
                    cout << endl;
                }
                else
                {
                    if(!from && !to)
                        cout<<"\nNo start city and end city was found in the database"<<endl;
                    else if(!from && to)
                        cout<<"\nNo start city was found in the database"<<endl;
                    else
                        cout<<"\nNo end city was found in the database"<<endl;
                }
        } break;
        case 4: {
            break;
        }
    }
}
