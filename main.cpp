#include <iostream>
#include <cmath>
#include <vector>

using byte = unsigned char;

void freeMatrix(byte** matrix, size_t m) {
    for(int i = 0; i < m; i++)
        delete[] matrix[i];
    delete[] matrix;
}

void printMatrix(byte** matrix, size_t m, size_t n) {
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++)
            std::cout << (int)matrix[i][j] << '\t';
        std::cout << std::endl;
    }
}

/*
 * Стъпва на клетка с координати (x,y) (ако е възможно),
   отбелязва клетката като обходена
   увеличава count и добавя стойността ѝ в sum, след което
   пробва да обходи всичките ѝ съседи
 */
void dfsArea(byte** matrix, size_t m, size_t n, int x, int y, int& count, int& sum) {
    if (x < m && y < n && x >= 0 && y >= 0 && matrix[x][y] != 0) {
        // стъпваме
        count++;
        sum += matrix[x][y];
        matrix[x][y] = 0;
        // обхождаме съседите
        for(int dx = -1; dx <= 1; dx++)
            for(int dy = -1; dy <= 1; dy++)
                if (dx != 0 || dy != 0)
                    dfsArea(matrix, m, n, x + dx, y + dy, count, sum);
    }
}

struct Area {
    int x, y;
    double avg;
};

void sortAreas(Area* areas, size_t areaCount) {
    for(int i = 0; i < areaCount - 1; i++) {
        int maxi = i;
        for (int j = i + 1; j < areaCount; j++)
            if (areas[j].avg > areas[maxi].avg)
                maxi = j;
        std::swap(areas[maxi], areas[i]);
    }
}

void printAreas(Area* areas, size_t areaCount) {
    for(int i = 0; i < areaCount; i++) {
        std::cout << '(' << areas[i].x << ", " << areas[i].y << ") ";
        std::cout << areas[i].avg << ' ';
    }
    std::cout << std::endl;
}

void printAreasInfo(byte** matrix, size_t m, size_t n) {
    Area* areas = new Area[m * n];
    size_t areaCount = 0;
    int count = 0, sum = 0;
    for(int x = 0; x < m; x++)
        for(int y = 0; y < n; y++)
            if (matrix[x][y] != 0) {
                count = sum = 0;
                dfsArea(matrix, m, n, x, y, count, sum);
                areas[areaCount].x = x;
                areas[areaCount].y = y;
                std::cout << sum << std::endl;
                std::cout << count << std::endl;
                areas[areaCount].avg = (double)sum / count;
                areaCount++;
            }

    sortAreas(areas, areaCount);
    printAreas(areas, areaCount);

    delete[] areas;
}

void July13CSProblem1() {
    byte** matrix =  new byte*[6] {
        new byte[6] { 170, 0, 0, 255, 221, 0 },
        new byte[6] { 68, 0, 17, 0, 0, 68},
        new byte[6] { 221, 0, 238, 136, 0, 255 },
        new byte[6] { 0, 0, 85, 0, 136, 238 },
        new byte[6] { 238, 17, 0, 68, 0, 255 },
        new byte[6] { 85, 170, 0, 221, 17 ,0 },
    };

    const size_t m = 6;
    const size_t n = 6;

    printMatrix(matrix, m, n);
    printAreasInfo(matrix, m, n);
    freeMatrix(matrix, m);
}

//---------------------------------------------------------------------------

struct Element {
    int x, y;
    double val;
};

using SparseMatrix = std::vector<Element>;

SparseMatrix addSparseMatrices(SparseMatrix const& a, SparseMatrix const& b) {
    SparseMatrix result;
    int ia = 0, ib = 0;
    while (ia < a.size() && ib < b.size()) {
        if (a[ia].x == b[ib].x && a[ia].y == b[ib].y) {
            double sum = a[ia].val + b[ib].val;
            /* проверка дали елементът се нулира след сумата, може да не се изисква от представянето */
            const double EPS = 1E-6;
            if (std::fabs(sum) >= EPS)
                result.push_back({a[ia].x, a[ia].y, sum});
            ia++;
            ib++;
        }
        else if (a[ia].x < b[ib].x || a[ia].x == b[ib].x && a[ia].y < b[ib].y)
            result.push_back(a[ia++]);
        else
            result.push_back(b[ib++]);
    }
    // ia == a.size() || ib == b.size()
    for(; ia < a.size(); ia++)
        result.push_back(a[ia]);
    for(; ib < b.size(); ib++)
        result.push_back(b[ib]);
    return result;
}

void printSparseMatrix(SparseMatrix const& m) {
    for(int i = 0; i < m.size(); i++)
        std::cout << '(' << m[i].x << ", " << m[i].y << ", " << m[i].val << ") ";
    std::cout << std::endl;
}

void July13CSProblem2() {
    SparseMatrix a = { { 0, 0, 1.2 }, { 1, 5, 2.3 }, { 2, 8, 3.9 } };
    SparseMatrix b = { { 0, 0, 2.3 }, { 0, 10, 3.7 }, { 1, 7, 2.6 } };
    printSparseMatrix(addSparseMatrices(a, b));
}

int main() {
    // July13CSProblem1();
    // July13CSProblem2();
    return 0;
}
