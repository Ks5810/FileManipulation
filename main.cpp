#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define DEBUG(x) {std::cout<<x<<endl;}
#define rep(i,n) for(int i=0;i<n;i++)

using namespace std;

int main(){
    vector<vector<string>> buffer;
    vector<vector<int>> sets(5,vector<int>()); //counting 1s in the set
    vector<int> total_count(5,0);
    vector<int> set_count(5,0);
    vector<bool> pre_index(5,false);  //keep previous row for columns
    vector<int> cur_sum(5,0);
    
    ifstream infile("data.csv");
    ofstream outfile;
    string junk,line,word;
    const int MAX_ROW=14900;
    const int MAX_COL=13;
    
    //read the file
    while(getline(infile,line)){
        stringstream ss(line);
        buffer.emplace_back();
        while(getline(ss,word,',')){
            buffer.back().push_back(word);
        }
    }
    infile.close();
    
    //check values on column 8 to 12 in buffer, and get the size of each set,
    // and number of sets and total number of 1s in each columns.
    for(int i=1;i<MAX_ROW;i++){
        for(int j=8;j<MAX_COL;j++){
            int cur_val=stoi(buffer[i][j]);
            int col=j-8;
            total_count[col]+=cur_val;
            if(i!=1&&pre_index[col]==true&&!cur_val){
                set_count[col]++;
                pre_index[col]=false;
                sets[col].push_back(cur_sum[j-8]);
                cur_sum[col]=0;
            }
            else if(i==MAX_ROW-1&&cur_val){
                set_count[col]++;
                sets[col].push_back(++cur_sum[col]);
            }
            else{
                pre_index[col]=bool (cur_val);
                cur_sum[col]+=cur_val;
            }
        }
    }
    
    //write total count and set count into a file
    outfile.open("data_out.csv");
    if(outfile.is_open()){
        outfile<<"what";
        rep(i,5) outfile<<","<<to_string(i+14);
        outfile<<'\n';
        
        outfile<<"total count";
        rep(i,5) outfile<<","<<total_count[i];
        outfile<<'\n';
        
        outfile<<"set count";
        rep(i,5) outfile<<","<<set_count[i];
        outfile<<'\n';
    }
    outfile.close();
    
    //write size of set for corresponding columns into a file
    outfile.open("count_out.csv");
    if(outfile.is_open()){
        rep(i,5){
            outfile<<i+14;
            for(const auto j:sets[i])
                outfile<<','<<j;
            outfile<<'\n';
        }
    }
    outfile.close();
    
    return 0;
}