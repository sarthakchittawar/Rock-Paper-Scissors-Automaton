#include <bits/stdc++.h>

using namespace std;

#define WIN (in_states[opp_state] == "R" && out_states[my_state] == "P") || (in_states[opp_state] == "P" && out_states[my_state] == "S") || (in_states[opp_state] == "S" && out_states[my_state] == "R")

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m;
    cin >> m;

    vector<string> in_states(m);
    vector<string> out_states;
    vector<vector<int>> in_transitions(m);
    vector<vector<int>> out_transitions;
    for (int i = 0; i < m; i++)
    {
        cin >> in_states[i];
        vector<int> v(3);
        cin >> v[0] >> v[1] >> v[2];
        in_transitions[i] = v;
    }
    int out_state_count = 0;
    int init_state;
    for (init_state = 0; init_state < m; init_state++)
    {
        string out_state;
        vector<pair<int, int>> draws;
        int rps_in, rps_out;
        if (in_states[init_state] == "R")
        {
            out_state = "P";
            rps_in = 1;
            rps_out = 0;
        }
        else if (in_states[init_state] == "P")
        {
            out_state = "S";
            rps_in = 2;
            rps_out = 1;
        }
        else if (in_states[init_state] == "S")
        {
            out_state = "R";
            rps_in = 0;
            rps_out = 2;
        }
        out_states.push_back(out_state);

        vector<int> v(3);
        int opp_state = init_state;
        int flag = 0;
        if (init_state != 0)
        {
            out_state_count = out_transitions.size() / (init_state);
        }
        out_transitions.push_back(v);
        int my_state = init_state * out_state_count;

        draws.push_back(make_pair(opp_state + 1, my_state + 1));
        opp_state = in_transitions[opp_state][rps_in];
        string opp_next = in_states[opp_state - 1];
        string next_state;
        int count = 1;
        while (count <= m)
        {
            if (opp_next == "R")
            {
                next_state = "P";
            }
            else if (opp_next == "P")
            {
                next_state = "S";
            }
            else if (opp_next == "S")
            {
                next_state = "R";
            }

            if (count == m)
            {
                for (int i = 0; i < draws.size(); i++)
                {
                    if (draws[i].first == opp_state)
                    {
                        out_transitions[my_state][rps_out] = draws[i].second;
                        out_state = next_state;
                        my_state = draws[i].second - 1;

                        opp_state = in_transitions[opp_state - 1][rps_in];
                        opp_next = in_states[opp_state - 1];
                        break;
                    }
                }
                count++;
                break;
            }

            else
            {
                out_states.push_back(next_state);
                vector<int> v(3);
                out_transitions.push_back(v);
                out_transitions[my_state][rps_out] = out_states.size();
                out_state = next_state;
                my_state++;

                draws.push_back(make_pair(opp_state, my_state + 1));

                if (opp_next == "R")
                {
                    rps_in = 1;
                    rps_out = 0;
                }
                else if (opp_next == "P")
                {
                    rps_in = 2;
                    rps_out = 1;
                }
                else if (opp_next == "S")
                {
                    rps_in = 0;
                    rps_out = 2;
                }

                opp_state = in_transitions[opp_state - 1][rps_in];
                opp_next = in_states[opp_state - 1];

                count++;
            }
        }
    }

    int total_size = out_states.size();
    int each_size = total_size / init_state;
    cout << total_size << endl;

    int my_state = 0;
    for (int i = 1; i < in_states.size(); i++)
    {
        int my_state = 0;
        int opp_state = i;
        int win = 0;

        int rps_in, rps_out;
        int count = 0;
        vector<pair<int, int>> visited;
        while (count++ < m * m)
        {
            if (my_state < 0 || opp_state < 0)
            {
                break;
            }
            win = 1;
            if (out_states[my_state] == "R")
            {
                rps_in = 0;
            }
            else if (out_states[my_state] == "P")
            {
                rps_in = 1;
            }
            else if (out_states[my_state] == "S")
            {
                rps_in = 2;
            }

            if (in_states[opp_state] == "R")
            {
                rps_out = 0;
            }
            else if (in_states[opp_state] == "P")
            {
                rps_out = 1;
            }
            else if (in_states[opp_state] == "S")
            {
                rps_out = 2;
            }
            
            int new_state = in_transitions[opp_state][rps_in] - 1;
            visited.push_back(make_pair(opp_state, my_state));

            if (out_transitions[my_state][rps_out] == 0 && (!(in_states[opp_state] == "R" && out_states[my_state] == "P") && !(in_states[opp_state] == "P" && out_states[my_state] == "S") && !(in_states[opp_state] == "S" && out_states[my_state] == "R")))
            {
                out_transitions[my_state][rps_out] = 1 + new_state * each_size;
                my_state = out_transitions[my_state][rps_out] - 1;
                opp_state = new_state;
                break;
            }
            if (new_state == opp_state && my_state == out_transitions[my_state][rps_out] - 1)
            {
                out_transitions[my_state][rps_out] = 1 + new_state * each_size;
                my_state = out_transitions[my_state][rps_out] - 1;
                opp_state = new_state;
                break;
            }

            int size = visited.size();
            for (int i = 3; i < m; i++)
            {
                if (size <= i)
                {
                    break;
                }
                if (visited[size - 1] == visited[size - i] && visited[size - 2] == visited[size - i - 1])
                {
                    out_transitions[my_state][rps_out] = 1 + new_state * each_size;
                    visited[size - 1].second = out_transitions[my_state][rps_out];
                    my_state = out_transitions[my_state][rps_out] - 1;
                    opp_state = new_state;
                    break;
                }
            }

            my_state = out_transitions[my_state][rps_out] - 1;
            opp_state = new_state;
        }
    }

    for (int i = 0; i < out_transitions.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (out_transitions[i][j] == 0)
            {
                out_transitions[i][j] = 1;
            }
        }
        cout << out_states[i] << " " << out_transitions[i][0] << " " << out_transitions[i][1] << " " << out_transitions[i][2] << endl;
    }

    return 0;
}