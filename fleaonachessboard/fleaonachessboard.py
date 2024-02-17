def solve_case(S: int, ix: int, iy: int, dx: int, dy: int):
    visited_states = set()
    n = 0
    M = 2 * S
    x = ix % M
    y = iy % M
    while (x,y) not in visited_states:
        if (0 < x < S and S < y) or (S < x and 0 < y < S):
            print(f"After {n} jumps the flea lands at ({ix + n * dx}, {iy + n * dy}).")
            return
        visited_states.add((x,y))
        n += 1
        x = (x + dx) % M
        y = (y + dy) % M
    print("The flea cannot escape from black squares.")
        
        

def main():
    while True:
        inputs = tuple(map(int, input().split()))
        if sum(inputs) == 0:
            break
        S, x, y, dx, dy = inputs
        solve_case(S, x, y, dx, dy)
        


if __name__ == "__main__":
    main()
