from __future__ import annotations

from typing import Sequence, Union, Tuple, TYPE_CHECKING

if TYPE_CHECKING:
    from numpy import ndarray
    from numpy.typing import ArrayLike


def linear_sum_assignment(
    cost_matrix: Union[Sequence[Sequence[float]], ArrayLike], maximize: bool = False
) -> Tuple[ndarray, ndarray]:
    """Solve the linear sum assignment problem.

    This function is a drop-in replacement for
    ``scipy.optimize.linear_sum_assignment()``.

    Parameters:
        cost_matrix: the cost matrix
        maximize: whether the total weight should be maximized (``True``) or
            minimized (``False``)

    Returns:
        an array of row indices and an array of column indices giving the optimal
        assignment. The cost of the assignment can be computed as
        ``cost_matrix[row_ind, col_ind].sum()``.
    """
    from numpy import asarray, float64
    from ._lsap import solve

    cost_matrix = asarray(cost_matrix, dtype=float64, order="C")
    return solve(cost_matrix, maximize)
