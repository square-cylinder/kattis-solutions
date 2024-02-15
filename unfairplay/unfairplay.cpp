#include <bits/stdc++.h>

using namespace std;
using veci = vector<int>;
using vecp = vector<pair<int, int>>;

bool validate(const veci& scores, const vecp& matches, const veci& answer) {
    int team_N = scores.back();
    veci results(scores);
    for (int i = 0; i < matches.size(); i++) {
        const auto& [team_1, team_2] = matches[i];
        const auto& result = answer[i];
        switch (result) {
        case 0:
            results[team_1] += 2;
            break;
        case 1:
            results[team_1] += 1;
            results[team_2] += 1;
            break;
        case 2:
            results[team_2] += 2;
            break;
        default:
            assert(false);
        }
    }
    for (int i = 0; i < results.size() - 1; i++) {
        if (results[i] >= results.back()) {
            return false;
        }
    }
    return true;
}

optional<veci> bruh_force(const veci& scores, const vecp& matches) {
    veci answer;
    answer.reserve(matches.size());
    vector<tuple<int, int, bool>> dfs;
    dfs.emplace_back(0, 0, true);
    dfs.emplace_back(0, 1, true);
    dfs.emplace_back(0, 2, true);
    while (!dfs.empty()) {
        auto [match_index, choice, first_visit] = dfs.back();
        if (match_index >= matches.size()) {
            if (validate(scores, matches, answer)) {
                return answer;
            }
            dfs.pop_back();
            continue;
        }
        if (first_visit) {
            answer.emplace_back(choice);
            get<2>(dfs.back()) = false;
            for (int i = 0; i < 3; i++) {
                dfs.emplace_back(match_index + 1, i, true);
            }
            continue;
        }
        answer.pop_back();
        dfs.pop_back();
    }
    return {};
}

int best_team_with_match(const veci& standings,
                         const vector<unordered_set<int>>& teams_matches) {
    int best_index = -1;
    int best_standing = -123;
    for (int i = 0; i < teams_matches.size() - 1; i++) {
        const auto score = standings[i];
        if (score > best_standing && teams_matches[i].size() > 0) {
            best_index = i;
            best_standing = score;
        }
    }
    return best_index;
}

// This solution probably won't ever work...
optional<veci> bruhless_force(const veci& scores, const vecp& matches) {
    veci answer;
    veci results(scores);
    vector<unordered_set<int>> teams_matches;
    teams_matches.resize(scores.size());
    for (int i = 0; i < matches.size(); i++) {
        const auto& [team1, team2] = matches[i];
        teams_matches[team1].emplace(i);
        teams_matches[team2].emplace(i);
    }
    int best = best_team_with_match(results, teams_matches);
    answer.resize(matches.size(), -1);
    while (best != -1) {
        unordered_set<int>& avail = teams_matches[best];
        if (avail.size() == 0) {
            best = best_team_with_match(results, teams_matches);
            continue;
        }
        int match = *avail.begin();
        for (auto i : avail) {
            auto [team1, team2] = matches[i];
            if (abs(results[team1] - results[team2]) > 1) {
                match = i;
                break;
            }
        }
        const auto [team1, team2] = matches[match];
        teams_matches[team1].erase(match);
        teams_matches[team2].erase(match);
        const int score1 = results[team1];
        const int score2 = results[team2];
        if (team1 == results.size() - 1) {
            answer[match] = 0;
            results[team1] += 2;
            continue;
        }
        if (team2 == results.size() - 1) {
            answer[match] = 2;
            results[team2] += 2;
            continue;
        }
        if (abs(score1 - score2) < 2) {
            results[team1]++;
            results[team2]++;
            answer[match] = 1;
        } else if (score1 > score2) {
            best = team1;
            results[team2] += 2;
            answer[match] = 2;
        } else {
            best = team2;
            results[team1] += 2;
            answer[match] = 0;
        }
    }
    for (int i = 0; i < results.size() - 1; i++) {
        if (results[i] >= results.back()) {
            return {};
        }
    }
    return answer;
}

struct FlowEdge {
    int cap, flow, dest;
};

struct Residual {
    int flowfrom, index;
    FlowEdge& get(vector<vector<FlowEdge>>& edges) const {
        return edges[flowfrom][index];
    }
};

