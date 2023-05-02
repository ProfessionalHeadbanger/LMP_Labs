#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Bottle {
    int fillTime;
    int corkTime;
    int id;
};

void backtrack(vector<Bottle>& bottles, vector<Bottle>& best_placement, vector<Bottle>& current_placement, int& best_time, vector<bool>& used)
{
    if (current_placement.size() == bottles.size())
    {
        int first_con = 0;  
        int second_con = 0;  
        for (int i = 0; i < current_placement.size(); i++)
        {
            Bottle& bottle = current_placement[i];
            first_con += bottle.fillTime;  
            if (first_con > second_con)
            {
                second_con = first_con + bottle.corkTime;  
            }
            else
            {
                second_con += bottle.corkTime;  
            }
        }
        if (second_con < best_time)
        {
            best_time = second_con;
            best_placement = current_placement;
            return;
        }
    }
    for (int i = 0; i < bottles.size(); i++)
    {
        if (!used[i])
        {
            used[i] = true;
            current_placement.push_back(bottles[i]);
            backtrack(bottles, best_placement, current_placement, best_time, used);
            current_placement.pop_back();
            used[i] = false;
        }
    }
}

void init(vector<Bottle>& bottles) {
    ifstream input("input.txt");
    int n;
    input >> n;

    for (int i = 0; i < n; i++) {
        Bottle bottle;
        input >> bottle.fillTime >> bottle.corkTime;
        bottle.id = i + 1;
        bottles.push_back(bottle);
    }

    input.close();
}

int main() {
    vector<Bottle> bottles;
    init(bottles);
    vector<Bottle> best_placement;
    vector<Bottle> current_placement;
    vector<bool> used(bottles.size(), false);
    int best_time = INT_MAX;

    backtrack(bottles, best_placement, current_placement, best_time, used);

    cout << "Best placement: ";
    for (int i = 0; i < best_placement.size(); i++)
    {
        cout << best_placement[i].id << " ";
    }
    cout << endl << "Best time: " << best_time << endl;
}
