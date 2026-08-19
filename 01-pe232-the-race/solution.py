# Project Euler 232 - The Race
# https://projecteuler.net/problem=232
#
# f[i][j] = P(player 2 eventually wins) from score (i, j), i,j < 100, player 1 to move.
# h[i][j] = same, but player 2 to move. Player 2 picks T to maximize h[i][j].
# f and h are mutually recursive (h(i,j) depends on f(i,j) itself on a miss), solved
# algebraically per state, then filled bottom-up since all transitions increase i or j.

TARGET = 100


def solve():
    f = [[0.0] * TARGET for _ in range(TARGET)]
    h = [[0.0] * TARGET for _ in range(TARGET)]

    for i in range(TARGET - 1, -1, -1):
        for j in range(TARGET - 1, -1, -1):
            h_next_i = h[i + 1][j] if i + 1 < TARGET else 0.0
            best = 0.0
            for T in range(1, 21):
                delta = 1 << (T - 1)
                p = 2.0 ** (-T)
                win_now = 1.0 if j + delta >= TARGET else f[i][j + delta]
                denom = 1 - 0.5 * (1 - p)
                hT = (p * win_now + 0.5 * (1 - p) * h_next_i) / denom
                if hT > best:
                    best = hT
            h[i][j] = best
            f[i][j] = 0.5 * h_next_i + 0.5 * best

    return f[0][0]


if __name__ == "__main__":
    print(f"{solve():.8f}")