optional<veci> go_with_the_flow(const veci& scores, const vecp& matches) {
    // Index and score of our team, score will be needed for construction of
    // flow graph
    const int ourbois = scores.size() - 1;
    int ourscore = scores.back();

    // Initialize our answer to be -1 which represents an unfinished answer
    vector<int> answer;
    answer.resize(matches.size(), -1);

    // We have one node for each match, one node for each team except ourselves,
    // a source and a sink
    vector<vector<FlowEdge>> edges;
    edges.resize(matches.size() + (scores.size() - 1) + 2);

    // We have one residual edge for every normal edge
    vector<vector<Residual>> residuals;
    residuals.resize(edges.size());

    // Some helpful offsets for finding matches, teams, the source and the sink
    // in the edge table
    const int m_off = 0;
    const int t_off = matches.size();
    const int source = matches.size() + (scores.size() - 1);
    const int sink = source + 1;

    // Process each match for the flow graph
    for (int i = 0; i < matches.size(); i++) {
        // We always want our team to win, and want to skip over these edges in
        // the flow graph
        const auto [team1, team2] = matches[i];
        if (team1 == ourbois) {
            answer[i] = 0;
            ourscore += 2;
        } else if (team2 == ourbois) {
            answer[i] = 2;
            ourscore += 2;
        } else {
            // Add an edge from the source node to this match with capacity 2
            edges[source].emplace_back(
                FlowEdge{.cap = 2, .flow = 0, .dest = m_off + i});
            // Add the residual
            residuals[m_off + i].emplace_back(
                Residual{.flowfrom = source,
                         .index = static_cast<int>(edges[source].size() - 1)});
            // Add an edge from the match to the node for team 1 with inf cap
            edges[m_off + i].emplace_back(
                FlowEdge{.cap = -1, .flow = 0, .dest = t_off + team1});
            // Add corresponding resudual
            residuals[t_off + team1].emplace_back(Residual{
                .flowfrom = m_off + i,
                .index = static_cast<int>(edges[m_off + i].size() - 1)});
            // Add edge from the match to the node for team 2 with inf cap
            edges[m_off + i].emplace_back(
                FlowEdge{.cap = -1, .flow = 0, .dest = t_off + team2});
            // Add corresponding residual
            residuals[t_off + team2].emplace_back(Residual{
                .flowfrom = m_off + i,
                .index = static_cast<int>(edges[m_off + i].size() - 1)});
        }
    }
    // Add the edges from the teams to the sink
    for (int i = 0; i < scores.size() - 1; i++) {
        const int theirscore = scores[i];
        const int cringe = ourscore - theirscore - 1;
        // If we have negative values it means we literally can't pass this
        // team, thus we early return
        if (cringe < 0) {
            return {};
        }
        // We don't add residual edges here since they should be unneccesary for
        // the sink
        edges[t_off + i].emplace_back(
            FlowEdge{.cap = cringe, .flow = 0, .dest = sink});
    }
    // Since I don't want to clear visited list every iteration, we just check
    // if we visited the node this iteration instead
    int iteration = 0;
    vector<int> visited;
    visited.resize(edges.size(), 0);
    // We want to continue finding paths until we fail to do so, in which case
    // we have a break condition later
    while (true) {
        iteration++;
        vector<pair<int, bool>> dfs;
        vector<int> path;
        dfs.emplace_back(source, true);
        while (!dfs.empty()) {
            const auto [cur, first_visit] = dfs.back();
            visited[cur] = iteration;
            // We went to the end, we're done
            if (cur == sink) {
                path.emplace_back(sink);
                break;
            }
            // We didn't find anything in this branch, move on
            if (!first_visit) {
                path.pop_back();
                dfs.pop_back();
                continue;
            }
            // Try exploring this branch
            dfs.back().second = false;
            path.emplace_back(cur);
            vector<FlowEdge>& connected = edges[cur];
            vector<Residual>& otherconn = residuals[cur];
            // Look through normal edges for a valid next node
            for (const auto& edge : connected) {
                // We can add it if it has availible bandwidth and is not
                // already passed through
                if ((edge.flow < edge.cap || edge.cap == -1) &&
                    visited[edge.dest] != iteration) {
                    dfs.emplace_back(edge.dest, true);
                }
            }
            // Look through residuals for valid next node
            for (const auto& res : otherconn) {
                const FlowEdge& actual = res.get(edges);
                // If we have some flow through the actual edge we can pass
                // through the residual edge
                if (actual.flow > 0 && visited[res.flowfrom] != iteration) {
                    dfs.emplace_back(res.flowfrom, true);
                }
            }
        }
        // If we didn't find anything when pathfinding we will have emptied the
        // path vector, another way would be to check the vector "dfs"
        if (path.size() == 0)
            break;

        // Find the bottleneck of the path and all its edges
        int bottleneck = 99999999;
        vector<pair<bool, FlowEdge*>> passed_edges;
        for (int i = 0; i < path.size() - 1; i++) {
            // Look between node i and node i + 1
            const int next = path[i + 1];
            bool found = false;
            // Look to see if we can find the edge we used in the normal edges
            for (int j = 0; j < edges[path[i]].size(); j++) {
                const auto& edge = edges[path[i]][j];
                if (edge.dest == next) {
                    found = true;
                    // Add it to our edges for later, false because it was not a
                    // residual edge
                    passed_edges.emplace_back(false, &edges[path[i]][j]);
                    // If edge.cap is -1 the edge is unlimited, so our
                    // bottleneck doesn't change
                    if (edge.cap == -1)
                        break;

                    // else our bottleneck will be at most the remaining
                    // capacity of the edge
                    const int remaining = edge.cap - edge.flow;
                    bottleneck = min(bottleneck, remaining);
                    break;
                }
            }
            // We have already found the edge, continue
            if (found)
                continue;
            // Look through residual edges
            for (int j = 0; j < residuals[path[i]].size(); j++) {
                const auto& res = residuals[path[i]][j];
                const auto& edge = res.get(edges);
                if (res.flowfrom == next) {
                    // This time we pass true because it is a residual edge
                    passed_edges.emplace_back(true, &res.get(edges));
                    // The maximum flow we can use through this edge is the flow
                    // we used to get here originally, i.e. everything >0
                    const int remaining = edge.flow;
                    bottleneck = min(bottleneck, remaining);
                    found = true;
                    break;
                }
            }
            assert(found);
        }
        // Go through all the edges we used in the path
        for (auto [was_residual, edge_p] : passed_edges) {
            // subtract, add the amount of flow we pushed through the system
            // depending on if we used a residual edge
            if (was_residual) {
                edge_p->flow -= bottleneck;
            } else {
                edge_p->flow += bottleneck;
            }
        }
    }
    // Once again go through matches
    for (int i = 0; i < matches.size(); i++) {
        const auto& [team1, team2] = matches[i];
        // We don't want to handle when our guys played again
        if (team1 != ourbois && team2 != ourbois) {
            const FlowEdge& e1 = edges[m_off + i][0];
            const FlowEdge& e2 = edges[m_off + i][1];
            // if the flow from this match does not add to 2, we could not
            // complete the flow graph, meaning we cannot distribute the scores
            // correctly
            if (e1.flow + e2.flow != 2)
                return {};
            // If the first edge pointed to the first team, then we have
            // e2.flow = 0 if first team won
            // e2.flow = 1 if it was a tie
            // e2.flow = 2 if first team lost
            // which is exactly what we want to output
            // The same goes for when they are reverse ordered
            if (e1.dest - t_off == team1) {
                answer[i] = e2.flow;
            } else {
                answer[i] = e1.flow;
            }
        }
    }

    return answer;
}

optional<string> solve_case(const veci& scores, const vecp& matches) {
    // optional<veci> maybesolution = bruhless_force(scores, matches);
    optional<veci> flow_ftw = go_with_the_flow(scores, matches);
    if (!flow_ftw.has_value()) {
        return {};
    }
    assert(validate(scores, matches, flow_ftw.value()));

    stringstream output;
    veci& solution = flow_ftw.value();
    if (solution.size() > 0) {
        output << solution[0];
    }
    for (int i = 1; i < solution.size(); i++) {
        output << " " << solution[i];
    }
    return output.str();
}

int main(int argc, char** argv) {
    while (true) {
        int n, m;
        cin >> n;
        if (n == -1) {
            break;
        }
        cin >> m;
        veci scores;
        vecp games;
        scores.reserve(n);
        games.reserve(m);
        for (int i = 0; i < n; i++) {
            int score;
            cin >> score;
            scores.emplace_back(score);
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            // Change indexing from 1..N to 0..N-1
            u -= 1;
            v -= 1;
            games.emplace_back(u, v);
        }
        optional<string> solution = solve_case(scores, games);
        cout << solution.value_or("NO") << "\n";
    }
    return 0;
}