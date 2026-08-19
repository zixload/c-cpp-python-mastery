/* Project Euler 232 - The Race
 * https://projecteuler.net/problem=232
 *
 * f[i][j] = P(player 2 eventually wins) from score (i, j), i,j < 100, player 1 to move.
 * h[i][j] = same, but player 2 to move. Player 2 picks T to maximize h[i][j].
 * f and h are mutually recursive (h(i,j) depends on f(i,j) itself on a miss), solved
 * algebraically per state, then filled bottom-up since all transitions increase i or j.
 */
#include <stdio.h>
#include <math.h>

#define TARGET 100

static double f[TARGET][TARGET];
static double h[TARGET][TARGET];

int main(void) {
    for (int i = TARGET - 1; i >= 0; i--) {
        for (int j = TARGET - 1; j >= 0; j--) {
            double h_next_i = (i + 1 < TARGET) ? h[i + 1][j] : 0.0;
            double best = 0.0;
            for (int T = 1; T <= 20; T++) {
                long delta = 1L << (T - 1);
                double p = pow(2.0, -T);
                double win_now = (j + delta >= TARGET) ? 1.0 : f[i][j + delta];
                double denom = 1 - 0.5 * (1 - p);
                double hT = (p * win_now + 0.5 * (1 - p) * h_next_i) / denom;
                if (hT > best) best = hT;
            }
            h[i][j] = best;
            f[i][j] = 0.5 * h_next_i + 0.5 * best;
        }
    }

    printf("%.8f\n", f[0][0]);
    return 0;
}
