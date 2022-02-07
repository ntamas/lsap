def solve(x, maximize: bool = False):
    from numpy import asarray, column_stack, float64
    from ._lsap import solve

    x = asarray(x, dtype=float64, order="C")
    row_ind, col_ind = solve(x, maximize)
    return column_stack([row_ind, col_ind])
