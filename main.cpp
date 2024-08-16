#include <iostream>

#include "graaf.hpp"

std::vector<std::vector<double>> floyd(GraafMetTakdata<GERICHT, int> &graaf) {
    std::vector<std::vector<double>> matrix(
        graaf.aantalKnopen(), std::vector<double>(graaf.aantalKnopen(), std::numeric_limits<double>::infinity()));

    // We need to fill the diagonals with 0 cause distance from node i to i is 0
    // For the rest, we just fill the distance from node i to its neighbour.
    for (int i = 0; i < graaf.aantalKnopen(); i++) {
        for (auto el : graaf[i]) {
            matrix[i][i] = 0;
            matrix[i][el.first] = *graaf.geefTakdata(i, el.first);
        }
    }

    // Then we iterate k times and each time take the min between the current value and value from previous matrix
    // See: https://www.youtube.com/watch?v=oNI0rf2P9gE
    for (int k = 0; k < graaf.aantalKnopen(); k++) {
        for (int i = 0; i < graaf.aantalKnopen(); i++) {
            for (int j = 0; j < graaf.aantalKnopen(); j++) {
                matrix[i][j] = std::min(matrix[i][j], (matrix[i][k] + matrix[k][j]));
            }
        }
    }

    return matrix;
}

int main() {
    GraafMetTakdata<GERICHT, int> graaf(4);

    graaf.voegVerbindingToe(0, 1, 3);
    graaf.voegVerbindingToe(1, 0, 8);
    graaf.voegVerbindingToe(1, 2, 2);
    graaf.voegVerbindingToe(2, 3, 1);
    graaf.voegVerbindingToe(3, 0, 2);
    graaf.voegVerbindingToe(0, 3, 7);
    graaf.voegVerbindingToe(2, 0, 5);

    std::vector<std::vector<double>> matrix = floyd(graaf);
    for (int i = 0; i < graaf.aantalKnopen(); i++) {
        for (int j = 0; j < graaf.aantalKnopen(); j++) {
            std::cout << " Distance from " << i << " to " <<  j << " is : " << matrix[i][j] << std::endl;
        }
    }
}
