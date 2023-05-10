#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Bottle {
    int fillTime;
    int corkTime;
    int id;
};

void backtrack(vector<Bottle>& bottles, vector<Bottle>& best_placement, vector<Bottle>& current_placement, int& best_time, vector<bool>& used, int first_con, int second_con)
{
    if (current_placement.size() == bottles.size())
    {
        if (second_con < best_time || best_time == 0)
        {
            best_time = second_con;
            best_placement = current_placement;
        }
    }
    else
    {
        for (int i = 0; i < bottles.size(); i++)
        {
            if (!used[i])
            {
                Bottle& bottle = bottles[i];
                if (max(first_con + bottle.fillTime, second_con) + bottle.corkTime < best_time || best_time == 0)
                {
                    current_placement.push_back(bottle);
                    used[i] = true;
                    backtrack(bottles, best_placement, current_placement, best_time, used, first_con + bottle.fillTime, max(first_con + bottle.fillTime, second_con) + bottle.corkTime);
                    current_placement.pop_back();
                    used[i] = false;
                }
            }
        }
    }
}

void init(vector<Bottle>& bottles) {
    ifstream input("input1.txt");
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
    int best_time = 0;

    backtrack(bottles, best_placement, current_placement, best_time, used, 0, 0);

    cout << "Best placement: ";
    for (int i = 0; i < best_placement.size(); i++)
    {
        cout << best_placement[i].id << " ";
    }
    cout << endl << "Best time: " << best_time << endl;
}
