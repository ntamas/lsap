from minilsap import linear_sum_assignment as solve


def test_solve_square():
    mat = [[82, 83, 69, 92], [77, 37, 49, 92], [11, 69, 5, 86], [8, 9, 98, 23]]
    rows, cols = solve(mat)
    assert rows.tolist() == [0, 1, 2, 3]
    assert cols.tolist() == [2, 1, 0, 3]


def test_solve_non_square():
    mat = [[82, 83, 69, 92], [77, 37, 49, 92], [11, 69, 5, 86]]
    rows, cols = solve(mat)
    assert rows.tolist() == [0, 1, 2]
    assert cols.tolist() == [2, 1, 0]


def test_solve_empty():
    rows, cols = solve([])
    assert rows.tolist() == []
    assert cols.tolist() == []

    rows, cols = solve([[]])
    assert rows.tolist() == []
    assert cols.tolist() == []
