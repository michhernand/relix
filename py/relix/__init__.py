import numpy as np
import pandas as pd
import typing as T
from numpy.typing import NDArray

from .relix_py import relix_cpp


def relative_importance(
        x: T.Union[pd.DataFrame, NDArray[np.float64]],
        y: T.Union[pd.Series, NDArray[np.float64]],
        algo: str,
) -> T.Union[pd.Series, NDArray[np.float64]]:
    """
    Calculates Relative Importnace of Linear Model Terms

    Args:
        x: DataFrame or 2D Numpy matrix of predictors.
        y: Series or 1D Numpy array of response variable.
        algo: String indicating which importance algorithm should be used.

    Returns:
        A Series or array with relative importance measures for each input column.
    """
    index_values = None
    if isinstance(x, pd.DataFrame):
        index_values = x.columns
        xx = x.values
    else:
        xx = x

    if isinstance(y, pd.Series):
        y = y.values

    return pd.Series(
            relix_cpp(xx, y, algo).flatten(),
            index=index_values,
    )
