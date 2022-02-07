from minilsap import solve


def test_solve_square():
    mat = [[82, 83, 69, 92], [77, 37, 49, 92], [11, 69, 5, 86], [8, 9, 98, 23]]
    assert solve(mat).tolist() == [[0, 2], [1, 1], [2, 0], [3, 3]]


def test_solve_non_square():
    mat = [[82, 83, 69, 92], [77, 37, 49, 92], [11, 69, 5, 86]]
    assert solve(mat).tolist() == [[0, 2], [1, 1], [2, 0]]


def test_solve_empty():
    mat = []
    assert solve(mat).tolist() == []
    mat = [[]]
    assert solve(mat).tolist() == []
