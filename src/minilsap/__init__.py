"""Python module to solve the linear sum assignment problem (LSAP)
efficiently.
"""

from .solver import linear_sum_assignment
from ._version import __version_info__, __version__

__all__ = ("linear_sum_assignment", "__version_info__", "__version__")
