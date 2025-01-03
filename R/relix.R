#' Calculate Relative Importance of Linear Model Terms
#'
#' @param fit linear model from lm().
#' @param type relative importance algorithm to use.
#' @return dataframe showing relative importance per column.
#' @examples
#' \dontrun{
#' fit <- lm(mpg ~ hp + disp, data = mtcars)
#' relix::relix(fit, type = "last")
#' }
#'
#' @export
relix <- function(fit, type) {
  # independent variables
  model_matrix <- stats::model.matrix(fit)

  model_frame <- stats::model.frame(fit)
  model_response <- stats::model.response(model_frame)

  result <- relix_r(model_matrix, model_response, type)

  df <- data.frame(colnames(model_matrix), result)
  colnames(df) <- c("column", "importance")
  return(df)
}

# #' Calculates Relative Importance of Linear Model Terms From Data
# #'
# #' @title Calculate Relative Importance from Data
# #' @description Calc relative importance of terms in linear model (from data)
# #' @param x Numeric matrix of predictors
# #' @param y Numeric vector of response variable
# #' @param type String indicating which importance algorithm should be used.
# #' @param intercept Boolean indicating whether to include an intercept term.
# #' @return A numeric vector of relative importance values.
# #' @useDynLib relix _relix_relix_r
# #' @export
# NULL
