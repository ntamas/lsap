"""Python module to solve the linear sum assignment problem (LSAP)
efficiently.
"""

from .solver import solve
from ._version import __version_info__, __version__

__all__ = ("solve", "__version_info__", "__version__")
