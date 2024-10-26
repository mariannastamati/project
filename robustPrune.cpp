#include "robustPrune.h"
#include <limits>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "printGraph.h"

// Βοηθητική συνάρτηση για να πάρει την απόσταση αν υπάρχει ή να την υπολογίσει
float getDistance(int p1, int p2, const std::vector<std::vector<edge>>& graph, const std::vector<std::vector<float>>& data) {
    for (const auto& e : graph[p1]) {
        if (e.first == p2) {
            return e.second;  // Επιστρέφει την προϋπολογισμένη απόσταση
        }
    }
    // Αν δεν βρεθεί προϋπολογισμένη απόσταση, υπολογίζει την Ευκλείδεια απόσταση
    return EuclideanDistance(data[p1], data[p2]);
}

std::vector<std::vector<edge>> RobustPrune(int p, std::vector<int>& V, float a, int R, std::vector<std::vector<edge>>& graph, const std::vector<std::vector<float>>& data) {
    std::unordered_set<int> N_out;  // N_out(p)
    V.erase(std::remove(V.begin(), V.end(), p), V.end());  // V ← (V ∪ N_out(p)) \ {p}

    while (!V.empty()) {
        // p* ← arg minp'∈V d(p, p')
        int p_star = V[0];
        float min_dist = std::numeric_limits<float>::max();

        // Βρίσκουμε τον πλησιέστερο γείτονα στο V
        for (int v : V) {
            float dist = getDistance(p, v, graph, data);
            if (dist < min_dist) {
                min_dist = dist;
                p_star = v;
            }
        }

        // N_out(p) ← N_out(p) ∪ {p*}
        N_out.insert(p_star);

        // Αφαιρούμε τον p* από το V
        V.erase(std::remove(V.begin(), V.end(), p_star), V.end());

        // Αν το μέγεθος του N_out είναι R, διακόπτουμε
        if (N_out.size() >= static_cast<size_t>(R)) {  // Διόρθωση τύπου
            break;
        }

        // Αφαιρούμε τους μακρινούς κόμβους από το V σύμφωνα με τον κανόνα απόστασης
        V.erase(std::remove_if(V.begin(), V.end(), [&](int p_prime) {
            float dist_star_prime = getDistance(p_star, p_prime, graph, data);
            float dist_p_prime = getDistance(p, p_prime, graph, data);
            return (a * dist_star_prime <= dist_p_prime);
        }), V.end());
    }

    // Ενημέρωση του γράφου κρατώντας μόνο τις ακμές προς τους επιλεγμένους γείτονες
    std::vector<edge> new_edges;
    for (const auto& neighbor : N_out) {
        auto it = std::find_if(graph[p].begin(), graph[p].end(), [&](const edge& e) {
            return e.first == neighbor;
        });
        if (it != graph[p].end()) {
            new_edges.push_back(*it);
        } else {
            // Αν δεν υπάρχει ήδη ακμή, υπολογίζουμε και την προσθέτουμε
            float distance = EuclideanDistance(data[p], data[neighbor]);
            new_edges.emplace_back(neighbor, distance);
        }
    }

    // Ενημέρωση της λίστας γειτνίασης του p στο γράφο
    graph[p] = new_edges;

    return graph;
}