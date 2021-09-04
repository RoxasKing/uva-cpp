#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 50 + 1;
const int maxc = 1000 + 1;
const int full = maxc * maxc * maxc;
const int dx[] = {-1, 1, 0, 0, 0, 0};
const int dy[] = {0, 0, -1, 1, 0, 0};
const int dz[] = {0, 0, 0, 0, -1, 1};

int n, x0[maxn], y0[maxn], z0[maxn], x1[maxn], y1[maxn], z1[maxn];
int nx, X[maxn * 2], ny, Y[maxn * 2], nz, Z[maxn * 2];
int g[maxn * 2][maxn * 2][maxn * 2];

struct Cell {
    int x, y, z;
    Cell(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
    bool valid() const { return 0 <= x && x < nx - 1 && 0 <= y && y < ny - 1 && 0 <= z && z < nz - 1; }
    bool solid() const { return g[x][y][z] == 1; }
    bool getVis() const { return g[x][y][z] == 2; }
    void setVis() const { g[x][y][z] = 2; }
    Cell adj(int dir) const { return Cell(x + dx[dir], y + dy[dir], z + dz[dir]); }
    int area(int dir) const {
        if (dx[dir] != 0) return (Y[y + 1] - Y[y]) * (Z[z + 1] - Z[z]);
        if (dy[dir] != 0) return (X[x + 1] - X[x]) * (Z[z + 1] - Z[z]);
        return (X[x + 1] - X[x]) * (Y[y + 1] - Y[y]);
    }
    int volume() const { return (X[x + 1] - X[x]) * (Y[y + 1] - Y[y]) * (Z[z + 1] - Z[z]); }
};

Cell q[maxn * 2 * maxn * 2 * maxn * 2];
int head, tail;

void discretize(int* x, int& n) {
    sort(x, x + n);
    n = unique(x, x + n) - x;
}

int ID(int* x, int n, int x0) { return lower_bound(x, x + n, x0) - x; }

void floodfill(int& a, int& v) {
    a = v = 0;
    Cell c0;
    c0.setVis();
    head = tail = 0;
    q[tail] = c0;
    while (head <= tail) {
        Cell c0 = q[head++];
        v += c0.volume();
        for (int dir = 0; dir < 6; dir++) {
            Cell c = c0.adj(dir);
            if (!c.valid()) continue;
            if (c.solid()) {
                a += c0.area(dir);
            } else if (!c.getVis()) {
                c.setVis();
                q[++tail] = c;
            }
        }
    }
    v = full - v;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        X[0] = Y[0] = Z[0] = 0;
        X[1] = Y[1] = Z[1] = maxc;
        nx = ny = nz = 2;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d%d%d%d", &x0[i], &y0[i], &z0[i], &x1[i], &y1[i], &z1[i]);
            x1[i] += x0[i], y1[i] += y0[i], z1[i] += z0[i];
            X[nx++] = x0[i], X[nx++] = x1[i];
            Y[ny++] = y0[i], Y[ny++] = y1[i];
            Z[nz++] = z0[i], Z[nz++] = z1[i];
        }
        discretize(X, nx), discretize(Y, ny), discretize(Z, nz);

        memset(g, 0, sizeof(g));
        for (int i = 0; i < n; i++) {
            int xl = ID(X, nx, x0[i]), xr = ID(X, nx, x1[i]);
            int yl = ID(Y, ny, y0[i]), yr = ID(Y, ny, y1[i]);
            int zl = ID(Z, nz, z0[i]), zr = ID(Z, nz, z1[i]);
            for (int x = xl; x < xr; x++)
                for (int y = yl; y < yr; y++)
                    for (int z = zl; z < zr; z++) g[x][y][z] = 1;
        }

        int a, v;
        floodfill(a, v);
        printf("%d %d\n", a, v);
    }
    return 0;
}
